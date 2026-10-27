#!/usr/bin/env python3
"""Repair Ghidra seeds that fail to compile, guided by VC6's own diagnostics.

Ghidra's C is looser than C++: globals are declared by width (`undefined4
DAT_x`) but used as pointers, and integer/pointer values are assigned,
compared and returned without casts. CL reports each such line with the
exact types involved. This tool regenerates the seed, compiles it, and for
each reported line applies one conversion that keeps the 32-bit value and
code generation unchanged:

  C2100 illegal indirection       `*DAT_x` on the line: declare DAT_x as a pointer
                                  (`code *` when it is called through)
  C2440 '=' / 'initializing'      wrap the assigned value in a cast to the target type
  C2440 'return'                  wrap the returned value in a cast to the return type
  C2446 '==' / '!='               compare both operands as `uint`
  C2664 parameter N               cast argument N to the parameter type

Up to --rounds compile/repair rounds run; seeds that still fail keep their
last log. Compiled seeds are scored like sweep_seeds.py and written to a new
sweep directory (results.jsonl, queue.md, src/) whose rows carry the repaired
`source`, so promote_sweep.py can promote byte-exact ones through strict
acceptance. Repaired sources drop the seed-generated marker: regeneration
would lose the repairs.
"""
import argparse
import json
from pathlib import Path
import re
import subprocess
import sys
import time

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

import diff_candidate as diff
from inventory import Inventory
from seed_candidate import MARKER, accepted_sources, seed, split_args, matching_paren
from sweep_seeds import score_object, stop_wine, write_queue

ERROR = re.compile(r'\((\d+)\) : error (C\d+): (.*)')
GLOBAL = re.compile(r'^(extern "C" )(undefined4|int|uint) (_?DAT_[0-9a-f]{8});$', re.M)


def depth_scan(text, start, step, stops):
    """Index where an operand starting at `start` ends, scanning by `step`.

    Stops at depth 0 on any of `stops`, or at an unmatched bracket.
    """
    depth, i = 0, start
    while 0 <= i < len(text):
        c = text[i]
        if c in ')]' if step > 0 else c in '([':
            if depth == 0:
                return i
            depth -= 1
        elif c in '([' if step > 0 else c in ')]':
            depth += 1
        elif depth == 0 and any(text.startswith(s, i if step > 0 else i - len(s) + 1) for s in stops):
            return i
        i += step
    return i


def assignments(line):
    """Positions of plain `=` operators in a line, rightmost first."""
    found = [m.start() for m in re.finditer(r'(?<![=!<>+\-*/%&|^])=(?!=)', line)]
    return found[::-1]


def wrap_value(line, position, kind):
    """Cast the value assigned at `position` (an `=`) to `kind`."""
    start = position + 1
    while start < len(line) and line[start] == ' ':
        start += 1
    end = depth_scan(line, start, 1, [';', ','])
    value = line[start:end].rstrip()
    if not value or value.startswith('(%s)(' % kind):
        return None
    return line[:start] + '(%s)(%s)' % (kind, value) + line[start + len(value):]


def compare_as_uint(line, operator):
    """Rewrite every `a OP b` on the line as `(uint)(a) OP (uint)(b)`."""
    changed, cursor, out = False, 0, ''
    for match in re.finditer(r' %s ' % re.escape(operator), line):
        if match.start() < cursor:
            continue
        left_end = match.start()
        left_start = depth_scan(line, left_end - 1, -1, [',', '&&', '||', '= ', '? ', ': ']) + 1
        right_start = match.end()
        right_end = depth_scan(line, right_start, 1, [',', ';', '&&', '||', ' ?', ' :'])
        left = line[left_start:left_end].strip(); right = line[right_start:right_end].strip()
        if not left or not right or left.startswith('(uint)'):
            continue
        lead = line[left_start:left_end][:len(line[left_start:left_end]) - len(line[left_start:left_end].lstrip())]
        out += line[cursor:left_start] + lead + '(uint)(%s) %s (uint)(%s)' % (left, operator, right)
        cursor = right_start + len(line[right_start:right_end].rstrip())
        changed = True
    return out + line[cursor:] if changed else None


