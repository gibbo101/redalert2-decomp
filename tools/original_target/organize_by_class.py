#!/usr/bin/env python3
"""Move class-owned accepted sources into src/recovered/classes/<Class>/.

Files directly under src/recovered/ (address-named discovery files) move in,
and files already under classes/ are re-filed when their owner changes;
family directories keep their own organization. Ownership comes from
class_owners.py (RTTI vtable slots and vptr writers). Files are moved with
`git mv` and catalog source paths updated; contents, compiler populations,
options and bindings are unchanged, so the build output is unaffected.
"""
import argparse
import json
from pathlib import Path
import re
import subprocess
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from class_owners import ClassOwners
import catalog_io


def directory_name(class_name):
    """'DynamicVectorClass<AbstractClass *>' -> 'DynamicVectorClass_AbstractClass_ptr'."""
    name = class_name.replace('::', '__').replace(' *', '_ptr').replace('*', '_ptr').replace('&', '_ref')
    name = re.sub(r'[<>, ]+', '_', name).strip('_')
    return re.sub(r'[^A-Za-z0-9_]', '', name)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()
    catalog_path = REPOSITORY / 'manifests/original_target.json'
    catalog = catalog_io.loads(catalog_path.read_bytes())
    owners = ClassOwners(); moved = 0
    for region in catalog['regions']:
        source = Path(region['source'])
        if region.get('semantic_name') or region.get('source_quality_family') == 'hand-written':
            continue    # named, hand-placed sources keep their location
        in_classes = source.parts[:3] == ('src', 'recovered', 'classes')
        if source.parent != Path('src/recovered') and not in_classes:
            continue
        owner = owners.owner(region['entry'])
        if owner:
            destination = Path('src/recovered/classes') / directory_name(owner[0]) / source.name
        elif in_classes:
            destination = Path('src/recovered') / source.name      # ownership withdrawn
        else:
            continue
        if destination == source:
            continue
        if (REPOSITORY / destination).exists():
            continue
        moved += 1
        if not args.dry_run:
            (REPOSITORY / destination).parent.mkdir(parents=True, exist_ok=True)
            tracked = subprocess.run(['git', 'ls-files', '--error-unmatch', str(source)], cwd=REPOSITORY,
                                     capture_output=True).returncode == 0
            if tracked:
                subprocess.run(['git', 'mv', str(source), str(destination)], cwd=REPOSITORY, check=True)
            else:
                (REPOSITORY / source).rename(REPOSITORY / destination)   # newly promoted, not yet committed
            region['source'] = destination.as_posix()
    if not args.dry_run:
        catalog_io.dump(catalog, catalog_path)
    print(json.dumps(dict(moved=moved, dry_run=args.dry_run)))


if __name__ == '__main__':
    main()
