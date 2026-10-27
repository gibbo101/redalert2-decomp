#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Scoped stock missing restriction input, with exact original/default/store evidence."""
import argparse,configparser,json,time
from pathlib import Path
from compare_unit_model_inputs import SOURCES as PARENTS
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_movement_restriction import verify
SOURCES=tuple(dict.fromkeys((*PARENTS,'tools/verify_unit_movement_restriction.py',
    'tests/original_unit_movement_restriction.py','tests/compare_unit_movement_restriction.py',
    'tests/test_unit_movement_restriction_evidence.py','tests/unit_movement_restriction_vectors.cpp',
    'src/assets/UnitMovementRestriction.cpp','src/assets/UnitMovementRestriction.hpp')))
def identities(a):
    return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
        'rules_path':str(a.rules.resolve()),'rules_sha256':hash_file(a.rules)}
def parse(command):
    w=command.split()
    if len(w)==3 and w[0]=='M' and int(w[1]) in (0,1) and 0<=int(w[2])<=255:return
    if len(w)==2 and w[0]=='O':return
    raise ValueError('Malformed restriction command')
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Restriction engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Restriction source/input identity differs')
    if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Restriction counts differ')
    for c in e['commands']:
        parse(c)
        if c.startswith('O ') and c[2:]!=current.get('rules_path'):raise ValueError('Restriction rules path differs')
def generate(a):
    from original_unit_movement_restriction import UnitMovementRestrictionOracle
    o=UnitMovementRestrictionOracle(a.exe);commands=[];expected=[];labels=[]
    for mode in (0,1):
        for neighbor in (0,1,66,127,255):
            commands.append(f'M {mode} {neighbor}');expected.append(list(map(str,o.run(mode,neighbor))));labels.append('scoped_default_then_missing_section_or_key_actual_children')
    config=configparser.ConfigParser(interpolation=None,strict=False,allow_no_value=True,inline_comment_prefixes=(';',))
    config.read_string(a.rules.read_text(encoding='latin1'))
    if config.has_option('HTNK','MovementRestrictedTo'):raise ValueError('Owned HTNK restriction key is present')
    commands.append('O '+str(a.rules.resolve()));expected.append(list(map(str,o.run(1,66))));labels.append('owned_HTNK_decoded_absence_not_full_INI_parser')
    assert all(o.entries[hex(p)] for p in (0x46a970,0x482eb0,0x482f00,0x50e9a0,0x781f20))
    return commands,expected,labels,{'actual_entries':o.entries,'distinct_original_instructions':len(o.entered),
        'audited_scoped_blocks':o.audit_blocks,'audited_callable_roots':o.audit_calls,
        'scope':o.inspection['scope'],'ordered_selected_writes_stack_register_arena_and_code_inputs_audited':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--rules',type=Path,default=ROOT/'private/map-depth-1006/resident-fixture-v1/rules.ini')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-movement-restriction-vectors')
    p.add_argument('--output',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text())
        validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        if not a.output or a.report:raise ValueError('Fresh restriction proof requires --output only')
        out=private_path(a.output,a.exe)
        if out.exists():raise ValueError('Fresh restriction destination exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if actual!=expected:raise AssertionError('Restriction original/native results differ')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Restriction inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
        'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
        'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands)} scoped missing restriction input results: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
