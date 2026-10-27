#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Current-native replay of the immutable, mixed-identity Unit destination proof.

The old driver/receipt remain unchanged. Its Python generator uses no native
input producer. Validate every historical original dependency, while retaining
separate current C++/CMake/runner identities. This is not receipt migration.
"""
import argparse,json,time
from pathlib import Path
import compare_unit_destination as old
from presentation_evidence import ROOT,hash_file,private_path,check_replay_destination
from compare_original import write_report
SOURCES=(*old.SOURCES,'tests/compare_unit_destination_current.py','tests/test_infantry_destination.py','tools/run_evidence.py')
def native_source(p):return Path(p).suffix in ('.cpp','.hpp') or Path(p).name=='CMakeLists.txt'
def validate(e,r,f,current):
 origin=e['evidence']['identities'];old.validate(e,r,f,origin)
 old.require(origin['inspection']==current['inspection'])
 historical={p:h for p,h in origin['sources'].items() if not native_source(p)}
 actual={p:h for p,h in current['sources'].items() if not native_source(p)}
 old.require(bool(historical) and historical==actual)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','expectations','report'):p.add_argument('--'+k,type=Path,required=True)
 a=p.parse_args();start=time.monotonic();current=old.identities(a);runner=hash_file(a.native)
 adapter=hash_file(Path(__file__));source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json'
 fingerprint=hash_file(source);receipt_hash=hash_file(receipt);e=json.loads(source.read_text())
 validate(e,json.loads(receipt.read_text()),fingerprint,current)
 report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 now=time.monotonic();count=old.compare(a,e['commands'],e['expected'],report.with_name(report.stem+'-native'))
 elapsed=time.monotonic()-now
 old.require(current==old.identities(a) and runner==hash_file(a.native) and adapter==hash_file(Path(__file__)))
 old.require(fingerprint==hash_file(source) and receipt_hash==hash_file(receipt))
 write_report(a.exe,report,dict(evidence_mode='current-native-original-replay',identities=current,native_sha256=runner,
  adapter_sha256=adapter,original_identity=e['evidence']['identities'],original_receipt_sha256=receipt_hash,
  expectations_sha256=fingerprint,original_sequence_reuse_hits=count,original_sequence_reuse_misses=0,
  original_instructions_executed=False,native_comparison_seconds=elapsed,elapsed_seconds=time.monotonic()-start,
  scope='All historical Unit/Foot destination commands and projections; rebuilt current native. No receipt relabeling.'))
 print(count,'Unit destination sequences PASS; original reuse hits/misses',count,0)
if __name__=='__main__':main()
