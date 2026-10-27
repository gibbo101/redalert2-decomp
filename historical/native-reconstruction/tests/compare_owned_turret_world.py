#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Independent turret commands on actual shared Process/drawing actors."""
import copy
import json
import re
import struct
import subprocess
import time
from collections import Counter
import compare_owned_command_world as command_world
import compare_owned_unit_processes as processes
from compare_original import PATCHED_EXPECTED, write_report
from owned_process_events import original as original_events
from presentation_evidence import ROOT, private_path, hash_file, validate_receipt, check_replay_destination
from verify_owned_turret_world import verify

SCHEDULE = ROOT/'private/unit-draw-1006/owned-unit-processes-v3/expected.json'
SOURCES = (*command_world.SOURCES, 'tools/verify_owned_turret_world.py',
           'tests/original_owned_turret_world.py', 'tests/owned_turret_world_vectors.cpp',
           'tests/owned_turret_world/CMakeLists.txt', 'tests/compare_owned_turret_world.py',
           'tests/test_owned_turret_world_evidence.py')


def parse(command):
    words = command.split()
    if words and words[0] in ('V', 'U'):
        values = list(map(int, words[1:]))
        if (len(values) == (3 if words[0] == 'V' else 7) and values[0] in (0, 1) and
                all(-2147483648 <= n <= 2147483647 for n in values) and
                (words[0] == 'V' or (values[2] in (0, 1) and values[3] in (0, 1, 2)))):
            return words[0], values
        raise ValueError('Malformed turret command')
    return command_world.parse(command)


def identities(args):
    return {'world': command_world.identities(args), 'turret': verify(args.exe.read_bytes()),
            'input_schedule_sha256': hash_file(SCHEDULE),
            'sources': {name: hash_file(ROOT/name) for name in SOURCES}}


def validate(evidence, receipt, fingerprint, current):
    validate_receipt(evidence, receipt, fingerprint)
    if not evidence['evidence'].get('independent_turret_commands_on_actual_actors'):
        raise ValueError('Independent original turret proof required')
    if not evidence['evidence'].get('original_parent_turning_flag_compared'):
        raise ValueError('Original parent turning flag proof required')
    if not (evidence.get('commands') and len(evidence['commands']) == len(evidence.get('expected', [])) == len(evidence.get('labels', []))):
        raise ValueError('Turret evidence counts differ')
    legacy = copy.deepcopy(evidence)
    rows = []
    joined = False
    commands_seen = set()
    for command, result, label in zip(evidence['commands'], evidence['expected'], evidence['labels']):
        op, values = parse(command)
        if op == 'P': joined = False
        if op == 'J': joined = True
        if op in ('V', 'U'):
            if not joined or not isinstance(result, dict) or set(result) != {'state'}:
                raise ValueError('Turret command requires joined actors and state')
            commands_seen.add((values[0], op))
        else:
            rows.append((command, result, label))
    if not rows:
        raise ValueError('Original Process/drawing evidence required')
    if commands_seen != {(id, op) for id in (0, 1) for op in ('V', 'U')}:
        raise ValueError('Both independent turret command/update streams required')
    legacy['commands'], legacy['expected'], legacy['labels'] = map(list, zip(*rows))
    command_world.validate(legacy, receipt, fingerprint, current)


def compare(args, commands, expected, diagnostic):
    proc = subprocess.run(command_world.native_args(args), input='\n'.join(commands)+'\n',
                          text=True, capture_output=True)
    diagnostic.parent.mkdir(parents=True, exist_ok=True)
    diagnostic.with_suffix('.stdout').write_text(proc.stdout)
    diagnostic.with_suffix('.stderr').write_text(proc.stderr)
    if proc.returncode:
        raise RuntimeError('Native turret world after '+str(len(proc.stdout.splitlines()))+' rows: '+proc.stderr)
    rows = proc.stdout.splitlines()
    if len(rows) != len(commands):
        raise AssertionError('Turret world result count differs')
    guards = re.fullmatch(r'Owned world guards: (\d+); unknown actor: (\d+); warm clone pairs: (\d+); actual Advance6/7 clone refusals: (\d+): PASS\n', proc.stderr)
    if guards is None or tuple(map(int, guards.groups()[:2])) != (6*sum(c.startswith('I ') for c in commands), sum(c.startswith('I ') for c in commands)):
        raise AssertionError('Turret world native ownership checks missing: '+proc.stderr)
    counts = Counter()
    for index, (command, row, result) in enumerate(zip(commands, rows, expected)):
        op, values = parse(command)
        words = row.split()
        if op in ('I', 'J', 'T', 'V', 'U'):
            at = words.index('actor-state')
            if words[at:] != result['state']:
                original = result['state']
                offset = next((n for n, (a, b) in enumerate(zip(words[at:], original)) if a != b), min(len(words)-at, len(original)))
                raise AssertionError(('Turret world state differs', index, command, offset,
                                      words[at+max(0,offset-3):at+offset+8], original[max(0,offset-3):offset+8]))
            if op == 'T':
                events = processes.native_events(words[:at], values[0])
                if events != result['events']:
                    raise AssertionError(('Turret world Process events differ', index, command))
                counts['selected_Process_stores'] += sum(e[0] in ('w','A','L') for e in events)
                counts['logged_queries'] += sum(e[0] == 'Q' for e in events)
                counts['Process_calls'] += 1
        elif words != result['tokens']:
            raise AssertionError(('Turret world complete draw/preparation differs', index, command[:80]))
        counts[op] += 1
    return dict(counts)


