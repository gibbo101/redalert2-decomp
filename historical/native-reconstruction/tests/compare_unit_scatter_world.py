#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary Scatter with actual shared world queries and Cell commands."""
import argparse,copy,itertools,json,random,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_scatter_world import verify
SCALARS='queued queued_byte forced suspended field5b9 field599 target bridge registry poolx pooly references global_references initial_target buffer owned capacity count field490 powered field5c8 field5c0 field3fc guard_start guard_remaining disabled1bc disabled1c0 floor_height layer_height project_height delay padding control9 control7 desired start timer duration rate disabled next1 next2'.split()
NATIVE=('tests/unit_scatter_world_vectors.cpp','src/sim/OriginalRandom.cpp','src/sim/UnitDiscovery.cpp','src/sim/Targeting.cpp','src/sim/FootCoordinates.cpp','src/sim/UnitAdmission.cpp','src/sim/MovingUnitAdmission.cpp','src/sim/MovementGate.cpp','src/assets/MapCellChildren.cpp','src/assets/MapFloorHeight.cpp','src/assets/MapCoordinateCell.cpp','src/assets/MovementData.cpp','src/assets/PreparedData.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),'tests/unit_scatter_world/CMakeLists.txt','tests/original_unit_scatter_world.py','tests/compare_unit_scatter_world.py','tests/test_unit_scatter_world_evidence.py','tools/verify_unit_scatter_world.py','tools/verify_unit_scatter.py','tools/verify_unit_destination.py','tools/verify_foot_layer.py','tools/verify_map_floor_height.py','tools/verify_unit_admission.py','tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
FLAGS=dict(actual_complete_Scatter_world_and_Cell_destination=True,actual_coordinates_layer_floor_permission_level_admission_projection=True,
 shared_actor_Drive_mission_RNG_lifetime_and_Cells=True,mission7_Cell_queue_head_retained=True,
 initial_records_and_mission_control_bytes_supplied=True,zero_point_pathfinder_supported=False,
 mission16_Cell_policy_supported=False,bridge_adjusted_commands_supported=False,owned_heap_disposal_supported=False,
 Cell_dispatch_joined=False,Advance6_executed=False,Process_joined=False,owned_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Scatter world evidence/input')
def defaults():
 # Authored stationary admission fixture, not extracted original records.
 OBJECTS=[[1,-1,0,0,2,0,0,5,0,0,0,0,0,-1,-1,0,0],
  [1,-1,0,0,2,0,0,5,0,0,0,0,0,-1,-1,0,0],
  [6,-1,0,1,2,0,0,1,0,0,0,0,0,-1,-1,0,0],
  [1,-1,1,0,2,0,0,5,0,0,0,0,0,-1,-1,0,0],
  [6,-1,1,1,24,0,1,1,0,0,0,0,0,-1,-1,0,0]]
 cells=[[y*512+x,x,y,0,0,0,1,-1,-1,0,0,-1,-1,0] for y in (49,50,51) for x in (49,50,51)]
 cells.append([-1,-7,5,0,0,0,2,-1,-1,0,0,-1,-1,0])
 objects=copy.deepcopy(OBJECTS);objects[0][15:17]=[0,0]
 return dict(projection=False,queued=2,queued_byte=173,forced=0,suspended=0,field5b9=0,field599=0,target=0,bridge=0,registry=-1,poolx=50,pooly=50,references=3,global_references=7,initial_target=0,buffer=0,owned=0,capacity=7,count=3,field490=391,powered=1,field5c8=0,field5c0=-1,field3fc=0,guard_start=-1,guard_remaining=0,disabled1bc=0,disabled1c0=0,floor_height=104,layer_height=104,project_height=104,delay=5,padding=-31,control9=1,control7=0,desired=0,start=0,timer=-1,duration=0,rate=1280,disabled=0,next1=0,next2=103,
 position=[12928,12928,0],head=[0,0,0],destination=[0,0,0],queue=[3,5,-1,*range(21)],shape=[64,0,0,64,64],speeds=[0x3f800000]*12,table=[0]*250,cells=cells,objects=objects,actions=[[12672,12928,0,0,0,100]])
def command(**kw):
 c=defaults();c.update(kw);values=[c[k] for k in SCALARS]
 for k in ('position','head','destination','queue','shape','speeds','table'):values.extend(c[k])
 for k in ('cells','objects'):values.extend(itertools.chain.from_iterable(c[k]))
 values.append(len(c['actions']));values.extend(itertools.chain.from_iterable(c['actions']))
 return ('P ' if c['projection'] else 'J ')+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(t and t[0] in ('J','P'));v=list(map(int,t[1:]));at=len(SCALARS);require(len(v)>=at+3*3+24+5+12+250+140+85+1);c=dict(zip(SCALARS,v));c['projection']=t[0]=='P'
 for k,n in (('position',3),('head',3),('destination',3),('queue',24),('shape',5),('speeds',12),('table',250)):
  c[k]=v[at:at+n];at+=n
 for k,n,size in (('cells',10,14),('objects',5,17)):
  c[k]=[v[i:i+size] for i in range(at,at+n*size,size)];at+=n*size
 count=v[at];at+=1;require(1<=count<=64 and len(v)==at+6*count);c['actions']=[v[i:i+6] for i in range(at,len(v),6)]
 i32=lambda x:-2147483648<=x<=2147483647;byte=lambda x:0<=x<=255;word=lambda x:-32768<=x<=32767
 require(-1<=c['queued']<=31 and c['queued']!=16 and 0<c['references']<0x7fffffff and 0<=c['global_references']<=0xffffffff)
 for k in ('queued_byte','forced','suspended','field5b9','field599','bridge','owned','powered','field5c8','disabled1bc','disabled1c0','control9','control7','disabled'):require(byte(c[k]))
 require(c['target'] in (0,1) and c['buffer'] in (0,1) and not(c['buffer'] and c['owned']) and 0<=c['initial_target']<=10 and c['powered']!=0)
 require(-128<=c['registry']<=127 and word(c['poolx']) and word(c['pooly']) and all(0<=c[k]<=65535 for k in ('desired','start','rate')) and all(0<=c[k]<250 for k in ('next1','next2')))
 for k in ('capacity','count','field490','field5c0','field3fc','guard_start','guard_remaining','floor_height','layer_height','project_height','delay','padding','timer','duration'):require(i32(c[k]))
 require(all(i32(n) for k in ('position','head','destination','queue','shape') for n in c[k]) and all(0<=n<=0xffffffff for k in ('speeds','table') for n in c[k]))
 slots=[]
 for i,row in enumerate(c['cells']):
  slot,x,y,level,ramp,flags,land,head,ehead,occ,eocc,owner,eowner,abstract=row
  require(-1<=slot<262144 and word(x) and word(y) and -128<=level<=127 and 0<=ramp<=20 and all(0<=n<=0xffffffff for n in (flags,occ,eocc)) and 0<=land<12 and -1<=head<5 and -1<=ehead<5 and i32(owner) and i32(eowner) and byte(abstract) and not(abstract&1))
  if slot!=-1:require(i!=9 and slot==y*512+x and slot not in slots);slots.append(slot)
 require(c['cells'][9][0]==-1)
 for i,o in enumerate(c['objects']):
  require(o[0] in (1,6) and -1<=o[1]<5 and 0<=o[2]<3 and -1<=o[4]<=31 and all(byte(o[j]) for j in (3,5,6,7,8,9,10,11)) and i32(o[12]) and all(-1<=o[j]<5 for j in (13,14)) and all(o[j] in (0,1) for j in (15,16)))
  require(not i or o[13]==-1)
  require(not(c['objects'][0][9] and i and o[8]))
 require(c['objects'][0][0]==1 and c['objects'][0][13]==-1)
 for i in range(5):
  seen=set()
  while i!=-1:require(i not in seen);seen.add(i);i=c['objects'][i][1]
 for x,y,z,im,id,tick in c['actions']:
  require(all(i32(n) for n in (x,y,z,tick)) and byte(im) and byte(id) and (c['projection'] or ((x,y,z)!=(0,0,0) and all(abs(a-b)<=1<<20 for a,b in zip(c['position'][:2],(x,y))))))
 return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},direction_data_sha256=hash_file(a.direction_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and all(isinstance(n,str) for n in row) and row.count('state')==1)
def generate(a):
 from original_unit_scatter_world import UnitScatterWorldOracle
 o=UnitScatterWorldOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x7072d0)
 def add(label,**kw):
  cmd=command(**kw)
  try:row=o.run(parse(cmd))
  except BaseException:
   print('Failed world case',len(commands),label,flush=True);raise
  expected.append(row);commands.append(cmd);labels.append(label);groups[label]=groups.get(label,0)+1
 add('complete_default_join')
 for x,y in ((0,0),(-1,0),(-257,255),(-8388608,-8388608),(8388352,8388352),(8388096,8388096),(2147483647,-2147483648)):
  for level,flags in ((0,0),(-128,0x1000),(127,0x1100)):
   cells=defaults()['cells'];cells[-1][3]=level;cells[-1][5]=flags
   add('direct_projection_signed_word_edges',projection=True,cells=cells,actions=[[x,y,z,0,0,100] for z in (-2147483648,0,2147483647)])
 for mission in range(-1,32):
  objects=defaults()['objects'];objects[0][4]=mission
  add('raw_mission',objects=objects)
 objects=defaults()['objects'];objects[0][10]=1;add('train_eligibility_early_return',objects=objects)
 for duration,tick in ((10,100),(10,109),(10,110),(10,111),(2147483647,-2147483648)):
  add('rotating_early_return',desired=32768,start=0,timer=100,duration=duration,actions=[[12672,12928,0,0,0,tick]])
 for mission,queued in itertools.product((-1,2,7,19),(0,2,7,19,31)):
  objects=defaults()['objects'];objects[0][4]=mission
  add('queued_mission',objects=objects,queued=queued,actions=[[12672,12928,0,1,1,100]])
 for key,value in (('control9',0),('control7',1),('field5b9',1),('field5c8',1),('field599',1),('target',1)):
  add('control_guard',**{key:value})
  add('control_ignore',**{key:value},initial_target=5,actions=[[12672,12928,0,255,255,100]])
 for key,value in (('suspended',1),('field5c0',0),('field3fc',1),('guard_remaining',9),('disabled1bc',1),('disabled1c0',1),('forced',1),('buffer',1),('owned',1),('global_references',0xffffffff)):
  add('destination_guard_or_store',**{key:value})
 for start,remaining,tick in ((90,10,100),(90,11,100),(101,10,100),(-2147483648,2147483647,2147483647)):
  add('command_timer_wrap',guard_start=start,guard_remaining=remaining,actions=[[12672,12928,0,0,0,tick]])
 for target in range(1,11):
  for forced in (0,1):add('same_or_other_target',initial_target=target,forced=forced,actions=[[12672,12928,0,0,1,100]])
 for h in ([12928,12928,1],[13184,12928,0],[12672,12928,0],[0,0,1]):
  add('head_current_destination_distinct',head=h,destination=[17,29,31],actions=[[12672,12928,0,0,1,100]])
 for registry in (-128,-1,0,127):
  for poolx,pooly in ((50,50),(51,49),(-1,0),(32767,-32768)):
   add('registry_or_shared_fallback',registry=registry,poolx=poolx,pooly=pooly)
 for direction,(dx,dy) in enumerate(((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))):
  for low in range(4):
   table=[(i*37+low)&0xffffffff for i in range(250)]
   add('bearing_neighbor_RNG',table=table,actions=[[12928-dx*1024,12928-dy*1024,1,0,0,100]])
 for ramp in range(21):
  for delta in (-4,-1,0,1,4):
   cells=defaults()['cells']
   for i,c in enumerate(cells):c[3]=delta if i!=4 else 0;c[4]=ramp
   add('all_ramps_level_admission',cells=cells)
 for bridge,flags in itertools.product((0,1,2,255),(0,0x100,0x200,0x300,0x1000,0x1100)):
  cells=defaults()['cells']
  for c in cells:c[5]=flags
  add('raw_bridge_projection_flags',cells=cells,bridge=bridge,suspended=1)
 for height in (-104,0,1,104,2147483647,-2147483648):
  cells=defaults()['cells'];cells[4][3]=4;cells[4][4]=8
  add('separate_heights_wrapping',cells=cells,floor_height=height,layer_height=height,project_height=height,suspended=1)
 for dimension in (0,64,98,99,100,101,300):
  add('permission_shape',shape=[dimension,0,0,64,64])
 for i in range(9):
  cells=defaults()['cells'];cells[i][0]=-1
  add('missing_slot_shared_fallback',cells=cells)
 for point in ((-1,0,0),(-257,-511,33),(0,0,0),(8388480,8388480,0),(-8388608,-8388608,0)):
  add('signed_coordinate_edges',position=list(point),actions=[[point[0]+512,point[1]+128,1,0,0,100]])
 for resident in range(5):
  for extra in (0,1,2):
   cells=defaults()['cells'];objects=defaults()['objects']
   for c in cells:c[7]=resident
   if extra==1:objects[resident][12]=2
   if extra==2:objects[0][15:17]=[1,1]
   add('stationary_resident_admission',cells=cells,objects=objects)
 for occ,owner in itertools.product((1,16,32,63,0x80000020),(-1,0,1,33)):
  cells=defaults()['cells']
  for c in cells:c[9]=occ;c[11]=owner
  add('occupation_owner_admission',cells=cells)
 for bits in (0,0x80000000,0xbf800000,0x7f800001,0x7fc00000,1,0x7f800000):
  add('zero_unordered_signed_speeds',speeds=[bits]*12)
 for mission in (2,7,19,-1):
  objects=defaults()['objects'];objects[0][4]=mission
  add('retained_64_calls',objects=objects,next1=248,next2=249,table=[rng.getrandbits(32) for _ in range(250)],actions=[[12672+(i%3)*128,12928-((i+1)%3)*128,1,1,1,100+i] for i in range(64)])
 for _ in range(96):
  cells=defaults()['cells']
  for c in cells:c[3]=rng.choice((-1,0,1));c[4]=rng.randrange(21);c[9]=rng.choice((0,0,32))
  add('deterministic_mixed_world',cells=cells,desired=rng.randrange(65536),start=rng.randrange(65536),table=[rng.getrandbits(32) for _ in range(250)],position=[rng.randrange(12800,13056),rng.randrange(12800,13056),rng.randrange(-100,101)])
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,original_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),selected_native_machine_write_order_claim=False)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.direction_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Scatter world runner failed',p.returncode,p.stderr[:2000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Scatter world differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-scatter-world-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'unit-scatter-world sequences PASS')
if __name__=='__main__':main()
