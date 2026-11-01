#!/usr/bin/env python3
"""Draw the recovery treemap: one box per function, as wide as its code.

Groups are classes (RTTI names, small classes rolled into their first base),
recovered source directories and original source files (from the path strings
the executable carries); each group is as big as its code. Inside a group
functions are laid out done-first in rows, so a group reads as a progress bar:
accepted exact bytes, then recorded near misses (docs/OPEN_MISSES.md), then
everything still to recover.

Sizes come from the canonical manifest (accepted body bytes) and the frozen
Ghidra inventory (remaining function bodies, counted outside accepted
regions). Nothing here is acceptance evidence; it is a picture of the ledger.

    python3 tools/original_target/treemap.py            # build/treemap.png + .svg
    python3 tools/original_target/treemap.py --out docs/treemap.png --width 2400
"""
import argparse
from collections import Counter, defaultdict
from datetime import date
import json
import math
from pathlib import Path
import re
import subprocess
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import catalog_io  # noqa: E402
from inventory import Inventory  # noqa: E402

REPOSITORY = Path(__file__).resolve().parents[2]
TEXT_BYTES = 3769805  # .text VirtualSize of the target (docs/STATUS.md)

STATUS_ORDER = ['exact', 'near', 'draft', 'remaining']
COLOURS = dict(background='#14171c', panel='#1b1f26', header='#e8e8e8', text='#9aa0a8',
               exact='#4fbf5a', near='#3f7ee8', draft='#2ea3b5', remaining='#4a4f57',
               edge='#14171c')
LABELS = dict(exact='accepted exact', near='near miss (best score 96+)',
              draft='recorded miss under 96', remaining='still to recover')


# ----------------------------------------------------------------- data
def accepted_regions():
    catalog = catalog_io.load(catalog_io.locate(REPOSITORY), references=False)
    return catalog['regions']


def mangled_class(symbol):
    """Outermost scope of a VC6 decorated name, or None for templates/free functions."""
    if not symbol or not symbol.startswith('?'):
        return None
    head = symbol.split('@@', 1)[0]
    parts = head.lstrip('?').split('@')
    scopes = parts[1:] if not head.startswith('??') else parts[1:]
    if head.startswith('??'):
        scopes = head[3:].split('@')  # ??0Class / ??1Class / ??_GClass ...
        if head[2] == '_':
            scopes = head[4:].split('@')
    scopes = [s for s in scopes if s]
    if not scopes or any(s.startswith('?$') for s in scopes):
        return None
    return scopes[-1]


def source_group(path):
    parts = Path(path).parts
    try:
        i = parts.index('recovered')
    except ValueError:
        return None
    rest = parts[i + 1:]
    if len(rest) >= 3 and rest[0] == 'classes':
        return rest[1]
    if len(rest) >= 2:
        return rest[0]
    return None


def rtti_tables():
    data = json.loads((REPOSITORY / 'manifests/rtti_classes.json').read_text())['vtables']
    bases, slot_classes = {}, defaultdict(list)
    for t in data:
        name = t.get('class_name')
        if not name:
            continue
        if t.get('object_offset', 0) == 0:
            bases.setdefault(name, [b['name'] for b in t.get('bases', [])])
        for slot in t.get('slots', []):
            slot_classes[int(slot, 16)].append(name)
    # A slot implemented in a base appears in every derived vtable: credit the
    # least derived class that lists it.
    owner = {}
    for slot, names in slot_classes.items():
        owner[slot] = min(names, key=lambda n: (len(bases.get(n, [])), n))
    return bases, owner


def original_source_spans():
    files = json.loads((REPOSITORY / 'manifests/original_source_files.json').read_text())['files']
    spans = []
    for f in files:
        anchors = sorted(int(a, 16) for a in f['anchors'])
        if anchors:
            spans.append((anchors[0], anchors[-1], f['file']))
    return sorted(spans)


def open_misses():
    """address -> best score, scraped from the hand-written misses document."""
    text = (REPOSITORY / 'docs/OPEN_MISSES.md').read_text(errors='replace')
    scores = {}
    for m in re.finditer(r'0x([0-9A-Fa-f]{6,8})\b([^0x]{0,40}?)(\d{2}\.\d{1,2})\b', text):
        entry = int(m.group(1), 16)
        score = float(m.group(3))
        if score <= 100:
            scores[entry] = max(scores.get(entry, 0.0), score)
    return scores


