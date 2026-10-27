#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Independent route/stop/body commands on the actual shared Process/draw world."""
import copy
import json
import re
import struct
import subprocess
import time
from collections import Counter
import compare_owned_turret_world as turret_world
import compare_owned_command_world as command_world
import compare_owned_unit_processes as processes
from compare_original import PATCHED_EXPECTED, write_report
from owned_process_events import original as original_events
from presentation_evidence import ROOT, private_path, hash_file, validate_receipt, check_replay_destination
from verify_owned_orders_world import verify

SCHEDULE = turret_world.SCHEDULE
SOURCES = (*turret_world.SOURCES, 'src/platform/OwnedUnitOrders.hpp',
           'tools/verify_owned_orders_world.py', 'tests/original_owned_orders_world.py',
           'tests/owned_orders_world_vectors.cpp', 'tests/owned_orders_world_check.cpp',
           'tests/owned_orders_world/CMakeLists.txt', 'tests/compare_owned_orders_world.py',
           'tests/test_owned_orders_world_evidence.py')
ORDER_OPS = ('M', 'S', 'B', 'F')


def parse(command):
    words = command.split()
    if words and words[0] in ORDER_OPS:
        op = words[0]
        v = list(map(int, words[1:]))
        if not all(-2147483648 <= n <= 2147483647 for n in v) or len(v) < 2 or v[0] not in (0, 1):
            raise ValueError('Malformed owned order')
        if op == 'M':
            if len(v) < 7 or not 1 <= v[5] <= 23 or len(v) != 6+v[5] or not all(0 <= d <= 7 for d in v[6:]) or v[2:5] == [0, 0, 0]:
                raise ValueError('Malformed owned move')
        elif len(v) != (3 if op == 'B' else 2):
            raise ValueError('Malformed owned stop/turn/finish')
        return op, v
    return turret_world.parse(command)


def identities(args):
    return {'world': turret_world.identities(args), 'orders': verify(args.exe.read_bytes()),
            'input_schedule_sha256': hash_file(SCHEDULE),
            'sources': {name: hash_file(ROOT/name) for name in SOURCES}}


def validate(evidence, receipt, fingerprint, current):
    validate_receipt(evidence, receipt, fingerprint)
    if evidence['evidence'].get('identities') != current:
        raise ValueError('Owned order identity differs')
    if not evidence['evidence'].get('independent_original_order_calls_on_actual_actors'):
        raise ValueError('Original per-actor command proof required')
    if not (evidence.get('commands') and len(evidence['commands']) == len(evidence.get('expected', [])) == len(evidence.get('labels', []))):
        raise ValueError('Owned order counts differ')
    rows, seen = [], set()
    joined = False
    for c, r, label in zip(evidence['commands'], evidence['expected'], evidence['labels']):
        op, v = parse(c)
        if op == 'P': joined = False
        if op == 'J': joined = True
        if op in (*ORDER_OPS, 'V', 'U'):
            if not joined or not isinstance(r, dict) or set(r) != {'state'}:
                raise ValueError('Owned orders require joined actors and state')
            if op in ORDER_OPS: seen.add((v[0], op))
        else:
            rows.append((c, r, label))
    if seen != {(id, op) for id in (0, 1) for op in ORDER_OPS}:
        raise ValueError('Both actors require move/stop/body/finish streams')
    if not rows: raise ValueError('Process/drawing proof required')
    base = copy.deepcopy(evidence)
    base['commands'], base['expected'], base['labels'] = map(list, zip(*rows))
    command_world.validate(base, receipt, fingerprint, current)


def compare(args, commands, expected, diagnostic):
    proc = subprocess.run(command_world.native_args(args), input='\n'.join(commands)+'\n', text=True, capture_output=True)
    diagnostic.parent.mkdir(parents=True, exist_ok=True)
    diagnostic.with_suffix('.stdout').write_text(proc.stdout)
    diagnostic.with_suffix('.stderr').write_text(proc.stderr)
    if proc.returncode:
        raise RuntimeError('Native orders after '+str(len(proc.stdout.splitlines()))+' rows: '+proc.stderr)
    rows = proc.stdout.splitlines()
    if len(rows) != len(commands): raise AssertionError('Owned orders result count differs')
    guards = re.fullmatch(r'Owned world guards: (\d+); unknown actor: (\d+); warm clone pairs: (\d+); actual Advance6/7 clone refusals: (\d+): PASS\n', proc.stderr)
    if guards is None or tuple(map(int, guards.groups()[:2])) != (6*sum(c.startswith('I ') for c in commands), sum(c.startswith('I ') for c in commands)):
        raise AssertionError('Owned orders native ownership checks missing: '+proc.stderr)
    counts = Counter()
    for index, (command, row, result) in enumerate(zip(commands, rows, expected)):
        op, v = parse(command)
        words = row.split()
        if op in ('I', 'J', 'T', 'V', 'U', *ORDER_OPS):
            at = words.index('actor-state')
            if words[at:] != result['state']:
                original = result['state']
                n = next((n for n, (a, b) in enumerate(zip(words[at:], original)) if a != b), min(len(words)-at, len(original)))
                raise AssertionError(('Owned orders state differs', index, command, n,
                                      words[at+max(0,n-3):at+n+8], original[max(0,n-3):n+8]))
            if op == 'T':
                events = processes.native_events(words[:at], v[0])
                if events != result['events']:
                    raise AssertionError(('Owned orders Process events differ', index, command))
                counts['selected_Process_stores'] += sum(e[0] in ('w','A','L') for e in events)
                counts['logged_queries'] += sum(e[0] == 'Q' for e in events)
                counts['Process_calls'] += 1
        elif words != result['tokens']:
            raise AssertionError(('Owned orders complete draw/preparation differs', index, command[:80]))
        counts[op] += 1
    return dict(counts)


