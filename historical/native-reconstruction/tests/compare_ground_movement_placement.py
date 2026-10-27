#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential actual location/floor children inside scoped Drive placement."""
import argparse,itertools,json,math,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_actor_ground_state import SOURCES as GROUND_SOURCES
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_movement_placement import verify
SOURCES=tuple(dict.fromkeys((*GROUND_SOURCES,'src/sim/GroundMovementPlacement.hpp','src/sim/GroundMovementPlacement.cpp',
 'tests/ground_movement_placement_vectors.cpp','tests/original_ground_movement_placement.py',
 'tests/compare_ground_movement_placement.py','tools/verify_ground_movement_placement.py')))
FIELDS=('op','onmap','marked','bridge','bh','x','y','z','nx','ny','nz','resident','level','ramp','fl','fr','mutation','mode')
DEFAULT=[1,1,1,0,416,51*256+100,72*256+100,17,51*256+128,72*256+128,23,1,4,0,2,0,1,0]
def command(planes=None,**kwargs):
 v=DEFAULT.copy()
 for k,n in kwargs.items():v[FIELDS.index(k)]=n
 return 'P '+' '.join(map(str,[*v,*([0]*100 if planes is None else planes)]))
def parse(cmd):
 p=cmd.split();assert len(p)==119 and p[0]=='P';v=list(map(int,p[1:19]));planes=list(map(int,p[19:]))
 assert all(-2147483648<=n<=2147483647 for n in v)
 op,onmap,marked,bridge,bh,x,y,z,nx,ny,nz,resident,level,ramp,fl,fr,mutation,mode=v
 assert op in range(3) and all(n in range(256) for n in (onmap,marked,bridge)) and resident in (0,1)
 assert -128<=level<=127 and -128<=fl<=127 and ramp in range(21) and fr in range(21) and mutation in range(16) and mode in range(4)
 assert all(0<=n<1<<64 and math.isfinite(struct.unpack('<d',struct.pack('<Q',n))[0]) for n in planes)
 return v,planes
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Movement placement engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Movement placement source/inspection identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Movement placement counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed movement placement command') from None
def generate(a):
 from original_ground_movement_placement import GroundMovementPlacementOracle
 o=GroundMovementPlacementOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];rng=random.Random(0x4a20b0)
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);cmd=command(planes,**kwargs);v,t=parse(cmd)
  commands.append(cmd);expected.append(o.place(v,t));labels.append(label)
 for op,ramp,level,marked,bridge in itertools.product((1,2),range(21),(-1,0,4),(0,1,255),(0,255)):
  add('all_ramps_levels_marked_and_bridge_bytes_actual_floor_after_location',op=op,ramp=ramp,level=level,marked=marked,bridge=bridge,
   nx=51*256+254 if op==2 else 52*256+1,ny=72*256+200,nz=-123)
 for op,mutation,marked,onmap in itertools.product(range(3),range(16),(0,1,255),(0,255)):
  add('supplied_Mark_flag_coordinate_input_and_post_write_mutation_order',op=op,mutation=mutation,marked=marked,onmap=onmap,
   nx=51*256+200 if op==2 else 52*256+1,ramp=7,fr=13)
 coords=[(-2147483648,2147483647),(2147483647,-2147483648),(-257,-256),(-256,-255),(-255,-1),(-1,0),(0,255),(255,256),
  (256,511),(16777216,0),(0,16777216),(131072,-256),(-131072,256)]
 for (x,nx),resident,marked in itertools.product(coords,(0,1),(0,255)):
  add('signed_division_then_word_Cell_compare_and_full_map_lookup',x=x,nx=nx,y=-1,ny=0,resident=resident,marked=marked,
   z=-2147483648,nz=2147483647,ramp=5,fr=13,bh=2147483647,bridge=255)
 for mode,op in itertools.product(range(4),range(3)):
  add('identical_location_floor_sequence_four_incoming_FP_modes',mode=mode,op=op,ramp=13,marked=255,bridge=255,mutation=15)
 return commands,expected,labels,{'actual_entries':o.entries,'audited_complete_roots':o.audit_calls,'scoped_Advance_blocks':o.blocks,
  'actual_Foot_location_roots':o.location_roots,'actual_floor_queries':o.height_calls,'actual_548000_entries':o.map_calls,
  'actual_scalar_actor_stores':o.actual_stores,'supplied_Mark_calls':o.Mark_calls,
  'candidate_register_stack_Mark_and_initial_map_actor_state_supplied':True,
  'complete_Advance_Process_clearance_body_world_runtime_and_frame_unverified':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/ground-movement-placement-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-movement-placement-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh movement placement destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native movement placement: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Movement placement result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Movement placement {i} {labels[i]}: {x} != {y}; {commands[i]}')
 safety=['','P 0',command(op=3),command(bridge=256),command(marked=-1),command(onmap=256),command(resident=2),command(ramp=21),command(fr=21),command(mutation=16),command(mode=4),command(x=2147483648),command()+' trailing']
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Native movement placement refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Movement placement run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} movement location/floor placement results: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
