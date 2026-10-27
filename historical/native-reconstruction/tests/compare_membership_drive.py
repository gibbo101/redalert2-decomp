#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare finalized Cells and complete Drive with mutable Unit map effects."""
import argparse,itertools,json,math,struct,subprocess,time
from pathlib import Path
import compare_prepared_foot_depth as prepared
import compare_resident_map_floor as floor
import compare_ground_drive_process as process
import compare_drive_body_pose as body
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_membership_drive import verify
from compare_occupied_cell import SOURCES as OCCUPIED_SOURCES
SOURCES=tuple(dict.fromkeys((*OCCUPIED_SOURCES,*prepared.SOURCES,*process.SOURCES,*body.SOURCES,
 'src/assets/PreparedDriveTerrain.hpp','src/assets/PreparedDriveTerrain.cpp',
 'tests/prepared_drive_state_vectors.cpp','tests/prepared_map_fixture.hpp',
 'tests/compare_prepared_drive_state.py','tests/original_prepared_drive_state.py',
 'tools/verify_prepared_drive_state.py','tests/original_prepared_unit_world.py',
 'tests/original_ground_unit_world.py','tools/verify_drive_shadow_pose.py',
 'src/render/DriveShadowPose.cpp','src/assets/PreparedUnitMembership.hpp','src/assets/PreparedUnitMembership.cpp','tests/membership_drive_vectors.cpp','tests/compare_membership_drive.py','tests/original_membership_drive.py','tools/verify_membership_drive.py')))
def command(at=(1408,1664,37),destination=(2176,1664,0),heading=16384,rot=5,speed=15,tick=100,steps=128,marked=0,effect=1,mode=0,present=1,key=0,route=(2,2,2),numeric=(1.,1.,.7,1.2)):
 return 'M '+' '.join(map(str,[*at,*destination,heading,rot,speed,tick,steps,marked,effect,mode,present,key,*route,*([-1]*(24-len(route))),*[floor.bits(n) for n in numeric]]))
def parse(cmd):
 op,tail=cmd.split(' ',1)
 if op=='P':
  f=floor.parse(tail);assert f[4]==104;return op,f
 assert op=='M';v=list(map(int,tail.split()));assert len(v)==44
 head,route,numeric=v[:16],v[16:40],v[40:]
 assert all(-2147483648<=n<=2147483647 for n in head)
 x,y,z,dx,dy,dz,heading,rot,speed,tick,steps,marked,effect,mode,present,key=head
 assert 0<=heading<=65535 and 1<=rot<=127 and 0<=speed<=255 and 1<=steps<=256
 assert marked==0 and effect==1 and mode in range(4) and present in (0,1)
 assert route[-1]==-1 and all(n in range(8) or n==-1 for n in route)
 end=False
 for n in route:
  if n==-1:end=True
  else:assert not end
 assert all(0<=n<1<<64 and math.isfinite(floor.number(n)) for n in numeric)
 return op,(head,route,[floor.number(n) for n in numeric])
def identities(a):
 e=json.loads(a.depth_fixture.read_text());validate_receipt(e,json.loads((a.depth_fixture.parent/'report.json').read_text()),hash_file(a.depth_fixture))
 return {'prepared':prepared.identities(a),'process':process.identities(a),'body':body.identities(a),
  'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'depth_input_snapshot_sha256':hash_file(a.depth_fixture)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Membership Drive engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Membership Drive source/input identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Membership Drive counts differ')
 ready=False
 for cmd in e['commands']:
  try:op,_=parse(cmd)
  except (AssertionError,ValueError,IndexError,OverflowError,struct.error):raise ValueError('Malformed membership Drive command') from None
  if op=='P':ready=True
  elif not ready:raise ValueError('Membership Drive lacks a prepared map')
