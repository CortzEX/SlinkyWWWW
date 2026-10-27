#!/usr/bin/env python3
"""Extract OpenSlinkyPlus module/settings metadata from payload jars."""
import json
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
JAR = ROOT / 'SlinkyNative' / 'payload' / 'slinky-intermediary.jar'
OUT = ROOT / 'osp_modules_metadata.json'

def main():
    z = zipfile.ZipFile(JAR)
    widget = json.loads(z.read('assets/slinkysemantic/WidgetMetadata.json'))
    ui = json.loads(z.read('assets/slinkysemantic/ModuleUi.json'))
    initial = json.loads(z.read('assets/slinkysemantic/InitialSettings.json'))

    modules = []
    ui_map = {m['module']: m for m in ui['modules']}
    init_map = initial.get('modules', {})

    for mod, settings_meta in widget.items():
        ui_entry = ui_map.get(mod, {})
        controls = []
        for variant in ui_entry.get('variants', []):
            for ctrl in variant.get('controls', []):
                if 'key' in ctrl:
                    controls.append(ctrl)
        # build ordered list using controls order
        settings = []
        for ctrl in controls:
            key = ctrl.get('key')
            meta = settings_meta.get(key, {})
            init = init_map.get(mod, {}).get(key, {})
            settings.append({
                'key': key,
                'label': meta.get('label'),
                'title': meta.get('title'),
                'section': ctrl.get('section'),
                'has_suggestions': meta.get('suggestions_endpoint_present', False),
                'initial_value': init.get('value') if isinstance(init, dict) else init,
                'raw_meta_keys': list(meta.keys()),
            })
        modules.append({
            'module': mod,
            'ui_controls_count': len(controls),
            'settings': settings,
        })
    OUT.write_text(json.dumps(modules, indent=2), encoding='utf-8')
    print(f"saved {OUT}")

if __name__ == '__main__':
    main()
