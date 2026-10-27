#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare finalized Cells -> live Process -> complete posed Unit/shadow drawing."""
import argparse,json,subprocess,time,math,struct
from pathlib import Path
import compare_ground_unit_height as height
import compare_prepared_drive_state as movement
import compare_prepared_foot_depth as prepared
import compare_resident_map_floor as floor
from original_results import OriginalResults, add_arguments as add_original_arguments
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_moving_unit_world import verify
SOURCES=tuple(dict.fromkeys((*height.SOURCES,*movement.SOURCES,'tests/compare_moving_unit_world.py',
 'tests/original_moving_unit_world.py','tests/original_moving_unit_movement.py',
 'tests/moving_unit_world_vectors.cpp','tests/moving_unit_fixture.hpp','tools/verify_moving_unit_world.py')))
def parse(cmd):
 op,tail=cmd.split(' ',1)
 if op=='M':
  _,v=movement.parse(cmd);assert v[0][14:]==[1,0];return op,v
 if op=='P':return movement.parse(cmd)
 v=list(map(int,tail.split()))
 if op=='O':height.parse(cmd)
 elif op=='T':assert len(v)==1 and 1<=v[0]<=256
 elif op=='R':assert len(v)==2 and all(0<=n<2**32 and math.isfinite(struct.unpack('<f',struct.pack('<I',n))[0]) and abs(struct.unpack('<f',struct.pack('<I',n))[0])<=1 for n in v)
 elif op=='D':
  assert len(v)==22
  height.parse('W '+' '.join(map(str,[0,0,0,*v[:5],0,*v[5:]])))
 else:raise ValueError('Unknown moving Unit/world command')
 return op,v

def identities(a):
 return {'height':height.identities(a),'movement':movement.identities(a),'inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Moving Unit engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Moving Unit source/input identity differs')
 if e['evidence'].get('same_guest_live_movement_and_complete_drawing') is not True:raise ValueError('Moving Unit join differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Moving Unit counts differ')
 ready=reset=actor=False
 for cmd in e['commands']:
  try:op,_=parse(cmd)
  except (AssertionError,ValueError,IndexError,OverflowError):raise ValueError('Malformed moving Unit command') from None
  if op=='P':ready=True;actor=False
  elif op=='O':reset=True
  elif op=='M':
   if not(ready and reset):raise ValueError('Moving Unit lacks map/cache setup')
   actor=True
  elif op in ('D','T','R') and not actor:raise ValueError('Moving Unit lacks live actor')

