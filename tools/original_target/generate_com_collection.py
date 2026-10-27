#!/usr/bin/env python3
"""Generate review candidates only. Never update canonical source or manifests."""
import argparse
import hashlib
import json
from pathlib import Path
import time
from source_paths import source_path

HERE = Path(__file__).resolve().parent
DEFAULT_REPOSITORY = HERE.parents[1]

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repository', type=Path, default=DEFAULT_REPOSITORY)
    parser.add_argument('--header', type=Path, default=None)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    repository = args.repository.resolve()
    output = args.output.resolve()
    allowed = [(repository / name).resolve() for name in ('private', 'build')]
    if not any(output.is_relative_to(root) and output != root for root in allowed) or output.exists():
        raise SystemExit('Output must be a new directory below ignored root private/ or build/')
    started = time.perf_counter()
    plan_path = HERE / 'com_collection_plan.json'
    plan = json.loads(plan_path.read_text())
    if len(plan['regions']) != 34 or len({r['entry'] for r in plan['regions']}) != 34:
        raise SystemExit('Incomplete bounded family plan')
    catalog = json.loads((repository / 'manifests/original_target.json').read_text())
    if catalog['target']['sha256'] != plan['target_sha256']:
        raise SystemExit('Wrong target catalog')
    current = {row['entry']:row for row in catalog['regions']}
    original_hashes = {row['entry']:row['source_sha256'] for row in plan['regions']}
    planned = []
    for frozen in plan['regions']:
        row = current[frozen['entry']]
        source_path(repository, row['source'])
        if (row['source'] != frozen['source'] or row['body_bytes'] != 127 or
            row['padding_bytes'] != 1 or row['population'] != 'population-26' or
            set(row['references'].values()) != {0x7afcd0, 0x79a5e8}):
            raise SystemExit('Current catalog differs from bounded COM family')
        if any(relocation['target'] not in (0x7afcd0, 0x79a5e8) or
               row['references'].get(relocation['symbol']) != relocation['target']
               for relocation in row['relocations']):
            raise SystemExit('Unexpected family relocation binding')
        planned.append(row)
    template_path = HERE / 'templates/serialize_com_collection.cpp.in'
    template = template_path.read_text()
    header_path = (args.header or repository / 'src/shared/com_collection.hpp').resolve()
    # Read-only snapshots show manual canonical work; they never seed destructive edits.
    observed = {}
    for row in planned:
        source = source_path(repository, row['source'])
        observed[row['source']] = digest(source)
    output.mkdir(parents=True, exist_ok=False)
    shared = output / 'src/shared/com_collection.hpp'
    shared.parent.mkdir(parents=True)
    shared.write_bytes(header_path.read_bytes())
    rows = []
    for row in planned:
        values = dict(TARGET_HASH=plan['target_sha256'], ENTRY='0x%08x'%row['entry'],
                      KEY='%x'%row['entry'], BODY_BYTES=str(row['body_bytes']),
                      PADDING_BYTES=str(row['padding_bytes']),
                      FUNCTION_NAME='SavePersistableCollection_%08x'%row['entry'])
        text = template
        for key, value in values.items():
            text = text.replace('@'+key+'@', value)
        if any('@'+key+'@' in text for key in values):
            raise SystemExit('Unexpanded template')
        source = output / row['source']
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text(text)
        rows.append(dict(row, previous_source_sha256=original_hashes[row['entry']],
                         observed_canonical_sha256=observed[row['source']],
                         source_sha256=digest(source), candidate_source=str(source),
                         semantic_name=values['FUNCTION_NAME'],
                         symbol='@'+values['FUNCTION_NAME']+'@8',
                         symbol_prefix='@'+values['FUNCTION_NAME']+'@8',
                         references={'_ra2_iid_ipersist_stream':0x7afcd0,
                                     '_ra2_ole_save_to_stream':0x79a5e8},
                         relocations=[dict(relocation, symbol=('_ra2_iid_ipersist_stream'
                             if relocation['target']==0x7afcd0 else '_ra2_ole_save_to_stream'))
                             for relocation in row['relocations']]))
    if any(digest(repository/p) != h for p,h in observed.items()):
        raise SystemExit('Canonical source changed concurrently during generation')
    receipt = dict(status='candidates-generated-not-compiled-not-accepted',
                   target_sha256=plan['target_sha256'], sources=rows,
                   proposed_header=dict(path='src/shared/com_collection.hpp',sha256=digest(shared)),
                   generator_sha256=digest(Path(__file__)),plan_sha256=digest(plan_path),
                   template_sha256=digest(template_path),header_template_sha256=digest(header_path),
                   canonical_sources_unchanged=True,seconds=time.perf_counter()-started)
    (output/'candidate-manifest.json').write_text(json.dumps(receipt,indent=2)+'\n')
    print(json.dumps(dict(output=str(output),sources=len(rows),header_sha256=digest(shared),
                         seconds=receipt['seconds'])))

if __name__ == '__main__':
    main()
