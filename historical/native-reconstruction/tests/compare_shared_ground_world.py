#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare two posed actors sharing prepared-map/world/shadow and cache owners."""
import argparse,json,math,struct,subprocess,time
from pathlib import Path
import compare_moving_unit_world as moving
import compare_ground_unit_world as ground
import compare_prepared_foot_depth as prepared
import compare_resident_map_floor as floor
from original_results import OriginalResults, add_arguments as add_original_arguments
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_shared_ground_world import verify
SOURCES=tuple(dict.fromkeys((*moving.SOURCES,'src/render/SharedGroundUnitVoxelWorld.hpp',
 'src/render/SharedUnitVoxelStaging.hpp','tests/compare_shared_ground_world.py',
 'tests/original_shared_ground_world.py','tests/original_shared_unit_staging.py',
 'tests/shared_ground_world_vectors.cpp','tests/shared_ground_world_check.cpp',
 'tests/test_shared_ground_world_evidence.py','tools/verify_shared_ground_world.py','CMakeLists.txt')))
def parse(cmd):
 op,tail=cmd.split(' ',1)
 if op in ('P','O'):return ground.parse(cmd)
 v=list(map(int,tail.split()))
 if op=='S':
  assert len(v)==16 and v[0] in (0,1) and 0<=v[1]<512*256 and 0<=v[2]<512*256 and abs(v[3])<=1048576
  assert all(0<=n<=65535 for n in v[4:7]) and all(-2147483648<=n<=2147483647 for n in v[7:14])
  assert v[8] in range(21) and v[9] in range(21)
  assert all(0<=n<2**32 and math.isfinite(struct.unpack('<f',struct.pack('<I',n))[0]) and abs(struct.unpack('<f',struct.pack('<I',n))[0])<=1 for n in v[14:])
 elif op=='D':
  assert len(v)==20 and v[0] in (0,1)
  ground.parse('W '+' '.join(map(str,[1664,1664,0,v[1],0,*v[2:5],0,0,0,*v[5:]])))
 else:raise ValueError('Unknown shared ground drawing command')
 return op,v
