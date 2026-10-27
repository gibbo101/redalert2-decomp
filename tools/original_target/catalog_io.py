"""Read and write the canonical catalog (manifests/original_target/).

Every region carries the reference bindings (mangled name -> address) used to
verify its relocations. Regions of one population share nearly all of them,
and the verifier merges them per compile group anyway, so the catalog stores
one table per population (`population_references`) instead of a copy per
region (which made the file over a gigabyte). On load each region gets its
population's table as `references` again (one shared dict, not a copy), so
readers are unchanged; writers call dump(), which rebuilds the tables from the
regions and refuses a name bound to two addresses within one population.

On disk the catalog is sharded by population, so a landing rewrites only the
populations it touches and no tracked file approaches a size limit:

    manifests/original_target/index.json              global keys and order
    manifests/original_target/populations/<id>.json   one per population

A shard holds a population's `populations` entry, its reference table and
its regions (in catalog order). index.json holds the top-level key order,
every other top-level value (target, headers, ...), the order of the
`populations` list, the region order as runs of population ids, and the
SHA-256 of every shard; load() refuses a shard that is missing, extra or
differs from its recorded hash (a torn or hand-edited catalog). The loaded
catalog is exactly the dictionary the former monolithic
manifests/original_target.json produced, and dumps() still renders that
monolithic text (byte-identical to the old file) for whole-catalog text
checks. dump() writes only the files whose bytes changed, the index last.

A path ending in .json is the legacy monolithic form (test fixtures, older
commits); it loads and dumps as before, including the older per-region form.
"""
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess

SHARDED = 'manifests/original_target'
LEGACY = 'manifests/original_target.json'
INDEX = 'index.json'
SHARDS = 'populations'
SCHEMA = 'ra2-original-target-shards-v1'
SPECIAL = ('populations', 'population_references', 'regions')
SHARD_ID = re.compile(r'[A-Za-z0-9_][A-Za-z0-9._-]*')


def sha(data):
    return hashlib.sha256(data).hexdigest()


def locate(repository):
    """The repository's catalog: the sharded directory, else a legacy file."""
    sharded, legacy = Path(repository) / SHARDED, Path(repository) / LEGACY
    if sharded.exists():
        if legacy.exists():
            raise ValueError('Both %s and %s exist; remove the stale one' % (SHARDED, LEGACY))
        return sharded
    return legacy


def is_sharded(path):
    return Path(path).suffix != '.json'


def attach(catalog):
    """Give every region its population's reference table (shared dicts)."""
    tables = catalog.get('population_references')
    if tables is not None:
        empty = {}
        for region in catalog['regions']:
            region['references'] = tables.get(region['population'], empty)
    return catalog


def loads(data):
    """Load the legacy monolithic text."""
    return attach(json.loads(data))


def load(path, references=True, blobs=None):
    """Load a catalog (sharded directory or legacy file).

    references=False returns the stored document itself (what json.loads of
    the monolithic file gave: `population_references`, no per-region copy).
    `blobs`, if a dict, receives {Path: bytes} of every file read.
    """
    path = Path(path)
    if is_sharded(path):
        def read(name):
            data = (path / name).read_bytes()
            if blobs is not None:
                blobs[path / name] = data
            return data
        shard_dir = path / SHARDS
        names = sorted(p.name for p in shard_dir.iterdir() if p.suffix == '.json') if shard_dir.is_dir() else []
        catalog = assemble(read, names)
    else:
        data = path.read_bytes()
        if blobs is not None:
            blobs[path] = data
        catalog = json.loads(data)
    return attach(catalog) if references else catalog


