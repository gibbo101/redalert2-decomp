#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete actor placement parent with explicit original-only reuse."""
import argparse,json,platform,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_actor_placement import verify
NATIVE=('src/render/RadarActorPlacement.hpp','src/render/RadarActorMarkers.hpp','src/render/RadarMarkerPlacement.hpp','src/sim/Drive.hpp','tests/radar_actor_placement_vectors.cpp')
ORIGINAL=('tests/original_radar_actor_placement.py','tools/verify_radar_actor_placement.py','tests/compare_radar_actor_placement.py')
SOURCES=(*NATIVE,*ORIGINAL)
FLAGS=dict(complete_actor_placement_parent=True,permission_status_output_preserved=True,child_effects_supplied=True,production_scheduling=False)
def require(v):
 if not v:raise ValueError('Actor marker input/evidence differs')
def command(**kw):
 d=dict(kind=15,arg=0,discovery=0,loading=0,permission=1,status=0,allowed=1,reg=0,x=2,y=1,px=3,py=2,flags=1,secondary=-1,owner=0,start=-1,remaining=6,frame=7,divisor=3,mutation=0,visible=0)
 require(not set(kw)-set(d));d.update(kw);return 'L '+' '.join(map(str,d.values()))
def parse(cmd):
 t=cmd.split();require(len(t)==22 and t[0]=='L');f=list(map(int,t[1:]));kind,arg,discovery,loading,permission,status,allowed,reg,x,y,px,py,flags,secondary,owner,start,remaining,frame,divisor,mutation,visible=f
 require(kind in (6,15) and 0<=arg<=511 and 0<=discovery<=255 and all(-2**31<=v<2**31 for v in (loading,status,x,y,px,py,start,remaining,frame,divisor)) and 0<=permission<=511 and 0<=allowed<=511 and 0<=reg<=255 and 0<=flags<=255 and -128<=secondary<=127 and owner in (0,1) and divisor!=0 and 0<=mutation<=6 and 0<=visible<=511)
 # Original idiv fault remains a native refusal, not an oracle crash scenario.
 elapsed=((frame-start+2**31)%2**32)-2**31
 effective=remaining if start==-1 else 0 if elapsed>=remaining else ((remaining-elapsed+2**31)%2**32)-2**31
 require(not(effective==-2**31 and divisor==-1));return f
def scenarios():
 for kind,arg,permission,status,reg in itertools.product((6,15),(0,1,256),(0,1,256,511),(0,2,-1),(0,128)):
  yield 'full_parent_low_bytes_building_reuse_and_permission_status',command(kind=kind,arg=arg,permission=permission,status=status,reg=reg)
 for discovery,loading,visible in itertools.product((0,128),(0,1),(0,1,256,511)):
  yield 'initial_discovery_low_byte_and_loading_bypasses',command(discovery=discovery,loading=loading,visible=visible)
 for px,py,allowed,flags,secondary in itertools.product((-1,0,16),(0,12),(0,1,256,511),(0,4),(-1,0)):
  yield 'screen_edges_map_permission_clamped_reprojection_and_visibility_gate',command(px=px,py=py,allowed=allowed,flags=flags,secondary=secondary,status=1,reg=1)
 for mutation,kind,status,reg in itertools.product(range(1,7),(6,15),(0,1),(0,1)):
  yield 'live_child_fields_and_registration_between_coordinate_stores',command(mutation=mutation,kind=kind,status=status,reg=reg,arg=1)
 for start,remaining,frame,divisor,owner in itertools.product((-1,5,2147483647),(-1,0,6,2147483647),(-2147483648,5,7,12),(-3,1,3),(0,1)):
  cmd=command(start=start,remaining=remaining,frame=frame,divisor=divisor,owner=owner)
  try:parse(cmd)
  except ValueError:continue
  yield 'signed_timer_wrapping_positive_gate_and_division_remainder',cmd
 for x,y in itertools.product((-2147483648,2147483647),(0,2147483647)):
  yield 'saved_Building_point_and_wrapped_rectangle_comparisons',command(kind=6,x=x,y=y,reg=1)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and row.count('F')==1);at=row.index('F');require(len(row)-at==6);list(map(int,row[at+1:]));i=0
 while i<at:
  n=dict(A=4,K=2,E=3,G=1,C=2,U=2,V=5,P=7,B=2,I=4,R=4,D=4,W=4,M=2).get(row[i]);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_actor_placement.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-actor-placement-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_actor_placement import RadarActorPlacementOracle
  oracle=RadarActorPlacementOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
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
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar actor placement sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