def generate(a,ramps=range(21),owned=True):
 from original_membership_drive import MembershipDriveOracle
 o=MembershipDriveOracle(a.exe);source=json.loads(a.depth_fixture.read_text());commands=[];expected=[];labels=[];steps=0;groups={}
 def save(label,cmd,result):
  parse(cmd);commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);groups[label]=groups.get(label,0)+1
 def prepare(f,label):save(label,'P '+floor.command(*f[:5],f[5:]),o.prepare_map(f));print(label,flush=True)
 def move(label,**kw):
  nonlocal steps
  kw.setdefault('mode',len(commands)%4);cmd=command(**kw);_,v=parse(cmd)
  save(label,cmd,o.run_joined(*v));steps+=v[0][10];print(label,steps,'ticks',flush=True)
 template,_=prepared.parse(source['commands'][3]);common=list(template[5]);common[:5]=[6,6,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 for ramp in ramps:
  types=[[1,1,1,60,30,1,0,0,0,0,0],[1,1,1,60,30,1,0,ramp,0,0,0]]
  cells=[]
  for y in range(13):
   for x in range(13):
    if x+y>6 and abs(x-y)<6 and x+y<=18:
     cells.append([x,y,int(x==6),0,2 if x==6 else 0,0,-1,0,0,0,0,0,17,91,-1,41,0])
  f=(*template[:5],common,[6,0,0,6,6],types,cells,[],[],template[11],[])
  prepare(f,'shared_finalization_ramp_'+str(ramp))
  move('prepared_floor_movement_stored_body_current_Cell_shadow',steps=96)
  move('reverse_turning_floor_and_ramp_transitions',at=(2176,1664,-101),destination=(1408,1664,0),heading=0,route=(6,6,6),steps=128,key=17)
  if ramp in (0,1,5,13,20):
   move('zero_speed_parked_actual_height_and_initial_stored_ramp',at=(1664,1664,2147483647),destination=(0,0,0),route=(),steps=4,speed=0,key=-1)
   move('two_direction_route_and_null_key',at=(1408,1408,0),destination=(1920,1920,0),route=(2,4,2,4),steps=128,present=0,key=-2147483648)
   move('signed_tick_wrap_live_movement_pose_and_key',tick=2147483640,steps=128,key=2147483647,mode=3)
 if owned:
  f,_=prepared.parse(source['commands'][0]);prepare(f,'owned_full_prepared_map_13515_Cells')
  move('owned_parked_cliff_51_72_floor_derived_Z',at=(51*256+128,72*256+128,-500),destination=(0,0,0),route=(),steps=8,heading=49152)
  for mode in range(4):
   move('owned_level_crossing_live_actor_and_pose_four_FP_modes',at=(86*256+128,101*256+128,31),destination=(92*256+128,101*256+128,0),route=(2,)*6,steps=160,mode=mode)
 o.coverage['actual_body_quaternion_interpolations']=o.all_entries['0x622ac0']
 if len(tuple(ramps))==21 and not all(o.coverage[k] for k in ('different_body_shadow_matrices','stored_vs_current_Cell_ramp_lag','actual_body_quaternion_interpolations')):raise AssertionError('Missing live ramp association coverage')
 required=(0x4a1000,0x4a2670,0x41b470,0x4c2e60,0x6c2550,0x5d4160,
  0x54ab70,0x54af70,0x473b30,0x473d20,0x707980,0x7079e0,
  0x568140,0x5683c0,0x6c2440,0x5d4230,0x472540,0x478f40,0x70a2d0)
 if not all(o.all_entries[hex(a)] for a in required) or not o.eligible_unmarks:
  raise AssertionError('Missing actual Process membership/occupation/discovery/recalculation child')
 return commands,expected,labels,{'groups':groups,'movement_ticks':steps,'coverage':o.coverage,'complete_Process_calls':o.roots,'actual_Process_entries':o.entries,
  'joined_actual_entries':o.all_entries,'audited_map_roots':o.prepared.audit_calls,'actual_map_entries':o.prepared.entries,
  'actual_height_Unlimbo_initializations':o.initializations,'actual_Unit_Mark_calls':o.actual_marks,'actual_recalculations':o.actual_recalculations,'actual_eligible_unmarks':o.eligible_unmarks,'selected_membership_effect_stores':o.effect_stores,'body_shadow_pose_calls':o.pose_calls,
  'audited_pose_and_numeric_roots':o.presentation.audit_calls,'numeric_global_stores':o.numeric.global_stores,'numeric_matrix_stores':o.numeric.matrix_stores,
  'same_guest_finalization_movement_and_both_poses_no_prepared_record_transfer':True,
  'floor_derived_actor_Z_and_Process_derived_stored_ramps':True,
  'actual_mutable_Unit_membership_occupation_discovery_recalculation':True,'initial_state_routes_speeds_admission_reservation_mission_supplied':True,
  'complete_Unit_drawing_startup_runtime_and_frames_excluded':True}
def arguments():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/membership-drive-vectors')
 p.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets/rules.ini')
 for kind,name in (('render','render-data.bin'),('raster','raster-data.bin'),('direction','direction-data.bin'),('geometry','ramp-geometry-data.bin'),('pose','ramp-pose-data.bin')):p.add_argument('--'+kind+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/name)
 for kind,name in (('terrain','resident-map-v6/expected.json'),('overlay','overlay-reader-owned-v1.json'),('parent','resident-finalization-v1/expected.json'),('floor','resident-floor-v1/expected.json'),('depth','prepared-foot-depth-v1/expected.json')):p.add_argument('--'+kind+'-fixture',type=Path,default=ROOT/'private/map-depth-1006'/name)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/membership-drive-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 return p.parse_args()
def native_args(a):return [str(a.native),str(a.exe),*[str(getattr(a,k+'_data')) for k in ('render','raster','direction','geometry','pose')]]
def main():
 a=arguments();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh membership Drive destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run(native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native membership Drive command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Membership Drive result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-10):j+16]} != {y[max(0,j-10):j+16]}; counts {len(x)}/{len(y)}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Membership Drive run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} membership Drive sequences / {metadata["movement_ticks"]:,} movement ticks: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