def collect():
    regions = accepted_regions()
    inv = Inventory()
    bases, slot_owner = rtti_tables()
    spans = original_source_spans()
    misses = open_misses()

    accepted = {}
    intervals = []
    for r in regions:
        entry = r['entry']
        group = mangled_class(r.get('symbol')) or source_group(r.get('source', '')) or 'other recovered'
        accepted[entry] = dict(entry=entry, bytes=r['body_bytes'], status='exact', group=group,
                               name=r.get('semantic_name') or r.get('symbol', ''), weak=group == 'other recovered')
        intervals.append((entry, entry + r['body_bytes']))
    intervals.sort()
    starts = [a for a, _ in intervals]

    def unaccepted_bytes(lo, hi):
        import bisect
        total = hi - lo
        i = bisect.bisect_right(starts, lo) - 1
        i = max(i, 0)
        while i < len(intervals) and intervals[i][0] < hi:
            a, b = intervals[i]
            overlap = min(b, hi) - max(a, lo)
            if overlap > 0:
                total -= overlap
            i += 1
        return max(total, 0)

    def span_group(entry):
        for a, b, name in spans:
            if a <= entry <= b:
                return name
        return None

    rows = inv.all_functions()
    remaining = {}
    for entry, row in rows.items():
        if entry in accepted or not row.get('contiguous') or len(row['ranges']) != 1:
            continue
        span = row['ranges'][0]
        lo, hi = entry, int(span['end_inclusive'], 16) + 1
        size = unaccepted_bytes(lo, hi)
        if size <= 0:
            continue
        group = slot_owner.get(entry) or span_group(entry)
        if group is None:
            group = 'C runtime' if entry >= 0x781000 else 'unattributed 0x%02X....' % (entry >> 16)
        score = misses.get(entry)
        status = 'remaining' if score is None else ('near' if score >= 96 else 'draft')
        remaining[entry] = dict(entry=entry, bytes=size, status=status, group=group,
                                name=row.get('qualified_name', ''), score=score, weak=group.startswith('unattributed'))
    functions = sorted(list(accepted.values()) + list(remaining.values()), key=lambda f: f['entry'])
    adopt_neighbours(functions)
    return functions, bases


def adopt_neighbours(functions, reach=3072):
    """VC6 keeps an object file's code together: a weakly attributed function
    between two neighbours of one group belongs to that group; a lone strong
    neighbour within reach also lends its group."""
    strong = [i for i, f in enumerate(functions) if not f.get('weak')]
    import bisect
    for i, f in enumerate(functions):
        if not f.get('weak'):
            continue
        k = bisect.bisect_left(strong, i)
        before = functions[strong[k - 1]] if k > 0 else None
        after = functions[strong[k]] if k < len(strong) else None
        if before and after and before['group'] == after['group']:
            f['group'] = before['group']
            continue
        near = []
        if before:
            near.append((f['entry'] - before['entry'] - before['bytes'], before))
        if after:
            near.append((after['entry'] - f['entry'] - f['bytes'], after))
        near.sort(key=lambda t: t[0])
        if near and near[0][0] <= reach:
            f['group'] = near[0][1]['group']
        else:
            f['group'] = 'unattributed'


def roll_up(functions, bases, threshold):
    """Classes under the threshold join their first base, cumulatively from the
    leaves; other small groups join 'other units'. 'unattributed' stays its own box."""
    size = Counter()
    for f in functions:
        size[f['group']] += f['bytes']

    def depth(name):
        d, seen = 0, set()
        while name in bases and bases[name] and name not in seen:
            seen.add(name)
            name = bases[name][0]
            d += 1
        return d

    acc = Counter(size)
    parent = {}
    for name in sorted(size, key=depth, reverse=True):
        if name in bases and bases[name] and acc[name] < threshold:
            base = bases[name][0]
            parent[name] = base
            acc[base] += acc[name]
            size.setdefault(base, 0)

    def resolve(name):
        seen = set()
        while name in parent and name not in seen:
            seen.add(name)
            name = parent[name]
        return name

    mapping = {}
    for name in size:
        target = resolve(name)
        if target == 'unattributed':
            pass
        elif acc[target] < threshold:
            target = 'other classes' if target in bases else 'other units'
        mapping[name] = target
    pretty = {'unowned': 'free functions (src/recovered/unowned)', 'header_statics': 'header statics and template instances',
              'C runtime': 'C runtime (library, not source credit)'}
    for f in functions:
        system = pretty.get(mapping[f['group']], mapping[f['group']])
        if system in ('other classes', 'other units'):
            # the long tail of small units, in link order (VC6 keeps object files together)
            band = f['entry'] >> 19
            system = 'other units 0x%02X-0x%02X' % (band << 3, (band << 3) + 7)
        f['system'] = system
    return functions


