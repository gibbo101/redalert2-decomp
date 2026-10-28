"""Shared helpers for worker lanes: whole-population plans, frozen deliveries and variant scoring.

  plan OUT NAME ANCHOR [ENTRY=DRAFT[:SYMBOL]]... --copy-dir DIR
      Plan for the HEAD population that holds accepted entry ANCHOR: every current source is copied to
      DIR as a context draft (source order kept), then each ENTRY=DRAFT replaces that row's draft or
      inserts a new row in address order (SYMBOL is the new row's symbol prefix).
  freeze PLAN DELIVERY NAME [ENTRY=classes/<Class>/<file>.cpp]...
      Copy every draft of PLAN into DELIVERY/unit/ and write DELIVERY/NAME.json (LF endings). Each
      ENTRY=PATH sets that row's canonical source under src/recovered/ and its semantic name.
  scores --entry HEX [--length N] [--symbol S] [--config C] [--output-dir DIR] FILE...
      Run diff_candidate.py on each candidate and print one line per file, best first:
      score, status, shape, instruction counts and the first compiler error of a failed build.

Lanes generate their variant files themselves and score them with one `scores` call.
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

REPOSITORY = Path(__file__).resolve().parents[2]
DEFAULT_OPTIONS = [['/O2', '/Ob2', '/G5', '/Gy']]


def entry_text(value):
    return '%08x' % (value if isinstance(value, int) else int(value, 16))


def build_plan(regions, anchor, name, drafts, copy_dir, copy=shutil.copyfile):
    """regions: catalog rows; drafts: [(entry, draft, symbol)]. Returns (population, plan)."""
    anchor = int(anchor, 16) if isinstance(anchor, str) else anchor
    matches = [r for r in regions if r['entry'] == anchor]
    if not matches:
        raise SystemExit('no accepted region at %08x' % anchor)
    population = matches[0]['population']
    rows = sorted((r for r in regions if r['population'] == population), key=lambda r: r['source_order'])
    copy_dir = Path(copy_dir)
    sources = []
    for row in rows:
        draft = copy_dir / os.path.basename(row['source'])
        copy(row['source'], draft)
        item = dict(entry=entry_text(row['entry']), draft=draft.as_posix(), source=row['source'],
                    symbol_prefix=row['symbol_prefix'])
        if row.get('semantic_name'):
            item['semantic_name'] = row['semantic_name']
        sources.append(item)
    for entry, draft, symbol in drafts:
        entry = entry_text(entry)
        existing = [s for s in sources if s['entry'] == entry]
        if existing:
            existing[0]['draft'] = draft
            continue
        item = dict(entry=entry, draft=draft, source='src/recovered/x_%s.cpp' % entry, symbol_prefix=symbol)
        at = next((k for k, s in enumerate(sources) if int(s['entry'], 16) > int(entry, 16)), len(sources))
        sources.insert(at, item)
    return population, dict(name=name, separate_units=False, options=DEFAULT_OPTIONS, sources=sources)


def parse_drafts(arguments):
    drafts = []
    for argument in arguments:
        entry, rest = argument.split('=', 1)
        draft, _, symbol = rest.partition(':')
        drafts.append((entry, draft, symbol))
    return drafts


def freeze_plan(plan, delivery, name, sources, copy=shutil.copyfile):
    """sources: {entry hex without leading zeros or padded: path under src/recovered/}."""
    sources = {entry_text(k): v for k, v in sources.items()}
    delivery = Path(delivery)
    unit = delivery / 'unit'
    unit.mkdir(parents=True, exist_ok=True)
    plan = json.loads(json.dumps(plan))
    for row in plan['sources']:
        canonical = sources.get(entry_text(row['entry']))
        if canonical:
            row['source'] = 'src/recovered/' + canonical
            row['semantic_name'] = Path(canonical).stem
        target = unit / os.path.basename(row['source'])
        copy(row['draft'], target)
        row['draft'] = target.as_posix()
    plan['name'] = name
    path = delivery / (name + '.json')
    with open(path, 'w', newline='\n') as handle:
        handle.write(json.dumps(plan, indent=1) + '\n')
    return path


def summarize(diff, compiler_log=''):
    """One summary dict for a diff_candidate diff.json (None when it never ran)."""
    rows = [r for r in (diff or {}).get('results', []) if 'score' in r]
    if not rows:
        error = next((line.strip() for line in compiler_log.splitlines() if 'error C' in line), '')
        failed = (diff or {}).get('results', [{}])
        return dict(score=-1.0, status=(failed[0].get('status') if failed else None) or 'no-result', detail=error)
    best = max(rows, key=lambda r: (r['status'] == 'byte-exact', r['score']))
    return dict(score=best['score'], status=best['status'], detail='shape %.2f insns %d/%d%s' % (
        best['shape_score'], best['original_instructions'], best['candidate_instructions'],
        ' unresolved ' + ','.join(best['unresolved']) if best.get('unresolved') else ''), options=best['options'])


def run_scores(args):
    python = os.environ.get('RA2_PYTHON', sys.executable)
    lines = []
    for path in args.files:
        path = Path(path).resolve()
        output = Path(args.output_dir) / path.stem
        command = [python, '-B', str(REPOSITORY / 'tools/original_target/diff_candidate.py'), str(path),
                   '--entry', args.entry, '--output', str(output)]
        if args.length: command += ['--length', str(args.length)]
        if args.symbol: command += ['--symbol', args.symbol]
        if args.config: command += ['--config', args.config]
        result = subprocess.run(command, cwd=REPOSITORY, capture_output=True, text=True)
        diff_path = output / 'diff.json'
        diff = json.loads(diff_path.read_text()) if diff_path.exists() else None
        summary = summarize(diff, result.stdout + result.stderr)
        lines.append((summary['score'], path.name, summary['status'], summary['detail']))
    for score, name, status, detail in sorted(lines, key=lambda x: -x[0]):
        print('%7.2f  %-10s %s  %s' % (score, status, name, detail))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = parser.add_subparsers(dest='command', required=True)
    plan = commands.add_parser('plan')
    plan.add_argument('out'); plan.add_argument('name'); plan.add_argument('anchor')
    plan.add_argument('drafts', nargs='*')
    plan.add_argument('--copy-dir', required=True)
    freeze = commands.add_parser('freeze')
    freeze.add_argument('plan'); freeze.add_argument('delivery'); freeze.add_argument('name')
    freeze.add_argument('sources', nargs='*')
    scores = commands.add_parser('scores')
    scores.add_argument('files', nargs='+')
    scores.add_argument('--entry', required=True)
    scores.add_argument('--length', type=int)
    scores.add_argument('--symbol')
    scores.add_argument('--config')
    scores.add_argument('--output-dir', default=str(REPOSITORY / 'build/diff/lane'))
    args = parser.parse_args(argv)
    # Plans carry repository-relative paths; resolve arguments first, then work from the repository root.
    def relative(path):
        path = Path(path).resolve()
        return path.relative_to(REPOSITORY) if REPOSITORY in path.parents else path
    if args.command == 'plan':
        args.out, args.copy_dir = Path(args.out).resolve(), relative(args.copy_dir)
        args.drafts = ['%s=%s%s' % (e, relative(d).as_posix(), ':' + s if s else '')
                       for e, d, s in parse_drafts(args.drafts)]
    elif args.command == 'freeze':
        args.plan, args.delivery = Path(args.plan).resolve(), relative(args.delivery)
    os.chdir(REPOSITORY)
    if args.command == 'plan':
        sys.path.insert(0, str(REPOSITORY / 'tools/original_target'))
        import catalog_io
        catalog = catalog_io.load(catalog_io.locate(REPOSITORY), references=False)
        Path(args.copy_dir).mkdir(parents=True, exist_ok=True)
        population, result = build_plan(catalog['regions'], args.anchor, args.name,
                                        parse_drafts(args.drafts), args.copy_dir)
        Path(args.out).write_text(json.dumps(result, indent=1))
        print(population, len(result['sources']))
    elif args.command == 'freeze':
        sources = dict(argument.split('=', 1) for argument in args.sources)
        print(freeze_plan(json.loads(Path(args.plan).read_text()), args.delivery, args.name, sources))
    else:
        run_scores(args)


if __name__ == '__main__':
    main()
