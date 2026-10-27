#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Bounded original Cell recalculation against resident supplied map/TMP records."""
import argparse,json,random,sys,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_cell_attributes import verify
SOURCES=('src/assets/MapCellChildren.hpp','src/assets/MapOverlay.hpp','src/assets/MapCellAttributes.hpp','src/assets/MapCellAttributes.cpp','src/assets/MapCellInputs.hpp','src/assets/MapCellInputs.cpp',
 'tests/map_cell_attribute_vectors.cpp','tests/compare_map_cell_attributes.py','tests/original_map_cell_attributes.py',
 'tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py',
 'tests/presentation_evidence.py','tests/compare_original.py','tests/compare_terrain_visibility.py',
 'tools/verify_terrain_visibility.py','tools/verify_map_cell_attributes.py','tools/verify_map_cell_inputs.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Cell attribute engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Cell attribute identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Cell attribute counts differ')
    for command in e['commands']:
        c=command.split()
        try:
            assert c and c[0] in ('I','A');assert len(c)==(5 if c[0]=='I' else 48);list(map(int,c[1:]))
        except (AssertionError,ValueError):raise ValueError('Malformed Cell attribute command') from None
def generate(a):
    from original_map_cell_attributes import MapCellAttributeOracle
    o=MapCellAttributeOracle(a.exe);rng=random.Random(0x52454341);commands=[];expected=[];labels=[];groups={}
    def save(group,op,values,row):commands.append(op+' '+' '.join(map(str,values)));expected.append(list(map(str,row)));labels.append(group);groups[group]=groups.get(group,0)+1
    for n in range(512):
        v=[rng.getrandbits(32),rng.choice([-2147483648,-101,-1,0,5,2147483647]),rng.choice([-2147483648,-1,0,31,2147483647]),rng.choice([1,17,262144,2147483647])]
        save('actual_clamped_buffer_index_signed_geometry_and_low32_wrap','I',v,o.index(*v))
    for n in range(2304):
        tile=[0,1,2,3,65535,2147483647][n%6]
        level=rng.choice([-128,-5,0,4,123,127]);cliff=[0,1,2,255][(n//6)%4]
        # Valid tube association excludes construction; it does not recover it.
        v=[rng.getrandbits(32),tile,rng.choice([0,2,6,8,-7]),0,[0,1,255][(n//24)%3],level,
           rng.choice([0,1,4,255]),rng.getrandbits(32),rng.randrange(256),rng.randrange(256),rng.randrange(256),
           rng.choice([-2147483648,-129,-1,0,4,127,128,2147483647]),int(n%47==0),cliff,3,
           rng.choice([0,1,2,65535,-2147483648]),rng.randrange(-2147483648,2147483648),
           int(n%7!=0),int(n%5!=0),rng.randrange(256),n%16,rng.choice([-2147483648,-30,0,15,30,45,60,2147483647]),
           rng.choice([-2147483648,-60,0,30,2147483647]),rng.choice([-2147483648,-30,0,60,2147483647]),n%2]
        mapping=[rng.choice([0,2,3,6,8,10]) for _ in range(16)]
        neighbors=[rng.choice([-128,127,max(-128,min(127,level+3)),max(-128,min(127,level+4))]) for _ in range(6)]
        # Rotate the first qualifying neighbor and include complete no-match scans.
        if n%8<6 and level<=123:neighbors=[level]*6;neighbors[n%8]=level+4
        elif n%8==6:neighbors=[-128]*6
        v+=mapping+neighbors
        save('complete_ordinary_recalculation_resident_invalid_missing_fallback_cliff_level_and_buffer_store_order','A',v,o.run(v))
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'neighbor_service_calls':o.neighbor_calls,
      'LAT_service_calls':o.lat_calls,'passability_service_calls':o.passability_calls,'ordered_selected_stores':o.selected_stores,
      'services_are_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-cell-attribute-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/cell-attributes-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Cell attribute destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Cell attribute result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Cell attribute run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 Cell attribute results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
