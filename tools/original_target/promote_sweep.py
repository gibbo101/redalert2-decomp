#!/usr/bin/env python3
"""Promote byte-exact sweep seeds through strict acceptance into canonical source.

For each `byte_exact` row in a sweep's results.jsonl this tool regenerates the
namespaced Ghidra seed, freezes a candidate population per inventory pass
(frozen bounds, independent gap padding, references bound by address-named
symbol prefixes), runs compile_candidates.py, and installs only rows that pass
its strict audit as `src/recovered/<entry>.cpp` with new catalog populations.

Prefilter: a seed whose own sweep object emitted data sections or extra code
(string literals, float constants, compiler helpers) would make the whole
population object unauditable, so it is left in the queue for manual work.

Run ./build.command afterwards; it must reproduce the complete file.
"""
import argparse
import json
from pathlib import Path
import re
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

from canonical import sha
from coff import Coff
from inventory import Inventory
from seed_candidate import MARKER, accepted_sources, seed
import diff_candidate as diff
import catalog_io

NAMES = re.compile(r'\b(_?PTR_(?:\w+?_)?[0-9a-f]{8}|_?DAT_[0-9a-f]{8}|LAB_[0-9a-f]{8}|FUN_[0-9a-f]{8}|'
                   r'[su]_\w*_[0-9a-f]{8})\b')
CONFIGS = ['original-target.local.json', 'original-target.wine.json', 'original-target.crossover.json',
           'original-target.interactive.json', 'original-target.sweep-b.json',
           'original-target.permute.json', 'original-target.w3.json', 'original-target.w4.json',
           'original-target.w5.json', 'original-target.win.json']


def clean_object(obj, entry):
    """True when the seed's object holds only its own function plus metadata."""
    coff = Coff(obj.read_bytes())
    defined = [s for s in coff.symbols.values()
               if s['section'] > 0 and s['type'] & 0x20 and s['storage'] == 2]
    if len(defined) != 1 or ('%08x' % entry) not in defined[0]['name']:
        return False
    for section in coff.sections:
        if not section['size'] or section['name'] in ('.drectve', '.debug$F', '.debug$S', '.debug$T'):
            continue
        if section['flags'] & 0xc0 or not section['flags'] & 0x20:
            return False
    return True


def references(text, entry, catalog_refs):
    """Bind every address-named symbol by a unique mangled prefix or C name."""
    refs = {}
    for name in sorted(set(NAMES.findall(text))):
        address = diff.address_from_name(name)
        if address is None:
            continue
        if name.startswith('FUN_'):
            refs['?%s@' % name] = address      # C++ function in some seed namespace
        else:
            refs['_' + name] = address
    for name, value in diff.SOURCE_REF.findall(text):
        refs[name] = int(value, 16)
    return refs


