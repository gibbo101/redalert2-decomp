#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the production owned-map Unit binding with isolated original routines.

This reuses the exact membership profile and oracle. Supplied initial records,
routes, admission and mission boundaries retain that profile's scope. Native
Simulation copying/commands and SDL are covered separately, not by this oracle.
"""
import json,subprocess,time
import compare_membership_drive as member
from compare_membership_drive import parse,generate,native_args,validate
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,check_replay_destination
from compare_terrain_visibility import ROOT
SOURCES=('src/assets/MutableUnitMap.hpp','src/assets/MutableUnitMap.cpp',
 'src/platform/TerrainUnitContext.hpp','src/platform/TerrainUnitContext.cpp',
 'src/sim/GroundDriveContext.hpp','src/sim/Simulation.hpp','src/sim/Simulation.cpp',
 'tests/runtime_membership_vectors.cpp','tests/compare_runtime_membership.py',
 'src/assets/PreparedUnitAdmission.hpp','src/assets/PreparedUnitAdmission.cpp',
 'src/assets/TileImagePreparation.hpp','src/assets/TileVariants.hpp','src/sim/OriginalRandom.hpp')
def identities(a):
 return {'membership':member.identities(a),'production_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def arguments():
 a=member.arguments()
 if a.native==ROOT/'build/native/membership-drive-vectors':a.native=ROOT/'build/native/runtime-membership-vectors'
 if a.output==ROOT/'private/map-depth-1006/membership-drive-v1':a.output=ROOT/'private/map-depth-1006/runtime-membership-v1'
 return a
def main():
 a=arguments();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh runtime membership destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run(native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native runtime membership command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Runtime membership result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-10):j+16]} != {y[max(0,j-10):j+16]}; counts {len(x)}/{len(y)}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Runtime membership run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} runtime membership sequences / {metadata["movement_ticks"]:,} movement ticks: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
