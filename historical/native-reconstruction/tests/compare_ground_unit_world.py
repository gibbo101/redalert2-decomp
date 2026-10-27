#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare shared prepared Cells through complete ground Unit and shadow drawing."""
import argparse,json,math,struct,subprocess,time
from pathlib import Path
import compare_unit_voxel_world as world
import compare_prepared_foot_depth as prepared
import compare_resident_map_floor as floor
from compare_map_floor_height import bits,number
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_unit_world import verify
import compare_unit_voxel_shadow_world as shadow
from compare_drive_shadow_pose import SOURCES as DRIVE_SOURCES
SOURCES=tuple(dict.fromkeys((*DRIVE_SOURCES,
 'src/render/GroundUnitVoxelWorld.hpp','src/render/GroundUnitVoxelWorld.cpp',
 'src/render/SharedGroundUnitVoxelWorld.hpp','src/render/SharedUnitVoxelStaging.hpp',
 'tests/ground_unit_world_vectors.cpp','tests/compare_ground_unit_world.py',
 'tests/original_ground_unit_world.py','tools/verify_ground_unit_world.py',
 'tests/prepared_map_fixture.hpp','tests/original_prepared_unit_world.py')))

def parse(command):
 op,tail=command.split(' ',1)
 if op=='P':
  f=floor.parse(tail);assert f[4]==104;return op,f
 v=list(map(int,tail.split()))
 if op=='O':assert len(v)==2 and v[0] in (0,1) and 0<=v[1]<=100000
 elif op=='W':
  assert len(v)==26 and all(-2147483648<=n<=2147483647 for n in v[:3])
  assert 0<=v[0]<512*256 and 0<=v[1]<512*256 and 0<=v[3]<1<<64 and math.isfinite(number(v[3])) and 0<number(v[3])<=1 and 0<=v[4]<=100000 and v[5] in (0,1)
  assert v[6] in (0,1) and v[7] in (0,1)
  body,turret,pitch,gate,disabled,valid,barrel,frame,brightness,predicate,camera,empty,x,y,bx,by,bw,bh=v[8:]
  assert all(0<=n<=65535 for n in (body,turret,pitch)) and 0<=gate<=255 and disabled in (0,1)
  assert 1<=valid<=7 and valid&1 and barrel in (0,1) and predicate in (0,1) and camera in (0,1) and empty in range(3)
  assert -2147483648<=frame<=2147483647 and 0<=brightness<=65535 and 0<=bx<=160 and 0<=by<=144 and 0<=bw<=160-bx and 0<=bh<=144-by
 else:raise ValueError('Unknown ground Unit/world command')
 return op,v
def identities(a):
 e=json.loads(a.depth_fixture.read_text());validate_receipt(e,json.loads((a.depth_fixture.parent/'report.json').read_text()),hash_file(a.depth_fixture))
 return {'shadow':shadow.identities(a),'world':world.identities(a),'prepared':prepared.identities(a),'inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES},'prepared_numeric_inputs':{k:hash_file(getattr(a,k+'_data')) for k in ('geometry','direction')},'depth_input_snapshot_sha256':hash_file(a.depth_fixture)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Ground Unit/world engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Ground Unit/world source/inspection/input identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Ground Unit/world counts differ')
 ready=reset=False
 for cmd in e['commands']:
  try:op,v=parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed ground Unit/world command') from None
  if op=='P':ready=True
  if op=='O':reset=True
  if op=='W' and not(ready and reset):raise ValueError('Ground Unit/world lacks map or cache reset')
