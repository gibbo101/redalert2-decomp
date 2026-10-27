#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual admission with production owned Cells and Unit membership."""
import itertools,json,struct,subprocess,time
import compare_runtime_membership as runtime
import compare_membership_drive as member
import compare_prepared_foot_depth as prepared
import compare_resident_map_floor as floor
from compare_ground_drive_admission_process import SOURCES as ADMISSION_SOURCES
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_owned_unit_admission import verify
SOURCES=tuple(dict.fromkeys((*member.SOURCES,*runtime.SOURCES,*ADMISSION_SOURCES,
 'tools/verify_owned_unit_admission.py','tests/original_owned_unit_admission.py',
 'tests/compare_owned_unit_admission.py','tests/test_owned_unit_admission_evidence.py')))
def command(crusher=1,**kwargs):return 'A '+member.command(**kwargs)[2:]+' '+str(crusher)
def parse(cmd):
 if cmd.startswith('P '):return member.parse(cmd)
 words=cmd.split();assert len(words)==46 and words[0]=='A'
 crusher=int(words[-1]);assert 0<=crusher<=255
 route=list(map(int,words[17:41]));assert route[-1]==-1 and all(-1<=d<=7 for d in route)
 canonical=words[1:-1].copy();end=False
 for i,d in enumerate(route):
  if end:canonical[16+i]='-1'
  if d==-1:end=True
 _,(head,_,numeric)=member.parse('M '+' '.join(canonical))
 return 'A',(head,route,numeric,crusher)
