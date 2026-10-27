#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Replay profile-specific original expectations through promoted native data.

Validate original receipts, oracle sources, mapping tools and every recorded
fixture by content. Rebuilt native/exporter binaries are recorded separately;
their identities cannot stand in for fixture content. Replay retained and promoted
inputs without changing old receipts or weakening their original validators.
No originals run.
"""
import argparse,hashlib,json,subprocess,sys,time
from pathlib import Path
from presentation_evidence import private_path,validate_receipt
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from prepared_data_profiles import DISC,PATCHED,default_output
# suite: compare CLI suffix, runner, promoted argument kinds
SUITES={
 'movement':('movement','movement-vectors',('exe',)),
 'curves':('curves','movement-vectors',('exe',)),
 'timing-targeting':('timing_targeting','timing-targeting-vectors',('exe','direction')),
 'presentation':('presentation','presentation-vectors',('render','vpl')),
 'raster':('raster','raster-vectors',('raster','render')),
 'composition':('composition','composition-vectors',('raster','render')),
 'shadow-color':('shadow_color','shadow-color-vectors',('raster',)),
 'staging':('staging','staging-vectors',('raster','render')),
 'map-light':('map_light','map-light-vectors',('render',)),
 'static-light':('static_light','static-light-vectors',('render',)),
 'unit-light':('unit_light','unit-light-vectors',('raster','render')),
 'voxel-cache':('voxel_cache','voxel-cache-vectors',('raster','render')),
 'shadow-keys':('shadow_keys','shadow-key-vectors',('raster','render')),
 'scenery':('scenery','scenery-vectors',('render',)),
 'terrain-types':('terrain_types','scenery-vectors',('render',)),
 'props':('props','scenery-vectors',('render',)),
 'occupation':('occupation','occupation-vectors',()),
 'lifecycle':('lifecycle','lifecycle-vectors',('render','raster'))}
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def validate_evidence(expected,digest,profile,source):
 expected=private_path(expected,source)
 receipt_path=private_path(expected.parent/'report.json',source)
 evidence=json.loads(expected.read_text());receipt=json.loads(receipt_path.read_text())
 validate_receipt(evidence,receipt,sha(expected))
 if receipt.get('original_instructions_executed') is not True:raise ValueError('Original execution receipt missing')
 if any(evidence.get(k)!=v or receipt.get(k)!=v for k,v in (('executable_sha256',digest),('profile',profile))):
  raise ValueError('Original evidence engine/profile differs')
 if receipt.get('native_data_executable_sha256')!=DISC:raise ValueError('Original fixture data profile differs')
 checks={str(expected):sha(expected),str(receipt_path):sha(receipt_path)}
 def add(path,value):
  path=Path(path)
  if sha(path)!=value:raise ValueError('Original source/fixture identity differs: '+str(path))
  checks[str(path)]=value
 groups={'oracle_sources':ROOT/'tests','native_sources':ROOT,'mapping_tools':ROOT/'tools',
         'assets_sha256':expected.parent/'assets','input_sha256':ROOT,'fixture_sha256':ROOT}
 for key,base in groups.items():
  for name,value in receipt.get(key,{}).items():add(base/name,value)
 fixed={'mapping_tool_sha256':ROOT/'tools'/('verify_presentation_mapping.py' if expected.parent.name=='presentation' else 'verify_movement_mapping.py'),
        'vpl_sha256':expected.parent/'voxels.vpl',
        **{k+'_data_sha256':default_output(DISC,k+'-data.bin') for k in ('direction','render','raster')}}
 for key,path in fixed.items():
  if key in receipt:add(path,receipt[key])
 # Exporters supplied bytes to the original fixtures, not original behavior.
 # Their old binary hashes remain in receipt_path; exact fixture bytes above
 # must still match. No original receipt/profile/fixture is relabeled.
 known=set(groups)|set(fixed)|{'executable_sha256','native_data_executable_sha256','native_sha256',
                              'exporter_sha256','staging_exporter_sha256','cell_exporter_sha256'}
 for key in receipt:
  if ('sha256' in key or key.endswith('_sources')) and key not in known and key!='expectations_sha256':
   raise ValueError('Unaccounted original identity field: '+key)
 if not receipt.get('oracle_sources'):raise ValueError('Original sources missing')
 return checks
def main():
 p=argparse.ArgumentParser(description=__doc__)
 p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,required=True)
 p.add_argument('--native-dir',type=Path,default=Path('build/native'))
 p.add_argument('--output-dir',type=Path,required=True)
 p.add_argument('--suite',choices=SUITES,action='append');a=p.parse_args()
 digest=sha(a.exe)
 if digest not in (DISC,PATCHED) or sha(a.disc)!=DISC:raise ValueError('Unknown executable identity')
 profile='allied-disc' if digest==DISC else 'supplied-ra2-1006'
 output=private_path(a.output_dir,a.exe)
 if output.exists():raise ValueError('Choose a fresh replay output directory')
 output.mkdir(parents=True)
 inputs={str(a.exe):digest,str(a.disc):DISC}
 for kind in ('direction','render','raster'):
  path=default_output(digest,kind+'-data.bin');inputs[str(path)]=sha(path)
 result=[];start=time.perf_counter();script_sha=sha(Path(__file__))
 for suite in (a.suite or SUITES):
  cli,runner,kinds=SUITES[suite];native=a.native_dir/runner;expected=ROOT/'private/migration'/profile/suite/'expected.json'
  baseline_report=output/(suite+'-retained-replay.json')
  before=validate_evidence(expected,digest,profile,a.exe)
  before[str(native)]=sha(native)
  evidence=json.loads(expected.read_text())
  values=[[str(v) for v in row] for row in evidence.get('values',evidence.get('expected'))]
  paths_retained={'exe':a.disc,**{k:default_output(DISC,k+'-data.bin') for k in ('direction','render','raster')},
                  'vpl':expected.parent/'voxels.vpl'}
  began=time.perf_counter()
  retained_argv=[str(native),*[str(paths_retained[k]) for k in kinds]]
  checked=subprocess.run(retained_argv,input='\n'.join(evidence['commands'])+'\n',capture_output=True,text=True,check=True)
  if [line.split() for line in checked.stdout.splitlines()]!=values:raise AssertionError('Retained replay differs: '+suite)
  retained_seconds=time.perf_counter()-began
  retained_receipt={'scope':'Content-checked original fixtures; historical exporter hashes retained in original receipt; no exporter runs',
                    'identities':before,'command':retained_argv,'comparisons':len(values),
                    'original_instructions_executed':False}
  baseline_report.write_text(json.dumps(retained_receipt,indent=2)+'\n')
  paths={'exe':a.exe,**{k:default_output(digest,k+'-data.bin') for k in ('direction','render','raster')},
         'vpl':expected.parent/'voxels.vpl'}
  argv=[str(native),*[str(paths[k]) for k in kinds]]
  before.update({str(paths[k]):sha(paths[k]) for k in kinds})
  began=time.perf_counter()
  native_result=subprocess.run(argv,input='\n'.join(evidence['commands'])+'\n',text=True,capture_output=True,check=True)
  actual=[line.split() for line in native_result.stdout.splitlines()]
  if values!=actual:raise AssertionError('Promoted data differs from original expectations: '+suite)
  for path,value in {**inputs,**before}.items():
   if sha(Path(path))!=value:raise ValueError('Replay input changed during execution: '+path)
  item={'suite':suite,'comparisons':len(actual),'retained_replay_seconds':retained_seconds,
        'promoted_replay_seconds':time.perf_counter()-began,'original_instructions_executed':False,
        'oracle_profile':profile,'native_data_source':digest,'native_command':argv,
        'identities':before,'retained_receipt_sha256':sha(baseline_report)}
  (output/(suite+'-promoted-replay.json')).write_text(json.dumps(item,indent=2)+'\n');result.append(item)
  print(f'{profile} {suite}: {len(actual):,} retained and promoted results PASS',flush=True)
 report={'scope':'Identity-checked cached original expectations; retained fixtures then source-matched prepared data; no fresh original execution',
         'profile':profile,'executable_sha256':digest,'inputs':inputs,'results':result,
         'total_comparisons_per_pass':sum(v['comparisons'] for v in result),
         'elapsed_seconds':time.perf_counter()-start,'source_sha256':script_sha}
 if sha(Path(__file__))!=script_sha:raise ValueError('Replay script changed during execution')
 (output/'summary.json').write_text(json.dumps(report,indent=2)+'\n')
if __name__=='__main__':main()
