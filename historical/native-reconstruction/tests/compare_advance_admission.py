#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Advance with actual Unit admission0/2/7, never Process."""
import argparse,copy,itertools,json,struct,subprocess,time
from pathlib import Path
import pefile
import compare_moving_resident_process as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_advance_admission import verify
SOURCES=tuple(dict.fromkeys((*parent.SOURCES,'src/sim/GroundDriveAdvanceAdmission.hpp',
 'tests/advance_admission_vectors.cpp','tests/original_advance_admission.py',
 'tests/compare_advance_admission.py','tools/verify_advance_admission.py',
 'tests/test_advance_admission_evidence.py','tests/advance_admission/CMakeLists.txt',
 'tools/verify_ground_drive_stores.py')))
def command(planes=None,**kw):
 kw.setdefault('track',19);kw.setdefault('index',37);kw.setdefault('acc',7);kw.setdefault('driving',1)
 kw.setdefault('route',(4,4,-1,7,6));kw.setdefault('land_speed',0.);kw.setdefault('steps',2)
 return 'V '+parent.command(planes,**kw)[2:]
def parse(cmd):
 p=cmd.split()
 if len(p)<315 or p[0]!='V':raise ValueError('Malformed Advance admission command')
 suppress=int(p[8])
 if suppress not in (0,1):raise ValueError('Advance suppress outside domain')
 p[8]='0';values=list(parent.parse('M '+' '.join(p[1:])))
 values[0][7]=suppress
 return tuple(values)
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'render_data':hash_file(a.render_data),'direction_data':hash_file(a.direction_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Advance engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Advance identity differs')
 if e['evidence'].get('root')!='0x4a1000' or not e['evidence'].get('complete_Advance_actual_admission') or e['evidence'].get('Process_executed') is not False:
  raise ValueError('Advance root/scope differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Advance counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,AssertionError,IndexError,TypeError,OverflowError,struct.error):raise ValueError('Malformed Advance admission command') from None
def track_cases(p):
 """Authored boundary choices derived from the user's tables, not expectations."""
 for track in range(64):
  raw=p.get_data(0x7a0180+track*12-0x400000,12);stream,_,_,facing,flags=struct.unpack('<BBHii',raw)
  if stream not in (3,4,5,6):continue
  address,jump,_,_=struct.unpack('<4i',p.get_data(0x7a00a0+stream*16-0x400000,16))
  _,_,angle=struct.unpack('<3i',p.get_data(address+12*jump-0x400000,12))
  if flags&1:angle=(-64-angle)&255
  if flags&2:angle=-angle&255
  if flags&4:angle=(-128-angle)&255
  candidates=[]
  for q in range(8):
   next_stream=p.get_data(0x7a0180+12*((((angle+16)>>5)&7)*8+q)-0x400000,1)[0]
   if q!=(((facing+16)>>5)&7) and next_stream and struct.unpack('<i',p.get_data(0x7a00a8+16*next_stream-0x400000,4))[0]>0:
    candidates.append(q)
  if not candidates:raise ValueError('No candidate Advance switch')
  yield track,jump,candidates

def generate(a):
 from original_advance_admission import AdvanceAdmissionOracle
 o=AdvanceAdmissionOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];coverage=[]
 def add(label,code=7,**kw):
  kw.setdefault('mode',len(commands)%4);cmd=command(planes,**kw);before=o.branch_returns.copy();d=o.default_index_stores
  result=o.run(*parse(cmd));measured={str(k):v-before[k] for k,v in o.branch_returns.items() if v!=before[k]}
  if code is not None and not measured.get(str(code)):raise ValueError(f'Case missed actual admission{code}: {label}/{kw}, {measured}')
  if code==7 and o.default_index_stores<=d:raise ValueError('Result7 default index continuation absent')
  commands.append(cmd);expected.append(result);labels.append(label);coverage.append(measured)
 for track,jump,candidates in track_cases(p):
  for q in candidates:
   add('all_curved_transforms_and_eligible_queued_directions_result7',track=track,index=jump,route=(q,-1,7,6))
  add('complete_track_after_result7_retains_full_queue',track=track,index=jump-1,route=(candidates[0],-1,7,6),steps=128)
 for speed,acc,suppress in itertools.product((0,1,15,255),(0,7,8),(0,1)):
  # Reaching admission is measured only when this call consumes jump point.
  reaches=acc+(0 if suppress else speed)>7
  add('suppression_speed_accumulator_and_later_Advance',code=7 if reaches else None,speed=speed,acc=acc,suppress=suppress,steps=1)
 for mode,land,level in itertools.product(range(4),(0.,-0.,-1.),(-126,-1,0,125)):
  add('signed_levels_zero_negative_speed_and_incoming_FP',code=0 if land<0. else 7,mode=mode,land_speed=land,level=level)
 for resident in (0,1):
  for x,y,hx,hy in ((-255,-257,-257,-1),(51*256,72*256,51*256+128,72*256+128),(16777215,-16777217,16777215,-16777217)):
   h=parent.parent.HEADER.copy();h[4:7]=[-1,-1,-1];h[8]=-1
   add('signed_divide_word_truncation_and_shared_fallback',h=h,resident=resident,x=x,y=y,hx=hx,hy=hy)
 for tick,marked,effect in itertools.product((-2147483648,-1,2147483647),(0,1,255),(0,1)):
  add('clock_wrap_Mark_effect_and_later_terminal_state',tick=tick,marked=marked,mark_effect=effect,steps=64)
 add('actual_zero_admission_comparison',code=0,land_speed=1.)
 h=parent.parent.HEADER.copy();h[2:6]=[-1,-1,-1,-1];h[6]=1
 add('actual_moving2_comparison_shared_fallback',code=2,h=h,resident=0,land_speed=1.)
 add('actual_moving2_overridden_by_late_zero_speed7',code=7,h=h,resident=0,land_speed=0.)
 add('inactive_retains_queue_and_clears_accumulator',code=None,track=-1,driving=0,acc=17)
 if not all(o.branch_returns[c] for c in (0,2,7)) or o.default_continuations!=o.default_index_stores or o.default_index_stores!=o.branch_returns[7]:
  raise ValueError('Missing Advance branch coverage')
 return commands,expected,labels,{'root':'0x4a1000','complete_Advance_actual_admission':True,'Process_executed':False,
  'actual_root_entries':dict(o.actual_roots),'audited_complete_Advance_calls':o.roots,
  'actual_admission_returns':dict(o.branch_returns),'actual_default_continuations':o.default_continuations,
  'actual_default_index_stores':o.default_index_stores,'selected_Drive_stores':dict(o.drive_stores),
  'selected_actor_stores':o.stores,'distinct_instructions':len(o.instructions),'per_case_actual_returns':coverage,
  'supplied_initial_records_and_Mark_occupation_notification_effects':True,'runtime_unwired':True}

def safety_commands():
 valid=command();p=valid.split();p[8]='2'
 return ['', 'V 0',valid+' trailing',' '.join(p),command(speed=256),command(route=(8,)),command(steps=0),parent.command()]
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin')
 p.add_argument('--native',type=Path,default=ROOT/'build/advance-admission/advance-admission-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/advance-admission-v1')
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
 for cmd in safety_commands():
  r=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Advance refusal absent')
 guard=subprocess.run([str(a.native),'--guards'],text=True,capture_output=True)
 if guard.returncode:raise AssertionError('Advance guards failed: '+guard.stderr)
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Advance run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety_commands()),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} Advance results /{metadata["audited_complete_Advance_calls"]:,} complete original calls: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
