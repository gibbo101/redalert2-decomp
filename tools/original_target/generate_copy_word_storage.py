#!/usr/bin/env python3
"""Render bounded review candidates; never modify accepted source or catalogs."""
import argparse
import hashlib
import json
from pathlib import Path
import time
from source_paths import source_path

HERE = Path(__file__).resolve().parent

def digest(data):
    return hashlib.sha256(data).hexdigest()

def require(value, message):
    if not value:
        raise ValueError(message)

def generate(repository, plan_path, template_path, executable, evidence_inputs, output, header_path=None):
    started = time.monotonic()
    repository = Path(repository).resolve()
    output = Path(output).resolve()
    require(not output.exists() and any(output.is_relative_to(repository / name) and
            output != repository / name for name in ('private', 'build')),
            'Output must be a new directory below private/ or build/')
    plan_bytes = Path(plan_path).read_bytes()
    plan = json.loads(plan_bytes)
    require(plan['schema'] == 'bounded-copy-word-storage-shared-v3', 'Wrong model schema')
    require(len(plan['regions']) == 17 and len({r['entry'] for r in plan['regions']}) == 17,
            'Changed bounded family membership')
    original = Path(executable).read_bytes()
    require(len(original) == plan['target']['size'] and digest(original) == plan['target']['sha256'],
            'Wrong supplied executable')
    evidence = {key: Path(value).read_bytes() for key, value in
                json.loads(Path(evidence_inputs).read_bytes()).items()}
    require(set(evidence) == set(plan['evidence_sha256']), 'Changed evidence input set')
    for key, expected in plan['evidence_sha256'].items():
        require(digest(evidence[key]) == expected, 'Frozen evidence hash drift: ' + key)
    facts = json.loads(evidence['facts'])
    peer = json.loads(evidence['peer_review'])
    require(peer['status'] == plan['peer_review_status'] and peer['regions'] == 17 and
            peer['readiness_sha256'] == digest(evidence['facts']), 'Missing independent original approval')
    require(facts['target'] == plan['target'], 'Wrong original facts target')
    original_rows = {r['entry']: r for r in facts['facts']}
    template_bytes = Path(template_path).read_bytes()
    require(digest(template_bytes) == plan['source_template_sha256'], 'Template drift')
    template = template_bytes.decode()
    header_path = Path(header_path) if header_path is not None else repository / plan['shared_header']['path']
    require(plan['shared_header']['path'] == 'src/shared/word_storage_layout.hpp', 'Unsupported shared header path')
    header_bytes = header_path.read_bytes()
    require(digest(header_bytes) == plan['shared_header']['sha256'], 'Shared declaration drift')
    catalog = json.loads((repository / 'manifests/original_target.json').read_bytes())
    require(catalog['target'] == plan['target'], 'Wrong canonical target')
    current = {r['entry']: r for r in catalog['regions']}
    require(len(current) == len(catalog['regions']), 'Duplicate canonical entries')
    observed = {}
    candidates = []
    for row in plan['regions']:
        entry = row['entry']
        fact = original_rows[entry]
        require(row['body_bytes'] == fact['body_bytes'] == 136 and
                row['region_bytes'] == fact['full_extent_bytes'] == 144 and
                row['body_sha256'] == fact['body_sha256'] and
                row['region_sha256'] == fact['full_extent_sha256'], 'Original extent binding differs')
        # The catalog owns accepted paths. The plan proposes paths only for entries
        # that have not been accepted yet; it never supplies an old flat fallback.
        path = current[entry]['source'] if entry in current else row['source']
        canonical = source_path(repository, path)
        require(Path(path).stem == row['semantic_name'] and len(Path(path).parts) > 3 and
                row['semantic_name'].endswith('_%08x' % entry), 'Unsupported descriptive source mapping')
        if entry in current:
            observed[path] = digest(canonical.read_bytes())
        owner = row['owner_class']
        require(owner.isascii() and owner.replace('_', '').isalnum(), 'Unsupported owner identifier')
        payload = template.replace('@ENTRY@', '%08x' % entry).replace('@OWNER_CLASS@', owner).encode()
        require(b'@ENTRY@' not in payload and digest(payload) == row['source_sha256'],
                'Rendered source differs from reviewed model')
        candidate = dict(row, source=path, original_inventory_row=fact['original_inventory_row'],
                         padding_hex=fact['padding_hex'], padding_provenance=fact['padding_provenance'])
        candidates.append((candidate, payload))
    # All original/model/path checks finish before creating any output.
    output.mkdir(parents=True, exist_ok=False)
    shared = output / plan['shared_header']['path']
    require(shared.parent == output / 'src/shared' and shared.suffix == '.hpp', 'Unsupported shared header path')
    shared.parent.mkdir(parents=True, exist_ok=True)
    shared.write_bytes(header_bytes)
    rendered = []
    for row, payload in candidates:
        destination = output / row['source']
        destination.parent.mkdir(parents=True, exist_ok=True)
        destination.write_bytes(payload)
        rendered.append(dict(row, candidate_source=str(destination)))
    require(all(digest(source_path(repository, path).read_bytes()) == expected
                for path, expected in observed.items()), 'Canonical source changed during generation')
    receipt = dict(status='review-candidates-only-not-accepted', sources=rendered,
                   canonical_sources_unchanged=True, observed_canonical_sha256=observed,
                   plan_sha256=digest(plan_bytes), template_sha256=digest(template_bytes),
                   generator_sha256=digest(Path(__file__).read_bytes()),
                   proposed_header=plan['shared_header'],
                   evidence_sha256=plan['evidence_sha256'], seconds=time.monotonic()-started)
    (output / 'candidate-manifest.json').write_text(json.dumps(receipt, indent=2)+'\n')
    return receipt

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repository', type=Path, required=True)
    parser.add_argument('--plan', type=Path, required=True)
    parser.add_argument('--template', type=Path, required=True)
    parser.add_argument('--exe', type=Path, required=True)
    parser.add_argument('--evidence-inputs', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--header', type=Path)
    args = parser.parse_args()
    result = generate(args.repository, args.plan, args.template, args.exe,
                      args.evidence_inputs, args.output, args.header)
    print(json.dumps(dict(sources=len(result['sources']), seconds=result['seconds'])))
