#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare base visibility startup construction with portable C++."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_visibility_startup import verify

NATIVE=('src/sim/VisibilityStartup.hpp','src/sim/VisibilityStartup.cpp','tests/visibility_startup_vectors.cpp')
ORIGINAL=('tests/original_visibility_startup.py','tools/verify_visibility_startup.py','tests/compare_visibility_startup.py')
SOURCES=(*NATIVE,*ORIGINAL)
FLAGS=dict(complete_spread_constructor_5441E0=True,complete_height_constructor_5461A0=True,constructor_registration_order=True,all_369_spread_and_309_height_points=True,projection_initializers_reused=True,private_lookup_tables_not_incorporated=True,production_visibility_schedule=False)
def require(value):
 if not value:raise ValueError('Visibility startup evidence/input differs')
def scenarios():return [('spread_height_and_projection_startup','V')]
def identities(args):
 paths=python_closure(ROOT/'tests/compare_visibility_startup.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(args.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(evidence,receipt,fingerprint,current,args):
 validate_receipt(evidence,receipt,fingerprint);require(evidence.get('executable_sha256')==PATCHED_EXPECTED and evidence.get('profile')=='supplied-ra2-1006' and evidence['evidence']['identities']['original']==current['original'])
 for key,value in FLAGS.items():require(evidence['evidence'].get(key) is value)
 require(list(zip(evidence['labels'],evidence['commands']))==scenarios() and len(evidence['expected'])==1)
 row=evidence['expected'][0];require(isinstance(row,list) and len(row)==1369 and row[0]=='V')
def main():
 parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--exe',type=Path,required=True);parser.add_argument('--native',type=Path,default=ROOT/'build/native/visibility-startup-vectors')
 for name in ('output','expectations','report'):parser.add_argument('--'+name,type=Path)
 args=parser.parse_args();started=time.monotonic();current=identities(args);runner=hash_file(args.native)
 if args.expectations:
  require(not args.output and args.report is not None);source=private_path(args.expectations,args.exe);fingerprint=hash_file(source);evidence=json.loads(source.read_text());validate(evidence,json.loads((source.parent/'report.json').read_text()),fingerprint,current,args);commands,labels,expected=[evidence[key] for key in ('commands','labels','expected')];meta=evidence['evidence'];generation=0;report=private_path(args.report,args.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(args.output is not None and not args.report);folder=private_path(args.output,args.exe);require(not folder.exists());from original_visibility_startup import VisibilityStartupOracle
  oracle=VisibilityStartupOracle(args.exe);commands=['V'];labels=[scenarios()[0][0]];now=time.monotonic();expected=[oracle.run()];generation=time.monotonic()-now;require(oracle.audit_calls==5 and current==identities(args) and runner==hash_file(args.native))
  meta=dict(FLAGS,identities=current,cases=1,audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(args.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(args.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(args.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for index,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   offset=next((j for j,(a,b) in enumerate(zip(got,want)) if a!=b),min(len(got),len(want)));raise AssertionError((index,labels[index],offset,got[max(0,offset-10):offset+30],want[max(0,offset-10):offset+30]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(args.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(args) and runner==hash_file(args.native));hits=1 if args.expectations else 0;misses=0 if args.expectations else 1
 write_report(args.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if args.expectations else 'fresh-original',original_instructions_executed=not bool(args.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-started,expectations_sha256=fingerprint));print('1 visibility startup sequence / 1,368 values PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