def generate(args, progress):
    from original_owned_turret_world import OwnedTurretWorldOracle, ACTORS, DRIVES
    oracle = OwnedTurretWorldOracle(args.exe, args.assets, args.palette.read_bytes())
    movement = oracle.movement
    source = json.loads(SCHEDULE.read_text())
    chosen = ('actor0_follows_turning_actor1', 'actor1_follows_turning_actor0', 'both_actors_ramp_entry_exit')
    if args.pilot: chosen = chosen[:1]
    commands, expected, labels = [], [], []
    progress.update(commands=commands, expected=expected, labels=labels)
    tick = schedule_tick = 100
    counts = Counter()

    def record(command, result, label):
        parse(command)
        commands.append(command); expected.append(result); labels.append(label)

    def state():
        return list(map(str, [*oracle.process_snapshot(), *oracle.turret_views(tick)]))

    def turret(command, label):
        op, v = parse(command)
        if op == 'V': oracle.command_turret(*v)
        else: oracle.update_turret(*v[:4], v[4:])
        counts[(v[0],op)] += 1
        record(command, {'state': state()}, label)

    for command, label in zip(source['commands'], source['labels']):
        if label not in chosen: continue
        op, v = processes.parse(command)
        if op == 'P': schedule_tick = 100
        if op == 'T': schedule_tick = v[1]
        if op in ('T', 'D') and schedule_tick > 163: continue
        progress.update(case=label, command=command[:80])
        if op == 'P':
            tick = 100
            record(command, {'tokens': list(map(str, oracle.prepare_map(v)))}, label)
        elif op == 'O':
            record(command, {'tokens': ['reset']}, label)
        elif op == 'I':
            head, queue, numeric, crusher, parked, heading, first, second, order, turrets = v
            oracle.initialize(head, queue, numeric, parked, heading, turrets)
            movement.put(0x1c01000+0x13d0, 8)
            record(command, {'state': state()}, label)
        elif op == 'J':
            movement.u.mem_write(DRIVES[1]+0x34, struct.pack('<3i', *v[:3]))
            movement.u.mem_write(ACTORS[1]+0x4d0, struct.pack('<24i', *v[3:27]))
            movement.u.mem_write(ACTORS[1]+0x530, struct.pack('<3i', *v[27:]))
            record(command, {'state': state()}, label)
        elif op == 'T':
            actor, tick = v
            events = movement.advance_actor(actor, tick)
            record(command, {'events': original_events(events), 'state': state()}, label)
            if actor == 1:
                if tick in (101, 102, 104, 115, 121):
                    for id, delta in ((0, {101:32768,102:0,104:-8192,115:1,121:-65537}[tick]),
                                      (1, {101:-65537,102:65536,104:16384,115:-32768,121:32767}[tick])):
                        turret(f'V {id} {tick} {delta}', label)
                for id in (0, 1):
                    manual = int(101 <= tick < (108 if id == 0 else 112))
                    target = (1 if id == 0 else 2) if tick < 121 else 0
                    turret(f'U {id} {tick} {manual} {target} {2688+(tick%4)*1024} {4224-(tick%3)*256} 0', label)
                if tick%8 == 4: print(label, tick, 'turrets', dict(counts), flush=True)
        elif op == 'D':
            id, *values = v
            result = oracle.draw_shared(id, tick, values)
            record(command, {'tokens': list(map(str, [*result, *oracle.process_snapshot(), *oracle.turret_views(tick)]))}, label)
    if not args.pilot:
        for id in (0, 1):
            for branch in ('busy', 'body', 'destination', 'manual-supplied-root-skip'):
                assert oracle.turret_counts[(id, branch)] > 0, (id, branch)
    return commands, expected, labels, {
        'stable_command_world_owner': True, 'independent_turret_commands_on_actual_actors': True,
        'original_parent_turning_flag_compared': True,
        'distinct_original_Process_records_shared_owned_world': True,
        'selected_stores_and_all_logged_queries_compared': True,
        'turret_counts': [[id, name, n] for (id,name),n in sorted(oracle.turret_counts.items())],
        'original_turret_stores': oracle.turret_stores,
        'actual_turret_instruction_count': len(oracle.turret_instructions),
        'process_counts': dict(movement.process_counts), 'actual_Process_entries': dict(movement.root_entries),
        'draws': oracle.shared_calls, 'selected_draw_stores': oracle.selected_writes,
        'manual_override_target_lifetime_weapon_services_and_padding_supplied': True,
        'runtime_unwired': True, 'pilot': args.pilot}


def main():
    args = processes.owned.shared.arguments()
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/owned-turret-world/owned-turret-world-vectors'
    if args.output == ROOT/'private/unit-draw-1006/shared-ground-world-v1':
        args.output = ROOT/'private/unit-draw-1006/owned-turret-world-v1'
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
            raise ValueError('Fresh turret destination invalid or exists')
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
        raise ValueError('Turret sources/inputs/runner changed during invocation')
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
    print(f'{len(commands)} shared turret results / {metadata["draws"]} complete draws: PASS')


if __name__ == '__main__': main()
