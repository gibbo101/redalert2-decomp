#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Original actor marker insertion/removal and complete stock children with explicit original-answer reuse."""
import argparse,json,platform,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_marker_buckets import verify
NATIVE=('src/render/RadarMarkerBuckets.hpp','src/render/RadarMarkerPlacement.hpp','src/render/RadarShapeBuckets.hpp','src/render/RadarProjection.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/render/SurfaceCopy.hpp','src/render/SurfaceClip.hpp','src/sim/OriginalMath.hpp','tests/radar_marker_buckets_vectors.cpp')
ORIGINAL=('tests/original_radar_marker_buckets.py','tools/verify_radar_marker_buckets.py','tests/compare_radar_marker_buckets.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_radar_marker_buckets.py')
FLAGS=dict(complete_marker_insert_and_remove=True,actual_stock_marker_vectors_and_CRT_move=True,actual_dirty_producer_and_point_resize=True,actual_stock_geometry_and_actor_kinds=True,heap_initial_records_and_mutation_probes_supplied=True,production_scheduling=False)
def require(v):
 if not v:raise ValueError('Marker bucket input/evidence differs')
def command(**kw):
 d=dict(mode=0,x=2,y=1,w=32,h=24,count=0,capacity=4,growth=10,owns=1,valid=1,present=1,local=1,failed=0,dirtyFailed=0,actor=1,slot=-1,mutation=0,repeats=2,requested=6)
 require(not set(kw)-set(d));d.update(kw);return 'B '+' '.join(map(str,d.values()))
def parse(cmd):
 t=cmd.split();require(len(t)==20 and t[0]=='B');f=list(map(int,t[1:]));mode,x,y,w,h,count,capacity,growth,owns,valid,present,local,failed,dirtyFailed,actor,slot,mutation,repeats,requested=f
 require(0<=mode<=5 and all(-2**31<=v<2**31 for v in (x,y)) and -1<=w<=64 and -1<=h<=64 and 0<=count<=capacity<=8 and -2<=growth<=16 and 0<=owns<=255 and 0<=valid<=255 and present in (0,1) and 0<=local<=7 and failed in (0,1) and dirtyFailed in (0,1) and 0<=actor<=2 and -1<=slot<8 and 0<=mutation<=3 and 1<=repeats<=3 and 0<=requested<=16 and (present or capacity==count==0));return f
def scenarios():
 for count,local,failed,dirtyFailed,actor in itertools.product((0,3,4),(0,1,2,7),(0,1),(0,1),(0,1,2)):
  yield 'prepend_append_duplicate_failed_growth_and_shared_dirty',command(count=count,local=local,failed=failed,dirtyFailed=dirtyFailed,actor=actor)
 for x,y,actor,w,h in ((-1,1,0,32,24),(32,24,0,32,24),(-2147483648,2147483647,0,32,24),(-1,-1,2,32,24),(32,24,2,32,24),(0,0,0,0,0),(0,0,0,-1,-1),(63,63,1,64,64)):
  yield 'offscreen_clamp_actor_stores_building_bypass_and_degenerate_rect',command(x=x,y=y,actor=actor,w=w,h=h)
 for mode,owns,growth,valid in itertools.product((0,1,2),(0,255),(-1,0,3),(0,255)):
  yield 'external_full_vector_policy_find_ignores_valid_and_complete_cycles',command(mode=mode,count=4,owns=owns,growth=growth,valid=valid,slot=1 if mode==1 else -1)
 for slot,valid in itertools.product(range(8),(0,255)):
  yield 'remove_first_middle_last_with_four_word_tails',command(mode=1,count=8,capacity=8,slot=slot,valid=valid)
 for mode,capacity,count,owns,present,failed,requested in itertools.product((3,4),(0,4),(0,4),(0,255),(0,1),(0,1),(0,2,6)):
  if count>capacity or not present and capacity:continue
  yield 'complete_stock_resize_clear_shrink_capacity_tails_and_failure',command(mode=mode,capacity=capacity,count=count,owns=owns,present=present,failed=failed,requested=requested,repeats=1)
 for slot,valid in itertools.product((-1,0,1,3),(0,255)):
  yield 'actual_find_ignores_valid_and_trailing_word',command(mode=5,count=4,slot=slot,valid=valid)
 for mutation,actor,x,y in itertools.product((1,2,3),(0,2),(-1,3),(1,30)):
  yield 'late_surface_current_House_and_owner_rereads',command(mutation=mutation,actor=actor,x=x,y=y)
 for mode in (0,2):yield 'new_empty_bucket_null_backing',command(mode=mode,count=0,capacity=0,present=0,repeats=3)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and row.count('R')==row.count('H')==1);at=row.index('R');end=row.index('H');require(end-at==19);list(map(int,row[at+1:end]));i=0
 while i<at:
  n=dict(I=2,T=2,G=2,W=3,Y=3,K=3,Q=3,O=4,F=5,f=4,P=4,p=5,A=3,a=3,D=2,d=2,b=3,S=2,V=7).get(row[i]);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
 pos=end+1;count=int(row[pos]);pos+=1;require(count>=1);list(map(int,row[pos:pos+count]));pos+=count;count=int(row[pos]);pos+=1;require(len(row)-pos==count);list(map(int,row[pos:]))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_marker_buckets.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-marker-buckets-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_marker_buckets import RadarMarkerBucketsOracle
  oracle=RadarMarkerBucketsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  roots=sum(parse(c)[17]*(8 if parse(c)[0]==2 else 1) for c in commands)
  require(oracle.audit_calls==roots and all(oracle.counts[hex(a)]>0 for a in (0x631910,0x631af0,0x632620,0x634e40,0x634bc0,0x634f50,0x783290)) and oracle.counts['marker_allocations']>0 and oracle.counts['marker_releases']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar marker bucket sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