def generate(a,ramps=range(21),owned=True,pilot=False):
 from original_moving_unit_world import MovingUnitWorldOracle
 from original_voxel_part import ACTOR
 from original_foot_voxel_staging import LOCO
 from original_map_preparation import SLOTS
 o=MovingUnitWorldOracle(a.exe,a.assets,a.palette.read_bytes())
 source=json.loads(a.depth_fixture.read_text());commands=[];expected=[];labels=[];groups={};draws=0;sampled=[]
 def run(label,cmd):
  nonlocal draws
  op,v=parse(cmd)
  if op=='P':result=o.prepare_map(v)
  elif op=='O':o.begin_unit(v[1]);result=['reset']
  elif op=='M':result=o.movement.begin(*v)
  elif op=='T':result=o.movement.advance(v[0])
  elif op=='R':o.u.mem_write(ACTOR+0x280,struct.pack('<2I',*v));result=['rocking']
  else:
   before=len(o.relative_heights);result=o.draw_live(v);draws+=1
   x,y,z=o.movement.get(ACTOR+0x88,'i'),o.movement.get(ACTOR+0x8c,'i'),o.movement.get(ACTOR+0x90,'i')
   cell=o.movement.get(SLOTS+4*((y//256)*512+x//256))
   bi=result.index('body');body_words=list(map(int,result[bi+1:bi+13]))
   sampled.append({'tick':o.movement.tick,'location':[x,y,z],'stored_ramp':o.movement.get(LOCO+0x1c),
    'previous_ramp':o.movement.get(LOCO+0x20),'Cell_ramp':o.movement.get(cell+0x11c,'B'),
    'body_matrix_dwords':body_words,'relative_heights':o.relative_heights[before:]})
  commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);groups[label]=groups.get(label,0)+1
  print(label,draws,'draws',o.movement.roots,'Process ticks',flush=True)
 def draw(label,n=0,**kw):
  values={'scale':floor.bits(.125),'seed':31,'contact':0,'no_shadow':0,'disable_shadow':0,'turret':8192,'pitch':14336,'gate':1,
   'disabled':0,'valid':7,'barrel':1,'frame':0,'brightness':1312,'predicate':0,'camera':0,'empty':0,'x':80,'y':72,'bx':0,'by':0,'bw':160,'bh':144}
  values.update(kw);run(label,'D '+' '.join(map(str,values.values())))
 template,_=prepared.parse(source['commands'][3]);common=list(template[5]);common[:5]=[6,6,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 for ramp in ramps:
  types=[[1,1,1,60,30,1,0,0,0,0,0],[1,1,1,60,30,1,0,ramp,0,0,0]]
  cells=[]
  for y in range(13):
   for x in range(13):
    if x+y>6 and abs(x-y)<6 and x+y<=18:cells.append([x,y,int(x==6),0,2 if x==6 else 0,0,-1,0,0,0,0,0,17,91,-1,41,0])
  f=(*template[:5],common,[6,0,0,6,6],types,cells,[],[],template[11],[])
  run('shared_finalization_ramp_'+str(ramp),'P '+floor.command(*f[:5],f[5:]))
  run('four_index_pool_reset','O 0 31')
  run('live_height_Unlimbo_and_Process',movement.command(steps=10,mode=ramp%4))
  draw('post_movement_Cell_vs_stored_body_ramp',camera=ramp%2,turret=(ramp*6144)%65536,predicate=ramp%2)
  run('Process_to_body_interpolation','T 2');draw('live_interpolated_body_turret_barrel',camera=ramp%2,predicate=ramp%2)
  if pilot:continue
  run('Process_to_settled_ramp','T 2');draw('live_settled_ramp_and_key',turret=(ramp*6144)%65536,predicate=ramp%2)
  if ramp in (0,1,5,13,20):
   draw('warm_exact_pose_forwarding',turret=(ramp*6144)%65536,predicate=ramp%2)
   run('Process_off_ramp_with_retained_Z','T 10');draw('departing_ramp_height_shadow_decisions',camera=1,gate=0,disabled=1,disable_shadow=1,x=-5,y=4,predicate=1)
   run('Process_new_ramp_timer','T 2');draw('return_interpolation_and_NoShadow',camera=1,no_shadow=1,barrel=ramp%2)
   run('supplied_rocking_on_the_live_actor','R '+' '.join(str(struct.unpack('<I',struct.pack('<f',n))[0]) for n in (.04,-.03)))
   draw('live_body_translation_turret_barrel_pivot',camera=1,pitch=24576,turret=40960)
   # Keep the uncached pitch experiment separate from later stock cache uses.
   run('rocking_sequence_cache_reset','O 0 31')
 if owned:
  f,_=prepared.parse(source['commands'][0]);run('owned_full_prepared_map_13515_Cells','P '+floor.command(*f[:5],f[5:]))
  run('owned_cache_reset','O 0 91')
  run('owned_parked_cliff_floor_derived_Z',movement.command(at=(51*256+128,72*256+128,-500),destination=(0,0,0),route=(),steps=1,heading=49152))
  draw('owned_parked_cliff_actual_body_and_depth',seed=91,turret=49152)
  assert o.movement.get(ACTOR+0x90,'i')==416
  for mode in range(4):
   run('owned_crossing_actor_move',movement.command(at=(86*256+128,101*256+128,31),destination=(92*256+128,101*256+128,0),route=(2,)*6,steps=64,mode=mode))
   draw('owned_crossing_complete_live_drawing',seed=91,turret=16384,camera=mode%2)
   run('owned_crossing_continue','T 64');draw('owned_crossing_later_live_drawing',seed=91,turret=16384,camera=mode%2,predicate=mode%2)
 coverage={'lagging_body_ramp_draws':sum(s['stored_ramp']!=s['Cell_ramp'] for s in sampled),
  'positive_height_draws':sum(any(h>0 for h in s['relative_heights']) for s in sampled),
  'negative_height_draws':sum(any(h<0 for h in s['relative_heights']) for s in sampled),
  'nonzero_body_translation_draws':sum(any(s['body_matrix_dwords'][i]&0x7fffffff for i in (3,7,11)) for s in sampled)}
 if not pilot and len(tuple(ramps))==21:
  assert all(coverage.values()),coverage
  assert o.live_entries.get('0x622ac0',0)>0
 return commands,expected,labels,{'groups':groups,'draws':draws,'movement_ticks':o.movement.roots,'coverage':coverage,'draw_samples':sampled,
  'actual_live_drawing_entries':o.live_entries,'actual_movement_entries':o.movement.entries,'actual_body_calls':o.body_calls,'actual_part_calls':o.part_calls,
  'actual_ground_queries':o.ground_calls,'actual_height_branch_entries':o.height_branches,'audited_world_and_movement_roots':o.audit_calls,'audited_map_roots':o.prepared.audit_calls,
  'same_guest_live_movement_and_complete_drawing':True,'no_final_actor_map_or_pose_transfer_between_guests':True,
  'initial_state_routes_speeds_Mark_occupation_mission_camera_house_planes_supplied':True,'startup_cache_lifecycle_runtime_full_frame_excluded':True}

def arguments(original_cache=False):
 # Keep the earlier complete height profile's input arguments, with explicit
 # additions for actual movement/body data. CLI parsing is defined here rather
 # than inheriting an executing main or silently changing an older profile.
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/moving-unit-world-vectors')
 p.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets/rules.ini')
 for kind,name in (('raster','raster-data.bin'),('render','render-data.bin'),('geometry','ramp-geometry-data.bin'),('direction','direction-data.bin'),('pose','ramp-pose-data.bin')):p.add_argument('--'+kind+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/name)
 p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets');p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal');p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
 for kind,name in (('terrain','resident-map-v6/expected.json'),('overlay','overlay-reader-owned-v1.json'),('parent','resident-finalization-v1/expected.json'),('floor','resident-floor-v1/expected.json'),('depth','prepared-foot-depth-v1/expected.json'),('input','ground-unit-world-v1/expected.json')):p.add_argument('--'+kind+'-fixture',type=Path,default=ROOT/'private/map-depth-1006'/name)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/moving-unit-world-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);p.add_argument('--pilot',action='store_true')
 if original_cache:add_original_arguments(p)
 return p.parse_args()
def native_args(a):return [str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette),str(a.geometry_data),str(a.direction_data),str(a.exe),str(a.pose_data)]
def main():
 a=arguments(original_cache=True);start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 reuse = OriginalResults(a, current, __file__)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());reuse.validate(validate,e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh moving Unit destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a,ramps=(1,) if a.pilot else range(21),owned=not a.pilot,pilot=a.pilot);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run(native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native moving Unit command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Moving Unit result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-10):j+16]} != {y[max(0,j-10):j+16]}; counts {len(x)}/{len(y)}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Moving Unit run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 reuse.annotate(result)
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);reuse.finish(source,report,validate);print(f'{len(commands):,} moving Unit results / {metadata["movement_ticks"]:,} ticks / {metadata["draws"]:,} complete draws: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
