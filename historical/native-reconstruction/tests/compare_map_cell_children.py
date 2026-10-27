#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Fresh exact-base LAT, empty-cell passability and map-permission evidence."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_cell_children import verify
SOURCES=('src/assets/MapCellChildren.hpp','src/assets/MapCellChildren.cpp','src/assets/MapCellInputs.hpp',
 'tests/map_cell_child_vectors.cpp','tests/compare_map_cell_children.py','tests/original_map_cell_children.py',
 'tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py','tests/original_presentation.py',
 'tests/original_foot_lit.py','tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py',
 'tools/verify_map_cell_children.py','tools/verify_map_cell_inputs.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Map child engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Map child identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Map child counts differ')
    for command in e['commands']:
        c=command.split()
        try:assert c and c[0] in ('L','E','P');assert len(c)=={'L':44,'E':11,'P':22}[c[0]];list(map(int,c[1:]))
        except (AssertionError,ValueError):raise ValueError('Malformed map child command') from None
def generate(a):
    from original_map_cell_children import MapCellChildOracle,packed
    o=MapCellChildOracle(a.exe);rng=random.Random(0x4c415443);commands=[];expected=[];labels=[];groups={}
    def save(label,op,v):
        row=o.run(op,v);commands.append(op+' '+' '.join(map(str,v)));expected.append(list(map(str,row)));labels.append(label);groups[label]=groups.get(label,0)+1
    ordinary=[packed(0,-1),packed(1,-1),packed(1,0),packed(1,1),packed(0,1),packed(-1,1),packed(-1,0),packed(-1,-1)]
    standard=[10,20,100,200,300,400,450,500,550,600,700,90,190,290,390]
    positions=[packed(51,72),packed(0,0),packed(32767,32767),packed(-32768,-32768),packed(512,0),packed(-1,1)]
    for n in range(2048):
        group=n%4;mask=(n//4)%16;variant=(n//64)%4;settings=standard.copy()
        if variant==1:
            for i in range(2,6):settings[i]=100
            for i in range(11,15):settings[i]=90
        elif variant==2:settings[3]=-1;settings[5]=-1
        elif variant==3:
            for i in (0,1,6,7,8):settings[i]=2147483647
        start=settings[11+group] if n%3 else settings[2+group]+(n%16)
        if start<0:start=999
        tiles=[settings[11+group]]*8
        for i in range(4):tiles[i*2]=999 if mask&(1<<i) else rng.choice([settings[11+group],max(0,settings[2+group]),settings[0],settings[1],settings[6],settings[7],settings[8]])
        directions=ordinary.copy()
        if n%17==0:directions[0]=packed(512,0);directions[4]=packed(0,1)
        v=[positions[(n//256)%len(positions)],start,n%256,n%2,*settings,*directions,*tiles,*[rng.choice([0,1,255]) for _ in range(8)]]
        save('complete_LAT_ordered_groups_masks_absent_and_overlapping_ranges_signed_bounds_alias_and_wrap','L',v)
    for n in range(256):
        slope=[0,1,2,3,4,5,255,128][n%8];mask=(n//8)%4
        slopes=[0 if mask&(1<<(i%2)) else 7 for i in range(8)]
        # Explicitly vary the two queried cardinals for each slope.
        if 1<=slope<=4:
            for bit,i in enumerate(((6,2),(0,4),(2,6),(4,0))[slope-1]):slopes[i]=0 if mask&(1<<bit) else 7
        v=[positions[(n//32)%len(positions)],standard[9 if n%2 else 10],slope,n%2,*standard,*ordinary,*([777]*8),*slopes]
        save('complete_LAT_slope_pair_order_all_zero_masks_fallback_and_resident_null_getters','L',v)
    for n in range(2048):
        shape=[100,0,0,100,100] if n%3 else [rng.choice([-2147483648,-100,-1,0,100,2147483647]) for _ in range(5)]
        p=positions[n%len(positions)] if n%3 else rng.getrandbits(32)
        v=[p,rng.choice([-128,-7,0,4,127]),rng.choice([0,1,255]),rng.choice([0,1,2,255,256,257,-1]),*shape,n%2]
        save('complete_map_permission_signed_geometry_elevation_byte_gate_fallback_and_low32_wrap','E',v)
    bits=[0,0x80000000,1,0x3c23d709,0x3c23d70a,0x3c23d70b,0x3f800000,0x7f800000,0xff800000,0x7fc00000]
    for n in range(1536):
        p=packed(51,72) if n%4 else rng.choice(positions)
        v=[p,rng.choice([-128,-7,0,4,127]),rng.choice([0,1,255]),n%11,100,0,0,100,100,n%2,*[bits[(n+i)%len(bits)] for i in range(11)]]
        save('complete_empty_passability_nested_actual_permission_float32_threshold_nan_special_lands_and_records','P',v)
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,'ordered_selected_stores':o.stores,'map_lookup_events':o.queries,
      'LAT_passability_permission_lookup_instructions_actual':True,'tile_globals_directions_geometry_and_speed_inputs_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-cell-child-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/cell-children-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh map child destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Map child result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Map child run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 map child results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
