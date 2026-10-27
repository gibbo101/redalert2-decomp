#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare shared owned mover/parked-Unit effects with unchanged original routines."""
import json,struct,subprocess,time
import compare_owned_unit_admission as parent
import compare_runtime_membership as runtime
import compare_prepared_foot_depth as prepared
import compare_resident_map_floor as floor
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_owned_unit_resident import verify
SOURCES=tuple(dict.fromkeys((*parent.SOURCES,'tests/original_owned_unit_resident.py',
 'tests/compare_owned_unit_resident.py','tools/verify_owned_unit_resident.py',
 'tools/verify_ground_drive_resident_process.py','tests/test_owned_unit_resident_evidence.py')))
def command(parked_at=(3200,3200,37),parked_heading=0,first_padding=19,second_padding=-23,order=0,**kwargs):
 return 'R '+parent.command(**kwargs)[2:]+' '+' '.join(map(str,(*parked_at,parked_heading,first_padding,second_padding,order)))
def parse(cmd):
 if cmd.startswith('P '):return parent.parse(cmd)
 p=cmd.split()
 if len(p)!=53 or p[0]!='R':raise ValueError('Malformed owned resident command')
 values=list(map(int,p[-7:]));at=values[:3];heading,first,second,order=values[3:]
 if any(not -2147483648<=n<=2147483647 for n in (*at,first,second)) or not 0<=heading<=65535 or order not in (0,1):
  raise ValueError('Owned resident records outside domain')
 _,old=parent.parse('A '+' '.join(p[1:-7]))
 return 'R',(*old,at,heading,first,second,order)
