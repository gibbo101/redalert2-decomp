#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary Process with actual Advance0/2/7 and later preparation."""
import argparse,copy,itertools,json,struct,subprocess,time
from pathlib import Path
import pefile
import compare_moving_resident_process as parent
from compare_advance_admission import track_cases
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_process_advance_admission import verify,CALLERS
SOURCES=tuple(dict.fromkeys((*parent.SOURCES,'src/sim/GroundDriveAdvanceAdmission.hpp',
 'tests/original_process_advance_admission.py','tests/compare_process_advance_admission.py',
 'tools/verify_process_advance_admission.py','tests/test_process_advance_admission_evidence.py',
 'tests/compare_advance_admission.py','tools/verify_advance_admission.py','tools/verify_ground_drive_stores.py')))
def command(planes=None,**kw):return 'N '+parent.command(planes,**kw)[2:]
def parse(cmd):
 p=cmd.split()
 if not p or p[0]!='N':raise ValueError('Malformed Process Advance admission command')
 return parent.parse('M '+' '.join(p[1:]))
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'render_data':hash_file(a.render_data),'direction_data':hash_file(a.direction_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Process Advance engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Process Advance identity differs')
 if e['evidence'].get('root')!='0x4a05f0' or not e['evidence'].get('complete_Process_actual_Advance_admission'):
  raise ValueError('Process Advance root/scope differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Process Advance counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,AssertionError,IndexError,TypeError,OverflowError,struct.error):raise ValueError('Malformed Process Advance admission command') from None

def head_on_from(p,offset,shift=(0,0)):
 stream,_,_,_,flags=struct.unpack('<BBHii',p.get_data(0x7a0180+19*12-0x400000,12))
 address,jump,_,_=struct.unpack('<4i',p.get_data(0x7a00a0+16*stream-0x400000,16))
 x,y,angle=struct.unpack('<3i',p.get_data(address+jump*12-0x400000,12))
 if flags&1:x,y,angle=y,x,(-64-angle)&255
 if flags&2:x,angle=-x,-angle&255
 if flags&4:y,angle=-y,(-128-angle)&255
 direction=(((angle>>4)+1)>>1)&7
 dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[direction]
 rows=copy.deepcopy(parent.MOTION)
 rows[0][:3]=[51*256+128+x+shift[0]+offset*dx,72*256+128+y+shift[1]+offset*dy,416]
 rows[0][9:14]=[((direction+4)&7)<<13,((direction+4)&7)<<13,-1,0,1280]
 return rows

def generate(a):
 from original_process_advance_admission import ProcessAdvanceAdmissionOracle
 o=ProcessAdvanceAdmissionOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];coverage=[]
 def add(label,code=None,caller=None,**kw):
  kw.setdefault('mode',len(commands)%4);cmd=command(planes,**kw);before=o.branch_returns.copy();callers=o.result7_callers.copy()
  at=len(o.measurements);pre={k:dict(v) for k,v in o.admission_caller_returns.items()}
  result=o.run(*parse(cmd));measured=o.branch_returns-before;actual_callers=o.result7_callers-callers
  if code is not None and not measured[code]:raise ValueError(f'Missed actual Advance{code}: {label}, {measured}')
  if caller and not actual_callers[caller]:raise ValueError(f'Missed actual result7 caller {caller}: {label}, {actual_callers}')
  commands.append(cmd);expected.append(result);labels.append(label)
  coverage.append({'actual_Advance_returns':dict(measured),'actual_result7_callers':dict(actual_callers),
   'actual_bearing_distance_returns':o.measurements[at:],'actual_preparation_arguments':o.preparationArguments.copy(),
   'actual_admission_returns':{k:{str(c):n-pre.get(k,{}).get(c,0) for c,n in v.items() if n!=pre.get(k,{}).get(c,0)} for k,v in o.admission_caller_returns.items()}})
 h=parent.parent.HEADER.copy();h[2:6]=[-1,-1,-1,-1];h[6]=1;h[8]=-1
 base=dict(h=h,resident=0,track=19,index=37,acc=7,driving=1,route=(4,4,-1,7,6),land_speed=1.)
 for offset,mode in itertools.product((128,361,362,363,511,512),range(4)):
  add('head_on_nonzero_speed_distance_boundary',code=7 if offset<=362 else 2,
   motion=head_on_from(p,offset),mode=mode,steps=8,**base)
 for tick,marked,effect in itertools.product((-2147483648,-1,2147483647),(0,1,255),(0,1)):
  add('head_on7_signed_clock_Mark_and_later_preparation_wait',code=7,caller='0x4a066b',
   motion=head_on_from(p,128),tick=tick,marked=marked,mark_effect=effect,steps=24,**base)
 for offset in (128,363):
  add('complete_head_on_track_later_Process_and_retained_tails',code=7 if offset==128 else 2,
   motion=head_on_from(p,offset),steps=128,**base)
 # Exercise result7 through the initial-preparation and post-completion callers.
 # Preparation shifts the track19 origin by (256,256); a preceding straight
 # completion shifts it by another (256,0). Large authored residual credit
 # reaches the jump in the same Advance call, including suppress-speed1.
 for prior,mode in itertools.product((False,True),range(4)):
  hh=parent.parent.HEADER.copy();hh[2:6]=[72*512+(52 if prior else 51),74*512+(53 if prior else 52),-1,1];hh[6]=-1;hh[8]=-1
  kw=dict(track=18,index=20,driving=1) if prior else {}
  add('result7_after_preparation_at_each_Process_Advance_caller',code=7,caller='0x4a0758' if prior else '0x4a0ba3',
   h=hh,resident=1,motion=head_on_from(p,128,(512 if prior else 256,256)),mode=mode,
   speed=255,acc=512,steps=4,route=(2,3,4,4),**kw)
 empty=parent.parent.HEADER.copy();empty[2:7]=[-1]*5;empty[8]=-1
 for track,jump,candidates in track_cases(p):
  add('all_curved_transforms_zero_speed7_complete_Process',code=7,h=empty,
   track=track,index=jump,driving=1,acc=7,route=(candidates[0],-1,7,6),land_speed=0.,steps=48)
 for resident in (0,1):
  for x,y,hx,hy in ((-255,-257,-257,-1),(16777215,-16777217,16777215,-16777217)):
   add('signed_coordinate_division_and_word_truncation',code=7,h=empty,resident=resident,
    x=x,y=y,hx=hx,hy=hy,track=19,index=37,driving=1,acc=7,route=(4,-1,7,6),land_speed=0.,steps=8)
 for second in (False,True):
  add('actual_later_moving2_preparation_and_wait',second=second,steps=8)
  add('actual_stationary6_preparation_retry',second=second,resident_flags=1,steps=4)
 add('expired_wait_selects_failed_pathfinder_option2',wait=[1,90,11,5,10,-17,-1,7,0],steps=4)
 for land in (0.,1.):
  add('empty_shared_map_complete_Process_and_later_queue',h=empty,land_speed=land,route=(2,3,4,4),steps=160)
 if not (o.default_continuations==o.default_index_stores==o.branch_returns[7] and all(o.branch_returns[c] for c in (0,2,7))
  and all(o.result7_callers[hex(c)] for c in CALLERS) and o.actual_roots['0x4a05f0']==o.roots):raise ValueError('Process Advance coverage incomplete')
 return commands,expected,labels,{'root':'0x4a05f0','complete_Process_actual_Advance_admission':True,
  'actual_root_entries':dict(o.actual_roots),'audited_complete_Process_calls':o.roots,'actual_Advance_callers':dict(o.advance_callers),
  'actual_Advance_admission_returns':dict(o.branch_returns),'actual_result7_callers':dict(o.result7_callers),
  'actual_admission_returns_by_caller':o.admission_caller_returns,'actual_default_continuations':o.default_continuations,
  'actual_default_index_stores':o.default_index_stores,'selected_Drive_stores':dict(o.drive_stores),
  'selected_actor_stores':o.stores,'selected_preparation_stores':o.decision_stores,'actual_wait_stores':o.waitStores,
  'actual_next_Cell_calls':o.next_calls,'distinct_instructions':len(o.instructions),'per_case_checks':coverage,
  'supplied_initial_records_Cells_type_House_Mark_occupation_notification_pathfinder_effects':True,'runtime_unwired':True}

def safety_commands():
 valid=command();p=valid.split();p[-9]='256'
 return ['', 'N 0',valid+' trailing',' '.join(p),command(speed=256),command(route=(8,)),command(steps=0),parent.command()]
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin')
 p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-drive-process-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/process-advance-admission-v1')
 p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh Advance destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 args=[str(a.native),str(a.exe),str(a.render_data),str(a.direction_data)]
 now=time.monotonic();proc=subprocess.run(args,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:
  index=proc.stdout.count('\n')
  raise RuntimeError(f'Native Advance at{index}: {proc.stderr.strip()}; {commands[min(index,len(commands)-1)]}')
 actual=[line.split() for line in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Advance counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   at=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'Advance {i} {labels[i]} token{at}: {x[max(0,at-12):at+16]} != {y[max(0,at-12):at+16]}; counts{len(x)}/{len(y)}; {commands[i]}')
 for cmd in safety_commands()[:-1]:
  r=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Process Advance refusal absent')
 # Existing M keeps both nonzero-result safety refusals. N still refuses6.
 old_safety=parent.safety_commands()[-2:]
 for cmd in (*old_safety,'N '+old_safety[0][2:]):
  r=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or 'switch admission requires zero result' not in r.stderr:
   raise AssertionError('Process Advance typed refusal absent: '+r.stderr)
  if r.stdout.split()[-3:]!=['a','r','6' if cmd!=old_safety[1] else '7']:
   raise AssertionError('Wrong original-backed native refusal boundary')
 guard=subprocess.run([str(a.native),'--guards'],text=True,capture_output=True)
 if guard.returncode:raise AssertionError('Advance guards failed: '+guard.stderr)
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Advance run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety_commands())-1+3,
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} Process Advance results /{metadata["audited_complete_Process_calls"]:,} complete original Process calls: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
