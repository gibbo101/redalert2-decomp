#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete ordinary Process/preparation/Advance on shared terrain Cells."""
import argparse,configparser,itertools,json,math,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_ground_movement_placement import SOURCES as PLACEMENT_SOURCES
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_drive_process import verify
SOURCES=tuple(dict.fromkeys((*PLACEMENT_SOURCES,'src/sim/GroundDriveProcess.hpp','src/sim/GroundDriveProcess.cpp',
 'tests/ground_drive_process_vectors.cpp','tests/original_ground_drive_process.py','tests/compare_ground_drive_process.py',
 'tools/verify_ground_drive_process.py','tests/original_movement.py','tests/movement_profiles.py','src/sim/Drive.cpp','src/sim/GroundDriveAdvance.hpp','src/sim/GroundDriveAdvanceResult.hpp','src/sim/GroundDriveAdvance.cpp','src/sim/GroundDriveOverlay.hpp','tests/original_ground_drive_advance.py',
 'src/assets/MovementData.hpp','src/assets/MovementData.cpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp',
 'src/assets/Bytes.hpp','src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp',
 'src/assets/MapCellChildren.hpp','src/assets/MapCellChildren.cpp','src/assets/RenderData.hpp','src/assets/RenderData.cpp','src/render/Lighting.hpp','src/render/Lighting.cpp')))
SOURCES=tuple(dict.fromkeys((*SOURCES,'tests/GroundDriveGateVectors.hpp',
 'src/sim/GroundDriveAdvanceAdmission.hpp',
 'src/sim/MovementGate.hpp','src/sim/MovementGate.cpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp',
 'tests/GroundDriveAdmissionVectors.hpp','tests/GroundDriveMovingResidentVectors.hpp','src/sim/UnitAdmission.hpp','src/sim/UnitAdmission.cpp','src/sim/MovingUnitAdmission.hpp','src/sim/MovingUnitAdmission.cpp',
 'src/sim/UnitNextCell.hpp','src/sim/UnitNextCell.cpp','src/sim/Targeting.hpp')))
FIELDS=('track','index','acc','driving','speed','tick','steps','suppress','marked','mark_effect','hx','hy','hz','x','y','z','level','ramp','pattern','resident','mode')
DEFAULT=[-1,0,0,0,15,100,128,0,1,1,51*256+128,72*256+128,999,50*256+128,72*256+128,23,4,0,1,1,0]
def command(planes=None,percentage=1.,land_speed=1.,uphill=1.,downhill=1.2,heading=16384,rot=5,initial_ramp=0,dest=1,route=(2,2,2),**kwargs):
 v=DEFAULT.copy()
 for key,n in kwargs.items():v[FIELDS.index(key)]=n
 numeric=[struct.unpack('<Q',struct.pack('<d',n))[0] for n in (percentage,land_speed,uphill,downhill)]
 return 'P '+' '.join(map(str,[*v,heading,rot,initial_ramp,dest,*route,*([-1]*(24-len(route))),*numeric,*([0]*100 if planes is None else planes)]))