def cast_argument(line, function, index, kind):
    """Cast argument `index` (1-based) of the first call of `function` on the line."""
    match = re.search(r'\b%s\s*\(' % re.escape(function.split('::')[-1]), line)
    if not match:
        return None
    open_paren = match.end() - 1
    try:
        close = matching_paren(line, open_paren)
    except ValueError:
        return None
    args = split_args(line[open_paren + 1:close])
    if index > len(args) or args[index - 1].strip().startswith('(%s)' % kind):
        return None
    args[index - 1] = '(%s)(%s)' % (kind, args[index - 1].strip())
    return line[:open_paren + 1] + ', '.join(a.strip() for a in args) + line[close:]


def repair(text, log, attempts):
    """Apply one fix per reported line; return the new text or None."""
    lines = text.split('\n'); fixed_lines = set(); changed = False
    for number, code, message in ERROR.findall(log):
        index = int(number) - 1
        if index in fixed_lines or not 0 <= index < len(lines):
            continue
        line = lines[index]; new = None
        if code == 'C2100':
            for name in re.findall(r'\*\s*(_?DAT_[0-9a-f]{8})\b', line):
                kind = 'code *' if re.search(r'\(\*%s\)\s*\(' % name, line) else 'undefined4 *'
                updated = GLOBAL.sub(lambda m: '%s%s %s;' % (m.group(1), kind, m.group(3))
                                     if m.group(3) == name else m.group(0), '\n'.join(lines))
                if updated != '\n'.join(lines):
                    lines = updated.split('\n'); changed = True
            fixed_lines.add(index); continue
        conversion = re.match(r"'([^']*)' : cannot convert from '([^']*)' to '([^']*)'", message)
        if code == 'C2440' and conversion:
            operator, source, target = conversion.groups()
            target = target.strip()
            if source == 'void' or '(' in target and '*)' not in target:
                continue
            if operator in ('=', 'initializing'):
                key = (index, message); attempt = attempts.get(key, 0); attempts[key] = attempt + 1
                positions = assignments(line)
                if attempt < len(positions):
                    new = wrap_value(line, positions[attempt], target)
            elif operator == 'return':
                match = re.match(r'^(\s*return )(.*);\s*$', line)
                if match and not match.group(2).startswith('(%s)(' % target):
                    new = '%s(%s)(%s);' % (match.group(1), target, match.group(2))
        elif code == 'C2446':
            operator = re.match(r"'([^']*)'", message)
            if operator and operator.group(1) in ('==', '!='):
                new = compare_as_uint(line, operator.group(1))
        elif code == 'C2664':
            match = re.match(r"'([^']*)' : cannot convert parameter (\d+) from '[^']*' to '([^']*)'", message)
            if match:
                new = cast_argument(line, match.group(1), int(match.group(2)), match.group(3).strip())
        if new and new != line:
            lines[index] = new; fixed_lines.add(index); changed = True
    return '\n'.join(lines) if changed else None


