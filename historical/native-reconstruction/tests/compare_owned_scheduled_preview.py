#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Same-schedule Process, finalization and isolated native move-preview checks."""
import copy
import json
import re
import struct
import subprocess
import time
from collections import Counter
import compare_owned_orders_world as orders
import compare_owned_turret_world as turret_world
import compare_owned_command_world as command_world
import compare_owned_unit_processes as processes
from compare_original import PATCHED_EXPECTED, write_report
from owned_process_events import original as original_events
from presentation_evidence import ROOT, private_path, hash_file, validate_receipt, check_replay_destination
from verify_owned_orders_world import verify

SCHEDULE = orders.SCHEDULE
SOURCES = (*orders.SOURCES, 'src/platform/OwnedUnitSchedule.hpp',
           'src/platform/OwnedUnitMovePreview.hpp', 'tests/owned_world_snapshot.hpp',
           'tests/owned_preview_checks.hpp', 'tests/owned_scheduled_preview_vectors.cpp',
           'tests/owned_scheduled_preview_check.cpp', 'tests/owned_scheduled_preview/CMakeLists.txt',
           'tests/compare_owned_scheduled_preview.py', 'tests/test_owned_scheduled_preview_evidence.py')


def parse(command):
    words = command.split()
    if words and words[0] in ('H', 'X'):
        if len(words) != 2:
            raise ValueError('Malformed scheduled preview command')
        value = int(words[1])
        if not -2147483648 <= value <= 2147483647 or (words[0] == 'X' and value not in (0, 1)):
            raise ValueError('Malformed scheduled preview command')
        return words[0], value
    op, values = orders.parse(command)
    if op in ('T', 'F', 'U'):
        raise ValueError('Scheduled proof requires complete H steps')
    return op, values


def identities(args):
    return {'orders': orders.identities(args),
            'input_schedule_sha256': hash_file(SCHEDULE),
            'sources': {name: hash_file(ROOT/name) for name in SOURCES}}


def validate(evidence, receipt, fingerprint, current):
    validate_receipt(evidence, receipt, fingerprint)
    if evidence['evidence'].get('identities') != current:
        raise ValueError('Scheduled preview identity differs')
    if not evidence['evidence'].get('same_schedule_original_Process0_Process1_finish0_finish1'):
        raise ValueError('Complete original scheduled proof required')
    commands = evidence.get('commands')
    if not commands or len(commands) != len(evidence.get('expected', [])) or len(commands) != len(evidence.get('labels', [])):
        raise ValueError('Scheduled preview counts differ')
    phase = 0; steps = draws = 0; modes = set(); actors = set()
    warm = set(); after = set(); preview = continued = False
    def closed():
        if preview and (after != {0, 1} or not continued):
            raise ValueError('Preview requires later complete drawing and Process')
    for command, result in zip(commands, evidence['expected']):
        op, v = parse(command)
        shape = {'events0', 'events1', 'state'} if op == 'H' else {'state'} if op in ('I', 'J', 'M', 'S', 'B', 'V', 'X') else {'tokens'}
        if not isinstance(result, dict) or set(result) != shape:
            raise ValueError('Malformed scheduled expectation')
        if op == 'P':
            closed(); phase = 1; warm = set(); after = set(); preview = continued = False
        elif op == 'O':
            if phase != 1: raise ValueError('Prepared map required')
            phase = 2
        elif op == 'I':
            if phase != 2: raise ValueError('Fresh reset required')
            phase = 3
        elif op == 'J':
            if phase != 3: raise ValueError('Fresh initialization required')
            phase = 4
        elif phase != 4: raise ValueError('Joined actors required')
        elif op == 'H':
            for id in (0, 1):
                events = result['events'+str(id)]
                if not events or events[-1][0:2] != ['R', id] or sum(e[0] == 'R' for e in events) != 1:
                    raise ValueError('Each scheduled actor requires one terminal return')
            steps += 1
            if preview: continued = True
        elif op == 'D':
            draws += 1; warm.add(v[0])
            if preview: after.add(v[0])
        elif op == 'X':
            if warm != {0, 1}: raise ValueError('Both warm complete draws required before preview')
            modes.add(v); preview = True; continued = False; after = set()
        elif op == 'M': actors.add(v[0])
    closed()
    if not steps or not draws or modes != {0, 1} or actors != {0, 1}:
        raise ValueError('Both actors, preview modes, complete steps and drawing required')


