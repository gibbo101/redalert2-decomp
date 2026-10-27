#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential complete Drive body pose with stored ramp transitions and rocking."""
import argparse,itertools,json,math,random,struct,subprocess,tempfile,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_ramp_geometry import SOURCES as GEOMETRY_SOURCES
from compare_actor_ground_state import SOURCES as STATE_SOURCES
from verify_drive_body_pose import verify
SOURCES=tuple(dict.fromkeys((*GEOMETRY_SOURCES,*STATE_SOURCES,
 'src/render/DriveBodyPose.hpp','src/render/DriveBodyPose.cpp',
 'src/render/DriveShadowPose.hpp','src/sim/Facing.hpp',
 'src/assets/RampPoseData.hpp','src/assets/RampPoseData.cpp','tools/prepare_ramp_pose_data.py',
 'tests/drive_body_pose_vectors.cpp','tests/original_drive_body_pose.py',
 'tests/compare_drive_body_pose.py','tools/verify_drive_body_pose.py')))
FIELDS=('op','nextRamp','current','previous','start','remaining','duration','tick','rx','ry','dx','dy',
 'desired','from_','fstart','fduration','rate','present','key','mode')
def fbits(v):return struct.unpack('<I',struct.pack('<f',v))[0]
def dbits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def number(n,fmt):return struct.unpack('<'+fmt,struct.pack('<'+('I' if fmt=='f' else 'Q'),n))[0]
DEFAULT=[0,0,0,0,-1,0,0,0,0,0,dbits(30.5),dbits(24.25),0,0,-1,0,0,1,0,0]
def command(**kwargs):
 v=DEFAULT.copy()
 for key,value in kwargs.items():v[FIELDS.index(key)]=value
 return 'B '+' '.join(map(str,v))
def parse(cmd):
 v=cmd.split()
 if v and v[0]=='Q':
  assert len(v)==2 and int(v[1]) in range(4);return ['Q',int(v[1])]
 assert len(v)==21 and v[0]=='B';v=list(map(int,v[1:]))
 for i,n in enumerate(v):
  if i==0:assert n in range(3)
  elif i in (1,2,3):assert n in range(21)
  elif i in (8,9):assert 0<=n<1<<32 and math.isfinite(number(n,'f')) and abs(number(n,'f'))<=1
  elif i in (10,11):assert 0<=n<1<<64 and math.isfinite(number(n,'d')) and abs(number(n,'d'))<=1e6
  elif i in (12,13,16):assert n in range(65536)
  elif i==17:assert n in (0,1)
  elif i==19:assert n in range(4)
  else:assert -2147483648<=n<=2147483647
 return v
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'prepared_inputs':{kind:hash_file(getattr(a,kind+'_data')) for kind in ('geometry','render','raster','direction','pose')}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Drive body engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Drive body identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Drive body counts differ')
 for c in e['commands']:
  try:parse(c)
  except (AssertionError,ValueError,IndexError,OverflowError,struct.error):raise ValueError('Malformed Drive body command') from None
