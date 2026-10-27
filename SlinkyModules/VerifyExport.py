"""Verify the standalone source package. No original binary is loaded."""
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent
LEX = re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|R"([^ ()\\\t\r\n]*)\([\s\S]*?\)\1"|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|\d+(?:[\w.]*)|[^\s]', re.M)


def sha(data):
    return hashlib.sha256(data).hexdigest()


def tokens(code):
    return [m.group() for m in LEX.finditer(code) if not m.group().startswith(('//', '/*'))]


def normalize(code, names):
    code = re.sub(r'^\s*#(?:ifndef|define)\s+SLINKY_SHARE_[^\n]*$|^\s*#endif\s*//\s*SLINKY_SHARE_[^\n]*$', '', code, flags=re.M)
    code = re.sub(r'^\s*#\s*(?:include\s*(?:"[^"]+"|<[^>]+>)|pragma\s+once)[^\n]*$', '', code, flags=re.M)
    previous = []
    def replace(m):
        value = m.group()
        if value.startswith(('//', '/*')):
            return value
        member = previous[-1:] == ['.'] or previous[-2:] == ['-', '>']
        previous.append(value)
        return value if member else names.get(value, value)
    return LEX.sub(replace, code)


def main():
    manifest = json.loads((ROOT / 'ExportManifest.json').read_text())
    failures, bodies = [], {}
    for relative, expected in manifest['package_sha256'].items():
        path = ROOT / relative
        if not path.is_file() or sha(path.read_bytes()) != expected:
            failures.append('File hash mismatch: ' + relative)
    paths = sorted((ROOT / 'modules').glob('*.cpp'))
    if len(paths) != 68 or {p.name for p in paths} != {Path(m['file']).name for m in manifest['modules']}:
        failures.append('Module inventory mismatch')
    for path in paths:
        stack = []
        for line in path.read_text().splitlines(keepends=True):
            if line.startswith('// BEGIN SOURCE '):
                stack.append((line.removeprefix('// BEGIN SOURCE ').strip(), []))
            elif line.startswith('// END SOURCE '):
                label, body = stack.pop()
                if label != line.removeprefix('// END SOURCE ').strip():
                    failures.append('Source-region mismatch: ' + label)
                bodies[(path.relative_to(ROOT).as_posix(), label)] = ''.join(body)
            elif stack:
                stack[-1][1].append(line)
        if stack:
            failures.append('Unclosed source region: ' + path.name)
    for segment in manifest['source_segments']:
        original_names = {v: k for k, v in segment['identifier_renames'].items()}
        code = bodies.get((segment['export'], segment['source']), '')
        actual = sha(json.dumps(tokens(normalize(code, original_names)), separators=(',', ':')).encode())
        if actual != segment['token_sha256']:
            failures.append('Source token mismatch: ' + segment['source'])
    # Support can be checked independently of the original tree as well.
    for entry in manifest['support_files']:
        text = (ROOT / entry['export']).read_text()
        text = re.sub(r'^\s*#(?:ifndef|define)\s+SLINKY_SHARE_[^\n]*$|^\s*#endif\s*//\s*SLINKY_SHARE_[^\n]*$', '', text, flags=re.M)
        actual = sha(json.dumps(tokens(text), separators=(',', ':')).encode())
        if actual != entry['token_sha256']:
            failures.append('Support token mismatch: ' + entry['source'])
    build = json.loads((ROOT / 'BuildVerification.json').read_text())
    if not build['passed'] or not build['source_snapshot_stable']:
        failures.append('Build/link verification did not pass')
    for relative, expected in build['source_sha256'].items():
        if sha((ROOT / relative).read_bytes()) != expected:
            failures.append('Build source snapshot mismatch: ' + relative)
    report = {'passed': not failures, 'modules': len(paths), 'source_segments': len(manifest['source_segments']),
              'support_files': len(manifest['support_files']), 'package_files': len(manifest['package_sha256']),
              'build_link_passed': build['passed'], 'failures': failures}
    print(json.dumps(report, indent=2))
    raise SystemExit(0 if not failures else 1)


if __name__ == '__main__':
    main()
