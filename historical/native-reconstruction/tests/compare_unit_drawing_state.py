#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base scoped Unit drawing defaults, Facing initialization and status."""
import argparse,itertools,json,random,time,subprocess
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_drawing_state import verify
SOURCES=('tests/compare_unit_drawing_state.py','tests/original_unit_drawing_state.py',
    'tests/unit_drawing_state_vectors.cpp','tools/verify_unit_drawing_state.py',
    'src/sim/UnitDrawingState.hpp','src/sim/Facing.hpp','tests/original_presentation.py',
    'tests/original_foot_lit.py','tools/verify_unit_type_visibility.py','tools/verify_unit_draw_caller.py')
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Drawing-state engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Drawing-state source/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Drawing-state counts differ')
    if any(c.split()[0] not in ('F','D','S') for c in e['commands']):raise ValueError('Unknown drawing-state runner command')
def generate(exe):
    from original_unit_drawing_state import UnitDrawingStateOracle
    o=UnitDrawingStateOracle(exe);rng=random.Random(0x44524157)
    commands=[];expected=[];labels=[];groups={}
    def save(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)));labels.append(group)
        groups[group]=groups.get(group,0)+1
    edges=[-2147483648,-65536,-1,0,1,127,255,65535,2147483647]
    for rate in list(range(-256,257))+edges:
        frame=rng.choice(edges);padding=rng.randrange(256)
        save('actual_rate_constructor_signed_clamp_low_byte_padding',['F',frame,rate,1,padding],o.facing(frame,rate,1,padding))
    for frame,padding in itertools.product(edges,(0,0x7f,0xa7,255)):
        save('actual_default_constructor_clock_padding',['F',frame,0,0,padding],o.facing(frame,0,0,padding))
        save('scoped_three_facings_flags_status_frame_staging_defaults',['D',frame,padding],o.defaults(frame,padding))
    for start,duration,frame in itertools.product(edges,repeat=3):
        args=[start,duration,frame,rng.randrange(256),rng.randrange(256)]
        save('actual_status_signed_positive_remainder_wrap_and_paused',['S',*args],o.status(*args))
    for n in range(1024):
        args=[rng.randint(-2147483648,2147483647) for _ in range(3)]+[n&255,(255-n)&255]
        save('status_random_full_words_and_all_flag_bytes',['S',*args],o.status(*args))
    return commands,expected,labels,{'groups':groups,'audited_callable_roots':o.audit_calls,
        'audited_scoped_blocks':o.audit_blocks,'actual_facing_constructor_calls':o.constructor_calls,
        'constructor_barrel_heading':0,'fixture_neutral_barrel_heading':16384,
        'neutral_barrel_initialization_verified':False}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-drawing-state-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/drawing-state-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a.exe);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh drawing-state evidence exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a.exe);generation=time.monotonic()-now
        metadata['scope']=current['inspection']['scope'];report=out/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:raise AssertionError(f'Native runner failed: {error.stderr}') from error
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Drawing-state result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Drawing-state inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 drawing-state results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
