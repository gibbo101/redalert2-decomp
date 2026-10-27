#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential Unit admission, including actual terrain and occupied decisions."""
import argparse,copy,itertools,json,random,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_admission import verify
SOURCES=('src/sim/UnitAdmission.hpp','src/sim/UnitAdmission.cpp','src/sim/MovingUnitAdmission.hpp','src/sim/MovingUnitAdmission.cpp','src/sim/MovementGate.hpp','src/sim/MovementGate.cpp',
 'src/sim/HouseIndexAlliance.hpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp',
 'src/sim/Facing.hpp','src/sim/Targeting.hpp','src/sim/Targeting.cpp','src/sim/OriginalMath.hpp',
 'tests/unit_admission_vectors.cpp','tests/original_unit_admission.py',
 'tests/compare_unit_admission.py','tools/verify_unit_admission.py','tests/test_unit_admission_evidence.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py',
 'tests/compare_original.py','tools/verify_terrain_visibility.py','CMakeLists.txt')
HEADER=[317,72*512+51,72*512+50,3]
DIRECTIONS=[0,-1,1,-1,1,0,1,1,0,1,-1,1,-1,0,-1,-1]
SPEEDS=[0x3f800000]*12
HOUSES=[[0,1],[1,2],[33,0]]
REGS=[[1,1,0,2],[1,0,0,6],[0,7,-9,-1]]
# x,y,registry,level,ramp,flags,occupation/elevated,owners,land,heads
CELLS=[[51,72,-1,0,0,0,0,0,-1,-1,0,-1,-1],
 [50,72,-1,0,0,0,0,0,-1,-1,1,-1,-1],[-7,5,-1,0,0,0,0,0,-1,-1,2,-1,-1]]
# kind,Next,owner,gate,mission,anim18/19,flags14,crushable,crusher,train,
# Building1350,state1B8,target,destination,weapon,projectile275
OBJECTS=[[1,-1,0,0,2,0,0,5,0,0,0,0,0,-1,-1,1,1],
 [1,-1,0,0,2,0,0,5,0,0,0,0,0,-1,-1,0,0],
 [6,-1,0,1,2,0,0,1,0,0,0,0,0,-1,-1,0,0],
 [1,-1,1,0,2,0,0,5,0,0,0,0,0,-1,-1,0,0],
 [6,-1,1,1,24,0,1,1,0,0,0,0,0,-1,-1,0,0]]