def generate(a,ramps=range(21),include_owned=True):
 from original_ground_unit_world import GroundUnitWorldOracle
 o=GroundUnitWorldOracle(a.exe,a.assets,a.palette.read_bytes())
 source=json.loads(a.depth_fixture.read_text());commands=[];expected=[];labels=[];groups={};draws=0
 def save(label,cmd,result):
  parse(cmd);commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);groups[label]=groups.get(label,0)+1
 def reset(seed):o.begin_unit(seed);save('four_indexes_pool_staging_reset',f'O 0 {seed}',['reset'])
 def prepare_map(f,label):
  save(label,'P '+floor.command(*f[:5],f[5:]),o.prepare_map(f));print(label,flush=True)
 def draw(label,location,heading,n,contact=0,warm=False,gate=1,disabled=0,no_shadow=0,disable_shadow=0,predicate=0):
  nonlocal draws
  unit=[heading,((heading//2048*7+3)%32)*2048,16384 if warm else 14336,gate,disabled,7,1,0,
    1712 if warm else 1312,predicate,n%2,0,(80,-5,150)[n%3],(72,4,140)[n%3],0,0,160,144]
  v=[*location,bits(0.125),n,contact,no_shadow,disable_shadow,*unit]
  result=o.draw_ground(location,0.125,[n,0,contact,no_shadow,disable_shadow,*unit]);draws+=1
  save(label,'W '+' '.join(map(str,v)),result);print(f'draw {draws}: {label}',flush=True)
 template,_=prepared.parse(source['commands'][3]);common=list(template[5]);common[:5]=[6,6,0,-1,0]
 common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 for ramp in ramps:
  types=[[1,1,1,60,30,1,0,0,0,0,0],[1,1,1,60,30,1,0,ramp,0,0,0]]
  cells=[]
  for y in range(13):
   for x in range(13):
    if x+y>6 and abs(x-y)<6 and x+y<=18:
     center=(x,y)==(6,6)
     cells.append([x,y,int(center),0,0 if center else (x+y)%4,0,-1,0,0,0,0,0,17,91,-1,41,0])
  f=(*template[:5],common,[6,0,0,6,6],types,cells,[],[],template[11],[])
  prepare_map(f,'shared_prepared_current_ramp_'+str(ramp));reset(3+ramp)
  heading=(ramp*3%32)*2048
  draw('all_ramps_actual_floor_Drive_Unit_and_complete_shadow_pixels',[1664,1664,0],heading,ramp,predicate=ramp%2)
  if ramp%2==0:draw('warm_shadow_lit_reuse_different_view_pitch_brightness',[1664,1664,-1],heading,24+ramp,contact=1,warm=True,predicate=ramp%2)
  if ramp%4==0:draw('uncacheable_raw_shadow_and_lit_bypass_clipping',[1536,1536,0],heading,48+ramp,gate=0,disabled=1,disable_shadow=1,predicate=1)
  if ramp in (0,20):draw('NoShadow_preserves_lit_draw_and_saved_cleanup',[1664,1664,0],heading,72+ramp,no_shadow=1)
 # One actual owned map is independently prepared here; prior receipts supply
 # input records only. Supplied actor absolute Z is not recovered placement.
 if include_owned:
  f,_=prepared.parse(source['commands'][0]);prepare_map(f,'owned_full_shared_preparation');reset(91)
  for n,(x,y,z) in enumerate(((51,72,416),(86,101,0),(91,101,0))):
   draw('owned_cliff_and_crossing_complete_ground_pipeline',[x*256+128,y*256+128,z],n*16384,n,contact=n%2)
 if include_owned and (not o.raw_spans or not o.shadow_spans or not all(o.gradient_calls.values())):raise AssertionError('Missing joined shadow/final coverage')
 return commands,expected,labels,{'groups':groups,'draws':draws,'audited_world_roots':o.audit_calls,'audited_map_roots':o.prepared.audit_calls,
  'actual_map_entries':o.prepared.entries,'actual_ground_queries':o.ground_calls,'actual_world_calls':o.world_calls,
  'actual_shadow_calls':o.shadow_calls,'actual_foot_shadow_entries':o.foot_shadow_entries,
  'actual_raw_shadow_spans':o.raw_spans,'actual_rle_shadow_spans':o.shadow_spans,'actual_gradient_surface_calls':o.gradient_calls,
  'numeric_global_stores':o.numeric.global_stores,'numeric_matrix_stores':o.numeric.matrix_stores,
  'same_guest_map_numeric_initialization_Unit_shadow_no_record_transfer':True,
  'actual_floor_relative_height_and_current_ramp_pose':True,'lit_locomotor_records_flat_settled_supplied':True,
  'initial_actor_absolute_Z_type_camera_planes_house_supplied':True,'relative_height_nonpositive_no_bridge_no_add14':True,
  'historical_fixtures_are_inputs_only':True,'placement_update_runtime_full_frame_excluded':True}

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-unit-world-vectors')
 p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin');p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets');p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal');p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
 p.add_argument('--terrain-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-map-v6/expected.json');p.add_argument('--overlay-fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json')
 p.add_argument('--parent-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-finalization-v1/expected.json');p.add_argument('--floor-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-floor-v1/expected.json');p.add_argument('--depth-fixture',type=Path,default=ROOT/'private/map-depth-1006/prepared-foot-depth-v1/expected.json')
 p.add_argument('--geometry-data',type=Path,default=ROOT/'private/derived/ra2-1006/ramp-geometry-data.bin');p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-unit-world-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current);report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh ground Unit/world destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette),str(a.geometry_data),str(a.direction_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native ground Unit/world: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Ground Unit/world counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'{i} {labels[i]}: {[(n,xx,yy) for n,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:12]}, lengths {len(x)}/{len(y)}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Ground Unit/world run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} prepared-map / complete ground Unit/shadow/world results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
