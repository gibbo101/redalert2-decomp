#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Fresh distinct-address Process/drawing proof through the SDL-free runtime."""
import json
import time
import compare_owned_scheduled_preview as scheduled
from compare_owned_scheduled_preview import processes, parse, compare
from compare_original import PATCHED_EXPECTED, write_report
from presentation_evidence import ROOT, private_path, hash_file, validate_receipt, check_replay_destination

SOURCES = (*scheduled.SOURCES, 'src/platform/OwnedTerrainRuntime.hpp',
    'src/platform/OwnedSdlApp.hpp', 'src/platform/SDLApp.cpp',
    'src/render/Renderer.cpp', 'src/render/Renderer.hpp', 'src/render/OwnedUnitDrawFrame.hpp',
    'tests/owned_terrain_runtime_vectors.cpp', 'tests/owned_terrain_runtime_check.cpp',
    'tests/owned_terrain_runtime/CMakeLists.txt', 'tests/compare_owned_terrain_runtime.py',
    'tests/test_owned_terrain_runtime_evidence.py')

def identities(args):
    return {'scheduled': scheduled.identities(args),
            'sources': {name: hash_file(ROOT/name) for name in SOURCES}}

def generate(args, progress):
    commands, expected, labels, metadata = scheduled.generate(args, progress)
    return commands, expected, labels, {**metadata, 'runtime_unwired': False,
        'runtime_owned_world_and_tick': True,
        'explicit_authored_command_timestamps_not_original_UI': True}

def validate(evidence, receipt, fingerprint, current):
    scheduled.validate(evidence, receipt, fingerprint, current)
    if (not evidence['evidence'].get('runtime_owned_world_and_tick') or
            evidence['evidence'].get('runtime_unwired') is not False):
        raise ValueError('Owned runtime step proof required')

def main():
    args = processes.owned.shared.arguments()
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/owned-terrain-runtime/owned-terrain-runtime-vectors'
    if args.output == ROOT/'private/unit-draw-1006/shared-ground-world-v1':
        args.output = ROOT/'private/unit-draw-1006/owned-terrain-runtime-v1'
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
