#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential complete Drive/base shadow pose and ordered key decisions."""
import argparse,itertools,json,math,random,struct,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_ramp_geometry import SOURCES as GEOMETRY_SOURCES
from verify_drive_shadow_pose import verify
SOURCES=tuple(dict.fromkeys((*GEOMETRY_SOURCES,
 'src/render/DriveShadowPose.hpp','src/render/DriveShadowPose.cpp','src/sim/Facing.hpp',
 'src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp','src/assets/MapFloorHeight.hpp',
 'src/assets/MapCellInputs.hpp','tests/drive_shadow_pose_vectors.cpp',
 'tests/original_drive_shadow_pose.py','tests/compare_drive_shadow_pose.py','tools/verify_drive_shadow_pose.py')))
FIELDS=('kind','x','y','z','resident','ramp','desired','start','fstart','fduration','rate','tick',
 'sstart','sremain','sduration','rx','ry','present','key','mode')
DEFAULT=[1,51*256+128,72*256+128,416,1,0,0,0,-1,0,0,0,-1,0,0,0,0,1,0,0]
def fbits(v):return struct.unpack('<I',struct.pack('<f',v))[0]
def fnumber(v):return struct.unpack('<f',struct.pack('<I',v))[0]
def command(**kwargs):
 v=DEFAULT.copy()
 for key,value in kwargs.items():v[FIELDS.index(key)]=value
 return 'D '+' '.join(map(str,v))
def parse(cmd):
 v=cmd.split();assert len(v)==21 and v[0]=='D';v=list(map(int,v[1:]))
 for i,n in enumerate(v):
  if i in (0,4,17):assert n in (0,1)
  elif i==5:assert n in range(21)
  elif i in (6,7,10):assert 0<=n<=65535
  elif i in (15,16):assert 0<=n<1<<32 and math.isfinite(fnumber(n))
  elif i==19:assert n in range(4)
  else:assert -2147483648<=n<=2147483647
 return v
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'prepared_inputs':{kind:hash_file(getattr(a,kind+'_data')) for kind in ('geometry','render','raster','direction')}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Drive shadow engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Drive shadow identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Drive shadow counts differ')
 for c in e['commands']:
  try:parse(c)
  except (AssertionError,ValueError,IndexError,OverflowError,struct.error):raise ValueError('Malformed Drive shadow command') from None
def generate(a):
 from original_drive_shadow_pose import DriveShadowPoseOracle
 o=DriveShadowPoseOracle(a.exe);commands=[];expected=[];labels=[];rng=random.Random(0x53d0d0)
 def add(label,**kwargs):
  kwargs.setdefault('mode',len(commands)%4);cmd=command(**kwargs);v=parse(cmd)
  commands.append(cmd);expected.append(o.pose(v));labels.append(label)
 keys=(-1,0,1,1023,2147483647,-2147483648,-2147483647)
 for ramp,heading,kind in itertools.product(range(21),range(32),(0,1)):
  i=len(commands);add('all_initialized_ramps_and_heading_bins_base_and_Drive',kind=kind,ramp=ramp,
   desired=heading*2048,key=keys[(ramp+heading)%len(keys)],present=int(i%11!=0),resident=int(i%13!=0))
 for heading,delta,kind in itertools.product(range(32),(-1,0,511,512,513,1023,1024,1535,1536,1537),(0,1)):
  add('heading_bin_boundaries_and_wrapped_keys',kind=kind,ramp=heading%21,
   desired=(heading*2048+delta)&65535,key=keys[(heading+delta)%len(keys)])
 for sstart,sremain,sduration,tick in itertools.product((-1,0,5,-2147483648,2147483647),
   (-2147483648,-1,0,1,3,2147483647),(-2147483648,-1,0,1,3,2147483647),(-3,0,1,5,7,-2147483648,2147483647)):
  add('signed_compare_subtract_wrapped_slope_timer',ramp=len(commands)%21,
   sstart=sstart,sremain=sremain,sduration=sduration,tick=tick,key=keys[len(commands)%7],present=int(len(commands)%9!=0))
 near=fbits(.005);rock=[0,fbits(-0.),near-1,near,near+1,fbits(-fnumber(near-1)),
  fbits(-fnumber(near)),fbits(-fnumber(near+1)),fbits(1e6),fbits(-1e6)]
 for rx,ry,kind in itertools.product(rock,rock,(0,1)):
  add('finite_rocking_threshold_both_components_base_vs_wrapper',kind=kind,ramp=len(commands)%21,
   rx=rx,ry=ry,key=keys[len(commands)%7],present=int(len(commands)%7!=0))
 for _ in range(384):
  add('actual_dynamic_Facing_and_optional_keys',kind=rng.randrange(2),ramp=rng.randrange(21),
   desired=rng.randrange(65536),start=rng.randrange(65536),fstart=rng.choice((-1,0,5,2147483647)),
   fduration=rng.choice((-3,0,1,8,128,2147483647)),rate=rng.choice((0,1,256,127*256,32768,65535)),
   tick=rng.choice((-2147483648,-1,0,1,7,129,2147483647)),key=rng.randint(-2147483648,2147483647),present=rng.randrange(2))
 coords=[(-2147483648,2147483647),(2147483647,-2147483648),(-257,256),(-256,256),(-255,-1),
  (-1,-1),(0,0),(255,255),(256,256),(131072,-256),(-131072,256),(16777216,0),(0,16777216)]
 for (x,y),resident,kind in itertools.product(coords,(0,1),(0,1)):
  add('actual_full_coordinate_map_lookup_and_shared_fallback',x=x,y=y,z=rng.randint(-2147483648,2147483647),
   resident=resident,kind=kind,ramp=len(commands)%21,key=keys[len(commands)%7])
 for mode in range(4):
  for ramp in (0,1,5,13,17,20):add('same_stock_pose_four_incoming_FP_modes',mode=mode,ramp=ramp,desired=1537,key=-2147483648)
 return commands,expected,labels,{'original_pose_calls':o.pose_calls,'audited_original_calls':o.audit_calls,
  'actual_entries':o.entries,'key_writes':o.key_writes,'fallback_stores':o.fallback_stores,
  'actual_numeric_chain_pairs':1,'actor_map_and_timer_storage_supplied':True,
  'Unit_caller_height_placement_runtime_and_frame_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/drive-shadow-pose-vectors')
 for kind,filename in (('geometry','ramp-geometry-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('direction','direction-data.bin')):
  p.add_argument('--'+kind+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/filename)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/drive-shadow-pose-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Drive shadow destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 args=[str(a.native),*[str(getattr(a,kind+'_data')) for kind in ('geometry','render','raster','direction')]]
 now=time.monotonic();proc=subprocess.run(args,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native Drive shadow: '+proc.stderr.strip())
 actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Drive shadow result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Drive shadow {i} {commands[i]}: native {x}, original {y}')
 safety=['','D 0',command(ramp=21),command(present=2),command(mode=4),command(x=2147483648),
  command(rx=fbits(float('nan'))),command(ry=fbits(float('inf'))),command()+' trailing']
 for cmd in safety:
  refused=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if refused.returncode==0 or not refused.stderr.strip():raise AssertionError('Native Drive shadow safety refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Drive shadow run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} complete Drive/base shadow results: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