def generate(a):
 from original_drive_body_pose import DriveBodyPoseOracle
 o=DriveBodyPoseOracle(a.exe);commands=[];expected=[];labels=[];rng=random.Random(0x4a0050)
 for mode in range(4):commands.append('Q '+str(mode));expected.append(o.quaternions);labels.append('stock_initialized_21_quaternions_four_incoming_FP_modes')
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);cmd=command(**kwargs)
  commands.append(cmd);labels.append(label);expected.append(o.pose(parse(cmd)))
 keys=(-1,0,1,1023,2147483647,-2147483648,-2147483647)
 for ramp,heading in itertools.product(range(21),range(32)):
  i=len(commands);add('all_settled_ramps_and_heading_bins',current=ramp,previous=(ramp+1)%21,desired=heading*2048,
   key=keys[i%7],present=int(i%11!=0))
 for previous,current,tick in itertools.product(range(21),range(21),range(4)):
  i=len(commands);add('all_stock_ramp_pairs_three_tick_transition',current=current,previous=previous,start=0,remaining=3,duration=3,tick=tick,
   desired=(i*1537)&65535,key=keys[i%7],present=int(i%13!=0))
 for op,ramp,tick in itertools.product((1,2),range(21),(0,1,2,3,4)):
  add('actual_Unlimbo_or_Process_prefix_before_body_pose',op=op,nextRamp=ramp,current=(ramp+7)%21,previous=(ramp+3)%21,
   start=-1,remaining=3,duration=3,tick=tick,desired=(ramp*2048+1537)&65535)
 for ramp,tick in itertools.product(range(21),(-1,0,1,3,4)):
  add('equal_Cell_ramp_keeps_stored_timer_then_body_pose',op=2,nextRamp=ramp,current=ramp,previous=(ramp+9)%21,start=0,remaining=3,duration=3,tick=tick)
 near=fbits(.005);rock=[0,fbits(-0.),near-1,near,near+1,fbits(-number(near,'f')),fbits(-number(near+1,'f')),fbits(.25),fbits(-.5),fbits(1),fbits(-1)]
 for rx,ry in itertools.product(rock,rock):
  i=len(commands);add('rocking_axes_threshold_sign_translation_and_matrix_order',rx=rx,ry=ry,current=i%21,previous=(i+3)%21,
   desired=(i*2048)&65535,key=keys[i%7],present=int(i%9!=0),start=0,remaining=3,duration=3,tick=i%5)
 timers=[(-1,3,3,-2147483648),(-1,-1,3,0),(-1,2147483647,-2147483648,0),
  (2147483647,3,3,-2147483648),(-2147483648,3,3,2147483647),(5,3,3,1),
  (0,-2147483648,-1,0),(0,2147483647,-2147483648,1),(0,3,0,1)]
 for (start,remaining,duration,tick),ramp in itertools.product(timers,(0,1,5,13,20)):
  add('signed_wrapped_timer_and_extrapolation',start=start,remaining=remaining,duration=duration,tick=tick,current=ramp,previous=(ramp+1)%21)
 for _ in range(256):
  add('finite_type_double_narrowing_dynamic_Facing_and_rocking',current=rng.randrange(21),previous=rng.randrange(21),
   rx=fbits(rng.uniform(-1,1)),ry=fbits(rng.uniform(-1,1)),dx=dbits(rng.uniform(-10000,10000)),dy=dbits(rng.uniform(-10000,10000)),
   desired=rng.randrange(65536),from_=rng.randrange(65536),fstart=rng.choice((-1,0,5,2147483647)),
   fduration=rng.choice((-3,0,1,8,128,2147483647)),rate=rng.choice((0,1,256,32768,65535)),
   tick=rng.choice((-2147483648,-1,0,1,7,129,2147483647)),key=rng.randint(-2147483648,2147483647),present=rng.randrange(2))
 for mode,ramp in itertools.product(range(4),(0,1,5,13,17,20)):
  add('identical_transition_rocking_four_incoming_FP_modes',mode=mode,current=ramp,previous=(ramp+1)%21,start=0,remaining=3,duration=3,tick=1,rx=fbits(.1),ry=fbits(-.2))
 return commands,expected,labels,{'original_body_calls':o.body_calls,'audited_original_calls':o.audit_calls,
  'actual_entries':o.entries,'key_writes':o.key_writes,'actual_Process_prefixes':o.prefixes,
  'supplied_timer_padding_writes':o.supplied_padding_writes,'actual_numeric_chain_pairs':1,
  'stock_quaternion_dwords_compared':84,'actual_quaternion_dword_stores':o.quaternion_stores,
  'actor_type_map_Facing_and_initial_timer_state_supplied':True,
  'complete_Process_actor_placement_Unit_drawing_runtime_and_frame_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/drive-body-pose-vectors')
 for kind,filename in (('geometry','ramp-geometry-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('direction','direction-data.bin'),('pose','ramp-pose-data.bin')):
  p.add_argument('--'+kind+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/filename)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/drive-body-pose-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Drive body destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 args=[str(a.native),*[str(getattr(a,kind+'_data')) for kind in ('geometry','render','raster','direction','pose')]]
 now=time.monotonic();proc=subprocess.run(args,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native Drive body: '+proc.stderr.strip())
 actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Drive body result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Drive body {i} {commands[i]}: native {x}, original {y}')
 safety=['','B 0','Q 4','Q 0 trailing',command(current=21),command(present=2),command(mode=4),command(tick=2147483648),
  command(rx=fbits(float('nan'))),command(ry=fbits(float('inf'))),command(rx=fbits(1.1)),command(dx=dbits(float('nan'))),command(dy=dbits(1e7)),
  command(current=1,previous=2,start=-1,remaining=2147483647,duration=1),command()+' trailing']
 for cmd in safety:
  refused=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if refused.returncode==0 or not refused.stderr.strip():raise AssertionError('Native Drive body safety refusal missing')
 with tempfile.TemporaryDirectory(prefix='drive-body-reader-',dir=ROOT/'build') as tmp:
  blob=a.pose_data.read_bytes()
  for kind,changed in (('size',blob[:-1]),('header',bytes([blob[0]^1])+blob[1:]),('table',blob[:-1]+bytes([blob[-1]^1]))):
   path=Path(tmp)/(kind+'.bin');path.write_bytes(changed)
   refused=subprocess.run([*args[:-1],str(path)],input='Q 0\n',text=True,capture_output=True)
   if refused.returncode==0 or not refused.stderr.strip():raise AssertionError('Native RampPose reader accepted changed '+kind)
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Drive body run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'prepared_reader_refusals':3,
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} complete Drive body/quaternion results: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