# --------------------------------------------------------------- layout
def squarify(items, x, y, w, h):
    """Bruls/Huizing/van Wijk squarified treemap. items: [(weight, payload)] sorted desc."""
    out = []
    total = sum(v for v, _ in items)
    if total <= 0 or not items:
        return out
    scale = w * h / total
    items = [(v * scale, p) for v, p in items]

    def worst(row, side):
        s = sum(v for v, _ in row)
        if s <= 0:
            return float('inf')
        mx, mn = max(v for v, _ in row), min(v for v, _ in row)
        return max(side * side * mx / (s * s), s * s / (side * side * mn))

    def place(row, x, y, w, h):
        s = sum(v for v, _ in row)
        if w >= h:  # column on the left
            cw = s / h if h else 0
            cy = y
            for v, p in row:
                ch = v / cw if cw else 0
                out.append((x, cy, cw, ch, p))
                cy += ch
            return x + cw, y, w - cw, h
        rh = s / w if w else 0
        cx = x
        for v, p in row:
            cw = v / rh if rh else 0
            out.append((cx, y, cw, rh, p))
            cx += cw
        return x, y + rh, w, h - rh

    row = []
    while items:
        side = min(w, h)
        candidate = row + [items[0]]
        if not row or worst(candidate, side) <= worst(row, side):
            row = candidate
            items.pop(0)
        else:
            x, y, w, h = place(row, x, y, w, h)
            row = []
    if row:
        place(row, x, y, w, h)
    return out


