#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Initialized resources and actual resident Cell children inside overlay loading."""
import argparse,json,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_resource_map_inputs import SOURCES as RESOURCE_SOURCES,commands as resource_commands,parse as resource_parse,identities as resource_identities,initialize
from compare_resident_cell import SOURCES as CELL_SOURCES
from verify_resident_overlay import verify
SOURCES=tuple(dict.fromkeys((*RESOURCE_SOURCES,*CELL_SOURCES,
 'src/assets/ResidentOverlayPreparation.hpp','src/assets/ResidentOverlayPreparation.cpp',
 'tests/original_resident_overlay.py','tests/compare_resident_overlay.py','tools/verify_resident_overlay.py')))
def parse(command):
    c=command.split();assert c and c[0]=='R';v=list(map(int,c[1:]));assert len(v)>1 and 0<=v[-1]<=3
    resource_parse('J '+' '.join(map(str,v[:-1])))
    return v[:-1],v[-1]
def identities(a):
    result=resource_identities(a)
    return {**result,'inspection':{'resource_input_phase':result['inspection'],'resident_overlay':verify(a.exe.read_bytes())},
      'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Resident overlay engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Resident overlay identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Resident overlay counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed resident overlay command') from None
def commands(a,frames):
    profiles=(0,1,2,3,0,3,1,1,0)
    return [(label+'_resident_profile_'+str(profile),[*v,profile])
      for (label,v),profile in zip(resource_commands(a,frames),profiles)]
def generate(a):
    from original_resource_type_inputs import ResourceTypeInputOracle
    from original_resident_overlay import ResidentOverlayOracle
    t=ResourceTypeInputOracle(a.exe);o=ResidentOverlayOracle(a.exe);cmds=[];expected=[];labels=[]
    for label,v in commands(a,o.frames):
        command='R '+' '.join(map(str,v));body,profile=parse(command);count=body[0];at=1+count*5
        rows=[body[i:i+5] for i in range(1,at,5)];tail=body[at:];seed=tail[1+tail[1]+1+9]
        records,fingerprint=initialize(t,rows,seed)
        expected.append([fingerprint,*o.run('N',[len(records),*[x for row in records for x in row],*tail[1:]],profile)])
        cmds.append(command);labels.append(label)
        print(label+': original complete',flush=True)
    return cmds,expected,labels,{'groups':dict.fromkeys(labels,1),'resource_type_audits':t.audit_calls,
      'resource_type_entries':t.roots,'overlay_audits':o.audit_calls,'actual_root_entries':o.roots,
      'ordered_selected_Cell_actor_registry_stores':o.stores,'ordered_buffer_stores':o.buffer_stores,
      'supplied_service_calls':o.service_calls,'actual_constructors':o.constructed,
      'actual_resource_entries':o.resource_entries,'actual_classifier_entries':o.classifier_entries,
      'missing_resource_logger_services':o.missing_logs,'actual_recalculations':o.recalculations,
      'actual_LAT_entries':o.lat_entries,'actual_passability_entries':o.passability_entries,
      'resource_initialization_separate_audited_phase':True,'overlay_reader_Cell_children_share_actual_guest_state':True,
      'original_startup_or_later_two_pass_map_parent_executed':False,'initial_Cell_TMP_type_geometry_table_Wheel_inputs_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-map-resource-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/resident-overlay-v2')
    p.add_argument('--fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);cmds,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh resident overlay destination invalid or exists')
        now=time.monotonic();cmds,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,cmds);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Resident overlay result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Resident overlay run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(cmds),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':cmds,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(cmds):,} shared resident overlay scenarios: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