STEP=['U',0,0,2,0,-1,1,255]
def command(h=None,directions=None,speeds=None,houses=None,regs=None,cells=None,objects=None,steps=None):
 flat=lambda rows:itertools.chain.from_iterable(rows)
 steps=[STEP] if steps is None else steps
 return 'W '+' '.join(map(str,[*(HEADER if h is None else h),*(DIRECTIONS if directions is None else directions),
  *(SPEEDS if speeds is None else speeds),*flat(HOUSES if houses is None else houses),*flat(REGS if regs is None else regs),
  *flat(CELLS if cells is None else cells),*flat(OBJECTS if objects is None else objects),len(steps),*flat(steps)]))
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported admission command')
def parse(cmd,*,moving=False):
 tokens=cmd.split();require(tokens and tokens[0]=='W');i=1
 def read(n):
  nonlocal i
  v=list(map(int,tokens[i:i+n]));require(len(v)==n);i+=n;return v
 def rows(n,size):return [read(size) for _ in range(n)]
 i32=lambda x:-2147483648<=x<=2147483647;byte=lambda x:0<=x<=255;word=lambda x:-32768<=x<=32767;obj=lambda x:-1<=x<5
 h=read(4);directions=read(16);speeds=read(12);houses=rows(3,2);regs=rows(3,4);cells=rows(3,13);objects=rows(5,17)
 require(i32(h[0]) and all(-1<=x<262144 for x in h[1:3]) and (h[1]==-1 or h[1]!=h[2]) and 0<=h[3]<=3)
 require(all(word(x) for x in directions) and all(0<=x<1<<32 for x in speeds))
 require(all(i32(index) and 0<=mask<1<<32 for index,mask in houses))
 require(all(p in (0,1) and word(x) and word(y) and i32(d) for p,x,y,d in regs))
 for c in cells:require(all(word(x) for x in c[:3]) and -128<=c[3]<=127 and byte(c[4]) and all(0<=x<1<<32 for x in c[5:8]) and all(i32(x) for x in c[8:10]) and 0<=c[10]<12 and all(obj(x) for x in c[11:13]))
 for j,o in enumerate(objects):
  require(o[0] in (1,6) and obj(o[1]) and 0<=o[2]<3 and byte(o[3]) and i32(o[4]) and all(byte(x) for x in o[5:12]) and i32(o[12]) and all(obj(x) for x in o[13:15]) and all(x in (0,1) for x in o[15:17]))
  require(moving or not j or o[13]==-1)
  # Crushing resident decisions need their own actual occupied-Unit child join.
  require(not(objects[0][9] and j and o[8]))
 require(objects[0][0]==1)
 for j in range(5):
  seen=set()
  while j!=-1:require(j not in seen);seen.add(j);j=objects[j][1]
 count=read(1)[0];require(1<=count<=128);steps=[]
 for _ in range(count):
  require(i<len(tokens));k=tokens[i];i+=1;m,t,d,l,p,c,e=read(7)
  require(k in ('U','T') and m==0 and 0<=t<3 and i32(d) and i32(l) and -1<=p<3 and byte(c) and byte(e))
  steps.append([k,m,t,d,l,p,c,e])
 require(i==len(tokens));return h,directions,speeds,houses,regs,cells,objects,steps
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Admission engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Admission identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Admission counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,IndexError,TypeError,OverflowError):raise ValueError('Malformed admission command') from None
def generate(a):
 from original_unit_admission import UnitAdmissionOracle
 oracle=UnitAdmissionOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x703040)
 def add(label,**kwargs):
  cmd=command(**kwargs);result=oracle.run(*parse(cmd));commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1
 # Full Foot decision, both return codes and level/elevated stores; absolute
 # difference uses signed wrapped dwords while Cell heights remain signed bytes.
 for level,delta,pflags,tflags,ramp in itertools.product((-2147483648,-1,0,1,4,2147483647),(-5,-4,-1,0,1,4,5),(0,0x100,0x300),(0,0x100,0x200,0x300),(0,1)):
  cells=copy.deepcopy(CELLS);cells[0][3:6]=[0,ramp,tflags];cells[1][3:6]=[delta,ramp,pflags]
  add('complete_Foot_height_ramp_bridge_flags_wrapped_level_and_retained_outputs',cells=cells,
   steps=[['T',0,0,2,level,1,1,255],['T',0,0,-1,level,1,0,128]])
 for t,p,l in ((-128,-124,-128),(127,123,127),(-4,0,0),(0,-4,0),(1,0,1),(0,1,1)):
  for flags in (0,0x100,0x200,0x300):
   cells=copy.deepcopy(CELLS);cells[0][3]=t;cells[1][3]=p;cells[0][5]=cells[1][5]=flags
   add('signed_byte_height_edges_and_explicit_previous_identity',cells=cells,steps=[['T',0,0,6,l,1,255,7],['U',0,0,6,l,1,255,7]])
 for d,reg,reverse in itertools.product((-2147483648,-1,0,2,7,8,2147483647),(-32768,-1,0,1,2,3,32767),(-1,0,1)):
  cells=copy.deepcopy(CELLS);cells[0][2]=reg;cells[1][2]=reverse;cells[2][2]=reverse
  add('actual_signed_registry_bounds_direction_and_direction8_shortcut',cells=cells,steps=[['U',0,0,d,0,-1,1,255]])
 for count,present,x in itertools.product(range(4),(0,1),(0,1)):
  h=HEADER.copy();h[3]=count;regs=copy.deepcopy(REGS);regs[0][0]=present;regs[0][1]=x;cells=copy.deepcopy(CELLS);cells[0][2]=0
  add('registry_count_null_slot_and_direction8_coordinates',h=h,regs=regs,cells=cells,steps=[['U',0,0,8,0,-1,1,7]])
 for stored,d in itertools.product((-2147483648,-1,0,1,2,3,4,5,6,7,8,2147483647),(-1,0,2,7)):
  cells=copy.deepcopy(CELLS);cells[0][2]=0;regs=copy.deepcopy(REGS);regs[0][3]=stored
  add('registry_direction_wrapped_absolute_difference',cells=cells,regs=regs,steps=[['U',0,0,d,0,-1,0,1]])
 for occ,owner,weapon,projectile,crusher,train in itertools.product((0,1,31,32,63,64,0x80000001),(-1,0,1,33),(0,1),(0,1),(0,1),(0,1)):
  cells=copy.deepcopy(CELLS);cells[0][6]=occ;cells[0][8]=owner;objects=copy.deepcopy(OBJECTS);objects[0][9:11]=[crusher,train];objects[0][15:17]=[weapon,projectile]
  add('occupation_owner_bit5_weapon_projectile_train_and_actual_unpromoted_ability',cells=cells,objects=objects)
 for resident,mission,weapon,animation,speed in itertools.product((0,1,2,3,4),(2,7,11,-1),(0,1),(0,1,2),(0,0x3f800000)):
  cells=copy.deepcopy(CELLS);cells[0][11]=resident;objects=copy.deepcopy(OBJECTS);objects[0][4]=mission;objects[0][13:15]=[resident,resident];objects[0][15]=weapon;objects[4][6]=animation
  add('self_stationary_Unit_alliance_closed_and_exact_open_gate_priority_over_speed',cells=cells,objects=objects,speeds=[speed]*12)
 for kind,owner,state,weapon,b1350,flags in itertools.product((1,6),(0,1,2),(0,2),(0,1),(0,1),(0,1,4,5)):
  cells=copy.deepcopy(CELLS);cells[0][11]=3;objects=copy.deepcopy(OBJECTS);objects[3][0]=kind;objects[3][2]=owner;objects[3][12]=state;objects[3][11]=b1350;objects[3][7]=flags;objects[0][15]=weapon
  add('generic_stationary_Unit_Building_cast_state_and_uncrushable_decision',cells=cells,objects=objects)
 for kind in (1,6):
  cells=copy.deepcopy(CELLS);cells[0][11]=3;objects=copy.deepcopy(OBJECTS);objects[3][0]=kind;objects[0][9]=1
  add('actual_enemy_noncrushable_type_getter_with_Crusher',cells=cells,objects=objects)
 for bits in (0,0x80000000,1,0x80000001,0x3f800000,0xbf800000,0x7f800000,0xff800000,0x7fc00000,0x7f800001,0xffc00000):
  for elevated in (0,1):
   cells=copy.deepcopy(CELLS);cells[0][5]=0x300 if elevated else 0;cells[1][5]=0x100 if elevated else 0;cells[0][3]=-4 if elevated else 0
   add('terrain_speed_zero_unordered_signed_subnormal_and_infinity',cells=cells,speeds=[bits]*12,steps=[['U',0,0,2,0,1,1,255]])
 for land,bits in itertools.product(range(12),(0,0x3f800000,0x7fc00000)):
  cells=copy.deepcopy(CELLS);cells[0][10]=land;speeds=SPEEDS.copy();speeds[land]=bits
  add('actual_selected_land_speed_index_with_distinct_other_entries',cells=cells,speeds=speeds)
 for order in itertools.permutations(range(5),3):
  cells=copy.deepcopy(CELLS);cells[0][11]=order[0];cells[0][6]=32;objects=copy.deepcopy(OBJECTS)
  for left,right in zip(order,(*order[1:],-1)):objects[left][1]=right
  add('ordered_mixed_residents_result_priority_and_live_self_occupation_clear',cells=cells,objects=objects)
 # Shared fallback can be target and opposite neighbor; the second lookup must
 # use its already rewritten coordinates. No independent Cell copies are legal.
 for point,d,prev in itertools.product(((-32768,32767),(32767,0),(-1,1),(512,0)),(-1,0,2,7),(-1,0,2)):
  h=HEADER.copy();h[1:3]=[-1,-1];cells=copy.deepcopy(CELLS);cells[2][:2]=point
  add('shared_fallback_repeated_neighbor_lookup_and_word_wrap',h=h,cells=cells,
   steps=[['U',0,2,d,0,prev,1,255],['T',0,2,d,-1,prev,0,7],['U',0,2,2,0,-1,0,1]])
 for i in range(100):
  cells=copy.deepcopy(CELLS);objects=copy.deepcopy(OBJECTS);houses=[[rng.choice((-33,-1,0,1,33)),rng.getrandbits(32)] for _ in range(3)]
  for j,o in enumerate(objects):o[1]=rng.choice([-1,*range(j+1,5)]);o[2]=rng.randrange(3)
  for c in cells:c[6]=rng.getrandbits(32);c[8]=rng.choice((-1,0,1,33));c[11:13]=[rng.randrange(-1,5),rng.randrange(-1,5)]
  cells[0][5]=0x100 if i%2 else 0;cells[1][5]=0x100 if i%2 else 0
  add('stable_mixed_shared_lists_House_mask_upper_occupation_and_primary_elevated_selection',cells=cells,objects=objects,houses=houses,
   steps=[['U',0,0,2,4 if i%2 else 0,1,i%3,255],['U',0,0,-1,0,0,1,7]])
 require(all(oracle.entries.values()) and all(oracle.kind_returns.values()) and all(oracle.locations.values()))
 require(set(oracle.root_results)=={0,1,2,3,5,6,7} and set(oracle.terrain_results)=={0,7})
 return commands,expected,labels,{'groups':groups,'audited_original_calls':oracle.audit_calls,'actual_entries':oracle.entries,
  'entered_distinct_instructions':len(oracle.instructions),'selected_original_stores':oracle.stores,'actual_result_counts':oracle.results,
  'root_return_codes':oracle.root_results,'terrain_return_codes':oracle.terrain_results,'selected_instruction_counts':oracle.locations,
  'kind_return_checks':oracle.kind_returns,'initial_records_associations_supplied':True,'Process_runtime_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-admission-vectors');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-admission-v3')
 p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh admission destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native admission: '+proc.stderr.strip())
 actual=[line.split() for line in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Admission result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Admission {i} {labels[i]} {commands[i]}: {x} != {y}')
 safety=['','W 0','bad',command()+' trailing',command(steps=[]),command(steps=[['U',1,0,2,0,-1,1,0]])]
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Admission refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Admission run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,
  'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} Unit admission results / {metadata["audited_original_calls"]:,} original calls: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
