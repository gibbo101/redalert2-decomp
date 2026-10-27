#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare exact-base ordinary Terrain occupation, membership and Mark decisions."""
import argparse
import hashlib
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

p = argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe', type=Path, required=True)
p.add_argument('--native', type=Path, default=Path('build/native/occupation-vectors'))
p.add_argument('--exporter', type=Path, default=Path('build/native/scenery-vectors'))
p.add_argument('--render-data', type=Path, default=Path('private/derived/render-data.bin'))
p.add_argument('--raster-data', type=Path, default=Path('private/derived/raster-data.bin'))
p.add_argument('--data-dir', type=Path, default=Path('private/game'))
p.add_argument('--expectations', type=Path)
p.add_argument('--report', type=Path)
p.add_argument('--native-data-exe', type=Path, help='Explicit retained disc identity for patched research')
p.add_argument('--cell-exporter', type=Path, default=Path('build/native/map-light-vectors'))
a = p.parse_args();a.suite='occupation'
engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
    replay(a,engine_digest,engine_profile,native_data,work)
    raise SystemExit(0)
original_started=time.monotonic()
from original_occupation import OccupationOracle
o = OccupationOracle(a.exe,allow_patched=True)
commands, expected, groups = [], [], {}
rng = random.Random(0x52413138)

def add(group, command, result):
    commands.append(' '.join(map(str, command)))
    expected.append(list(map(str, result)))
    groups[group] = groups.get(group, 0) + 1

def occupation(group, x, y, z, theater, temperate, snow, flags, mark):
    args = [x, y, z, theater, temperate, snow, flags, mark]
    add(group, ['O', *args], o.occupation(*args))

# Exhaust each relevant low mask/flag combination in both directions and
# both theater paths. Non-snow chooses temperate, even outside named theaters.
for theater in [0, 1]:
    for mask in range(8):
        for low in range(256):
            for mark in [0, 1]:
                occupation('exhaustive_masks_flags', 18304, 29312, 416,
                           theater, mask, mask, 0xa573c900 | low, mark)
edges = [-2147483648, -8388864, -8388609, -8388608, -65537, -257,
         -256, -255, -1, 0, 1, 255, 256, 257, 8388351, 8388352,
         8388607, 8388608, 2147483647]
for x in edges:
    for y in edges:
        for mark in [0, 1]:
            occupation('signed_coordinates_word_wrap', x, y, rng.choice(edges),
                       rng.choice([-2147483648, -1, 0, 1, 2, 2147483647]),
                       rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32), mark)
for i in range(512):
    occupation('seeded_masks_theaters', *[rng.randrange(-2147483648, 2147483648) for _ in range(3)],
               rng.choice([-2147483648, -200, -1, 0, 1, 2, 200, 2147483647]),
               rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32), i % 2)

def state(group, op, theater, cx, cy, flags, head, alt, items, target, mode, alternate=0):
    command = [op, theater, cx, cy, flags, head, alt, len(items), target, mode, alternate,
               *[v for item in items for v in item]]
    add(group, command, o.state(op, theater, cx, cy, flags, head, alt, items, target, mode, alternate))

def actors(cx, cy, count):
    return [(cx * 256 + 128, cy * 256 + 128, 416, rng.getrandbits(32),
             rng.getrandbits(32), -1, 1, 0, 0) for _ in range(count)]

# Finite lists plus the exact head->next insertion guard. A raw insertion
# of an existing head can create a self-link; test its writes but do not
# feed that invalid cyclic list to traversal/removal.
for alternate in [0, 1]:
    for theater in [-1, 0, 1, 2]:
        for n in range(96):
            cx, cy = rng.choice([(0, 0), (71, 114), (511, 511)])
            count = n % 7 + 1
            items = actors(cx, cy, count)
            order = list(range(count))
            rng.shuffle(order)
            length = n % (count + 1)
            chain = order[:length]
            for i, id in enumerate(chain):
                items[id] = (*items[id][:5], chain[i + 1] if i + 1 < length else -1, *items[id][6:])
            head = chain[0] if chain else -1
            target = n // 7 % count
            heads = (-1, head) if alternate else (head, -1)
            for mode in [4, 5]:
                state('complete_cell_lists', 'S', theater, cx, cy, rng.getrandbits(32),
                      *heads, items, target, mode, alternate)

