#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual Unit Scatter policy with named unjoined world/destination services."""
import argparse,itertools,json,random,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_scatter import verify
SCALARS='mission queued queued_byte train control9 control7 ignore_mission ignore_destination field5c8 field5b9 field599 destination target bridge type5a4 current_level layer level height tick desired start timer duration rate references global_references disabled next1 next2 mutate_point repeats'.split()
ARRAYS=dict(position=3,coordinates=3,away=3,empty_cell=2,path_result=2,neighbors=16,bounds=8,admissions=8,projections=8,flags=8,table=250)
NATIVE=('tests/unit_scatter_vectors.cpp','src/sim/OriginalRandom.cpp','src/sim/UnitDiscovery.cpp','src/sim/Targeting.cpp','src/assets/MovementData.cpp','src/assets/PreparedData.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),'tests/unit_scatter/CMakeLists.txt','tests/original_unit_scatter.py','tests/compare_unit_scatter.py','tests/test_unit_scatter_evidence.py','tools/verify_unit_scatter.py','tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
FLAGS=dict(actual_Unit_Scatter_parent=True,actual_eligibility_mission_Facing_bearing_RNG=True,
 actual_Drive_QI_classid_AddRef_Release=True,atomic_operations_supplied=True,
 map_coordinates_layer_level_bounds_admission_projection_supplied=True,
 destination_and_pathfinder_supplied=True,supplied_initial_records=True,
 Advance6_executed=False,owned_world_join=False,runtime_enabled=False,
 general_COM_or_destruction_recovered=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Unit Scatter evidence/input')
def defaults():
 return dict(mission=7,queued=-1,queued_byte=173,train=0,control9=1,control7=0,
 ignore_mission=0,ignore_destination=0,field5c8=0,field5b9=0,field599=0,destination=0,target=0,
 bridge=0,type5a4=3,current_level=0,layer=0,level=0,height=104,tick=100,desired=0,start=0,timer=-1,duration=0,rate=1280,
 references=3,global_references=7,disabled=0,next1=0,next2=103,mutate_point=0,repeats=1,
 position=[128,128,0],coordinates=[128,128,0],away=[-128,128,0],empty_cell=[0,0],path_result=[0,0],
 neighbors=[(0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1)],
 bounds=[1]*8,admissions=[0]*8,projections=[1]*8,flags=[0]*8,table=[0]*250)
def command(**kw):
 c=defaults();c.update(kw);values=[c[k] for k in SCALARS]
 for k in ARRAYS:values.extend(itertools.chain.from_iterable(c[k]) if k=='neighbors' else c[k])
 return 'U '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='U');v=list(map(int,t[1:]));require(len(v)==len(SCALARS)+sum(ARRAYS.values()))
 c=dict(zip(SCALARS,v));at=len(SCALARS)
 for k,n in ARRAYS.items():c[k]=v[at:at+n];at+=n
 c['neighbors']=list(zip(c['neighbors'][::2],c['neighbors'][1::2]))
 require(-1<=c['mission']<=31 and -1<=c['queued']<=31 and 0<c['references']<0x7fffffff and 0<=c['global_references']<=0xffffffff)
 for k in ('queued_byte','train','control9','control7','ignore_mission','ignore_destination','field5c8','field5b9','field599','bridge','layer','disabled'):require(0<=c[k]<=255)
 for k in ('destination','target','mutate_point'):require(c[k] in (0,1))
 require(1<=c['repeats']<=512)
 require(-128<=c['current_level']<=127 and 0<=c['next1']<250 and 0<=c['next2']<250)
 require(all(0<=c[k]<=65535 for k in ('desired','start','rate')))
 require(all(-2147483648<=c[k]<=2147483647 for k in ('type5a4','level','height','tick','timer','duration')))
 require(all(-2147483648<=n<=2147483647 for k in ('position','coordinates','away') for n in c[k]))
 require(all(abs(x-y)<=1<<20 for x,y in zip(c['position'][:2],c['away'][:2])))
 require(all(-32768<=n<=32767 for k in ('empty_cell','path_result') for n in c[k]))
 require(len(set(c['neighbors']))==8 and (0,0) not in c['neighbors'] and all(-32768<=n<=32767 for p in c['neighbors'] for n in p))
 require(all(n in (0,1) for k in ('bounds','projections') for n in c[k]) and all(0<=n<=7 for n in c['admissions']) and all(0<=n<=0xffffffff for k in ('flags','table') for n in c[k]))
 return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},direction_data=hash_file(a.direction_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006')
 require(e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(isinstance(row,list) and bool(row) and all(isinstance(v,str) for v in row) and row.count('state')==1)
def generate(a):
 from original_unit_scatter import UnitScatterOracle
 o=UnitScatterOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x7072d0)
 def add(label,**kw):
  cmd=command(**kw);expected.append(o.run(parse(cmd)));commands.append(cmd);labels.append(label);groups[label]=groups.get(label,0)+1
 for mission,queued,train in itertools.product(range(-1,32),(-1,0,6,7,16,19),(0,1,255)):
  add('actual_eligibility_three_mission_reads_queued_fallback_train_and_queue',mission=mission,queued=queued,train=train)
 for k in ('control9','control7','ignore_mission','ignore_destination','field5c8','field5b9','field599','destination','target'):
  for n in (0,1,128,255):
   if k in ('destination','target') and n>1:continue
   add('raw_control_and_early_exits',**{k:n})
 for desired,start,rate,timer,duration in ((32768,0,1280,100,5),(32768,0,1280,-1,5),(32768,0,1280,99,1),(65535,1,0,100,5),(65535,1,65535,100,5),(32768,0,1280,2147483647,5)):
  add('actual_Facing_rotation_and_expiry',desired=desired,start=start,rate=rate,timer=timer,duration=duration)
 for flags,projection in itertools.product((0,0x100,0xffffffff),(0,1)):
  for free in range(8):
   admissions=[7]*8;admissions[free]=0
   add('all_neighbor_positions_first_free_projection_and_flags',admissions=admissions,flags=[flags]*8,projections=[projection]*8)
 for bounds in ([0]*8,[1]*8):
  for sentinel in ([0,0],[7,9],[-1,-1]):add('bounds_before_admission_zero_initialized_locals_nonzero_sentinel',bounds=bounds,admissions=[7]*8,empty_cell=sentinel)
 for current,layer,height in itertools.product((-128,-1,0,1,127),(0,1,128,255),(-2147483648,104,2147483647)):
  add('signed_level_byte_layer_and_wrapped_world_height',current_level=current,layer=layer,height=height,level=2147483647)
 for coord in ((-257,-255,71),(-1,-256,-9),(8388607,-8388608,0),(-8388864,8388608,123)):
  add('signed_divide_before_word_projection_and_neighbor_wrap',coordinates=coord,projections=[0]*8)
 for away in ((-128,128,0),(384,128,0),(128,-128,0),(128,384,0),(128,128,7),(-700000,700000,0)):
  for raw in (0,1,2,3,0xffffffff):
   table=[0]*250;table[0]=raw
   add('actual_away_bearing_rng_rejection_consumption',away=away,table=table,next1=0,next2=103)
 for target,ignore,disabled in itertools.product((0,1),(0,1),(0,255)):
  for raw in range(8):
   table=[0]*250;table[0]=raw
   add('target_one_in_four_and_heading_rng_consumption',target=target,ignore_mission=ignore,disabled=disabled,table=table)
 for path in ((0,0),(12,-8),(-32768,32767)):
  for coord in ((128,128,0),(-257,-65537,88)):
   add('zero_coordinate_pathfinder_policy_and_no_queue',away=[0,0,0],path_result=path,coordinates=coord,bridge=255)
 for heading in (0,4095,4096,8191,32768,65535):add('borrowed_point_changed_by_diagnostic_control_service_uses_Facing',mutate_point=1,desired=heading)
 for destination,ignore,field599,control9,ignoreMission in itertools.product((0,1),(0,1,255),(0,1,255),(0,1),(0,1)):
  add('destination_and_mission_control_short_circuit_combinations',destination=destination,ignore_destination=ignore,field599=field599,control9=control9,ignore_mission=ignoreMission)
 for mission,queued in ((-1,7),(2,-1),(2,5),(7,-1),(19,7),(28,7)):
  add('later_Scatter_calls_retain_queued_mission_RNG_and_reference_ownership',mission=mission,queued=queued,repeats=9,flags=[0x100]*8,table=[rng.getrandbits(32) for _ in range(250)])
 add('long_retained_RNG_sequence_wraps_both_indices',repeats=512,target=1,table=[rng.getrandbits(32) for _ in range(250)],next1=249,next2=249)
 for i in range(128):
  add('seeded_heterogeneous_policy_and_cleanup',mission=rng.choice((2,7,19,28,-1)),queued=7,
   destination=rng.randrange(2),ignore_destination=rng.choice((0,1,255)),ignore_mission=rng.randrange(2),
   control9=rng.choice((0,1,128)),control7=rng.choice((0,0,1)),target=rng.randrange(2),
   coordinates=[rng.randint(-100000,100000),rng.randint(-100000,100000),rng.randint(-100,100)],
   bounds=[rng.randrange(2) for _ in range(8)],admissions=[rng.randrange(8) for _ in range(8)],
   projections=[rng.randrange(2) for _ in range(8)],flags=[rng.choice((0,0x100,0x200)) for _ in range(8)],
   next1=rng.choice((0,249)),next2=rng.choice((103,249)),table=[rng.getrandbits(32) for _ in range(250)],
   references=rng.choice((1,3,0x7ffffffe)),global_references=rng.choice((0,1,0xffffffff)))
 require(o.counts['0x7072d0']==o.audit_calls and o.counts['atomic_inc']==o.counts['atomic_dec']>0)
 require(all(o.counts[k]>0 for k in ('coordinates','lookup','layer','bounds','level','admission','projection','pathfinder','destination','0x594cb0','0x6388a0','0x4b8be0','0x4ba600')))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,
  original_arena_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),
  full_arena_and_caller_checks=o.audit_calls,selected_native_machine_write_order_claim=False)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.direction_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 require(p.returncode==0);rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Unit Scatter differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/unit-scatter/unit-scatter-vectors')
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-scatter-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'unit-scatter sequences PASS')
if __name__=='__main__':main()
