#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Original complete overlay Cell recalculation with actual classification and TMP children."""
import argparse,json,random,sys,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_overlay_recalculation import verify
SOURCES=('src/assets/MapOverlay.hpp','src/assets/MapOverlay.cpp',
 'src/assets/MapCellChildren.hpp','src/assets/MapCellChildren.cpp',
 'tools/verify_map_overlay.py','tools/verify_map_cell_attributes.py',
 'tests/original_map_overlay.py', 'src/assets/MapCellAttributes.hpp','src/assets/MapCellAttributes.cpp','src/assets/MapCellInputs.hpp','src/assets/MapCellInputs.cpp',
 'tests/map_overlay_recalculation_vectors.cpp','tests/compare_map_overlay_recalculation.py','tests/original_map_overlay_recalculation.py',
 'tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py',
 'tests/presentation_evidence.py','tests/compare_original.py','tests/compare_terrain_visibility.py',
 'tools/verify_terrain_visibility.py','tools/verify_map_overlay_recalculation.py','tools/verify_map_cell_inputs.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Overlay recalculation engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Overlay recalculation identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Overlay recalculation counts differ')
    for command in e['commands']:
        c=command.split()
        try:
            assert c and c[0]=='O';assert len(c)==77;list(map(int,c[1:]))
        except (AssertionError,ValueError):raise ValueError('Malformed Overlay recalculation command') from None
def generate(a):
    from original_map_overlay_recalculation import MapOverlayRecalculationOracle
    o=MapOverlayRecalculationOracle(a.exe);rng=random.Random(0x4f564154);commands=[];expected=[];labels=[];groups={}
    for n in range(2304):
        tile=[0,1,2,3,65535,2147483647][n%6]
        level=rng.choice([-128,-5,0,4,123,127]);cliff=[0,1,2,255][(n//6)%4]
        v=[rng.getrandbits(32),tile,rng.choice([0,2,6,8,-7]),0,[0,1,255][(n//24)%3],level,
           rng.choice([0,1,4,255]),rng.getrandbits(32),rng.randrange(256),rng.randrange(256),rng.randrange(256),
           rng.choice([-2147483648,-129,-1,0,4,127,128,2147483647]),int(n%47==0),cliff,3,
           rng.choice([0,1,2,65535,-2147483648]),rng.randrange(-2147483648,2147483648),
           int(n%7!=0),int(n%5!=0),rng.randrange(256),n%16,rng.choice([-2147483648,-30,0,15,30,45,60,2147483647]),
           rng.choice([-2147483648,-60,0,30,2147483647]),rng.choice([-2147483648,-30,0,60,2147483647]),n%2]
        mapping=[rng.choice([0,2,3,6,8,10]) for _ in range(16)]
        neighbors=[rng.choice([-128,127,max(-128,min(127,level+3)),max(-128,min(127,level+4))]) for _ in range(6)]
        if n%8<6 and level<=123:neighbors=[level]*6;neighbors[n%8]=level+4
        elif n%8==6:neighbors=[-128]*6
        v+=mapping+neighbors
        overlay=-1 if n%23==0 else [6,14,22][(n//3)%3]
        extra=[overlay,[0,1,2,3,4,5,6,8,9,10,11][(n//4)%11],
               [0,1,255,256][(n//12)%4],[0,0,1,255,256][(n//48)%5],4,8,4]
        speeds=[0,0x80000000,1,0x80000001,0x3c23d709,0x3c23d70a,0x3c23d70b,0x3f800000,0xbf800000,0x7f800000,0xff800000,0x7fc00000]
        v[0]=[(51|(72<<16)),0,512,2147450879,2147516416][(n//128)%5] if n%4==0 else (51|(72<<16))
        shape=[100,0,0,100,100] if n%7 else [4,0,0,2,2]
        extra += [255 if n%13==0 else 0,2 if n%11==0 else 0,128 if n%3==0 else 0,n%2,
                  *shape,n%2,*[speeds[(n//64+i)%12] for i in range(12)]]
        row=o.run(v,*extra);commands.append('O '+' '.join(map(str,[*v,*extra])));expected.append(list(map(str,row)))
        label='complete_overlay_early_ordinary_missing_sentinel_resource_removal_cliff_and_ordered_buffers'
        labels.append(label);groups[label]=groups.get(label,0)+1
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'neighbor_service_calls':o.neighbor_calls,
      'LAT_service_calls':o.lat_calls,'passability_service_calls':o.passability_calls,'ordered_selected_stores':o.selected_stores,
      'actual_classifier_calls':o.classifier_calls,'missing_resource_logger_services':o.log_calls,
      'LAT_cliff_neighbors_and_registry_construction_supplied':True,'actual_no_occupant_passability_and_permission':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-overlay-recalculation-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-recalculation-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Overlay recalculation destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Overlay recalculation result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Overlay recalculation run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 Overlay recalculation results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