def assemble(read, names):
    """Rebuild the stored document from an index and its shards.

    read(relative path) returns bytes; names lists the shard file names present.
    """
    index = json.loads(read(INDEX))
    if index.get('schema') != SCHEMA:
        raise ValueError('Unknown catalog index schema %r' % index.get('schema'))
    expected = {pid + '.json' for pid in index['shards']}
    if set(names) != expected:
        raise ValueError('Catalog shards differ from the index: missing %s, extra %s' % (
            sorted(expected - set(names))[:5], sorted(set(names) - expected)[:5]))
    shards = {}
    for pid, digest in index['shards'].items():
        data = read(SHARDS + '/' + pid + '.json')
        if sha(data) != digest:
            raise ValueError('Catalog shard %s differs from the index (torn or edited catalog)' % pid)
        shard = json.loads(data)
        if shard.get('id') != pid:
            raise ValueError('Catalog shard %s names %r' % (pid, shard.get('id')))
        shards[pid] = shard
    catalog = {}
    for key in index['keys']:
        if key == 'populations':
            catalog[key] = [shards[pid]['population'] for pid in index['populations']]
        elif key == 'population_references':
            catalog[key] = {pid: shards[pid]['references'] for pid in sorted(shards) if 'references' in shards[pid]}
        elif key == 'regions':
            regions, taken = [], {}
            for pid, count in index['region_runs']:
                start = taken.get(pid, 0)
                rows = shards[pid].get('regions', [])[start:start + count]
                if len(rows) != count:
                    raise ValueError('Catalog region runs overrun shard %s' % pid)
                regions.extend(rows)
                taken[pid] = start + count
            if any(len(s.get('regions', [])) != taken.get(pid, 0) for pid, s in shards.items()):
                raise ValueError('Catalog shard regions not covered by the index runs')
            catalog[key] = regions
        else:
            catalog[key] = index['catalog'][key]
    return catalog


def document(catalog):
    """The stored document: per-population tables instead of per-region copies."""
    tables = {}
    for region in catalog.get('regions', ()):
        table = tables.setdefault(region['population'], {})
        for name, value in (region.get('references') or {}).items():
            if table.setdefault(name, value) != value:
                raise ValueError('Reference %s bound to two addresses in %s' % (name, region['population']))
    out = {}
    for key, value in catalog.items():
        if key == 'population_references':
            continue
        if key == 'regions':
            out['population_references'] = {pid: tables[pid] for pid in sorted(tables) if tables[pid]}
            value = [{k: v for k, v in region.items() if k != 'references'} for region in value]
        out[key] = value
    return out


def dumps(catalog):
    """The legacy monolithic text (byte-identical to the former file)."""
    return json.dumps(document(catalog), indent=2) + '\n'


def _items(name, items, last=False):
    # A top-level index value written one compact item per line.
    is_dict = isinstance(items, dict)
    end = '' if last else ','
    if not items:
        return ['  %s: %s%s' % (json.dumps(name), '{}' if is_dict else '[]', end)]
    rows = (['%s: %s' % (json.dumps(k), json.dumps(v)) for k, v in items.items()] if is_dict
            else [json.dumps(v) for v in items])
    return (['  %s: %s' % (json.dumps(name), '{' if is_dict else '[')] +
            ['    %s%s' % (row, ',' if i < len(rows) - 1 else '') for i, row in enumerate(rows)] +
            ['  %s%s' % ('}' if is_dict else ']', end)])


def shard_files(catalog):
    """{relative path: bytes} of the sharded form; deterministic."""
    doc = document(catalog)
    shards, order, runs = {}, [], []

    def shard(pid):
        if not isinstance(pid, str) or not SHARD_ID.fullmatch(pid):
            raise ValueError('Population id unusable as a shard name: %r' % (pid,))
        return shards.setdefault(pid, {'id': pid})
    for population in doc.get('populations', ()):
        entry = shard(population['id'])
        if 'population' in entry:
            raise ValueError('Duplicate population %s' % population['id'])
        entry['population'] = population
        order.append(population['id'])
    for pid, table in doc.get('population_references', {}).items():
        shard(pid)['references'] = table
    for region in doc.get('regions', ()):
        pid = region['population']
        shard(pid).setdefault('regions', []).append(region)
        if runs and runs[-1][0] == pid:
            runs[-1][1] += 1
        else:
            runs.append([pid, 1])
    files, digests = {}, {}
    for pid in sorted(shards):
        data = (json.dumps(shards[pid], indent=2) + '\n').encode()
        files[SHARDS + '/' + pid + '.json'] = data
        digests[pid] = sha(data)
    rest = {k: v for k, v in doc.items() if k not in SPECIAL}
    head = json.dumps(dict(schema=SCHEMA, keys=list(doc), catalog=rest), indent=2)[:-2] + ','
    lines = [head] + _items('populations', order) + _items('region_runs', runs) + \
        _items('shards', digests, last=True) + ['}']
    files[INDEX] = ('\n'.join(lines) + '\n').encode()
    return files


