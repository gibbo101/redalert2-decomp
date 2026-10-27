#!/usr/bin/env python3
"""Search small type variations of near-miss seeds for exact compiler output.

For each entry, start from its Ghidra seed and try single mutations that VC6's
code generation is sensitive to but that do not change which variables or
operations exist:

  * signedness of one declared local or parameter (int <-> uint,
    short <-> ushort, char <-> uchar; undefined4 behaves as uint),
  * the function's return type (byte vs 32-bit result),
  * operand order of one comparison (`a < b` -> `b > a`; VC6 keeps the
    source order in `cmp`),
  * the recorded option variants.

Each round compiles every mutation of the current best source in one Wine
session and keeps the best-scoring one (hill climbing). A byte-exact result
fixes the types to the ones consistent with the original machine code; it
still goes through promote_sweep.py's strict acceptance.

Results land in OUTPUT/results.jsonl in the sweep format plus a `source`
field, so `promote_sweep.py --sweep OUTPUT` promotes them unchanged.
"""
import argparse
import catalog_io
import json
from pathlib import Path
import re
import sys
import time

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

import diff_candidate as diff
from inventory import Inventory
from seed_candidate import MARKER, accepted_sources, seed
from sweep_seeds import score_object
from repair_seeds import depth_scan

FLIPS = {'int': 'uint', 'uint': 'int', 'undefined4': 'int', 'short': 'ushort', 'ushort': 'short',
         'undefined2': 'short', 'char': 'uchar', 'uchar': 'char', 'byte': 'char', 'undefined1': 'char'}
DECLARATION = re.compile(r'^(\s+)(int|uint|undefined4|short|ushort|undefined2|char|uchar|byte|undefined1)'
                         r'(\s+\**\s*)(\w+);$', re.M)
RETURNS = {'int': ['bool'], 'uint': ['bool'], 'undefined4': ['bool', 'char'], 'undefined': ['bool'],
           'char': ['bool'], 'byte': ['bool'], 'bool': ['int']}
GLOBAL_DECLARATION = re.compile(r'^(extern "C" )(int|uint|undefined4|short|ushort|undefined2|char|uchar|byte|'
                                r'undefined1) (_?DAT_[0-9a-f]{8});$', re.M)
NOTE = ('// Adjusted from the Ghidra seed by permute_seeds.py (signedness, comparison order, return width) to\n'
        '// match the original; edit freely, this file is no longer regenerated.')


MIRROR = {'==': '==', '!=': '!=', '<': '>', '>': '<', '<=': '>=', '>=': '<='}
COMPARISON = re.compile(r' (==|!=|<=|>=|<|>) ')


def swapped_comparisons(text):
    """Yield (description, text) with one comparison's operands exchanged."""
    body = text.find('\n{')
    for match in COMPARISON.finditer(text, max(body, 0)):
        line_start = text.rfind('\n', 0, match.start()) + 1
        line_end = text.find('\n', match.end())
        left_start = depth_scan(text[:match.start()], match.start() - 1, -1,
                                [',', '&&', '||', '= ', '? ', ': ', '\n', '!']) + 1
        right_end = depth_scan(text[:line_end], match.end(), 1, [',', ';', '&&', '||', ' ?', ' :'])
        if left_start < line_start or right_end > line_end:
            continue
        left = text[left_start:match.start()].strip(); right = text[match.end():right_end].strip()
        if not left or not right or 'return' in left or '=' in left.replace('==', ''):
            continue
        lead = len(text[left_start:match.start()]) - len(text[left_start:match.start()].lstrip())
        replacement = '%s %s %s' % (right, MIRROR[match.group(1)], left)
        yield ('swap %s at %d' % (match.group(1), text.count('\n', 0, match.start()) + 1),
               text[:left_start + lead] + replacement + text[match.end() + len(text[match.end():right_end].rstrip()):])


