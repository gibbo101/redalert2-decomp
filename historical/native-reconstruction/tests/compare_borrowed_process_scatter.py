#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original Process over actual prepared Cell/Unit/nearby owners (unwired)."""
import argparse,json,time
from pathlib import Path
import compare_process_terminal_scatter as parent
import compare_borrowed_cell_scatter as borrowed
from original_results import OriginalResults,add_arguments
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
SOURCES=tuple(sorted(set((*parent.SOURCES,*borrowed.SOURCES,
 'tests/compare_borrowed_process_scatter.py','tests/test_borrowed_process_scatter_evidence.py',
 'tests/borrowed_process_scatter_check.cpp','tests/borrowed_process_scatter/CMakeLists.txt'))))
FLAGS=dict(actual_prepared_Process_Advance_Cell_Unit_nearby_owners=True,
 no_motion_or_target_refresh=True,Process_root_actor0=True,complete_Process1_verified=False,
 production_runtime_enabled=False)
require=parent.require
command=parent.command
def parse(cmd):
 c=parent.parse(cmd)
 # The same original diagnostic arena has five actors. Only two are bound;
 # the remaining three must retain the unreachable original defaults.
 borrowed.parse(borrowed.nearby.command(**{k:v for k,v in c.items() if k in borrowed.nearby.defaults()}))
 return c
def identities(a):
 result=parent.identities(a);result['sources']={p:hash_file(ROOT/p) for p in SOURCES}
 result['legacy_native_sha256']=hash_file(a.legacy_native);return result
def validate(e,r,f,current):
 parent.validate(e,r,f,current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 for cmd in e['commands']:parse(cmd)
def generate(a):
 commands,expected,labels,meta=parent.generate(a)
 for cmd in commands:parse(cmd)
 return commands,expected,labels,dict(meta,**FLAGS)
def compare(a,commands,expected,report):
 count=parent.compare(a,commands,expected,report)
 import copy
 legacy=copy.copy(a);legacy.native=a.legacy_native
 require(parent.compare(legacy,commands,expected,report.with_name(report.name+'-legacy'))==count)
 return count
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True);p.add_argument('--legacy-native',type=Path,required=True)
 for name,filename in [('direction','direction-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('geometry','ramp-geometry-data.bin')]:p.add_argument('--'+name+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/filename)
 p.add_argument('--pilot',action='store_true');p.add_argument('--pilot-limit',type=int);p.add_argument('--output',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);add_arguments(p);a=p.parse_args();require(a.pilot_limit is None or a.pilot and a.pilot_limit>0);start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 reuse=OriginalResults(a,current,__file__)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());reuse.validate(validate,e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 reuse.annotate(result)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'complete Process sequences PASS')
 reuse.finish(source,report,validate)
if __name__=='__main__':main()
