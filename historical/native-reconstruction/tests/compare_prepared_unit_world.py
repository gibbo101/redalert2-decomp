#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare finalized shared map Cells/TMP through complete lit Unit/world drawing."""
import argparse,json,math,struct,subprocess,time
from pathlib import Path
import compare_unit_voxel_world as world
import compare_prepared_foot_depth as prepared
import compare_resident_map_floor as floor
from compare_map_floor_height import bits,number
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_prepared_unit_world import verify
SOURCES=('src/render/PreparedUnitDepth.hpp','src/render/PreparedUnitDepth.cpp',
 'src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp',
 'tests/prepared_map_fixture.hpp','tests/prepared_unit_world_vectors.cpp',
 'tests/compare_prepared_unit_world.py','tests/original_prepared_unit_world.py','tools/verify_prepared_unit_world.py')
def parse(command):
 op,tail=command.split(' ',1)
 if op=='P':return op,floor.parse(tail)
 v=list(map(int,tail.split()))
 if op=='O':assert len(v)==2 and v[0] in (0,1) and 0<=v[1]<=100000
 elif op=='W':
  assert len(v)==24 and all(-2147483648<=n<=2147483647 for n in v[:3])
  assert 0<=v[0]<512*256 and 0<=v[1]<512*256 and 0<=v[3]<1<<64 and math.isfinite(number(v[3])) and 0<number(v[3])<=1 and 0<=v[4]<=100000 and v[5] in (0,1)
  body,turret,pitch,gate,disabled,valid,barrel,frame,brightness,predicate,camera,empty,x,y,bx,by,bw,bh=v[6:]
  assert all(0<=n<=65535 for n in (body,turret,pitch)) and 0<=gate<=255 and disabled in (0,1)
  assert 0<=valid<=7 and barrel in (0,1) and predicate in (0,1) and camera in (0,1) and empty in range(3)
  assert -2147483648<=frame<=2147483647 and 0<=brightness<=65535 and 0<=bx<=160 and 0<=by<=144 and 0<=bw<=160-bx and 0<=bh<=144-by
 else:raise ValueError('Unknown prepared Unit/world command')
 return op,v
def identities(a):
 e=json.loads(a.depth_fixture.read_text());validate_receipt(e,json.loads((a.depth_fixture.parent/'report.json').read_text()),hash_file(a.depth_fixture))
 return {'world':world.identities(a),'prepared':prepared.identities(a),'inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES},'depth_input_snapshot_sha256':hash_file(a.depth_fixture)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Prepared Unit/world engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Prepared Unit/world source/inspection/input identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Prepared Unit/world counts differ')
 ready=reset=False
 for cmd in e['commands']:
  try:op,v=parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed prepared Unit/world command') from None
  if op=='P':ready=True
  if op=='O':reset=True
  if op=='W' and not(ready and reset):raise ValueError('Prepared Unit/world lacks map or cache reset')
def generate(a):
 from original_prepared_unit_world import PreparedUnitWorldOracle
 o=PreparedUnitWorldOracle(a.exe,a.assets,a.palette.read_bytes())
 source=json.loads(a.depth_fixture.read_text());commands=[];expected=[];labels=[];groups={};draws=0
 def save(label,cmd,result):
  parse(cmd);commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);groups[label]=groups.get(label,0)+1
 def reset(seed):o.begin_unit(seed);save('indexes_pool_staging_reset',f'O 0 {seed}',['reset'])
 def prepare_map(f,label):save(label,'P '+floor.command(*f[:5],f[5:]),o.prepare_map(f))
 def draw(label,location,heading,n,contact=0,warm=False):
  nonlocal draws
  unit=[heading,((heading//2048*7+3)%32)*2048,14336,1,n%2 if not warm else 0,7 if not warm else 0,1,0,1312 if not warm else 1712,n%2,n%2,0,
    (80,-5,150)[n%3],(72,4,140)[n%3],0,0,160,144]
  v=[*location,bits(0.125),n,contact,*unit];result=o.draw_prepared(location,0.125,[n,0,contact,*unit]);draws+=1
  save(label,'W '+' '.join(map(str,v)),result)
 # Re-execute the maps in this guest. Prior receipts supply inputs only.
 for index,cmd in enumerate(source['commands'][:3]):
  f,_=prepared.parse(cmd);rows={(r[0],r[1]):r for r in f[8]};prepare_map(f,'owned_finalization_cliff_mode_'+str(index));reset(3+index)
  for n,(x,y) in enumerate([(51,72),*[(x,101) for x in range(86,94)]]):
   loc=[x*256+128,y*256+128,rows[x,y][4]*104]
   for h in ((0,16384,32768,49152) if n==0 else (0,32768)):draw('owned_cliff_and_crossing_actual_map_base_final_pixels',loc,h,n,contact=n%2)
   draw('owned_warm_missing_models_changed_brightness_and_contact',loc,49152,n,contact=1,warm=True)
 # Synthetic prepared maps cover ramps/flags/overlays/dimensions. Actor Z stays
 # supplied (level*104), and relative height stays the documented zero service.
 for index in (3,4,6,7,11,15):
  f,_=prepared.parse(source['commands'][index])
  center=next(r for r in f[8] if r[:2]==[6,6]);f[7][center[2]][7+6*center[3]]=0
  # Constrain supplied type inputs before original recalculation, never overwrite
  # a finalized Cell. Nonflat current Drive shadow poses are separately refused.
  prepare_map(f,'synthetic_flat_actor_shared_neighbor_ramps_'+str(index));reset(index)
  for n,h in enumerate(range(0,65536,16384)):draw('shared_ramps_flags_overlay_priority_and_actual_dimensions',[1664,1664,416],h,n,contact=n%2)
 return commands,expected,labels,{'groups':groups,'draws':draws,'audited_world_roots':o.audit_calls,'audited_map_roots':o.prepared.audit_calls,
  'actual_map_entries':o.prepared.entries,'actual_world_map_and_dimension_calls':o.prepared_calls,'world_calls':o.world_calls,'gradient_calls':o.gradient_calls,
  'same_guest_map_preparation_no_record_transfer':True,'actual_current_Cell_flat_preflight_and_neighbor_ramps_allowed':True,'initial_actor_absolute_Z_type_camera_planes_and_relative_zero_supplied':True,
  'neutral_relative_height_service_and_shadow_observation':True,'historical_fixtures_are_inputs_only':True,'runtime_and_full_frame_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/prepared-unit-world-vectors')
 p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin');p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets');p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal');p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
 p.add_argument('--terrain-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-map-v6/expected.json');p.add_argument('--overlay-fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json')
 p.add_argument('--parent-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-finalization-v1/expected.json');p.add_argument('--floor-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-floor-v1/expected.json');p.add_argument('--depth-fixture',type=Path,default=ROOT/'private/map-depth-1006/prepared-foot-depth-v1/expected.json')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/prepared-unit-world-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current);report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh prepared Unit/world destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native prepared Unit/world: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Prepared Unit/world counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'{i} {labels[i]}: {[(n,xx,yy) for n,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:12]}, lengths {len(x)}/{len(y)}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Prepared Unit/world run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} prepared-map / complete Unit/world results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
