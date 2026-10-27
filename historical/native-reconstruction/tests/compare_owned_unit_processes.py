#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare two explicit owned Process records and shared complete Unit drawing."""
import json
import re
import struct
import subprocess
import time

import compare_owned_unit_world as owned
from original_results import OriginalResults
from compare_original import PATCHED_EXPECTED, write_report
from owned_process_events import original as original_events, native as native_events
from presentation_evidence import (ROOT, private_path, hash_file, validate_receipt,
                                   check_replay_destination)
from verify_owned_unit_processes import verify

SOURCES = tuple(dict.fromkeys((*owned.SOURCES, 'tests/original_owned_unit_processes.py',
    'tests/compare_owned_unit_processes.py', 'tests/owned_process_events.py',
    'tests/test_owned_unit_processes_evidence.py', 'tools/verify_owned_unit_processes.py')))


def parse(command):
    words = command.split()
    if not words:
        raise ValueError('Empty owned Process command')
    op = words[0]
    if op in ('P', 'O', 'I', 'D'):
        return owned.parse(command)
    if op == 'T' and len(words) == 3:
        actor, tick = map(int, words[1:])
        if actor in (0, 1) and -2147483648 <= tick <= 2147483647:
            return op, (actor, tick)
    if op == 'J' and len(words) == 31:
        values = list(map(int, words[1:]))
        if (all(-2147483648 <= n <= 2147483647 for n in values) and
                all(-1 <= n <= 7 for n in values[3:27]) and values[26] == -1):
            return op, values
    raise ValueError('Malformed owned Process command')


def identities(args):
    return {'world': owned.identities(args),
            'inspection': verify((ROOT / 'private/disc-allied/game.exe').read_bytes(), args.exe.read_bytes()),
            'sources': {name: hash_file(ROOT / name) for name in SOURCES}}


def validate(evidence, receipt, fingerprint, current):
    validate_receipt(evidence, receipt, fingerprint)
    if evidence.get('executable_sha256') != PATCHED_EXPECTED or evidence.get('profile') != 'supplied-ra2-1006':
        raise ValueError('Owned Processes engine/profile differs')
    if evidence['evidence'].get('identities') != current:
        raise ValueError('Owned Processes identity differs')
    if not (evidence['evidence'].get('distinct_original_Process_records_shared_owned_world') and
            evidence['evidence'].get('selected_stores_and_all_logged_queries_compared')):
        raise ValueError('Owned Processes join differs')
    commands = evidence.get('commands')
    if not commands or len(commands) != len(evidence.get('labels', [])) or len(commands) != len(evidence.get('expected', [])):
        raise ValueError('Owned Processes counts differ')
    prepared = reset = initialized = joined = False
    pending = None
    paired = False
    for command, result in zip(commands, evidence['expected']):
        try:
            op, values = parse(command)
        except (ValueError, AssertionError, TypeError, IndexError, OverflowError, struct.error):
            raise ValueError('Malformed owned Process command') from None
        if not isinstance(result, dict) or set(result) != ({'events', 'state'} if op == 'T' else {'state'} if op in ('I', 'J') else {'tokens'}):
            raise ValueError('Malformed owned Process expectation')
        if op == 'P':
            if pending is not None:
                raise ValueError('Incomplete original Process pair')
            prepared = True
            reset = initialized = joined = paired = False
        elif op == 'O':
            if not prepared or reset:
                raise ValueError('Fresh prepared map required')
            reset = True
        elif op == 'I':
            if not reset or initialized:
                raise ValueError('Fresh reset required')
            initialized = True
        elif op == 'J':
            if not initialized or joined:
                raise ValueError('Fresh owned initialization required')
            joined = True
        else:
            if not joined:
                raise ValueError('Both owned Process records required')
            if op == 'T':
                actor, tick = values
                if actor == 0:
                    if pending is not None:
                        raise ValueError('Process1 must follow Process0')
                    pending = tick
                else:
                    if pending != tick:
                        raise ValueError('Process1 must retain the paired tick')
                    pending = None
                    paired = True
            elif not paired:
                raise ValueError('Drawing requires original Process calls')
            elif pending is not None:
                raise ValueError('Drawing requires a complete Process pair')
    if pending is not None:
        raise ValueError('Incomplete original Process pair')


