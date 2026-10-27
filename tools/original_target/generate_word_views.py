#!/usr/bin/env python3
"""Render the bounded accepted A3/A4 families to new review candidates only.

Canonical files, including manual semantic improvements, are never written.
No original-code execution, compiler or ignored authored script is invoked.
"""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import time
from source_paths import source_path

HERE = Path(__file__).resolve().parent
REPOSITORY = HERE.parents[1]
COUNTS = {'guarded_scaled_offset':331, 'equal_word_sequences':154,
          'find_word_index_guarded':151, 'find_word_index':153}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def candidate_destination(repository, output):
    repository = Path(repository).resolve()
    output = Path(output).resolve()
    if output.exists() or not any(output.is_relative_to(repository/name) and output != repository/name
                                  for name in ('private','build')):
        raise ValueError('Candidate output must be a new ignored private/build directory; canonical writes forbidden')
    return output


def renamed_symbol(symbol, function):
    if not re.fullmatch(r'[A-Za-z_][A-Za-z_0-9]*', function) or not symbol.startswith('?get@'):
        raise ValueError('Unsupported function binding/name')
    return '?' + function + symbol[len('?get'):]


def render_source(plan_row, template, target_hash):
    values = dict(ADDRESS='0x%08x'%plan_row['entry'], TARGET_HASH=target_hash,
                  OWNER=plan_row['owner'], FUNCTION_NAME=plan_row['semantic_name'],
                  SHIFT=str(plan_row.get('shift',0)))
    for key,value in values.items():
        template = template.replace('@'+key+'@',value)
    if re.search(r'@[A-Z_]+@',template):
        raise ValueError('Unexpanded source template')
    return template.encode()


def generate(repository, output):
    repository = Path(repository).resolve()
    output = candidate_destination(repository, output)
    started = time.monotonic()
    plan_path = HERE/'word_views_plan.json'
    plan = json.loads(plan_path.read_bytes())
    if plan['schema'] != 'bounded-accepted-word-views-v1' or Counter(r['variant'] for r in plan['regions']) != COUNTS:
        raise ValueError('Changed bounded family membership')
    if len({r['entry'] for r in plan['regions']}) != sum(COUNTS.values()):
        raise ValueError('Duplicate planned entry')
    catalog = json.loads((repository/'manifests/original_target.json').read_bytes())
    if catalog['target'] != plan['target']:
        raise ValueError('Wrong target catalog')
    current = {r['entry']:r for r in catalog['regions']}
    templates = {variant:(HERE/'templates'/(variant+'.cpp.in')).read_text() for variant in COUNTS}
    header = repository/'src/shared/word_sequence_views.hpp'
    header_bytes = header.read_bytes()
    sources = []
    observed = {}
    for frozen in plan['regions']:
        row = current[frozen['entry']]
        path = row['source']
        canonical = source_path(repository, path)
        if path != frozen['source'] or row['population'] != frozen['population'] or row['references'] or row['relocations']:
            raise ValueError('Current canonical family/bindings differ')
        observed[path] = sha(canonical.read_bytes())
        data = render_source(frozen,templates[frozen['variant']],plan['target']['sha256'])
        candidate = dict(row, source_sha256=sha(data), observed_canonical_sha256=observed[path],
                         previous_source_sha256=frozen['source_sha256'], semantic_name=frozen['semantic_name'],
                         symbol=renamed_symbol(frozen['original_symbol'],frozen['semantic_name']),
                         symbol_prefix=renamed_symbol(frozen['original_symbol_prefix'],frozen['semantic_name']),
                         source_quality_family=frozen['family'])
        sources.append((candidate,data))
    output.mkdir(parents=True,exist_ok=False)
    for row,data in sources:
        path=output/row['source'];path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
    destination=output/'src/shared/word_sequence_views.hpp';destination.parent.mkdir(parents=True,exist_ok=True);destination.write_bytes(header_bytes)
    if any(sha((repository/path).read_bytes()) != digest for path,digest in observed.items()) or header.read_bytes() != header_bytes:
        raise ValueError('Canonical inputs changed during generation')
    receipt=dict(status='review-candidates-only-not-accepted',sources=[row for row,_ in sources],
                 header=dict(path='src/shared/word_sequence_views.hpp',sha256=sha(header_bytes)),
                 canonical_sources_unchanged=True, plan_sha256=sha(plan_path.read_bytes()),
                 generator_sha256=sha(Path(__file__).read_bytes()),
                 template_sha256={name:sha(data.encode()) for name,data in templates.items()},
                 seconds=time.monotonic()-started)
    (output/'candidate-manifest.json').write_text(json.dumps(receipt,indent=2)+'\n')
    return receipt


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repository',type=Path,default=REPOSITORY)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();receipt=generate(args.repository,args.output)
    print(json.dumps(dict(sources=len(receipt['sources']),output=str(args.output),seconds=receipt['seconds'])))


if __name__=='__main__':main()
