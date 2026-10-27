#!/usr/bin/env python3
"""Regenerate accepted seed-generated sources with the current seed generator.

Only canonical sources from the ghidra-seed-sweep family that still carry the
seed-generated marker (or the pre-marker seed banner) are rewritten; a file
edited by hand has the marker removed and is never touched. Catalog source
hashes are updated and the shared header list is synchronized with
src/shared. Every changed file is compiled with its recorded options before it is
written; a rewrite is applied only if it still produces the original bytes.
A file whose new output does not match keeps its matching text and is frozen
(marker replaced), so later generator changes never regress accepted source.
Run ./build.command afterwards to verify the complete file.
"""
import argparse
import json
from pathlib import Path
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

from canonical import sha
from inventory import Inventory
from seed_candidate import MARKER, accepted_sources, seed
import catalog_io

OLD_BANNER = '// Ghidra seed for 0x'
FROZEN = ('// seed-frozen: a newer seed generator no longer reproduced this function;\n'
          '// this matching version is kept and is not regenerated.')


def verify(pending):
    """Compile candidate rewrites with each region's options; return exact entries."""
    import capstone
    import diff_candidate as diff
    from build import wine_command, win
    from coff import Coff
    from verify_manifest import Audit
    config = json.loads((REPOSITORY / 'private/original-target.local.json').read_bytes())
    audit = Audit(REPOSITORY, config['executable'])
    work = REPOSITORY / 'build/regenerate-check'; work.mkdir(parents=True, exist_ok=True)
    compiler = win(Path(config['compiler_directory']) / 'CL.EXE'); lines = []
    for region, _, text in pending:
        source = work / ('%08x.cpp' % region['entry']); source.write_text(text)
        obj = source.with_suffix('.obj')
        if obj.exists(): obj.unlink()
        lines.append('"%s" %s >"%s" 2>&1' % (compiler, ' '.join('"' + a + '"' for a in diff.compiler_args(region['options']) + [
            '/I' + win(REPOSITORY / 'src'), '/Fo' + win(obj), win(source)]), win(source.with_suffix('.log'))))
    wine_command(config, work, lines + ['exit /b 0'], 'regenerate-check', timeout=1800)
    exact = set()
    for region, _, text in pending:
        obj = work / ('%08x.obj' % region['entry'])
        if not obj.exists():
            continue
        coff = Coff(obj.read_bytes())
        try:
            symbol, section, start, end = coff.function(region['symbol_prefix'])
        except ValueError:
            continue
        if symbol['name'] != region['symbol']:
            continue
        relocs = [(o - start, i, k) for o, i, k in section['relocs'] if start <= o < end]
        data, unresolved = diff.resolve(section['data'][start:end], relocs, coff.symbols, region['entry'],
                                        region['references'])
        if not unresolved and data == audit.original(region['entry'], region['full_extent_bytes']):
            exact.add(region['entry'])
    return exact


def regenerable(text):
    return MARKER.splitlines()[0] in text or (text.startswith(OLD_BANNER) and FROZEN.splitlines()[0] not in text)


def sync_headers(catalog):
    known = {h['path']: h for h in catalog.get('headers', [])}
    for path in sorted((REPOSITORY / 'src/shared').rglob('*.hpp')):
        relative = path.relative_to(REPOSITORY).as_posix()
        known[relative] = dict(path=relative, sha256=sha(path.read_bytes()))
    catalog['headers'] = [known[k] for k in [h['path'] for h in catalog.get('headers', [])] if k in known] + \
                         [v for k, v in known.items() if k not in {h['path'] for h in catalog.get('headers', [])}]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--dry-run', action='store_true')
    args = parser.parse_args()
    catalog_path = REPOSITORY / 'manifests/original_target.json'
    catalog = catalog_io.loads(catalog_path.read_bytes())
    accepted = accepted_sources(catalog)
    # Regenerate each seed from the inventory pass its population was accepted
    # under (matched by functions.jsonl hash), so bounds and exports never drift.
    from inventory import PASSES
    by_hash = {}
    for directory in PASSES:
        by_hash[sha((directory / 'functions.jsonl').read_bytes())] = directory
    population_pass = {p['id']: by_hash.get(p['inventory_sha256']) for p in catalog['populations']}
    inventories = {}
    changed = kept = 0
    pending = []
    for region in catalog['regions']:
        if region.get('source_quality_family') != 'ghidra-seed-sweep':
            continue
        path = REPOSITORY / region['source']
        current = path.read_text()
        if not regenerable(current):
            kept += 1; continue
        directory = population_pass.get(region['population'])
        if directory is None:
            kept += 1; continue
        inventory = inventories.setdefault(directory, Inventory([directory] + [d for d in PASSES if d != directory]))
        text = seed(region['entry'], inventory, accepted)
        if text == current:
            continue
        pending.append((region, path, text))
    frozen = 0
    if pending and not args.dry_run:
        exact = verify(pending)
        for region, path, text in pending:
            if region['entry'] in exact:
                changed += 1
                path.write_text(text); region['source_sha256'] = sha(path.read_bytes())
            else:
                frozen += 1
                path.write_text(path.read_text().replace(MARKER, FROZEN))
                region['source_sha256'] = sha(path.read_bytes())
    if not args.dry_run:
        sync_headers(catalog)
        catalog_io.dump(catalog, catalog_path)
    print(json.dumps(dict(regenerated=changed, frozen=frozen, kept_manual=kept,
                          pending=len(pending), dry_run=args.dry_run)))


if __name__ == '__main__':
    main()
