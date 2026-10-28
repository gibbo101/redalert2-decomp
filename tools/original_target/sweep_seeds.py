#!/usr/bin/env python3
"""Seed, compile and score many unrecovered functions; write a ranked queue.

Every unaccepted, contiguous inventory function gets a Ghidra seed
(seed_candidate.py), compiled in batches inside one CrossOver session per
option set, then scored against the original (diff_candidate.py scoring).
Results are resumable and land in an ignored output directory:

  results.jsonl  one row per entry: compiled/score/shape/byte-exact
  queue.md       byte-exact first, then near misses by score, then failures

Nothing is accepted here. Byte-exact seeds still need a population manifest
and compile_candidates.py strict acceptance, plus naming/typing on promotion.
"""
import argparse
import catalog_io
import json
from pathlib import Path
import sys
import time

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

import diff_candidate as diff
from inventory import Inventory
from seed_candidate import accepted_sources, seed


def candidates(inventory, accepted, regions, minimum, maximum):
    covered = sorted((r['entry'], r['entry'] + r['full_extent_bytes']) for r in regions)
    starts = [c[0] for c in covered]
    from bisect import bisect_right
    for entry, row in sorted(inventory.all_functions().items()):
        if entry in accepted or row.get('external') or row.get('thunk'):
            continue
        try:
            length = inventory.body_length(entry)
        except ValueError:
            continue
        index = bisect_right(starts, entry) - 1
        if index >= 0 and covered[index][1] > entry:
            continue
        if minimum <= length <= maximum:
            yield entry, length


def score_object(audit, decoder, references, obj, entry, length, source_text):
    from coff import Coff
    refs = dict(references)
    refs.update({k: int(v, 16) for k, v in diff.SOURCE_REF.findall(source_text)})
    coff = Coff(obj.read_bytes())
    symbol, section, start, end = diff.pick_symbol(coff, None, entry)
    relocs = [(o - start, s, k) for o, s, k in section['relocs'] if start <= o < end]
    data, unresolved = diff.resolve(section['data'][start:end], relocs, coff.symbols, entry, refs)
    body, _ = diff.split_padding(data, length)
    original = audit.original(entry, length)
    summary, _ = diff.score(diff.disassemble(decoder, original, entry),
                            diff.disassemble(decoder, body, entry, unresolved))
    return dict(symbol=symbol['name'], unresolved=sorted(set(unresolved.values())),
                byte_exact=not unresolved and body == original, **summary)


def stop_wine(config):
    """Stop every Wine process of this config's prefix (a hung compiler)."""
    import os
    import subprocess
    if config.get('wine_kind') == 'wine' and config.get('wineserver'):
        subprocess.run([config['wineserver'], '-k'], env=dict(os.environ, WINEPREFIX=config['wine_prefix']),
                       check=False, capture_output=True)
    else:
        subprocess.run(['pkill', '-f', 'CL.EXE'], check=False)


def compile_batch(config, batch, directory, options, timeout=1800):
    """Compile seeds in concurrent Wine sessions; returns entries killed as hung.

    The parallel runner's watchdog kills a compiler stuck for minutes on one
    seed; that seed is recorded as hung and the rest continue.
    """
    if config.get('wine_kind') == 'native':
        return compile_native_batch(config, batch, directory, options)
    from build import wine_parallel, win
    compiler = win(Path(config['compiler_directory']) / 'CL.EXE')
    units = []
    for entry in batch:
        obj = directory / ('%08x.obj' % entry); log = directory / ('%08x.log' % entry)
        for path in (obj, log):
            if path.exists(): path.unlink()
        args = diff.compiler_args(options) + ['/I' + win(REPOSITORY / 'src'), '/Fo' + win(obj),
                                           win(directory / ('%08x.cpp' % entry))]
        units.append(['"%s" %s >"%s" 2>&1' % (compiler, ' '.join('"' + a + '"' for a in args), win(log))])
    receipt = wine_parallel(config, directory, units, 'sweep-%08x' % batch[0], timeout=timeout, hang_seconds=180)
    hung = []
    for line in receipt.get('killed_hung_compilers', []):
        hung += [e for e in batch if ('%08x.cpp' % e) in line]
    return hung