def compile_all(config, directory, entries, options, timeout):
    """Compile entries' sources in concurrent Wine sessions; True per object."""
    from build import wine_parallel, win
    compiler = win(Path(config['compiler_directory']) / 'CL.EXE')
    units = []
    for entry in entries:
        obj = directory / ('%08x.obj' % entry); log = directory / ('%08x.log' % entry)
        for path in (obj, log):
            if path.exists(): path.unlink()
        args = diff.compiler_args(options) + ['/I' + win(REPOSITORY / 'src'), '/Fo' + win(obj),
                                           win(directory / ('%08x.cpp' % entry))]
        units.append(['"%s" %s >"%s" 2>&1' % (compiler, ' '.join('"' + a + '"' for a in args), win(log))])
    try:
        wine_parallel(config, directory, units, 'repair-%08x' % entries[0], timeout=timeout)
    except subprocess.TimeoutExpired:
        stop_wine(config)
    return {e: (directory / ('%08x.obj' % e)).exists() for e in entries}


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--sweep', type=Path, help='sweep whose compile-failed rows to repair')
    parser.add_argument('--entries', nargs='*', help='explicit hex entries instead')
    parser.add_argument('--output', type=Path, required=True, help='new sweep directory for repaired results')
    parser.add_argument('--rounds', type=int, default=5)
    parser.add_argument('--batch', type=int, default=400)
    parser.add_argument('--options', default='0,2', help='option variant indexes to score (see diff_candidate)')
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    args = parser.parse_args()
    import capstone
    from verify_manifest import Audit
    config = json.loads(args.config.read_bytes())
    audit = Audit(REPOSITORY, config['executable'])
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    catalog = json.loads((REPOSITORY / 'manifests/original_target.json').read_bytes())
    references = diff.canonical_references(catalog)
    inventory = Inventory(); accepted = accepted_sources(catalog)
    if args.entries:
        todo = [int(e, 16) for e in args.entries]
    else:
        latest = {}
        for row in map(json.loads, (args.sweep / 'results.jsonl').open()):
            latest[row['entry']] = row
        todo = [int(e, 16) for e, r in latest.items() if r.get('status') == 'compile-failed']
    covered = [(r['entry'], r['entry'] + r['full_extent_bytes']) for r in catalog['regions']]
    todo = [e for e in todo if e not in accepted and not any(s <= e < t for s, t in covered)]
    output = args.output.resolve(); output.mkdir(parents=True, exist_ok=True)
    sources = output / 'src'; sources.mkdir(exist_ok=True)
    results_path = output / 'results.jsonl'
    results = {}
    if results_path.exists():
        for row in map(json.loads, results_path.open()):
            results[row['entry']] = row
    todo = [e for e in todo if '%08x' % e not in results]
    variants = [diff.OPTIONS[int(i)] for i in args.options.split(',')]
    print('%d seeds to repair' % len(todo), flush=True)
    with results_path.open('a') as out:
        for first in range(0, len(todo), args.batch):
            started = time.monotonic(); batch = todo[first:first + args.batch]; rows = {}; texts = {}
            work = output / '0'; work.mkdir(exist_ok=True)
            for entry in batch:
                row = rows[entry] = dict(entry='%08x' % entry)
                try:
                    row['length'] = inventory.body_length(entry)
                    texts[entry] = seed(entry, inventory, accepted)
                except ValueError as error:
                    row.update(status='seed-failed', reason=str(error))
            pending = list(texts); attempts = {e: {} for e in pending}; rounds = {e: 0 for e in pending}
            for round_ in range(args.rounds + 1):
                if not pending:
                    break
                for entry in pending:
                    (work / ('%08x.cpp' % entry)).write_text(texts[entry])
                compiled = compile_all(config, work, pending, variants[0], timeout=1800)
                still = []
                for entry in pending:
                    if compiled[entry]:
                        continue
                    log = work / ('%08x.log' % entry)
                    fixed = repair(texts[entry], log.read_text(errors='replace') if log.exists() else '',
                                   attempts[entry]) if round_ < args.rounds else None
                    if fixed:
                        texts[entry] = fixed.replace(MARKER + '\n', '', 1); rounds[entry] += 1; still.append(entry)
                    else:
                        rows[entry].update(status='compile-failed', repair_rounds=rounds[entry])
                pending = still
            ready = [e for e in texts if 'status' not in rows[e]]
            for entry in ready:
                path = sources / ('%08x.cpp' % entry); path.write_text(texts[entry])
                rows[entry].update(source=str(path), repair_rounds=rounds[entry])
            for index, options in enumerate(variants):
                directory = output / str(index); directory.mkdir(exist_ok=True)
                if index:
                    for entry in ready:
                        (directory / ('%08x.cpp' % entry)).write_text(texts[entry])
                    compile_all(config, directory, ready, options, timeout=1800)
                for entry in ready:
                    obj = directory / ('%08x.obj' % entry)
                    if not obj.exists():
                        continue
                    try:
                        scored = score_object(audit, decoder, references, obj, entry, rows[entry]['length'],
                                              texts[entry])
                    except ValueError as error:
                        rows[entry].setdefault('status', 'score-refused'); rows[entry]['reason'] = str(error)
                        continue
                    best = rows[entry]
                    if (scored['byte_exact'], scored['score']) > (best.get('byte_exact', False), best.get('score', -1)):
                        best.pop('status', None); best.pop('reason', None)
                        best.update(scored, options=' '.join(options), object=str(obj))
            for entry, row in rows.items():
                if 'score' not in row:
                    row.setdefault('status', 'compile-failed')
                results[row['entry']] = row; out.write(json.dumps(row) + '\n')
            out.flush()
            print('batch %d-%d: %d compiled, %d byte-exact, %.0fs' % (
                first, first + len(batch), sum('score' in r for r in rows.values()),
                sum(1 for r in rows.values() if r.get('byte_exact')), time.monotonic() - started), flush=True)
    write_queue(output, {k: v for k, v in results.items() if 'length' in v})


if __name__ == '__main__':
    main()
