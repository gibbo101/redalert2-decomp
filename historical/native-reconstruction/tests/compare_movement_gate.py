#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete base gate interaction, alliance, animation and Mission children."""
import argparse,copy,itertools,json,random,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_movement_gate import verify
SOURCES=('src/sim/MovementGate.hpp','src/sim/MovementGate.cpp',
 'src/sim/HouseIndexAlliance.hpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp','src/sim/TerrainOccupation.hpp',
 'src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp',
 'tests/movement_gate_vectors.cpp','tests/original_movement_gate.py','tests/compare_movement_gate.py',
 'tools/verify_movement_gate.py','tests/original_presentation.py','tests/presentation_profiles.py',
 'tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py',
 'tests/test_movement_gate_evidence.py','CMakeLists.txt')
HEADER=[317,-1515870811,7,72*512+51,72*512+52,0,3,1,-7,5]
HOUSES=[[0,1],[1,2],[33,0]]
# kind, Next, Owner, Gate, mission, queued, A4, animation18/19, A8/AC/B0/B4/B8
OBJECTS=[[1,1,0,0,2,-1,255,0,0,17,18,19,20,21],
 [6,-1,0,1,2,-1,255,0,0,27,28,29,30,31],
 [6,-1,1,0,24,7,127,0,1,37,38,39,40,41],
 [6,-1,1,1,2,-1,1,0,0,47,48,49,50,51],
 [36,-1,2,0,14,-1,0,2,255,57,58,59,60,61]]
