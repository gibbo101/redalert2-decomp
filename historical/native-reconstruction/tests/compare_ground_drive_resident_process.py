#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Process with actual stationary Unit admission and result-6 retry."""
import argparse,copy,itertools,json,struct,subprocess,time
from pathlib import Path
import pefile
import compare_ground_drive_gate_process as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_drive_resident_process import verify
from compare_ground_drive_admission_process import SOURCES as ADMISSION_SOURCES
SOURCES=tuple(dict.fromkeys((*ADMISSION_SOURCES,'tests/compare_ground_drive_resident_process.py','tests/original_ground_drive_resident_process.py',
 'tools/verify_ground_drive_resident_process.py','tools/verify_unit_admission.py','tools/verify_unit_next_cell.py',
 'src/sim/TerrainOccupation.hpp','src/assets/Formats.hpp','tests/test_ground_drive_resident_process_evidence.py')))
# Keep the earlier parser and its Building-only domain unchanged.
HEADER=parent.HEADER.copy();HEADER[4]=-1
OBJECTS=copy.deepcopy(parent.OBJECTS[1:]);OBJECTS[-1][0]=6;OBJECTS[-1][2]=2
def command(planes=None,crusher=1,first_padding=19,second_padding=-23,resident_flags=1,**kwargs):
 kwargs.setdefault('h',HEADER);kwargs.setdefault('objects',OBJECTS)
 return 'R '+parent.command(planes,**kwargs)[2:]+' '+str(crusher)+' '+str(first_padding)+' '+str(second_padding)+' '+str(resident_flags)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported resident Process command')
