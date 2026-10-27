#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Current-native replay of historical Mark/membership/resident-Cell/redraw receipts.

These Python generators have no native input producer. Preserve the old full
receipt/validator and independently check every current original dependency;
record current C++/runner identities separately. No receipt migration.
"""
import argparse,json,subprocess,time
from pathlib import Path
import compare_unit_mark as mark
import compare_unit_membership as membership
import compare_resident_cell as resident
import compare_redraw as redraw
from presentation_evidence import ROOT,hash_file,private_path,check_replay_destination
from compare_original import write_report
FAMILIES={'mark':mark,'membership':membership,'resident':resident,'redraw':redraw}
SOURCES=tuple(sorted(set((*mark.SOURCES,*membership.SOURCES,*resident.SOURCES,*redraw.SOURCES,'src/sim/MembershipPolicy.hpp',
 'tests/compare_membership_current.py','tests/test_infantry_membership.py','tools/run_evidence.py','CMakeLists.txt'))))
def native_source(p):return Path(p).suffix in ('.cpp','.hpp') or Path(p).name=='CMakeLists.txt'
def require(v):
 if not v:raise ValueError('Historical membership original identity differs')
def validate(old,e,r,f,current):
 origin=e['evidence']['identities'];old.validate(e,r,f,origin)
 require(origin['inspection']==current['inspection'])
 historical={p:h for p,h in origin['sources'].items() if not native_source(p)}
 actual={p:h for p,h in current['sources'].items() if not native_source(p)}
 require(bool(historical) and historical==actual)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--family',choices=FAMILIES,required=True)
 for k in ('exe','native','expectations','report'):p.add_argument('--'+k,type=Path,required=True)
 a=p.parse_args();start=time.monotonic();old=FAMILIES[a.family]
 def identity():return old.identities(a.exe) if a.family=='redraw' else old.identities(a)
 snapshot=identity();current=dict(snapshot,sources=dict(snapshot['sources']));runner=hash_file(a.native)
 current['sources']['src/sim/MembershipPolicy.hpp']=hash_file(ROOT/'src/sim/MembershipPolicy.hpp')
 # The added native header is not an original dependency and is not passed to
 # the unchanged mixed-identity validator as a fabricated historical source.
 current['build_source_sha256']=hash_file(ROOT/'CMakeLists.txt')
 adapter=hash_file(Path(__file__));source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json'
 fingerprint=hash_file(source);receipt_hash=hash_file(receipt);e=json.loads(source.read_text())
 validate(old,e,json.loads(receipt.read_text()),fingerprint,snapshot)
 report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(e['commands'])+'\n',text=True,capture_output=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(e['expected']))
 for i,(got,want) in enumerate(zip(actual,e['expected'])):
  if got!=want:raise AssertionError((a.family,i,e['labels'][i],got,want))
 if a.family in ('resident','redraw'):
  guard=subprocess.run([str(a.native)],input='?\n' if a.family=='redraw' else 'K 0\n',capture_output=True,text=True);require(guard.returncode!=0 and bool(guard.stderr.strip()))
 else:
  guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('PASS' in guards.stdout)
 elapsed=time.monotonic()-now
 require(snapshot==identity() and current['sources']['src/sim/MembershipPolicy.hpp']==hash_file(ROOT/'src/sim/MembershipPolicy.hpp'))
 require(current['build_source_sha256']==hash_file(ROOT/'CMakeLists.txt'))
 require(runner==hash_file(a.native) and adapter==hash_file(Path(__file__)) and fingerprint==hash_file(source) and receipt_hash==hash_file(receipt))
 write_report(a.exe,report,dict(evidence_mode='current-native-original-replay',identities=current,native_sha256=runner,
  adapter_sha256=adapter,original_identity=e['evidence']['identities'],original_receipt_sha256=receipt_hash,
  expectations_sha256=fingerprint,original_sequence_reuse_hits=len(actual),original_sequence_reuse_misses=0,
  original_instructions_executed=False,native_comparison_seconds=elapsed,elapsed_seconds=time.monotonic()-start,
  scope='All historical '+a.family+' commands/projections; current native. No receipt relabeling.'))
 print(len(actual),a.family,'sequences PASS; original reuse hits/misses',len(actual),0)
if __name__=='__main__':main()