def generate(args, progress):
    from original_owned_orders_world import OwnedOrdersWorldOracle, ACTORS, DRIVES
    oracle = OwnedOrdersWorldOracle(args.exe, args.assets, args.palette.read_bytes())
    movement = oracle.movement
    source = json.loads(SCHEDULE.read_text())
    source_rows = [c for c, l in zip(source['commands'], source['labels']) if l == 'both_actors_ramp_entry_exit']
    commands, expected, labels = [], [], []
    progress.update(commands=commands, expected=expected, labels=labels)
    label = 'independent_ramp_move_stop_deferred_turn_restart'
    tick = 100

    def state():
        return list(map(str, [*oracle.process_snapshot(), *oracle.turret_views(tick), *oracle.command_views()]))

    def record(command):
        nonlocal tick
        progress.update(command=command[:100], tick=tick)
        op, v = parse(command)
        if op == 'P': result = {'tokens': list(map(str, oracle.prepare_map(v)))}
        elif op == 'O': result = {'tokens': ['reset']}
        elif op == 'I':
            head, queue, numeric, crusher, parked, heading, first, second, order, turrets = v
            oracle.initialize(head, queue, numeric, parked, heading, turrets)
            movement.put(0x1c01000+0x13d0, 8)
            result = {'state': state()}
        elif op == 'J':
            movement.u.mem_write(DRIVES[1]+0x34, struct.pack('<3i', *v[:3]))
            movement.u.mem_write(ACTORS[1]+0x4d0, struct.pack('<24i', *v[3:27]))
            movement.u.mem_write(ACTORS[1]+0x530, struct.pack('<3i', *v[27:]))
            result = {'state': state()}
        elif op == 'T':
            id, tick = v
            result = {'events': original_events(movement.advance_actor(id, tick)), 'state': state()}
        elif op == 'D':
            id, *values = v
            result = {'tokens': list(map(str, [*oracle.draw_shared(id, tick, values),
                       *oracle.process_snapshot(), *oracle.turret_views(tick), *oracle.command_views()]))}
        else:
            id, tick = v[:2]
            if op == 'M': oracle.order(id, tick, v[2:5], v[6:])
            elif op == 'S': oracle.stop_order(id, tick)
            elif op == 'B': oracle.turn_body(id, tick, v[2])
            elif op == 'F': oracle.finish_tick(id, tick)
            elif op == 'V': oracle.command_turret(id, tick, v[2])
            else: raise ValueError('Unexpected authored orders command')
            result = {'state': state()}
        commands.append(command); expected.append(result); labels.append(label)

    for op in ('P', 'O', 'I', 'J'): record(next(c for c in source_rows if c.startswith(op+' ')))
    draws = [next(c for c in source_rows if c.startswith(f'D {id} ')) for id in (0, 1)]
    for id in (0, 1):
        p = ACTORS[id]
        target = struct.unpack('<3i', oracle.u.mem_read(DRIVES[id]+0x34, 12))
        route = list(struct.unpack('<24i', oracle.u.mem_read(p+0x4d0, 96)))
        route = route[:route.index(-1)]
        record('M '+' '.join(map(str, [id, tick, *target, len(route), *route])))
    for tick in range(101, 125 if args.pilot else 241):
        for id in (0, 1): record(f'T {id} {tick}')
        if tick in (106, 180):
            for id, delta in ((0, 32768), (1, -65537)): record(f'V {id} {tick} {delta}')
        if tick == 112: record(f'S 0 {tick}')
        if tick == 113: record(f'B 0 {tick} 8192')
        if tick == 114: record(f'S 1 {tick}'); record(f'B 1 {tick} -16384')
        if tick == 115: record(f'B 0 {tick} -65537')
        if tick == 165:
            for id in (0, 1): record(f'B {id} {tick} 65537')
        if tick == 176:
            for id in (0, 1):
                p = DRIVES[id]+0x40 if movement.get(DRIVES[id]+0x63, 'B') else ACTORS[id]+0x88
                x, y, z = struct.unpack('<3i', oracle.u.mem_read(p, 12))
                record(f'M {id} {tick} {x+256} {y} 0 1 2')
        if tick == 190:
            for id in (0, 1): record(f'S {id} {tick}'); record(f'B {id} {tick} -32768')
        for id in (0, 1): record(f'F {id} {tick}')
        if tick % 16 == 4:
            for draw in (draws if tick % 32 == 4 else draws[::-1]): record(draw)
            print(label, tick, dict(oracle.order_counts), flush=True)
    if not args.pilot:
        for id in (0, 1):
            for branch in ('deferred-body', 'idle-body', 'applied-deferred-body'):
                assert oracle.order_counts[(id, branch)] > 0, (id, branch)
            for root in ('0x49fe30', '0x49fef0', '0x4a0fd0'):
                assert oracle.order_counts[(id, root)] > 0, (id, root)
    return commands, expected, labels, {
        'stable_command_world_owner': True,
        'independent_original_order_calls_on_actual_actors': True,
        'distinct_original_Process_records_shared_owned_world': True,
        'selected_stores_and_all_logged_queries_compared': True,
        'order_counts': [[id, name, n] for (id, name), n in sorted(oracle.order_counts.items())],
        'original_order_stores': oracle.order_stores,
        'actual_order_instruction_count': len(oracle.order_instructions),
        'turret_counts': [[id, name, n] for (id, name), n in sorted(oracle.turret_counts.items())],
        'process_counts': dict(movement.process_counts), 'actual_Process_entries': dict(movement.root_entries),
        'draws': oracle.shared_calls, 'selected_draw_stores': oracle.selected_writes,
        'routes_controls_scheduling_target_lifetime_weapon_services_and_padding_supplied': True,
        'runtime_unwired': True, 'pilot': args.pilot}

