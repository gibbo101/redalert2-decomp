#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete actor registration/footprint callers with explicit original-only reuse."""
import argparse,json,platform,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_actor_markers import verify
NATIVE=('src/render/RadarActorMarkers.hpp','src/render/RadarMarkerBuckets.hpp','src/render/RadarMarkerPlacement.hpp','tests/radar_actor_markers_vectors.cpp')
ORIGINAL=('tests/original_radar_actor_markers.py','tools/verify_radar_actor_markers.py','tests/compare_radar_actor_markers.py')
SOURCES=(*NATIVE,*ORIGINAL)
FLAGS=dict(complete_six_actor_callers=True,actual_stock_shape_selector=True,child_marker_dirty_effects_supplied=True,production_scheduling=False)
def require(v):
 if not v:raise ValueError('Actor marker input/evidence differs')
def command(op,index=0,count=3,x=2,y=1,reg=0,mutation=0):
 return 'A '+' '.join(map(str,(op,index,count,x,y,reg,mutation)))
def parse(cmd):
 t=cmd.split();require(len(t)==8 and t[0]=='A');f=list(map(int,t[1:]));op,index,count,x,y,reg,mutation=f
 require(0<=op<6 and 0<=index<22 and -1<=count<=8 and -2**31<=x<2**31 and -2**31<=y<2**31 and 0<=reg<=255 and 0<=mutation<=5);return f
def scenarios():
 for op,reg,mutation in itertools.product(range(6),(0,128,255),range(6)):
  yield 'late_registration_alias_and_live_child_mutations',command(op,reg=reg,mutation=mutation)
 for op,index,count in itertools.product(range(3,6),range(22),(-1,0,1,8)):
  yield 'all_stock_footprint_indexes_and_empty_negative_counts',command(op,index=index,count=count)
 for op,x,y in itertools.product(range(6),(-2147483648,2147483647),(2147483647,-2147483648)):
  yield 'wrapped_footprint_composition',command(op,x=x,y=y)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and row.count('R')==1);at=row.index('R');require(len(row)-at==7);list(map(int,row[at+1:]));i=0
 while i<at:
  n=dict(I=4,D=4,Q=5,L=3,M=2,S=2,W=2).get(row[i]);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_actor_markers.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-actor-markers-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_actor_markers import RadarActorMarkersOracle
  oracle=RadarActorMarkersOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar actor marker sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
