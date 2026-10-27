#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base loaded wall placement evidence and identity-checked native replay."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_overlay_wall_placement import verify
SOURCES=('src/assets/MapWallUpdate.hpp','src/assets/OverlayPlacement.hpp','src/assets/OverlayPlacement.cpp',
 'src/assets/OverlayTypeInputs.hpp','src/assets/MapOverlayLoading.hpp','src/assets/MapCellInputs.hpp','src/sim/Drive.hpp',
 'tests/overlay_wall_placement_vectors.cpp','tests/compare_overlay_wall_placement.py',
 'tests/original_overlay_wall_placement.py','tools/verify_overlay_wall_placement.py',
 'tools/verify_overlay_placement.py','tests/original_overlay_placement.py',
 'tests/original_overlay_type_inputs.py','tools/verify_overlay_type_inputs.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py','tools/verify_terrain_visibility.py')
def parse(command):
    tokens=command.split();assert tokens and tokens[0]=='W';v=list(map(int,tokens[1:]));assert len(v)==32
    assert all(0<=v[i]<=0xffffffff for i in (0,11,*range(16,24)))
    assert all(-2147483648<=v[i]<=2147483647 for i in (1,8,9,10,12,13,14)) and v[14]!=0
    assert all(0<=v[i]<=255 for i in range(2,8)) and v[3]!=0 and 0<=v[15]<=3
    assert all(0<=n<=8 for n in v[24:])
    assert v[1] not in (0x18,0x19,0xed,0xee,0x7e,0xa7)
    return v
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Wall placement engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Wall placement identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Wall placement counts differ')
    for command in e['commands']:
        try:parse(command)
        except (ValueError,AssertionError,IndexError):raise ValueError('Malformed wall placement command') from None
def generate(a):
    from original_overlay_wall_placement import OverlayWallPlacementOracle
    o=OverlayWallPlacementOracle(a.exe);rng=random.Random(0x57414c4c);commands=[];expected=[];labels=[];groups={}
    def packed(x,y):return (x&65535)|((y&65535)<<16)
    directions=[packed(x,y) for x,y in ((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))]
    def make(seed,**kw):
        d=dict(seed=seed,index=203,slope=0,wall=1,limbo=0,onMap=0,redraw=0,active=1,mode=1,
          x=51*256+128,y=72*256+128,p=packed(51,72),flag=-1,owner=3,loading=1,effect=0)
        d.update(kw);return [*d.values(),*directions,*range(1,9)]
    def save(label,v):
        command='W '+' '.join(map(str,v));parse(command);commands.append(command);expected.append(o.run(v));labels.append(label);groups[label]=groups.get(label,0)+1
    for mode in (-2147483648,-1,0,1,2,3,4,2147483647):
        for limbo in (0,1,2,255):
            for on_map in (0,1,255):
                for redraw in (0,1,255):
                    save('actual_base_mark_gates_and_nonplacement_mutations',make(rng.getrandbits(32),mode=mode,limbo=limbo,onMap=on_map,redraw=redraw))
    for index in (0,1,2,3,22,26,178,203,204,240,-1,2147483647):
        for slope in (0,4,5,127,255):
            for flag in (-2147483648,-1,0,1,2147483647):
                for effect in range(4):
                    save('wall_data_before_index_update_owner_neighbor_counts_and_final_recalculation',make(rng.getrandbits(32),index=index,slope=slope,flag=flag,effect=effect,
                      owner=rng.randrange(-2147483648,2147483648),wall=rng.choice((1,2,255)),loading=rng.choice((-2147483648,-1,1,255,2147483647))))
    for seed in (0,1,127,254,255,256,0x12345678,0xffffffff):
        for p in (packed(0,0),packed(-32768,32767),packed(32767,-32768),packed(-1,-1)):
            for effect in range(4):
                for pattern in range(4):
                    v=make(seed,p=p,x=rng.choice((-2147483648,-257,-256,-255,-1,0,255,256,2147483647)),
                      y=rng.choice((-2147483648,-257,-1,0,255,257,2147483647)),effect=effect,flag=0,mode=3)
                    v[16:24]=[rng.getrandbits(32) for _ in range(8)]
                    v[24:]=list(range(1,9)) if pattern==0 else ([0]*8 if pattern==1 else ([1]*8 if pattern==2 else [rng.randrange(9) for _ in range(8)]))
                    save('word_wrapping_supplied_direction_order_aliases_and_counter_overflow',v)
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'ordered_selected_guest_stores':o.stores,'supplied_service_calls':o.services,
      'wall_update_lookup_recalculation_and_retirement_effects_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-wall-placement-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-wall-placement-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh wall placement destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Wall placement result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Wall placement run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 loaded wall placement results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
