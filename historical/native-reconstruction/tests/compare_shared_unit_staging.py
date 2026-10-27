#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare interleaved two-actor original Unit staging with explicit native owners."""
import argparse,json,subprocess,time
from pathlib import Path
import compare_unit_voxel_staging as parent
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from verify_shared_unit_staging import verify
SOURCES=(*parent.SOURCES,'src/render/SharedUnitVoxelStaging.hpp','src/render/SharedUnitVoxelStaging.cpp',
 'tests/shared_unit_staging_vectors.cpp','tests/original_shared_unit_staging.py',
 'tests/compare_shared_unit_staging.py','tests/test_shared_unit_staging_evidence.py','tests/shared_unit_staging_check.cpp','tools/verify_shared_unit_staging.py','CMakeLists.txt')
def parse(cmd):
 t=cmd.split()
 def require(v):
  if not v:raise ValueError('Malformed shared Unit staging command')
 require(bool(t));v=list(map(int,t[1:]));require(all(-2147483648<=n<=2147483647 for n in v))
 if t[0]=='O':require(len(v)==2 and v[0] in (0,1) and 0<=v[1]<=100000)
 elif t[0]=='S':require(len(v)==7 and v[0] in (0,1) and all(0<=n<=65535 for n in v[1:4]) and v[-1]==0)
 elif t[0]=='D':
  require(len(v)==16 and v[0] in (0,1) and 0<=v[1]<=255 and v[2] in (0,1) and 0<=v[3]<=7 and v[4] in (0,1)
   and 0<=v[7]<=255 and v[8] in (0,1) and v[9] in range(3) and all(abs(n)<=1048576 for n in v[10:]))
 else:raise ValueError('Unknown shared Unit staging command')
 return t[0],v