def compile_native_batch(config, batch, directory, options, timeout=180):
    """Bound each native compiler process; never inspect or kill other jobs."""
    from concurrent.futures import ThreadPoolExecutor
    import os
    import subprocess
    from build import exclusive_lock
    compiler = str(Path(config['compiler_directory']) / 'CL.EXE')

    def compile_one(entry):
        source = directory / ('%08x.cpp' % entry)
        obj = source.with_suffix('.obj')
        log = source.with_suffix('.log')
        if obj.exists():
            obj.unlink()
        temporary = directory / ('tmp-%08x' % entry)
        temporary.mkdir(exist_ok=True)
        env = dict(os.environ, TMP=str(temporary), TEMP=str(temporary))
        for name in ('CL', '_CL_', 'LINK', 'INCLUDE', 'LIB', 'WINEPREFIX', 'CX_BOTTLE', 'CX_INITIALIZED'):
            env.pop(name, None)
        command = [compiler] + diff.compiler_args(options) + [
            '/I' + str(REPOSITORY / 'src'), '/Fo' + str(obj), str(source)]
        started = time.monotonic()
        timed_out = False
        with log.open('wb') as stream:
            try:
                result = subprocess.run(command, cwd=directory, env=env, stdin=subprocess.DEVNULL,
                                        stdout=stream, stderr=subprocess.STDOUT, timeout=timeout,
                                        creationflags=getattr(subprocess, 'BELOW_NORMAL_PRIORITY_CLASS', 0))
                code = result.returncode
            except subprocess.TimeoutExpired:
                # subprocess.run terminates and waits for this exact CL process.
                # Remove a possibly partial object; it cannot be a scoring input.
                timed_out, code = True, None
                if obj.exists():
                    obj.unlink()
        return dict(entry='%08x' % entry, command=command, returncode=code,
                    seconds=time.monotonic() - started, timed_out=timed_out)

    before = time.monotonic()
    with exclusive_lock(config['lock']):
        waited = time.monotonic() - before
        count = max(1, min(int(config.get('parallel_sessions', 2)), len(batch)))
        with ThreadPoolExecutor(count) as pool:
            receipts = list(pool.map(compile_one, batch))
    receipt = dict(backend='native', units=receipts, lock_wait_seconds=waited)
    (directory / ('sweep-%08x-command.json' % batch[0])).write_text(
        json.dumps(receipt, indent=2) + '\n', encoding='utf-8')
    return [int(row['entry'], 16) for row in receipts if row['timed_out']]


def size_summary(results):
    """Keep large-body compile progress visible; >=75 includes byte-exact rows."""
    buckets = [(0, 256, '<256 B'), (256, 1024, '256 B-1 KB'),
               (1024, 4096, '1-4 KB'), (4096, float('inf'), '>=4 KB')]
    summary = []
    for first, last, label in buckets:
        rows = [r for r in results.values() if first <= r['length'] < last]
        summary.append(dict(bucket=label, attempted=len(rows),
                            compiled=sum(r.get('compiled', 'score' in r or r.get('status') == 'score-refused')
                                         for r in rows),
                            exact=sum(bool(r.get('byte_exact')) for r in rows),
                            score_at_least_75=sum(r.get('score', -1) >= 75 for r in rows)))
    return summary


