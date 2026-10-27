#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential 21-matrix shadow table from the complete original initializer."""
import argparse,json,math,random,struct,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_voxel_ramp_shadow import verify
SOURCES=('src/render/VoxelRampShadow.hpp','src/render/VoxelRampShadow.cpp','src/render/VoxelRaster.hpp','src/render/VoxelRaster.cpp',
 'src/sim/OriginalMath.hpp','src/assets/RasterData.hpp','src/assets/RasterData.cpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp',
 'src/assets/Archive.hpp','src/assets/Archive.cpp','src/assets/Formats.hpp','src/assets/Formats.cpp',
 'tests/voxel_ramp_shadow_vectors.cpp','tests/compare_voxel_ramp_shadow.py','tests/original_voxel_ramp_shadow.py','tests/original_presentation.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py','tools/verify_voxel_ramp_shadow.py')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def number(v):return struct.unpack('<d',struct.pack('<Q',v))[0]
def parse(cmd):
 v=list(map(int,cmd.split()));assert len(v)==3 and all(0<=n<1<<64 for n in v[:2]) and v[2] in range(4)
 assert all(math.isfinite(number(n)) and abs(number(n))<=3 for n in v[:2]);return v

def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'raster_data_sha256':hash_file(a.raster_data)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Ramp shadow engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Ramp shadow identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Ramp shadow counts differ')
 for c in e['commands']:
  try:parse(c)
  except (AssertionError,ValueError,IndexError,OverflowError,struct.error):raise ValueError('Malformed ramp shadow command') from None

def generate(a):
 from original_voxel_ramp_shadow import VoxelRampShadowOracle
 o=VoxelRampShadowOracle(a.exe);commands=[];expected=[];labels=[];rng=random.Random(0x718060)
 pairs=[(0.,0.),(-0.,-0.),(.25,.5),(-.125,.75),(3.,-3.),(-3.,3.)]
 for x in (2**-149,-2**-149,.125-2**-27,.125+2**-27,math.nextafter(.5,0),math.nextafter(.5,1)):
  pairs.append((x,-x))
 pairs.extend((rng.uniform(-3,3),rng.uniform(-3,3)) for _ in range(32))
 for seed,(axis,diagonal) in enumerate(pairs):
  result=o.run(axis,diagonal,seed)
  for mode in range(4):
   cmd=f'{bits(axis)} {bits(diagonal)} {mode}';parse(cmd);commands.append(cmd);expected.append(result)
   labels.append('complete_initializer_21_shadow_matrices_with_supplied_tilts_and_restored_native_FP')
 return commands,expected,labels,{'original_initializers':o.audit_calls,'actual_entries':o.entries,'shadow_table_dword_stores':o.table_stores,
  'native_FP_modes':4,'original_angle_globals_supplied':True,'original_startup_other_outputs_and_runtime_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',required=True,type=Path);p.add_argument('--native',type=Path,default=ROOT/'build/native/voxel-ramp-shadow-vectors')
 p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ramp-shadow-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current);report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh ramp shadow destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native ramp shadow: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Ramp shadow result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Ramp shadow {i}: {[(n,xx,yy) for n,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:12]}')
 safety=[f'{bits(v)} 0 0' for v in (float('nan'),float('inf'),-3.001,3.001)]+['0 0','0 0 4','0 0 0 trailing']
 for cmd in safety:
  refused=subprocess.run([str(a.native),str(a.raster_data)],input=cmd+'\n',text=True,capture_output=True)
  if refused.returncode==0 or not refused.stderr.strip():raise AssertionError('Native ramp shadow safety refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Ramp shadow run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} native ramp-shadow results against {result["original_initializers"]} original initializers: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
