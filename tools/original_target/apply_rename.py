#!/usr/bin/env python3
"""Apply a signature/name rename batch to accepted source in one pass.

    apply_rename.py SPEC [--config CONFIG] [--output DIR] [--dry-run] [--header-users]

A rename (a parameter retyped, a function, field or global renamed) changes
source text and manglings across many accepted populations without changing
a single original byte. Instead of one whole-population plan per affected
population through accept_sources.py, this applies the batch once and
re-verifies exactly the affected translation units:

  {"name": "screen26-ren2",
   "renames": {"OLD MANGLING": "NEW MANGLING", ...},   (or a path to such a JSON file)
   "mangling_rewrite": [{"pattern": "REGEX", "replace": "TEXT"}, ...],
   "rewrite": [{"pattern": "REGEX", "replace": "TEXT"}, ...],
   "headers": {"src/shared/techno.hpp": "build/class-work/W/shared/techno.hpp"},
   "header_base": "COMMIT the header copies were made from",
   "sources": {"src/recovered/.../X.cpp": "build/class-work/W/d/X.cpp"},
   "moves": {"src/recovered/.../Old_0076e730.cpp": "src/recovered/.../New_0076e730.cpp"}}

`mangling_rewrite` rules expand into further renames: every name in the
catalog and symbols.json they change (the expanded list is in the receipt).
Header copies are merged onto the tree with `git merge-file TREE BASE COPY`
(a conflict refuses). Then every tracked source and shared header gets the
`rewrite` rules (Python re, in order) and the plain-text renames; `sources`
replaces whole files after that, `moves` renames files. The catalog's names
(symbol, symbol_prefix, population reference tables, relocation receipts) and
manifests/symbols.json are renamed exactly, never by substring.

Affected populations are those holding a changed source or naming an old
mangling. Each is recompiled as whole translation units with its recorded
options (the build's own grouping), every region must reproduce its complete
original extent, and the result goes through the canonical V4 audit used by
build.py (bounds, padding, emitted-section coverage, reference and operand
checks). With --header-users, units that include a changed header are also
recompiled and must verify with their manifest rows unchanged.

Any miss, unbound reference or old name left anywhere refuses: every written
file is restored and the catalog is untouched. On success the catalog is
written once. Run ./build.command afterwards; it remains the final gate.
"""
import argparse
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time

REPOSITORY = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))

from canonical import CanonicalAudit, compile_group_key, separate_unit_populations, sha, validate_includes
from source_paths import source_path
import catalog_io

CATALOG = catalog_io.locate(REPOSITORY)
SYMBOLS = REPOSITORY / 'manifests/symbols.json'


def load_spec(path, catalog):
    spec = json.loads(Path(path).read_text())
    renames = spec.get('renames', {})
    if isinstance(renames, str):
        renames = json.loads((REPOSITORY / renames).read_text())
    rules = [(re.compile(r['pattern']), r['replace']) for r in spec.get('mangling_rewrite', [])]
    if rules:
        # Expand mangling rules over every name the catalog and symbols.json hold.
        names = {n for region in catalog['regions'] for n in
                 [region['symbol'], region['symbol_prefix'], *(region.get('references') or {}),
                  *(r['symbol'] for r in region.get('relocations') or [])]}
        names |= {s['mangled_prefix'] for s in json.loads(SYMBOLS.read_text())['symbols'] if s.get('mangled_prefix')}
        for name in sorted(names):
            new = name
            for pattern, replace in rules:
                new = pattern.sub(replace, new)
            if new != name and renames.setdefault(name, new) != new:
                raise SystemExit('conflicting renames for %s' % name)
    if any(old == new or not old or not new for old, new in renames.items()) or \
            len(set(renames.values())) != len(renames) or set(renames) & set(renames.values()):
        raise SystemExit('renames must map distinct old names to distinct, new names')
    spec['renames'] = renames
    spec['rules'] = [(re.compile(r['pattern'], re.M), r['replace']) for r in spec.get('rewrite', [])]
    return spec


def rewrite(text, spec):
    for pattern, replace in spec['rules']:
        text = pattern.sub(replace, text)
    renames = spec['renames']
    if renames:
        # One pass, longest name first: a replacement is never renamed again.
        names = re.compile('|'.join(map(re.escape, sorted(renames, key=len, reverse=True))))
        text = names.sub(lambda match: renames[match[0]], text)
    return text


def leftover(text, renames):
    """Old names still present once every new name is blanked (a new name may contain an old one)."""
    for new in sorted(renames.values(), key=len, reverse=True):
        text = text.replace(new, '\0')
    return sorted(old for old in renames if old in text)


