#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete nearby search with original permission/admission/projection children."""
import argparse,copy,itertools,json,random,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from compare_nearby_cell_admission import command as cell_command,parse as parse_cell
from verify_nearby_location_map import verify
NATIVE=('tests/nearby_location_map_vectors.cpp','src/assets/MapCellChildren.cpp','src/render/Lighting.cpp','src/assets/RenderData.cpp','src/assets/PreparedData.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),'tests/nearby_location_map/CMakeLists.txt','tests/original_nearby_location_map.py',
 'tests/compare_nearby_location_map.py','tests/test_nearby_location_map_evidence.py','tools/verify_nearby_location_map.py',
 'tests/original_nearby_cell_admission.py','tests/compare_nearby_cell_admission.py','tools/verify_nearby_cell_admission.py','tools/verify_nearby_location.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
FLAGS=dict(actual_complete_nearby_parent_with_children=True,actual_permission_rectangle_Cell_projection=True,
 actual_shared_map_slots_fallback_and_sqrt=True,supplied_initial_records_types_speeds_shape_frame=True,
 zone_minus1_burrow0_profile=True,world_queries_not_supplied_decisions=True,
 Unit_Scatter_joined=False,Cell_Scatter_joined=False,Advance6_joined=False,Process_joined=False,
 production_owned_world_join=False,general_pathfinding_recovered=False,runtime_enabled=False)
SCALARS='dimension0 dimension1 frame speed zone movement alternate width height disallow match bridge skip origin_x origin_y shape_width shape_height'.split()
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported nearby map evidence/input')
def defaults():
 cells=[[512*y+x,x,y,0,0,0,0,0,0,-1] for x in range(47,57) for y in range(47,57)];cells[33][7]=1;cells.append([-1,-7,5,0,0,0,0,0,0,-1])
 return dict(mode=0,source=[50,50],close=[0,0],empty=[0,0],dimension0=2,dimension1=2,frame=0,speed=1,zone=-1,movement=0,alternate=0,width=1,height=1,disallow=0,match=1,bridge=1,skip=0,origin_x=0,origin_y=0,shape_width=100,shape_height=100,cells=cells,speeds=[0x3f800000]*108,overlays=[[0,0,0],[1,0,255],[1,1,0],[1,128,255]])
def command(**kw):
 c=defaults();c.update(kw)
 return 'M '+' '.join(map(str,[c['mode'],*c['source'],*c['close'],*c['empty'],*[c[k] for k in SCALARS],len(c['cells']),*itertools.chain.from_iterable(c['cells']),len(c['speeds']),*c['speeds'],len(c['overlays']),*itertools.chain.from_iterable(c['overlays'])]))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='M')
 try:v=list(map(int,t[1:]))
 except ValueError:raise ValueError('Malformed nearby map integer') from None
 require(len(v)>=7+len(SCALARS)+1);c=dict(mode=v[0],source=v[1:3],close=v[3:5],empty=v[5:7]);c.update(zip(SCALARS,v[7:]));at=7+len(SCALARS);count=v[at];at+=1
 require(1<=count<=128 and len(v)>at+10*count);c['cells']=[v[i:i+10] for i in range(at,at+10*count,10)];at+=10*count
 n=v[at];at+=1;require(1<=n<=4096 and len(v)>at+n);c['speeds']=v[at:at+n];at+=n
 n=v[at];at+=1;require(n==4 and len(v)==at+3*n);c['overlays']=[v[i:i+3] for i in range(at,len(v),3)]
 require(c['zone'] in (-1,65535) and 0<=c['mode']<4 and all(-32768<=n<=32767 for k in ('source','close','empty') for n in c[k]))
 require(all(-2147483648<=c[k]<=2147483647 for k in SCALARS if k!='alternate') and 0<=c['alternate']<=0xffffffff)
 require(all(0<=c[k]<=255 for k in ('disallow','match','bridge','skip')) and c['width']<=4 and c['height']<=4)
 parse_cell(cell_command(mode=c['mode'],x=c['source'][0],y=c['source'][1],width=c['width'],height=c['height'],speed=c['speed'],cells=c['cells'],speeds=c['speeds'],overlays=c['overlays']))
 return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},render_data_sha256=hash_file(a.render_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and all(isinstance(n,str) for n in row) and row.count('state')==1)
