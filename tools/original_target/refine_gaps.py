#!/usr/bin/env python3
"""Split leading alignment NOPs out of large unassigned gaps (original bytes only).

VC6 pads each function to a 16-byte boundary with 0x90. When Ghidra missed the
following function, the inventory records padding plus that undiscovered code
as one large gap, and strict acceptance refuses padding that is only part of a
gap. This tool writes a refined copy of an inventory pass whose gaps are split
wherever a gap begins with 1-15 NOPs that end exactly on a 16-byte boundary and
are followed by a non-NOP byte. Bounds come only from the original image and
the frozen gap list, never from candidate output.

Output: <pass>-aligned/ with an identical functions.jsonl and the refined
unassigned-executable.jsonl, plus refinement.json describing each split.
"""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))


def split_gap(gap, original):
    """Return [gap] or [padding, remainder] for one frozen gap row."""
    start = int(gap['start'], 16); length = gap['length']
    head = original(start, min(16, length))
    count = 0
    while count < len(head) and head[count] == 0x90:
        count += 1
    if not 1 <= count <= 15 or count == length or (start + count) % 16 or head[count] == 0x90:
        return [gap]
    padding = dict(start='%08x' % start, end_inclusive='%08x' % (start + count - 1), length=count,
                   classification='alignment_nop_padding_split_from_unassigned_gap')
    rest = dict(gap, start='%08x' % (start + count), length=length - count)
    return [padding, rest]


def refine(directory, original):
    rows = [json.loads(l) for l in (directory / 'unassigned-executable.jsonl').read_text().splitlines()]
    refined, splits = [], []
    for gap in rows:
        parts = split_gap(gap, original)
        refined.extend(parts)
        if len(parts) == 2:
            splits.append(dict(original=gap, padding=parts[0], remainder=parts[1]))
    return refined, splits


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('passes', nargs='*', type=Path, help='inventory pass directories (default: both frozen passes)')
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    args = parser.parse_args()
    from inventory import PASSES
    from verify_manifest import Audit
    audit = Audit(REPOSITORY, json.loads(args.config.read_bytes())['executable'])
    for directory in args.passes or PASSES:
        directory = Path(directory).resolve()
        target = directory.with_name(directory.name + '-aligned')
        if target.exists():
            print('exists, unchanged:', target); continue
        refined, splits = refine(directory, audit.original)
        target.mkdir()
        shutil.copyfile(directory / 'functions.jsonl', target / 'functions.jsonl')
        (target / 'unassigned-executable.jsonl').write_text(''.join(json.dumps(r, separators=(',', ':')) + '\n'
                                                                    for r in refined))
        source_gaps = (directory / 'unassigned-executable.jsonl').read_bytes()
        (target / 'refinement.json').write_text(json.dumps(dict(
            source_pass=str(directory.relative_to(REPOSITORY)),
            source_gaps_sha256=hashlib.sha256(source_gaps).hexdigest(),
            rule='leading 1-15 NOPs ending on a 16-byte boundary, followed by non-NOP, split from longer gaps',
            splits=len(splits), padding_bytes=sum(s['padding']['length'] for s in splits),
            examples=splits[:20]), indent=1))
        print(target, len(splits), 'splits')


if __name__ == '__main__':
    main()