def merged_header(path, copy, base):
    """The tree header with the worker's change (copy against base) merged in."""
    import tempfile
    original = subprocess.run(['git', 'show', '%s:%s' % (base, path)], cwd=REPOSITORY,
                              capture_output=True, check=True).stdout
    with tempfile.TemporaryDirectory() as scratch:
        base_file = Path(scratch) / 'base'; base_file.write_bytes(original)
        merged = subprocess.run(['git', 'merge-file', '-p', str(REPOSITORY / path), str(base_file),
                                 str(REPOSITORY / copy)], capture_output=True)
    if merged.returncode:
        raise SystemExit('header merge conflict: %s' % path)
    return merged.stdout


def planned_files(spec):
    """{path: new bytes} for every tracked source/header the batch changes, plus removed paths."""
    files = {}
    for path, copy in spec.get('headers', {}).items():
        if not spec.get('header_base'):
            raise SystemExit('header copies need header_base (the commit they were made from)')
        if not path.startswith('src/shared/'):
            raise SystemExit('header outside src/shared: %s' % path)
        files[path] = merged_header(path, copy, spec['header_base']) if (REPOSITORY / path).exists() else \
            (REPOSITORY / copy).read_bytes()
    tracked = sorted(p.relative_to(REPOSITORY).as_posix() for root in ('src/recovered', 'src/shared')
                     for p in (REPOSITORY / root).rglob('*') if p.suffix in ('.cpp', '.hpp', '.h'))
    for path in sorted(set(tracked) | set(files)):
        current = files[path] if path in files else (REPOSITORY / path).read_bytes()
        text = rewrite(current.decode('latin-1'), spec).encode('latin-1')
        if not (REPOSITORY / path).exists() or text != (REPOSITORY / path).read_bytes():
            files[path] = text
    for path, draft in spec.get('sources', {}).items():
        source_path(REPOSITORY, path)
        files[path] = (REPOSITORY / draft).read_bytes()
    removed = []
    for old, new in spec.get('moves', {}).items():
        source_path(REPOSITORY, old); source_path(REPOSITORY, new)
        files[new] = files.pop(old, None) or (REPOSITORY / old).read_bytes()
        removed.append(old)
    return files, removed


def rename_catalog(catalog, renames, files, moves):
    """Rename the catalog's names exactly; return the affected population ids."""
    affected = set()
    tables = {}
    for region in catalog['regions']:
        pid = region['population']
        if pid not in tables:
            old = region.get('references') or {}
            table = {}
            for name, value in old.items():
                new = renames.get(name, name)
                if table.setdefault(new, value) != value:
                    raise SystemExit('%s: %s would bind two addresses' % (pid, new))
            tables[pid] = table
            if any(name in renames for name in old):
                affected.add(pid)
        region['references'] = tables[pid]
        for key in ('symbol', 'symbol_prefix'):
            if region[key] in renames:
                region[key] = renames[region[key]]; affected.add(pid)
        for relocation in region.get('relocations') or []:
            if relocation['symbol'] in renames:     # the fresh compile rewrites the receipt;
                relocation['symbol'] = renames[relocation['symbol']]; affected.add(pid)   # known names stay current
        if region['source'] in moves:
            region['source'] = moves[region['source']]
            if region.get('semantic_name'):
                region['semantic_name'] = Path(region['source']).stem
        if region['source'] in files:
            affected.add(pid)
    return affected


def header_users(catalog, headers, populations):
    """Populations outside `populations` whose sources include a changed header (transitively)."""
    include = re.compile(rb'#\s*include\s+"([^"]+)"')
    graph = {p.relative_to(REPOSITORY / 'src').as_posix(): set(include.findall(p.read_bytes()))
             for p in (REPOSITORY / 'src/shared').rglob('*') if p.suffix in ('.h', '.hpp')}
    changed = {h[len('src/'):] for h in headers}
    reaches = {}
    def reach(name):
        if name not in reaches:
            reaches[name] = False
            reaches[name] = name in changed or any(reach(n.decode()) for n in graph.get(name, ()))
        return reaches[name]
    users = set()
    for region in catalog['regions']:
        if region['population'] in populations or region['population'] in users:
            continue
        if any(reach(n.decode()) for n in include.findall((REPOSITORY / region['source']).read_bytes())):
            users.add(region['population'])
    return users


def bind_changed(catalog, populations, files, config):
    """Bindings a changed source adds, exactly as accept_sources.py derives them
    (@ref comments, then known names the text mentions, RTTI under /GR); the
    population's existing (renamed) table keeps precedence."""
    import diff_candidate as diff
    from accept_sources import bind, rtti_references, with_headers
    known = diff.known_references(catalog)
    audit = None
    for pid in sorted(populations):
        rows = [r for r in catalog['regions'] if r['population'] == pid]
        table = rows[0]['references']
        for row in rows:
            if row['source'] not in files:
                continue
            text = files[row['source']].decode('latin-1')
            for name, value in diff.SOURCE_REF.findall(text):
                if table.setdefault(name, int(value, 16)) != int(value, 16):
                    raise SystemExit('%s: @ref %s differs from the accepted binding' % (row['source'], name))
            for name, value in bind(with_headers(text), known).items():
                table.setdefault(name, value)
            if '/GR' in row['options']:
                if audit is None:
                    from verify_manifest import Audit
                    audit = Audit(REPOSITORY, config['executable'])
                for name, value in rtti_references(with_headers(text), audit.original_type_descriptors()).items():
                    table.setdefault(name, value)


