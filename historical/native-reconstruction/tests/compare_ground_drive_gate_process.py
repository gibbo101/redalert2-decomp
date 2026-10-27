#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Process with actual result-bearing gate children."""
import argparse,configparser,copy,itertools,json,struct,subprocess,time
from pathlib import Path
import pefile
import compare_ground_drive_process as parent
from compare_movement_gate import HOUSES,OBJECTS
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_drive_gate_process import verify
HEADER=[-1515870811,7,72*512+51,72*512+52,0,-1,0,0,1]
SOURCES=tuple(dict.fromkeys((*parent.SOURCES,'tests/GroundDriveGateVectors.hpp',
 'src/sim/MovementGate.hpp','src/sim/MovementGate.cpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp',
 'tests/original_ground_drive_gate_process.py','tests/compare_ground_drive_gate_process.py',
 'tests/compare_movement_gate.py',
 'tests/test_ground_drive_gate_process_evidence.py','tools/verify_ground_drive_gate_process.py','tools/verify_movement_gate.py')))
def command(planes=None,h=None,houses=None,objects=None,updates=(),**kwargs):
 return 'G '+parent.command(planes,**kwargs)[2:]+' '+' '.join(map(str,[*(HEADER if h is None else h),
  *itertools.chain.from_iterable(HOUSES if houses is None else houses),
  *itertools.chain.from_iterable(OBJECTS[1:] if objects is None else objects),len(updates),*itertools.chain.from_iterable(updates)]))
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported gate Process command')
def parse(cmd):
 p=cmd.split();require(len(p)>=226 and p[0]=='G')
 v,extra,route,numeric,planes=parent.parse('P '+' '.join(p[1:154]));raw=list(map(int,p[154:225]))
 h=raw[:9];houses=[raw[i:i+2] for i in range(9,15,2)];objects=[raw[i:i+14] for i in range(15,71,14)]
 i32=lambda n:-2147483648<=n<=2147483647;id_=lambda n:-1<=n<5;byte=lambda n:0<=n<=255
 require(all(i32(n) for n in h[:2]) and all(-1<=n<262144 for n in h[2:4]) and (h[2]==-1 or h[2]!=h[3]) and all(id_(n) for n in h[4:7]) and 0<=h[7]<=2 and id_(h[8]))
 require(all(i32(index) and 0<=mask<1<<32 for index,mask in houses))
 for r in objects:
  require(r[0] in (6,36) and id_(r[1]) and -1<=r[2]<=2 and all(byte(r[i]) for i in (3,6,7,8)) and all(i32(n) for n in r[4:6]+r[9:]) and not(r[0]==6 and r[3] and r[2]==-1))
 links=[h[8],*[r[1] for r in objects]]
 for i in range(5):
  seen=set()
  while i!=-1:require(i not in seen);seen.add(i);i=links[i]
 count=int(p[225]);require(0<=count<=128 and len(p)==226+4*count);updates=[]
 for i in range(226,len(p),4):
  row=list(map(int,p[i:i+4]));require(0<=row[0]<v[6] and 1<=row[1]<5 and all(byte(n) for n in row[2:]));updates.append(row)
 return v,extra,route,numeric,planes,h,houses,objects,updates
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'owned_rules':{str(a.rules.resolve()):hash_file(a.rules)},'render_data':hash_file(a.render_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Gate Process engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Gate Process identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Gate Process counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,AssertionError,IndexError,TypeError,OverflowError,struct.error):raise ValueError('Malformed gate Process command') from None
def generate(a):
 from original_ground_drive_gate_process import GroundDriveGateProcessOracle
 o=GroundDriveGateProcessOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 rules=configparser.ConfigParser(strict=False,interpolation=None,allow_no_value=True,inline_comment_prefixes=(';',));rules.read(a.rules,encoding='latin1')
 if rules.get('HTNK','Accelerates',fallback=None)!='false' or rules.get('HTNK','IsTrain',fallback=None) is not None or rules.getboolean('HTNK','Passive',fallback=False):raise ValueError('Owned ordinary Rhino inputs changed')
 commands=[];expected=[];labels=[]
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);kwargs.setdefault('steps',40);kwargs.setdefault('pattern',0)
  cmd=command(planes,**kwargs);commands.append(cmd);expected.append(o.run(*parse(cmd)));labels.append(label)
 for b18,b19,mission,owner,heading in itertools.product((0,1,255),(0,1,2,255),(2,24),(0,1),(16384,0)):
  objects=copy.deepcopy(OBJECTS[1:]);objects[0][2]=owner;objects[0][4]=mission;objects[0][7:9]=[b18,b19]
  add('complete_Process_gate_return_precedes_turn_admission_and_track_commitment',objects=objects,heading=heading)
 for d,open_at,resident in itertools.product(range(8),(0,3,17),(0,1)):
  # Stock initialized direction table: ordinal zero is north in map coordinates.
  dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[d]
  h=HEADER.copy();h[2]=(72+dy)*512+50+dx;h[3]=-1
  objects=copy.deepcopy(OBJECTS[1:]);objects[0][4]=24;objects[0][7:9]=[0,0]
  add('wait_then_supplied_animation_completion_all_queued_directions_and_fallback',h=h,objects=objects,route=(d,d,d),heading=d<<13,resident=resident,updates=[(open_at,1,0,1)],steps=80)
 for route in ((2,2,2),(2,3,3),(2,1,1),(2,2,2,2,2,2)):
  h=HEADER.copy();h[5]=2;objects=copy.deepcopy(OBJECTS[1:]);objects[0][4]=24;objects[0][7:9]=[0,1];objects[1][2:5]=[0,1,24];objects[1][7:9]=[0,0]
  add('committed_Advance_then_gate_wait_at_following_preparation_caller',h=h,objects=objects,route=route,steps=192,updates=[(70,2,0,1)])
 for links,head,enemy_open in itertools.product(((1,2,-1,-1,-1),(4,-1,-1,1,3),(3,-1,-1,1,-1)),(0,3,4),(0,1)):
  h=HEADER.copy();h[4]=head;h[8]=links[0];objects=copy.deepcopy(OBJECTS[1:])
  for i,r in enumerate(objects,1):r[1]=links[i]
  objects[2][4]=24 if enemy_open else 2;objects[2][7:9]=[0,enemy_open]
  add('shared_primary_list_self_skip_Terrain36_and_enemy_open_early_return',h=h,objects=objects)
 for tick,pad1,pad2,mode in itertools.product((-2147483648,-1,2147483640),(-1515870811,0,2147483647),(0,7),range(4)):
  h=HEADER.copy();h[:2]=[pad1,pad2]
  add('actual_mission_store_order_signed_clock_and_four_incoming_FP_modes',h=h,tick=tick,mode=mode,updates=[(3,1,0,1)],steps=24)
 for resident,x,y in itertools.product((0,1),(-257,-1,50*256+128),(72*256+128,1)):
  add('combined_signed_lookup_and_shared_fallback_forwarding',resident=resident,x=x,y=y,hx=x+256,hy=y,steps=16)
 for ramp in range(21):
  add('all_terrain_ramps_with_gate_wait_and_supplied_opening',ramp=ramp,initial_ramp=(ramp+1)%21,updates=[(3,1,0,1)],steps=80)
 for left,right,mask in itertools.product((-1,0,33),(-1,1),(0,1,0xffffffff)):
  houses=copy.deepcopy(HOUSES);houses[0][0]=left;houses[1]=[right,mask]
  objects=copy.deepcopy(OBJECTS[1:]);objects[0][2]=1
  add('result_bearing_caller_signed_House_indices_and_alliance_masks',houses=houses,objects=objects,steps=12)
 for speed,dest,route in itertools.product((0,15),(0,1),((),(2,2))):
  add('zero_speed_empty_queue_and_absent_destination_do_not_force_gate_work',speed=speed,dest=dest,route=route,steps=8)
 require(all(o.gate_returns.values()) and all(o.kind_returns.values()) and all(o.locations.values()) and o.false_snapshots==o.gate_returns[0])
 return commands,expected,labels,{'audited_complete_Process_roots':o.roots,'actual_entries':o.entries,'gate_returns':o.gate_returns,
  'selected_caller_instruction_counts':o.locations,'false_gate_protected_record_checks':o.false_snapshots,
  'actual_gate_stores':o.gate_stores,'supplied_gate_padding_stores':o.padding_stores,'supplied_animation_changes':o.animation_changes,
  'kind_return_checks':o.kind_returns,'entered_distinct_instructions':len(o.instructions),
  'initial_records_admission_next_Cell_Mark_occupation_notification_mission_pathfinder_supplied':True,
  'gate_animation_progression_prepared_map_runtime_startup_frames_unverified':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets/rules.ini')
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-drive-process-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-drive-gate-process-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh gate Process destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.exe),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError(f'Native gate Process at {len(proc.stdout.splitlines())}: {proc.stderr.strip()}')
 actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected));elapsed=time.monotonic()-now
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'Gate Process {i} {labels[i]} token {j}: {x[max(0,j-10):j+16]} != {y[max(0,j-10):j+16]}; counts {len(x)}/{len(y)}; {commands[i]}')
 safety=['','G 0',command()+' trailing',command(updates=[(128,1,0,1)]),command(updates=[(0,0,0,1)]),command(heading=65536)]
 for cmd in safety:
  r=subprocess.run([str(a.native),str(a.exe),str(a.render_data)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Native gate Process refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Gate Process run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} gate Process sequences / {result["audited_complete_Process_roots"]:,} calls: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
