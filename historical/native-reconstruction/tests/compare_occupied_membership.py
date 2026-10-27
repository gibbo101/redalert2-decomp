#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Unit membership with actual occupied Cell recalculation."""
import argparse,itertools,json,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_unit_membership_discovery import command as joined_command,parse as joined_parse,FIELDS
from compare_unit_membership import RECORDS,row
from compare_occupied_cell import SOURCES as OCCUPIED_SOURCES
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_occupied_cell import verify
SOURCES=(*OCCUPIED_SOURCES,'tests/original_occupied_membership.py','tests/compare_occupied_membership.py')
PREPARED=[[i if i<3 else 65535,0,0,213,1,1,(i*3)%11,45] for i in range(4)]
def command(prepared=None,**kwargs):return 'K '+' '.join(map(str,[n for r in (PREPARED if prepared is None else prepared) for n in r]))+' '+joined_command(**kwargs)[2:]
def parse(cmd):
 p=cmd.split();assert p[0]=='K';v=list(map(int,p[1:33]));assert len(v)==32
 prepared=[v[i:i+8] for i in range(0,32,8)]
 for tile,land,sub,extra,present,valid,tmp,height in prepared:
  assert tile in (0,1,2,65535) and 0<=land<11 and 0<=sub<=255 and 0<=extra<=255 and present in (0,1) and valid in (0,1) and 0<=tmp<11 and -2147483648<=height<=2147483647
 args=joined_parse('J '+' '.join(p[33:]));return prepared,*args
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Occupied membership engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Occupied membership identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Occupied membership counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,OverflowError):raise ValueError('Malformed occupied membership command') from None
def generate(a):
 from original_occupied_membership import OccupiedMembershipOracle
 o=OccupiedMembershipOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];groups={};steps=0
 def add(label,prepared=None,**kwargs):
  nonlocal steps
  cmd=command(prepared=prepared,planes=planes,**kwargs);args=parse(cmd);commands.append(cmd);expected.append(o.run_occupied(*args));labels.append(label);groups[label]=groups.get(label,0)+1;steps+=len(args[-1])
 for ramp,level,profile,alt in itertools.product(range(21),(-1,4),range(4),(0,1)):
  rec=[r.copy() for r in RECORDS];rec[0][:3]=[level,ramp,0];prepared=[r.copy() for r in PREPARED]
  if profile==1:prepared[0][4]=0
  elif profile==2:prepared[0][5]=0
  elif profile==3:prepared[0][0]=65535
  prepared[0][6]=ramp%11;prepared[0][7]=(30,45,60)[ramp%3]
  fields=FIELDS.copy();fields[:4]=[8,0,8,8]
  add('complete_Mark_membership_discovery_occupation_Cell_LAT_TMP_passability_buffers_shared',prepared,
   fields=fields,records=rec,header=[0,0,1,1,0,0,0,128,0],rows=[row(mode=m,z=level*104+128,alt=alt) for m in (1,2,0,3,0)])
 for sub,tile,current in itertools.product((0,1,255),(0,1,2,65535),(0,1)):
  prepared=[r.copy() for r in PREPARED];prepared[0][:3]=[tile,6,sub]
  add('resident_type_selection_subtile_failure_and_live_current_House',prepared,header=[0,0,1,0,0,0,current,128,0],rows=[row(root=r) for r in (2,3,2,3)])
 for alt in (0,1):
  rec=[r.copy() for r in RECORDS];rec[0][5+alt]=1
  add('long_existing_Unit_list_primary_vs_alternate_passability_and_warm_fields',records=rec,links=[-1,2,3,-1],header=[0,0,1,1,0,0,0,128,0],rows=[row(mode=m,alt=alt) for m in (1,2,0,3,0)*12])
 for x,y in ((52*256+128,72*256+128),(53*256+128,72*256+128),(54*256,72*256),(16777216+51*256+128,72*256+128),(-256,256)):
  add('map_word_vs_full_coordinate_aliases_and_shared_fallback_with_recalculation',rows=[row(mode=m,x=x,y=y) for m in (1,2,0,3,0)])
 assert o.recalculations and o.pass_kind_calls
 assert all(o.entries[hex(root)] for root in (0x472540,0x471d10,0x478f40,0x55a660,0x5293d0,0x529300,0x52b690,0x52b6f0))
 return commands,expected,labels,{'groups':groups,'query_steps':steps,'audited_original_calls':o.audit_calls,'actual_entries':o.entries,'selected_original_stores':o.selected_stores,
  'actual_recalculations':o.recalculations,'actual_occupied_kind_calls':o.pass_kind_calls,'remaining_atexit_services':o.service_counts['0x78298a'],
  'initial_actor_House_map_TMP_type_geometry_speed_records_supplied':True,'Tag_null_loading_one_no_overlay_no_allocation':True,'Process_runtime_frame_parity_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-membership-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/occupied-membership-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh occupied membership destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native occupied membership: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Occupied membership result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   first=next((j for j,(xx,yy) in enumerate(zip(x,y)) if xx!=yy),min(len(x),len(y)))
   raise AssertionError(f'Occupied membership {i} {labels[i]} at {first}: {x[max(0,first-8):first+12]} != {y[max(0,first-8):first+12]}; {commands[i]}')
 safety=['','K 0',command()+' trailing',command(prepared=[[4,*PREPARED[0][1:]],*PREPARED[1:]])]
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Occupied membership safety refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Occupied membership run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} occupied membership sequences: PASS ({result["evidence_mode"]}, {metadata["query_steps"]:,} calls, {elapsed:.3f}s native)')
if __name__=='__main__':main()
