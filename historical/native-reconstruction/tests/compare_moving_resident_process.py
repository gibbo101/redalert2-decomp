#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary Process with actual moving Unit result-2 wait callers."""
import argparse,copy,itertools,json,struct,subprocess,time
from pathlib import Path
import pefile
import compare_ground_drive_resident_process as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_moving_resident_process import verify
from compare_moving_unit_admission import SOURCES as MOTION_SOURCES
SOURCES=tuple(dict.fromkeys((*parent.SOURCES,*MOTION_SOURCES,
 'tests/compare_moving_resident_process.py','tests/original_moving_resident_process.py',
 'tests/GroundDriveMovingResidentVectors.hpp','tools/verify_moving_resident_process.py',
 'tests/test_moving_resident_process_evidence.py')))
MOTION=[[14000+i*512,18560,0,16000,18560,0,0,0,0,16384,16384,-1,0,1280,1,-1,0,0,0] for i in range(4)]
WAIT=[0,-1,11,0,10,-17,-1,7,0]
def default_objects():
 objects=copy.deepcopy(parent.OBJECTS)
 for o in objects:o[0]=1;o[1]=-1;o[2:5]=[0,0,2]
 return objects
def command(planes=None,motion=None,wait=None,second=False,**kw):
 h=parent.HEADER.copy();h[2]=72*512+51;h[3]=73*512+52;h[4]= -1 if second else 1;h[5]=1 if second else -1
 kw.setdefault('h',h);kw.setdefault('objects',default_objects());kw.setdefault('pattern',0);kw.setdefault('ramp',0)
 kw.setdefault('steps',4);kw.setdefault('route',(2,3,-1,4,5));kw.setdefault('resident_flags',5)
 cmd=parent.command(planes,**kw)
 rows=MOTION if motion is None else motion;timer=WAIT if wait is None else wait
 return 'M '+cmd[2:]+' '+' '.join(map(str,[*itertools.chain.from_iterable(rows),*timer]))
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported moving-resident Process command')
def parse(cmd):
 p=cmd.split();require(len(p)>=315 and p[0]=='M')
 rows=list(map(int,p[-85:-9]));wait=list(map(int,p[-9:]));require(len(rows)==76)
 require(all(-2147483648<=n<=2147483647 for n in [*rows,*wait]))
 motion=[rows[i:i+19] for i in range(0,76,19)]
 for row in motion:
  require(all(0<=row[i]<=65535 for i in (9,10,13)) and 0<=row[14]<=255 and 0<=row[16]<64 and 0<=row[18]<=255)
 require(0<=wait[0]<=255)
 base=parent.parse('R '+' '.join(p[1:-85]));require(all(row[0]==1 for row in base[7]))
 return (*base,motion,wait)
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'render_data':hash_file(a.render_data),'direction_data':hash_file(a.direction_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Moving-resident Process engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Moving-resident Process identity differs')
 if not e['evidence'].get('complete_Process_and_actual_moving_children'):raise ValueError('Moving-resident Process join differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Moving-resident Process counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,AssertionError,IndexError,TypeError,OverflowError,struct.error):raise ValueError('Malformed moving-resident Process command') from None
def generate(a):
 from original_moving_resident_process import MovingResidentProcessOracle
 o=MovingResidentProcessOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];options={1:0,2:0};preparations={};per_case=[]
 def add(label,required_caller='0x4a34f1',required_code=2,required_option=None,recursive=False,**kw):
  kw.setdefault('mode',len(commands)%4);cmd=command(planes,**kw)
  before=o.admission_caller_returns.get(required_caller,{}).get(required_code,0);at=len(o.pathfinderOptions)
  expected.append(o.run(*parse(cmd)));commands.append(cmd);labels.append(label)
  if required_code is not None:require(o.admission_caller_returns.get(required_caller,{}).get(required_code,0)>before)
  measured=o.pathfinderOptions[at:]
  if required_option is not None:require(required_option in measured)
  if recursive:require(('0x4a41df',1,1) in o.preparationArguments)
  for option in measured:options[option]+=1
  for caller,flag,third in o.preparationArguments:
   key=f'{caller}:{flag}:{third}';preparations[key]=preparations.get(key,0)+1
  per_case.append({'required_caller':required_caller,'required_code':required_code,'actual_pathfinder_options':measured,
   'actual_preparation_arguments':o.preparationArguments.copy()})
 add('first2_start_wait',required_option=1)
 add('first2_expired_wait',wait=[1,90,11,5,10,-17,-1,7,0],required_option=2)
 add('first2_retry_nonzero',wait=[0,-1,11,0,10,-17,100,7,8])
 add('second2_force_single',second=True,required_caller='0x4a40ea',recursive=True)
 h=parent.HEADER.copy();h[2:6]=[72*512+53,73*512+54,1,-1]
 add('first2_after_complete_Advance',h=h,route=(2,2,2,2),steps=160)
 require(any(row[0]=='0x4a0739' for row in o.preparationArguments))
 h=parent.HEADER.copy();h[2:6]=[72*512+51,74*512+52,-1,1]
 add('actual_Advance2_before_nonPassive_rejection',h=h,route=(2,3,4,4),steps=160,required_caller='0x4a1c9f')
 for tick in (-2147483648,-1,2147483647):
  for start,duration in ((-1,0),(-1,-1),(100,0),(2147483646,4),(-2147483648,4)):
   add('signed_wait_clock_start_and_duration',tick=tick,wait=[1,start,11,duration,10,-17,-1,7,0])
 for d,mode in itertools.product(range(8),range(4)):
  dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[d]
  h=parent.HEADER.copy();h[2]=(72+dy)*512+50+dx;h[4]=1
  add('first2_all_directions_and_FP_modes',h=h,route=(d,d,-1,4,5),heading=d<<13,mode=mode)
 for flag,mode,timer in itertools.product((0,1,255),range(4),(
  (-2147483648,-1,0,-1,0),(-1,2147483646,4,-1,0),(2147483647,-2147483648,4,-1,0),
  (100,90,5,-1,0),(100,-1,-1,-1,0),(100,90,20,100,8),(100,-1,10,-1,-1),(100,99,4,98,1))):
  tick,start,duration,retryStart,retryDuration=timer
  add('wait_initialization_retention_signed_retry_and_incoming_FP',tick=tick,mode=mode,
   wait=[flag,start,-1515870811,duration,duration,2147483647,retryStart,-2147483648,retryDuration])
 for flags,kind in itertools.product((1,5),('destinationZ','headXY','headZonly','turn')):
  rows=copy.deepcopy(MOTION);rows[0][3:9]=[0]*6
  if kind=='destinationZ':rows[0][3:6]=[0,0,1]
  if kind=='headXY':rows[0][6:9]=[rows[0][0]+1,rows[0][1],0]
  if kind=='headZonly':rows[0][6:9]=[*rows[0][:2],1]
  if kind=='turn':rows[0][9:14]=[32768,16384,100,40,1280]
  add('actual_activity_before_result2_or_stationary6',motion=rows,resident_flags=flags,
   required_code=2 if flags==5 and kind!='headZonly' else 6)
 for second,index in itertools.product((False,True),(-1,0)):
  rows=copy.deepcopy(MOTION);rows[0][14:19]=[0,1,0,index,0]
  add('actual_Drive_A4_controls_result2_not_activity_alone',motion=rows,second=second,
   required_caller='0x4a40ea' if second else '0x4a34f1',required_code=2 if index==-1 else 0)
 add('late_zero_speed_overrides_moving_result2',land_speed=0.,required_code=7)
 rows=copy.deepcopy(MOTION);rows[1][3:9]=[0]*6
 objects=default_objects();objects[0][1]=2
 add('later_stationary_resident_overrides_moving_result2',motion=rows,objects=objects,required_code=6)
 require(all(o.admission_caller_returns.get(k,{}).get(2,0)>0 for k in ('0x4a34f1','0x4a40ea','0x4a1c9f')))
 require(options[1] and options[2] and preparations.get('0x4a41df:1:1',0))
 require(all(o.moving_Process_callers.get(k,0)>0 for k in ('0x4a0739','0x4a0b75','Advance')) and all(o.waitBranches.values()))
 return commands,expected,labels,{'audited_complete_Process_roots':o.roots,'actual_entries':o.entries,
  'entered_distinct_instructions':len(o.instructions),'actual_admission_returns':o.returns,
  'actual_admission_returns_by_caller':o.admission_caller_returns,'actual_next_Cell_calls':o.next_calls,
  'selected_decision_stores':o.decision_stores,'actual_wait_dword_stores':o.waitStores,
  'moving_result2_by_Process_caller':o.moving_Process_callers,'actual_wait_branches':o.waitBranches,
  'supplied_default_pathfinder_calls':o.defaultPathfinderCalls,
  'actual_actor57a_state_checks':o.actor_byte_checks,'actual_pathfinder_options':options,
  'actual_preparation_arguments':preparations,'per_case_checks':per_case,
  'resident_record_checks':o.stationary_checks,'initial_records_associations_wait_duration_padding_and_named_failed_pathfinder_services_supplied':True,
  'complete_Process_and_actual_moving_children':True,
  'runtime_unwired':True,'parked_commands_enabled':False}
def safety_commands():
 valid=command();p=valid.split();p[-9]='256'
 cases=['','M 0',valid+' trailing',' '.join(p),command(wait=[0,-1,0,0,10,0,-1,0,2147483648])]
 for index,value in ((9,-1),(10,65536),(13,65536),(14,256),(16,64),(18,256)):
  rows=copy.deepcopy(MOTION);rows[0][index]=value;cases.append(command(motion=rows))
 objects=default_objects();objects[0][0]=6;cases.append(command(objects=objects))
 h=parent.HEADER.copy();h[2:6]=[72*512+51,74*512+52,-1,1]
 cases.append(command(h=h,resident_flags=1,route=(2,3,4,4),steps=160))
 rows=copy.deepcopy(MOTION);rows[0][:3]=[13432,18808,416];rows[0][9:11]=[57344,57344]
 cases.append(command(h=h,motion=rows,route=(2,3,4,4),steps=160))
 return cases
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin')
 p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-drive-process-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/moving-resident-process-v1')
 p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh moving-resident Process destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 args=[str(a.native),str(a.exe),str(a.render_data),str(a.direction_data)]
 now=time.monotonic();proc=subprocess.run(args,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native moving-resident Process: '+proc.stderr.strip())
 actual=[line.split() for line in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Moving-resident Process counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   at=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'Moving-resident Process {i} {labels[i]} token{at}: {x[max(0,at-12):at+16]} != {y[max(0,at-12):at+16]}; counts {len(x)}/{len(y)}; {commands[i]}')
 safety=safety_commands()
 for i,cmd in enumerate(safety):
  r=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError(f'Moving-resident refusal missing at{i}')
  if i>=len(safety)-2:
   code=6 if i==len(safety)-2 else 7
   if 'switch admission requires zero result' not in r.stderr or r.stdout.split()[-3:]!=['a','r',str(code)]:
    raise AssertionError('Wrong unsupported Advance refusal: '+r.stderr)
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Moving-resident Process run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} moving-resident Process results / {metadata["audited_complete_Process_roots"]:,} original ticks: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
