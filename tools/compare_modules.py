#!/usr/bin/env python3
"""Compare docs.slinky.gg settings with OpenSlinkyPlus metadata (semantic)."""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
docs = json.loads((ROOT / 'docs_modules_raw.json').read_text())
osp = json.loads((ROOT / 'osp_modules_metadata.json').read_text())


def norm(s):
    if not s:
        return ''
    return s.lower().replace(' ', '').replace('-', '').replace('_', '')


def token_set(s):
    return set(norm(w) for w in str(s).lower().split() if len(w) > 2)


docs_by = {norm(m['module']): m for m in docs}
osp_by = {norm(m['module']): m for m in osp}

report_modules = []
high = medium = low = none = 0

for osp_mod in osp:
    key = norm(osp_mod['module'])
    doc = docs_by.get(key)
    if not doc:
        report_modules.append({
            'module': osp_mod['module'],
            'category': 'unknown',
            'docs_url': None,
            'discrepancies': ['OSP module not found in docs'],
            'severity': 'medium',
        })
        medium += 1
        continue

    docs_text = ' '.join(s['name'] + ' ' + s['description'] for s in doc['settings'])
    docs_names = [s['name'] for s in doc['settings']]
    docs_norm_names = {norm(n) for n in docs_names}

    discrepancies = []
    # Check each OSP label against docs text
    for s in osp_mod['settings']:
        label = s['label'] or s['key']
        nlabel = norm(label)
        if nlabel not in docs_text and not any(tok in docs_text for tok in token_set(label)):
            discrepancies.append(f"OSP setting '{label}' not mentioned in docs")
        # Red-flag suggestion endpoints that aren't Teams/AutoTool/BlockESP/ItemESP/Weapons/AutoSoup
        if s.get('has_suggestions'):
            if osp_mod['module'] == 'Teams' and s['key'] == 'team_colors':
                pass  # patched
            elif osp_mod['module'] == 'Auto Tool' and s['key'] == 'allowed_blocks':
                discrepancies.append(f"Auto Tool allowed_blocks likely needs block suggestions, currently returns items")
            elif osp_mod['module'] == 'Block ESP' and s['key'] == 'allowed_blocks':
                pass
            elif osp_mod['module'] in ('Item ESP', 'Auto Soup', 'Weapons') and s['key'] in ('allowed_items', 'extra_items'):
                pass
            else:
                discrepancies.append(f"Unexpected suggestions endpoint on '{label}'")

    # Check each docs heading against OSP labels
    osp_labels_norm = {norm(s['label'] or s['key'] or '') for s in osp_mod['settings']}
    for dname in docs_names:
        nd = norm(dname)
        if nd not in osp_labels_norm and not any(nd in lab for lab in osp_labels_norm):
            # Maybe docs heading is a section containing OSP labels; check if any OSP label words appear in docs text for this heading
            # Heuristic: if dname words appear in OSP labels
            words = token_set(dname)
            if not words & osp_labels_norm:
                discrepancies.append(f"Docs setting '{dname}' has no matching OSP label")

    if discrepancies:
        # classify severity
        if any('likely needs block' in d or 'Unexpected suggestions' in d or 'not mentioned in docs' in d for d in discrepancies):
            sev = 'high'
        else:
            sev = 'low'
    else:
        sev = 'none'

    if sev == 'high': high += 1
    elif sev == 'medium': medium += 1
    elif sev == 'low': low += 1
    else: none += 1

    report_modules.append({
        'module': osp_mod['module'],
        'category': doc['category'],
        'docs_url': doc['url'],
        'docs_settings': docs_names,
        'osp_settings': [s['label'] or s['key'] for s in osp_mod['settings']],
        'discrepancies': discrepancies,
        'severity': sev,
    })

# Docs modules missing in OSP
for doc in docs:
    key = norm(doc['module'])
    if key not in osp_by:
        report_modules.append({
            'module': doc['module'],
            'category': doc['category'],
            'docs_url': doc['url'],
            'discrepancies': ['Docs module not found in OSP'],
            'severity': 'medium',
        })
        medium += 1

report = {
    'summary': {
        'docs_modules': len(docs),
        'osp_modules': len(osp),
        'high_severity': high,
        'medium_severity': medium,
        'low_severity': low,
        'matching': none,
    },
    'modules': sorted(report_modules, key=lambda x: (x['severity'] != 'high', x['severity'] != 'medium', x['module'])),
}
(ROOT / 'docs_comparison_report.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
print(json.dumps(report['summary'], indent=2))
print('\nHIGH/MEDIUM issues:')
for m in report['modules']:
    if m['severity'] in ('high', 'medium'):
        print(f"[{m['severity'].upper()}] {m['module']}: {m['discrepancies']}")