def identities(a):
 return {**parent.identities(a),'shared_inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
  'shared_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Shared staging engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Shared staging identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[]))):raise ValueError('Shared staging counts differ')
 ready=False;actors=set()
 for cmd in e['commands']:
  try:op,v=parse(cmd)
  except (ValueError,IndexError,TypeError):raise ValueError('Malformed shared staging command') from None
  if op=='O':ready=True;actors=set()
  elif not ready:raise ValueError('Shared staging reset required')
  elif op=='S':actors.add(v[0])
  elif len(actors)!=2:raise ValueError('Both supplied actors required')
def generate(a):
 from original_shared_unit_staging import SharedUnitStagingOracle
 commands=[];expected=[];labels=[];audits=[]
 def save(label,op,v,result):
  cmd=op+' '+' '.join(map(str,v));parse(cmd);commands.append(cmd);expected.append(list(map(str,result)));labels.append(label)
 for pm in range(2):
  o=SharedUnitStagingOracle(a.exe,a.assets,bytes(768) if pm else a.palette.read_bytes())
  o.reset_shared(3);save('shared_global_stage_type_indexes_pool_reset','O',[pm,3],['reset'])
  def actor(id,body,turret,pitch=14336):
   v=[body,turret,pitch,2560+id*256,2816,0];o.set_actor(id,v);save('supplied_distinct_actor_Facing_location_records','S',[id,*v],['set'])
  def draw(id,label,**kwargs):
   v=[kwargs.get(k,default) for k,default in zip(('gate','disabled','valid','barrel','frame','brightness','predicate','camera','template','x','y','bx','by','bw','bh'),
    (1,0,7,1,0,1312,0,0,0,30+id*60,40,0,0,256,256))]
   save(label,'D',[id,*v],o.draw_actor(id,v));print(pm,id,label,flush=True)
  for n in range(32):
   body=n*2048;turret=((n*7+3)%32)*2048
   actor(0,body,turret);actor(1,(body+32768)&65535,(turret+32768)&65535,15360)
   draw(0,'interleaved_first_actor_cold_or_shared_cache',camera=n%2)
   draw(1,'opposite_actor_cold_or_shared_cache',camera=n%2)
   draw(0,'first_actor_warm_after_other_actor',brightness=65535,valid=0,predicate=1,camera=1-n%2)
   draw(1,'second_actor_warm_after_other_actor',brightness=0,predicate=255,camera=1-n%2,x=-3,by=7,bw=211,bh=201)
  # Equal pose proves actual cache hits whose snapshots came from the other
  # actor; changing actor0 then drawing actor1 exposes unintended state aliasing.
  actor(0,4096,32768);actor(1,4096,32768,0)
  draw(0,'same_type_pose_first_actor');draw(1,'same_type_cross_actor_warm_hit')
  actor(0,6144,40960,16384)
  draw(1,'unchanged_second_actor_after_first_pose_change');draw(0,'changed_first_actor_pose')
  for id in (1,0):
   for disabled,gate,valid,barrel,template in ((1,1,7,1,2),(0,0,7,1,0),(0,1,3,0,1),(1,1,0,0,2)):
    draw(id,'independent_actor_bypass_optional_and_invalid_cleanup',disabled=disabled,gate=gate,valid=valid,barrel=barrel,template=template)
  assert o.cross_actor_hits and o.warm_shortcuts and o.cold_transforms
  assert o.selected_writes==o.shared_calls*8 and o.part_calls
  audits.append({'palette':pm,'complete_Unit_calls':o.shared_calls,'audited_roots':o.audit_calls,
   'selected_ordered_stores':o.selected_writes,'actual_part_matrices':o.part_calls,'cross_actor_cache_hits':o.cross_actor_hits,
   'warm_matrix_shortcuts':o.warm_shortcuts,'cold_matrix_builds':o.cold_transforms,
   'cache_calls':o.joined_calls,'cached_spans':o.cache_counts,'raster_calls':o.actual_calls,'heap_allocations':len(o.allocations)})
 return commands,expected,labels,{'audits':audits,'native_pool_capacity':0x80000,'runtime_unwired':True,
  'initial_associations_visibility_height_final_world_shadow_and_heap_supplied':True}
def arguments():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 for key,value in (('assets','private/migration/supplied-ra2-1006/raster/assets'),('palette','private/migration/supplied-ra2-1006/staging/assets/temperat.pal'),
  ('raster-data','private/derived/ra2-1006/raster-data.bin'),('render-data','private/derived/ra2-1006/render-data.bin'),('poses','private/unit-draw-1006/barrel-v1/expected.json'),
  ('native','build/native/shared-unit-staging-vectors'),('output','private/unit-draw-1006/shared-unit-stage-v1')):p.add_argument('--'+key,type=Path,default=ROOT/value)
 p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);return p.parse_args()
def main():
 a=arguments();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';e=json.loads(source.read_text());fingerprint=hash_file(source)
  validate(e,json.loads(receipt.read_text()),fingerprint,current);report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh shared staging destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();native=[str(p) for p in (a.native,a.raster_data,a.render_data,a.assets,a.palette)]
 proc=subprocess.run(native,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native shared staging: '+proc.stderr.strip())
 actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Shared staging result count differs')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-9):j+16]} != {y[max(0,j-9):j+16]}; lengths {len(x)}/{len(y)}')
 safety=('', 'O 0 -1','S 2 0 0 0 0 0 0','S 0 0 0 0 0 0 1','D 0','D 0 1 0 7 1 0 1000 0 0 0 0 0 0 0 256 256')
 for cmd in safety:
  r=subprocess.run(native,input='O 0 3\n'+cmd+'\n',text=True,capture_output=True)
  if not r.returncode or not r.stderr.strip():raise AssertionError('Shared staging safety refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Shared staging inputs changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'original_generation_seconds':generation,'native_comparison_seconds':elapsed,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
   'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 write_report(a.exe,report,{**result,'expectations_sha256':fingerprint})
 print(f'{len(commands):,} interleaved two-actor staging results: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
