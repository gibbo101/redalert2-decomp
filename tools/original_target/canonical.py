"""Canonical tracked-source input validation and fresh-object V4 acceptance.

Historical manifests remain evidence only. Runtime inputs are the catalog, its
tracked sources, pinned private boundary inventories, and the supplied executable.
"""
import hashlib
import json
import re
from pathlib import Path

from coff import Coff
from compiler_output import classify
from source_paths import source_path
from verify_manifest import Audit, require, TARGET_BYTES, TARGET_SHA256


# Compiler option sets a canonical region may be accepted under. /Gr, /Ob1 and
# /GR are explicit-only (a plan names them; compile_candidates never tries
# them by default). /GR enables RTTI (the original was built with it); every
# RTTI structure it emits is bound to the original's copy by the strict audit.
RECORDED_OPTIONS = [['/O2', '/Ob2', '/G5', '/Gy'], ['/O2', '/Ob2', '/G6', '/Gy'],
                    ['/O1', '/Ob2', '/G5', '/Gy'], ['/O2', '/Ob2', '/G5', '/Gy', '/Gr'],
                    ['/O2', '/Ob1', '/G5', '/Gy'], ['/O2', '/Ob2', '/G5', '/Gy', '/GR']]
BASE_COMPILER_ARGUMENTS = ['/nologo', '/c', '/TP', '/Zp4', '/GX-', '/GR-', '/W3']


def compiler_arguments(options):
    """Base compiler arguments followed by an option set. An option set
    naming /GR replaces the base /GR- in place (never both on one line)."""
    options = list(options)
    if '/GR' in options:
        return ['/GR' if a == '/GR-' else a for a in BASE_COMPILER_ARGUMENTS] + [o for o in options if o != '/GR']
    return BASE_COMPILER_ARGUMENTS + options


def sha(data):
    return hashlib.sha256(data).hexdigest()


def validate_headers(repository, catalog):
    headers = catalog.get('headers', [])
    paths, blobs = set(), {}
    for header in headers:
        value = header['path']
        path = Path(value)
        require(not path.is_absolute() and path.as_posix() == value and '..' not in path.parts,
                'Noncanonical header path')
        require(path.parts[:2] == ('src', 'shared') and path.suffix in ('.h', '.hpp'),
                'Header outside canonical shared tree')
        resolved = (repository / path).resolve()
        require(resolved.is_relative_to((repository / 'src/shared').resolve()), 'Header escapes tree')
        require(value not in paths, 'Duplicate canonical header')
        data = resolved.read_bytes()
        require(sha(data) == header['sha256'], 'Header hash drift')
        paths.add(value)
        blobs[path.relative_to('src').as_posix()] = data
    actual = {p.relative_to(repository).as_posix() for p in (repository/'src/shared').rglob('*')
              if p.is_file() and p.suffix in ('.h', '.hpp')}
    require(paths == actual, 'Uncatalogued/missing shared header')
    return blobs


def validate_includes(data, headers):
    # Apply preprocessing character/line/comment phases before recognizing
    # directives, so comments or continuations cannot hide a dependency.
    text = data.decode()
    for old, new in [('??=', '#'), ('??/', chr(92)), ('??\'', '^'), ('??(', '['),
                     ('??)', ']'), ('??!', '|'), ('??<', '{'), ('??>', '}'), ('??-', '~')]:
        text = text.replace(old, new)
    text = re.sub(r'\\\r?\n', '', text)
    tokens = r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*'
    text = re.sub(tokens, lambda m: (' ' + '\n' * m[0].count('\n'))
                  if m[0].startswith(('/*', '//')) else m[0], text, flags=re.S)
    text = re.sub(r'^(\s*)%:', r'\1#', text, flags=re.M)
    includes = set()
    for line in text.splitlines():
        directive = re.match(r'^\s*#\s*(\w+)', line)
        if not directive: continue
        name = directive[1]
        require(name not in ('import', 'using') and
                not (name == 'pragma' and 'include_alias' in line), 'Untracked compiler dependency directive')
        if name.startswith('include'):
            match = re.fullmatch(r'\s*#\s*include\s+"([^"\n]+)"\s*', line)
            require(match is not None and match[1] in headers, 'Untracked/noncanonical include dependency')
            includes.add(match[1])
    return includes