def main():
    args = processes.owned.shared.arguments()
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/owned-orders-world/owned-orders-world-vectors'
    if args.output == ROOT/'private/unit-draw-1006/shared-ground-world-v1':
        args.output = ROOT/'private/unit-draw-1006/owned-orders-world-v1'
    start = time.monotonic(); current = identities(args); runner = hash_file(args.native)
    if args.expectations:
        source = private_path(args.expectations, args.exe); receipt = source.parent/'report.json'
        fingerprint = hash_file(source); envelope = json.loads(source.read_text())
        validate(envelope, json.loads(receipt.read_text()), fingerprint, current)
        commands, expected, labels = [envelope[k] for k in ('commands','expected','labels')]
        metadata = envelope['evidence']; generation = 0
        report = private_path(args.report, args.exe); check_replay_destination(report, source, receipt)
    else:
        folder = private_path(args.output, args.exe)
        if args.report or (folder/'expected.json').exists() or (folder/'report.json').exists():
            raise ValueError('Fresh orders destination invalid or exists')
        now = time.monotonic(); progress = {}
        try: commands, expected, labels, metadata = generate(args, progress)
        except BaseException as error:
            folder.mkdir(parents=True, exist_ok=True)
            write_report(args.exe, folder/'partial-diagnostic.json', {**progress, 'accepted_proof': False, 'error': repr(error), 'identities': current})
            raise
        generation = time.monotonic()-now; report = folder/'report.json'
        write_report(args.exe, folder/'original-diagnostic.json', {'commands':commands,'expected':expected,'labels':labels,'metadata':metadata,'accepted_proof':False,'identities':current})
    now = time.monotonic(); checks = compare(args, commands, expected, report.with_name(report.stem+'-native'))
    comparison = time.monotonic()-now
    if identities(args) != current or hash_file(args.native) != runner:
        raise ValueError('Orders sources/inputs/runner changed during invocation')
    result = {**metadata, 'identities':current,'native_sha256':runner,'cases':len(commands),
              'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006', 'native_checks':checks,
              'evidence_mode':'cached-original-replay' if args.expectations else 'fresh-original',
              'original_instructions_executed':not bool(args.expectations),'original_instructions_modified':False,
              'original_generation_seconds':generation,'native_comparison_seconds':comparison,'elapsed_seconds':time.monotonic()-start}
    if not args.expectations:
        source = folder/'expected.json'
        write_report(args.exe, source, {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                    'commands':commands,'expected':expected,'labels':labels,'evidence':result})
        fingerprint = hash_file(source)
    result['expectations_sha256'] = fingerprint; write_report(args.exe, report, result)
    print(f'{len(commands)} shared orders results / {metadata["draws"]} complete draws: PASS')


if __name__ == '__main__': main()