def strip_rows(functions, x, y, w, h, min_row=5.0, max_row=28.0):
    """Done-first rows, each function as wide as its bytes; rows justified to the box."""
    total = sum(f['bytes'] for f in functions)
    if total <= 0 or w <= 1 or h <= 1:
        return []
    n = len(functions)
    k = max(1, int(round(math.sqrt(n * h / max(w, 1)) * 0.9)))
    k = max(1, min(k, int(h // min_row) or 1))
    row_h = h / k
    if row_h > max_row:
        k = max(1, int(h // max_row))
        row_h = h / k
    per_row = total / k
    out, row, acc, cy = [], [], 0.0, y
    for f in functions:
        row.append(f)
        acc += f['bytes']
        if acc >= per_row and len(out) + 1 < k * 4:
            out.append((row, acc))
            row, acc = [], 0.0
    if row:
        out.append((row, acc))
    # distribute heights by row byte share so areas stay proportional
    rects = []
    for row, acc in out:
        rh = h * acc / total
        cx = x
        for f in row:
            fw = w * f['bytes'] / acc
            rects.append((cx, cy, fw, rh, f))
            cx += fw
        cy += rh
    return rects


def layout(functions, width, height, margin, header, gap):
    systems = defaultdict(list)
    for f in functions:
        systems[f['system']].append(f)
    rank = {s: 0 for s in STATUS_ORDER}
    for i, s in enumerate(STATUS_ORDER):
        rank[s] = i
    weights = sorted(((sum(f['bytes'] for f in fs), name) for name, fs in systems.items()), reverse=True)
    boxes = squarify([(w, name) for w, name in weights], margin, margin, width - 2 * margin, height - 2 * margin)
    result = []
    for bx, by, bw, bh, name in boxes:
        fs = sorted(systems[name], key=lambda f: (rank[f['status']], -(f.get('score') or 0), f['entry']))
        inner = (bx + gap, by + gap + header, max(bw - 2 * gap, 1), max(bh - 2 * gap - header, 1))
        done = sum(f['bytes'] for f in fs if f['status'] == 'exact')
        total = sum(f['bytes'] for f in fs)
        result.append(dict(name=name, box=(bx, by, bw, bh), inner=inner, done=done, total=total,
                           rects=strip_rows(fs, *inner)))
    return result


# ------------------------------------------------------------- rendering
def summary(functions):
    c = Counter()
    b = Counter()
    for f in functions:
        c[f['status']] += 1
        b[f['status']] += f['bytes']
    return c, b


def title_lines(functions, commit):
    c, b = summary(functions)
    pct = 100.0 * b['exact'] / TEXT_BYTES
    return ['%.2f%% of .text matched exactly: %s of %s bytes in %s functions' % (
                pct, format(b['exact'], ','), format(TEXT_BYTES, ','), format(c['exact'], ',')),
            '%s near misses at 96+ (%s B) · %s recorded misses under 96 (%s B) · %s functions still to recover (%s B)' % (
                format(c['near'], ','), format(b['near'], ','), format(c['draft'], ','), format(b['draft'], ','),
                format(c['remaining'], ','), format(b['remaining'], ',')),
            'grouped by class, original source file or recovered directory, each as big as its code · one box per function, done first · %s, %s' % (
                commit, date.today().isoformat())]


def render_png(groups, functions, path, width, height, commit, top):
    from PIL import Image, ImageDraw, ImageFont
    img = Image.new('RGB', (width, height), COLOURS['background'])
    d = ImageDraw.Draw(img)

    def font(size, bold=False):
        for candidate in ('/System/Library/Fonts/Helvetica.ttc', '/System/Library/Fonts/Supplemental/Arial.ttf',
                          '/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf'):
            try:
                return ImageFont.truetype(candidate, size, index=1 if bold and candidate.endswith('.ttc') else 0)
            except OSError:
                continue
        return ImageFont.load_default()

    big, small, label = font(int(top * 0.30), True), font(int(top * 0.15)), font(int(top * 0.15), True)
    lines = title_lines(functions, commit)
    d.text((24, 16), lines[0], fill=COLOURS['header'], font=big)
    d.text((24, 16 + top * 0.36), lines[1], fill=COLOURS['text'], font=small)
    d.text((24, 16 + top * 0.54), lines[2], fill=COLOURS['text'], font=small)
    lx = 24
    ly = 16 + top * 0.74
    for status in STATUS_ORDER:
        d.rectangle([lx, ly, lx + top * 0.14, ly + top * 0.14], fill=COLOURS[status])
        d.text((lx + top * 0.2, ly - 2), LABELS[status], fill=COLOURS['text'], font=small)
        lx += d.textlength(LABELS[status], font=small) + top * 0.5

    for g in groups:
        bx, by, bw, bh = g['box']
        d.rectangle([bx, by, bx + bw, by + bh], fill=COLOURS['panel'], outline=COLOURS['background'])
        for x, y, w, h, f in g['rects']:
            d.rectangle([x, y, x + w, y + h], fill=COLOURS[f['status']], outline=COLOURS['edge'] if w > 2 and h > 2 else None)
        caption = '%s %d%%' % (g['name'], round(100.0 * g['done'] / g['total'])) if g['total'] else g['name']
        if bw > 40:
            while caption and d.textlength(caption, font=label) > bw - 8:
                caption = caption[:-2] + '…' if len(caption) > 3 else ''
            d.text((bx + 4, by + 2), caption, fill=COLOURS['header'], font=label)
    img.save(path)


def render_svg(groups, functions, path, width, height, commit, top):
    def esc(s):
        return s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;').replace('"', '&quot;')
    lines = title_lines(functions, commit)
    out = ['<svg xmlns="http://www.w3.org/2000/svg" width="%d" height="%d" viewBox="0 0 %d %d" '
           'font-family="Helvetica, Arial, sans-serif">' % (width, height, width, height),
           '<rect width="100%%" height="100%%" fill="%s"/>' % COLOURS['background'],
           '<text x="24" y="%d" font-size="%d" font-weight="bold" fill="%s">%s</text>' % (
               16 + top * 0.3, top * 0.3, COLOURS['header'], esc(lines[0])),
           '<text x="24" y="%d" font-size="%d" fill="%s">%s</text>' % (16 + top * 0.5, top * 0.15, COLOURS['text'], esc(lines[1])),
           '<text x="24" y="%d" font-size="%d" fill="%s">%s</text>' % (16 + top * 0.68, top * 0.15, COLOURS['text'], esc(lines[2]))]
    lx = 24
    ly = 16 + top * 0.74
    for status in STATUS_ORDER:
        out.append('<rect x="%d" y="%d" width="%d" height="%d" fill="%s"/>' % (lx, ly, top * 0.14, top * 0.14, COLOURS[status]))
        out.append('<text x="%d" y="%d" font-size="%d" fill="%s">%s</text>' % (
            lx + top * 0.2, ly + top * 0.13, top * 0.15, COLOURS['text'], esc(LABELS[status])))
        lx += len(LABELS[status]) * top * 0.085 + top * 0.5
    for g in groups:
        bx, by, bw, bh = g['box']
        out.append('<g><title>%s: %s of %s bytes exact</title>' % (esc(g['name']), format(g['done'], ','), format(g['total'], ',')))
        out.append('<rect x="%.1f" y="%.1f" width="%.1f" height="%.1f" fill="%s"/>' % (bx, by, bw, bh, COLOURS['panel']))
        for x, y, w, h, f in g['rects']:
            tip = '%08X %s %s B%s' % (f['entry'], f['name'], format(f['bytes'], ','),
                                      '' if f.get('score') is None else ' best %.2f' % f['score'])
            out.append('<rect x="%.1f" y="%.1f" width="%.1f" height="%.1f" fill="%s" stroke="%s" stroke-width="0.4">'
                       '<title>%s</title></rect>' % (x, y, w, h, COLOURS[f['status']], COLOURS['edge'], esc(tip)))
        if bw > 40:
            caption = '%s %d%%' % (g['name'], round(100.0 * g['done'] / g['total'])) if g['total'] else g['name']
            out.append('<clipPath id="c%d"><rect x="%.1f" y="%.1f" width="%.1f" height="%.1f"/></clipPath>' % (
                id(g), bx, by, bw, bh))
            out.append('<text clip-path="url(#c%d)" x="%.1f" y="%.1f" font-size="%d" font-weight="bold" fill="%s">%s</text>' % (
                id(g), bx + 4, by + top * 0.15, top * 0.15, COLOURS['header'], esc(caption)))
        out.append('</g>')
    out.append('</svg>')
    Path(path).write_text('\n'.join(out))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--out', default=str(REPOSITORY / 'build/treemap.png'), help='PNG path; an .svg is written beside it')
    ap.add_argument('--width', type=int, default=2200)
    ap.add_argument('--height', type=int, default=2400)
    ap.add_argument('--threshold', type=int, default=24000, help='bytes a group needs for its own box')
    ap.add_argument('--json', help='also write the per-function table here')
    args = ap.parse_args()

    functions, bases = collect()
    roll_up(functions, bases, args.threshold)
    commit = subprocess.run(['git', 'rev-parse', '--short', 'HEAD'], cwd=REPOSITORY, capture_output=True, text=True).stdout.strip()
    top = 96
    groups = layout(functions, args.width, args.height - top, 12, 22, 3)
    for g in groups:  # shift below the title block
        bx, by, bw, bh = g['box']
        g['box'] = (bx, by + top, bw, bh)
        g['rects'] = [(x, y + top, w, h, f) for x, y, w, h, f in g['rects']]
    bottom = max(y + h for g in groups for x, y, w, h, f in g['rects'])
    assert bottom <= args.height + 0.5, 'layout overflows the canvas: %.1f > %d' % (bottom, args.height)
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    render_svg(groups, functions, out.with_suffix('.svg'), args.width, args.height, commit, top)
    try:
        render_png(groups, functions, out, args.width, args.height, commit, top)
    except ImportError:
        print('Pillow is not installed: wrote the SVG only (use the system python3 for the PNG)')
    if args.json:
        Path(args.json).write_text(json.dumps([{k: v for k, v in f.items()} for f in functions], indent=0))
    c, b = summary(functions)
    print('\n'.join(title_lines(functions, commit)))
    print('%d groups; wrote %s and %s' % (len(groups), out, out.with_suffix('.svg')))
    for g in sorted(groups, key=lambda g: -g['total'])[:12]:
        print('  %-28s %9s B  %3d%% exact' % (g['name'][:28], format(g['total'], ','), round(100.0 * g['done'] / g['total'])))


if __name__ == '__main__':
    main()