def _replace(path, data):
    temporary = path.with_name(path.name + '.tmp%d' % os.getpid())
    temporary.write_bytes(data)
    os.replace(temporary, path)


def dump(catalog, path):
    """Write the catalog; in the sharded form only files whose bytes changed.

    Shards are written first and the index (which pins their hashes) last, so
    a reader sees the old or the new catalog, or refuses a torn one. Returns
    the relative paths written or removed.
    """
    path = Path(path)
    if not is_sharded(path):
        path.write_text(dumps(catalog))
        return [path.name]
    files = shard_files(catalog)
    (path / SHARDS).mkdir(parents=True, exist_ok=True)
    changed = []
    for name in sorted(files, key=lambda n: n == INDEX):
        target = path / name
        if not target.exists() or target.read_bytes() != files[name]:
            _replace(target, files[name])
            changed.append(name)
    for stale in sorted((path / SHARDS).glob('*.json')):
        if SHARDS + '/' + stale.name not in files:
            stale.unlink()
            changed.append(SHARDS + '/' + stale.name)
    return changed


def files(path):
    """Every file of a catalog on disk (to fingerprint it)."""
    path = Path(path)
    if not is_sharded(path):
        return [path]
    return [path / INDEX] + sorted((path / SHARDS).glob('*.json'))


def digest(path, blobs=None):
    """One SHA-256 naming a catalog on disk, after verifying its shards.

    Sharded: the index's hash (the index pins every shard's hash). Legacy:
    the file's hash. `blobs` may hold bytes already read ({Path: bytes}).
    """
    path = Path(path)
    blobs = {} if blobs is None else blobs
    if is_sharded(path):
        if path / INDEX not in blobs:
            load(path, references=False, blobs=blobs)
        return sha(blobs[path / INDEX])
    data = blobs.get(path)
    return sha(path.read_bytes() if data is None else data)


def header_document(document):
    """The part of a stored document holding plain top-level keys (headers).

    For a sharded catalog's index.json that is its `catalog` value; a legacy
    monolithic document holds them itself.
    """
    return document['catalog'] if document.get('schema') == SCHEMA else document


def load_git(repository, commit, references=True):
    """The catalog as committed at `commit` (sharded or legacy), or None."""
    def git(*args, **kw):
        return subprocess.run(['git', *args], cwd=repository, capture_output=True, check=True, **kw).stdout
    blobs = {}
    for line in git('ls-tree', '-r', '--full-tree', commit, '--', SHARDED, LEGACY).decode().splitlines():
        meta, name = line.split('\t', 1)
        blobs[name] = meta.split()[2]
    prefix = SHARDED + '/'
    names = sorted(n[len(prefix):] for n in blobs if n.startswith(prefix))
    if INDEX not in names:
        if LEGACY not in blobs:
            return None
        catalog = json.loads(git('cat-file', 'blob', blobs[LEGACY]))
        return attach(catalog) if references else catalog
    batch = git('cat-file', '--batch', input=''.join(blobs[prefix + n] + '\n' for n in names).encode())
    contents, offset = {}, 0
    for name in names:
        end = batch.index(b'\n', offset)
        size = int(batch[offset:end].split()[2])
        contents[name] = batch[end + 1:end + 1 + size]
        offset = end + 1 + size + 1
    catalog = assemble(contents.__getitem__, [n[len(SHARDS) + 1:] for n in names if n.startswith(SHARDS + '/')])
    return attach(catalog) if references else catalog