def native_args(args):
    return [*owned.native_args(args), '--two-processes']


def compare(args, commands, expected, pilot, diagnostic_prefix=None):
    proc = subprocess.run(native_args(args), input='\n'.join(commands) + '\n', text=True, capture_output=True)
    if diagnostic_prefix is not None:
        diagnostic_prefix.parent.mkdir(parents=True, exist_ok=True)
        diagnostic_prefix.with_suffix('.stdout').write_text(proc.stdout)
        diagnostic_prefix.with_suffix('.stderr').write_text(proc.stderr)
    if proc.returncode:
        raise RuntimeError('Native owned Processes at command ' + str(len(proc.stdout.splitlines())) + ': ' + proc.stderr.strip())
    lines = proc.stdout.splitlines()
    if len(lines) != len(commands):
        raise AssertionError('Owned Processes result counts differ')
    counts = {'selected_ordered_stores': 0, 'logged_queries': 0, 'decisions_and_failed_routes': 0}
    for index, (command, line, result) in enumerate(zip(commands, lines, expected)):
        op, values = parse(command)
        words = line.split()
        if op in ('I', 'J', 'T'):
            marker = words.index('actor-state')
            if words[marker:] != result['state']:
                raise AssertionError(('Owned Process state differs', index, command[:120]))
            if op == 'T':
                actual = native_events(words[:marker], values[0])
                if actual != result['events']:
                    at = next((i for i, (a, b) in enumerate(zip(actual, result['events'])) if a != b), min(len(actual), len(result['events'])))
                    raise AssertionError(('Owned Process ordering differs', index, command[:120], at,
                                          actual[max(0, at-3):at+6], result['events'][max(0, at-3):at+6]))
                if sum(e[0] == 'R' for e in actual) != 1 or actual[-1][0] != 'R':
                    raise AssertionError('One terminal Process return must be compared')
                counts['selected_ordered_stores'] += sum(e[0] in ('w', 'A', 'L') for e in actual)
                counts['logged_queries'] += sum(e[0] == 'Q' for e in actual)
                counts['decisions_and_failed_routes'] += sum(e[0] in ('D', 'G', 'B') for e in actual)
        elif words != result['tokens']:
            raise AssertionError(('Owned Process complete drawing/preparation differs', index, command[:120]))
    match = re.fullmatch(r'Owned two-Process guards: (\d+); unknown actor: (\d+); warm clone pairs: (\d+); actual Advance6/7 clone refusals: (\d+): PASS\n', proc.stderr)
    if match is None:
        raise AssertionError('Native owned Process guard evidence missing: ' + proc.stderr)
    guards, unknown, clones, refusals = map(int, match.groups())
    initializations = sum(c.startswith('I ') for c in commands)
    if guards != initializations * 6 or unknown != initializations or (not pilot and (clones < 4 or refusals != 2)):
        raise AssertionError(('Native ownership checks not entered', guards, unknown, clones, refusals))
    return {**counts, 'constructor_refusals': guards, 'unknown_actor_refusals': unknown,
            'warm_clone_step_pairs': clones, 'native_Advance6_and_7_clone_refusals': refusals}


