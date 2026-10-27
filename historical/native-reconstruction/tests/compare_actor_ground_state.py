#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential actor floor-height writes and stored Drive ramp association."""
import argparse,itertools,json,math,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_map_floor_height import SOURCES as FLOOR_SOURCES,number
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_actor_ground_state import verify
SOURCES=tuple(dict.fromkeys((*FLOOR_SOURCES,'src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp',
 'src/sim/ActorGroundState.hpp','src/sim/ActorGroundState.cpp','tests/actor_ground_state_vectors.cpp',
 'tests/original_actor_ground_state.py','tests/compare_actor_ground_state.py','tools/verify_actor_ground_state.py')))
FIELDS=('op','tick','height','bridge','marked','bridgeHeight','x','y','z','resident','level','ramp',
 'flevel','framp','current','previous','start','padding','remaining','duration','temporary','mutation','mode')
DEFAULT=[0,100,0,0,0,416,51*256+128,72*256+128,17,1,4,0,2,0,0,7,-1,123,91,19,456,0,0]
def command(planes=None,**kwargs):
 v=DEFAULT.copy()
 for k,n in kwargs.items():v[FIELDS.index(k)]=n
 return 'G '+' '.join(map(str,[*v,*([0]*100 if planes is None else planes)]))
def parse(cmd):
 p=cmd.split();assert p[0]=='G' and len(p)==124;v=list(map(int,p[1:24]));planes=list(map(int,p[24:]))
 assert all(-2147483648<=n<=2147483647 for n in v)
 op,tick,height,bridge,marked,bh,x,y,z,resident,level,ramp,fl,fr,current,previous,start,padding,remaining,duration,temporary,mutation,mode=v
 assert op in range(6) and 0<=bridge<=255 and 0<=marked<=255 and resident in (0,1)
 assert -128<=level<=127 and -128<=fl<=127 and ramp in range(256) and fr in range(256)
 assert op not in (0,4,5) or (ramp<=20 and fr<=20)
 assert mutation in range(8) and mode in range(4)
 assert all(0<=n<1<<64 and math.isfinite(number(n)) for n in planes)
 return v,planes
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Ground state engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Ground state source/inspection identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Ground state counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed ground state command') from None

def generate(a):
 from original_actor_ground_state import ActorGroundStateOracle
 o=ActorGroundStateOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];groups={};rng=random.Random(0x4a061a)
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);cmd=command(planes,**kwargs);v,t=parse(cmd)
  commands.append(cmd);expected.append(o.run_ground(v,t));labels.append(label);groups[label]=groups.get(label,0)+1
 for op,ramp,level in itertools.product((0,2,3,4,5),range(21),(-1,0,4)):
  add('all_current_ramps_floor_height_and_stored_ramp_paths',op=op,ramp=ramp,level=level,current=(ramp+1)%21)
 for bridge,marked,height,op in itertools.product((0,1,2,128,255),(0,1,2,128,255),(-2147483648,-417,-1,0,1,417,2147483647),(0,4,5)):
  add('byte_gates_and_wrapped_height_addition',op=op,bridge=bridge,marked=marked,height=height,
   bridgeHeight=rng.choice((-2147483648,-416,0,416,2147483647)),ramp=len(commands)%21)
 for ramp,current,tick in itertools.product(range(21),(0,7,20,255,-1),(-2147483648,-1,0,2147483647)):
  add('changed_ramp_vs_unchanged_timer_and_signed_ticks',op=3,ramp=ramp,current=current,tick=tick,
   previous=rng.randint(-2147483648,2147483647),start=rng.randint(-2147483648,2147483647),
   remaining=rng.randint(-2147483648,2147483647),duration=rng.randint(-2147483648,2147483647),
   padding=rng.randint(-2147483648,2147483647),temporary=rng.randint(-2147483648,2147483647))
 for ramp,tick,padding in itertools.product((-2147483648,-1,0,1,20,255,2147483647),(-2147483648,-1,0,2147483647),(-2147483648,-1,0,2147483647)):
  add('Force_New_Slope_full_signed_input_and_explicit_temporary_padding',op=1,height=ramp,tick=tick,temporary=padding)
 for op,mutation,marked,bridge in itertools.product((0,2,3,4,5),range(8),(0,255),(0,255)):
  add('supplied_Mark_and_between_lookup_mutation_order',op=op,mutation=mutation,marked=marked,bridge=bridge,ramp=7,framp=13)
 coords=[(-2147483648,2147483647),(2147483647,-2147483648),(-257,256),(-256,256),(-255,-1),(-1,-1),
  (0,0),(255,255),(256,256),(131072,-256),(-131072,256),(16777216,0),(0,16777216),(51*256+128,72*256+128)]
 for (x,y),resident,op in itertools.product(coords,(0,1),(0,2,3,4,5)):
  add('actual_signed_map_alias_and_fallback_then_height_or_ramp',op=op,x=x,y=y,resident=resident,
   ramp=rng.randrange(21),framp=rng.randrange(21),z=rng.randint(-2147483648,2147483647))
 for mode,op in itertools.product(range(4),range(6)):
  add('identical_state_under_four_incoming_FP_modes',mode=mode,op=op,ramp=13,marked=1,bridge=1,mutation=3)
 return commands,expected,labels,{'groups':groups,'audited_complete_roots':o.audit_calls,'audited_Process_prefixes':o.prefixes,
  'actual_entries':o.entries,'actual_map_lookups':o.map_calls,'actual_floor_queries':o.height_calls,'actual_scalar_stores':o.scalar_writes,
  'supplied_service_scalar_stores':o.supplied_writes,'Process_suffix_and_actual_Mark_supplied_or_excluded':True,
  'temporary_timer_padding_supplied_not_original_initialization':True,'placement_movement_body_pose_runtime_and_frames_unverified':True}

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/actor-ground-state-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/actor-ground-state-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh ground state destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native ground state: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Ground state result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Ground state {i} {labels[i]}: {x} != {y}; {commands[i]}')
 safety=['','G 0',command(op=6),command(bridge=256),command(marked=-1),command(resident=2),command(op=0,ramp=21),command(framp=256),command(mutation=8),command(mode=4),command(x=2147483648),command()+' trailing']
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Native ground state refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Ground state run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} actor ground-height/ramp state results: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
