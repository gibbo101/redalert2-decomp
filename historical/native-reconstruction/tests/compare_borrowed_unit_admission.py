#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual prepared-owner admission with exact original Unit roots.

This is a separate dependency proof, not complete Process/runtime adoption.
"""
import argparse,copy,itertools,json,subprocess,time
from pathlib import Path
import compare_moving_unit_admission as parent
import compare_unit_admission as base
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
SOURCES=tuple(dict.fromkeys((*parent.SOURCES,
 'src/sim/BorrowedUnitAdmission.hpp','src/sim/UnitNextCell.hpp','src/sim/UnitNextCell.cpp',
 'src/sim/UnitDestination.hpp','src/sim/FootDestination.hpp','src/assets/BorrowedPreparedUnitAdmission.hpp',
 'src/assets/PreparedUnitMembership.hpp','src/assets/PreparedUnitMembership.cpp',
 'src/sim/GroundDriveProcess.hpp','src/sim/GroundDriveAdvance.hpp','src/sim/GroundDriveOverlay.hpp','src/sim/GroundMovementPlacement.hpp',
 'src/sim/ActorGroundState.hpp','src/sim/UnitMembership.hpp','src/sim/UnitMembership.cpp',
 'src/sim/UnitMark.hpp','src/sim/UnitMark.cpp','src/sim/UnitOccupation.hpp','src/sim/UnitOccupation.cpp',
 'src/sim/MapVisibility.hpp','src/sim/MapVisibility.cpp',
 'src/assets/MapCellInputs.hpp','src/assets/MapFloorHeight.hpp','src/assets/MapCellAttributes.hpp',
 'src/assets/MapFloorHeight.cpp','src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp',
 'src/assets/MapCellChildren.hpp','src/assets/MapCellChildren.cpp','src/assets/MapCellAttributes.cpp',
 'src/assets/ResidentCellPreparation.hpp','src/assets/OccupiedCellPassability.hpp','src/assets/OccupiedCellPassability.cpp',
 'src/assets/Bytes.hpp','src/assets/Formats.hpp','src/assets/MapOverlay.hpp',
 'tests/borrowed_admission_fixture.hpp','tests/borrowed_unit_admission_vectors.cpp',
 'tests/borrowed_unit_admission_check.cpp','tests/borrowed_unit_admission/CMakeLists.txt',
 'tests/compare_borrowed_unit_admission.py','tests/test_borrowed_unit_admission_evidence.py')))

def command(**kw):return parent.command(**kw)
def parse(cmd):
 fixture,rows,mode=parent.parse(cmd)
 h,dirs,speeds,houses,regs,cells,objects,steps=fixture
 base.require(all(c[11]<=1 and c[12]<=1 for c in cells))
 base.require(all(o[1]<=1 and o[13]<=1 and o[14]<=1 and not o[3] for o in objects[:2]))
 # Other original actors remain supplied and unreachable. They do not become
 # hidden native residents or substitute for either bound production actor.
 base.require(all(o==parent.OBJECTS[i] for i,o in enumerate(objects) if i>=2))
 return fixture,rows,mode

def identities(a):
 result=parent.identities(a)
 result['sources']={p:hash_file(ROOT/p) for p in SOURCES}
 return result

def validate(e,r,f,current):
 parent.validate(e,r,f,current)
 if not e['evidence'].get('actual_prepared_owner_binding'):
  raise ValueError('Missing prepared-owner evidence scope')
 for cmd in e['commands']:parse(cmd)

def generate(a):
 from original_moving_unit_admission import MovingUnitAdmissionOracle
 oracle=MovingUnitAdmissionOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,motion=None,**kw):
  cmd=command(motion=motion,mode=len(commands)%4,**kw);fixture,rows,_=parse(cmd);oracle.motion=rows
  result=oracle.run(*fixture);commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1
 for distance,eligibility,target,flags in itertools.product((0,511,512,1024),(0,1),(-1,0),(1,5)):
  motion=copy.deepcopy(parent.MOTION);motion[1][0]=motion[0][0]+distance;motion[1][14]=eligibility
  objects=copy.deepcopy(parent.OBJECTS);objects[1][13]=target;objects[1][7]=flags
  add('actual_prepared_Drive_target_flags_eligibility_and_distance',motion,objects=objects)
 for own,other in itertools.product((0,4095,4096,32767,49152,65535),repeat=2):
  motion=copy.deepcopy(parent.MOTION);motion[0][9:11]=[own,own];motion[1][9:11]=[other,other]
  add('actual_distinct_body_Facings_and_original_bearing',motion)
 for activity in ('idle','destinationZ','headZ','headXY','turn'):
  motion=copy.deepcopy(parent.MOTION);motion[1][3:9]=[0]*6
  if activity=='destinationZ':motion[1][5]=1
  if activity=='headZ':motion[1][6:9]=[*motion[1][:2],7]
  if activity=='headXY':motion[1][6:9]=[motion[1][0]+1,motion[1][1],0]
  if activity=='turn':motion[1][9:14]=[49152,32768,300,40,1280]
  add('borrowed_full_sentinels_XY_and_rotation_'+activity,motion)
 for mission,target,destination,head in itertools.product((2,7,11),(-1,0,1),(-1,1),(0,1)):
  objects=copy.deepcopy(parent.OBJECTS);objects[0][4]=mission;objects[0][13:15]=[target,destination]
  cells=copy.deepcopy(parent.CELLS);cells[0][11]=head
  add('actual_mission_target1B0_versus_target494_and_self_skip',objects=objects,cells=cells)
 for owner,state,weapon in itertools.product((0,1,2),(0,2),(0,1)):
  objects=copy.deepcopy(parent.OBJECTS);objects[1][2]=owner;objects[1][12]=state;objects[0][15]=weapon
  add('prepared_House_metadata_and_enemy_state_decisions',objects=objects)
 for occupation,elevated,bits in itertools.product((0,32,0x80000000,0xffffffff),(0,1),(0,0x3f800000,0x7fc00000)):
  cells=copy.deepcopy(parent.CELLS);cells[0][11:13]=[-1,-1]
  if elevated:cells[0][5]=0x300;cells[1][5]=0x100;cells[0][3]=-4
  cells[0][6]=occupation;cells[0][7]=occupation
  add('actual_whole_occupation_upper_bits_and_shared_speed_table',cells=cells,speeds=[bits]*12,
      steps=[['U',0,0,2,0,1,1,255]])
 for level,delta,ramp in itertools.product((-1,0,4),(-4,-1,0,1,4),(0,1)):
  cells=copy.deepcopy(parent.CELLS);cells[0][3:6]=[0,ramp,0x300];cells[1][3:6]=[delta,ramp,0x100]
  add('actual_signed_levels_ramps_and_retained_outputs',cells=cells,
      steps=[['T',0,0,2,level,1,1,255],['U',0,0,2,level,1,1,255]])
 for direction,point in itertools.product((-1,0,2,7),((-32768,32767),(-7,5),(32767,0))):
  h=base.HEADER.copy();h[1:3]=[-1,-1];cells=copy.deepcopy(parent.CELLS);cells[2][:2]=point
  add('actual_shared_prepared_fallback_repeated_lookup_saved_words',h=h,cells=cells,
      steps=[['U',0,2,direction,0,-1,1,255],['T',0,2,direction,-1,-1,0,7],['U',0,2,2,0,-1,1,255]])
 base.require(set(oracle.root_results)=={0,1,2,5,6,7} and set(oracle.terrain_results)=={0,7})
 return commands,expected,labels,{'groups':groups,'audited_original_calls':oracle.audit_calls,
  'actual_entries':oracle.entries,'actual_moving_entries':oracle.moving_entries,
  'entered_distinct_instructions':len(oracle.instructions),'root_return_codes':oracle.root_results,
  'terrain_return_codes':oracle.terrain_results,'actual_distance_returns':oracle.distance_returns,
  'actual_switch_returns':oracle.switch_returns,'complete_parent_and_actual_moving_children':True,
  'actual_prepared_owner_binding':True,'initial_records_and_associations_supplied':True,
  'Process_runtime_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin');p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--native',type=Path,default=ROOT/'build/borrowed-unit-admission/borrowed-unit-admission-vectors');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/borrowed-unit-admission-new')
 p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh borrowed admission destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 args=[str(a.native),str(a.exe),str(a.direction_data),str(a.render_data)]
 now=time.monotonic();proc=subprocess.run(args,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native borrowed admission command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Borrowed admission result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-12):j+20]} != {y[max(0,j-12):j+20]}; counts {len(x)}/{len(y)}')
 safety=['','V 0',command()+' trailing',command(mode=4),command().replace(' M ',' X ',1)]
 for cmd in safety:
  bad=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if not bad.returncode or not bad.stderr.strip():raise AssertionError('Missing borrowed admission native refusal')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Borrowed admission run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} borrowed admission results: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