def identities(a):
 return {'production':runtime.identities(a),'inspection':verify(a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Owned resident engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Owned resident identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Owned resident counts differ')
 ready=False
 for cmd in e['commands']:
  try:op,_=parse(cmd)
  except (ValueError,AssertionError,IndexError,TypeError,OverflowError,struct.error):raise ValueError('Malformed owned resident command') from None
  if op=='P':ready=True
  elif not ready:raise ValueError('Owned resident requires a prepared map')
def generate(a,ramps=range(21),owned=True,focus=False):
 from original_owned_unit_resident import OwnedUnitResidentOracle
 o=OwnedUnitResidentOracle(a.exe);source=json.loads(a.depth_fixture.read_text());commands=[];expected=[];labels=[];ticks=0
 def save(label,cmd,result):
  parse(cmd);commands.append(cmd);expected.append(list(map(str,result)));labels.append(label)
 def prepare(f,label):save(label,'P '+floor.command(*f[:5],f[5:]),o.prepare_map(f));print(label,flush=True)
 def move(label,**kwargs):
  nonlocal ticks
  kwargs.setdefault('at',(2944,3200,37));kwargs.setdefault('destination',(3968,3200,0));kwargs.setdefault('heading',16384)
  kwargs.setdefault('mode',len(commands)%4);cmd=command(**kwargs);_,values=parse(cmd)
  save(label,cmd,o.run_resident(*values));ticks+=values[0][10];print(label,ticks,'ticks',flush=True)
 template,_=prepared.parse(source['commands'][3]);common=list(template[5]);common[:5]=[12,12,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 for ramp in ramps:
  types=[[1,1,1,60,30,1,0,0,0,0,0],[1,1,1,60,30,1,0,ramp,0,0,0]]
  cells=[[x,y,int(x==12),0,0,0,-1,0,0,0,0,0,17,91,-1,41,0] for y in range(25) for x in range(25)
   if x+y>12 and abs(x-y)<12 and x+y<=36]
  f=(*template[:5],common,[12,0,0,12,12],types,cells,[],[],template[11],[])
  prepare(f,f'shared_Units_ramp_{ramp}')
  move('parked_first_target_actual_membership_and_result6_retry',parked_at=(3200,3200,-31),route=(2,-1,4,5),steps=8)
  move('parked_second_target_actual_membership_and_distinct_retry',parked_at=(3456,3456,77),route=(2,3,-1,4,5),steps=8)
  if ramp==0:
   for order in (0,1):
    move('shared_initial_Cell_Next_and_ordered_whole_occupation_effects',parked_at=(2944,3200,-77),route=(2,2,2),steps=96,order=order)
   if not focus:
    for d in range(8):
     dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[d]
     for mode in range(4):move('eight_directions_FP_modes_and_allied_resident',parked_at=(2944+256*dx,3200+256*dy,37),
      destination=(2944+512*dx,3200+512*dy,0),heading=d<<13,route=(d,d),steps=8,mode=mode)
    move('empty_movement_before_later_parked_Unit',parked_at=(3712,3200,-101),route=(2,2,2,2),steps=160)
    move('turn_before_stationary_admission',parked_at=(3200,3200,0),route=(2,2),heading=0,steps=64)
    for mode in range(4):
     move('zero_Track_speed_overrides_allied_resident',parked_at=(3200,3200,0),route=(2,-1,4,5),steps=16,mode=mode,numeric=(1.,0.,.7,1.2))
     move('signed_tick_and_distinct_timer_words',parked_at=(3200,3200,0),route=(2,-1,4,5),steps=8,mode=mode,
      tick=2147483646,first_padding=-2147483648,second_padding=2147483647)
 if owned:
  f,_=prepared.parse(source['commands'][0]);prepare(f,'owned_original_map_shared_13515_Cells')
  for mode in range(4):
   move('owned_level_crossing_then_parked_Unit',at=(22144,25984,31),destination=(23680,25984,0),
    parked_at=(23168,25984,-500),route=(2,)*6,steps=160,mode=mode)
 if not o.admission_returns.get(6) or not all(o.retry_loads.values()) or o.actual_actor57a_checks!=ticks:
  raise AssertionError('Missing actual shared resident retry coverage')
 return commands,expected,labels,{'movement_ticks':ticks,'complete_Process_calls':o.roots,'actual_entries':o.all_entries,
  'actual_admission_returns':o.admission_returns,'admission_callers':{hex(k):v for k,v in o.callers.items()},
  'actual_gate_returns':o.gate_returns,'actual_next_Cell_calls':o.next_calls,'actual_self_skip_entries':o.self_skips,
  'selected_preparation_stores':o.preparation_stores,'supplied_retry_padding_words':o.supplied_retry_words,
  'actual_actor57a_state_checks':o.actual_actor57a_checks,'actual_Mark_calls':o.actual_marks,'actual_recalculations':o.actual_recalculations,
  'actual_eligible_unmarks':o.eligible_unmarks,'selected_membership_effect_stores':o.effect_stores,'body_shadow_pose_calls':o.pose_calls,
  'parked_initializations':o.parked_initializations,'parked_selected_stores':o.parked_stores,'parked_arena_checks':o.parked_stability_checks,
  'resident_retry_loads':o.retry_loads,'preparation_flags':o.preparation_flags,'coverage':o.coverage,
  'entered_distinct_instructions':len(o.instructions),'two_Units_share_actual_owned_map_and_membership':True,
  'initial_records_associations_padding_and_other_mission_pathfinder_services_supplied':True,'runtime_unwired':True}
def main():
 a=runtime.arguments()
 if a.output==ROOT/'private/map-depth-1006/runtime-membership-v1':a.output=ROOT/'private/map-depth-1006/owned-unit-resident-v2'
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh owned resident destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run(parent.member.native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True);elapsed=time.monotonic()-now
 if proc.returncode:raise RuntimeError('Native owned resident command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[row.split() for row in proc.stdout.splitlines()]
 if len(actual)!=len(expected):raise AssertionError('Owned resident result count differs')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-12):j+16]} != {y[max(0,j-12):j+16]}; counts {len(x)}/{len(y)}')
 safety=['','R 0',command()+' trailing',command(order=2),
  command(at=(2944,3200,37),destination=(3968,3200,0),heading=16384,parked_at=(3456,3712,0),route=(2,3,4,4),steps=160)]
 for i,cmd in enumerate(safety):
  r=subprocess.run(parent.member.native_args(a),input=commands[0]+'\n'+cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Owned resident safety refusal missing')
  if i==4 and ('switch admission requires zero result' not in r.stderr or r.stdout.split()[-5:]!=['a','d','6','0','0']):
   raise AssertionError('Wrong original-domain Advance6 refusal: '+r.stderr+' '+repr(r.stdout.split()[-15:]))
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Owned resident source/runner changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
  'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} owned resident results / {metadata["movement_ticks"]:,} original ticks: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