def parse(cmd):
 p=cmd.split();require(len(p)>=230 and p[0]=='R')
 padding=list(map(int,p[-3:-1]));require(all(-2147483648<=n<=2147483647 for n in padding))
 flags=int(p[-1]);require(flags in (1,5))
 normalized=p[:-3];normalized[0]='A'
 for i in range(4):
  at=169+14*i;require(int(p[at]) in (1,6));normalized[at]='6'
 from compare_ground_drive_admission_process import parse as old_parse
 result=list(old_parse(' '.join(normalized)))
 for i,row in enumerate(result[7]):row[0]=int(p[169+14*i])
 return (*result,*padding,flags)
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'render_data':hash_file(a.render_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Resident Process engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Resident Process identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Resident Process counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,AssertionError,IndexError,TypeError,OverflowError,struct.error):raise ValueError('Malformed resident Process command') from None
def generate(a):
 from original_ground_drive_resident_process import GroundDriveResidentProcessOracle
 o=GroundDriveResidentProcessOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[]
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);kwargs.setdefault('steps',48);kwargs.setdefault('pattern',0)
  cmd=command(planes,**kwargs);commands.append(cmd);expected.append(o.run(*parse(cmd)));labels.append(label)
 for d,mode in itertools.product(range(8),range(4)):
  dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[d]
  # Diagonal continuation uses one Cell; use a cardinal-to-diagonal curve
  # for actual second admission coverage separately below.
  h=HEADER.copy();h[2]=(72+dy)*512+50+dx;h[4]=1
  objects=copy.deepcopy(OBJECTS);objects[0][0]=1;objects[0][1]=-1;objects[0][2]=0
  objects[0][3]=0;objects[0][4]=2
  add('stationary_allied_first_admission6_all_directions_and_FP_modes',h=h,objects=objects,route=(d,d,d),heading=d<<13,mode=mode,steps=4)
 for second,tick,pad,mode in itertools.product((False,True),(-2147483648,-1,2147483646),(-1515870811,0,2147483647),range(4)):
  h=HEADER.copy();h[2]=72*512+51;h[3]=73*512+52;h[4 if not second else 5]=1
  objects=copy.deepcopy(OBJECTS);objects[0][0]=1;objects[0][1]=-1;objects[0][2:5]=[0,0,2]
  add('distinct_first_second_admission6_signed_clock_padding_retained_tail',h=h,objects=objects,route=(2,3,-1,4,5,6),heading=16384,tick=tick,mode=mode,first_padding=pad,second_padding=~pad,steps=4)
 for track,heading in itertools.product((-1,18),(0,16384)):
  h=HEADER.copy();h[4]=1
  objects=copy.deepcopy(OBJECTS);objects[0][0]=1;objects[0][1]=-1;objects[0][2:5]=[0,0,2]
  add('occupied_first_retry_with_retained_nonzero_head_or_initial_turn',h=h,objects=objects,route=(2,2,2),track=track,heading=heading,steps=48)
 for route in ((2,2,2,2),(2,3,3),(2,1,1)):
  h=HEADER.copy();h[2]=72*512+53;h[3]=73*512+54;h[4]=1;h[5]=1
  objects=copy.deepcopy(OBJECTS);objects[0][0]=1;objects[0][1]=-1;objects[0][2:5]=[0,0,2]
  add('empty_Cell_movement_then_stationary_Unit_at_later_preparation',h=h,objects=objects,route=route,steps=160,ramp=0)
 for resident in (0,1):
  h=HEADER.copy();h[6]=1
  objects=copy.deepcopy(OBJECTS);objects[0][0]=1;objects[0][1]=-1;objects[0][2:5]=[0,0,2]
  add('canonical_resident_and_shared_fallback_occupied_identity',h=h,objects=objects,route=(2,2,2),resident=resident,steps=4)
 for flags,head,owner,land_speed in itertools.product((1,5),(0,1,2),(0,1),(0.,1.)):
  h=HEADER.copy();h[4]=head
  objects=copy.deepcopy(OBJECTS)
  for r in objects:r[0]=1;r[1]=-1;r[2:5]=[owner,0,2]
  objects[1][1]=1
  houses=[[0,3],[1,3],[2,0]]
  add('settled_Facing_Drive_self_skip_shared_Unit_list_and_allied_House',h=h,houses=houses,objects=objects,route=(2,-1,4,5),heading=16384,resident_flags=flags,land_speed=land_speed,steps=4)
 require(o.returns[6] and all(o.resident_loads.values()) and all(o.resident_paths.values()))
 require(all(o.preparation_flags.get(k,0)>0 for k in ('0x4a0739:1','0x4a0b75:1','0x4a4518:0')))
 require(all(o.resident_Process_callers.get(k,0)>0 for k in ('0x4a0739','0x4a0b75')) and o.nonzero_head_first_retries)
 return commands,expected,labels,{'audited_complete_Process_roots':o.roots,'actual_entries':o.entries,'entered_distinct_instructions':len(o.instructions),
  'actual_admission_returns':o.returns,'actual_next_Cell_calls':o.next_calls,'selected_caller_instruction_counts':o.callers,'selected_decision_stores':o.decision_stores,
  'actual_admission_returns_by_caller':o.admission_caller_returns,'actual_zero_head_speed_setter_calls':o.zero_head_speed_calls,'actual_actor57a_state_checks':o.actor_byte_checks,
  'retry_gate_returns':o.retry_gate_returns,'supplied_retry_padding_words':o.supplied_retry_padding,
  'preparation_flags':o.preparation_flags,'resident_result6_by_Process_caller':o.resident_Process_callers,'nonzero_head_first_retries':o.nonzero_head_first_retries,'resident_retry_loads':o.resident_loads,'resident_paths':o.resident_paths,'stationary_record_checks':o.stationary_checks,'initial_records_associations_and_Mark_occupation_notification_mission_pathfinder_supplied':True,'runtime_unwired':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-drive-process-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-drive-resident-process-v4');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh resident Process destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.exe),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native resident Process: '+proc.stderr.strip())
 actual=[line.split() for line in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Resident Process counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'Resident Process {i} {labels[i]} token{j}: {x[max(0,j-12):j+16]} != {y[max(0,j-12):j+16]}; counts {len(x)}/{len(y)}; {commands[i]}')
 safety=['','R 0',command()+' trailing',command(crusher=256),command(route=(2,-1,8)),command(first_padding=2147483648)]
 h=HEADER.copy();h[3]=74*512+52;h[5]=1
 objects=copy.deepcopy(OBJECTS);objects[0][0]=1;objects[0][1]=-1;objects[0][2:5]=[0,0,2]
 safety.append(command(h=h,objects=objects,route=(2,3,4,4),ramp=0,steps=160,pattern=0))
 for i,cmd in enumerate(safety):
  r=subprocess.run([str(a.native),str(a.exe),str(a.render_data)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Resident Process refusal missing')
  if i==6 and ('switch admission requires zero result' not in r.stderr or r.stdout.split()[-3:]!=['a','r','6']):
   raise AssertionError('Wrong resident Advance result/refusal: '+r.stderr)
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Resident Process run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,
  'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} resident Process results / {metadata["audited_complete_Process_roots"]:,} original ticks: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