def generate(args, progress):
    commands, expected, labels, samples = [], [], [], []
    progress.update(commands=commands, expected=expected, labels=labels, draw_samples=samples,
                    stage='original_setup')
    from original_owned_unit_processes import OwnedUnitProcessesOracle, ACTORS, DRIVES
    from original_map_preparation import SLOTS
    from original_foot_lit import ints, words
    from verify_ground_drive_stores import STORE_SITES

    oracle = OwnedUnitProcessesOracle(args.exe, args.assets, args.palette.read_bytes())
    movement = oracle.movement
    source = json.loads(args.depth_fixture.read_text())
    template, _ = owned.shared.prepared.parse(source['commands'][3])
    common = list(template[5])
    common[:5] = [12, 12, 0, -1, 0]
    common[27:42] = [-1] * 15
    common[50:61] = [1065353216] * 11
    cases = [
        ('actor0_follows_turning_actor1', (2944,3200,0), (3968,3200,0), 16384, (2,2,2,2,-1,4,5), (3200,3200,0), 0, (4224,3200,0), (2,2,2,2,-1,7,6), 64, 0),
        ('actor1_follows_turning_actor0', (3200,3200,0), (4224,3200,0), 0, (2,2,2,2,-1,4,5), (2944,3200,0), 16384, (3968,3200,0), (2,2,2,2,-1,7,6), 64, 0),
        ('actor1_curve_Advance2', (3456,3712,0), (4480,3712,0), 49152, (2,2,2,2,-1,4,5), (2944,3200,0), 16384, (3968,3968,0), (2,3,4,4,-1,7,6), 96, 0),
        ('actor0_curve_Advance2', (2944,3200,0), (3968,3968,0), 16384, (2,3,4,4,-1,5,6), (3456,3712,0), 49152, (4480,3712,0), (2,2,2,2,-1,7,6), 96, 0),
        ('both_actors_ramp_entry_exit', (2944,3200,0), (3968,3200,0), 16384, (2,2,2,2,-1,4,5), (2944,3712,0), 16384, (3968,3712,0), (2,2,2,2,-1,7,6), 96, 1),
        ('actor0_first_stationary6', (2944,3200,0), (3968,3200,0), 16384, (2,-1,4,5), (3200,3200,0), 0, (0,0,0), (), 8, 0),
        ('actor0_second_stationary6', (2944,3200,0), (3968,3200,0), 16384, (2,3,-1,4,5), (3456,3456,0), 0, (0,0,0), (), 8, 0),
        ('actor1_first_stationary6', (3200,3200,0), (0,0,0), 0, (), (2944,3200,0), 16384, (3968,3200,0), (2,-1,7,6), 8, 0),
        ('actor1_second_stationary6', (3456,3456,0), (0,0,0), 0, (), (2944,3200,0), 16384, (3968,3200,0), (2,3,-1,7,6), 8, 0),
    ]
    if args.pilot:
        cases = [(*cases[0][:-2], 8, 0)]
    draws = 0

    def record(command, result, label):
        parse(command)
        commands.append(command)
        expected.append(result)
        labels.append(label)

    for name, at, destination, heading, route, other_at, other_heading, dest1, route1, steps, ramp in cases:
        progress.update(stage='original_scenario', case=name)
        types = [[1,1,1,60,30,1,0,0,0,0,0], [1,1,1,60,30,1,0,ramp,0,0,0]]
        cells = [[x,y,int(x==12),0,0,0,-1,0,0,0,0,0,17,91,-1,41,0] for y in range(25) for x in range(25) if x+y>12 and abs(x-y)<12 and x+y<=36]
        fixture = (*template[:5], common, [12,0,0,12,12], types, cells, [], [], template[11], [])
        prepared = oracle.prepare_map(fixture)
        record('P '+owned.shared.floor.command(*fixture[:5], fixture[5:]), {'tokens': list(map(str, prepared))}, name)
        record('O 0 0', {'tokens': ['reset']}, name)
        init = owned.resident.command(at=at, destination=destination, heading=heading, route=route,
                                      parked_at=other_at, parked_heading=other_heading,
                                      steps=1, mode=0, marked=0, effect=1, present=1, key=0)
        _, values = owned.resident.parse(init)
        head, queue, numeric, crusher, parked, parked_heading, first, second, order = values
        oracle.initialize(head, queue, numeric, parked, parked_heading, [8192,40960])
        movement.put(0x1c01000+0x13d0, 8)
        record('I '+init[2:]+' 8192 40960', {'state': list(map(str, oracle.process_snapshot()))}, name)
        queue1 = [*route1, *([-1]*(24-len(route1)))]
        movement.u.mem_write(ACTORS[1]+0x4d0, struct.pack('<24i', *queue1))
        movement.u.mem_write(DRIVES[1]+0x34, struct.pack('<3i', *dest1))
        movement.u.mem_write(ACTORS[1]+0x530, struct.pack('<3i', -1,-17,0))
        record('J '+' '.join(map(str, [*dest1,*queue1,-1,-17,0])), {'state': list(map(str, oracle.process_snapshot()))}, name)
        lag_draws = 0
        for tick in range(100,100+steps):
            for actor in (0,1):
                progress.update(tick=tick, actor=actor)
                events = movement.advance_actor(actor,tick)
                record(f'T {actor} {tick}', {'events': original_events(events), 'state': list(map(str, oracle.process_snapshot()))}, name)
            lagged = False
            for actor, drive in zip(ACTORS,DRIVES):
                x,y,z = ints(movement.u,actor+0x88,3)
                cell = words(movement.u,SLOTS+((y//256)*512+x//256)*4,1)[0]
                lagged |= words(movement.u,drive+0x1c,1)[0] != movement.u.mem_read(cell+0x11c,1)[0]
            if tick in (100,101,116,132,148,100+steps-1) or (lagged and lag_draws<2):
                if lagged:
                    lag_draws += 1
                for actor in (0,1,0):
                    values = [owned.shared.floor.bits(.125),0,0,0,1,0,7,1,0,1312,1,0,0,80+actor*5,72,0,0,160,144]
                    before = len(oracle.relative_heights)
                    result = oracle.draw_shared(actor,tick,values)
                    draws += 1
                    x,y,z = ints(movement.u,ACTORS[actor]+0x88,3)
                    cell = words(movement.u,SLOTS+((y//256)*512+x//256)*4,1)[0]
                    samples.append({'case': name, 'actor': actor, 'tick': tick,
                        'stored_ramp': words(movement.u,DRIVES[actor]+0x1c,1)[0],
                        'Cell_ramp': movement.u.mem_read(cell+0x11c,1)[0],
                        'relative_heights': oracle.relative_heights[before:]})
                    record('D '+' '.join(map(str,[actor,*values])), {'tokens': list(map(str,[*result,*oracle.process_snapshot()]))}, name)
            if tick%16==4:
                print(name,tick,dict(movement.process_counts),flush=True)
        print(name,'complete',draws,'draws',flush=True)
    coverage = {}
    for actor in (0,1):
        selected = [s for s in samples if s['actor']==actor and s['case']=='both_actors_ramp_entry_exit']
        coverage[actor] = {'lagged': sum(s['stored_ramp']!=s['Cell_ramp'] for s in selected),
                           'positive': sum(any(h>0 for h in s['relative_heights']) for s in selected),
                           'negative': sum(any(h<0 for h in s['relative_heights']) for s in selected)}
    assert dict(movement.root_entries) == dict(movement.process_counts)
    assert sum(movement.process_counts.values()) == sum(c.startswith('T ') for c in commands)
    assert oracle.shared_calls == draws and oracle.selected_writes == draws*8
    if not args.pilot:
        assert all(all(c.values()) for c in coverage.values()), coverage
        assert all(any(a==actor and caller==0x4a1c9f and result==2 for a,caller,result in movement.admissions) for actor in (0,1)), movement.admissions
        for actor in (0,1):
            for caller, result in ((0x4a34f1,2),(0x4a34f1,6),(0x4a40ea,6)):
                assert movement.admissions[(actor,caller,result)] > 0, (actor,hex(caller),result)
            assert movement.wait_stores[actor] > 0, (actor,'wait stores')
            assert all(movement.path_options[(actor,option)] > 0 for option in (1,2)), (actor,'failed route options')
        assert set(movement.drive_store_sites)==set(map(hex,STORE_SITES)), movement.drive_store_sites
    return commands, expected, labels, {
        'process_counts': dict(movement.process_counts), 'actual_Process_entries': dict(movement.root_entries),
        'actual_admissions': [[actor,hex(caller),result,count] for (actor,caller,result),count in sorted(movement.admissions.items())],
        'actual_wait_stores': dict(movement.wait_stores),
        'actual_failed_route_options': [[actor,option,count] for (actor,option),count in sorted(movement.path_options.items())],
        'selected_Advance_store_sites': dict(movement.drive_store_sites), 'draws': draws, 'draw_samples': samples,
        'actual_shared_draw_entries': oracle.shared_calls, 'selected_draw_stores': oracle.selected_writes,
        'nonflat_coverage': coverage, 'actual_instructions': len(movement.instructions),
        'distinct_original_Process_records_shared_owned_world': True,
        'selected_stores_and_all_logged_queries_compared': True, 'all_machine_stores_compared': False,
        'initial_snapshots_compared_initial_order_retains_legacy_proof': True,
        'initial_records_padding_and_named_services_supplied': True, 'runtime_unwired': True, 'pilot': args.pilot}


def main():
    args = owned.shared.arguments(original_cache=True)
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/native/owned-unit-world-vectors'
    if args.output == ROOT/'private/unit-draw-1006/shared-ground-world-v1':
        args.output = ROOT/'private/unit-draw-1006/owned-unit-processes-v1'
    start = time.monotonic()
    current = identities(args)
    runner = hash_file(args.native)
    reuse = OriginalResults(args, current, __file__)
    if args.expectations:
        source = private_path(args.expectations,args.exe)
        receipt = source.parent/'report.json'
        fingerprint = hash_file(source)
        envelope = json.loads(source.read_text())
        reuse.validate(validate,envelope,json.loads(receipt.read_text()),fingerprint,current)
        report = private_path(args.report or source.parent/'replay.json',args.exe)
        check_replay_destination(report,source,receipt)
        commands, expected, labels = [envelope[key] for key in ('commands','expected','labels')]
        metadata = envelope['evidence']
        generation = 0
    else:
        dest = private_path(args.output,args.exe)
        if args.report or (dest/'expected.json').exists() or (dest/'report.json').exists():
            raise ValueError('Fresh owned Processes output invalid or exists')
        now = time.monotonic()
        progress = {}
        try:
            commands, expected, labels, metadata = generate(args, progress)
        except BaseException as failure:
            diagnostic = dest/'original-partial-diagnostic.json'
            diagnostic.parent.mkdir(parents=True, exist_ok=True)
            with diagnostic.open('x') as stream:
                json.dump({**progress, 'accepted_proof': False,
                           'error': type(failure).__name__+': '+str(failure),
                           'identities': current, 'native_sha256': runner}, stream, indent=2)
                stream.write('\n')
            raise
        generation = time.monotonic()-now
        report = dest/'report.json'
    if not args.expectations:
        diagnostic = dest/'original-diagnostic.json'
        diagnostic.parent.mkdir(parents=True, exist_ok=True)
        with diagnostic.open('x') as stream:
            json.dump({'stage': 'original_complete_native_not_compared', 'accepted_proof': False,
                       'commands': commands, 'expected': expected, 'labels': labels,
                       'metadata': metadata, 'identities': current, 'native_sha256': runner}, stream, indent=2)
            stream.write('\n')
    now = time.monotonic()
    checks = compare(args,commands,expected,metadata['pilot'],report.with_name(report.stem+'-native-output'))
    comparison = time.monotonic()-now
    if identities(args)!=current or hash_file(args.native)!=runner:
        raise ValueError('Owned Processes sources/inputs/runner changed during invocation')
    result = {**metadata, **checks, 'identities': current, 'native_sha256': runner,
        'executable_sha256': PATCHED_EXPECTED, 'profile': 'supplied-ra2-1006', 'cases': len(commands),
        'evidence_mode': 'cached-original-replay' if args.expectations else 'fresh-original',
        'original_instructions_executed': not bool(args.expectations), 'original_instructions_modified': False,
        'original_generation_seconds': generation, 'native_comparison_seconds': comparison,
        'elapsed_seconds': time.monotonic()-start}
    reuse.annotate(result)
    if not args.expectations:
        source = dest/'expected.json'
        write_report(args.exe,source,{'executable_sha256': PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                                    'commands': commands,'expected': expected,'labels': labels,'evidence': result})
        fingerprint = hash_file(source)
    result['expectations_sha256'] = fingerprint
    write_report(args.exe,report,result)
    reuse.finish(source, report, validate)
    print(f'{len(commands)} owned Processes results / {metadata["draws"]} complete draws: PASS ({result["evidence_mode"]})')


if __name__ == '__main__':
    main()
