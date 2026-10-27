#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary Unit/Foot Cell destinations with actual Drive/floor/map children."""
import argparse,itertools,json,math,random,re,struct,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_destination import verify
SCALARS='mission queued forced suspended reached field490 initial_target buffer owned capacity count powered field5c8 field5c0 field3fc guard_start guard_remaining disabled1bc disabled1c0 references global_references height delay fallback_flags percentage_bits'.split()
ARRAYS=dict(position=3,destination=3,head=3,queue=24,cells=12)
NATIVE=('tests/unit_destination_vectors.cpp','src/sim/UnitDiscovery.cpp','src/assets/MapFloorHeight.cpp','src/assets/MapCoordinateCell.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),'tests/unit_destination/CMakeLists.txt','tests/original_unit_destination.py','tests/compare_unit_destination.py','tests/test_unit_destination_evidence.py','tools/verify_unit_destination.py','tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
FLAGS=dict(actual_complete_Unit_and_Foot_roots=True,actual_Drive_commands_and_guards=True,
 actual_Cell_center_floor_and_map_lookup=True,actual_QI_classid_reference_lifetime=True,
 heap_disposal_and_initial_records_supplied=True,temporary_padding_supplied_except_coordinate_alias=True,
 non7_non16_powered_ordinary_Cell_profile=True,bridge_adjustment_supported=False,
 Unit_Scatter_joined=False,Advance6_executed=False,owned_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported destination evidence/input')
def bits(x):return struct.unpack('<Q',struct.pack('<d',x))[0]
def defaults():
 return dict(mission=2,queued=2,forced=0,suspended=0,reached=173,field490=391,initial_target=0,
  buffer=0,owned=0,capacity=7,count=3,powered=1,field5c8=0,field5c0=-1,field3fc=0,
  guard_start=-1,guard_remaining=0,disabled1bc=0,disabled1c0=0,references=3,global_references=7,
  height=104,delay=5,fallback_flags=0,percentage_bits=bits(1.),position=[128,128,0],destination=[0,0,0],head=[0,0,0],
  queue=[3,5,-1,*range(21)],cells=[[3,4,0,0,0,1],[5,6,1,3,0,1]],actions=[[1,1,1,100,23]])
def command(**kw):
 c=defaults();c.update(kw);values=[c[k] for k in SCALARS]
 for k in ARRAYS:values.extend(itertools.chain.from_iterable(c[k]) if k=='cells' else c[k])
 values.append(len(c['actions']));values.extend(itertools.chain.from_iterable(c['actions']))
 return 'Z '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='Z');v=list(map(int,t[1:]));at=len(SCALARS);require(len(v)>=at+sum(ARRAYS.values())+1)
 c=dict(zip(SCALARS,v))
 for k,n in ARRAYS.items():c[k]=v[at:at+n];at+=n
 c['cells']=[c['cells'][:6],c['cells'][6:]];count=v[at];at+=1
 require(1<=count<=64 and len(v)==at+5*count);c['actions']=[v[i:i+5] for i in range(at,len(v),5)]
 require(all(-1<=c[k]<=31 and c[k] not in (7,16) for k in ('mission','queued')))
 for k in ('forced','suspended','reached','owned','powered','disabled1bc','disabled1c0'):require(0<=c[k]<=255)
 require(c['powered']!=0 and c['field5c8']==0 and c['buffer'] in (0,1) and c['initial_target'] in (0,1,2))
 require(0<c['references']<0x7fffffff and 0<=c['global_references']<=0xffffffff and 0<=c['percentage_bits']<=0xffffffffffffffff)
 require(math.isfinite(struct.unpack('<d',struct.pack('<Q',c['percentage_bits']))[0]))
 require(0<=c['fallback_flags']<=0xffffffff and c['fallback_flags']&0x100==0)
 for k in ('field490','capacity','count','field5c0','field3fc','guard_start','guard_remaining','height','delay'):require(-2147483648<=c[k]<=2147483647)
 require(all(-2147483648<=n<=2147483647 for k in ('position','destination','head','queue') for n in c[k]))
 for x,y,level,ramp,flags,present in c['cells']:
  require(-32768<=x<=32767 and -32768<=y<=32767 and -128<=level<=127 and 0<=ramp<=20 and 0<=flags<=0xffffffff and flags&0x100==0 and present in (0,1))
 for mode,target,flag,tick,padding in c['actions']:
  require(mode in (0,1) and target in (0,1,2) and 0<=flag<=255 and -2147483648<=tick<=2147483647 and -2147483648<=padding<=2147483647)
 return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006')
 require(e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(isinstance(row,list) and bool(row) and all(isinstance(v,str) for v in row) and row.count('state')==1)
def generate(a):
 from original_unit_destination import UnitDestinationOracle
 o=UnitDestinationOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x7053f0)
 def add(label,**kw):
  cmd=command(**kw);expected.append(o.run(parse(cmd)));commands.append(cmd);labels.append(label);groups[label]=groups.get(label,0)+1
 for mode,target,initial,forced,suspended,flag in itertools.product((0,1),(0,1,2),(0,1,2),(0,255),(0,173),(0,1,255)):
  add('complete_roots_equal_forced_null_suspended_flag',initial_target=initial,forced=forced,suspended=suspended,actions=[[mode,target,flag,100,-91]])
 for buffer,owned,flag,target in itertools.product((0,1),(0,1,255),(0,1,255),(0,1)):
  add('actual_vector_clear_null_owned_unowned_retained_buffer',buffer=buffer,owned=owned,actions=[[1,target,flag,100,23]])
 for ramp,level in itertools.product(range(21),(-128,-1,0,1,127)):
  add('actual_Cell_center_signed_level_all_ramps_cold_warm_floor',cells=[[3,4,level,ramp,0,1],[5,6,-1,(ramp+7)%21,0,1]],actions=[[1,1,1,100,23],[0,2,0,101,-31],[0,1,1,102,99]])
 for x,y,present in itertools.product((-32768,-2,-1,0,1,32767),(-32768,-1,0,1,32767),(0,1)):
  add('signed_center_division_map_fallback_alias_identity',cells=[[x,y,-1,3,2,present],[5,6,0,0,0,1]])
 for dest,head,position in itertools.product(([0,0,0],[0,0,1],[1,0,0]),([0,0,0],[128,128,0],[128,128,999],[129,128,0],[128,129,0]),([128,128,0],[-1,0,1])):
  add('actual_IsMoving_destination_head_XY_not_head_Z',destination=dest,head=head,position=position)
 for key,values in dict(field5c0=(-2147483648,-1,0,1,2147483647),field3fc=(-2147483648,-1,0,1,2147483647),disabled1bc=(0,1,128,255),disabled1c0=(0,1,128,255)).items():
  for value in values:add('actual_Move_To_short_circuit_guards',**{key:value})
 for start,remaining,tick in itertools.product((-2147483648,-1,0,100,2147483647),(-2147483648,-1,0,1,100,2147483647),(-2147483648,0,99,100,101,2147483647)):
  add('actual_guard_timer_signed_wrap_and_expiry',guard_start=start,guard_remaining=remaining,actions=[[1,1,1,tick,17]])
 for mission in range(-1,32):
  if mission not in (7,16):add('actual_mission_getter_fallback_non_special_profile',mission=mission,queued=2)
 for fraction,head in itertools.product((-1.,-0.,0.,0.1,0.30000001192092896,1.,2.),([0,0,0],[1,2,3])):
  add('actual_stop_cap_retains_committed_head_queue_tails',initial_target=1,percentage_bits=bits(fraction),head=head,actions=[[1,0,0,100,-31]])
 for globalrefs,refs in itertools.product((0,1,0x7fffffff,0xffffffff),(1,3,0x7ffffffe)):
  add('ordered_interface_global_wrap_and_retained_counts',global_references=globalrefs,references=refs)
 for height,level in itertools.product((-2147483648,0,104,208,2147483647),(-128,-1,1,127)):
  add('wrapped_level_height_product_and_cold_floor',height=height,cells=[[3,4,level,3,0,1],[5,6,0,0,0,1]])
 for _ in range(96):
  add('retained_mixed_roots_targets_timers_and_queue_tails',buffer=rng.randrange(2),owned=rng.choice((0,1,255)),
   suspended=rng.choice((0,1,255)),powered=rng.choice((1,128,255)),
   queue=[rng.randint(-2147483648,2147483647) for _ in range(24)],
   actions=[[rng.randrange(2),rng.randrange(3),rng.choice((0,1,255)),rng.randint(-2147483648,2147483647),rng.randint(-2147483648,2147483647)] for _ in range(rng.randint(2,16))])
 add('long_retained_alternating_target_interface_and_clears',buffer=1,owned=255,actions=[[i%2,(i%3),255,(2147483600+i+2147483648)%4294967296-2147483648,-31] for i in range(64)])
 require(all(o.counts[hex(k)]>0 for k in (0x7053f0,0x4c8030,0x49fe30,0x49fef0,0x4cde30,0x410290,0x47ba50,0x4706c0,0x548000,0x70a240,0x6d8e80,0x4cd080,0x6d6df0,0x6d6e00,0x4a47f0)))
 require(all(o.counts['floor.ramp.'+str(r)]>0 for r in range(21)))
 require(all(o.counts['guard.'+hex(off)+'.'+str(value)]>0 for off in (0x324,0x328,0x1bc,0x1c0) for value in (0,1)))
 require(all(o.counts['IsMoving.'+str(value)]>0 for value in (0,1)))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,
  original_arena_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),
  full_arena_and_caller_checks=o.audit_calls,selected_native_machine_write_order_claim=False)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Destination runner failed',p.returncode,p.stderr[:2000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Destination differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-destination-v3');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'unit-destination sequences PASS')
if __name__=='__main__':main()
