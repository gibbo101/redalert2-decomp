#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Copy read-only native-resolved map terrain inputs into an ignored fixture."""
import argparse
import hashlib
import json
import shlex
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--data-dir', type=Path, required=True)
    p.add_argument('--map', default='mp03t4.map')
    p.add_argument('--inspector', type=Path, default=ROOT/'build/native/archive-inspect')
    p.add_argument('--output', type=Path, required=True)
    a = p.parse_args()
    destination = a.output.resolve()
    if not destination.is_relative_to(ROOT/'private') or destination.exists():
        raise ValueError('Choose a new ignored private fixture directory')
    source = a.data_dir.resolve()
    if destination.is_relative_to(source) or source.is_relative_to(destination):
        raise ValueError('Fixture must be separate from supplied installation')
    result = subprocess.run([str(a.inspector),str(source),'--prototype-inputs',a.map],
                            check=True, capture_output=True, text=True)
    selected = {}
    for line in result.stdout.splitlines():
        if not line.startswith('Q '):
            continue
        _, name, _, _, file, offset, size, digest = shlex.split(line)
        if not name.lower().endswith('.tem') and name.lower() not in ('temperat.ini','rules.ini',a.map.lower()):
            continue
        name = name.lower()
        if Path(name).name != name or name in selected:
            raise ValueError('Invalid/duplicate fixture name')
        with Path(file).open('rb') as stream:
            stream.seek(int(offset))
            data = stream.read(int(size))
        if hashlib.sha256(data).hexdigest() != digest:
            raise ValueError('Resolved supplied slice changed: '+name)
        selected[name] = (data, {'file':file,'offset':int(offset),'size':int(size),'sha256':digest})
    if not all(name in selected for name in ('temperat.ini','rules.ini',a.map.lower())):
        raise ValueError('Missing supplied map/INI inputs')
    destination.mkdir(parents=True)
    for name,(data,_) in selected.items():
        (destination/name).write_bytes(data)
    manifest = {'inspector_sha256':hashlib.sha256(a.inspector.read_bytes()).hexdigest(),
                'files':{name:record for name,(_,record) in selected.items()},
                'boundary':'Native-decoded indexes and file resolution supply fixtures; no original archive/parser parity is implied.'}
    (destination/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    print(f'{len(selected)} supplied slices copied privately; source files unchanged')

if __name__ == '__main__':
    main()
