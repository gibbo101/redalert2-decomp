#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact patched Unit image decisions, scoped defaults and nested DrawIt timer."""
import argparse,itertools,json,random,time
from pathlib import Path
from compare_unit_draw_caller import ROOT,SOURCES as CALLER_SOURCES
from compare_terrain_visibility import native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_type_visibility import verify
SOURCES=CALLER_SOURCES+('tests/compare_unit_type_visibility.py','tests/original_unit_type_visibility.py',
                       'tests/unit_type_visibility_vectors.cpp','tools/verify_unit_type_visibility.py')
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Type visibility engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Type visibility source/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Type visibility counts differ')
    if any(c.split()[0] not in ('type','caller') for c in e['commands']):raise ValueError('Unknown type visibility runner')
def generate(exe):
    from original_unit_type_visibility import UnitTypeVisibilityOracle
    oracle=UnitTypeVisibilityOracle(exe);rng=random.Random(0x52413236)
    commands=[];expected=[];labels=[];groups={}
    def save(runner,op,group,args,result):
        commands.append(' '.join(map(str,[runner,op,*args])));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    edges=[-2147483648,-2147483647,-257,-256,-1,0,1,255,256,2147483646,2147483647]
    for mode,a,b,same in itertools.product([-2147483648,-1,0,1,2147483647],[0,1,255,256,-1],[0,1,255,256,-1],[0,1]):
        v=[mode,a,b,same];save('type','H','actual_owner_helper_flags_and_current_pointer',v,oracle.owner(*v))
    indexes=[-2147483648,-33,-32,-1,0,1,23,31,32,33,2147483647]
    for present,same,owner,current,mask in itertools.product([0,1],[0,1],indexes,indexes,[0,1,0x80000000,0xffffffff]):
        v=[present,same,owner,current,mask];save('type','A','actual_alliance_helper_x86_shift_and_sentinels',v,oracle.allied(*v))
    for argument,present,same,owner,current,mask in itertools.product(
            [-257,-256,-1,0,1,255,256,257,-2147483648,2147483647],[0,1],[0,1],[-1,1],[0,1,31,32],[0,0xffffffff]):
        v=[argument,present,same,owner,current,mask];save('type','S','actual_display_type_low_argument_byte_and_house_query',v,oracle.select(*v))
    for frame in edges+[rng.randrange(-2**31,2**31) for _ in range(128)]:
        save('type','C','eight_scoped_constructor_field_blocks',[frame],oracle.defaults(frame))
    def state(**changes):
        a=dict(start=-1,duration=0,disguised=0,creation=0,mode=0,flagA=0,flagB=0,
               same=0,owner_index=1,current_index=2,alliances=0,sensors=0)
        assert set(changes)<=set(a);a.update(changes);return list(a.values())
    def visibility(group,frame,**changes):
        v=state(**changes);save('type','V',group,[frame,*v],oracle.visibility(frame,v))
    for delta,disguised,mode,same in itertools.product(range(-320,577),[0,1,255],[0,1],[0,1]):
        visibility('actual_predicate_signed_phase_window_and_owner_paths',delta,
                   disguised=disguised,mode=mode,same=same,flagA=1)
    for frame,start,duration in itertools.product(edges,repeat=3):
        for owner in [0,1]:
            visibility('actual_predicate_wrapped_timer_compare_before_subtraction',frame,
                       start=start,duration=duration,disguised=1,flagA=owner,creation=rng.choice(edges),
                       sensors=rng.choice([-32768,-1,0,1,32767]))
    for sensors,disguised,current in itertools.product([-32768,-32767,-1,0,1,32766,32767],[0,1,255,256],range(24)):
        visibility('actual_double_cell_getter_and_signed_house_sensor',100,sensors=sensors,
                   disguised=disguised,current_index=current)
    # Existing full caller fixture. Both final draw children and decorations are
    # read-only recorders; all selected type/house/map routines execute unchanged.
    base=[0,0,123,46,47,0,0,96,88,18304,29312,416,0,0,-1,2,416,1112,200,0,0,1,1,1,0,0,0,10,20,96,88]
    for frame,start,duration in itertools.product(edges,repeat=3):
        timer=[frame,start,duration];v=base.copy()
        v[15]=rng.choice([2,5]);v[26]=rng.choice([0,499,500])
        save('caller','timer','complete_caller_timer_after_foot_and_layer5_skip',v+timer,oracle.extended_draw(v,timer))
    for n in range(2048):
        frame=rng.choice(edges) if n%3==0 else rng.randrange(-500,700)
        timer=[frame,rng.choice([-1,frame]),rng.choice([0,1,-1,2147483647])]
        v=base.copy()
        for index in (12,13,14):v[index]=rng.randrange(256)
        v[15]=rng.choice([2,5]);v[19]=rng.choice([0,0x10000]);v[20]=rng.choice([0,1,255,256])
        v[22:26]=[rng.randrange(2) for _ in range(4)];v[26]=rng.choice([0,499,500])
        s=state(start=rng.choice([-1,frame]),duration=rng.choice([0,1,-1]),disguised=rng.randrange(256),
                creation=rng.choice(edges),mode=rng.choice([0,1,-1]),flagA=rng.randrange(2),flagB=rng.randrange(2),
                same=rng.randrange(2),owner_index=rng.randrange(24),current_index=rng.randrange(24),
                alliances=rng.randrange(2**32),sensors=rng.choice([-32768,-1,0,1,32767]))
        save('caller','state','complete_caller_nested_actual_type_house_cell_selection',v+timer+s,oracle.extended_draw(v,timer,s))
    oracle.check_table()
    return commands,expected,labels,groups,oracle.audit_calls,oracle.audit_blocks
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-type-visibility-vectors')
    p.add_argument('--caller-native',type=Path,default=ROOT/'build/native/unit-draw-caller-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/type-state')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a.exe);runners={'type':a.native,'caller':a.caller_native}
    runner_hashes={k:hash_file(v) for k,v in runners.items()}
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh type evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls,blocks=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'audited_constructor_blocks':blocks,'seed':0x52413236,
                  'scope':'Complete type/house/alternate predicates, actual duplicate map getter and signed observer counter; nested full ordinary caller with timer decision and final-body/Foot/timer-decoration services. Eight scoped constructor blocks with supplied live registers, original ordered writes and full arenas; not complete construction. Synthetic owner/map associations, no fog, final pixels, runtime integration or frame parity.'}
        report=out/'report.json'
    now=time.monotonic();actual=[None]*len(commands)
    for key,path in runners.items():
        chosen=[(n,c.split(' ',1)[1]) for n,c in enumerate(commands) if c.split()[0]==key]
        results=native(path,[c for n,c in chosen])
        if len(results)!=len(chosen):raise AssertionError('Type result count differs')
        for (n,c),result in zip(chosen,results):actual[n]=result
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Type result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe)!=current or {k:hash_file(v) for k,v in runners.items()}!=runner_hashes:raise ValueError('Type inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner_hashes,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 Unit type/state results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
