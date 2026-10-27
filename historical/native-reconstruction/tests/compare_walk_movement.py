#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare committed infantry Walk; reuse original answers, run current C++."""
import argparse,itertools,json,random,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_walk_movement import verify
NATIVE=('tests/walk_movement_vectors.cpp','src/sim/WalkMovement.cpp','src/sim/Targeting.cpp',
 'src/sim/GroundMovementPlacement.cpp','src/sim/ActorGroundState.cpp','src/render/Lighting.cpp',
 'src/render/VoxelRaster.cpp','src/assets/MovementData.cpp','src/assets/PreparedData.cpp',
 'src/assets/RenderData.cpp','src/assets/RasterData.cpp','src/assets/Archive.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
ORIGINAL=('tests/original_walk_movement.py','tools/verify_walk_movement.py','tests/compare_walk_movement.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py',
 'tests/compare_original.py','tools/verify_terrain_visibility.py')
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_walk_movement.py','CMakeLists.txt')
FLAGS=dict(complete_committed_Walk_Process=True,selected_ordered_stores_and_services=True,
 initial_records_head_speed_Mark_floor_map_dirty_supplied=True,arrival_and_subcell_selection=False,
 production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Walk evidence/input differs')
def command(position=(128,128,29),head=(896,128,29),speed=12,immobilized=0,marked=0,bridge=0,
 a1=173,a2=197,moving=1,floor=0,bridgeHeight=104,oldLevel=0,newLevel=0,oldFlags=0,newFlags=0,
 policy=1,desired=0,start=0,timer=-1,duration=0,tick=61):
 return 'W '+' '.join(map(str,(*position,*head,speed,immobilized,marked,bridge,a1,a2,moving,
  floor,bridgeHeight,oldLevel,newLevel,oldFlags,newFlags,policy,desired,start,timer,duration,tick)))
def parse(cmd):
 t=cmd.split();require(len(t)==26 and t[0]=='W');v=list(map(int,t[1:]));require(all(-2147483648<=n<=2147483647 for n in v))
 require(all(0<=v[i]<=255 for i in (8,9,10,11,12)) and all(-128<=v[i]<=127 for i in (15,16)))
 require(0<=v[19]<=7 and all(0<=v[i]<=65535 for i in (20,21)) and v[3:6]!=[0,0,0])
 require(all(abs(v[i]-v[i+3])<=1<<20 for i in (0,1)))
 require(sum((v[i]-v[i+3])**2 for i in (0,1))>=17**2)
 return v
def scenarios():
 for dx,dy in ((0,-768),(768,-768),(768,0),(768,768),(0,768),(-768,768),(-768,0),(-768,-768),(17,0),(0,17),(11,13),(31,617),(-617,31)):
  for speed in (-301,-17,0,1,12,255,301):
   for position in ((128,128,29),(-255,-1,-77),(255,256,104)):
    yield 'headings_signed_coordinates_and_crossings',command(position=position,head=(position[0]+dx,position[1]+dy,29),speed=speed)
 for marked,bridge,policy in itertools.product((0,1,128,255),(0,1,128,255),range(8)):
  yield 'raw_bytes_nested_Mark_and_late_position',command(position=(250,250,79),head=(1024,400,0),speed=29,marked=marked,bridge=bridge,policy=policy,floor=-79)
 for old,new,oldFlags,newFlags in itertools.product((-128,-4,0,4,127),(-128,-4,0,4,127),(0,256),(0,256)):
  yield 'signed_bridge_level_and_independent_flags',command(position=(255,128,29),speed=37,oldLevel=old,newLevel=new,oldFlags=oldFlags,newFlags=newFlags,bridge=173)
 for frozen,moving in itertools.product((-2147483648,-1,0,1,2147483647),(0,1,128,255)):
  yield 'signed_immobilization_raw_result',command(immobilized=frozen,moving=moving,marked=255,bridge=128)
 for desired,start,timer,duration,tick in ((0,0,-1,0,0),(0,32768,0,128,1),(32768,0,0,128,2),(65535,1,-1,17,3),
  (16383,16383,55,1,61),(49151,65535,0,255,13),(0,1,2147483647,17,-2147483648)):
  yield 'actual_Facing_current_timer_and_host_rounding',command(desired=desired,start=start,timer=timer,duration=duration,tick=tick)
 rng=random.Random(0x71dff0)
 for i in range(96):
  p=(rng.randrange(-200000,200000),rng.randrange(-200000,200000),rng.randrange(-1000,1000))
  h=(p[0]+rng.randrange(-32768,32768),p[1]+rng.randrange(-32768,32768),rng.randrange(-1000,1000))
  yield 'deterministic_quantization_and_FP_modes',command(position=p,head=h,speed=rng.randrange(-512,512),tick=i,
   marked=rng.randrange(256),bridge=rng.randrange(256),policy=i%8,desired=rng.randrange(65536),start=rng.randrange(65536),timer=i-17,duration=i%11)
def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},
  data={k:hash_file(getattr(a,k)) for k in ('render_data','raster_data','direction_data')}),
  native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_complete_roots']==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('R')==1)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','raster-data','direction-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_walk_movement import WalkMovementOracle
  o=WalkMovementOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run(parse(cmd))
   except BaseException:print('Failed Walk scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_complete_roots=o.audit_calls,counts=dict(o.counts))
  require(all(o.counts.get(hex(k),0)>0 for k in (0x71dff0,0x71e220,0x71dea0,0x71e170,0x4b8b10,0x4ca160,0x5d4860,0x453eb0)))
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data),str(a.raster_data),str(a.direction_data)],
  input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True)
 require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(len(commands),'complete committed Walk roots PASS')
if __name__=='__main__':main()