def identities(a):
 return {'moving_inspection_and_inputs':moving.identities(a),
  'inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Shared world engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Shared world identity differs')
 if not(e['evidence'].get('same_guest_distinct_actors_prepared_map_world_and_shadow') and e['evidence'].get('world_not_reset_between_actors')):raise ValueError('Shared world join differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[]))):raise ValueError('Shared world counts differ')
 ready=reset=False;actors=set()
 for cmd in e['commands']:
  try:op,v=parse(cmd)
  except (AssertionError,ValueError,IndexError,OverflowError,struct.error):raise ValueError('Malformed shared world command') from None
  if op=='P':ready=True;reset=False;actors=set()
  elif op=='O':
   if not ready:raise ValueError('Shared world prepared map required')
   reset=True;actors=set()
  elif op=='S':
   if not reset:raise ValueError('Shared world reset required')
   actors.add(v[0])
  elif not(reset and len(actors)==2):raise ValueError('Both shared world actors required')
def generate(a,pilot=False):
 from original_shared_ground_world import SharedGroundWorldOracle
 from original_shared_unit_staging import SUBJECTS,DRIVES
 from original_map_preparation import SLOTS
 from original_foot_lit import words,ints
 o=SharedGroundWorldOracle(a.exe,a.assets,a.palette.read_bytes())
 source=json.loads(a.depth_fixture.read_text());commands=[];expected=[];labels=[];draws=0;samples=[];states={};groups={}
 def run(label,cmd):
  nonlocal draws
  op,v=parse(cmd)
  if op=='P':result=o.prepare_map(v);states.clear()
  elif op=='O':o.reset_shared(v[1]);states.clear();result=['reset']
  elif op=='S':states[v[0]]=v[1:];result=o.set_actor(v[0],v[1:])
  else:
   id=v[0];before=len(o.relative_heights);result=o.draw_shared(id,states[id][6],v[1:]);draws+=1
   actor,drive=SUBJECTS[id],DRIVES[id];x,y,z=ints(o.u,actor+0x88,3)
   cell=words(o.u,SLOTS+((y//256)*512+x//256)*4,1)[0]
   bi=result.index('body');body=list(map(int,result[bi+1:bi+13]))
   samples.append({'actor':id,'location':[x,y,z],'stored_ramp':words(o.u,drive+0x1c,1)[0],
    'Cell_ramp':o.u.mem_read(cell+0x11c,1)[0],'relative_heights':o.relative_heights[before:],
    'body_matrix_dwords':body,'world_color_sha256':result[result.index('world')+1]})
  commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);groups[label]=groups.get(label,0)+1
  print(label,draws,'draws',flush=True)
 def actor(id,body=0,turret=8192,z=416,current=0,previous=0,remaining=0,duration=0,rock=(0.,0.),x=1664,y=1664):
  raw=[struct.unpack('<I',struct.pack('<f',n))[0] for n in rock]
  run('supplied_distinct_actor_Drive_turret_records','S '+' '.join(map(str,[id,x,y,z,body,turret,14336,2,current,previous,0,7,remaining,duration,*raw])))
 def draw(id,label='interleaved_complete_world',**kw):
  fields={'scale':floor.bits(.125),'contact':0,'no_shadow':0,'disable_shadow':0,'gate':1,'disabled':0,'valid':7,
   'barrel':1,'frame':0,'brightness':1312,'predicate':1,'camera':0,'empty':0,'x':80+id*5,'y':72,'bx':0,'by':0,'bw':160,'bh':144}
  fields.update(kw);run(label,'D '+' '.join(map(str,[id,*fields.values()])))
 template,_=prepared.parse(source['commands'][3]);common=list(template[5]);common[:5]=[6,6,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 for ramp in ((1,) if pilot else range(21)):
  types=[[1,1,1,60,30,1,0,0,0,0,0],[1,1,1,60,30,1,0,ramp,0,0,0]]
  cells=[[x,y,int(x==6),0,2 if x==6 else 0,0,-1,0,0,0,0,0,17,91,-1,41,0] for y in range(13) for x in range(13) if x+y>6 and abs(x-y)<6 and x+y<=18]
  f=(*template[:5],common,[6,0,0,6,6],types,cells,[],[],template[11],[])
  run('shared_prepared_map_ramp_'+str(ramp),'P '+floor.command(*f[:5],f[5:]));run('shared_global_world_pool_reset','O 0 31')
  heading=(ramp*3%32)*2048;turret=(ramp*7%32)*2048
  actor(0,heading,turret,current=ramp);actor(1,(heading+32768)&65535,(turret+32768)&65535,z=-1,current=(ramp+1)%21,y=1920)
  draw(0);draw(1);draw(0,'warm_first_actor_after_other');draw(1,'warm_second_actor_after_other')
  if pilot:continue
  actor(1,heading,turret,current=ramp,y=1920)
  draw(1,'equal_pose_actual_cross_actor_cache_hit');draw(0,'overlapping_world_keeps_prior_actor_pixels')
  actor(0,heading,turret,z=52,current=ramp,remaining=3,duration=3,previous=(ramp+7)%21,rock=(.04,-.03))
  draw(0,'interpolated_rocking_body_barrel_translation',camera=1,predicate=0,gate=0,disabled=1,disable_shadow=1)
  draw(1,'other_actor_unchanged_after_pose_change',contact=ramp%2,no_shadow=ramp%2,barrel=ramp%2,empty=ramp%3,x=-5,y=4)
 if not pilot:
  f,_=prepared.parse(source['commands'][0]);run('owned_13515_Cell_map','P '+floor.command(*f[:5],f[5:]));run('owned_shared_world_reset','O 0 91')
  actor(0,49152,8192,z=416,current=0,x=51*256+128,y=72*256+128)
  actor(1,16384,40960,z=416,current=0,x=52*256+128,y=72*256+128)
  for id in (1,0,1,0):draw(id,'owned_cliff_interleaved_draw',predicate=id)
 coverage={'lagged_body_current_Cell_draws':sum(s['stored_ramp']!=s['Cell_ramp'] for s in samples),
  'positive_height_draws':sum(any(h>0 for h in s['relative_heights']) for s in samples),
  'negative_height_draws':sum(any(h<0 for h in s['relative_heights']) for s in samples),
  'translated_body_draws':sum(any(s['body_matrix_dwords'][i]&0x7fffffff for i in (3,7,11)) for s in samples)}
 if not pilot:assert all(coverage.values()) and all(o.cross_actor_hits) and o.warm_shortcuts and o.cold_transforms,coverage
 assert o.selected_writes==draws*8 and o.shared_calls==draws
 return commands,expected,labels,{'draws':draws,'groups':groups,'coverage':coverage,'samples':samples,
  'actual_part_matrices':o.part_calls,'selected_ordered_stores':o.selected_writes,'cross_actor_cache_hits':o.cross_actor_hits,
  'warm_matrix_shortcuts':o.warm_shortcuts,'cold_matrix_builds':o.cold_transforms,
  'actual_height_branches':o.height_branches,'actual_ground_queries':o.ground_calls,
  'actual_shadow_calls':o.shadow_calls,'raw_shadow_spans':o.raw_spans,'cached_shadow_spans':o.shadow_spans,
  'audited_roots':o.audit_calls,'audited_map_roots':o.prepared.audit_calls,
  'same_guest_distinct_actors_prepared_map_world_and_shadow':True,'world_not_reset_between_actors':True,
  'initial_actor_Drive_pose_turret_type_House_camera_planes_heap_supplied':True,
  'Process_membership_live_owned_map_runtime_and_frame_excluded':True,'runtime_unwired':True,'pilot':pilot}

def arguments(original_cache=False):
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/shared-ground-world-vectors')
 p.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets/rules.ini')
 for kind,name in (('raster','raster-data.bin'),('render','render-data.bin'),('geometry','ramp-geometry-data.bin'),('direction','direction-data.bin'),('pose','ramp-pose-data.bin')):p.add_argument('--'+kind+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/name)
 p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets');p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal');p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
 for kind,name in (('terrain','resident-map-v6/expected.json'),('overlay','overlay-reader-owned-v1.json'),('parent','resident-finalization-v1/expected.json'),('floor','resident-floor-v1/expected.json'),('depth','prepared-foot-depth-v1/expected.json'),('input','ground-unit-world-v1/expected.json')):p.add_argument('--'+kind+'-fixture',type=Path,default=ROOT/'private/map-depth-1006'/name)
 p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/shared-ground-world-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);p.add_argument('--pilot',action='store_true')
 if original_cache:add_original_arguments(p)
 return p.parse_args()
def native_args(a):return [str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette),str(a.geometry_data),str(a.direction_data),str(a.pose_data)]

def main():
 a=arguments(original_cache=True);start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 reuse = OriginalResults(a, current, __file__)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());reuse.validate(validate,e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh shared ground world destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a,pilot=a.pilot);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run(native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native shared ground world command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Shared ground world result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-10):j+16]} != {y[max(0,j-10):j+16]}; counts {len(x)}/{len(y)}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Shared ground world run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 reuse.annotate(result)
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);reuse.finish(source,report,validate);print(f'{len(commands):,} shared ground world results / {metadata["draws"]:,} complete draws: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
