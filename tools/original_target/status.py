#!/usr/bin/env python3
"""Generate the numeric part of docs/STATUS.md from the canonical manifest.

Coverage comes from manifests/original_target.json; the .text size from the
supplied executable's section header. Throughput history comes from every
commit that changed the manifest, so the matched-bytes-per-hour trend is
measured, not narrated. The block between the generated markers in
docs/STATUS.md is replaced; everything else in that file is hand-written.
"""
import argparse
from collections import Counter
from datetime import datetime
import json
from pathlib import Path
import subprocess
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
MANIFEST = 'manifests/original_target.json'
BEGIN, END = '<!-- generated:status -->', '<!-- /generated:status -->'


def coverage(catalog):
    regions = catalog['regions']
    return dict(regions=len(regions), body=sum(r['body_bytes'] for r in regions),
                padding=sum(r['padding_bytes'] for r in regions))


def history(repository=REPOSITORY):
    log = subprocess.run(['git', 'log', '--reverse', '--format=%h %cI %s', '--', MANIFEST],
                         cwd=repository, capture_output=True, text=True, check=True).stdout
    rows = []
    for line in log.splitlines():
        commit, stamp, subject = line.split(' ', 2)
        blob = subprocess.run(['git', 'show', '%s:%s' % (commit, MANIFEST)], cwd=repository,
                              capture_output=True, check=True).stdout
        rows.append(dict(commit=commit, time=datetime.fromisoformat(stamp), subject=subject,
                         **coverage(json.loads(blob))))
    return rows


def text_bytes(executable):
    import pefile
    pe = pefile.PE(executable, fast_load=True)
    return next(s.Misc_VirtualSize for s in pe.sections if s.Characteristics & 0x20)


def render(catalog, text, rows):
    now = coverage(catalog)
    scaffold = text - now['body'] - now['padding']
    populations = Counter(r['population'] for r in catalog['regions'])
    lines = [BEGIN, '',
             '| Measure | Value |', '| --- | ---: |',
             '| Accepted regions | {:,} |'.format(now['regions']),
             '| Matched C/C++ body bytes | {:,} ({:.2f}% of .text) |'.format(now['body'], 100.0 * now['body'] / text),
             '| Frozen padding bytes | {:,} |'.format(now['padding']),
             '| Original .text scaffold bytes | {:,} |'.format(scaffold),
             '| Logical .text bytes | {:,} |'.format(text),
             '| Compiler populations | {} |'.format(len(populations)), '']
    if rows:
        lines += ['Manifest history (body bytes added per commit, and per hour since the previous commit):', '',
                  '| Commit | Time | Regions | Body bytes | +Body | +Body/hour |',
                  '| --- | --- | ---: | ---: | ---: | ---: |']
        previous = None
        for row in rows:
            added = row['body'] - previous['body'] if previous else 0
            hours = (row['time'] - previous['time']).total_seconds() / 3600 if previous else 0
            rate = '{:,.0f}'.format(added / hours) if hours > 0 else ''
            lines.append('| `{}` | {} | {:,} | {:,} | {:+,} | {} |'.format(
                row['commit'], row['time'].strftime('%Y-%m-%d %H:%M %z'), row['regions'], row['body'],
                added, rate))
            previous = row
        lines.append('')
    lines.append(END)
    return '\n'.join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    parser.add_argument('--text-bytes', type=int, help='override instead of reading the executable')
    parser.add_argument('--write', action='store_true', help='replace the generated block in docs/STATUS.md')
    args = parser.parse_args()
    catalog = json.loads((REPOSITORY / MANIFEST).read_bytes())
    text = args.text_bytes or text_bytes(json.loads(args.config.read_bytes())['executable'])
    block = render(catalog, text, history())
    if not args.write:
        print(block); return
    path = REPOSITORY / 'docs/STATUS.md'
    current = path.read_text()
    if BEGIN not in current or END not in current:
        sys.exit('docs/STATUS.md has no generated markers')
    head, rest = current.split(BEGIN, 1)
    path.write_text(head + block + rest.split(END, 1)[1])
    print('updated', path)


if __name__ == '__main__':
    main()
