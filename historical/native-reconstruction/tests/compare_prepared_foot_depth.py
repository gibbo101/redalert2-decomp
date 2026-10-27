#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare ordinary prepared Foot depth after actual shared map/floor preparation."""
import argparse,json,math,random,struct,subprocess,time
from pathlib import Path
import compare_unit_base_depth as base
import compare_resident_map_floor as parent
from compare_map_floor_height import bits,number
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_prepared_foot_depth import verify
SOURCES=tuple(dict.fromkeys((*base.SOURCES,
 'src/render/UnitBaseDepth.hpp','src/render/UnitBaseDepth.cpp',
 'src/render/FootDepth.hpp','src/render/FootDepth.cpp',
 'src/render/PreparedFootDepth.hpp','src/render/PreparedFootDepth.cpp',
 'tests/compare_prepared_foot_depth.py','tests/original_prepared_foot_depth.py','tools/verify_prepared_foot_depth.py')))
def command(floor,queries):return 'E '+parent.command(*floor[:5],floor[5:])[2:]+' | '+str(len(queries))+' '+' '.join(str(n) for r in queries for n in r)
def parse(cmd):
 head,tail=cmd.split(' | ');assert head.startswith('E ');v=list(map(int,tail.split()));count=v[0]
 assert 1<=count<=4096 and len(v)==1+23*count
 queries=[v[i:i+23] for i in range(1,len(v),23)]
 floor,_=base.parse('D '+head[2:]+' | '+str(count)+' '+' '.join(str(n) for r in queries for n in r[:15]))
 for row in queries:
  assert row[13]==0 and row[15] in (0,1) and -2147483648<=row[16]<=2147483647
  assert all(-32768<=n<=32767 for n in row[17:19]) and all(-2147483648<=n<=2147483647 for n in row[19:])
 return floor,queries
def identities(a):
 e=json.loads(a.floor_fixture.read_text());validate_receipt(e,json.loads((a.floor_fixture.parent/'report.json').read_text()),hash_file(a.floor_fixture))
 return {**parent.identities(a),'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'floor_input_snapshot_sha256':hash_file(a.floor_fixture)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Prepared Foot depth engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Prepared Foot depth source/inspection/input identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Prepared Foot depth counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed Prepared Foot depth command') from None

