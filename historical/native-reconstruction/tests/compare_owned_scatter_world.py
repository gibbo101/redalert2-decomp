#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Distinct original Process pair/Scatter/arrival/drawing on production owners.

Full selected snapshots and complete drawing tokens are compared. Process event
prefixes remain diagnostics, not a claim to compare every ordered machine store.
"""
import json
import struct
import subprocess
import time
import compare_owned_terrain_runtime as runtime
import compare_owned_orders_world as orders
from original_results import OriginalResults, python_closure
from compare_original import PATCHED_EXPECTED, write_report
from presentation_evidence import ROOT, private_path, hash_file, validate_receipt, check_replay_destination

INPUTS = ROOT/'private/unit-draw-1006/owned-advance-runtime-pilot-v1/expected.json'
SOURCES = (*runtime.SOURCES, 'tests/compare_owned_scatter_world.py',
           'tests/original_owned_scatter_world.py', 'tests/test_owned_scatter_world.py')


def parse(command):
    words = command.split()
    if words and words[0] == 'H':
        if len(words) != 2 or not 101 <= int(words[1]) <= 4096:
            raise ValueError('Invalid Scatter schedule tick')
        return 'H', int(words[1])
    if not words or words[0] not in ('P', 'O', 'I', 'J', 'M', 'S', 'B', 'V', 'D'):
        raise ValueError('Scatter interaction requires ordinary commands and scheduled steps')
    return orders.parse(command)


def identities(args):
    return {'runtime': runtime.identities(args), 'authored_inputs_sha256': hash_file(INPUTS),
            'sources': {p: hash_file(ROOT/p) for p in SOURCES},
            'python_sources': python_closure(__file__, {'sources': dict.fromkeys(SOURCES)})}


def sections(tokens, marker, size):
    """Read explicit consumer records, including those appended to complete draws."""
    found = {}
    for i, word in enumerate(tokens):
        if word == marker:
            id, *values = map(int, tokens[i+1:i+size+2])
            if id not in (0, 1) or id in found or len(values) != size:
                raise ValueError('Malformed or duplicate ' + marker)
            found[id] = values
    if set(found) != {0, 1}:
        raise ValueError('Missing actual-owner ' + marker)
    return found


def validate_stream(commands, expected, labels, proof):
    if proof.get('supplied_separate_Drive_height_divisor') != 104:
        raise ValueError('Separate supplied Drive height divisor differs')
    if not commands or not len(commands) == len(expected) == len(labels):
        raise ValueError('Scatter result counts differ')
    phase, tick, draws = 0, 100, [0, 0]
    draw_targets, draw_order, states = [], [], []
    for command, result, label in zip(commands, expected, labels):
        op, value = parse(command)
        if label != 'supplied_flat_two_tank_encounter':
            raise ValueError('Scatter scenario label differs')
        if phase < 4:
            if op != ('P', 'O', 'I', 'J')[phase]:
                raise ValueError('Ordered actual-owner initialization required')
            phase += 1
        elif op in ('P', 'O', 'I', 'J'):
            raise ValueError('One actual-owner initialization required')
        elif op == 'H':
            if value != tick + 1:
                raise ValueError('Consecutive Process pair schedule required')
            tick = value
        elif op == 'D':
            draws[value[0]] += 1
            draw_order.append(value[0])
        if set(result) != ({'tokens'} if op in ('P', 'O', 'D') else {'state'}):
            raise ValueError('Malformed Scatter expectation')
        tokens = result.get('state', result.get('tokens'))
        if not isinstance(tokens, list) or not all(isinstance(v, str) for v in tokens):
            raise ValueError('Scatter expectations must contain string tokens')
        if op not in ('P', 'O'):
            targets = sections(tokens, 'scatter-state', 3)
            if op == 'D':
                if tokens[:2] != ['actor', str(value[0])] or 'surface' not in tokens or 'world' not in tokens:
                    raise ValueError('Complete actual-owner drawing required')
                draw_targets.append([targets[id][:2] for id in (0, 1)])
            states.append(tokens)
    counts = {'0': tick-100, '1': tick-100}
    if (tick != 228 or draws != [3, 3] or draw_order != [0, 1]*3 or
            proof.get('process_counts') != counts or proof.get('actual_Process_entries') != counts or
            proof.get('draws') != sum(draws)):
        raise ValueError('Actual Process/drawing counts differ from command stream')
    destinations = proof.get('scatter_destinations')
    if (not isinstance(destinations, list) or len(destinations) != 1 or
            len(destinations[0]) != 5 or destinations[0][1] != 1):
        raise ValueError('One actual resident Scatter destination required')
    dispatch_tick, _, x, y, z = destinations[0]
    if not 101 <= dispatch_tick <= tick or x % 256 != 128 or y % 256 != 128:
        raise ValueError('Malformed actual Scatter destination')
    target = [x//256, y//256]
    empty = [[-1, -1], [-1, -1]]
    if draw_targets != [empty, empty, [[-1, -1], target], [[-1, -1], target], empty, empty]:
        raise ValueError('Drawing must preserve actual dispatch target through subsequent arrival')
    initial, final = states[0], states[-1]
    def position(tokens, id):
        indices = [i for i, v in enumerate(tokens) if v == 'actor-state' and tokens[i+1] == str(id)]
        if len(indices) != 1:
            raise ValueError('Actual actor snapshot required')
        return list(map(int, tokens[indices[0]+2:indices[0]+5]))
    if position(initial, 1) == [x,y,z] or position(final, 1) != [x,y,z]:
        raise ValueError('Resident must actually reach its selected Scatter destination')
    children = proof.get('child_counts', {})
    required = {'actual.Cell.0x4a32b4': 1, 'actual.Unit.1': 1, 'actual.nearby.1': 1,
                'supplied.snapshot_growth': 1, 'supplied.snapshot_release': 1}
    terminal = proof.get('actual_terminal_drive_store_sites', {})
    if (any(children.get(k) != v for k,v in required.items()) or
            children.get('actual.counter.0', 0) < 1 or children.get('actual.destination.1', 0) != 1 or
            any(terminal.get(ip) != 1 for ip in ('0x4a21fb','0x4a2203','0x4a220c','0x4a2249')) or
            children.get('supplied.atomic.1', 0) != children.get('supplied.atomic.-1', 0) or
            children.get('supplied.atomic.1', 0) < 1):
        raise ValueError('Actual Scatter/nearby/destination child coverage missing')


def validate(envelope, receipt, fingerprint, current):
    validate_receipt(envelope, receipt, fingerprint)
    if envelope.get('executable_sha256') != PATCHED_EXPECTED or envelope.get('profile') != 'supplied-ra2-1006':
        raise ValueError('Scatter engine/profile differs')
    proof = envelope['evidence']
    if proof.get('identities') != current:
        raise ValueError('Scatter identity differs')
    if not proof.get('distinct_Process0_Process1_actual_Scatter_arrival') or not proof.get('target_preserving_complete_draws'):
        raise ValueError('Scatter interaction scope differs')
    validate_stream(*[envelope.get(k, []) for k in ('commands', 'expected', 'labels')], proof)


def native_args(args):
    return [*runtime.processes.native_args(args), '--scatter-interaction']


def compare(args, commands, expected, diagnostic):
    proc = subprocess.run(native_args(args), input='\n'.join(commands)+'\n', text=True, capture_output=True)
    diagnostic.parent.mkdir(parents=True, exist_ok=True)
    diagnostic.with_suffix('.stdout').write_text(proc.stdout)
    diagnostic.with_suffix('.stderr').write_text(proc.stderr)
    if proc.returncode:
        raise RuntimeError(f'Scatter native row {len(proc.stdout.splitlines())}: {proc.stderr}')
    rows = proc.stdout.splitlines()
    if len(rows) != len(commands):
        raise AssertionError('Scatter native result count differs')
    for index, (command, row, wanted) in enumerate(zip(commands, rows, expected)):
        op, _ = parse(command)
        words = row.split()
        actual = words[words.index('actor-state'):] if 'state' in wanted else words
        target = wanted.get('state', wanted.get('tokens'))
        if actual != target:
            at = next((i for i, (a, b) in enumerate(zip(actual, target)) if a != b), min(len(actual), len(target)))
            raise AssertionError(('Scatter result', index, command[:100], at, actual[max(0,at-4):at+10], target[max(0,at-4):at+10]))
    if proc.stderr != 'Owned world guards: 6; unknown actor: 1; warm clone pairs: 0; actual Advance6/7 clone refusals: 0: PASS\n':
        raise AssertionError('Scatter identity guards missing')
    return {'results': len(rows), 'Process_calls': 2*sum(c.startswith('H ') for c in commands),
            'complete_draws': sum(c.startswith('D ') for c in commands)}


def generate(args, progress):
    from original_owned_scatter_world import OwnedScatterWorldOracle
    from original_owned_unit_processes import ACTORS, DRIVES
    oracle = OwnedScatterWorldOracle(args.exe, args.assets, args.palette.read_bytes())
    m = oracle.movement
    source = json.loads(INPUTS.read_text())
    commands, expected, labels = [], [], []
    progress.update(commands=commands, expected=expected, labels=labels)
    tick = 100

    def state():
        values = [*oracle.process_snapshot(), *oracle.turret_views(tick), *oracle.command_views()]
        for id, actor in enumerate(ACTORS):
            target = m.get(actor+0x494)
            values.extend(('scatter-state', id, *(struct.unpack('<2h', m.u.mem_read(target+0x24, 4)) if target else (-1,-1)), m.get(actor+0x53c, 'i')))
        return list(map(str, values))

    def record(command):
        nonlocal tick
        op, value = parse(command)
        progress.update(command=command[:100], tick=tick, counts=dict(m.scatter_counts))
        if op == 'P':
            result = {'tokens': list(map(str, oracle.prepare_map(value)))}
        elif op == 'O':
            result = {'tokens': ['reset']}
        elif op == 'I':
            head, route, numeric, crusher, parked, heading, first, second, order, turrets = value
            oracle.initialize(head, route, numeric, parked, heading, turrets)
            result = {'state': state()}
        elif op == 'J':
            m.u.mem_write(DRIVES[1]+0x34, struct.pack('<3i', *value[:3]))
            m.u.mem_write(ACTORS[1]+0x4d0, struct.pack('<24i', *value[3:27]))
            m.u.mem_write(ACTORS[1]+0x530, struct.pack('<3i', *value[27:]))
            result = {'state': state()}
        elif op == 'H':
            tick = value
            for id in (0, 1):
                m.advance_actor(id, tick)
                oracle.follow_scatter()
            for id in (0, 1):
                oracle.finish_tick(id, tick)
            result = {'state': state()}
        elif op == 'D':
            id, *draw = value
            result = {'tokens': list(map(str, [*oracle.draw_shared(id, tick, draw), *state()]))}
        else:
            id, tick = value[:2]
            if op == 'M': oracle.order(id, tick, value[2:5], value[6:])
            elif op == 'S': oracle.stop_order(id, tick)
            elif op == 'B': oracle.turn_body(id, tick, value[2])
            elif op == 'V': oracle.command_turret(id, tick, value[2])
            result = {'state': state()}
        commands.append(command); expected.append(result); labels.append('supplied_flat_two_tank_encounter')

    f = list(parse(source['commands'][0])[1])
    f[7] = [[*row[:7], 0, *row[8:]] for row in f[7]]  # Supplied flat tile types.
    f[8] = [[*row[:2], 0, *row[3:]] for row in f[8]]
    floor = runtime.processes.owned.shared.floor
    record('P '+floor.command(*f[:5], f[5:]))
    record('O 0 0')
    values = list(map(int, next(c for c in source['commands'] if c.startswith('I ')).split()[1:]))
    values[:7] = [2944, 3200, 0, 0, 0, 0, 16384]
    values[16:40] = [-1]*24
    values[45:49] = [3456, 3200, 0, 16384]
    record('I '+' '.join(map(str, values)))
    record('J '+' '.join(map(str, [0,0,0,*([-1]*24),-1,-17,0])))
    draws = [next(c for c in source['commands'] if c.startswith(f'D {id} ')) for id in (0,1)]
    for command in draws: record(command)
    record('M 0 100 3712 3200 0 3 2 2 2')
    resident = bytes(m.u.mem_read(ACTORS[1]+0x88, 12))
    dispatched = False
    for at in range(101, 229):
        record(f'H {at}')
        if not dispatched and m.scatter_counts['actual.Unit.1']:
            for command in draws: record(command)
            dispatched = True
        if at % 16 == 4: print('Scatter pair tick', at, dict(m.scatter_counts), flush=True)
    for command in draws: record(command)
    assert dispatched and bytes(m.u.mem_read(ACTORS[1]+0x88, 12)) != resident
    assert m.get(ACTORS[1]+0x494) == 0 and m.get(DRIVES[1]+0x63, 'B') == 0
    assert len(m.scatter_destinations) == 1
    assert list(struct.unpack('<3i', m.u.mem_read(ACTORS[1]+0x88, 12))) == m.scatter_destinations[0][2:]
    assert m.process_counts == m.root_entries and min(m.process_counts.values()) == 128
    return commands, expected, labels, {
        'distinct_Process0_Process1_actual_Scatter_arrival': True,
        'target_preserving_complete_draws': True, 'process_counts': {str(k):v for k,v in m.process_counts.items()},
        'actual_Process_entries': {str(k):v for k,v in m.root_entries.items()}, 'child_counts': dict(m.scatter_counts),
        'scatter_destinations': m.scatter_destinations,
        'actual_terminal_drive_store_sites': dict(m.drive_store_sites),
        'draws': oracle.shared_calls, 'selected_snapshots_not_all_Process_events': True,
        'supplied_separate_Drive_height_divisor': m.get(0x8529d0),
        'routing_initial_records_heap_atomic_missions_and_schedule_supplied': True,
        'normal_SDL_Scatter_still_guarded': True}


def main():
    args = runtime.processes.owned.shared.arguments(original_cache=True)
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/owned-terrain-runtime/owned-terrain-runtime-vectors'
    start = time.monotonic(); current = identities(args); runner = hash_file(args.native)
    reuse = OriginalResults(args, current, __file__)
    if args.expectations:
        source = private_path(args.expectations, args.exe); receipt = source.parent/'report.json'
        fingerprint = hash_file(source); envelope = json.loads(source.read_text())
        reuse.validate(validate, envelope, json.loads(receipt.read_text()), fingerprint, current)
        commands, expected, labels = [envelope[k] for k in ('commands','expected','labels')]
        metadata = envelope['evidence']; generation = 0
        report = private_path(args.report, args.exe); check_replay_destination(report, source, receipt)
    else:
        folder = private_path(args.output, args.exe)
        if args.report or (folder/'expected.json').exists() or (folder/'report.json').exists():
            raise ValueError('Fresh Scatter destination invalid or exists')
        now = time.monotonic(); progress = {}
        try: commands, expected, labels, metadata = generate(args, progress)
        except BaseException as error:
            folder.mkdir(parents=True, exist_ok=True)
            write_report(args.exe, folder/'partial-diagnostic.json', {**progress, 'accepted_proof': False, 'error': repr(error), 'identities': current})
            raise
        generation = time.monotonic()-now; report = folder/'report.json'
        write_report(args.exe, folder/'original-diagnostic.json', {'commands':commands,'expected':expected,'labels':labels,'metadata':metadata,'accepted_proof':False,'identities':current})
    validate_stream(commands, expected, labels, metadata)
    now = time.monotonic(); checks = compare(args, commands, expected, report.with_name(report.stem+'-native'))
    comparison = time.monotonic()-now
    if identities(args) != current or hash_file(args.native) != runner:
        raise ValueError('Scatter sources/inputs/runner changed during invocation')
    result = {**metadata, 'identities':current, 'native_sha256':runner, 'cases':len(commands),
              'executable_sha256':PATCHED_EXPECTED, 'profile':'supplied-ra2-1006', 'native_checks':checks,
              'evidence_mode':'cached-original-replay' if args.expectations else 'fresh-original',
              'original_instructions_executed':not bool(args.expectations), 'original_instructions_modified':False,
              'original_generation_seconds':generation, 'native_comparison_seconds':comparison, 'elapsed_seconds':time.monotonic()-start}
    reuse.annotate(result)
    if not args.expectations:
        source = folder/'expected.json'
        write_report(args.exe, source, {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                    'commands':commands,'expected':expected,'labels':labels,'evidence':result})
        fingerprint = hash_file(source)
        validate(json.loads(source.read_text()), {**result, 'expectations_sha256':fingerprint}, fingerprint, current)
    result['expectations_sha256'] = fingerprint; write_report(args.exe, report, result)
    reuse.finish(source, report, validate)
    print(f'{len(commands)} Scatter interaction results / {metadata["draws"]} complete draws: PASS')


if __name__ == '__main__': main()
