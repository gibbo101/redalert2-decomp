"""Read and write the canonical catalog (manifests/original_target.json).

Every region carries the reference bindings (mangled name -> address) used to
verify its relocations. Regions of one population share nearly all of them,
and the verifier merges them per compile group anyway, so the catalog stores
one table per population (`population_references`) instead of a copy per
region (which made the file over a gigabyte). On load each region gets its
population's table as `references` again (one shared dict, not a copy), so
readers are unchanged; writers call dump(), which rebuilds the tables from the
regions and refuses a name bound to two addresses within one population.
A catalog in the older per-region form loads unchanged.
"""
import json
from pathlib import Path


def loads(data):
    catalog = json.loads(data)
    tables = catalog.get('population_references')
    if tables is not None:
        empty = {}
        for region in catalog['regions']:
            region['references'] = tables.get(region['population'], empty)
    return catalog


def load(path):
    return loads(Path(path).read_bytes())


def dumps(catalog):
    tables = {}
    for region in catalog['regions']:
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
    return json.dumps(out, indent=2) + '\n'


def dump(catalog, path):
    Path(path).write_text(dumps(catalog))