def generate(a):
 from original_nearby_location_map import NearbyLocationMapOracle
 o=NearbyLocationMapOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x550cf0)
 def add(label,**kw):
  cmd=command(**kw)
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed nearby map case',len(commands),label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
 for mode,frame in itertools.product(range(4),range(16)):add('actual_neighbor_search_order',mode=mode,frame=frame)
 for mode,close in itertools.product(range(4),([55,50],[50,55],[45,50],[50,45],[51,51],[49,49])):add('actual_projection_and_distance',mode=mode,close=close)
 for alternate,zone,match,skip in itertools.product((0,1,256,0x800000ff),(-1,65535),(0,1),(0,128)):
  add('raw_parent_arguments',alternate=alternate,zone=zone,match=match,skip=skip)
 for overlay,movement,disallow in itertools.product((-1,0,1,2,3),(0,1,2,4,8),(0,255)):
  cells=defaults()['cells']
  for row in cells:row[9]=overlay
  add('actual_wall_or_disallowed_overlay',cells=cells,movement=movement,disallow=disallow)
 for mode,bits,flags in itertools.product(range(4),(0,0x80000000,0xbf800000,0x7f800000,0xff800000,0x7fc00001),(0,0x100)):
  cells=defaults()['cells'];speeds=defaults()['speeds'];speeds[1]=bits
  for row in cells:row[5]=flags
  add('actual_speed_and_elevated_occupation',mode=mode,speeds=speeds,cells=cells,alternate=1)
 for occupation,elevated in itertools.product((0,1,0x20,0x80,0x100),(0,1,0x100)):
  cells=defaults()['cells']
  for row in cells:row[7]=occupation;row[8]=elevated;row[5]=0x100
  add('actual_primary_elevated_low_byte',cells=cells,alternate=1)
 for level,flags,slope in itertools.product((-2,0,2,4,12),(0,0x100,0x1000),(0,1)):
  cells=defaults()['cells'];cells[33][3]=level;cells[33][5]=flags;cells[33][4]=slope
  add('stored_source_level_bridge_slope',cells=cells)
 for width,height in ((0,1),(1,0),(-1,2),(2,-1),(2,3),(3,2)):
  add('actual_rectangle_dimensions_and_iteration',width=width,height=height)
 for dim0,dim1 in ((0,0),(-1,0),(1,0),(2147483647,1),(-2147483648,-2147483648)):
  add('empty_wrapped_limit',dimension0=dim0,dimension1=dim1)
 cells=defaults()['cells']
 for row in cells:row[7]=1
 add('all32_radii_actual_refusals',cells=cells,dimension1=30)
 cells=[[512*y+x,x,y,0,0,0,0,0,0,-1] for x in range(49,54) for y in range(49,54)]
 cells += [[512*y+x,x,y,12,0,0,0,1,0,-1] for x in range(55,60) for y in range(55,60)]
 cells.append([-1,-7,5,0,0,0,0,1,0,-1])
 for frame in (0,1,23,2147483647):add('actual_nonmatching_projection_capacity24',source=[51,51],cells=cells,dimension1=4,match=0,frame=frame,origin_x=-10)
 for source in ((32767,32767),(-32768,-32768),(-1,1),(512,-1)):
  for close in ((0,0),(-32768,-32768)):
   add('actual_word_fallback_wrapped_squared_distance',source=list(source),close=list(close),empty=[7,9],shape_width=65536,shape_height=65536,cells=[[-1,-7,5,0,0,0,0,0,0,-1]],match=0)
 for i in range(40):
  cells=defaults()['cells']
  for row in cells:row[3]=rng.randint(-2,4);row[5]=rng.choice((0,0x100,0x1000));row[7]=rng.choice((0,0,1,0x100));row[8]=rng.choice((0,1));row[9]=rng.randrange(-1,4)
  add('seeded_actual_shared_world',cells=cells,mode=i%4,frame=rng.randrange(32768),alternate=rng.choice((0,1,256)),match=rng.randrange(2),bridge=rng.randrange(2),close=rng.choice(([0,0],[55,51])))
 require(o.counts['0x5502e0']==len(commands) and o.counts['Cell_calls']>0 and o.counts['projection_calls']>0)
 require(all(o.counts[k]>0 for k in ('permission.0','permission.1','rectangle.0','rectangle.1','preferred','other','capacity24','radius.31','sqrt.negative','sqrt.positive','Cell_return.0','Cell_return.1')))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,original_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),full_arena_and_caller_guards=True,native_machine_store_order_claim=False)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 require(p.returncode==0);rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Nearby map differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True);p.add_argument('--output',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();a.render_data=ROOT/'private/derived/ra2-1006/render-data.bin'
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  require(a.output is not None and a.report is None);folder=private_path(a.output,a.exe);require(not(folder/'expected.json').exists() and not(folder/'report.json').exists());now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now;require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'nearby map sequences PASS')
if __name__=='__main__':main()
