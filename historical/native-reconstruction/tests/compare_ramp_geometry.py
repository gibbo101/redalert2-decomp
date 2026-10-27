#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Stock ramp/Cell numeric initialization, original table leaves and shadow matrices."""
import argparse,json,math,struct,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_voxel_ramp_shadow import SOURCES as SHADOW_SOURCES
from verify_ramp_geometry import verify
SOURCES=tuple(dict.fromkeys((*SHADOW_SOURCES,
 'src/assets/RampGeometryData.hpp','src/assets/RampGeometryData.cpp',
 'src/assets/RenderData.hpp','src/assets/RenderData.cpp','src/assets/MovementData.hpp','src/assets/MovementData.cpp',
 'src/sim/Targeting.hpp','src/sim/Targeting.cpp','src/render/Lighting.hpp','src/render/Lighting.cpp',
 'src/render/RampGeometry.hpp','src/render/RampGeometry.cpp','tests/ramp_geometry_vectors.cpp',
 'tests/compare_ramp_geometry.py','tests/original_ramp_geometry.py','tools/verify_ramp_geometry.py',
 'tools/prepare_ramp_geometry_data.py','tools/prepared_data_profiles.py')))
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def number(v):return struct.unpack('<d',struct.pack('<Q',v))[0]
def parse(cmd):
 v=cmd.split();assert v and v[0] in ('S','T','A')
 assert len(v)==(2 if v[0]=='S' else 3) and int(v[-1]) in range(4)
 if v[0]!='S':
  n=int(v[1]);assert 0<=n<1<<64 and math.isfinite(number(n)) and abs(number(n))<=1e6
 return v
def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'prepared_inputs':{kind:hash_file(getattr(a,kind+'_data')) for kind in ('geometry','render','raster','direction')}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Geometry engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Geometry identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Geometry counts differ')
 for c in e['commands']:
  try:parse(c)
  except (AssertionError,ValueError,IndexError,OverflowError,struct.error):raise ValueError('Malformed geometry command') from None
def generate(a):
 from original_ramp_geometry import RampGeometryOracle
 o=RampGeometryOracle(a.exe);commands=[];expected=[];labels=[];stock=leaves=0
 def add(cmd,result,label):
  parse(cmd);commands.append(cmd);expected.append(result);labels.append(label)
 for seed in range(4):
  result=o.stock(seed);stock+=1
  for mode in range(4):add(f'S {mode}',result,'two_distinct_stock_numeric_chains_and_21_shadow_matrices')
 tangentScale=struct.unpack_from('<d',a.geometry_data.read_bytes(),16424)[0]
 slopeStep=struct.unpack_from('<f',a.direction_data.read_bytes(),40+4097*4)[0]
 for kind,count,scale in (('T',4096,1/tangentScale),('A',4097,slopeStep)):
  values=[sign*((i+.375)*scale) for i in range(count) for sign in (1,-1)]
  for i,value in enumerate(values):
   result=o.leaf(kind,value);leaves+=1
   add(f'{kind} {bits(value)} {i%4}',result,'all_table_bins_both_signs_with_native_FP_restoration')
  edges=[0.,-0.,math.nextafter(0.,-1.),math.nextafter(0.,1.),2**-149,-2**-149,2**-150,-2**-150,1e6,-1e6]
  for i in (1,2,16,128,1024,2048,4095,4096,4097):
   value=i*scale
   edges.extend(sign*x for x in (math.nextafter(value,0),value,math.nextafter(value,math.inf)) for sign in (1,-1))
  # Includes signed zero, stored-float underflow, truncation/remainder boundaries,
  # arctangent saturation and the finite safety profile's endpoints.
  for value in edges:
   result=o.leaf(kind,value);leaves+=1
   for mode in range(4):add(f'{kind} {bits(value)} {mode}',result,'table_leaf_boundaries_four_native_FP_modes')
 return commands,expected,labels,{'original_stock_chain_pairs':stock,'original_leaf_calls':leaves,
  'audited_original_calls':o.audit_calls,'actual_entries':o.entries,'numeric_global_stores':o.global_stores,
  'shadow_matrix_dword_stores':o.matrix_stores,'original_entry_FP':'53-bit_toward_zero',
  'original_CRT_flag_supplied':0,'original_leaf_return_observation':'x87_physical_register_read_then_harness_consumption',
  'startup_order_general_pow_Drive_and_runtime_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/ramp-geometry-vectors')
 for kind,filename in (('geometry','ramp-geometry-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('direction','direction-data.bin')):
  p.add_argument('--'+kind+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/filename)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ramp-geometry-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh geometry destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 args=[str(a.native),*[str(getattr(a,kind+'_data')) for kind in ('geometry','render','raster','direction')]]
 now=time.monotonic();proc=subprocess.run(args,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native geometry: '+proc.stderr.strip())
 actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Geometry result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Geometry {i} {commands[i]}: {[(n,xx,yy) for n,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:12]}')
 safety=[f'{kind} {bits(value)} 0' for kind in ('T','A') for value in (float('nan'),float('inf'),1e6+1,-1e6-1)]+['','S','S 4','S 0 trailing','T 0','A 0 0 trailing','X 0']
 for cmd in safety:
  refused=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if refused.returncode==0 or not refused.stderr.strip():raise AssertionError('Native geometry safety refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Geometry run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} native geometry results: PASS ({result["evidence_mode"]}; {result["original_stock_chain_pairs"]} stock chain pairs, {result["original_leaf_calls"]} original leaf calls)')
if __name__=='__main__':main()