def dependency_headers(audit, sources):
    catalog = audit.document('manifests/original_target.json')
    headers = validate_headers(audit.repository, catalog)
    pending = set()
    for source in sources:
        pending.update(validate_includes(audit.read(source['source'], source['source_sha256']), headers))
    seen = set()
    while pending:
        name = pending.pop()
        if name in seen: continue
        seen.add(name)
        pending.update(validate_includes(headers[name], headers) - seen)
    return [dict(path='src/' + name, sha256=sha(headers[name])) for name in sorted(seen)]


def compile_group_key(row, separate_populations):
    """Translation unit a canonical source compiles in.

    Sources of one population and option set normally form one unit (in
    source order). A population marked separate_units compiles every source
    alone (e.g. explicit template instantiations of single members).
    """
    key = (row['population'], tuple(row['options']))
    return key + (row['source'],) if row['population'] in separate_populations else key


def separate_unit_populations(catalog):
    return {p['id'] for p in catalog.get('populations', []) if p.get('separate_units')}


def validate_catalog(repository, catalog):
    require(catalog['schema'] == 'ra2-canonical-source-v1', 'Unsupported catalog')
    require(catalog['target'] == dict(size=TARGET_BYTES, sha256=TARGET_SHA256), 'Wrong catalog target')
    headers = validate_headers(repository, catalog)
    for data in headers.values(): validate_includes(data, headers)
    ids = [p['id'] for p in catalog['populations']]
    require(len(ids) == len(set(ids)), 'Duplicate populations')
    entries, paths, orders = set(), set(), set()
    cursor = 0
    for row in sorted(catalog['regions'], key=lambda r: r['entry']):
        va = row['entry']
        require(va >= cursor and row['body_bytes'] > 0 and 0 <= row['padding_bytes'] <= 15,
                'Overlapping/invalid canonical extent')
        require(row['full_extent_bytes'] == row['body_bytes'] + row['padding_bytes'], 'Extent size differs')
        require(row['entry'] not in entries and row['source'] not in paths and row['source_order'] not in orders,
                'Duplicate canonical entry/source/order')
        if row.get('semantic_name'):
            require(Path(row['source']).stem == row['semantic_name'] and
                    len(Path(row['source']).parts) > 3 and
                    row['semantic_name'].endswith('_%08x' % va),
                    'Understood operation requires descriptive filename and purpose directory')
        require(row['population'] in ids, 'Missing bound population')
        require(row['options'] in RECORDED_OPTIONS, 'Unsupported accepted options')
        data = source_path(repository, row['source']).read_bytes()
        require(sha(data) == row['source_sha256'], 'Source hash drift')
        validate_includes(data, headers)
        entries.add(va); paths.add(row['source']); orders.add(row['source_order'])
        cursor = va + row['full_extent_bytes']
    require(bool(entries), 'Empty canonical source catalog')
    require(paths == {p.relative_to(repository).as_posix() for p in (repository/'src/recovered').rglob('*.cpp')},
            'Uncatalogued/missing canonical sources')