def gap_padding(original, gaps, end):
    """Frozen padding: a whole independent gap of at most 15 original NOPs."""
    gap = gaps.get(end)
    if gap and gap['length'] <= 15 and original(end, gap['length']) == b'\x90' * gap['length']:
        return '90' * gap['length'], gap
    return '', None


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--sweep', type=Path, default=REPOSITORY / 'build/sweep')
    parser.add_argument('--output', type=Path, required=True, help='new directory under private/ for frozen populations')
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    parser.add_argument('--limit', type=int)
    args = parser.parse_args()
    from compile_candidates import compile_population, aligned_unreferenced_entry
    from verify_manifest import Audit, TARGET_SHA256
    config = json.loads(args.config.read_bytes())
    audit = Audit(REPOSITORY, config['executable'])
    catalog_path = catalog_io.locate(REPOSITORY)
    catalog = catalog_io.load(catalog_path)
    accepted = accepted_sources(catalog)
    inventory = Inventory()
    output = args.output.resolve()
    if output.exists():
        sys.exit('output exists: %s' % output)
    rows = [json.loads(l) for l in (args.sweep / 'results.jsonl').read_text().splitlines()]
    latest = {}
    for row in rows:
        latest[row['entry']] = row
    exact = [r for r in latest.values() if r.get('byte_exact')][:args.limit]
    by_pass, skipped = {}, {}
    for row in exact:
        entry = int(row['entry'], 16)
        if entry in accepted or any(r['entry'] < entry + row['length'] and entry < r['entry'] + r['full_extent_bytes']
                                    for r in catalog['regions']):
            skipped[row['entry']] = 'overlaps accepted source'; continue
        obj = Path(row['object']) if row.get('object') else next(
            (args.sweep / d / ('%08x.obj' % entry) for d in ('0', '1', '2')
             if (args.sweep / d / ('%08x.obj' % entry)).exists()), None)
        if obj is None or not clean_object(obj, entry):
            skipped[row['entry']] = 'object emits data/extra code'; continue
        directory, bound = inventory.function(entry)
        # Use the frozen pass whose bound is the one the sweep scored.
        for candidate_pass in inventory.passes:
            other = inventory.rows(candidate_pass).get(entry)
            if other and other['contiguous'] and len(other['ranges']) == 1 and \
                    int(other['ranges'][0]['start'], 16) == entry and other['ranges'][0]['length'] == row['length']:
                directory, bound = candidate_pass, other
                break
        if not bound['name'].startswith('FUN_'):
            # Ghidra-named entries (operator_new, CRT helpers) belong to the
            # library ledger, not automated game-source promotion.
            skipped[row['entry']] = 'named library/analysis symbol ' + bound['name']; continue
        if not bound.get('entry_references') and not aligned_unreferenced_entry(audit, bound, None):
            # Same rule as the strict audit: an unreferenced entry needs
            # original-byte alignment evidence (virtual methods, inlined code).
            skipped[row['entry']] = 'no entry references or alignment evidence'; continue
        # Prefer the refine_gaps.py copy: identical bounds, alignment-split gaps.
        aligned = directory.with_name(directory.name + '-aligned')
        by_pass.setdefault(aligned if aligned.exists() else directory, []).append(
            (entry, bound, Path(row['source']).read_text() if row.get('source') else None))
    # A bogus inventory row inside the alignment padding leaves a partial gap
    # row at the body end; those entries go through a composite pass whose
    # gap rows hold the whole original NOP run (accept_sources.composite_pass).
    from accept_sources import composite_pass
    partial = []
    for directory in list(by_pass):
        gaps = {int(g['start'], 16): g for g in map(json.loads,
                (directory / 'unassigned-executable.jsonl').read_text().splitlines())}
        keep = []
        for entry, bound, override in by_pass[directory]:
            end = int(bound['ranges'][0]['end_inclusive'], 16) + 1
            run = 0
            while run < 15 and audit.original(end + run, 1) == b'\x90':
                run += 1
            gap = gaps.get(end)
            if run and (end + run) % 16 == 0 and (gap is None or gap['length'] < run):
                partial.append((entry, override))
            else:
                keep.append((entry, bound, override))
        by_pass[directory] = keep
    if partial:
        plan = dict(name='sweep-' + output.name, sources=[dict(entry='%08x' % e) for e, _ in partial])
        target = composite_pass(plan, inventory, {}, catalog, audit)
        if target is not None:
            rows = Inventory([target]).rows(target)
            by_pass[target] = [(e, rows[e], o) for e, o in partial if e in rows]
    by_pass = {d: e for d, e in by_pass.items() if e}
    output.mkdir(parents=True)
    catalog_refs = diff.canonical_references(catalog)
    summary = dict(skipped=skipped, populations=[])
    compiled = []
    next_population = max(int(p['id'].split('-')[1]) for p in catalog['populations']) + 1
    # One population compiles as one unit; seeds declaring the same C-linkage
    # global with different types (char vs undefined4) would share one
    # declaration there, so such seeds go to separate populations.
    units = []
    for directory, entries in sorted(by_pass.items()):
        buckets = []
        for entry, bound, override in entries:
            text = override or seed(entry, inventory, accepted)
            declared = dict((name, kind.strip()) for kind, name in
                            re.findall(r'^extern "C" ([^\n;(]*?)\b(_?\w+)(?:\[\])?;', text, re.M))
            for bucket in buckets:
                if all(bucket['types'].get(n, k) == k for n, k in declared.items()):
                    break
            else:
                bucket = dict(types={}, entries=[]); buckets.append(bucket)
            bucket['types'].update(declared); bucket['entries'].append((entry, bound, text))
        for index, bucket in enumerate(buckets):
            units.append((directory, directory.name + ('-%d' % index if index else ''), bucket['entries']))
    for directory, label, entries in units:
        inventory_path = directory / 'functions.jsonl'; gaps_path = directory / 'unassigned-executable.jsonl'
        gaps = {int(g['start'], 16): g for g in map(json.loads, gaps_path.read_text().splitlines())}
        sources = output / label / 'src'; sources.mkdir(parents=True)
        candidates = []
        for entry, bound, override in entries:
            # A permute_seeds.py result carries its adjusted source; otherwise
            # regenerate the plain seed.
            text = override
            path = sources / ('%08x.cpp' % entry); path.write_text(text)
            body = audit.original(entry, int(bound['ranges'][0]['end_inclusive'], 16) + 1 - entry)
            pad_hex, provenance = gap_padding(audit.original, gaps, entry + len(body))
            region = body + bytes.fromhex(pad_hex)
            candidates.append(dict(entry=entry, method='%08x' % entry, source=str(path),
                                   source_sha256=sha(path.read_bytes()), symbol_prefix='?FUN_%08x@' % entry,
                                   references=references(text, entry, catalog_refs),
                                   body_bytes=len(body), body_sha256=sha(body), region_bytes=len(region),
                                   region_sha256=sha(region), padding_hex=pad_hex, padding_provenance=provenance,
                                   original_inventory_row=bound))
        population = dict(executable_sha256=TARGET_SHA256,
                          inventory=str(inventory_path.relative_to(REPOSITORY)),
                          inventory_sha256=sha(inventory_path.read_bytes()),
                          gap_inventory_sha256=sha(gaps_path.read_bytes()),
                          source_model='ghidra-seed-sweep-v1', candidates=candidates)
        manifest_path = output / label / 'manifest.json'
        manifest_path.write_text(json.dumps(population, indent=1))
        compiled.append((label, population, manifest_path, gaps_path, len(candidates),
                         compile_population(manifest_path, output / label / 'compile', config)))
    # Install only after every population compiled and passed its strict audit.
    for label, population, manifest_path, gaps_path, count, receipt in compiled:
        accepted_doc = json.loads(Path(receipt['accepted_manifest']).read_bytes())
        if not accepted_doc['accepted']:
            summary['populations'].append(dict(pass_=label, candidates=count, accepted=0)); continue
        population_id = 'population-%02d' % next_population; next_population += 1
        catalog['populations'].append(dict(id=population_id, inventory_sha256=population['inventory_sha256'],
                                           gaps_sha256=population['gap_inventory_sha256'],
                                           historical_population_sha256=sha(manifest_path.read_bytes()),
                                           historical_acceptance_sha256=sha(Path(receipt['accepted_manifest']).read_bytes())))
        keys = ['entry', 'method', 'symbol', 'symbol_prefix', 'options', 'body_bytes', 'body_sha256', 'padding_bytes',
                'full_extent_bytes', 'full_extent_sha256', 'references', 'relocations', 'source_sha256']
        for row in accepted_doc['accepted']:
            destination = REPOSITORY / 'src/recovered' / ('%08x.cpp' % row['entry'])
            family = 'ghidra-seed-sweep' if MARKER.splitlines()[0] in Path(row['source']).read_text() else 'ghidra-seed-adjusted'
            if destination.exists():
                sys.exit('refusing to overwrite %s' % destination)
            destination.write_bytes(Path(row['source']).read_bytes())
            region = {k: row.get(k, {}) for k in keys}
            region.update(source=str(destination.relative_to(REPOSITORY)),
                          source_order=max(r['source_order'] for r in catalog['regions']) + 1,
                          population=population_id, padding_sha256=sha(bytes.fromhex(row['padding_hex'])),
                          boundary_confidence='Frozen independent analysis hypothesis; exact compiler extent, not certified function',
                          source_quality_family=family)
            catalog['regions'].append(region)
        for name in CONFIGS:
            path = REPOSITORY / 'private' / name
            if path.exists():
                document = json.loads(path.read_bytes())
                document['populations'][population_id] = dict(inventory=population['inventory'],
                                                               gaps=str(gaps_path.relative_to(REPOSITORY)))
                path.write_text(json.dumps(document, indent=2) + '\n')
        summary['populations'].append(dict(pass_=label, population=population_id, candidates=count,
                                           accepted=len(accepted_doc['accepted']),
                                           body_bytes=accepted_doc['body_bytes'],
                                           padding_bytes=accepted_doc['frozen_padding_bytes']))
    catalog_io.dump(catalog, catalog_path)
    (output / 'promotion.json').write_text(json.dumps(summary, indent=1))
    print(json.dumps({k: (v if k != 'skipped' else len(v)) for k, v in summary.items()}, indent=1))


if __name__ == '__main__':
    main()
