#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete committed ordinary Drive Advance with actual floor children."""
import argparse,configparser,itertools,json,math,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_ground_movement_placement import SOURCES as PLACEMENT_SOURCES
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_drive_advance import verify
SOURCES=tuple(dict.fromkeys((*PLACEMENT_SOURCES,'src/sim/GroundDriveAdvance.hpp','src/sim/GroundDriveAdvanceResult.hpp','src/sim/GroundDriveAdvance.cpp',
 'tests/ground_drive_advance_vectors.cpp','tests/original_ground_drive_advance.py','tests/compare_ground_drive_advance.py',
 'tools/verify_ground_drive_advance.py','tests/original_movement.py','tests/movement_profiles.py','src/sim/Drive.cpp',
 'src/assets/MovementData.hpp','src/assets/MovementData.cpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp',
 'src/assets/Bytes.hpp','src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp',
 'src/assets/MapCellChildren.hpp','src/assets/MapCellChildren.cpp')))
FIELDS=('track','index','acc','driving','speed','tick','steps','suppress','marked','mark_effect','hx','hy','hz','x','y','z','level','ramp','pattern','resident','mode')
DEFAULT=[18,0,0,1,15,100,40,0,1,1,51*256+128,72*256+128,999,50*256+128,72*256+128,23,4,0,1,1,0]
def command(planes=None,percentage=1.,**kwargs):
 v=DEFAULT.copy()
 for key,n in kwargs.items():v[FIELDS.index(key)]=n
 bits=struct.unpack('<Q',struct.pack('<d',percentage))[0]
 return 'A '+' '.join(map(str,[*v,bits,*([0]*100 if planes is None else planes)]))
