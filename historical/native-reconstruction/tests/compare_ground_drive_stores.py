#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual selected Drive stores through complete ordinary Advance."""
import argparse,json,struct,subprocess,time
from pathlib import Path
import pefile
import compare_ground_drive_advance as base
from original_results import OriginalResults, add_arguments as add_original_arguments
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_drive_stores import verify,STORE_SITES

SOURCES=tuple(dict.fromkeys((*base.SOURCES,'tests/original_ground_drive_stores.py',
 'tests/compare_ground_drive_stores.py','tests/test_ground_drive_stores_evidence.py',
 'tools/verify_ground_drive_stores.py')))

def identities(a):
 return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
  'owned_rules':{str(a.rules.resolve()):hash_file(a.rules)}}

def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':
  raise ValueError('Drive-store engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Drive-store source/input identity differs')
 if not e['evidence'].get('selected_Drive_stores_and_actor_query_service_order'):
  raise ValueError('Drive-store ordered proof missing')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):
  raise ValueError('Drive-store counts differ')
 for cmd in e['commands']:
  try:base.parse(cmd)
  except (AssertionError,ValueError,IndexError,OverflowError,struct.error):
   raise ValueError('Malformed Drive-store command') from None

def generate(a):
 from original_ground_drive_stores import GroundDriveStoresOracle
 originals=[]
 def factory(exe):
  oracle=GroundDriveStoresOracle(exe);originals.append(oracle);return oracle
 commands,expected,labels,metadata=base.generate(a,oracle_type=factory)
 o=originals[0];p=pefile.PE(str(a.exe));planes=base.parse(commands[0])[2]
 legacy_count=len(commands)
 for track in range(64):
  raw=p.get_data(0x7a0180+12*track-0x400000,1)[0]
  if not raw:continue
  stream=struct.unpack('<I',p.get_data(0x7a00a0+16*raw-0x400000,4))[0]
  for index in range(1,128):
   if p.get_data(stream+12*index-0x400000,8)==bytes(8):break
  else:raise ValueError('Missing ordinary terminator')
  for head_z in (0,9):
   cmd=base.command(planes,track=track,index=index,acc=8,suppress=1,steps=2,
    hx=0,hy=0,hz=head_z,x=0,y=0,z=0,level=0,ramp=0,pattern=0,mode=len(commands)%4)
   v,percentage,t=base.parse(cmd);commands.append(cmd);expected.append(o.run(v,percentage,t))
   labels.append('terminal_zero_head_retains_driving' if not head_z else 'terminal_Z_only_head_still_clears')
 if set(o.drive_stores)!=set(map(hex,STORE_SITES)):
  raise AssertionError('Selected original store site not entered')
 metadata.update(audited_complete_Advance_roots=o.roots,actual_selected_actor_stores=o.stores,
  actual_entries=o.entries,supplied_Mark_calls=o.marks,actual_selected_Drive_stores=dict(o.drive_stores),
  selected_Drive_stores_and_actor_query_service_order=True,
  retained_legacy_scenarios=legacy_count,terminal_zero_or_Z_only_head_scenarios=len(commands)-legacy_count)
 return commands,expected,labels,metadata

def main():
 parser=argparse.ArgumentParser(description=__doc__)
 parser.add_argument('--exe',type=Path,required=True)
 parser.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets/rules.ini')
 parser.add_argument('--native',type=Path,default=ROOT/'build/native/ground-drive-advance-vectors')
 parser.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-drive-stores-v1')
 parser.add_argument('--expectations',type=Path);parser.add_argument('--report',type=Path)
 add_original_arguments(parser)
 a=parser.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 reuse = OriginalResults(a, current, __file__)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
  e=json.loads(source.read_text());reuse.validate(validate,e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():
   raise ValueError('Fresh Drive-store output invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now
  report=dest/'report.json'
 now=time.monotonic()
 proc=subprocess.run([str(a.native),str(a.exe),'--drive-stores'],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native Drive-store failure: '+proc.stderr.strip())
 actual=[line.split() for line in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Drive-store result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-12):j+16]} != {y[max(0,j-12):j+16]}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Drive-store run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 reuse.annotate(result)
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
   'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);reuse.finish(source,report,validate)
 print(f'{len(commands)} Drive-store sequences /{metadata["audited_complete_Advance_roots"]} original calls: PASS ({result["evidence_mode"]})')

if __name__=='__main__':main()
