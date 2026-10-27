"""Compile each recovered callback component as C++ with bounded subprocesses."""

import hashlib
import json
import subprocess
import tempfile
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parent


def main():
    manifest = json.loads((ROOT / "manifest.json").read_text(encoding="utf-8"))
    start = time.monotonic()
    results = []
    with tempfile.TemporaryDirectory() as directory:
        for component in manifest["components"]:
            if time.monotonic() - start > 120:
                raise TimeoutError("120-second C++ build limit reached")
            source = ROOT.parent.parent / component["cpp"]
            assert source.is_file(), source
            process = subprocess.run(
                ["cl", "/nologo", "/std:c++20", "/EHsc", "/c", "/TP",
                 f"/Fo{directory}\\component.obj", str(source)],
                capture_output=True, text=True, timeout=10,
            )
            errors = [line.strip() for line in (process.stdout + "\n" + process.stderr).splitlines()
                      if "error " in line.lower()]
            results.append({
                "cpp": component["cpp"],
                "cpp_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
                "compiled_as_cpp": process.returncode == 0,
                "errors": errors,
            })
    report = {"component_count": len(results), "compiled_as_cpp": sum(x["compiled_as_cpp"] for x in results),
              "compiler": "MSVC cl /std:c++20 /EHsc /c /TP", "results": results}
    (ROOT / "build_report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8", newline="\n")
    print(f"{report['compiled_as_cpp']}/{report['component_count']} callback components compile as C++")
    for result in results:
        if not result["compiled_as_cpp"]:
            print(result["cpp"], result["errors"][0] if result["errors"] else "compiler failed without error text")


if __name__ == "__main__":
    main()
