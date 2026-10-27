#!/usr/bin/env python3
"""Overlay fresh accepted source on a pinned prior byte/evidence partition.

No inventory regeneration or new game/library classification is performed.
All output, including original analysis labels, remains ignored research data.
"""
import argparse
from collections import Counter
import json
from pathlib import Path
import time

from canonical import sha
from verify_manifest import require, TARGET_BYTES, TARGET_SHA256

ROOT = Path(__file__).resolve().parents[2]
SOURCE_CATEGORIES = ('accepted_C_body', 'accepted_frozen_NOP_padding')


def overlay(prior, regions):
    require(all(a[1] <= b[0] for a, b in zip(regions, regions[1:])), 'Source extents overlap')
    require(prior and prior[0]['file_start'] == 0 and
            all(a['file_end_exclusive'] == b['file_start'] for a, b in zip(prior, prior[1:])),
            'Prior partition is not complete/contiguous')
    output = []; index = 0
    for old in prior:
        start = old['file_start']; end = old['file_end_exclusive']
        require(start < end and old['bytes'] == end-start, 'Invalid prior partition interval')
        cuts = {start, end}; covering = []
        while index < len(regions) and regions[index][1] <= start: index += 1
        cursor = index
        while cursor < len(regions) and regions[cursor][0] < end:
            a, b, category, source = regions[cursor]
            if b > start:
                cuts.update((max(start, a), min(end, b))); covering.append(regions[cursor])
            cursor += 1
        points = sorted(cuts)
        for a, b in zip(points, points[1:]):
            row = dict(old, file_start=a, file_end_exclusive=b, bytes=b-a)
            sources = [r for r in covering if r[0] <= a and b <= r[1]]
            require(len(sources) <= 1, 'Ambiguous source ownership')
            row['original_partition_category'] = old.get('original_partition_category', old['category'])
            row['prior_partition_category'] = old['category']
            if sources:
                _, _, row['category'], source = sources[0]
                row.update(source_region_entry=source['entry'], source=source['source'],
                           source_sha256=source['source_sha256'], object_sha256=source['object_sha256'],
                           source_boundary_confidence='Frozen independent analysis hypothesis; exact compiler extent, not certified function')
            else:
                require(old['category'] not in SOURCE_CATEGORIES, 'Prior accepted source disappeared')
            output.append(row)
    require(not regions or regions[0][0] >= 0 and regions[-1][1] <= prior[-1]['file_end_exclusive'],
            'Source outside prior file partition')
    return output


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--prior', type=Path, required=True)
    parser.add_argument('--prior-sha256', required=True)
    parser.add_argument('--build', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args(); started = time.monotonic(); output = args.output.resolve()
    require(not output.exists() and any(output.is_relative_to(ROOT/name) and output != ROOT/name
            for name in ('private','build')), 'Output must be a new ignored child directory')
    inputs = {}
    def read(path):
        data = path.read_bytes(); inputs[str(path)] = sha(data); return data
    prior_bytes = read(args.prior)
    require(sha(prior_bytes) == args.prior_sha256, 'Prior ledger hash drift')
    prior = [json.loads(line) for line in prior_bytes.splitlines()]
    receipt = json.loads(read(args.build/'build-receipt.json'))
    manifest = json.loads(read(args.build/'fresh-accepted.json'))
    catalog_bytes = read(ROOT/'manifests/original_target.json'); catalog = json.loads(catalog_bytes)
    require(receipt['whole_file_exact'] and receipt['output_sha256'] == TARGET_SHA256 and
            receipt['output_bytes'] == TARGET_BYTES and manifest['executable_sha256'] == TARGET_SHA256 and
            receipt['canonical_manifest_sha256'] == sha(catalog_bytes), 'Wrong/stale fresh build')
    require(sha(read(args.build/'reference.exe')) == TARGET_SHA256, 'Packaged output drift')
    current = {r['entry']: r for r in catalog['regions']}
    require(len(current) == len(catalog['regions']) == len(manifest['accepted']) == receipt['tracked_sources'],
            'Fresh source population differs')
    text = receipt['original_pe_structure']['sections'][0]
    require(text['name'] == '.text' and text['rva'] == text['raw_offset'] == 0x1000, 'Unsupported text/file mapping')
    regions = []
    for row in sorted(manifest['accepted'], key=lambda r: r['entry']):
        canonical = current[row['entry']]
        require(all(row[k] == v for k, v in canonical.items()), 'Fresh/canonical source row differs')
        a = row['entry']-0x400000; body_end = a+row['body_bytes']; end = a+row['full_extent_bytes']
        require(0x1000 <= a < body_end <= end <= 0x1000+text['virtual_size'], 'Source outside initialized text')
        require(end-body_end == row['padding_bytes'], 'Padding extent differs')
        regions.append((a, body_end, SOURCE_CATEGORIES[0], row))
        if body_end < end: regions.append((body_end, end, SOURCE_CATEGORIES[1], row))
    rows = overlay(prior, regions); categories = Counter(); libraries = Counter()
    for row in rows:
        categories[row['category']] += row['bytes']
        if row.get('exact_archive_section_identity'): libraries[row['category']] += row['bytes']
    require(rows[-1]['file_end_exclusive'] == TARGET_BYTES and sum(categories.values()) == TARGET_BYTES,
            'Final file accounting differs')
    require(categories[SOURCE_CATEGORIES[0]] == receipt['body_bytes'] == manifest['body_bytes'] and
            categories[SOURCE_CATEGORIES[1]] == receipt['padding_bytes'] == manifest['frozen_padding_bytes'],
            'Source/padding accounting differs')
    old_library_bytes = sum(r['bytes'] for r in prior if r.get('exact_archive_section_identity'))
    require(sum(libraries.values()) == old_library_bytes, 'Archive attribution changed')
    output.mkdir(parents=True)
    partition = output/'partition.jsonl'
    partition.write_text(''.join(json.dumps(r,separators=(',',':'))+'\n' for r in rows))
    summary = dict(status='source-overlay-only-original-evidence-preserved', input_sha256=inputs,
                   partition_sha256=sha(partition.read_bytes()), source_regions=len(current), file_bytes=TARGET_BYTES,
                   body_bytes=receipt['body_bytes'], padding_bytes=receipt['padding_bytes'],
                   text_scaffold_bytes=text['virtual_size']-receipt['body_bytes']-receipt['padding_bytes'],
                   file_category_bytes=dict(categories), exact_archive_identity_bytes=old_library_bytes,
                   library_identity_by_category=dict(libraries), library_completion_exception_bytes=0,
                   virtual_zero_tail_bytes=sum(r['verified_zero_tail_bytes'] for r in receipt['sections']),
                   source_function_count_certified=False, seconds=time.monotonic()-started,
                   tool_sha256=sha(Path(__file__).read_bytes()),
                   scope='Source/padding overlay only; prior original labels/conflicts/archive attribution retained. No new inventory, oracle, function count, library exception or code/data classification.')
    (output/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(json.dumps({k:summary[k] for k in ['source_regions','body_bytes','padding_bytes','text_scaffold_bytes','partition_sha256','seconds']}))


if __name__ == '__main__': main()