def mutations(text):
    """Yield (description, text) single signedness flips and comparison swaps."""
    yield from swapped_comparisons(text)
    for match in DECLARATION.finditer(text):
        indent, kind, space, name = match.groups()
        flipped = FLIPS[kind]
        yield ('%s %s->%s' % (name, kind, flipped),
               text[:match.start()] + indent + flipped + space + name + ';' + text[match.end():])
    # Globals: Ghidra declares them by width (undefined4 = unsigned).
    for match in GLOBAL_DECLARATION.finditer(text):
        prefix, kind, name = match.groups()
        yield ('%s %s->%s' % (name, kind, FLIPS[kind]),
               text[:match.start()] + prefix + FLIPS[kind] + ' ' + name + ';' + text[match.end():])
    # Return width: Ghidra types byte results (bool) as 32-bit values.
    definition = re.search(r'^(\w+)(\s+(?:__\w+\s+)?(?:\w+::)?FUN_[0-9a-f]{8}\()', text, re.M)
    if definition and definition.group(1) in RETURNS:
        name = re.search(r'FUN_[0-9a-f]{8}', definition.group(2)).group(0)
        for replacement in RETURNS[definition.group(1)]:
            changed = text[:definition.start()] + replacement + text[definition.start(1) + len(definition.group(1)):]
            # A member seed also declares the method in its owner struct.
            changed = changed.replace('{ %s %s(' % (definition.group(1), name), '{ %s %s(' % (replacement, name))
            yield ('return %s->%s' % (definition.group(1), replacement), changed)
    # Parameters: flip a type in the definition signature and its declaration.
    header = re.search(r'^(\w[^\n]*?)\b(FUN_[0-9a-f]{8})\(([^)\n]*)\)\s*\n\{', text, re.M)
    if header:
        for param in [p.strip() for p in header.group(3).split(',') if p.strip()]:
            parts = param.split()
            if len(parts) == 2 and parts[0] in FLIPS and not parts[1].startswith('*'):
                flipped = FLIPS[parts[0]] + ' ' + parts[1]
                yield ('%s %s->%s' % (parts[1], parts[0], FLIPS[parts[0]]),
                       re.sub(r'\b' + re.escape(param) + r'\b', flipped, text))


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--entries', nargs='+', required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--rounds', type=int, default=2)
    parser.add_argument('--options', default='0,1,2')
    parser.add_argument('--sources', type=Path, help='results.jsonl whose `source` rows start the search '
                        '(e.g. a repair_seeds.py sweep)')
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    args = parser.parse_args()
    import capstone
    from verify_manifest import Audit
    config = json.loads(args.config.read_bytes())
    audit = Audit(REPOSITORY, config['executable'])
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    catalog = catalog_io.load(catalog_io.locate(REPOSITORY), references=False)
    references = diff.canonical_references(catalog)
    inventory = Inventory(); accepted = accepted_sources(catalog)
    output = args.output.resolve(); output.mkdir(parents=True, exist_ok=True)
    done = set()
    if (output / 'results.jsonl').exists():
        done = {json.loads(l)['entry'] for l in (output / 'results.jsonl').read_text().splitlines()}
    variants = [diff.OPTIONS[int(i)] for i in args.options.split(',')]
    starting = {}
    if args.sources:
        for row in map(json.loads, args.sources.read_text().splitlines()):
            if row.get('source'):
                starting[int(row['entry'], 16)] = Path(row['source']).read_text()
    state = {}
    for item in args.entries:
        entry = int(item, 16)
        if '%08x' % entry in done or entry in accepted:
            continue
        try:
            state[entry] = dict(text=starting.get(entry) or seed(entry, inventory, accepted), length=inventory.body_length(entry),
                                best=None, history=[])
        except ValueError:
            continue
    started = time.monotonic()
    from build import wine_parallel, win
    compiler = win(Path(config['compiler_directory']) / 'CL.EXE')
    for round_index in range(args.rounds + 1):
        trials = []   # (entry, name, description, text, options)
        for entry, s in state.items():
            if s['best'] and s['best']['byte_exact']:
                continue
            if round_index == 0:
                options = [('seed', s['text'])]; option_sets = variants
            else:
                if not s['best']:
                    continue
                options = list(mutations(s['best']['text']))
                option_sets = [s['best']['options'].split()]
            for k, (description, text) in enumerate(options):
                for v, option in enumerate(option_sets):
                    trials.append((entry, '%08x_%d_%d' % (entry, k, v), description, text, option))
        if not trials:
            break
        directory = output / ('round%d' % round_index); directory.mkdir(parents=True, exist_ok=True)
        units = []
        for entry, name, description, text, option in trials:
            (directory / (name + '.cpp')).write_text(text)
            obj = directory / (name + '.obj')
            if obj.exists(): obj.unlink()
            units.append(['"%s" %s >"%s" 2>&1' % (compiler, ' '.join('"' + x + '"' for x in diff.compiler_args(option) + [
                '/I' + win(REPOSITORY / 'src'), '/Fo' + win(obj), win(directory / (name + '.cpp'))]),
                win(directory / (name + '.log')))])
        wine_parallel(config, directory, units, 'permute', timeout=3600)
        for entry, name, description, text, option in trials:
            obj = directory / (name + '.obj'); s = state[entry]
            if not obj.exists():
                continue
            try:
                scored = score_object(audit, decoder, references, obj, entry, s['length'], text)
            except ValueError:
                continue
            candidate = dict(scored, text=text, options=' '.join(option), mutation=description, object=str(obj))
            best = s['best']
            if best is None or (candidate['byte_exact'], candidate['score']) > (best['byte_exact'], best['score']):
                s['best'] = candidate
        for s in state.values():
            if s['best']:
                s['history'].append((s['best']['mutation'], s['best']['score']))
        print('round %d: %d trials, %d exact, %.0fs' % (round_index, len(trials),
              sum(1 for s in state.values() if s['best'] and s['best']['byte_exact']), time.monotonic() - started),
              flush=True)
    sources = output / 'sources'; sources.mkdir(exist_ok=True)
    with (output / 'results.jsonl').open('a') as log:
        for entry, s in state.items():
            best = s['best']
            row = dict(entry='%08x' % entry, length=s['length'])
            if best:
                text = best['text']
                if best['mutation'] != 'seed':
                    text = text.replace(MARKER, NOTE)
                path = sources / ('%08x.cpp' % entry); path.write_text(text)
                row.update({k: v for k, v in best.items() if k not in ('text',)}, source=str(path),
                           history=s['history'])
            else:
                row['status'] = 'compile-failed'
            log.write(json.dumps(row) + '\n')
    print(output / 'results.jsonl')


if __name__ == '__main__':
    main()
