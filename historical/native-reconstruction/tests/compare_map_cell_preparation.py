#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary Cell recalculation with actual LAT/passability/permission children."""
import argparse,json,random,sys,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_cell_preparation import verify
SOURCES=('src/assets/MapOverlay.hpp','src/assets/MapCellAttributes.hpp','src/assets/MapCellAttributes.cpp','src/assets/MapCellChildren.hpp','src/assets/MapCellChildren.cpp',
 'src/assets/MapCellInputs.hpp','src/assets/MapCellInputs.cpp','tests/map_cell_preparation_vectors.cpp',
 'tests/compare_map_cell_preparation.py','tests/original_map_cell_preparation.py','tests/original_presentation.py',
 'tests/original_foot_lit.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py',
 'tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py','tools/verify_map_cell_preparation.py',
 'tools/verify_map_cell_children.py','tools/verify_map_cell_attributes.py','tools/verify_map_cell_inputs.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Cell preparation engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Cell preparation identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Cell preparation counts differ')
    for command in e['commands']:
        c=command.split()
        try:
            assert c and c[0]=='J' and len(c)==88;list(map(int,c[1:]));assert int(c[13])==0
        except (AssertionError,ValueError):raise ValueError('Malformed Cell preparation command') from None
def cases():
    rng=random.Random(0x43454c4c);result=[]
    def packed(x,y):return (x&65535)|((y&65535)<<16)
    dirs=[packed(0,-1),packed(1,-1),packed(1,0),packed(1,1),packed(0,1),packed(-1,1),packed(-1,0),packed(-1,-1)]
    standard=[10,20,0,200,300,400,450,500,550,600,700,90,190,290,390]
    speed_bits=[0,0x80000000,1,0x3c23d70a,0x3c23d70b,0x3f800000,0x7f800000,0xff800000,0x7fc00000]
    for n in range(1536):
        pos=rng.choice([packed(51,72),packed(0,0),packed(512,0),packed(-32768,-32768),packed(32767,32767)])
        v=[pos,[0,1,2,100,200,65535][n%6],rng.choice([0,2,6,8,-7]),0,[0,0,1,255][(n//6)%4],rng.choice([-128,-5,0,4,123,127]),
           rng.choice([0,1,4,255]),rng.getrandbits(32),rng.randrange(256),rng.randrange(256),rng.randrange(256),
           rng.choice([-2147483648,-129,-1,0,4,127,128,2147483647]),0,[0,1,2,255][(n//24)%4],3,0,rng.randrange(-2147483648,2147483648),
           int(n%7!=0),int(n%5!=0),rng.randrange(256),n%16,rng.choice([-2147483648,-30,0,15,30,45,60,2147483647]),
           rng.choice([-2147483648,-60,0,30,2147483647]),rng.choice([-2147483648,-30,0,60,2147483647]),n%2]
        mapping=[rng.choice([0,2,3,6,8,10]) for _ in range(16)]
        settings=standard.copy()
        if n%4==1:
            for i in range(2,6):settings[i]=0
            for i in range(11,15):settings[i]=90
        elif n%4==2:settings[3]=-1;settings[5]=-1
        elif n%4==3:
            for i in (0,1,6,7,8):settings[i]=2147483647
        shape=[100,0,0,100,100] if n%3 else [rng.choice([-2147483648,-100,-1,0,100,2147483647]) for _ in range(5)]
        v += [*mapping,*([0]*6),n%8,*settings,*dirs,*shape,*[speed_bits[(n+i)%len(speed_bits)] for i in range(11)]]
        result.append(v)
    return result

def generate(a):
    from original_map_cell_preparation import MapCellPreparationOracle
    o=MapCellPreparationOracle(a.exe);commands=[];expected=[];labels=[]
    for v in cases():
        row=o.run(v);commands.append('J '+' '.join(map(str,v)));expected.append(list(map(str,row)));labels.append('complete_Cell_root_nested_actual_LAT_passability_permission_lookup_resident_TMP')
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_root_entries':o.actual_entries,
      'map_lookup_events':o.neighbor_calls,'actual_LAT_entries':o.lat_calls,'actual_passability_entries':o.passability_calls,
      'ordered_selected_stores':o.selected_stores,'actual_LAT_changes':o.lat_changes,'actual_alternate_type_getters':o.alternate_getters,
      'heterogeneous_type_metadata_after_LAT':True,'LAT_passability_permission_lookup_instructions_actual':True,
      'registry_type_map_grid_geometry_directions_tile_globals_and_land_speeds_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-cell-preparation-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/cell-preparation-v2')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Cell preparation destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Cell preparation result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Cell preparation run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 Cell preparation results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
