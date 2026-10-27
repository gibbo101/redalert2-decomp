#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Verify exact-base ordinary Terrain placement/removal and layer registration."""
import argparse
import hashlib
import itertools
import json
import random
import subprocess
from pathlib import Path
import time
from terrain_lifecycle_evidence import prepare, identities, save, replay, run_native


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def section(text, name):
    found = False
    result = {}
    for line in text.splitlines():
        line = line.split(';', 1)[0].strip()
        if line.startswith('['):
            found = line.lower() == '[' + name.lower() + ']'
        elif found and '=' in line:
            key, value = line.split('=', 1)
            result[key.strip().lower()] = value.strip()
    return result


def layer_tokens(layers):
    return [v for slots, count, grow, valid, owned, storage in layers
            for v in [len(slots), count, grow, valid, owned, storage, *slots]]


def empty_layers():
    return [([], 0, 10, 1, 1, -1) for _ in range(5)]


p = argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe', type=Path, required=True)
p.add_argument('--native', type=Path, default=Path('build/native/lifecycle-vectors'))
p.add_argument('--exporter', type=Path, default=Path('build/native/scenery-vectors'))
p.add_argument('--data-dir', type=Path, default=Path('private/game'))
p.add_argument('--render-data', type=Path, default=Path('private/derived/render-data.bin'))
p.add_argument('--raster-data', type=Path, default=Path('private/derived/raster-data.bin'))
p.add_argument('--expectations', type=Path)
p.add_argument('--report', type=Path)
p.add_argument('--native-data-exe', type=Path, help='Explicit retained disc identity for patched research')
p.add_argument('--cell-exporter', type=Path, default=Path('build/native/map-light-vectors'))
a = p.parse_args();a.suite='lifecycle'
engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
    replay(a,engine_digest,engine_profile,native_data,work)
    raise SystemExit(0)
original_started=time.monotonic()
from original_lifecycle import LifecycleOracle
oracle = LifecycleOracle(a.exe,allow_patched=True)
rng = random.Random(0x52413139)
commands, expected, groups = [], [], {}

def add(group, tokens, result):
    commands.append(' '.join(map(str, tokens)))
    expected.append(list(map(str, result)))
    groups[group] = groups.get(group, 0) + 1

def layer(group, action, actors, layers, target, index=2, sorted=True, allocation=True):
    add(group, ['L', action, len(actors), target, index, int(sorted), int(allocation),
                *[v for actor in actors for v in actor], *layer_tokens(layers)],
        oracle.layer(action, actors, layers, target, index, sorted, allocation))