def parse(cmd):
 p=cmd.split();assert len(p)==123 and p[0]=='A';v=list(map(int,p[1:22]));bits=int(p[22]);planes=list(map(int,p[23:]))
 assert all(-2147483648<=n<=2147483647 for n in v)
 track,index,acc,driving,speed,tick,steps,suppress,marked,effect,hx,hy,hz,x,y,z,level,ramp,pattern,resident,mode=v
 assert -1<=track<64 and 0<=index<128 and driving in (0,1) and 0<=speed<=255 and 1<=steps<=64
 assert suppress in (0,1) and marked in range(256) and effect in (0,1) and -126<=level<=125 and ramp in range(21)
 assert pattern in (0,1) and resident in (0,1) and mode in range(4) and 0<=bits<1<<64
 percentage=struct.unpack('<d',struct.pack('<Q',bits))[0];assert math.isfinite(percentage)
 assert all(0<=n<1<<64 and math.isfinite(struct.unpack('<d',struct.pack('<Q',n))[0]) for n in planes)
 return v,percentage,planes
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'owned_rules':{str(a.rules.resolve()):hash_file(a.rules)}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Ground Advance engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Ground Advance source/input identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Ground Advance counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed ground Advance command') from None
def generate(a,oracle_type=None):
 if oracle_type is None:
  from original_ground_drive_advance import GroundDriveAdvanceOracle
  oracle_type=GroundDriveAdvanceOracle
 o=oracle_type(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 rules=configparser.ConfigParser(strict=False,interpolation=None,allow_no_value=True,inline_comment_prefixes=(';',));rules.read(a.rules,encoding='latin1')
 if rules.get('HTNK','Accelerates',fallback=None)!='false':raise ValueError('Selected owned Rhino Accelerates input changed')
 if rules.get('HTNK','IsTrain',fallback=None) is not None:raise ValueError('Selected owned Rhino IsTrain absence changed')
 commands=[];expected=[];labels=[];rng=random.Random(0x4a1000)
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);cmd=command(planes,**kwargs);v,percentage,t=parse(cmd)
  commands.append(cmd);expected.append(o.run(v,percentage,t));labels.append(label)
 valid=[j for j in range(64) if p.get_data(0x7a0180+12*j-0x400000,1)!=b'\0']
 for track,level in itertools.product(valid,(-7,-1,0,4)):
  add('all_ordinary_transforms_complete_sequences_on_shared_nonflat_cells',track=track,level=level,ramp=track%21,steps=48,marked=(0,1,255)[track%3],mark_effect=track%2)
 for ramp,d in itertools.product(range(21),(0,2,4,6)):
  dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[d]
  add('all_ramps_committed_floor_then_residual_location',track=d*9,ramp=ramp,x=DEFAULT[10]-dx*256,y=DEFAULT[11]-dy*256,pattern=0,steps=32)
 for acc,suppress,percentage in itertools.product(range(9),(0,1),(-1.,0.,0.5,1.,1.5)):
  add('strict_seven_boundary_float_fraction_and_suppression',acc=acc,suppress=suppress,percentage=percentage,steps=1,speed=0 if acc<=7 else 15)
 for n in range(100):
  track=rng.choice(valid);add('corner_identity_arbitration_with_repeated_fallback_queries',track=track,acc=rng.randrange(8),speed=0,steps=1,
   x=DEFAULT[10]+rng.randrange(-700,701),y=DEFAULT[11]+rng.randrange(-700,701),z=rng.randrange(-500,1000),resident=n%2,mark_effect=(n//2)%2)
 for coord,mode in itertools.product(((-257,-1),(-1,255),(0,0),(131072,-256),(16777216,0),(2147483647,-2147483648)),range(4)):
  x,y=coord;add('signed_wrapping_world_coordinate_and_word_cell_boundaries',hx=x,hy=y,x=x,y=y,steps=1,speed=15,ramp=13,mode=mode)
 for track,driving in itertools.product((-1,18),(0,1)):
  add('inactive_root_clears_accumulator_without_height_or_location',track=track,driving=driving,acc=7,steps=1)
 for acc in (-2147483648,-256,-1,7,8,65536,2147483640,2147483647):
  add('full_signed_accumulator_and_wrapped_speed_addition',acc=acc,steps=1,speed=15)
 for track in valid:
  raw=p.get_data(0x7a0180+12*track-0x400000,1)[0]
  stream=struct.unpack('<I',p.get_data(0x7a00a0+16*raw-0x400000,4))[0]
  for index in range(128):
   if index and p.get_data(stream+12*index-0x400000,8)==bytes(8):break
  add('terminator_location_height_credit_and_notification',track=track,index=index,steps=2,acc=8,suppress=1,ramp=13)
 for mode in range(4):add('identical_nonflat_sequence_four_incoming_FP_modes',mode=mode,track=18,ramp=13,steps=48)
 return commands,expected,labels,{'audited_complete_Advance_roots':o.roots,'actual_entries':o.entries,
  'actual_selected_actor_stores':o.stores,'supplied_Mark_calls':o.marks,'owned_HTNK_Accelerates':'false','owned_HTNK_IsTrain_absent':True,
  'Accelerates_default_and_INI_association_inspected_not_executed':True,
  'initial_track_map_type_actor_and_Mark_occupation_notification_services_supplied':True,
  'preparation_Process_body_world_runtime_startup_and_frames_unverified':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets/rules.ini')
 p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-drive-advance-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-drive-advance-v2');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh ground Advance destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.exe)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:
  index=len(proc.stdout.splitlines());raise RuntimeError(f'Native ground Advance at command {index}: {proc.stderr.strip()}; {commands[min(index,len(commands)-1)]}')
 actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Ground Advance result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'Ground Advance {i} {labels[i]} token {j}: {x[max(0,j-12):j+16]} != {y[max(0,j-12):j+16]}; counts {len(x)}/{len(y)}; {commands[i]}')
 safety=['','A 0',command(track=64),command(index=128),command(acc=-2147483649),command(marked=256),command(speed=256),command(resident=2),command(ramp=21),command(steps=0),command(mode=4),command(percentage=float('nan')),command()+' trailing']
 for cmd in safety:
  r=subprocess.run([str(a.native),str(a.exe)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Native ground Advance refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Ground Advance run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} ground Advance sequences / {result["audited_complete_Advance_roots"]:,} complete calls: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