def compare(args, commands, expected, diagnostic):
    proc = subprocess.run(command_world.native_args(args), input='\n'.join(commands)+'\n', text=True, capture_output=True)
    diagnostic.parent.mkdir(parents=True, exist_ok=True)
    diagnostic.with_suffix('.stdout').write_text(proc.stdout)
    diagnostic.with_suffix('.stderr').write_text(proc.stderr)
    if proc.returncode: raise RuntimeError('Native scheduled preview after '+str(len(proc.stdout.splitlines()))+' rows: '+proc.stderr)
    rows = proc.stdout.splitlines()
    if len(rows) != len(commands): raise AssertionError('Scheduled result count differs')
    if 'Warm scheduled preview mode 0: 17 isolation checks: PASS' not in proc.stderr or 'Warm scheduled preview mode 1: 2 isolation checks: PASS' not in proc.stderr:
        raise AssertionError('Warm renderer/preview checks missing: '+proc.stderr)
    counts = Counter()
    for index, (command, row, result) in enumerate(zip(commands, rows, expected)):
        op, v = parse(command); words = row.split()
        if 'state' in result:
            at = words.index('actor-state')
            if words[at:] != result['state']:
                original = result['state']
                n = next((n for n, (a, b) in enumerate(zip(words[at:], original)) if a != b), min(len(words)-at, len(original)))
                raise AssertionError(('Scheduled state differs', index, command, n, words[at+max(0,n-3):at+n+8], original[max(0,n-3):n+8]))
            if op == 'H':
                if words[0] != 'phase0': raise AssertionError('Process0 must run first')
                one, end = words.index('phase1'), words.index('finish')
                for id, segment in ((0, words[1:one]), (1, words[one+1:end])):
                    events = processes.native_events(segment, id)
                    if events != result['events'+str(id)]:
                        raise AssertionError(('Scheduled ordered events differ', index, command, id))
                    counts['Process_calls'] += 1
                    counts['selected_Process_stores'] += sum(e[0] in ('w','A','L') for e in events)
                    counts['logged_queries'] += sum(e[0] == 'Q' for e in events)
                if end+1 != at: raise AssertionError('Unexpected finish events')
        elif words != result['tokens']:
            raise AssertionError(('Scheduled complete drawing/preparation differs', index, command[:80]))
        counts[op] += 1
    return dict(counts)


