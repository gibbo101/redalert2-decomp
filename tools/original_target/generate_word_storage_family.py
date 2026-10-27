#!/usr/bin/env python3
"""Render reviewed readable C++ to NEW ignored candidates, never canonical src.

Only standard-library code is imported. Plan/template are byte-free tracked
proposals; private original/evidence paths are supplied explicitly at invocation.
No compiler, original-code execution or historical ignored Python is invoked.
"""
import argparse
import hashlib
import catalog_io
import json
from pathlib import Path
from source_paths import source_path

APPROVED_STATUS = 'independent-original-freeze-approved-for-bounded-source-modeling'


def digest(data):
    return hashlib.sha256(data).hexdigest()


def require(condition, message):
    if not condition:
        raise ValueError(message)


def render_family(repository, plan_path, template_path, executable, evidence_paths, output, shared_template_path=None):
    repository = Path(repository).resolve()
    output = Path(output).resolve()
    require(output.is_relative_to(repository / 'private') or output.is_relative_to(repository / 'build'),
            'Candidate output must be under ignored private/build, never canonical source')
    require(not output.exists(), 'Candidate output must be new; overwrites are forbidden')
    plan = json.loads(Path(plan_path).read_bytes())
    require(plan['schema'] == 'ra2-readable-word-storage-plan-v1', 'Wrong family plan schema')
    template_bytes = Path(template_path).read_bytes()
    require(digest(template_bytes) == plan['template_sha256'], 'Template hash drift')
    template = template_bytes.decode('utf-8')
    original = Path(executable).read_bytes()
    require(len(original) == plan['target']['size'] and digest(original) == plan['target']['sha256'],
            'Wrong original target')
    require(set(evidence_paths) == set(plan['evidence_sha256']), 'Missing/extra private evidence binding')
    evidence = {}
    for name, expected in plan['evidence_sha256'].items():
        data = Path(evidence_paths[name]).read_bytes()
        require(digest(data) == expected, 'Original evidence hash drift: ' + name)
        evidence[name] = data
    facts = [json.loads(line) for line in evidence['facts'].splitlines() if line.strip()]
    ready = {row['entry']: row for row in facts if not row['refusals']}
    held = sorted(row['entry'] for row in facts if row['refusals'])
    review = json.loads(evidence['peer_review'])
    require(review['status'] == APPROVED_STATUS, 'Original freeze was not independently approved')
    require(review['ready_regions'] == len(ready) == len(plan['regions']) and len(ready) > 0,
            'Original ready count differs')
    require(review['body_bytes'] == sum(row['body_bytes'] for row in plan['regions']) and
            review['padding_bytes'] == sum(row['padding_bytes'] for row in plan['regions']),
            'Original review byte accounting differs')
    require(held == sorted(plan['held_entries']) and held == [int(review['held_entry'], 16)],
            'Held entries differ; do not generate refused source')
    require(set(ready) == {row['entry'] for row in plan['regions']}, 'Planned source entries differ')
    require(len({row['entry'] for row in plan['regions']}) == len(plan['regions']), 'Duplicate source entries')
    catalog = catalog_io.load(catalog_io.locate(repository), references=False)
    require(catalog['target'] == plan['target'], 'Wrong canonical target')
    current = {row['entry']: row for row in catalog['regions']}
    sources = []
    shared_headers = {}
    shared_template_bytes = None
    observed = {}
    for row in plan['regions']:
        entry = row['entry']
        canonical = current[entry]
        canonical_path = source_path(repository, canonical['source'])
        if canonical_path.exists():
            observed[canonical['source']] = digest(canonical_path.read_bytes())
        fact = ready[entry]
        require(row['body_bytes'] == fact['body_bytes'] == 93 and row['padding_bytes'] == fact['padding_bytes'] == 3,
                'Unsupported family extent')
        require(row['body_sha256'] == fact['body_sha256'] and
                row['full_extent_sha256'] == fact['full_region_sha256'], 'Original region hash differs')
        key = '%08x' % entry
        expected_references = {'_allocate_storage_' + key: fact['allocation_target'],
                               '_base_dispatch_' + key: fact['base_table'],
                               '_derived_dispatch_' + key: fact['derived_table']}
        require(row['references'] == expected_references, 'Original field/call bindings differ')
        source = template.replace('@ENTRY@', key).replace('@TARGET_SHA256@', plan['target']['sha256']).encode('utf-8')
        require(digest(source) == row['source_sha256'], 'Rendered source differs from frozen readable family')
        # First prove the original reviewed model, then apply an explicitly pinned
        # shared declaration variant only where the catalog requests that variant.
        header = canonical.get('shared_declaration_header')
        if header is not None:
            require(header == 'src/shared/word_storage_layout.hpp', 'Unsupported shared declaration header')
            require('shared_template_sha256' in plan, 'Missing shared template pin')
            if shared_template_bytes is None:
                variant_path = (Path(shared_template_path) if shared_template_path is not None
                                else Path(template_path).with_name('word_storage_shared.cpp.in'))
                shared_template_bytes = variant_path.read_bytes()
                require(digest(shared_template_bytes) == plan['shared_template_sha256'], 'Shared template hash drift')
            pins = [h for h in catalog.get('headers', []) if h['path'] == header]
            require(len(pins) == 1, 'Shared header is not uniquely catalogued')
            header_path = repository / header
            require(header_path.resolve().is_relative_to((repository/'src/shared').resolve()), 'Shared header escapes tree')
            header_data = header_path.read_bytes()
            require(digest(header_data) == pins[0]['sha256'], 'Shared header hash drift')
            shared_headers[header] = header_data
            source = shared_template_bytes.decode().replace('@ENTRY@', key).replace(
                '@TARGET_SHA256@', plan['target']['sha256']).encode()
        sources.append((dict(row, canonical_source=canonical['source'],
                             shared_declaration_header=header), source))
    # Every original/model check precedes output creation. Canonical files are
    # neither consulted as templates nor opened for writing.
    output.mkdir(parents=True, exist_ok=False)
    for header, data in shared_headers.items():
        destination = output / header
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(data)
    candidates = []
    for row, source in sources:
        path = output / row['canonical_source']
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(source)
        candidates.append(dict(row, source=str(path), source_sha256=digest(source)))
    require(all(digest(source_path(repository, path).read_bytes()) == expected
                for path, expected in observed.items()), 'Canonical source changed during generation')
    manifest = dict(schema='ra2-readable-candidate-family-v1', target=plan['target'],
                    plan_sha256=digest(Path(plan_path).read_bytes()), template_sha256=digest(template_bytes),
                    evidence_sha256=plan['evidence_sha256'], candidates=candidates,
                    shared_template_sha256=digest(shared_template_bytes) if shared_template_bytes is not None else None,
                    proposed_headers=[dict(path=path,sha256=digest(data)) for path,data in shared_headers.items()],
                    observed_canonical_sha256=observed,
                    generation_policy='New ignored candidate outputs only; canonical manual edits are never overwritten')
    (output / 'candidate-manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repository', type=Path, required=True)
    parser.add_argument('--plan', type=Path, required=True)
    parser.add_argument('--template', type=Path, required=True)
    parser.add_argument('--exe', type=Path, required=True)
    parser.add_argument('--evidence-inputs', type=Path, required=True,
                        help='Private JSON map from evidence IDs to immutable original evidence paths')
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--shared-template', type=Path)
    args = parser.parse_args()
    result = render_family(args.repository, args.plan, args.template, args.exe,
                           json.loads(args.evidence_inputs.read_bytes()), args.output, args.shared_template)
    print(json.dumps(dict(candidates=len(result['candidates']), output=str(args.output))))


if __name__ == '__main__':
    main()
