#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete shared drawing with supplied targets on actual distinct actor fields.

This is a drawing/ownership proof. It runs no Process roots and supplies targets
as initial diagnostic records, not as evidence of original Scatter or movement.
"""
import json
import subprocess
import time
import compare_owned_terrain_runtime as runtime
from compare_original import PATCHED_EXPECTED, write_report
from presentation_evidence import (ROOT, private_path, hash_file, validate_receipt,
                                   check_replay_destination)

INPUTS = ROOT/'private/unit-draw-1006/owned-advance-runtime-pilot-v1/expected.json'
SOURCES = (*runtime.SOURCES, 'tests/compare_owned_target_drawing.py',
           'tests/test_owned_target_drawing.py', 'src/render/OwnedUnitDrawScene.hpp')


def parse(command):
    words = command.split()
    if words and words[0] == 'Y':
        if len(words) != 4:
            raise ValueError('Malformed supplied draw target')
        id, x, y = map(int, words[1:])
        if id not in (0, 1) or not ((x, y) == (-1, -1) or (0 <= x < 512 and 0 <= y < 512)):
            raise ValueError('Supplied draw target outside domain')
        return 'Y', (id, x, y)
    if not words or words[0] not in ('P', 'O', 'I', 'J', 'D'):
        raise ValueError('Draw-target fixture cannot run movement or commands')
    op, values = runtime.parse(command)
    if op == 'D' and values[2] != 0:
        raise ValueError('Actual-owner contact association must remain empty')
    return op, values


def identities(args):
    return {'runtime': runtime.identities(args), 'authored_inputs_sha256': hash_file(INPUTS),
            'sources': {name: hash_file(ROOT/name) for name in SOURCES}}


def validate(envelope, receipt, fingerprint, current):
    validate_receipt(envelope, receipt, fingerprint)
    if envelope.get('executable_sha256') != PATCHED_EXPECTED or envelope.get('profile') != 'supplied-ra2-1006':
        raise ValueError('Draw-target engine/profile differs')
    proof = envelope['evidence']
    if proof.get('identities') != current:
        raise ValueError('Draw-target identity differs')
    if not (proof.get('supplied_targets_on_actual_owners') and proof.get('targets_preserved_before_and_after_binding')
            and proof.get('actual_Process_roots') == 0):
        raise ValueError('Draw-target scope differs')
    commands = envelope.get('commands', [])
    if not commands or len(commands) != len(envelope.get('expected', [])) or len(commands) != len(envelope.get('labels', [])):
        raise ValueError('Draw-target counts differ')
    phase = 0
    targets = [(-1, -1), (-1, -1)]
    patterns = set()
    draws = [0, 0]
    for command, result in zip(commands, envelope['expected']):
        op, values = parse(command)
        if set(result) != {'tokens'}:
            raise ValueError('Malformed draw-target expectation')
        if op in ('P', 'O', 'I', 'J'):
            if phase >= 4 or op != ('P', 'O', 'I', 'J')[phase]:
                raise ValueError('One ordered actual-owner initialization required')
            phase += 1
        elif phase != 4:
            raise ValueError('Actual-owner initialization required before target/draw')
        elif op == 'Y':
            id, x, y = values
            targets[id] = (x, y)
        else:
            draws[values[0]] += 1
            patterns.add(tuple(p != (-1, -1) for p in targets))
        if phase >= 3:
            tail = [str(v) for id, p in enumerate(targets) for v in ('draw-target', id, *p)]
            if result['tokens'][-8:] != tail:
                raise ValueError('Actual target observations differ from supplied setup')
    if patterns != {(False, False), (True, False), (False, True), (True, True)} or min(draws) < 4:
        raise ValueError('Both actors and all target-presence combinations required')


def native_args(args):
    return [*runtime.processes.native_args(args), '--draw-targets']


def compare(args, commands, expected, diagnostic):
    proc = subprocess.run(native_args(args), input='\n'.join(commands)+'\n', text=True, capture_output=True)
    diagnostic.parent.mkdir(parents=True, exist_ok=True)
    diagnostic.with_suffix('.stdout').write_text(proc.stdout)
    diagnostic.with_suffix('.stderr').write_text(proc.stderr)
    if proc.returncode:
        raise RuntimeError(f'Draw-target native row {len(proc.stdout.splitlines())}: {proc.stderr}')
    rows = proc.stdout.splitlines()
    if len(rows) != len(commands):
        raise AssertionError('Draw-target result count differs')
    for index, (command, row, result) in enumerate(zip(commands, rows, expected)):
        op, _ = parse(command)
        wanted, actual = result['tokens'], row.split()
        if op in ('I', 'J', 'Y'):
            # Initialization emits its existing placement trace before the
            # snapshot. This proof compares initialized state; every complete
            # drawing token remains compared, with no prefix removal for D.
            actual = actual[actual.index('actor-state'):]
        if actual != wanted:
            at = next((i for i, (a, b) in enumerate(zip(actual, wanted)) if a != b), min(len(actual), len(wanted)))
            raise AssertionError(('Draw-target result', index, command[:100], at, actual[at:at+8], wanted[at:at+8]))
    if proc.stderr != 'Owned world guards: 6; unknown actor: 1; warm clone pairs: 0; actual Advance6/7 clone refusals: 0: PASS\n':
        raise AssertionError('Actual-owner native identity guards missing')
    return {'results': len(rows), 'complete_draws': sum(c.startswith('D ') for c in commands)}


def generate(args, progress):
    import struct
    from original_owned_orders_world import OwnedOrdersWorldOracle
    from original_owned_unit_processes import ACTORS, DRIVES
    from original_map_preparation import SLOTS
    oracle = OwnedOrdersWorldOracle(args.exe, args.assets, args.palette.read_bytes())
    m = oracle.movement
    source = json.loads(INPUTS.read_text())
    commands, expected, labels = [], [], []
    progress.update(commands=commands, expected=expected, labels=labels)
    tick = 100

    def targets():
        return [v for id, actor in enumerate(ACTORS) for v in
                ('draw-target', id, *(struct.unpack('<2h', m.u.mem_read(m.get(actor+0x494)+0x24, 4))
                                      if m.get(actor+0x494) else (-1, -1)))]

    def state():
        return [*oracle.process_snapshot(), *oracle.turret_views(tick), *oracle.command_views(), *targets()]

    def record(command):
        op, values = parse(command)
        progress['command'] = command[:100]
        if op == 'P':
            result = oracle.prepare_map(values)
        elif op == 'O':
            result = ['reset']
        elif op == 'I':
            head, queue, numeric, crusher, parked, heading, first, second, order, turrets = values
            oracle.initialize(head, queue, numeric, parked, heading, turrets)
            m.put(0x1c01000+0x13d0, 8)
            result = state()
        elif op == 'J':
            m.u.mem_write(DRIVES[1]+0x34, struct.pack('<3i', *values[:3]))
            m.u.mem_write(ACTORS[1]+0x4d0, struct.pack('<24i', *values[3:27]))
            m.u.mem_write(ACTORS[1]+0x530, struct.pack('<3i', *values[27:]))
            result = state()
        elif op == 'Y':
            id, x, y = values
            p = 0 if (x, y) == (-1, -1) else m.get(SLOTS+(y*512+x)*4)
            assert (x, y) == (-1, -1) or p != 0
            m.put(ACTORS[id]+0x494, p)  # Explicit supplied initial-state boundary.
            result = state()
        else:
            id, *draw = values
            before = targets()
            result = [*oracle.draw_shared(id, tick, draw), *state()]
            assert targets() == before
            if oracle.shared_calls % 8 == 0:
                print('Original target-preserving draws:', oracle.shared_calls, flush=True)
        commands.append(command)
        expected.append({'tokens': list(map(str, result))})
        labels.append('supplied-target-drawing-only')

    for command in source['commands'][:4]:
        record(command)  # Prior expectations/outputs are never consumed.
    sample = next(c for c in source['commands'] if c.startswith('D ')).split()
    for first, second in (((-1, -1), (-1, -1)), ((12, 12), (-1, -1)),
                          ((-1, -1), (13, 12)), ((12, 12), (13, 12)),
                          ((13, 12), (12, 12)), ((-1, -1), (-1, -1))):
        for id, point in enumerate((first, second)):
            record('Y '+' '.join(map(str, (id, *point))))
        for id in (0, 1, 0, 1):
            sample[1] = str(id)
            record(' '.join(sample))
    assert not m.process_counts
    return commands, expected, labels, {'supplied_targets_on_actual_owners': True,
        'targets_preserved_before_and_after_binding': True, 'actual_Process_roots': 0,
        'draws': oracle.shared_calls, 'empty_contacts_supplied': True,
        'not_original_Scatter_or_movement_or_whole_frame_proof': True}


def main():
    args = runtime.processes.owned.shared.arguments(original_cache=False)
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/owned-terrain-runtime/owned-terrain-runtime-vectors'
    if args.output == ROOT/'private/unit-draw-1006/shared-ground-world-v1':
        args.output = ROOT/'private/owned-target-drawing-20261017'
    start = time.monotonic()
    current, runner = identities(args), hash_file(args.native)
    if args.expectations:
        source = private_path(args.expectations, args.exe)
        receipt = source.parent/'report.json'
        fingerprint = hash_file(source)
        envelope = json.loads(source.read_text())
        validate(envelope, json.loads(receipt.read_text()), fingerprint, current)
        commands, expected, labels = [envelope[k] for k in ('commands', 'expected', 'labels')]
        metadata, generation = envelope['evidence'], 0
        report = private_path(args.report, args.exe)
        check_replay_destination(report, source, receipt)
    else:
        folder = private_path(args.output, args.exe)
        if args.report or (folder/'expected.json').exists() or (folder/'report.json').exists():
            raise ValueError('Fresh target-drawing destination invalid or exists')
        now, progress = time.monotonic(), {}
        try:
            commands, expected, labels, metadata = generate(args, progress)
        except BaseException as error:
            folder.mkdir(parents=True, exist_ok=True)
            write_report(args.exe, folder/'partial-diagnostic.json', {**progress, 'accepted_proof': False,
                         'error': repr(error), 'identities': current})
            raise
        generation, report = time.monotonic()-now, folder/'report.json'
        write_report(args.exe, folder/'original-diagnostic.json', {'commands': commands, 'expected': expected,
                     'labels': labels, 'metadata': metadata, 'accepted_proof': False, 'identities': current})
    now = time.monotonic()
    checks = compare(args, commands, expected, report.with_name(report.stem+'-native'))
    comparison = time.monotonic()-now
    if identities(args) != current or hash_file(args.native) != runner:
        raise ValueError('Target-drawing sources/inputs/runner changed during invocation')
    result = {**metadata, 'identities': current, 'native_sha256': runner, 'native_checks': checks,
              'executable_sha256': PATCHED_EXPECTED, 'profile': 'supplied-ra2-1006',
              'evidence_mode': 'cached-original-replay' if args.expectations else 'fresh-original',
              'original_instructions_executed': not bool(args.expectations), 'original_instructions_modified': False,
              'original_generation_seconds': generation, 'native_comparison_seconds': comparison,
              'elapsed_seconds': time.monotonic()-start}
    if not args.expectations:
        source = folder/'expected.json'
        write_report(args.exe, source, {'executable_sha256': PATCHED_EXPECTED, 'profile': 'supplied-ra2-1006',
                     'commands': commands, 'expected': expected, 'labels': labels, 'evidence': result})
        fingerprint = hash_file(source)
        validate(json.loads(source.read_text()), {**result, 'expectations_sha256': fingerprint}, fingerprint, current)
    result['expectations_sha256'] = fingerprint
    write_report(args.exe, report, result)
    print(f'{checks["results"]} target-drawing results / {checks["complete_draws"]} complete draws: PASS')


if __name__ == '__main__':
    main()