def write_files(files, removed, backup):
    """Write the batch; every overwritten or removed file is copied to `backup` first."""
    written = []
    for path in list(files) + removed:
        target = REPOSITORY / path
        if target.exists():
            copy = backup / path; copy.parent.mkdir(parents=True, exist_ok=True)
            copy.write_bytes(target.read_bytes())
    for path, data in files.items():
        target = REPOSITORY / path
        written.append((path, target.exists()))
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data)
    for path in removed:
        (REPOSITORY / path).unlink()
    return written


def restore(backup, written, removed):
    for path, existed in written:
        target = REPOSITORY / path
        if existed:
            target.write_bytes((backup / path).read_bytes())
        elif target.exists():
            target.unlink()
    for path in removed:
        (REPOSITORY / path).write_bytes((backup / path).read_bytes())


def verify(catalog, populations, config, output, phase):
    """Compile `populations` as whole canonical units and run the strict audit;
    record each region's fresh symbol and relocation receipt first."""
    from build import compile_sources
    from compile_candidates import compare_candidate
    from coff import Coff
    rows = [r for r in catalog['regions'] if r['population'] in populations]
    (output / 'compile').mkdir()
    compiled = compile_sources(config, dict(catalog, regions=rows), output / 'compile')
    phase('compile')
    audit = CanonicalAudit(REPOSITORY, catalog, config)
    phase('audit setup')
    misses = []
    for group, obj in compiled:
        coff = Coff(obj.read_bytes())
        for row in group:
            candidate = dict(row, method='%08x' % row['entry'], region_bytes=row['full_extent_bytes'])
            result = compare_candidate(audit, coff, candidate, obj, row['options'], 0)
            if result['status'] != 'extent-exact':
                misses.append(dict(entry='%08x' % row['entry'], source=row['source'], status=result['status'],
                                   reason=result.get('reason'), differing_bytes=result.get('differing_bytes')))
                continue
            row['symbol'] = result['symbol']
            row['relocations'] = result['relocations']
    if misses:
        return misses, None
    manifest = audit.verify_fresh(output / 'compile', compiled, complete=False)
    try:
        audit.verify_inputs_unchanged()
    except ValueError as error:
        raise SystemExit('refused: %s' % error)
    phase('strict audit')
    return [], manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('spec', type=Path)
    parser.add_argument('--config', type=Path, default=REPOSITORY / 'private/original-target.local.json')
    parser.add_argument('--output', type=Path, help='new ignored directory (default private/.../rename-<name>)')
    parser.add_argument('--dry-run', action='store_true', help='report what would change; write nothing')
    parser.add_argument('--header-users', action='store_true',
                        help='also recompile and verify unchanged units that include a changed header')
    args = parser.parse_args()
    started = time.monotonic(); marks = [started]; timings = {}
    def phase(name):
        now = time.monotonic(); timings[name] = round(now - marks[-1], 1); marks.append(now)
        print('phase %s: %.1fs' % (name, timings[name]), file=sys.stderr, flush=True)
    config = json.loads(args.config.read_bytes())
    catalog_blobs = {}
    catalog = catalog_io.load(CATALOG, blobs=catalog_blobs)
    catalog_digest = catalog_io.digest(CATALOG, catalog_blobs)
    spec = load_spec(args.spec, catalog)
    phase('load')
    files, removed = planned_files(spec)
    moves = spec.get('moves', {})
    sources = {p: d for p, d in files.items() if p.startswith('src/recovered/')}
    headers = sorted(p for p in files if p.startswith('src/shared/'))
    populations = rename_catalog(catalog, spec['renames'], sources, moves)
    unknown = [p for p in sources if p not in {r['source'] for r in catalog['regions']}]
    if unknown:
        raise SystemExit('changed files are not accepted sources: %s' % unknown[:5])
    users = header_users(catalog, headers, populations) if args.header_users else set()
    phase('plan')
    summary = dict(name=spec['name'], renames=spec['renames'], changed_sources=sorted(sources),
                   changed_headers=headers, moved=moves, affected_populations=sorted(populations),
                   affected_regions=sum(r['population'] in populations for r in catalog['regions']),
                   header_user_populations=len(users))
    if args.dry_run:
        print(json.dumps(summary, indent=1)); return
    output = (args.output or REPOSITORY / 'private/original-target-20261020' / ('rename-' + spec['name'])).resolve()
    if output.exists():
        raise SystemExit('output exists: %s' % output)
    if not any(output.is_relative_to(REPOSITORY / name) for name in ('private', 'build')):
        raise SystemExit('output must be under ignored private/ or build/')
    output.mkdir(parents=True)
    backup = output / 'backup'
    # symbols.json: exact JSON string tokens only, so the file keeps its layout.
    symbols = SYMBOLS.read_text()
    renamed = symbols
    for old, new in spec['renames'].items():
        renamed = renamed.replace(json.dumps(old), json.dumps(new))
    if renamed != symbols:
        json.loads(renamed)
        files['manifests/symbols.json'] = renamed.encode()
    written = write_files(files, removed, backup)
    try:
        from regenerate_seeds import sync_headers
        for region in catalog['regions']:
            if region['source'] in sources:
                region['source_sha256'] = sha(sources[region['source']])
                if region.get('source_quality_family') == 'ghidra-seed-sweep':
                    region['source_quality_family'] = 'hand-written'    # as accept_sources records it
        sync_headers(catalog)
        bind_changed(catalog, populations, sources, config)
        left = leftover(catalog_io.dumps(catalog), spec['renames'])
        if left:    # checked again on the final text; this refuses before compiling
            raise SystemExit('refused: old names left after the rename (tree restored): %s' % left[:10])
        phase('write and bind')
        before = {r['entry']: json.dumps(r, sort_keys=True) for r in catalog['regions'] if r['population'] in users}
        misses, manifest = verify(catalog, populations | users, config, output, phase)
        if misses:
            raise SystemExit('refused, %d regions no longer match (tree restored):\n%s' %
                             (len(misses), json.dumps(misses[:20], indent=1)))
        drifted = [r['source'] for r in catalog['regions']
                   if r['entry'] in before and json.dumps(r, sort_keys=True) != before[r['entry']]]
        if drifted:
            raise SystemExit('refused: header users outside the batch changed: %s' % drifted[:5])
        # Provenance as accept_sources.py records it: the frozen population and
        # its verified acceptance, here one per affected population.
        accepted = {}
        for row in manifest['accepted']:
            accepted.setdefault(row['population'], []).append(row)
        for population in catalog['populations']:
            pid = population['id']
            if pid not in populations:
                continue
            folder = output / pid; folder.mkdir()
            rows = [{k: v for k, v in r.items() if k != 'references'}
                    for r in catalog['regions'] if r['population'] == pid]
            table = next(r['references'] for r in catalog['regions'] if r['population'] == pid)
            (folder / 'population.json').write_text(json.dumps(dict(rename=spec['name'], references=table, regions=rows)))
            (folder / 'accepted.json').write_text(json.dumps(dict(accepted=[
                {k: v for k, v in r.items() if k != 'references'} for r in accepted[pid]])))
            population['historical_population_sha256'] = sha((folder / 'population.json').read_bytes())
            population['historical_acceptance_sha256'] = sha((folder / 'accepted.json').read_bytes())
        text = catalog_io.dumps(catalog)
        left = sorted(set(leftover(text, spec['renames'])) |
                      {old for path, data in files.items() for old in leftover(data.decode('latin-1'), spec['renames'])})
        if left:
            raise SystemExit('refused: old names left after the rename (tree restored): %s' % left[:10])
        for path, data in files.items():
            if (REPOSITORY / path).read_bytes() != data:
                raise SystemExit('refused: %s changed during verification (tree restored)' % path)
        if catalog_io.digest(CATALOG) != catalog_digest:
            raise SystemExit('refused: the catalog changed while the batch ran (tree restored)')
        catalog_io.dump(catalog, CATALOG)
    except BaseException:
        restore(backup, written, removed)
        raise
    phase('write catalog')
    # Keep the logs, receipts and verification report; the objects are several GB.
    for path in [*(output / 'compile').glob('compile-*/accepted.*'), output / 'compile/fresh-accepted.json']:
        path.unlink()
    shutil.rmtree(backup, ignore_errors=True)
    summary.update(regions_verified=manifest['matched_source_regions'], body_bytes=manifest['body_bytes'],
                   seconds=round(time.monotonic() - started, 1), timings=timings,
                   spec_sha256=sha(args.spec.read_bytes()), catalog_sha256=catalog_io.digest(CATALOG))
    (output / 'receipt.json').write_text(json.dumps(summary, indent=1) + '\n')
    print(json.dumps(dict({k: v for k, v in summary.items() if k not in ('renames', 'changed_sources', 'affected_populations')},
                          renames=len(spec['renames']), changed_sources=len(sources),
                          affected_populations=len(populations)), indent=1))


if __name__ == '__main__':
    main()
