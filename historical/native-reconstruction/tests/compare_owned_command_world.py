#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Fresh distinct-address Process/drawing proof through the stable command owner.

The original protocol/oracle is deliberately unchanged. Host clone/preview checks
are additional native evidence, not new original command or scheduler behavior.
"""
import json
import re
import subprocess
import time
import compare_owned_unit_processes as processes
import compare_owned_unit_world as owned
from original_results import OriginalResults
from compare_original import PATCHED_EXPECTED, write_report
from owned_process_events import native as native_events
from presentation_evidence import ROOT, private_path, hash_file, check_replay_destination

SOURCES = (*processes.SOURCES, 'src/platform/OwnedUnitWorld.hpp',
    'tests/owned_command_world_vectors.cpp', 'tests/owned_command_world_check.cpp',
    'tests/owned_command_world/CMakeLists.txt', 'tests/compare_owned_command_world.py',
    'tests/test_owned_command_world_evidence.py')
parse = processes.parse


def identities(args):
    return {'processes': processes.identities(args),
            'sources': {name: hash_file(ROOT/name) for name in SOURCES}}


def validate(evidence, receipt, fingerprint, current):
    processes.validate(evidence, receipt, fingerprint, current)
    if not evidence['evidence'].get('stable_command_world_owner'):
        raise ValueError('Stable command world owner proof required')


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
    match = re.fullmatch(r'Owned world guards: (\d+); unknown actor: (\d+); warm clone pairs: (\d+); actual Advance6/7 clone refusals: (\d+): PASS\n', proc.stderr)
    if match is None:
        raise AssertionError('Native owned Process guard evidence missing: ' + proc.stderr)
    guards, unknown, clones, refusals = map(int, match.groups())
    initializations = sum(c.startswith('I ') for c in commands)
    if guards != initializations * 6 or unknown != initializations or (not pilot and (clones < 4 or refusals != 2)):
        raise AssertionError(('Native ownership checks not entered', guards, unknown, clones, refusals))
    return {**counts, 'constructor_refusals': guards, 'unknown_actor_refusals': unknown,
            'warm_clone_step_pairs': clones, 'native_Advance6_and_7_clone_refusals': refusals}


def generate(args, progress):
    commands, expected, labels, evidence = processes.generate(args, progress)
    return commands, expected, labels, {**evidence, 'stable_command_world_owner': True,
        'command_routing_turret_policy_and_preview_are_host_adapters': True,
        'SDL_routing_unchanged': True}


def main():
    args = owned.shared.arguments(original_cache=True)
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/owned-command-world/owned-command-world-vectors'
    if args.output == ROOT/'private/unit-draw-1006/shared-ground-world-v1':
        args.output = ROOT/'private/unit-draw-1006/owned-command-world-v1'
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
            raise ValueError('Fresh owned command world output invalid or exists')
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
        raise ValueError('Owned command world sources/inputs/runner changed during invocation')
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
    print(f'{len(commands)} owned command world results / {metadata["draws"]} complete draws: PASS ({result["evidence_mode"]})')


if __name__ == '__main__':
    main()