def identities(a):
 return {'production':runtime.identities(a),'inspection':verify(a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Owned admission engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Owned admission identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Owned admission counts differ')
 ready=False
 for cmd in e['commands']:
  try:op,_=parse(cmd)
  except (ValueError,AssertionError,IndexError,TypeError,OverflowError,struct.error):raise ValueError('Malformed owned admission command') from None
  if op=='P':ready=True
  elif not ready:raise ValueError('Owned admission requires a prepared map')
def blocked_trace_samples(row):
 try:states=[list(map(int,row[i+1:i+58])) for i,t in enumerate(row) if t=='S']
 except (ValueError,TypeError):raise ValueError('Malformed blocked guest state') from None
 if len(states)!=32 or not all(len(s)==57 and s[1:4]==[18816,10624,832] and s[10]==0 and s[33:36]==[-1,4,5] and s[56]==-1 for s in states):
  raise ValueError('Blocked guest position/driving/retained queue coverage differs')
 if not any(row[i:i+5]==['a','d','7','0','0'] for i in range(len(row)-4)):raise ValueError('Blocked guest result7 not observed')
 return len(states)
def generate(a,ramps=range(21),owned=True):
 from original_owned_unit_admission import OwnedUnitAdmissionOracle
 o=OwnedUnitAdmissionOracle(a.exe);source=json.loads(a.depth_fixture.read_text());commands=[];expected=[];labels=[];ticks=0;synthetic=True
 def save(label,cmd,result):
  parse(cmd);commands.append(cmd);expected.append(list(map(str,result)));labels.append(label)
 def prepare(f,label):save(label,'P '+floor.command(*f[:5],f[5:]),o.prepare_map(f));print(label,flush=True)
 def move(label,**kwargs):
  nonlocal ticks
  if synthetic:
   # Keep unused diagonal/curve probes inside prepared ordinary Cells too.
   at=kwargs.get('at',(1408,1664,37));destination=kwargs.get('destination',(2176,1664,0))
   kwargs['at']=(at[0]+1536,at[1]+1536,at[2])
   kwargs['destination']=destination if destination==(0,0,0) else (destination[0]+1536,destination[1]+1536,destination[2])
  kwargs.setdefault('mode',len(commands)%4);cmd=command(**kwargs);_,values=parse(cmd)
  save(label,cmd,o.run_owned(*values));ticks+=values[0][10];print(label,ticks,'ticks',flush=True)
 template,_=prepared.parse(source['commands'][3]);common=list(template[5]);common[:5]=[12,12,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 for ramp in ramps:
  for level in (0,1,2):
   types=[[1,1,1,60,30,1,0,0,0,0,0],[1,1,1,60,30,1,0,ramp,0,0,0]]
   cells=[]
   for y in range(25):
    for x in range(25):
     if x+y>12 and abs(x-y)<12 and x+y<=36:
      cells.append([x,y,int(x==12),0,level if x==12 else 0,0,-1,0,0,0,0,0,17,91,-1,41,0])
   f=(*template[:5],common,[12,0,0,12,12],types,cells,[],[],template[11],[])
   prepare(f,f'owned_membership_ramp_{ramp}_level_{level}')
   move('actual_admission_with_live_Mark_occupation_and_recalculation',steps=96)
   move('reverse_turn_before_actual_admission',at=(2176,1664,-101),destination=(1408,1664,0),heading=0,route=(6,6,6),steps=128,key=17)
   if ramp==0 and level==0:
    for direction,crusher in itertools.product(range(8),(0,1,255)):
     dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[direction]
     move('eight_directions_raw_crusher_and_live_membership',at=(1664,1664,37),destination=(1664+512*dx,1664+512*dy,0),
      heading=direction<<13,route=(direction,direction),crusher=crusher,steps=96)
    for route in ((2,3,4,4),(2,1,0,0),(2,-1,4,5),(2,3,-1,4,5,6,7)):
     move('curves_and_retained_queue_tails',route=route,steps=160)
    for speed in (0.,-0.,.5,1.5):move('actual_land_speed_admission',numeric=(1.,speed,.7,1.2),steps=32)
    move('signed_tick_wrap_and_actual_Facing',tick=2147483640,steps=128,mode=3)
 if owned:
  synthetic=False
  f,_=prepared.parse(source['commands'][0]);prepare(f,'owned_original_map_13515_Cells')
  move('owned_parked_cliff_floor_height_and_actual_Mark',at=(51*256+128,72*256+128,-500),destination=(0,0,0),route=(),steps=8,heading=49152)
  for mode in range(4):move('owned_level_crossing_actual_admission_and_membership',at=(86*256+128,101*256+128,31),destination=(92*256+128,101*256+128,0),route=(2,)*6,steps=160,mode=mode)
  for mode in range(4):move('owned_zero_speed_terrain_rejection_retains_route_tail',at=(73*256+128,41*256+128,31),destination=(74*256+128,41*256+128,0),route=(2,4,5),heading=16384,steps=32,mode=mode,numeric=(1.,0.,.7,1.2))
 blocked_samples=sum(blocked_trace_samples(row) for label,row in zip(labels,expected) if label=='owned_zero_speed_terrain_rejection_retains_route_tail')
 if owned and blocked_samples!=128:raise AssertionError('Missing actual stock-map blocked-state coverage')
 required=(0x55acd0,0x703040,0x705160,0x4c2e60,0x54ab70,0x54af70,0x707980,0x7079e0,0x472540,0x478f40)
 if not all(o.all_entries[hex(a)] for a in required) or not o.next_calls or not all(o.admission_returns.get(n) for n in (0,7)) or o.actual_actor57a_checks!=ticks:
  raise AssertionError('Missing joined original decision/membership coverage')
 return commands,expected,labels,{'movement_ticks':ticks,'complete_Process_calls':o.roots,'actual_entries':o.all_entries,
  'stock_blocked_guest_state_samples':blocked_samples,'stock_blocked_Track_speed_supplied_zero':True,
  'actual_admission_returns':o.admission_returns,'admission_callers':{hex(k):v for k,v in o.callers.items()},'actual_gate_returns':o.gate_returns,
  'actual_next_Cell_calls':o.next_calls,'actual_self_skip_entries':o.self_skips,'selected_preparation_stores':o.preparation_stores,
  'supplied_retry_padding_words':o.supplied_retry_words,'actual_actor57a_state_checks':o.actual_actor57a_checks,
  'actual_Mark_calls':o.actual_marks,'actual_recalculations':o.actual_recalculations,'actual_eligible_unmarks':o.eligible_unmarks,
  'selected_membership_effect_stores':o.effect_stores,'body_shadow_pose_calls':o.pose_calls,'coverage':o.coverage,
  'entered_distinct_instructions':len(o.instructions),'new_code_and_direction_registry_loading_inputs_audited':True,
  'same_guest_prepared_map_actual_admission_next_Cell_and_mutable_Mark':True,
  'initial_type_House_registry_directions_speeds_owners_and_missions_supplied':True,
  'single_Unit_no_stationary_residents_gate_animation_pathfinding_or_full_frame_claim':True}
def main():
 a=runtime.arguments()
 if a.output==ROOT/'private/map-depth-1006/runtime-membership-v1':a.output=ROOT/'private/map-depth-1006/owned-unit-admission-v1'
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh owned admission destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run(member.native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True);elapsed=time.monotonic()-now
 if proc.returncode:raise RuntimeError('Native owned admission command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[row.split() for row in proc.stdout.splitlines()]
 if len(actual)!=len(expected):raise AssertionError('Owned admission result count differs')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-12):j+16]} != {y[max(0,j-12):j+16]}; counts {len(x)}/{len(y)}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Owned admission source/runner changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} owned admission results / {metadata["movement_ticks"]:,} original ticks: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
