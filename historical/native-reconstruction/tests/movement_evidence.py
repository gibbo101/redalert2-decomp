# SPDX-License-Identifier: GPL-3.0-or-later
"""Private evidence and explicit retained native table inputs during migration."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
from compare_original import EXPECTED, PATCHED_EXPECTED, write_report
from movement_profiles import movement_profile

ROOT = Path(__file__).resolve().parents[1]
SOURCES = ('original_movement.py', 'original_curves.py', 'movement_profiles.py',
           'movement_evidence.py', 'compare_movement.py', 'compare_curves.py',
           'compare_timing_targeting.py')
sys.path.insert(0, str(ROOT/'tools'))
from verify_movement_mapping import verify


def hash_file(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def source_identities(args):
    result = {'oracle_sources': {name: hash_file(ROOT/'tests'/name) for name in SOURCES},
              'mapping_tool_sha256': hash_file(ROOT/'tools/verify_movement_mapping.py')}
    if hasattr(args, 'direction_data'):
        result['direction_data_sha256'] = hash_file(args.direction_data)
    return result


def prepare(args, suite):
    digest, profile = movement_profile(args.exe.read_bytes(), allow_patched=True)
    native_data = args.native_data_exe or args.exe
    if hash_file(native_data) != EXPECTED:
        raise ValueError('Native vectors still require the verified disc data; use --native-data-exe explicitly for patched research')
    if digest == PATCHED_EXPECTED:
        # Fresh mapping/data check, not cached expectations or assumed equality.
        verify(native_data.read_bytes(), args.exe.read_bytes())
    args.research_identities = source_identities(args)
    output = ROOT/'private'/'migration'/profile/suite
    return digest, profile, native_data, output


def identities(args, digest, profile, native_data):
    current = source_identities(args)
    if current != args.research_identities:
        raise ValueError('Oracle sources/prepared inputs changed during this run; preserve earlier evidence and rerun')
    if hash_file(args.exe) != digest or hash_file(native_data) != EXPECTED:
        raise ValueError('Executable inputs changed during this run')
    return {'executable_sha256': digest, 'profile': profile,
            'native_data_executable_sha256': hash_file(native_data),
            'native_sha256': hash_file(args.native), **current,
            'audit_scope': 'Root return address, caller-owned stack after consumed arguments, ESP/callee-saved registers, fixture edge canaries and original read-only image stores; full actor arenas and ordered native/original writes are not compared',
            'runtime_profile_promoted': False}


def save(args, digest, profile, output, expectations, report):
    report['evidence_mode'] = 'fresh-original'
    report['original_instructions_executed'] = True
    evidence = {'executable_sha256': digest, 'profile': profile,
                **expectations, 'evidence': report}
    expected_path = output/'expected.json'
    if args.report and args.report.resolve() == expected_path.resolve():
        raise ValueError('Report cannot replace original expectations')
    write_report(args.exe, expected_path, evidence)
    report['expectations_sha256'] = hash_file(expected_path)
    write_report(args.exe, output/'report.json', report)
    if args.report and args.report.resolve() != (output/'report.json').resolve():
        write_report(args.exe, args.report, report)


def validate_cached(evidence, current):
    for field in ('executable_sha256', 'profile', 'native_data_executable_sha256',
                  'oracle_sources', 'mapping_tool_sha256', 'direction_data_sha256'):
        if evidence['evidence'].get(field) != current.get(field):
            raise ValueError('Cached original evidence identity differs: '+field)
    if evidence.get('executable_sha256') != current['executable_sha256'] or evidence.get('profile') != current['profile']:
        raise ValueError('Cached original envelope identity differs')


def validate_receipt(evidence, receipt, expectations_sha256):
    if receipt.get('evidence_mode') != 'fresh-original' or receipt.get('expectations_sha256') != expectations_sha256:
        raise ValueError('Cached original expectation fingerprint differs from fresh receipt')
    if {k: v for k, v in receipt.items() if k != 'expectations_sha256'} != evidence['evidence']:
        raise ValueError('Cached original evidence differs from fresh receipt')


def check_replay_destination(destination, expectations, receipt):
    destination = destination.resolve()
    if destination in (expectations.resolve(), receipt.resolve()):
        raise ValueError('Replay report cannot replace original expectations or fresh receipt')
    if destination.exists():
        prior = json.loads(destination.read_text())
        if prior.get('evidence_mode') == 'fresh-original' or 'commands' in prior:
            raise ValueError('Replay report cannot replace fresh original evidence')


def replay(args, digest, profile, native_data, output, suite):
    source = args.expectations.absolute()
    if any(p.is_symlink() for p in (source, *source.parents)):
        raise ValueError('Symlink expectation paths are refused')
    source = source.resolve(strict=True)
    if not any(source.is_relative_to(ROOT/name) for name in ('private', 'build')):
        raise ValueError('Original expectations must stay private')
    evidence = json.loads(source.read_text())
    receipt_path = source.parent/'report.json'
    if receipt_path.is_symlink():
        raise ValueError('Symlink original receipts are refused')
    validate_receipt(evidence, json.loads(receipt_path.read_text()), hash_file(source))
    destination = args.report or output/'replay-report.json'
    check_replay_destination(destination, source, receipt_path)
    current = identities(args, digest, profile, native_data)
    validate_cached(evidence, current)
    values = evidence.get('values', evidence.get('expected'))
    commands = evidence['commands']
    arguments = [str(args.native), str(native_data)]
    if suite == 'timing-targeting':
        arguments.append(str(args.direction_data))
    proc = subprocess.run(arguments, input='\n'.join(commands)+'\n', text=True, capture_output=True, check=True)
    current = identities(args, digest, profile, native_data)
    actual = [[int(n) for n in line.split()] for line in proc.stdout.splitlines()]
    if actual != values:
        mismatch = next((i for i, pair in enumerate(zip(actual, values)) if pair[0] != pair[1]), min(len(actual), len(values)))
        raise AssertionError(f'Cached original/native comparison differs at result {mismatch}')
    report = {**evidence['evidence'], **current, 'evidence_mode': 'cached-original-replay',
              'original_instructions_executed': False, 'expectations_sha256': hash_file(source),
              'comparisons': len(actual), 'matched': len(actual)}
    write_report(args.exe, destination, report)
    print(f'{len(actual):,} identity-checked {profile} {suite} expectations: PASS (native replay; no original execution)')
