#!/usr/bin/env python3
"""Write byte-free import facts: manifests/imports.json.

For each PE import: DLL, name, import-address-table slot VA and, where the
Ghidra import metadata has one, its calling convention and parameter count.
Seeds use these to declare API calls as dllimport functions bound to their
original IAT slots (`call dword ptr [__imp__Name@N]`).
"""
import json
from pathlib import Path
import re

REPOSITORY = Path(__file__).resolve().parents[2]
EXTERNALS = REPOSITORY / 'private/original-target-20261020/inventory/external-functions.jsonl'


def main():
    import pefile
    config = json.loads((REPOSITORY / 'private/original-target.local.json').read_bytes())
    pe = pefile.PE(config['executable'])
    signatures = {}
    if EXTERNALS.exists():
        for row in map(json.loads, EXTERNALS.read_text().splitlines()):
            name = row['name'].split('::')[-1]
            match = re.search(r'\((.*)\)', row.get('signature', ''))
            params = [p for p in (match.group(1).split(',') if match else []) if p.strip() not in ('', 'void')]
            signatures[name] = dict(convention=row.get('calling_convention'), parameters=len(params),
                                    signature=row.get('signature'))
    imports = []
    for directory in pe.DIRECTORY_ENTRY_IMPORT:
        for item in directory.imports:
            if not item.name:
                continue
            name = item.name.decode()
            imports.append(dict(dll=directory.dll.decode(), name=name, iat='%08x' % item.address,
                                **signatures.get(name, {})))
    (REPOSITORY / 'manifests/imports.json').write_text(json.dumps(dict(
        source='PE import directory of the supplied executable; Ghidra import signatures',
        imports=imports), indent=1) + '\n')
    print(len(imports), 'imports')


if __name__ == '__main__':
    main()
