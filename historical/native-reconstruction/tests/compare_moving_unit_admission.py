#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Unit admission with actual moving/turning resident children."""
import argparse,copy,itertools,json,struct,subprocess,time
from pathlib import Path
import pefile
import compare_unit_admission as base
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_moving_unit_admission import verify
SOURCES=tuple(dict.fromkeys((*base.SOURCES,'src/sim/MovingUnitAdmission.hpp','src/sim/MovingUnitAdmission.cpp',
 'src/sim/Targeting.hpp','src/sim/Targeting.cpp','src/sim/OriginalMath.hpp',
 'src/assets/MovementData.hpp','src/assets/MovementData.cpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp',
 'src/assets/RenderData.hpp','src/assets/RenderData.cpp','src/render/Lighting.hpp','src/render/Lighting.cpp',
 'tests/moving_unit_admission_vectors.cpp','tests/original_moving_unit_admission.py',
 'tests/compare_moving_unit_admission.py','tests/test_moving_unit_admission_evidence.py','tools/verify_moving_unit_admission.py')))
MOTION=[[13184+i*128,18560,0,0,0,0,0,0,0,16384,16384,0,0,1280,1,-1,0,0,0] for i in range(5)]
MOTION[1][3:6]=[14000,18560,0];MOTION[1][9:11]=[49152,49152]
OBJECTS=copy.deepcopy(base.OBJECTS)
for o in OBJECTS:o[0]=1;o[3]=0
CELLS=copy.deepcopy(base.CELLS);CELLS[0][11]=1
def command(motion=None,mode=0,**kw):
 kw.setdefault('objects',OBJECTS);kw.setdefault('cells',CELLS)
 words=base.command(**kw).split()
 return ' '.join(['V',*words[1:175],'M',*map(str,itertools.chain.from_iterable(MOTION if motion is None else motion)),str(mode),*words[175:]])
