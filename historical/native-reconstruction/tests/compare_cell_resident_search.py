#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the complete primary/secondary Cell resident search."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_cell_resident_search import verify,HELPER

NATIVE=('src/sim/CellResidentSearch.hpp','src/sim/CellResidentKind6.hpp','tests/cell_resident_search_vectors.cpp')
ORIGINAL=('tests/original_cell_resident_search.py','tools/verify_cell_resident_search.py','tests/compare_cell_resident_search.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_cell_resident_search.py')
FLAGS=dict(complete_471760=True,low_byte_list_selection=True,disabled_no_query_and_first_match=True,virtual_kind_supplied=True,authored_lists=True,production_binding=False)
def require(value):
 if not value:raise ValueError('Cell resident search evidence/input differs')
def command(initial,selector,requested,split,kinds):return 'R '+' '.join(map(str,(initial,selector,requested,split,len(kinds),*kinds)))
def parse(cmd):
 f=cmd.split();require(len(f)>=6 and f[0]=='R');v=list(map(int,f[1:]));initial,selector,requested,split,count=v[:5];kinds=v[5:]
 require(0<=initial<=255 and 0<=selector<2**32 and -2**31<=requested<2**31 and 0<=split<=count<=32 and len(kinds)==count and all(-2**31<=x<2**31 for x in kinds));return initial,selector,requested,split,kinds
def scenarios():
 for initial in (0,1,128,255):
  for selector in (0,1,128,255,256,0xffffff00,0xffffffff):
   for split,kinds in ((0,()),(0,(36,6)),(2,(36,6)),(2,(6,36,36,6)),(2,(36,36,6,36)),(1,(6,7,8))):
    yield 'complete_resident_search',command(initial,selector,36,split,kinds)
 rng=random.Random(0x471760)
 for i in range(120):
  count=i%33;requested=(-2**31,-1,0,6,36,2**31-1)[i%6];kinds=[rng.randint(-40,40) for _ in range(count)]
  if count and i%3:kinds[(i//3)%count]=requested
  yield 'signed_kind_and_list_order',command((0,1,255)[i%3],(0,1,256,257,0xffffff00)[i%5],requested,i%(count+1),kinds)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_resident_search.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},
  environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),
  unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for key,value in FLAGS.items():require(e['evidence'].get(key) is value)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  initial,selector,requested,split,kinds=parse(cmd);require(row[:2]==['S',str(initial)] and row[-2]=='R')
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/cell-resident-search-vectors')
 for key in ('output','expectations','report'):p.add_argument('--'+key,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_resident_search import CellResidentSearchOracle
  oracle=CellResidentSearchOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():
   commands.append(cmd);labels.append(label);expected.append(oracle.run(*parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['roots']==len(commands) and oracle.counts['kind']>0 and oracle.counts['next']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta))
  fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True)
 report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,
  native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell resident search sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
