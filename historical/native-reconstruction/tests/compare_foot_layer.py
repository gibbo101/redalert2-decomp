#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Object/Foot layer with actual coordinate, floor and map children."""
import argparse,itertools,json,random,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_foot_layer import verify
NATIVE=('tests/foot_layer_vectors.cpp','src/sim/FootCoordinates.cpp','src/assets/MapFloorHeight.cpp','src/assets/MapCoordinateCell.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),'tests/foot_layer/CMakeLists.txt','tests/original_foot_layer.py','tests/compare_foot_layer.py','tests/test_foot_layer_evidence.py','tools/verify_foot_layer.py','tools/verify_map_floor_height.py','tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
FLAGS=dict(actual_complete_Object_and_Foot_layer=True,actual_Foot_Drive_Object_coordinates=True,
 actual_nested_map_Cell_floor_and_lookup=True,ordered_live_queries_and_raw_bridge_byte=True,
 initial_records_globals_and_floor_template_supplied=True,diagnostic_mutations_not_gameplay=True,
 Unit_Scatter_joined=False,Advance6_executed=False,owned_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported layer evidence/input')
def defaults():
 return dict(index=-1,poolx=1,pooly=0,flevel=0,framp=0,fflags=0x100,
  position=[128,128,0],head=[384,128,0],cells=[[0,4,0,0],[1,0,0,0x100]],actions=[[1,0,0,104,104,-1]])
def command(**kw):
 c=defaults();c.update(kw);values=[c[k] for k in ('index','poolx','pooly','flevel','framp','fflags')]
 values.extend(c['position']);values.extend(c['head']);values.append(len(c['cells']));values.extend(itertools.chain.from_iterable(c['cells']))
 values.append(len(c['actions']));values.extend(itertools.chain.from_iterable(c['actions']))
 return 'L '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='L');v=list(map(int,t[1:]));require(len(v)>=14)
 c=dict(zip(('index','poolx','pooly','flevel','framp','fflags'),v));c.update(position=v[6:9],head=v[9:12]);n=v[12];require(0<=n<=16 and len(v)>=14+4*n)
 c['cells']=[v[i:i+4] for i in range(13,13+4*n,4)];at=13+4*n;count=v[at];at+=1
 require(1<=count<=128 and len(v)==at+6*count);c['actions']=[v[i:i+6] for i in range(at,len(v),6)]
 require(-128<=c['index']<=127 and all(-32768<=c[k]<=32767 for k in ('poolx','pooly')))
 require(-128<=c['flevel']<=127 and 0<=c['framp']<=20 and 0<=c['fflags']<=0xffffffff)
 require(all(-2147483648<=x<=2147483647 for x in c['position']+c['head']))
 require(len({row[0] for row in c['cells']})==n)
 for slot,level,ramp,flags in c['cells']:require(0<=slot<262144 and -128<=level<=127 and 0<=ramp<=20 and 0<=flags<=0xffffffff)
 for mode,flag,bridge,height,threshold,mutation in c['actions']:
  require(mode in (0,1) and 0<=bridge<=255 and -1<=mutation<=255 and all(-2147483648<=x<=2147483647 for x in (flag,height,threshold)))
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
 from original_foot_layer import FootLayerOracle
 o=FootLayerOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x5d52f0)
 def add(label,**kw):
  cmd=command(**kw);expected.append(o.run(parse(cmd)));commands.append(cmd);labels.append(label);groups[label]=groups.get(label,0)+1
 for index,mode in itertools.product(range(-128,128),(0,1)):
  add('all_signed_registry_indices_bypass_or_actual_coordinates',index=index,actions=[[mode,-2147483648,0,104,104,-1]])
 for bridge,difference in itertools.product(range(256),(-4,0,4)):
  add('all_raw_bridge_bytes_both_height_directions',cells=[[0,difference,0,0],[1,0,0,0x100]],actions=[[1,255,bridge,104,104,-1]])
 for saved,live,diff,flags in itertools.product((0,1,128,255),(0,1,128,255),(-4,0,4),(0,0x100)):
  add('diagnostic_saved_and_reread_bridge_at_actual_floor_return',cells=[[0,diff,0,0],[1,0,0,flags]],actions=[[1,7,saved,104,104,live]])
 for difference,threshold,bridge,flags in itertools.product((-5,-4,-3,0,3,4,5),(-105,-104,-1,0,103,104,105,0x40000000,0x55555555,2147483647,-2147483648),(0,173),(0,0x100)):
  add('strict_signed_wrapped_difference_and_triple_threshold',cells=[[0,difference,0,0],[1,0,0,flags]],actions=[[1,0,bridge,104,threshold,-1]])
 for ramp,x,y in itertools.product(range(21),(0,1,127,128,254,255),(0,127,255)):
  add('actual_all_ramps_low_bytes_two_independent_floor_queries',position=[x,y,77],head=[256+(255-x),255-y,-33],cells=[[0,4,(ramp+9)%21,0],[1,-1,ramp,0x100]],actions=[[1,0,0,104,104,-1],[0,255,128,208,104,-1]])
 for head,position in itertools.product(([0,0,0],[0,0,1],[384,128,0],[-1,-255,13]),([0,0,0],[128,128,0],[-256,256,123])):
  add('actual_head_sentinel_current_and_Object_coordinate_fallback',head=head,position=position)
 for point,position in itertools.product(([-1,-1,7],[-255,-255,-1],[-256,256,0],[-131072,256,9],[2147483647,-2147483648,3],[67108735,130816,0]),([128,128,0],[-1,-1,0],[-256,256,0])):
  add('full_signed_divide_combined_index_shared_fallback_forwarding',head=point,position=position,cells=[],flevel=-1,framp=7,actions=[[1,0,0,104,-1,-1],[0,99,255,208,104,-1]])
 for index,x,y in itertools.product((0,127),(-32768,-1,0,1,32767),(-32768,-1,0,32767)):
  add('actual_indexed_signed_word_center_vs_independent_actor',index=index,poolx=x,pooly=y,actions=[[0,1,0,104,104,-1],[1,0,255,104,104,-1]])
 for height,level in itertools.product((-2147483648,-104,-1,0,104,208,2147483647),(-128,-1,0,1,127)):
  add('independent_live_floor_and_layer_globals_wrapped_level_product',cells=[[0,level,3,0],[1,-1,7,0x100]],actions=[[1,0,0,height,104,-1],[0,1,255,104,height,-1]])
 for _ in range(128):
  add('retained_cold_then_warm_floor_and_fallback_sequences',position=[rng.randint(-512,512),rng.randint(-512,512),rng.randint(-99,99)],head=[rng.randint(-512,512),rng.randint(-512,512),rng.randint(-99,99)],
   flevel=rng.randint(-128,127),framp=rng.randrange(21),fflags=rng.getrandbits(32),actions=[[rng.randrange(2),rng.randint(-2147483648,2147483647),rng.randrange(256),rng.choice((0,104,208,-104)),rng.choice((104,-1,0x40000000)),rng.choice((-1,-1,0,255))] for _ in range(rng.randint(2,12))])
 add('long_retained_floor_state_and_query_order',actions=[[i%2,i,(i*71)%256,104 if i%3 else 208,104 if i%4 else -1,-1] for i in range(128)])
 require(all(o.counts[hex(k)]>0 for k in RANGES_EXECUTED))
 require(all(o.counts['ramp.'+str(r)]>0 for r in range(21)))
 require(all(o.counts['result.'+str(r)]>0 for r in range(256)))
 require(all(o.counts['return.'+hex(r)]>0 for r in (0x5d5391,0x5d53b2,0x5d53bd)))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,
  original_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),full_arena_and_caller_checks=o.audit_calls,selected_native_machine_write_order_claim=False)
RANGES_EXECUTED=(0x4cc4b0,0x5d52f0,0x4ca6f0,0x49fdb0,0x5d4e40,0x55a280,0x4706c0,0x77f110,0x548000)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Layer runner failed',p.returncode,p.stderr[:2000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Layer differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/foot-layer-v2');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'foot-layer sequences PASS')
if __name__=='__main__':main()
