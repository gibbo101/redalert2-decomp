#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Nearby Cell search policy, actual lookup/sqrt and supplied decision services."""
import argparse,copy,itertools,json,random,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_nearby_location import verify
NATIVE=('tests/nearby_location_vectors.cpp','src/sim/NearbyLocation.cpp','src/render/Lighting.cpp','src/assets/RenderData.cpp','src/assets/PreparedData.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),'tests/nearby_location/CMakeLists.txt','tests/original_nearby_location.py',
 'tests/compare_nearby_location.py','tests/test_nearby_location_evidence.py','tools/verify_nearby_location.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
FLAGS=dict(actual_complete_nearby_location_root=True,actual_inline_lookup_and_table_sqrt=True,
 supplied_permission_rectangle_burrowable_projection=True,supplied_initial_Cells_dimensions_frame_sentinel=True,
 diagnostic_boundary_mutations_not_gameplay=True,Unit_Scatter_executed=False,Advance6_executed=False,
 Process_joined=False,production_owned_world_join=False,general_pathfinding_recovered=False,runtime_enabled=False)
SCALARS='dimension0 dimension1 frame speed zone movement alternate width height overlay match burrow bridge skip flip_at mutation mutation_frame'.split()
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported nearby-location evidence/input')
def defaults():
 cells=[[512*y+x,x,y,0,0,1,1,1,1] for y in range(47,54) for x in range(47,54)]
 cells[24][6]=0 # center rectangle refused: actually search a neighboring destination
 cells.append([-1,-7,5,0,0,0,0,0,0])
 return dict(mode=0,source=[50,50],close=[0,0],empty=[0,0],dimension0=2,dimension1=2,frame=0,speed=1,zone=-1,movement=0,alternate=0,width=1,height=1,overlay=0,match=1,burrow=0,bridge=1,skip=0,flip_at=0,mutation=0,mutation_frame=7,mutation_close=[55,50],cells=cells)
def command(**kw):
 c=defaults();c.update(kw)
 values=[c['mode'],*c['source'],*c['close'],*c['empty'],*[c[k] for k in SCALARS],*c['mutation_close'],len(c['cells']),*itertools.chain.from_iterable(c['cells'])]
 return 'N '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='N');v=list(map(int,t[1:]));require(len(v)>=27)
 c=dict(mode=v[0],source=v[1:3],close=v[3:5],empty=v[5:7]);at=7
 c.update(zip(SCALARS,v[at:at+len(SCALARS)]));at+=len(SCALARS)
 c['mutation_close']=v[at:at+2];at+=2;count=v[at];at+=1
 require(1<=count<=128 and len(v)==at+9*count);c['cells']=[v[i:i+9] for i in range(at,len(v),9)]
 i32=lambda n:-2147483648<=n<=2147483647;word=lambda n:-32768<=n<=32767
 require(0<=c['mode']<4 and all(word(n) for k in ('source','close','empty','mutation_close') for n in c[k]))
 require(all(i32(c[k]) for k in ('dimension0','dimension1','frame','speed','zone','movement','width','height','mutation_frame')))
 require(0<=c['alternate']<=0xffffffff and all(0<=c[k]<=255 for k in ('overlay','match','burrow','bridge','skip')))
 require(0<=c['flip_at']<=100000 and 0<=c['mutation']<=2)
 slots=set()
 for i,row in enumerate(c['cells']):
  slot,x,y,level,flags,*decisions=row
  require(-1<=slot<262144 and word(x) and word(y) and -128<=level<=127 and 0<=flags<=0xffffffff and all(n in (0,1) for n in decisions))
  require((slot==-1)==(i==count-1))
  if slot!=-1:require(slot not in slots);slots.add(slot)
 return c