def parse(cmd):
 t=cmd.split();base.require(len(t)>=273 and t[0]=='V' and t[175]=='M')
 fixture=base.parse(' '.join(['W',*t[1:175],*t[272:]]),moving=True)
 rows=[list(map(int,t[176+19*i:195+19*i])) for i in range(5)];mode=int(t[271])
 base.require(mode in range(4) and all(o[0]==1 for o in fixture[6]))
 for m in rows:
  base.require(len(m)==19 and all(-2147483648<=v<=2147483647 for v in m[:9]+m[11:13]+[m[15],m[17]])
   and all(0<=m[j]<=65535 for j in (9,10,13)) and 0<=m[14]<=255 and 0<=m[16]<64 and 0<=m[18]<=255)
 return fixture,rows,mode
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'direction_data':hash_file(a.direction_data),'render_data':hash_file(a.render_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Moving admission engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Moving admission identity differs')
 if not e['evidence'].get('complete_parent_and_actual_moving_children'):raise ValueError('Moving admission join differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Moving admission counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,IndexError,TypeError,OverflowError):raise ValueError('Malformed moving admission command') from None
def generate(a):
 from original_moving_unit_admission import MovingUnitAdmissionOracle
 oracle=MovingUnitAdmissionOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,motion=None,assert_code=None,**kw):
  cmd=command(motion=motion,mode=len(commands)%4,**kw);fixture,rows,_=parse(cmd);oracle.motion=rows
  result=oracle.run(*fixture);commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1
  if assert_code is not None:
   base.require(result[-8]=='R' and result[-4]=='z' and int(result[-7])==assert_code)
  if len(commands)%128==0:print(len(commands),'moving admission scenarios',flush=True)
 for distance in (0,1,255,510,511,512,513,1024):
  motion=copy.deepcopy(MOTION);motion[1][0]=motion[0][0]+distance
  add('actual_head_on_distance_cutoff',motion)
 if not a.pilot:
  headings=sorted({0,65535,*[v+d for v in range(4096,65536,8192) for d in (-1,0,1)]})
  for own,other in itertools.product(headings,repeat=2):
   motion=copy.deepcopy(MOTION);motion[0][9:11]=[own,own];motion[1][9:11]=[other,other]
   add('rounded_heading_bins_opposite_7fff_and_bearing',motion)
  for eligibility,target,flags,kind in itertools.product((0,1,255),(-1,0),(1,4,5,255),('destination','head','turn','idle')):
   motion=copy.deepcopy(MOTION);motion[1][14]=eligibility;motion[1][0]+=1024;motion[1][3:9]=[0]*6
   if kind=='destination':motion[1][3:6]=[14000,18560,0]
   if kind=='head':motion[1][6:9]=[14000,18560,0]
   if kind=='turn':motion[1][9:14]=[49152,32768,300,40,1280]
   objects=copy.deepcopy(OBJECTS);objects[1][7]=flags;objects[1][13]=target
   add('target_turning_and_actual_Drive_activity_short_circuit',motion,objects=objects)
  pe=pefile.PE(str(a.exe))
  for track,q,short in itertools.product(range(64),(-2,-1,0,1,2,3,4,5,6,7,8,9),(0,1)):
   transform=pe.get_data(0x7a0180+track*12-0x400000,12);selected=transform[short]
   if selected>6:continue
   jump=struct.unpack('<i',pe.get_data(0x7a00a4+selected*16-0x400000,4))[0]
   for index in sorted({0,jump,jump+1}):
    motion=copy.deepcopy(MOTION);motion[1][0]+=1024;motion[1][14:19]=[0,q,track,index,short]
    add('complete_Drive_A4_ordinary_track_queue_index_and_short_selection',motion)
  for z,other_z in ((0,0),(0,511),(0,512),(-2147483648,2147483647),(2147483647,-2147483648),(0,-2147483648)):
   motion=copy.deepcopy(MOTION);motion[0][2]=z;motion[1][2]=other_z
   add('wrapped_three_component_distance_and_FTOL_low_dword',motion)
  for delta in ((1,0),(0,1),(-1,0),(0,-1),(1,1),(1,-1),(-1,1),(-1,-1),(1048576,1),(1,1048576)):
   for heading in range(0,65536,8192):
    motion=copy.deepcopy(MOTION);motion[0][9:11]=[heading,heading];motion[1][0:2]=[motion[0][0]+delta[0],motion[0][1]+delta[1]]
    add('table_bearing_quadrants_saturation_and_zero_components',motion)
  for tick,start,duration,rate in itertools.product((317,-1,2147483647,-2147483648),(-1,300,2147483640),(0,40),(0,1280,65535)):
   h=base.HEADER.copy();h[0]=tick;motion=copy.deepcopy(MOTION);motion[1][0]+=1024;motion[1][9:14]=[49152,32768,start,duration,rate]
   add('actual_Facing_current_rotating_signed_timer_and_rate',motion,h=h)
  for order,speed in itertools.product(itertools.permutations((0,1,3)),(0,0x3f800000,0x7fc00000)):
   objects=copy.deepcopy(OBJECTS);cells=copy.deepcopy(CELLS);cells[0][11]=order[0]
   for left,right in zip(order,(*order[1:],-1)):objects[left][1]=right
   motion=copy.deepcopy(MOTION);motion[1][0]+=1024;motion[3][3:6]=[14000,18560,0]
   add('ordered_mixed_list_self_skip_and_late_speed_rejection',motion,objects=objects,cells=cells,speeds=[speed]*12)
  # Drive activity uses all three components for sentinel tests, but only X/Y
  # when comparing a nonzero head with current location. Require actual parent
  # returns here instead of inferring that distinction from scenario names.
  for mask in range(8):
   motion=copy.deepcopy(MOTION);motion[1][0]+=1024;motion[1][3:9]=[0]*6
   motion[1][3:6]=[int(bool(mask&(1<<axis))) for axis in range(3)]
   add('full_destination_sentinel_including_Z_only',motion,assert_code=2 if mask else 6)
  for mask in range(8):
   motion=copy.deepcopy(MOTION);motion[1][0]+=1024;motion[1][3:6]=[0]*3
   motion[1][6:9]=[motion[1][axis]+int(bool(mask&(1<<axis))) for axis in range(3)]
   add('nonzero_head_compares_current_XY_only',motion,assert_code=2 if mask&3 else 6)
  for head in ((0,0,0),(0,0,1)):
   motion=copy.deepcopy(MOTION);motion[1][0]+=1024;motion[1][3:6]=[0]*3;motion[1][6:9]=head
   add('full_head_sentinel_including_Z_only',motion,assert_code=2 if any(head) else 6)
  for z in (-2147483648,-1,1,2147483647):
   motion=copy.deepcopy(MOTION);motion[1][0]+=1024;motion[1][3:6]=[0]*3
   motion[1][6:9]=[*motion[1][:2],z]
   add('head_Z_difference_does_not_make_Drive_active',motion,assert_code=6)
  base.require(all(oracle.switch_returns.values()) and all(oracle.moving_entries.values()) and
   all(oracle.entries[hex(a)]>0 for a in (0x4ba410,0x4ba600,0x4b8be0,0x5d4e40,0x4a4ac0,0x77f110)) and
   set(oracle.root_results)=={0,2,5,6,7})
 return commands,expected,labels,{'groups':groups,'audited_original_calls':oracle.audit_calls,'actual_entries':oracle.entries,
  'actual_moving_entries':oracle.moving_entries,'entered_distinct_instructions':len(oracle.instructions),
  'selected_original_stores':oracle.stores,'actual_result_counts':oracle.results,'root_return_codes':oracle.root_results,
  'actual_distance_returns':oracle.distance_returns,'actual_bearing_returns':oracle.bearing_returns,'actual_switch_returns':oracle.switch_returns,
  'complete_parent_and_actual_moving_children':True,'initial_records_and_associations_supplied':True,'Process_runtime_excluded':True,'pilot':a.pilot}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin');p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--native',type=Path,default=ROOT/'build/native/moving-unit-admission-vectors');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/moving-unit-admission-new')
 p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);p.add_argument('--pilot',action='store_true');a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh moving admission destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 args=[str(a.native),str(a.exe),str(a.direction_data),str(a.render_data)]
 now=time.monotonic();proc=subprocess.run(args,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native moving admission command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Moving admission result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-12):j+20]} != {y[max(0,j-12):j+20]}; counts {len(x)}/{len(y)}')
 safety=['','V 0',command()+' trailing',command(mode=4),command().replace(' M ',' X ',1)]
 for cmd in safety:
  bad=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if not bad.returncode or not bad.stderr.strip():raise AssertionError('Missing moving admission native refusal')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Moving admission run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} moving admission results: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
