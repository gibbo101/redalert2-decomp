#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete base archive request stages; keep private exact-engine receipts."""
import argparse,hashlib,json,subprocess,sys,time
from pathlib import Path
from archive_profiles import archive_profile
from compare_archive import source_identities as primitive_sources,validate_cached,run_native
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
from verify_archive_sequence_mapping import verify
from verify_archive_startup_order import verify as verify_order
from inspect_patch import write_report
SOURCES=('tests/archive_sequence_profiles.py','tests/original_archive_sequence.py','tests/compare_archive_sequence.py',
 'tests/archive_sequence_vectors.cpp','src/assets/ArchiveSequence.cpp','src/assets/ArchiveSequence.hpp',
 'tools/verify_archive_sequence_mapping.py','tools/verify_archive_startup_order.py')
def sources():return {**primitive_sources(),**{p:hash_file(ROOT/p) for p in SOURCES}}

def main():
 p=argparse.ArgumentParser(description=__doc__)
 p.add_argument('--exe',type=Path,required=True);p.add_argument('--disc',type=Path,default=ROOT/'private/disc-allied/game.exe')
 p.add_argument('--patched',type=Path,default=ROOT/'private/official-1006-probe/game.exe')
 p.add_argument('--native',type=Path,default=ROOT/'build/native/archive-sequence-vectors')
 p.add_argument('--output-dir',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();digest,profile=archive_profile(a.exe.read_bytes());verify(a.disc.read_bytes(),a.patched.read_bytes());order=verify_order(a.exe.read_bytes())
 work=private_path(a.output_dir or ROOT/'private/migration'/profile/'archive-sequence',a.exe)
 initial=sources();native_hash=hash_file(a.native)
 def identity():
  if archive_profile(a.exe.read_bytes())!=(digest,profile) or initial!=sources() or native_hash!=hash_file(a.native):raise ValueError('Archive stage source/engine/native changed during run')
  return {'executable_sha256':digest,'profile':profile,'sources':initial,'fixtures':{},'native_sha256':native_hash,'runtime_profile_promoted':False}
 if a.expectations:
  source=private_path(a.expectations,a.exe);e=json.loads(source.read_text());receipt=private_path(source.parent/'report.json',a.exe)
  validate_receipt(e,json.loads(receipt.read_text()),hash_file(source));validate_cached(e,identity())
  destination=private_path(a.report or work/'replay-report.json',a.exe);check_replay_destination(destination,source,receipt)
  actual=run_native(a.native,e['commands']);validate_cached(e,identity())
  if actual!=e['expected']:raise AssertionError('Archive stage cached original/native mismatch')
  report={**e['evidence'],**identity(),'evidence_mode':'cached-original-replay','original_instructions_executed':False,'expectations_sha256':hash_file(source)}
  write_report(a.exe,destination,report);print(f'{len(actual):,} {profile} archive-stage results PASS (native replay; no original execution)');return
 for path in [work/'expected.json',work/'report.json',*([a.report] if a.report else [])]:
  private_path(path,a.exe)
  if path.exists():raise ValueError('Fresh archive stage output exists; use --expectations')
 from original_archive_sequence import ArchiveSequenceOracle
 o=ArchiveSequenceOracle(a.exe);commands=[];expected=[];groups={};observations=[]
 def add(group,command,result,events):
  commands.append(command);expected.append(list(map(str,result)));groups[group]=groups.get(group,0)+1;observations.append(events)
 def startup(enumerate,media,available,maps=(),movies=()):
  result,events=o.startup(enumerate,media,available,maps,movies)
  args=' '.join(str(len(items))+' '+ ' '.join(json.dumps(item) for item in items) for items in (available,maps,movies))
  add('startup-enumeration' if enumerate else 'startup-selected',f'S {enumerate} {media} '+args,result,events)
 started=time.monotonic()
 for media in (0,1):
  names=['conquer.mix','cameo.mix',f'maps{media+1:02d}.mix','multi.mix','theme.mix',f'movies{media+1:02d}.mix']
  for mask in range(64):startup(0,media,[name for i,name in enumerate(names) if mask&(1<<i)])
  names=['conquer.mix','cameo.mix','multi.mix','theme.mix']
  for mask in range(16):
   for maps in [[],['maps01.mix'],['maps02.mix','maps01.mix'],['maps03.mix','maps01.mix','maps03.mix']]:
    for movies in [[],['movies01.mix'],['movies02.mix','movies01.mix'],['movies03.mix','movies01.mix','movies03.mix']]:
     startup(1,media,[name for i,name in enumerate(names) if mask&(1<<i)],maps,movies)
 for new in range(3):
  for previous in (-1,0,1,2):
   for existing in (False,True):
    for palette in (False,True):
     result,events=o.theater(new,previous,existing,palette)
     add('theater-requests',f'T {new} {previous}',result,events)
 original_seconds=time.monotonic()-started;actual=run_native(a.native,commands)
 if actual!=expected:
  mismatch=next((i for i,pair in enumerate(zip(expected,actual)) if pair[0]!=pair[1]),min(len(expected),len(actual)))
  raise AssertionError(f'Archive stage mismatch {mismatch}: {commands[mismatch]}\noriginal {expected[mismatch]}\nnative {actual[mismatch]}')
 report={**identity(),'evidence_mode':'fresh-original','original_instructions_executed':True,'cases':len(commands),'groups':groups,
  'callable_roots':o.calls,'audited_guest_writes':o.audit_writes,'original_generation_seconds':original_seconds,'service_events':observations,
  'startup_order_inspection':order,'limits':'successful allocation; constructor/destructor/cache/OS/directory/format/palette/display services; initial startup handles zero; empty color-type array; request results only, no lifetime or palette parity'}
 evidence={'executable_sha256':digest,'profile':profile,'commands':commands,'expected':expected,'evidence':report}
 write_report(a.exe,work/'expected.json',evidence);report={**report,'expectations_sha256':hash_file(work/'expected.json')}
 write_report(a.exe,work/'report.json',report)
 if a.report and a.report.resolve()!=(work/'report.json').resolve():write_report(a.exe,a.report,report)
 print(f'{len(commands):,} {profile} original/native archive-stage results PASS')
if __name__=='__main__':main()