def generate(args, progress):
    from original_owned_orders_world import OwnedOrdersWorldOracle, ACTORS, DRIVES
    oracle = OwnedOrdersWorldOracle(args.exe, args.assets, args.palette.read_bytes())
    movement = oracle.movement; source = json.loads(SCHEDULE.read_text())
    commands, expected, labels = [], [], []
    progress.update(commands=commands, expected=expected, labels=labels)
    tick = 100; label = ''
    def state(): return list(map(str, [*oracle.process_snapshot(), *oracle.turret_views(tick), *oracle.command_views()]))
    def record(command):
        nonlocal tick
        progress.update(command=command[:100], tick=tick)
        op, v = parse(command)
        if op == 'P': result = {'tokens': list(map(str, oracle.prepare_map(v)))}
        elif op == 'O': result = {'tokens': ['reset']}
        elif op == 'I':
            head, queue, numeric, crusher, parked, heading, first, second, order, turrets = v
            oracle.initialize(head, queue, numeric, parked, heading, turrets)
            movement.put(0x1c01000+0x13d0, 8); result = {'state': state()}
        elif op == 'J':
            movement.u.mem_write(DRIVES[1]+0x34, struct.pack('<3i', *v[:3]))
            movement.u.mem_write(ACTORS[1]+0x4d0, struct.pack('<24i', *v[3:27]))
            movement.u.mem_write(ACTORS[1]+0x530, struct.pack('<3i', *v[27:])); result = {'state': state()}
        elif op == 'H':
            tick = v
            events = [original_events(movement.advance_actor(id, tick)) for id in (0, 1)]
            for id in (0, 1): oracle.finish_tick(id, tick)
            result = {'events0': events[0], 'events1': events[1], 'state': state()}
        elif op == 'X': result = {'state': state()} # Native policy checks; original world does not advance.
        elif op == 'D':
            id, *values = v
            result = {'tokens': list(map(str, [*oracle.draw_shared(id, tick, values), *oracle.process_snapshot(), *oracle.turret_views(tick), *oracle.command_views()]))}
        else:
            id, tick = v[:2]
            if op == 'M': oracle.order(id, tick, v[2:5], v[6:])
            elif op == 'S': oracle.stop_order(id, tick)
            elif op == 'B': oracle.turn_body(id, tick, v[2])
            elif op == 'V': oracle.command_turret(id, tick, v[2])
            else: raise ValueError('Unexpected scheduled command')
            result = {'state': state()}
        commands.append(command); expected.append(result); labels.append(label)
    for label, mode, last in [('both_actors_ramp_entry_exit', 0, 210), ('actor1_curve_Advance2', 1, 140)]:
        tick = 100
        rows = [c for c,l in zip(source['commands'],source['labels']) if l == label]
        for op in ('P','O','I','J'): record(next(c for c in rows if c.startswith(op+' ')))
        draws = [next(c for c in rows if c.startswith(f'D {id} ')) for id in (0,1)]
        for id in (0,1):
            target = struct.unpack('<3i',oracle.u.mem_read(DRIVES[id]+0x34,12))
            route = list(struct.unpack('<24i',oracle.u.mem_read(ACTORS[id]+0x4d0,96)))
            route = route[:route.index(-1)]
            record('M '+' '.join(map(str,[id,tick,*target,len(route),*route])))
        for at in range(101, 119 if args.pilot else last+1):
            if mode == 0:
                if at == 132: record(f'B 0 {at} 8192')
                if at == 134: record(f'S 1 {at}'); record(f'B 1 {at} -65537')
                if at == 135: record(f'B 0 {at} -65537')
                if at == 180:
                    for id in (0,1):
                        where=DRIVES[id]+0x40 if movement.get(DRIVES[id]+0x63,'B') else ACTORS[id]+0x88
                        x,y,z=struct.unpack('<3i',oracle.u.mem_read(where,12))
                        record(f'M {id} {at} {x+256} {y} 0 1 2')
                if at == 190:
                    for id in (0,1): record(f'V {id} {at} -32768')
            record(f'H {at}')
            if at%16 == 4 or at == 116:
                for draw in draws: record(draw)
                print(label, at, flush=True)
            if at == 116:
                record(f'X {mode}')
                for draw in draws[::-1]: record(draw)
    return commands, expected, labels, {
        'same_schedule_original_Process0_Process1_finish0_finish1': True,
        'independent_original_order_calls_on_actual_actors': True,
        'distinct_original_Process_records_shared_owned_world': True,
        'selected_stores_and_all_logged_queries_compared': True,
        'native_preview_policy_and_isolation_separate_from_original_fidelity': True,
        'order_counts': [[id,name,n] for (id,name),n in sorted(oracle.order_counts.items())],
        'process_counts':dict(movement.process_counts), 'actual_Process_entries':dict(movement.root_entries),
        'draws':oracle.shared_calls,'selected_draw_stores':oracle.selected_writes,
        'routes_controls_scheduling_target_lifetime_weapon_services_and_padding_supplied':True,
        'runtime_unwired':True,'pilot':args.pilot}

def main():
    args = processes.owned.shared.arguments()
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/owned-scheduled-preview/owned-scheduled-preview-vectors'
    if args.output == ROOT/'private/unit-draw-1006/shared-ground-world-v1':
        args.output = ROOT/'private/unit-draw-1006/owned-scheduled-preview-v1'
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
    print(f'{len(commands)} scheduled world results / {metadata["draws"]} complete draws: PASS')


if __name__ == '__main__': main()
