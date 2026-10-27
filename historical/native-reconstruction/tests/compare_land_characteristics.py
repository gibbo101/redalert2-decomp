#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete land assignment against supplied-1.006 original execution."""
import argparse
import configparser
import json
import random
import struct
import subprocess
import time
from pathlib import Path
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED, write_report
from presentation_evidence import private_path, hash_file, validate_receipt, check_replay_destination
from verify_land_characteristics import verify, SECTIONS, KEYS

SOURCES = ('src/assets/LandCharacteristics.hpp','src/assets/LandCharacteristics.cpp',
    'tests/land_characteristic_vectors.cpp','tests/compare_land_characteristics.py',
    'tests/original_land_characteristics.py','tools/verify_land_characteristics.py',
    'tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py',
    'tests/compare_original.py','tests/presentation_evidence.py','tests/compare_terrain_visibility.py',
    'tools/verify_terrain_visibility.py')

def identities(a):
    return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
            'owned_rules_sha256':hash_file(a.rules)}

def command(mode, rows):
    return 'L '+' '.join(map(str,[mode,*[v for row in rows for v in row]]))

def parse(cmd):
    parts = cmd.split()
    assert parts[0] == 'L'
    values = list(map(int,parts[1:]))
    assert len(values) == 301 and 0 <= values[0] <= 3
    rows = [values[i:i+25] for i in range(1,len(values),25)]
    for row in rows:
        assert all(0 <= n <= 0xffffffff for n in row[:10])
        assert 0 <= row[10] <= 255
        assert all(0 <= n <= 0xffffffffffffffff for n in row[11:])
    return values[0], rows

def validate(e, r, fingerprint, current):
    validate_receipt(e,r,fingerprint)
    if e.get('executable_sha256') != PATCHED_EXPECTED or e.get('profile') != 'supplied-ra2-1006':
        raise ValueError('Land engine/profile differs')
    if e['evidence'].get('identities') != current:
        raise ValueError('Land source/inspection/input identity differs')
    if not (e['commands'] and len(e['commands']) == len(e['expected']) == len(e['labels'])):
        raise ValueError('Land result counts differ')
    for cmd in e['commands']:
        try:
            parse(cmd)
        except (ValueError,AssertionError,IndexError):
            raise ValueError('Malformed land command') from None

def bits(value):
    return struct.unpack('<Q',struct.pack('<d',value))[0]

def generate(a):
    from original_land_characteristics import LandCharacteristicOracle
    oracle = LandCharacteristicOracle(a.exe)
    rng = random.Random(0x4c414e44)
    values = [0,0x8000000000000000,bits(0.005),bits(0.01),bits(0.02),bits(0.1),bits(0.7),
        bits(1.0)-1,bits(1.0),bits(1.0)+1,bits(-0.7),bits(-1.0),bits(1.5),bits(1e100),
        bits(-1e100),1,0x8000000000000001,bits(2**-149),bits(2**-126),bits(2**-150),
        bits(-2**-150),bits(float('inf')),bits(-float('inf')),0x7ff8000000000000,0xfff8000000000000]
    commands, expected, labels = [], [], []
    def add(label,mode,rows):
        cmd = command(mode,rows)
        commands.append(cmd)
        expected.append(oracle.run(*parse(cmd)))
        labels.append(label)
    for case in range(128):
        rows = []
        for s in range(12):
            row = [rng.choice([0,0,1,2,256,0xffffffff]),rng.choice([0,1,2,255,0x12345678]),
                   *[rng.getrandbits(32) for _ in range(8)],rng.randrange(256)]
            for _ in range(7):
                first = rng.choice(values)
                row.extend([first,first if case%3 else rng.choice(values)])
            rows.append(row)
        add('ordered_presence_duplicate_reads_clamp_float_store_and_supplied_initial_records',case%4,rows)
    for case in range(64):
        value = values[(case//4)%len(values)]
        rows = [[int(case%8 != 0),1,*[0xa5a5a5a5]*8,165,*([value,value]*7)] for _ in range(12)]
        add('all_rounding_modes_signed_zero_thresholds_subnormals_and_nonfinite',case%4,rows)
    ini = configparser.ConfigParser(interpolation=None,strict=False,allow_no_value=True,
                                    inline_comment_prefixes=(';',))
    ini.read_string(a.rules.read_text(encoding='latin1'))
    rows = []
    # Host-decoded INI values are service fixtures, not original parser evidence.
    for section in SECTIONS:
        text = ini.get(section,'Buildable',fallback='').strip().lower()
        row = [int(ini.has_section(section)),int(bool(text) and text[0] in '1ty'),*[0]*8,0]
        for key in (KEYS[i] for i in (3,0,1,2,5,6,7)):
            text = ini.get(section,key,fallback='1').strip()
            value = float(text[:-1])/100 if text.endswith('%') else float(text)
            row.extend([bits(value)]*2)
        rows.append(row)
    for mode in range(4):
        add('owned_rules_host_decoded_values_supplied_to_complete_parent',mode,rows)
    return commands,expected,labels,{'audited_roots':oracle.audit_calls,'actual_parent_entries':oracle.entries,
        'supplied_INI_calls':oracle.service_calls,'guest_table_stores':oracle.stores,
        'caller_rounding_modes':4,'INI_parser_and_initial_table_supplied':True,'original_instructions_modified':False}

def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/land-characteristic-vectors')
    p.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/map-light/assets/rules.ini')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/land-v1')
    p.add_argument('--expectations',type=Path)
    p.add_argument('--report',type=Path)
    a = p.parse_args()
    start = time.monotonic()
    current,runner = identities(a),hash_file(a.native)
    if a.expectations:
        source = private_path(a.expectations,a.exe)
        receipt = source.parent/'report.json'
        fingerprint = hash_file(source)
        e = json.loads(source.read_text())
        validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report = private_path(a.report or source.parent/'replay.json',a.exe)
        check_replay_destination(report,source,receipt)
        commands,expected,labels = [e[k] for k in ('commands','expected','labels')]
        metadata,generation = e['evidence'],0
    else:
        dest = private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():
            raise ValueError('Fresh land destination invalid or exists')
        now = time.monotonic()
        commands,expected,labels,metadata = generate(a)
        generation,report = time.monotonic()-now,dest/'report.json'
    now = time.monotonic()
    proc = subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
    if proc.returncode:
        raise RuntimeError('Native land fixture: '+proc.stderr.strip())
    actual = [line.split() for line in proc.stdout.splitlines()]
    elapsed = time.monotonic()-now
    if len(actual) != len(expected):
        raise AssertionError('Land result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x != y:
            raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a) != current or hash_file(a.native) != runner:
        raise ValueError('Land run changed')
    result = {**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),
        'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
        'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
        'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
        'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source = dest/'expected.json'
        write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result})
        fingerprint = hash_file(source)
    result['expectations_sha256'] = fingerprint
    write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 land results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')

if __name__ == '__main__':
    main()
