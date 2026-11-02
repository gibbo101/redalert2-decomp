#!/usr/bin/env python3
"""Matched bytes landed per worker per day, from the catalog's commit history.

Each commit that changed the canonical manifest adds (or removes) accepted body
bytes; status.history() already computes that per commit and caches it. This
tool attributes each commit's delta to the workers named in its subject
(codex1..codex4 for Windows, the Mac lane tag such as "Modem410" otherwise,
split equally when several are named) and prints a table by day.

    python3 tools/original_target/throughput.py                 # last 7 days, per worker
    python3 tools/original_target/throughput.py --since 2026-10-29 --lanes   # Mac lanes individually
    python3 tools/original_target/throughput.py --hours 6       # six-hour buckets
    python3 tools/original_target/throughput.py --markdown      # table for HANDOFF
"""
import argparse
from collections import Counter, defaultdict
from datetime import datetime, timedelta, timezone
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import status  # noqa: E402

WINDOWS = re.compile(r'\b(codex[1-6])\b')
LANE = re.compile(r'\(([A-Z][A-Za-z]+\d{2,3})\b')


def attribute(subject, lanes):
    workers = sorted(set(WINDOWS.findall(subject)))
    if workers:
        return workers
    if lanes:
        tags = sorted(set(LANE.findall(subject)))
        if tags:
            return tags
    return ['mac']


def buckets(rows, since, hours, lanes):
    table = defaultdict(Counter)
    previous = None
    for row in rows:
        if previous is not None and row['time'] >= since:
            delta = row['body'] - previous
            when = row['time'].astimezone(timezone.utc)
            if hours >= 24:
                key = when.strftime('%Y-%m-%d')
            else:
                key = when.strftime('%Y-%m-%d ') + '%02dZ' % (when.hour // hours * hours)
            who = attribute(row['subject'], lanes)
            for name in who:
                table[key][name] += delta // len(who)
        previous = row['body']
    return table


def columns(table, lanes, top=12):
    names = Counter()
    for row in table.values():
        for name, value in row.items():
            names[name] += abs(value)
    fixed = [n for n in ('codex1', 'codex2', 'codex3', 'codex4', 'codex5', 'codex6') if n in names]
    rest = sorted((n for n in names if n not in fixed), key=lambda n: -names[n])
    if lanes:
        return fixed + rest[:top]
    return fixed + [n for n in rest if n == 'mac']


def render(table, names, markdown):
    head = ['period'] + names + ['other', 'windows', 'total']
    lines = []
    for key in sorted(table):
        row = table[key]
        windows = sum(v for n, v in row.items() if n.startswith('codex'))
        shown = sum(row.get(n, 0) for n in names)
        cells = [key] + [format(row.get(n, 0), ',') for n in names] + [format(sum(row.values()) - shown, ','),
                                                                     format(windows, ','), format(sum(row.values()), ',')]
        lines.append(cells)
    if markdown:
        out = ['| ' + ' | '.join(head) + ' |', '|' + '---|' * len(head)]
        out += ['| ' + ' | '.join(cells) + ' |' for cells in lines]
        return '\n'.join(out)
    widths = [max(len(str(c)) for c in col) for col in zip(head, *lines)] if lines else [len(h) for h in head]
    fmt = '  '.join('%%%ds' % w if i else '%%-%ds' % w for i, w in enumerate(widths))
    return '\n'.join([fmt % tuple(head)] + [fmt % tuple(cells) for cells in lines])


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--since', help='first day to include (YYYY-MM-DD, UTC); default seven days ago')
    ap.add_argument('--hours', type=int, default=24, help='bucket size in hours (24 = per day)')
    ap.add_argument('--lanes', action='store_true', help='show Mac lanes individually instead of one mac column')
    ap.add_argument('--top', type=int, default=12, help='with --lanes, how many lanes to show individually')
    ap.add_argument('--markdown', action='store_true')
    args = ap.parse_args()
    since = (datetime.fromisoformat(args.since).replace(tzinfo=timezone.utc) if args.since
             else datetime.now(timezone.utc) - timedelta(days=7))
    rows = status.history()
    table = buckets(rows, since, args.hours, args.lanes)
    names = columns(table, args.lanes, args.top)
    print(render(table, names, args.markdown))


if __name__ == '__main__':
    main()