def command(h=None,houses=None,objects=None,steps=None):
 steps=[['C',0,51,72]] if steps is None else steps
 return 'W '+' '.join(map(str,[*(HEADER if h is None else h),
  *itertools.chain.from_iterable(HOUSES if houses is None else houses),
  *itertools.chain.from_iterable(OBJECTS if objects is None else objects),len(steps),
  *itertools.chain.from_iterable(steps)]))
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported gate command')
def parse(cmd):
 tokens=cmd.split();require(tokens and tokens[0]=='W');require(len(tokens)>=88)
 v=list(map(int,tokens[1:87]));h=v[:10];houses=[v[i:i+2] for i in range(10,16,2)];objects=[v[i:i+14] for i in range(16,86,14)]
 i32=lambda x:-2147483648<=x<=2147483647;byte=lambda x:0<=x<=255;word=lambda x:-32768<=x<=32767;obj=lambda x:-1<=x<5
 require(all(i32(x) for x in h[:3]) and all(-1<=x<262144 for x in h[3:5]) and (h[3]==-1 or h[3]!=h[4]))
 require(all(obj(x) for x in h[5:8]) and all(word(x) for x in h[8:10]))
 require(all(i32(index) and 0<=mask<1<<32 for index,mask in houses))
 for o in objects:
  require(o[0] in (1,6,36) and obj(o[1]) and -1<=o[2]<=2 and all(byte(o[i]) for i in (3,6,7,8))
   and all(i32(o[i]) for i in (4,5,9,10,11,12,13)) and not(o[0]==6 and o[3] and o[2]==-1))
 for i in range(5):
  seen=set()
  while i!=-1:require(i not in seen);seen.add(i);i=objects[i][1]
 count=int(tokens[87]);require(1<=count<=128 and len(tokens)==88+4*count);steps=[]
 for i in range(88,len(tokens),4):
  k=tokens[i];a,b,c=map(int,tokens[i+1:i+4]);require(k in ('C','A','G','I','T'))
  if k=='C':require(obj(a) and word(b) and word(c))
  elif k=='A':require(0<=a<3 and obj(b) and c==0)
  elif k in ('G','I'):require(0<=a<5 and objects[a][0]==6 and b==c==0)
  else:require(0<=a<5 and byte(b) and byte(c))
  steps.append([k,a,b,c])
 return h,houses,objects,steps
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Gate engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Gate identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Gate counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,IndexError,TypeError,OverflowError):raise ValueError('Malformed gate command') from None
def generate(a):
 from original_movement_gate import MovementGateOracle
 o=MovementGateOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x55acd0)
 def add(label,h=None,houses=None,objects=None,steps=None):
  cmd=command(h,houses,objects,steps);args=parse(cmd);result=o.run(*args)
  commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1
 for gate,mission,queued,b18,b19,k in itertools.product((0,1,255),(-1,19,24,28),(-1,7,24),(0,1,2,255),(0,1,2,255),('G','I')):
  objects=copy.deepcopy(OBJECTS);objects[1][3:9]=[gate,mission,queued,255,b18,b19]
  add('complete_Building_helpers_exact_animation_bytes_and_actual_mission_children',objects=objects,steps=[[k,1,0,0]])
 # House pointer equality, index equality (including -1), null object/owner and
 # x86 low-five-bit shift behavior are distinct branches.
 indices=(-2147483648,-33,-32,-2,-1,0,1,31,32,33,63,2147483647)
 for left,right,mask in itertools.product(indices,indices,(0,1,2,0x80000000,0xffffffff)):
  houses=copy.deepcopy(HOUSES);houses[0]=[left,mask];houses[1][0]=right
  objects=copy.deepcopy(OBJECTS);objects[0][2]=1
  add('House_pointer_index_signed_indices_and_masked_alliance_shift',houses=houses,objects=objects,steps=[['A',0,0,0]])
 for owner,mover in itertools.product((-1,0,1,2),(-1,0,1,4)):
  objects=copy.deepcopy(OBJECTS);objects[0][2]=owner
  add('null_object_null_owner_same_House_and_actual_Terrain_null_owner',objects=objects,steps=[['A',0,mover,0]])
 # A closed enemy gate continues; an open enemy gate short-circuits before an
 # allied closed gate. A later allied false is final. Self is skipped before kind.
 for heads,links,enemy_open in itertools.product(((0,3,1),(3,0,1),(2,3,1),(1,3,0),(4,3,1)),
   ((1,-1,-1,-1,-1),(2,-1,3,1,-1),(3,-1,-1,1,-1),(4,-1,-1,-1,1)),(0,1)):
  h=HEADER.copy();h[5:8]=heads;objects=copy.deepcopy(OBJECTS)
  for obj,next_ in zip(objects,links):obj[1]=next_
  objects[3][4]=24 if enemy_open else 2;objects[3][7:9]=[0,1 if enemy_open else 0]
  add('primary_list_self_skip_nongate_and_enemy_early_return_order',h=h,objects=objects,
   steps=[['C',0,51,72],['C',0,52,72],['C',1,-1,-1]])
 for x,y in ((51,72),(52,72),(-1,1),(511,0),(512,0),(-32768,64),(32767,0),(32767,32767),(-32768,-32768),(0,512),(0,-1)):
  for resident in (0,1):
   h=HEADER.copy();h[3:5]=[-1,-1]
   index=y*512+x
   if resident and 0<=index<262144:h[3]=index
   add('signed_combined_word_index_null_slot_shared_fallback_and_primary_only',h=h,
    steps=[['C',0,x,y],['C',0,-32768,32767],['C',0,x,y]])
 for tick,pad1,pad2 in itertools.product((-2147483648,-1,0,2147483647),(-1515870811,0,2147483647),(0,7)):
  h=HEADER.copy();h[:3]=[tick,pad1,pad2]
  add('ordered_actual_Set_Queue_Commence_writes_and_supplied_animation_progression',h=h,
   steps=[['C',0,51,72],['C',0,51,72],['T',1,0,1],['C',0,51,72],['I',1,0,0],['T',1,0,2],['C',0,51,72]])
 for i in range(100):
  h=HEADER.copy();h[:3]=[rng.randint(-2147483648,2147483647) for _ in range(3)];h[5:8]=[rng.randrange(-1,5) for _ in range(3)]
  objects=copy.deepcopy(OBJECTS);houses=[[rng.choice(indices),rng.getrandbits(32)] for _ in range(3)]
  for j,obj in enumerate(objects):
   obj[1]=rng.choice([-1,*range(j+1,5)]);obj[2]=rng.randrange(3);obj[3]=rng.choice((0,1,128,255))
   obj[4:9]=[rng.choice((-1,2,19,24,28)),rng.choice((-1,7,24)),rng.randrange(256),rng.choice((0,1,2,255)),rng.choice((0,1,2,255))]
  add('stable_shared_list_aliased_heads_signed_mission_and_upper_bytes',h=h,houses=houses,objects=objects,
   steps=[['C',rng.randrange(-1,5),51,72],['C',rng.randrange(-1,5),52,72],['C',0,-1,-1]])
 require(all(o.entries.values()) and all(o.kind_return_checks.values()))
 return commands,expected,labels,{'groups':groups,'audited_original_calls':o.audit_calls,'actual_entries':o.entries,
  'kind_return_checks':o.kind_return_checks,'entered_distinct_instructions':len(o.instructions),'selected_original_stores':o.selected_stores,
  'supplied_child_entry_padding_stores':o.supplied_padding_stores,'supplied_animation_transitions':o.supplied_animation_transitions,
  'initial_records_and_opaque_timer_padding_supplied':True,'gate_animation_admission_Process_runtime_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/movement-gate-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/movement-gate-v3')
 p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=private_path(source.parent/'report.json',a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh gate destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native gate: '+proc.stderr.strip())
 actual=[line.split() for line in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Gate result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Gate {i} {labels[i]} {commands[i]}: {x} != {y}')
 safety=['','W 0','bad',command()+' trailing',command(steps=[]),command(steps=[['C',0,32768,0]]),command(steps=[['G',0,0,0]]),command(steps=[['A',-1,0,0]]),command(steps=[['T',1,256,0]])]
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Gate native refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Gate run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} base gate results / {metadata["audited_original_calls"]:,} original calls: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