def parse(cmd):
 p=cmd.split();assert len(p)==154 and p[0]=='P';v=list(map(int,p[1:22]));extra=list(map(int,p[22:26]));route=list(map(int,p[26:50]));bits=list(map(int,p[50:54]));planes=list(map(int,p[54:]))
 assert all(-2147483648<=n<=2147483647 for n in v)
 track,index,acc,driving,speed,tick,steps,suppress,marked,effect,hx,hy,hz,x,y,z,level,ramp,pattern,resident,mode=v
 assert -1<=track<64 and 0<=index<128 and driving in (0,1) and 0<=speed<=255 and 1<=steps<=256
 assert suppress==0 and marked in range(256) and effect in (0,1) and -126<=level<=125 and ramp in range(21)
 assert pattern in (0,1) and resident in (0,1) and mode in range(4)
 heading,rot,initial,dest=extra;assert 0<=heading<=65535 and 1<=rot<=127 and initial in range(21) and dest in (0,1)
 assert route[-1]==-1 and all(d in range(8) or d==-1 for d in route)
 end=False
 for d in route:
  if d==-1:end=True
  else:assert not end
 assert all(0<=n<1<<64 for n in [*bits,*planes])
 numeric=[struct.unpack('<d',struct.pack('<Q',n))[0] for n in bits]
 assert all(math.isfinite(n) for n in numeric) and all(math.isfinite(struct.unpack('<d',struct.pack('<Q',n))[0]) for n in planes)
 return v,extra,route,numeric,planes
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'owned_rules':{str(a.rules.resolve()):hash_file(a.rules)},'render_data':hash_file(a.render_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Ground Process engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Ground Process source/input identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Ground Process counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed ground Process command') from None
def generate(a):
 from original_ground_drive_process import GroundDriveProcessOracle
 o=GroundDriveProcessOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 rules=configparser.ConfigParser(strict=False,interpolation=None,allow_no_value=True,inline_comment_prefixes=(';',));rules.read(a.rules,encoding='latin1')
 if rules.get('HTNK','Accelerates',fallback=None)!='false' or rules.get('HTNK','IsTrain',fallback=None) is not None or rules.getboolean('HTNK','Passive',fallback=False):raise ValueError('Owned ordinary Rhino inputs changed')
 commands=[];expected=[];labels=[]
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);cmd=command(planes,**kwargs)
  commands.append(cmd);expected.append(o.run(*parse(cmd)));labels.append(label)
 for first,second in itertools.product(range(8),repeat=2):
  add('all_queued_pairs_complete_Process_preparation_and_Advance',route=(first,second,second),heading=first<<13,ramp=first+second,steps=128)
 for ramp,d in itertools.product(range(21),(0,2,4,6)):
  add('all_ramps_and_stored_pre_movement_observation',route=(d,d,d),heading=(d*8192+20000)%65536,ramp=ramp,pattern=0,steps=160,initial_ramp=(ramp+1)%21)
 for land,up,down in itertools.product((0.,0.5,1.,1.5),(0.7,1.),(1.,1.2)):
  add('supplied_float_land_speed_and_binary64_floor_slope_factors',land_speed=land,uphill=up,downhill=down,route=(6,6,6),heading=49152,steps=128)
 for route in ((0,2,4,6,0,2),(2,3,4,5,6,7),(7,6,5,4,3,2),(),(1,1,0,7,6,6)):
  for effect in (0,1):add('mixed_route_queue_tail_and_turn_completion',route=route,heading=0,mark_effect=effect,steps=256)
 for mode in range(4):
  for tick in (100,-1,2147483640):add('signed_tick_wrap_and_four_incoming_native_FP_modes',tick=tick,mode=mode,steps=128,route=(2,3,4,4))
 for marked,resident in itertools.product((0,1,255),(0,1)):
  add('shared_fallback_identity_and_nonzero_marked_bytes',marked=marked,resident=resident,steps=128,route=(2,2),heading=16384)
 for dest in (0,1):add('empty_queue_no_pathfinding_and_stationary',dest=dest,route=(),steps=4)
 return commands,expected,labels,{'audited_complete_Process_roots':o.roots,'actual_entries':o.entries,'actual_selected_actor_stores':o.stores,
  'supplied_Mark_calls':o.marks,'initial_map_type_actor_and_admission_occupation_mission_pathfinder_supplied':True,
  'prepared_map_body_world_runtime_startup_and_frames_unverified':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets/rules.ini')
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-drive-process-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-drive-process-v2');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh ground Process destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.exe),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:
  index=len(proc.stdout.splitlines());raise RuntimeError(f'Native ground Process at command {index}: {proc.stderr.strip()}; {commands[min(index,len(commands)-1)]}')
 actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Ground Process result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'Ground Process {i} {labels[i]} token {j}: {x[max(0,j-12):j+16]} != {y[max(0,j-12):j+16]}; counts {len(x)}/{len(y)}; {commands[i]}')
 safety=['','P 0',command(track=64),command(index=128),command(acc=-2147483649),command(marked=256),command(speed=256),command(resident=2),command(ramp=21),command(steps=0),command(mode=4),command(percentage=float('nan')),command(route=(2,-1,2)),command(rot=0),command()+' trailing']
 for cmd in safety:
  r=subprocess.run([str(a.native),str(a.exe),str(a.render_data)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Native ground Process refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Ground Process run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} ground Process sequences / {result["audited_complete_Process_roots"]:,} complete calls: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