# All insertion positions, signed wrapped keys, equal-key stability and
# append ordering. Unused capacity tails are included in both final outputs.
keys = [-2147483648, -2147483647, -1, 0, 1, 2147483646, 2147483647]
for n in range(384):
    actors = [(rng.choice(keys), rng.choice(keys), 0, -1) for _ in range(8)]
    if n % 3 == 0:
        actors = [(key, -key if key != -2147483648 else -2147483648, 0, -1)
                  for key in [*keys, 0]]
    ids = list(range(7))
    ids.sort(key=lambda id: oracle.signed(actors[id][0] + actors[id][1]))
    layers = empty_layers()
    layers[2] = (ids + [-2, -2], 7, 10, n % 4, (n // 4) % 4, 2)
    for sorted_insert in [False, True]:
        layer('sorted_wrapped_keys_and_append', 'I', actors, layers, 7, sorted=sorted_insert)
for capacity, owned, valid, grow, allocation, sorted_insert in itertools.product(
        [0, 1, 4], [0, 1, 2, 255], [0, 1, 255], [-1, 0, 1, 10], [False, True], [False, True]):
    actors = [(i * 256, 128, 0, -1) for i in range(5)]
    layers = empty_layers()
    layers[2] = (list(range(capacity)), capacity, grow, valid, owned, 2)
    layer('growth_gates_outcomes_and_capacity_tails', 'I', actors, layers, 4,
          sorted=sorted_insert, allocation=allocation)
for n in range(256):
    actors = [(i * 256, i * -128, 0, -1) for i in range(6)]
    target = n % 6
    last = [-1, 0, 1, 2, 3, 4][n // 6 % 6]
    actors[target] = (*actors[target][:3], last)
    layers = empty_layers()
    for index in range(5):
        slots = [rng.randrange(6) for _ in range(6)]
        if n % 2 == 0 and index == last:
            slots = [id for id in slots if id != target]
        layers[index] = (slots + [-2] * 2, len(slots), 10, 1, 1, index)
    for action in ['S', 'R']:
        layer('known_stale_duplicate_and_unregistered_actors', action, actors, layers, target)
for target in [-1, 0]:
    for action in ['S', 'R']:
        layer('null_and_empty_registration', action, [(0, 0, 0, -1)], empty_layers(), target)

for position in itertools.product([-2147483648, -257, -1, 0, 257, 2147483647], repeat=3):
    first, second = rng.choice(keys), rng.choice(keys)
    add('type_ground_adjustment', ['G', *position, first, second],
        oracle.ground_adjust(position, first, second))
for z, first, second in itertools.product(keys, repeat=3):
    add('type_ground_second_call_and_signed_edges', ['G', 0, 0, z, first, second],
        oracle.ground_adjust((0, 0, z), first, second))

def life(group, actors, cells, steps, layers=None, theater=0, enabled=1,
         loading=0, allocation=True, origin=(0, 0)):
    if layers is None:
        layers = empty_layers()
    tokens = ['T', len(actors), len(cells), len(steps), theater, enabled, loading,
              int(allocation), *origin, *[v for actor in actors for v in actor]]
    for point, values in sorted(cells.items()):
        tokens.extend([*point, *values])
    tokens.extend(layer_tokens(layers))
    for action, id, target in steps:
        tokens.extend([action, id, *target])
    add(group, tokens, oracle.lifecycle(actors, cells, layers, steps, theater,
                                       enabled, loading, allocation, origin))

def actor(on_map=0, redraw=0, limbo=1, active=1, logic=1, vein=0):
    return (18304, 29312, 416, 7, 3, -1, on_map, redraw, limbo,
            2 if on_map else -1, active, logic, vein, 0, 0, -53, 119)

def cells_for(on_map=0, neighbors=0, allowed=True):
    cells = {(x, y): (416, int(allowed), 0x837ac940, -1, -1, neighbors, 17, 14)
             for x in range(70, 73) for y in range(113, 116)}
    if on_map:
        cells[71, 114] = (416, int(allowed), 0x837ac95c, 0, -1, neighbors, 17, 14)
    return cells

# Noncanonical bytes, gate failures and the pre-rejection Limbo side effects.
for enabled, on_map, redraw, limbo in itertools.product([0, 1, 2, 255], repeat=4):
    for action in ['U', 'R']:
        actors = [actor(on_map, redraw, limbo)]
        layers = empty_layers()
        if on_map:
            layers[2] = ([0, -2], 1, 10, 1, 1, 2)
        life('complete_lifecycle_state_gates', actors, cells_for(on_map, 0),
             [(action, 0, (18304, 29312, 416))], layers, enabled=enabled)
for n in range(256):
    on_map = n % 2
    active, logic, vein = [rng.choice([0, 1, 2, 255]) for _ in range(3)]
    actors = [actor(on_map, rng.choice([0, 1, 255]), 0 if on_map else 1,
                    active, logic, vein)]
    layers = empty_layers()
    if on_map:
        layers[2] = ([0], 1, 1, 1, 1, 2)
    else:
        layers[2] = ([], 0, n % 3 - 1, 1, 1, -1)
    action = 'R' if on_map else 'U'
    life('loading_permission_active_logic_vein_and_failure', actors,
         cells_for(on_map, rng.choice([0, 1, 254, 255]), n % 4 != 0),
         [(action, 0, (18304, 29312, 400))], layers, theater=n % 3,
         loading=[0, 1, -1][n % 3], allocation=bool(n % 2),
         origin=(rng.choice(keys), rng.choice(keys)))
for n in range(64):
    life('placement_removal_repetition_and_counter_wrap', [actor()],
         cells_for(neighbors=n % 4 * 85),
         [('U', 0, (18304, 29312, 400)), ('U', 0, (18304, 29312, 416)),
          ('R', 0, (0, 0, 0)), ('R', 0, (0, 0, 0)), ('U', 0, (18304, 29312, 416))],
         theater=n % 3, loading=n % 2, origin=(n * -123, n * 471))

assets = a.assets
rules, art = [(assets / name).read_text() for name in ['rules.ini', 'art.ini']]
types = [f'tree{n:02}' for n in range(1, 29)]
types += [path.stem for path in sorted(assets.glob('*.tem')) if not path.stem.startswith('tree')]
assert len(types) == 51
masks = {}
for id in types:
    data = section(rules, id)
    assert section(art, id)['foundation'] == '1x1'
    assert data.get('isveinhole', 'no').lower() in ['no', 'false', '0']
    masks[id] = tuple(int(data.get(key, '7')) & 0xffffffff
                      for key in ['temperateoccupationbits', 'snowoccupationbits'])
    item = actor()
    item = (*item[:3], *masks[id], *item[5:])
    life('owned_stock_type_inputs', [item], cells_for(),
         [('U', 0, (18304, 29312, 416)), ('R', 0, (0, 0, 0))])
rows = subprocess.check_output([str(a.cell_exporter), '--cells', str(assets / 'mp03t4.map')], text=True)
heights = {(x, y): z for x, y, z in (map(int, line.split()) for line in rows.splitlines())}
placements = [(int(key) % 1000, int(key) // 1000, id.lower())
              for key, id in section((assets / 'mp03t4.map').read_text(), 'Terrain').items()
              if id.lower() in masks]
assert len(placements) == 565
all_actors = []
for x, y, id in placements:
    z = heights[x, y] * 104
    item = (x * 256 + 128, y * 256 + 128, z, *masks[id], -1, 0, 0, 1,
            -1, 1, 1, 0, 0, 0, 0, 0)
    cells = {(cx, cy): (heights[cx, cy] * 104, 1, 0, -1, -1, 0, -1, 0)
             for cx in range(x - 1, x + 2) for cy in range(y - 1, y + 2)}
    life('owned_map_placement_removal_restoration', [item], cells,
         [('U', 0, item[:3]), ('R', 0, (0, 0, 0)), ('U', 0, item[:3])])
    all_actors.append(item)
all_cells = {point: (z * 104, 1, 0, -1, -1, 0, -1, 0) for point, z in heights.items()}
steps = [('U', id, item[:3]) for id, item in enumerate(all_actors)]
steps += [('R', id, (0, 0, 0)) for id in reversed(range(len(all_actors)))]
steps += [('U', id, item[:3]) for id, item in enumerate(all_actors)]
life('complete_565_actor_map_sequence', all_actors, all_cells, steps, origin=(-999, 2147483647))
inputs = [assets / name for name in ['rules.ini', 'art.ini', 'mp03t4.map']]
inputs += [a.render_data, a.raster_data]
inputs += [Path('tests') / name for name in ['compare_lifecycle.py', 'original_lifecycle.py',
          'original_occupation.py', 'original_presentation.py', 'compare_original.py', 'lifecycle_vectors.cpp']]
inputs += [Path('src/sim') / name for name in ['ObjectLayers.cpp', 'ObjectLayers.hpp',
           'TerrainLifecycle.cpp', 'TerrainLifecycle.hpp', 'TerrainOccupation.cpp', 'TerrainOccupation.hpp']]
report = {'executable_sha256': engine_digest, 'input_sha256': {str(path): digest(path) for path in inputs},
          'groups': groups, 'seed': 0x52413139, 'stock_types': len(types),
          'map_placements': len(placements), 'map_cells': len(all_cells),
          'map_sequence_calls': len(steps), 'original_instructions_modified': False,
          'scope': 'Complete ordinary Terrain/Object Unlimbo and Limbo, actual Mark/Map/Cell membership, type adjustment, ground-layer and sorting getters, layer insertion/submission/removal/resize/search. Final states, full capacity tails and ordered writes/services; actor/type/cell/map-table/scenario/tactical/buffer arenas, caller stack/ESP and callee-saved registers audited. Supplied ground/flat cell height, null-type Track placement permission, visible/redraw/logic/global cleanup and allocator outcomes. No selected actors, alpha/radial resources, bridges or elevated membership. Construction/storage, full draw/update scheduling, clearance/pathfinding and whole-frame parity excluded.'}

original_seconds=time.monotonic()-original_started
native_started=time.monotonic();actual=run_native(a,commands)
native_seconds=time.monotonic()-native_started
if len(actual)!=len(expected):raise AssertionError(f'Result count {len(actual)}/{len(expected)}')
for i,(native,original) in enumerate(zip(actual,expected)):
    if native!=original:
        index=next((j for j,pair in enumerate(zip(native,original)) if pair[0]!=pair[1]),min(len(native),len(original)))
        raise AssertionError(f'Case {i}, token {index}: {commands[i][:120]}: native {native[max(0,index-8):index+24]}, original {original[max(0,index-8):index+24]}; lengths {len(native)}/{len(original)}')
report={**report,**identities(a,engine_digest,engine_profile,native_data),'cases':len(commands),
         'original_generation_seconds':original_seconds,'native_comparison_seconds':native_seconds,
         'audited_callable_roots':oracle.audit_calls,'audited_image_writes':oracle.audit_image_writes}
save(a,work,commands,expected,report)
print(f'{len(commands):,} fresh {engine_profile} original/native lifecycle results: PASS; {report["groups"]}')