def identities(a):
 return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},render_data_sha256=hash_file(a.render_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(isinstance(row,list) and all(isinstance(n,str) for n in row) and row.count('state')==1)
def generate(a):
 from original_nearby_location import NearbyLocationOracle
 o=NearbyLocationOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x5502e0)
 def add(label,**kw):
  cmd=command(**kw)
  try:row=o.run(parse(cmd))
  except BaseException:
   print('Failed nearby case',len(commands),label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
 for mode,frame in itertools.product(range(4),range(16)):add('frame_remainder_neighbor_order',mode=mode,frame=frame)
 for key,values in (('alternate',(1,255,256,0x80000001)),('zone',(-2147483648,-1,0,65535,2147483647)),('match',(0,128,255)),('burrow',(1,128,255)),('bridge',(0,128,255)),('skip',(1,128,255)),('overlay',(1,128,255)),('width',(-1,0,3)),('height',(-1,0,3))):
  for value in values:add('raw_arguments_'+key,**{key:value})
 for mode,close in itertools.product(range(4),([55,50],[50,55],[45,50],[50,45],[51,51],[49,49])):
  add('preferred_target_distance_and_first_tie',mode=mode,close=close)
 for i in range(1,9):add('projection_requeried_and_partition_changes',flip_at=i)
 cells=defaults()['cells'];cells[24][6]=1
 for frame in (0,1,2147483647,-2147483648):add('radius_zero_duplicates',cells=cells,frame=frame)
 for cells in (defaults()['cells'],[[-1,-7,5,0,0,1,1,1,0]]):
  for c in cells:c[8]=0
  for alternate,flip,frame in ((0,0,0),(0,0,23),(0,0,2147483647),(0,0,-2147483640),(1,0,1),(256,0,3),(0,24,5)):
   add('capacity24_or_other_projection_selection',cells=cells,alternate=alternate,flip_at=flip,frame=frame,match=0)
 for dims in ((0,0),(-1,0),(1,0),(1,1),(31,1),(2147483647,1),(-2147483648,-2147483648)):
  cells=[[-1,-7,5,0,0,0,0,0,0]];add('wrapped_dimensions_clamp_empty_search',dimension0=dims[0],dimension1=dims[1],cells=cells)
 for source in ([32767,0],[-32768,64],[0,32767],[0,-32768],[-1,0],[512,-1]):
  cells=[[-1,-7,5,-128,0x100,1,1,1,1]]
  add('word_wrap_and_shared_fallback',source=source,cells=cells,skip=1,alternate=1)
 for level,flags,alternate in itertools.product((-128,-2,-1,0,1,2,127),(0,0x100),(0,1)):
  cells=defaults()['cells'];cells[24][3]=level;cells[24][4]=flags
  add('signed_level_and_bridge_threshold',cells=cells,alternate=alternate)
 for decision in (5,6,7):
  cells=defaults()['cells']
  for row in cells:row[decision]=0
  add('required_service_false_short_circuit',cells=cells,burrow=1)
 for mutation in (1,2):add('diagnostic_late_frame_or_target_read',mutation=mutation,mutation_frame=13,mutation_close=[45,50])
 for empty,close in (([7,9],[7,9]),([7,9],[0,0]),([0,9],[0,0]),([9,0],[9,0])):
  add('distinct_supplied_sentinel',empty=empty,close=close)
 for mode,source,close in itertools.product(range(4),([32767,32767],[32767,0],[0,0]),([-32768,-32768],[-32768,0],[0,0])):
  if source==[0,0] and close==[0,0]:continue
  add('wrapped_signed_squared_distance_with_actual_negative_sqrt',mode=mode,source=source,close=close,empty=[7,9],cells=[[-1,-7,5,0,0,1,1,1,1]])
 for i in range(80):
  cells=defaults()['cells']
  for row in cells:
   row[3]=rng.randint(-3,3);row[4]=rng.choice((0,0x100,0x1000,0x1100));row[5:9]=[rng.randrange(2) for _ in range(4)]
  add('seeded_heterogeneous_cells',cells=cells,mode=i%4,frame=rng.randrange(32768),alternate=rng.choice((0,1,255,256)),match=rng.choice((0,1)),burrow=rng.randrange(2),bridge=rng.randrange(2),skip=rng.randrange(2),close=rng.choice(([0,0],[55,51])))
 require(o.counts['0x5502e0']==len(commands) and o.counts['candidate_store']>=24 and o.counts['distance']>0)
 require(all(o.counts[k]>0 for k in ('preferred','other','frame_preferred','frame_other','radius.31')))
 require(all(o.counts[k]>0 for k in ('capacity24','zone65535_normalized','level_difference.1','level_difference.2')))
 require(all(o.counts[k]>0 for k in ('sqrt.negative','sqrt.zero','sqrt.positive')))
 require(all(o.counts['return.'+hex(a)]>0 for a in (0x550c02,0x550c21,0x550ccb,0x550ce7)))
 require(all(o.writes[hex(a)]>0 for a in (0x55051a,0x5506c5,0x55089d,0x550a36)))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,
  original_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),
  full_arena_fallback_code_input_and_caller_checks=True,native_machine_store_order_claim=False)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 require(p.returncode==0);rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Nearby location differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/nearby-location-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 a.render_data=ROOT/'private/derived/ra2-1006/render-data.bin'
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'nearby-location sequences PASS')
if __name__=='__main__':main()