def generate(a):
 from original_prepared_foot_depth import PreparedFootDepthOracle
 o=PreparedFootDepthOracle(a.exe);source=json.loads(a.floor_fixture.read_text());rng=random.Random(0x464f4f54)
 commands=[];expected=[];labels=[];groups={};steps=0
 def query(x=6*256+128,y=6*256+128,z=416,heading=0,**kw):
  return [x,y,z,heading,kw.get('start',heading),kw.get('timer',0),kw.get('duration',0),kw.get('rate',0),kw.get('tick',0),bits(kw.get('scale',0.125)),kw.get('current',-1),kw.get('neighbor',-1),kw.get('rock',3),0,kw.get('default',0),kw.get('drive',1),kw.get('tilebase',0),-32768,-32768,*kw.get('factors',(8,13,10,0))]
 def add(label,floor,queries):
  nonlocal steps
  cmd=command(floor,queries);f,q=parse(cmd);value=o.run_foot(f,q)
  commands.append(cmd);expected.append(value);labels.append(label);groups[label]=groups.get(label,0)+1;steps+=len(q)
 # The owned maps supply inputs only. Query the retained cliff and crossing
 # positions; no missing-image initialization is silently substituted.
 for index,cmd in enumerate(source['commands'][32:35]):
  floor=parent.parse(cmd);rows={(r[0],r[1]):r for r in floor[8]};queries=[]
  for x,y in [(51,72),*[(x,101) for x in range(86,94)]]:
   for h in range(0,65536,2048):
    for drive in (0,1):queries.append(query(x*256+128,y*256+128,rows[(x,y)][4]*104,h,drive=drive))
  add('owned_prepared_cliff_and_crossing_'+str(index),floor,queries)
 template=parent.parse(source['commands'][0]);common=list(template[5]);common[:5]=[6,6,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 # Independent center/neighbor ramps, first overlay priority, flags, real TMP
 # crop height/extra height and sentinel/default tile. Missing images are refused.
 for case in range(64):
  types=[]
  for i in range(24):
   ramp=(i if case%4==0 else 0) if i<=20 else 0
   types.append([1,1,1,60,[30,36,37,60,-30][(i+case)%5],1,0,ramp,15 if i%3==0 else 0,-30 if i%3==0 else 0,int(i%3==0)])
  cells=[]
  for y in range(13):
   for x in range(13):
    if x+y>6 and abs(x-y)<6 and x+y<=18:
     tile=(x*7+y*11+case)%24 if case%4<2 else 0
     flags=(0x10000 if case%8==3 else (0x100,0x400,0x800,0x900,0xc00,0)[(x+y+case)%6])
     overlay=-1
     if case%4==0 and (x,y) in ((6,7),(7,6),(7,7)):overlay=((case//4)+x+y)%3-1
     cells.append([x,y,tile,0,(case+x*3+y*5)%13,flags,-1,0,0,0,0,0,17,91,overlay,41,0])
  overlays=[[0,0,0,0,1,0,1],[0,0,0,0,1,0,0]]
  floor=(*template[:5],common,[6,0,0,6,6],types,cells,overlays,[],template[11],[])
  queries=[]
  for heading in range(0,65536,1024):
   queries.append(query(z=rng.choice([-2147483648,-729,-1,0,416,727,728,729,2147483647]),heading=heading,
    scale=rng.choice([0.125,0.11048543456039805,1.0]),current=-7,neighbor=9,rock=23,default=case%24,drive=(heading//1024+case)%2,tilebase=case%24,factors=tuple(rng.choice([-2147483648,-1,0,8,10,13,2147483647]) for _ in range(4))))
  # Facing interpolation, signed timer edges and word-coordinate wrapping.
  for k in range(16):
   queries.append(query(x=rng.choice([1664,-1,16777216]),y=rng.choice([1664,-257,2147483647]),heading=rng.randrange(65536),
    start=rng.randrange(65536),timer=rng.choice([-1,0,2147483647]),duration=rng.choice([0,1,8,32]),rate=rng.choice([0,256,2048,32768,65535]),tick=rng.choice([-2147483648,0,1,31,2147483647]),current=-7,neighbor=9,rock=23,drive=k%2,factors=(-7,9,23,41)))
  add('ordinary_shared_Cell_TMP_ramps_flags_overlay_priority_dimensions_and_Facing',floor,queries)
 return commands,expected,labels,{'groups':groups,'query_steps':steps,'audited_roots':o.audit_calls,'actual_entries':o.entries,
  'actual_Foot_queries':o.foot_calls,'actual_gradient_queries':o.gradient_calls,'actual_cell_predicates':o.cell_predicates,'actual_dimensions_calls':o.dimensions_calls,'parent_floor_calls':o.floor_calls,
  'initial_actor_type_global_height_scale_default_tile_supplied':True,'empty_tube_registry_and_nonbridge':True,'missing_image_dimensions_refused':True,
  'historical_fixtures_are_inputs_only':True,'ordinary_kind1_nonharvester_special_zero':True,
  'null_map_pointers_runtime_startup_and_full_frame_excluded':True}

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/resident-map-finalization-vectors')
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--terrain-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-map-v6/expected.json');p.add_argument('--overlay-fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json')
 p.add_argument('--parent-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-finalization-v1/expected.json');p.add_argument('--floor-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-floor-v1/expected.json');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/prepared-foot-depth-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current);report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Prepared Foot depth destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native Prepared Foot depth: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Prepared Foot depth result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Prepared Foot depth run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} prepared-map / Prepared Foot depth results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