def write_queue(output, results):
    rows = sorted(results.values(), key=lambda r: (not r.get('byte_exact'), -r.get('score', -1), r['entry']))
    exact = [r for r in rows if r.get('byte_exact')]
    near = [r for r in rows if not r.get('byte_exact') and r.get('score', 0) >= 75]
    lines = ['# Seed sweep queue', '',
             '%d entries: %d compiled, %d byte-exact (%d body bytes), %d near misses (score >= 75).' % (
                 len(rows), sum(r['compiled'] for r in size_summary(results)), len(exact),
                 sum(r['length'] for r in exact), len(near)), '',
             '| body size | attempted | compiled | exact | score >=75 (including exact) |',
             '| --- | ---: | ---: | ---: | ---: |']
    summary = size_summary(results)
    for bucket in summary:
        lines.append('| {bucket} | {attempted} | {compiled} | {exact} | {score_at_least_75} |'.format(**bucket))
    lines += ['',
             '| entry | bytes | options | score | shape | status |', '| --- | ---: | --- | ---: | ---: | --- |']
    for r in rows:
        status = 'byte-exact' if r.get('byte_exact') else r.get('status', 'mismatch')
        lines.append('| %s | %d | %s | %s | %s | %s |' % (
            r['entry'], r['length'], r.get('options', ''), r.get('score', ''), r.get('shape_score', ''), status))
    with (output / 'queue.md').open('w', encoding='utf-8', newline='\n') as stream:
        stream.write('\n'.join(lines) + '\n')
    (output / 'summary.json').write_text(json.dumps(dict(size_buckets=summary), indent=2) + '\n', encoding='utf-8')


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--output', type=Path, default=REPOSITORY / 'build/sweep')
    parser.add_argument('--min-bytes', type=int, default=1)
    parser.add_argument('--max-bytes', type=int, default=4096)
    parser.add_argument('--limit', type=int, help='stop after this many new entries')
    parser.add_argument('--batch', type=int, default=150, help='compiles per CrossOver session')
    parser.add_argument('--options', default='0,2', help='option variant indexes to try (see diff_candidate)')
    parser.add_argument('--entries', nargs='*', help='explicit hex entries instead of the inventory')
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
    results_path = output / 'results.jsonl'
    results = {}
    if results_path.exists():
        for row in map(json.loads, results_path.open()):
            results[row['entry']] = row
    if args.entries:
        todo = []
        for item in args.entries:
            try:
                todo.append((int(item, 16), inventory.body_length(int(item, 16))))
            except ValueError:
                pass    # noncontiguous or entry-not-first bounds stay out of automated sweeps
    else:
        todo = list(candidates(inventory, accepted, catalog['regions'], args.min_bytes, args.max_bytes))
    todo = [(e, n) for e, n in todo if '%08x' % e not in results][:args.limit]
    variants = [diff.OPTIONS[int(i)] for i in args.options.split(',')]
    print('%d entries to sweep, %d already recorded' % (len(todo), len(results)))
    with results_path.open('a') as log:
        for first in range(0, len(todo), args.batch):
            started = time.monotonic(); batch = todo[first:first + args.batch]; rows = {}
            for entry, length in batch:
                row = dict(entry='%08x' % entry, length=length)
                try:
                    text = seed(entry, inventory, accepted)
                except ValueError as error:
                    row.update(status='seed-failed', reason=str(error)); rows[entry] = row; continue
                rows[entry] = row
                for index in range(len(variants)):
                    directory = output / str(index); directory.mkdir(exist_ok=True)
                    with open(directory / ('%08x.cpp' % entry), 'w', encoding='utf-8', newline='\n') as stream:
                        stream.write(text)
            compiled = [e for e in rows if 'status' not in rows[e]]
            for index, options in enumerate(variants):
                if compiled:
                    for entry in compile_batch(config, compiled, output / str(index), options):
                        rows[entry]['status'] = 'compile-timeout'
                for entry in compiled:
                    obj = output / str(index) / ('%08x.obj' % entry)
                    if not obj.exists():
                        continue
                    rows[entry]['compiled'] = True
                    try:
                        scored = score_object(audit, decoder, references, obj, entry, rows[entry]['length'],
                                              (output / str(index) / ('%08x.cpp' % entry)).read_text(encoding='utf-8'))
                    except ValueError as error:
                        rows[entry].setdefault('status', 'score-refused'); rows[entry]['reason'] = str(error)
                        continue
                    best = rows[entry]
                    if (scored['byte_exact'], scored['score']) > (best.get('byte_exact', False), best.get('score', -1)):
                        best.pop('status', None); best.pop('reason', None)
                        best.update(scored, options=' '.join(options), object=str(obj),
                                    source=str(output / str(index) / ('%08x.cpp' % entry)))
            for entry, row in rows.items():
                if 'score' not in row:
                    row.setdefault('status', 'compile-failed')
                results[row['entry']] = row; log.write(json.dumps(row) + '\n')
            log.flush()
            exact = sum(1 for r in rows.values() if r.get('byte_exact'))
            print('batch %d-%d: %d compiled, %d byte-exact, %.0fs' % (
                first, first + len(batch), sum('score' in r for r in rows.values()), exact,
                time.monotonic() - started))
    write_queue(output, results)
    print(output / 'queue.md')


if __name__ == '__main__':
    main()