class CanonicalAudit(Audit):
    """Supply V4 with canonical rows and private independently frozen bounds.

    The inherited verifier retains all decoding, section-coverage, reference,
    common-symbol, operand-boundary and full-extent checks. No candidate search,
    historical object, aggregate source, report, or ignored Python is executed.
    """
    def __init__(self, repository, catalog, config):
        super().__init__(repository, config['executable'])
        validate_catalog(repository, catalog)
        self.catalog = catalog
        self.bounds = {}
        self.groups = {}
        # Most populations share a few inventory passes: parse each verified
        # file content (by hash) once. The rows are only read afterwards.
        parsed = {}
        def rows(path, digest, key):
            if (digest, key) not in parsed:
                data = self.read(path, digest)
                items = [json.loads(line) for line in data.splitlines() if line.strip()]
                table = {int(r[key], 16): r for r in items}
                require(len(table) == len(items), 'Duplicate original boundary rows')
                parsed[digest, key] = table
            else:
                self.read(path, digest)
            return parsed[digest, key]
        for population in catalog['populations']:
            pid = population['id']
            inputs = config['populations'][pid]
            self.bounds[pid] = (rows(inputs['inventory'], population['inventory_sha256'], 'entry'),
                                rows(inputs['gaps'], population['gaps_sha256'], 'start'))

    def population(self, manifest):
        key = manifest['canonical_compile_group']
        rows = self.groups[key]
        pid = rows[0]['population']
        inventory, gaps = self.bounds[pid]
        candidates, cases = {}, {}
        for row in rows:
            body = self.original(row['entry'], row['body_bytes'])
            pad = self.original(row['entry'] + row['body_bytes'], row['padding_bytes']) if row['padding_bytes'] else b''
            require(sha(pad) == row['padding_sha256'], 'Frozen padding hash differs')
            candidate = dict(row, original_inventory_row=inventory[row['entry']],
                             region_bytes=row['full_extent_bytes'], region_sha256=row['full_extent_sha256'],
                             padding_hex=pad.hex(), padding_provenance=gaps.get(row['entry']+len(body)) if pad else row['padding_provenance'])
            candidates[row['method']] = candidate
            cases[(row['method'], row['variant'])] = dict(row, status='extent-exact')
        return candidates, inventory, gaps, cases, key

    def compiler_output(self, owner, candidates, case, coff, inventory, gaps):
        pid = next(iter(candidates.values()))['population']
        populations = self.catalog.get('populations', [])
        population = next((p for p in populations if p['id'] == pid), {})
        reference = population.get('compiler_output_policy')
        if reference is None: return []
        compiler = self.document('manifests/toolchain.json')['compiler']
        return classify(self, coff, reference, list(candidates.values()), case['options'], compiler,
                        population['inventory_sha256'], population['gaps_sha256'],
                        dependency_headers(self, list(candidates.values())), (inventory, gaps))

    def verify_fresh(self, destination, compiled_groups, complete=True):
        # Full-file equality can hide omitted source behind original scaffold.
        # Require the complete canonical plan before any object is accepted.
        # A partial check (apply_rename.py) still compiles whole canonical units.
        expected = {}
        separate = separate_unit_populations(self.catalog)
        for row in sorted(self.catalog['regions'], key=lambda r: r['source_order']):
            expected.setdefault(compile_group_key(row, separate), []).append(row)
        if complete:
            require([rows for rows, _ in compiled_groups] == list(expected.values()),
                    'Fresh compile groups differ from complete canonical source plan')
        else:
            require(compiled_groups and all(rows == expected.get(compile_group_key(rows[0], separate))
                                            for rows, _ in compiled_groups),
                    'Fresh compile groups are not whole canonical units')
        runtime = []
        for index, (rows, object_path) in enumerate(compiled_groups):
            data = object_path.read_bytes()
            object_hash = sha(data)
            coff = Coff(data)
            key = 'fresh-%03d' % index
            group_manifest = destination / (key + '.json')
            group_manifest.write_text(json.dumps(dict(canonical_compile_group=key)))
            group = []
            for canonical in rows:
                symbol, section, start, end = coff.function(canonical['symbol_prefix'])
                bound, gaps = self.bounds[canonical['population']]
                pad = self.original(canonical['entry']+canonical['body_bytes'], canonical['padding_bytes']) if canonical['padding_bytes'] else b''
                # Empty padding provenance has multiple historical representations;
                # absence is canonical here, consistently passed to candidate and row.
                provenance = gaps.get(canonical['entry']+canonical['body_bytes']) if pad else None
                row = dict(canonical, object=str(object_path), object_sha256=object_hash,
                           variant=0, original_bound=bound[canonical['entry']], padding_hex=pad.hex(),
                           padding_provenance=provenance, accepted_batch_manifest=str(group_manifest),
                           section_index=symbol['section'], section_start=start, section_end=end,
                           raw_section_sha256=sha(section['data'][start:end]))
                require(row['symbol'] == symbol['name'], 'Fresh symbol differs')
                group.append(row)
            self.groups[key] = group
            runtime.extend(group)
        manifest = dict(executable_sha256=TARGET_SHA256, accepted=runtime,
                        matched_source_regions=len(runtime), body_bytes=sum(r['body_bytes'] for r in runtime),
                        frozen_padding_bytes=sum(r['padding_bytes'] for r in runtime),
                        full_extent_bytes=sum(r['full_extent_bytes'] for r in runtime))
        path = destination/'fresh-accepted.json'
        # Unindented: each row carries its population's reference table, and
        # the indenting encoder took most of the verification time.
        path.write_text(json.dumps(manifest)+'\n')
        result = self.audit(path)
        (destination/'fresh-verification.json').write_text(json.dumps(result, indent=2)+'\n')
        return manifest
