#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Process with shared actual 0/3/7 admission, gates and next-Cell."""
import argparse,copy,itertools,json,struct,subprocess,time
from pathlib import Path
import pefile
import compare_ground_drive_gate_process as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_drive_admission_process import verify
SOURCES=tuple(dict.fromkeys((*parent.SOURCES,'tests/compare_ground_drive_admission_process.py','tests/original_ground_drive_admission_process.py',
 'tools/verify_ground_drive_admission_process.py','tools/verify_unit_admission.py','tools/verify_unit_next_cell.py',
 'src/sim/TerrainOccupation.hpp','src/assets/Formats.hpp','tests/test_ground_drive_admission_process_evidence.py')))
HEADER=parent.HEADER.copy();HEADER[4]=-1
OBJECTS=copy.deepcopy(parent.OBJECTS[1:]);OBJECTS[-1][0]=6;OBJECTS[-1][2]=2
# Preserve all supplied gate fields; only the actor domain becomes ordinary Buildings.
def command(planes=None,crusher=1,**kwargs):
 kwargs.setdefault('h',HEADER);kwargs.setdefault('objects',OBJECTS)
 return 'A '+parent.command(planes,**kwargs)[2:]+' '+str(crusher)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported admission Process command')
def parse(cmd):
 p=cmd.split();require(len(p)>=227 and p[0]=='A');crusher=int(p[-1]);require(0<=crusher<=255)
 route=list(map(int,p[26:50]));require(len(route)==24 and route[-1]==-1 and all(-1<=d<=7 for d in route))
 # Legacy parsing keeps its canonical queue guard. This distinct entry permits
 # actual retained tails and validates every stored word independently.
 canonical=p[1:-1].copy();end=False
 for i,d in enumerate(route):
  if end:canonical[25+i]='-1'
  if d==-1:end=True
 v,extra,_,numeric,planes,h,houses,objects,updates=parent.parse('G '+' '.join(canonical))
 require(all(r[0]==6 and r[2]>=0 for r in objects));require(all(r[0]<v[6] for r in updates))
 return v,extra,route,numeric,planes,h,houses,objects,updates,crusher
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'render_data':hash_file(a.render_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Admission Process engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Admission Process identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Admission Process counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,AssertionError,IndexError,TypeError,OverflowError,struct.error):raise ValueError('Malformed admission Process command') from None
def generate(a):
 from original_ground_drive_admission_process import GroundDriveAdmissionProcessOracle
 o=GroundDriveAdmissionProcessOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[]
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);kwargs.setdefault('steps',48);kwargs.setdefault('pattern',0)
  cmd=command(planes,**kwargs);commands.append(cmd);expected.append(o.run(*parse(cmd)));labels.append(label)
 for d,crusher,resident in itertools.product(range(8),(0,1,255),(0,1)):
  add('actual_shared_admission_zero_and_next_Cell_all_directions',route=(d,d,d),heading=d<<13,crusher=crusher,resident=resident)
 for first,second in itertools.product(range(8),repeat=2):
  add('actual_admission_all_queued_pairs_and_ordinary_curves',route=(first,second,second),heading=first<<13,ramp=0,steps=128)
 for second,code in itertools.product((False,True),(3,7)):
  for heading,updates_at in itertools.product((0,16384),(None,5)):
   h=HEADER.copy();h[2]=72*512+51;h[3]=73*512+52;h[4 if not second else 5]=1
   objects=copy.deepcopy(OBJECTS);objects[0][2:5]=[1,1,24];objects[0][7:9]=[0,1]
   if code==3:
    objects[0][1]=2;objects[1][2:5]=[0,1,2];objects[1][7:9]=[0,0]
   else:objects[0][2:5]=[0,0,2]
   updates=[] if updates_at is None else [(updates_at,2 if code==3 else 1,0,1)]
   add('distinct_first_and_second_admission_3_7_and_supplied_opening',h=h,objects=objects,route=(2,3,3),heading=heading,updates=updates)
  add('retained_nonzero_head_clear_order_on_actual_blocked_admission',h=h,objects=objects,route=(2,3,3),track=18,steps=3)
 for heading in (0,16384):
  h=HEADER.copy();h[3]=73*512+52;h[5]=1
  objects=copy.deepcopy(OBJECTS);objects[0][2:5]=[0,1,24];objects[0][7:9]=[0,0]
  add('second_admission3_ignores_false_repeated_gate_result',h=h,objects=objects,heading=heading,route=(2,3,3))
 for route in ((2,-1,4,5),(2,3,-1,4,5,6,7),(2,2,-1,7,6,5,4),tuple([2,3,-1,*[i%8 for i in range(19)],7])):
  add('retained_queue_words_after_sentinel_one_and_two_step_consumption',route=route,steps=4)
 for land_speed in (0.,-0.,0.5,1.,1.5):
  add('actual_land_speed_rejection_and_accepted_speed',land_speed=land_speed,route=(2,2,2),steps=8)
 for ramp in range(21):add('actual_admission_and_warning1_all_flat_level_ramps',ramp=ramp,initial_ramp=(ramp+1)%21,steps=32)
 for level in (-126,-5,-1,0,1,125):add('signed_admission_level_from_original_Cells',level=level,steps=4)
 for tick,padding,mode in itertools.product((-2147483648,-1,2147483640),(-1515870811,0,2147483647),range(4)):
  h=HEADER.copy();h[0]=padding;h[4]=1;objects=copy.deepcopy(OBJECTS);objects[0][3]=0
  add('result7_retained_tails_signed_clock_and_four_FP_modes',h=h,objects=objects,tick=tick,mode=mode,steps=3)
 for route in ((2,3,3),(2,1,1),(2,2,2,2,2,2),(2,3,4,4),(2,3,2,2),(2,1,0,0)):
  add('Advance_completion_and_both_Process_preparation_callers',route=route,steps=160)
 add('zero_world_point_remains_the_original_head_sentinel',x=-256,y=0,z=0,hx=256,hy=0,hz=0,level=0,ramp=0,route=(2,2),steps=4)
 for d in range(8):
  dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[d]
  h=HEADER.copy();h[2]=(72+dy)*512+50+dx;h[3]=-1;h[4]=1
  objects=copy.deepcopy(OBJECTS);objects[0][2:5]=[0,1,24];objects[0][7:9]=[0,0]
  add('initial_gate_wait_then_actual_admission_and_next_Cell',h=h,objects=objects,route=(d,d,d),heading=d<<13,updates=[(3,1,0,1)],steps=64)
 require(all(o.returns.values()) and o.next_calls and o.callers['0x4a34eb'] and o.callers['0x4a40e4'] and o.callers['0x4a35f9'] and o.callers['0x4a416f'] and o.callers['0x4a4513'] and o.callers['0x4a45a5'])
 if not(o.actor_byte_checks==o.roots and o.zero_head_speed_calls and len(o.admission_caller_returns)==3 and o.callers['0x4a1c99'] and all(o.retry_gate_returns.values())):
  raise ValueError(f'Missing original coverage: callers={o.callers}, returns={o.admission_caller_returns}, retry_gates={o.retry_gate_returns}, zero_head={o.zero_head_speed_calls}, actor_checks={o.actor_byte_checks}/{o.roots}')
 return commands,expected,labels,{'audited_complete_Process_roots':o.roots,'actual_entries':o.entries,'entered_distinct_instructions':len(o.instructions),
  'actual_admission_returns':o.returns,'actual_next_Cell_calls':o.next_calls,'selected_caller_instruction_counts':o.callers,'selected_decision_stores':o.decision_stores,
  'actual_admission_returns_by_caller':o.admission_caller_returns,'actual_zero_head_speed_setter_calls':o.zero_head_speed_calls,'actual_actor57a_state_checks':o.actor_byte_checks,
  'retry_gate_returns':o.retry_gate_returns,'supplied_retry_padding_words':o.supplied_retry_padding,
  'initial_records_associations_and_Mark_occupation_notification_mission_pathfinder_supplied':True,'runtime_unwired':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-drive-process-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-drive-admission-process-v2');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh admission Process destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.exe),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native admission Process: '+proc.stderr.strip())
 actual=[line.split() for line in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Admission Process counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'Admission Process {i} {labels[i]} token{j}: {x[max(0,j-12):j+16]} != {y[max(0,j-12):j+16]}; counts {len(x)}/{len(y)}; {commands[i]}')
 safety=['','A 0',command()+' trailing',command(crusher=256),command(route=(2,-1,8)),command(steps=2,updates=[(2,1,0,1)])]
 h=HEADER.copy();h[3]=74*512+52;h[5]=1
 for gate in (0,1):
  objects=copy.deepcopy(OBJECTS);objects[0][2:5]=[0,gate,24];objects[0][7:9]=[0,0]
  safety.append(command(h=h,objects=objects,route=(2,3,4,4),ramp=0,steps=160,pattern=0))
 for i,cmd in enumerate(safety):
  r=subprocess.run([str(a.native),str(a.exe),str(a.render_data)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Admission Process refusal missing')
  if i>=6 and 'switch admission requires zero result' not in r.stderr:raise AssertionError('Wrong Advance switch refusal: '+r.stderr)
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Admission Process run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,
  'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} admission Process results / {metadata["audited_complete_Process_roots"]:,} original ticks: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
