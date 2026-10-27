# SPDX-License-Identifier: GPL-3.0-or-later
"""Replay unchanged historical scenery/prop inputs against the current renderer.

The captured exported bytes are validated directly; the old native exporter is
not rerun or relabeled as current. All original Python/mapping sources stay exact.
"""
import argparse,json,subprocess,time
from pathlib import Path
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
import scenery_evidence as old
SOURCES=tuple('tests/'+p for p in old.SOURCES)+('tests/compare_scenery_current.py','src/render/Scenery.cpp','src/render/Scenery.hpp','src/render/Composition.cpp','src/render/Composition.hpp','tests/scenery_vectors.cpp')
def require(v):
 if not v:raise ValueError('Historical scenery original identity differs')
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 origin=e['evidence'];require(origin['original_instructions_modified'] is False)
 for k in ('oracle_sources','mapping_tools','render_data_sha256','assets_sha256','fixture_sha256','suite'):
  require(origin.get(k)==current.get(k))
 require(origin['suite'] in ('scenery','props') and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(len(e['commands'])=={'scenery':420,'props':808}[origin['suite']])
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','expectations','report'):p.add_argument('--'+k,type=Path,required=True)
 a=p.parse_args();start=time.monotonic();source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json'
 report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 fingerprint=hash_file(source);receipt_hash=hash_file(receipt);require(hash_file(a.exe)==PATCHED_EXPECTED)
 e=json.loads(source.read_text());origin=e['evidence'];suite=origin['suite'];require(suite in ('scenery','props'))
 require(source.resolve()==(ROOT/'private/migration/supplied-ra2-1006'/suite/'expected.json').resolve())
 def identity():
  return dict(oracle_sources={p:hash_file(ROOT/'tests'/p) for p in origin['oracle_sources']},
   mapping_tools={p:hash_file(ROOT/'tools'/p) for p in origin['mapping_tools']},render_data_sha256=hash_file(a.render_data),
   assets_sha256={p:hash_file(source.parent/'assets'/p) for p in origin['assets_sha256']},
   fixture_sha256={p:hash_file(private_path(Path(p),a.exe)) for p in origin['fixture_sha256']},suite=suite)
 current=identity();validate(e,json.loads(receipt.read_text()),fingerprint,current);runner=hash_file(a.native);adapter=hash_file(Path(__file__))
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(e['commands'])+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr)
 require(run.returncode==0);actual=[row.split() for row in run.stdout.splitlines()];require(len(actual)==len(e['expected']))
 for i,(got,want) in enumerate(zip(actual,e['expected'])):
  if got!=want:raise AssertionError((suite,i,e['labels'][i],got,want))
 require(current==identity() and runner==hash_file(a.native) and adapter==hash_file(Path(__file__)) and fingerprint==hash_file(source) and receipt_hash==hash_file(receipt) and hash_file(a.exe)==PATCHED_EXPECTED)
 write_report(a.exe,report,dict(evidence_mode='current-native-original-replay',original_identity=origin,current_original_inputs=current,native_sha256=runner,adapter_sha256=adapter,expectations_sha256=fingerprint,original_receipt_sha256=receipt_hash,original_instructions_executed=False,original_sequence_reuse_hits=len(actual),original_sequence_reuse_misses=0,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,scope='All unchanged captured '+suite+' inputs; exporter provenance retained, exported bytes independently validated without rerunning exporter; no receipt relabeling'))
 print(len(actual),suite,'sequences PASS; original reuse hits/misses',len(actual),0)
if __name__=='__main__':main()
