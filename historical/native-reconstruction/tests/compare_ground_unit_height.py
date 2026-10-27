#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete prepared-map Unit drawing on both height shadow branches."""
import argparse,json,subprocess,time
from pathlib import Path
import compare_ground_unit_world as base
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_map_floor_height import bits,number
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_unit_height import verify
SOURCES=tuple(dict.fromkeys((*base.SOURCES,'tests/compare_ground_unit_height.py',
 'tests/original_ground_unit_height.py','tools/verify_ground_unit_height.py')))
parse=base.parse
def identities(a):
 source=json.loads(a.input_fixture.read_text())
 validate_receipt(source,json.loads((a.input_fixture.parent/'report.json').read_text()),hash_file(a.input_fixture))
 return {'ground':base.identities(a),'inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES},'input_snapshot_sha256':hash_file(a.input_fixture)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Height-aware Unit engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Height-aware Unit source/input identity differs')
 if e['evidence'].get('height_aware_native_entry') is not True:raise ValueError('Height-aware Unit entry differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Height-aware Unit counts differ')
 ready=reset=False
 for cmd in e['commands']:
  try:op,_=parse(cmd)
  except (AssertionError,ValueError,IndexError,OverflowError):raise ValueError('Malformed height-aware Unit command') from None
  if op=='P':ready=True
  if op=='O':reset=True
  if op=='W' and not(ready and reset):raise ValueError('Height-aware Unit lacks map or cache reset')
def generate(a):
 from original_ground_unit_height import GroundUnitHeightOracle
 o=GroundUnitHeightOracle(a.exe,a.assets,a.palette.read_bytes())
 historical=json.loads(a.input_fixture.read_text());commands=[];expected=[];labels=[];groups={};draws=0;pm=0
 def run(label,cmd,relative=None):
  nonlocal draws,pm
  op,v=parse(cmd)
  if op=='P':result=o.prepare_map(v)
  elif op=='O':pm=v[0];o.begin_unit(v[1]);result=['reset']
  else:
   before=len(o.relative_heights)
   result=o.draw_ground(v[:3],number(v[3]),[v[4],pm,*v[5:]]);draws+=1
   if relative is not None:
    heights=o.relative_heights[before:]
    if not heights or any(n!=relative for n in heights):raise AssertionError('Original boundary relative height differs: '+str(heights)+' != '+str(relative))
  commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);groups[label]=groups.get(label,0)+1
  print(label,draws,'draws',flush=True)
 # Historical prepared-map commands supply inputs only. The unchanged older
 # draw domain is freshly checked separately with compare_ground_unit_world.
 maps=[cmd for cmd in historical['commands'] if cmd.startswith('P ')]
 for i,p in enumerate(maps):
  run('prepared_height_branch_map_'+str(i),p);run('height_branch_reset',f'O 0 {100+i}')
  if i<21:location=[1664,1664,416]
  else:location=[51*256+128,72*256+128,417]
  for j,predicate in enumerate((0,1,1) if i in (0,1,20,21) else (0,)):
   heading=(i*3%32)*2048
   unit=[heading,((heading//2048*7+3)%32)*2048,14336,1,0,7,1,0,1312,predicate,j%2,0,80,72,0,0,160,144]
   run('positive_height_stencil_raw_or_predicate_cached','W '+' '.join(map(str,[*location,bits(.125),100+i,0,0,0,*unit])))
  # The synthetic center has level zero: its flat floor is 0. The supplied
  # owned cliff is 416. Check the actual original return, not just this label.
  # Probe each side of the branch, zero projected pixels, clipping and NoShadow.
  if i in (0,21):
   floor=0 if i==0 else 416
   for z in (floor-1,floor,floor+1,floor+7,floor+8,floor+9,floor+104):
    for predicate in ((0,1) if z in (floor+1,floor+8) else (0,)):
     unit=[16384,8192,14336,1,0,7,1,0,1312,predicate,0,0,80,72,0,0,160,144]
     run('height_zero_and_projection_boundaries','W '+' '.join(map(str,[*location[:2],z,bits(.125),131,0,0,0,*unit])),relative=z-floor)
   for no_shadow,disable in ((1,0),(0,1)):
    unit=[16384,8192,14336,0,1,7,1,0,1712,0,1,0,-5,4,0,0,160,144]
    run('positive_NoShadow_or_bypass_clipping','W '+' '.join(map(str,[*location,bits(.125),137,1,no_shadow,disable,*unit])))
 if not all(o.height_branches.values()):raise AssertionError('Missing actual Unit height branch coverage')
 return commands,expected,labels,{'groups':groups,'draws':draws,'height_aware_native_entry':True,'actual_height_branch_entries':o.height_branches,
  'actual_relative_height_samples':{'positive':sum(n>0 for n in o.relative_heights),'zero':o.relative_heights.count(0),'negative':sum(n<0 for n in o.relative_heights)},
  'boundary_original_relative_returns_asserted':True,
  'audited_world_roots':o.audit_calls,'audited_map_roots':o.prepared.audit_calls,'actual_ground_queries':o.ground_calls,
  'actual_shadow_calls':o.shadow_calls,'actual_raw_shadow_spans':o.raw_spans,'actual_rle_shadow_spans':o.shadow_spans,
  'actual_gradient_surface_calls':o.gradient_calls,'numeric_global_stores':o.numeric.global_stores,'numeric_matrix_stores':o.numeric.matrix_stores,
  'same_guest_prepared_map_actual_floor_and_complete_draw':True,'initial_actor_Z_and_flat_settled_lit_state_supplied':True,
  'historical_receipts_inputs_only':True,'movement_runtime_startup_full_frame_excluded':True}
def arguments():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-unit-world-vectors')
 for kind,name in (('raster','raster-data.bin'),('render','render-data.bin'),('geometry','ramp-geometry-data.bin'),('direction','direction-data.bin')):p.add_argument('--'+kind+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/name)
 p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets');p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal');p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
 for kind,name in (('terrain','resident-map-v6/expected.json'),('overlay','overlay-reader-owned-v1.json'),('parent','resident-finalization-v1/expected.json'),('floor','resident-floor-v1/expected.json'),('depth','prepared-foot-depth-v1/expected.json')):p.add_argument('--'+kind+'-fixture',type=Path,default=ROOT/'private/map-depth-1006'/name)
 p.add_argument('--input-fixture',type=Path,default=ROOT/'private/map-depth-1006/ground-unit-world-v1/expected.json')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-unit-height-v2');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 return p.parse_args()
def native_args(a):return [str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette),str(a.geometry_data),str(a.direction_data),'--height-aware']
def main():
 a=arguments();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh height-aware Unit destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run(native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native height-aware Unit command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Height-aware Unit result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'{i} {labels[i]}: {[(j,xx,yy) for j,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:12]}, counts {len(x)}/{len(y)}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Height-aware Unit run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} height-aware complete Unit results / {metadata["draws"]:,} draws: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
