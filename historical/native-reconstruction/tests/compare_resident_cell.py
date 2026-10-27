#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base Cell/LAT/classifier/passability join on shared resident inputs."""
import argparse,json,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_map_cell_preparation import SOURCES as CELL_SOURCES
from verify_resident_cell import verify
SOURCES=tuple(dict.fromkeys((*CELL_SOURCES,'src/assets/MapOverlay.cpp',
 'src/assets/ResidentCellPreparation.hpp','src/assets/ResidentCellPreparation.cpp',
 'tests/resident_cell_vectors.cpp','tests/original_resident_cell.py','tests/compare_resident_cell.py',
 'tools/verify_resident_cell.py','tools/verify_map_overlay.py')))

def parse(command):
    c=command.split();assert c and c[0]=='K' and len(c)==99;v=list(map(int,c[1:]));assert v[12]==0
    assert 0<=v[0]<=0xffffffff and all(-2147483648<=n<=0xffffffff for n in v)
    assert 0<=v[4]<=255 and -128<=v[5]<=127 and 0<=v[6]<=255
    overlay,land,tiberium,no_use,crushable,wall,rubble,rock,image,images,slopes=v[87:]
    assert overlay==-1 or 0<=overlay<64
    assert 0<=land<11 and all(0<=n<=255 for n in (tiberium,no_use,crushable,wall,rubble,rock))
    assert all(-2147483648<=n<=2147483647 for n in (image,images,slopes))
    return v[:87],v[87:]

def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}

def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Resident Cell engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Resident Cell identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Resident Cell counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed resident Cell command') from None

def cases():
    from compare_map_cell_preparation import cases as ordinary_cases
    captured=ordinary_cases()
    result=[]
    def add(label,v,profile):
        command='K '+' '.join(map(str,[*v,*profile]));parse(command);result.append((label,command))
    for n in range(768):
        v=captured[n*2].copy()
        # Direct control of ordinary ramp and land cases with a real resident
        # source image. Other cases retain sentinel/invalid images and extremes.
        if n%3:
            v[0]=51|(72<<16);v[1]=[0,1,100,200,300,400,600,700][(n//3)%8];v[4]=0
            v[17]=v[18]=1;v[19]=[0,1,4,5,255][(n//8)%5];v[21]=[30,45,60][n%3]
            v[5]=[0,4,123][(n//24)%3]
        overlay=-1 if n%17==0 else [6,14,22][(n//7)%3]
        land=[0,1,2,3,4,5,6,8,9,10][(n//3)%10]
        profile=[overlay,land,[0,1,255][(n//5)%3],[0,1,255][(n//15)%3],
          [0,1,255][(n//45)%3],[0,1][(n//90)%2],[0,128][(n//180)%2],n%2,
          [0,6,14,22,2147483647,-2147483648][(n//30)%6],4,8]
        add('actual_shared_LAT_classifier_passability_permission_TMP_order',v,profile)
    # Explicit actual LAT mutation while the saved original TMP record supplies
    # ramp/land/dimensions after the Cell tile has changed to alternate metadata.
    for no_use in (0,1):
      for ramp in (0,1,4,5):
       for tiberium in (0,255):
        v=captured[0].copy();v[0]=51|(72<<16);v[1]=100;v[4]=0;v[5]=4;v[7]=0
        v[13]=0;v[17]=v[18]=1;v[19]=ramp;v[20]=0;v[21]=45;v[47]=0
        v[48:63]=[10,20,100,200,300,400,450,500,550,600,700,90,190,290,390]
        v[71:76]=[80,0,0,80,85];v[76:87]=[0x3f800000]*11
        add('explicit_saved_TMP_actual_LAT_change_resource_clear_before_passability',v,[6,0,tiberium,no_use,0,0,0,0,6,4,8])
    return result

def generate(a):
    from original_resident_cell import ResidentCellOracle
    o=ResidentCellOracle(a.exe);commands=[];expected=[];labels=[]
    for label,command in cases():
        v,profile=parse(command);commands.append(command);labels.append(label);expected.append(o.run(v,profile))
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_root_entries':o.actual_entries,
      'map_lookup_events':o.neighbor_calls,'actual_LAT_entries':o.lat_calls,'actual_passability_entries':o.passability_calls,
      'actual_classifier_entries':o.classifier_calls,'missing_resource_logger_services':o.log_calls,
      'ordered_selected_stores':o.selected_stores,'actual_LAT_changes':o.lat_changes,'actual_alternate_type_getters':o.alternate_getters,
      'LAT_classifier_passability_permission_lookup_TMP_actual_together':True,
      'type_resource_initialization_registry_geometry_tables_and_Wheel_speeds_supplied':True}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/resident-cell-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/resident-cell-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh resident Cell destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Resident Cell result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Resident Cell run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} shared resident Cell results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
