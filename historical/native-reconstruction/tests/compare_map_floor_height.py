#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete finite floor/map/relative/center height queries and lazy state."""
import argparse,json,math,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_floor_height import verify
SOURCES=('src/assets/MapFloorHeight.hpp','src/assets/MapFloorHeight.cpp','src/assets/MapCellInputs.hpp',
 'src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/OriginalMath.hpp','tests/map_floor_height_vectors.cpp',
 'tests/compare_map_floor_height.py','tests/original_map_floor_height.py','tools/verify_map_floor_height.py',
 'tools/verify_terrain_visibility.py','tests/compare_terrain_visibility.py','tests/compare_original.py',
 'tests/presentation_evidence.py','tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py')
def bits(n):return struct.unpack('<Q',struct.pack('<d',n))[0]
def number(n):return struct.unpack('<d',struct.pack('<Q',n))[0]
def command(mode,flags,height,scale,planes,rows):return ' '.join(map(str,[mode,flags,height,scale,*planes,len(rows),*[n for r in rows for n in r]]))
def parse(cmd):
 p=cmd.split();mode=p[0];assert mode in ('H','C','M','R');v=list(map(int,p[1:]));flags,h,scale=v[:3];planes=v[3:103];count=v[103]
 assert 0<=flags<=255 and len(planes)==100 and 1<=count<=64 and len(v)==104+count*12
 assert all(0<=n<1<<64 and math.isfinite(number(n)) for n in [h,scale,*planes])
 rows=[v[i:i+12] for i in range(104,len(v),12)]
 for row in rows:
  current,level,ramp,x,y,z,bridge,bheight,slot,present,flevel,framp=row
  assert all(-2147483648<=n<=2147483647 for n in (current,x,y,z,bheight))
  assert -128<=level<=127 and 0<=ramp<=20 and -128<=flevel<=127 and 0<=framp<=20
  assert 0<=bridge<=255 and 0<=slot<262144 and present in (0,1)
  if mode=='C':assert -32768<=x<=32767 and -32768<=y<=32767
 return mode,flags,h,scale,planes,rows
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Floor height engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Floor height source/inspection identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Floor height counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed floor height command') from None
def generate(a):
 from original_map_floor_height import MapFloorHeightOracle
 o=MapFloorHeightOracle(a.exe);pe=pefile.PE(str(a.exe));template=list(struct.unpack('<100Q',pe.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];groups={};steps=0;rng=random.Random(0x48454947)
 def add(label,mode,rows,flags=0xa0,h=17.25,scale=-0.125,planes=None):
  nonlocal steps
  cmd=command(mode,flags,bits(h),bits(scale),template if planes is None else planes,rows);args=parse(cmd)
  result=o.run(*args);commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1;steps+=len(rows)
 def row(current=104,level=0,ramp=0,x=0,y=0,z=0,bridge=0,bheight=416,slot=0,present=1,flevel=3,framp=0):return [current,level,ramp,x,y,z,bridge,bheight,slot,present,flevel,framp]
 edges=[-2147483648,-257,-256,-255,-129,-128,-1,0,1,127,128,129,254,255,2147483647]
 for ramp in range(21):
  for level in (-128,-127,-2,-1,0,1,31,127):
   for i,x in enumerate(edges):
    y=edges[(i*7+3)%len(edges)]
    add('all_ramps_signed_level_byte_local_low_bytes_and_warm_live_height_change','H',
     [row(104,level,ramp,x,y),row(208,level,ramp,y,x),row(-104,level,ramp,x,y)])
 for level in range(-128,128):
  add('all_signed_levels_and_low_product_wrap','H',[row(n,level,0) for n in (-2147483648,-2147483647,-1,0,1,2147483647)])
 for case in range(256):
  planes=[bits(rng.choice([-2,-1,-0.0,0.0,0.125,1,2,16,104])) for _ in range(100)]
  add('independent_lazy_bits_upper_flags_retained_template_and_cached_planes','H',
   [row(rng.choice([-2147483648,-104,0,1,104,2147483647]),rng.randrange(-128,128),rng.randrange(21),rng.randrange(-1024,1024),rng.randrange(-1024,1024)) for _ in range(3)],
   flags=(case%8)|(case&0xf8),h=rng.choice([-0.0,0,1.5,-104,104,208]),scale=rng.choice([-0.0,0,1/256,-104/256,104/256]),planes=planes)
 for ramp in range(21):
  for level in (-128,-1,0,1,4,31,127):
   for x,y in ((0,0),(51,72),(-32768,32767),(32767,-32768),(-1,-1)):
    add('actual_Cell_center_signed_word_coordinates_with_nested_floor','C',[row(104,level,ramp,x,y),row(208,level,ramp,y,x)])
 points=[(-2147483648,-2147483648),(2147483647,2147483647),(-1,-1),(-255,0),(-256,256),(-257,256),(0,0),(255,1),(256,256),(16777216,0),(131072,2147483647)]
 def divided(n):return n//256 if n>=0 else -((-n)//256)
 for mode in ('M','R'):
  for case in range(256):
   rows=[]
   for i in range(4):
    x,y=points[(case+i)%len(points)] if case<128 else (rng.randrange(-100000,100000),rng.randrange(-100000,100000))
    index=(divided(y)*512+divided(x))&0xffffffff
    slot=index if index<262144 else rng.randrange(262144)
    rows.append(row(rng.choice([104,208,-104]),rng.randrange(-128,128),rng.randrange(21),x,y,
     rng.choice([-2147483648,-1,0,1,2147483647]),rng.choice([0,1,2,128,255]),rng.choice([-2147483648,-416,0,416,2147483647]),
     slot,int((case+i)%3!=0),rng.randrange(-128,128),rng.randrange(21)))
   add('actual_map_and_relative_wrapper_alias_fallback_byte_gate_and_wrapped_subtractions',mode,rows)
 return commands,expected,labels,{'groups':groups,'query_steps':steps,'audited_roots':o.audit_calls,'actual_entries':o.entries,
  'audited_guest_writes':o.writes,'lazy_flag_stores':o.flag_writes,'fallback_position_stores':o.fallback_writes,
  'initial_global_template_map_actor_and_bridge_storage_supplied':True,'finite_ramps_0_through_20_only':True,
  'initialization_store_order_not_compared':True,'runtime_and_original_startup_unverified':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/map-floor-height-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/floor-height-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh height destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native floor height: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Height result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}; {commands[i]}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Height run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} floor/map/relative/center height sequences: PASS ({result["evidence_mode"]}, {metadata["query_steps"]:,} queries, {elapsed:.3f}s native)')
if __name__=='__main__':main()
