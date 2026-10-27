#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the scenario-loop setter and complete kind-6 Cell traversal."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_cell_resident_kind6 import verify,HELPER

NATIVE=('src/sim/CellResidentKind6.hpp','src/sim/CellResidentKind6.cpp','tests/cell_resident_kind6_vectors.cpp')
ORIGINAL=('tests/original_cell_resident_kind6.py','tools/verify_cell_resident_kind6.py','tests/compare_cell_resident_kind6.py')
FLAGS=dict(selected_scenario_loop_setter_store=True,both_direct_loop_callers=True,top_level_loop_callers_inspected=True,
 complete_4717B0_primary_list_traversal=True,disabled_no_query_and_kind6_early_return=True,supplied_virtual_kind_child=True,
 complete_scenario_startup=False,production_resident_owner_binding=False)
def require(value):
 if not value:raise ValueError('Cell kind-6 resident evidence/input differs')
def command(initial,mode,kinds):return 'R '+' '.join(map(str,(initial,mode,len(kinds),*kinds)))
def parse(cmd):
 fields=cmd.split();require(len(fields)>=4 and fields[0]=='R');values=list(map(int,fields[1:]));initial,mode,count=values[:3]
 require(0<=initial<=255 and mode in (0,1,2) and 0<=count<=32 and len(values)==3+count and all(-2**31<=x<2**31 for x in values[3:]));return initial,mode,values[3:]
def scenarios():
 fixed=((0,0,()),(0,0,(6,)),(0,0,(1,2,6)),(1,0,()),(1,0,(6,)),(1,0,(1,2,6,7)),(255,0,(1,2,3)),
        (0,1,()),(0,1,(6,)),(0,1,(1,6,2)),(255,1,(1,2,3)),(0,2,()),(0,2,(4,5,6)),(255,2,(6,7)))
 for values in fixed:yield 'setter_and_complete_kind6',command(*values)
 rng=random.Random(0x4717b0)
 for i in range(50):
  initial=(0,1,255)[i%3];mode=i%3;count=i%11;kinds=[rng.randint(-9,15) for _ in range(count)]
  if count and i%2==0:kinds[i%count]=6
  yield 'setter_and_complete_kind6',command(initial,mode,kinds)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_resident_kind6.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},
  environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),
  unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for key,value in FLAGS.items():require(e['evidence'].get(key) is value)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  initial,mode,kinds=parse(cmd);prefix=['W','1','S','1'] if mode else ['S',str(initial)]
  require(row[:len(prefix)]==prefix and row[-2]=='R')
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/cell-resident-kind6-vectors')
 for key in ('output','expectations','report'):p.add_argument('--'+key,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_resident_kind6 import CellResidentKind6Oracle
  oracle=CellResidentKind6Oracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():
   commands.append(cmd);labels.append(label);expected.append(oracle.run(*parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts[hex(HELPER[0])]==len(commands) and oracle.counts['caller1']>0 and oracle.counts['caller2']>0 and
   oracle.counts['setter_store']==oracle.counts['caller1']+oracle.counts['caller2'] and current==identities(a) and runner==hash_file(a.native))
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
  native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell kind-6 resident sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