for on_map in [0, 1, 2, 255]:
    for redraw in [0, 1, 2, 255]:
        for limbo in [0, 1, 2, 255]:
            for mode in [-2147483648, -1, 0, 1, 2, 3, 4, 5, 2147483647]:
                items = [(18304, 29312, 416, 7, 3, -1, on_map, redraw, limbo)]
                state('complete_mark_state_modes', 'M', mode & 1, 71, 114, 0xa573c91c,
                      0 if on_map else -1, -1, items, 0, mode)
# Full Mark through multi-member insertion/removal, missing-member unmark,
# and overlapping occupation; no reference-count semantics are imposed.
for n in range(192):
    items = actors(71, 114, 4)
    for id in range(3):
        items[id] = (*items[id][:5], id + 1 if id < 2 else -1, 1, 0, 0)
    target = n % 4
    mode = [0, 1, 2, 3][n // 4 % 4]
    items[target] = (*items[target][:6], int(mode in [0, 2]), n // 16 % 2, 0)
    # Insertion targets must be absent to retain a valid resulting list.
    if mode in [1, 3]:
        target = 3
        items[3] = (*items[3][:6], 0, n // 16 % 2, 0)
    state('complete_map_mark_lists', 'M', n % 3, 71, 114, rng.getrandbits(32),
          0, -1, items, target, mode)

assets = a.assets
rules = (assets / 'rules.ini').read_text()
art = (assets / 'art.ini').read_text()
# Independently enumerate the supplied ordinary profile and map placements.
types = [f'tree{n:02}' for n in range(1, 29)]
types += [path.stem for path in sorted(assets.glob('*.tem')) if not path.stem.startswith('tree')]
assert len(set(types)) == 51
masks = {}
for id in types:
    data = section(rules, id)
    assert section(art, id)['foundation'] == '1x1'
    masks[id] = tuple(int(data.get(key, '7')) & 0xffffffff
                      for key in ['temperateoccupationbits', 'snowoccupationbits'])
    for theater in [0, 1, 2]:
        for mode in [0, 1, 2, 3]:
            on_map = int(mode in [0, 2])
            items = [(18304, 29312, 416, *masks[id], -1, on_map, 0, 0)]
            state('owned_stock_type_inputs', 'M', theater, 71, 114, 0xa573c91c,
                  0 if on_map else -1, -1, items, 0, mode)
rows = subprocess.check_output([str(a.cell_exporter), '--cells', str(assets / 'mp03t4.map')], text=True)
heights = {(x, y): z for x, y, z in (map(int, line.split()) for line in rows.splitlines())}
placements = [(int(key) % 1000, int(key) // 1000, id.lower())
              for key, id in section((assets / 'mp03t4.map').read_text(), 'Terrain').items()
              if id.lower() in masks]
assert len(placements) == 565
for cx, cy, id in placements:
    items = [(cx * 256 + 128, cy * 256 + 128, heights[cx, cy] * 104, *masks[id], -1, 0, 0, 0)]
    result = o.state('M', 0, cx, cy, 0, -1, -1, items, 0, 1, 0)
    add('owned_map_insertions', ['M', 0, cx, cy, 0, -1, -1, 1, 0, 1, 0, *items[0]], result)
    items[0] = (*items[0][:6], 1, 1, 0)
    state('owned_map_removals', 'M', 0, cx, cy, result[3], 0, -1, items, 0, 0)
inputs = [assets / name for name in ['rules.ini', 'art.ini', 'mp03t4.map']]
inputs += [Path('tests') / name for name in ['compare_occupation.py', 'original_occupation.py',
                                           'original_presentation.py', 'compare_original.py']]
report = {'executable_sha256': engine_digest, 'input_sha256': {str(path): digest(path) for path in inputs},
          'groups': groups, 'seed': 0x52413138, 'stock_types': len(types), 'map_placements': len(placements),
          'stock_masks': masks, 'original_instructions_modified': False,
          'scope': 'Complete ordinary Terrain mark/unmark occupation, Cell insertion/removal and Object/Terrain Mark through actual Map insert/remove, layer/height, type/foundation getters. Compare final state and ordered writes/services; audit actor/type/scenario/cell/map-table arenas, caller stack and callee-saved registers. Supplied 1x1 foundation pointer, flat height/ground-relative-zero, no attached animation, visible and redraw/queue/lookup services. Original INI parsing, complete construction/Unlimbo/lifecycle, scheduling/ordering, visibility effects and locomotor collision/pathfinding excluded.'}

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
         'audited_callable_roots':o.audit_calls,'audited_image_writes':o.audit_image_writes}
save(a,work,commands,expected,report)
print(f'{len(commands):,} fresh {engine_profile} original/native occupation results: PASS; {report["groups"]}')
