#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Marker coordinate projection and dirty-point queue with explicit original-answer reuse."""
import argparse,json,platform,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_marker_placement import verify
NATIVE=('src/render/RadarMarkerPlacement.hpp','src/render/RadarShapeBuckets.hpp','src/render/RadarProjection.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/radar_marker_placement_vectors.cpp')
ORIGINAL=('tests/original_radar_marker_placement.py','tools/verify_radar_marker_placement.py','tests/compare_radar_marker_placement.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_radar_marker_placement.py')
FLAGS=dict(complete_coordinate_and_dirty_helpers=True,actual_stock_getters_resize_and_FTOL=True,original_FP_53_bit_toward_zero=True,heap_and_initial_records_supplied=True,actor_bucket_insertion_and_production_scheduling=False)
def require(v):
 if not v:raise ValueError('Marker input/evidence differs')
def command(**kw):
 d=dict(mode=0,bits=1056964608,x=14784,y=22976,ox=80,oy=81,w=64,h=48,clamp=0,count=0,capacity=4,growth=10,owns=1,present=1,failed=0,repeats=1,step=0,alias=0,mutation=0)
 require(not set(kw)-set(d));d.update(kw);return 'M '+' '.join(map(str,d.values()))
def parse(cmd):
 t=cmd.split();require(len(t)==20 and t[0]=='M');f=list(map(int,t[1:]));mode,bits,x,y,ox,oy,w,h,clamp,count,capacity,growth,owns,present,failed,repeats,step,alias,mutation=f
 require(mode in (0,1) and 0<=bits<2**32 and all(-2**31<=v<2**31 for v in (x,y,ox,oy,w,h,growth,step)) and 0<=clamp<=255 and 0<=owns<=255 and present in (0,1) and failed in (0,1) and 1<=repeats<=4 and alias in (0,1) and 0<=mutation<=3 and 0<=count<=capacity<=16)
 if mode:require(-2<=x<=65 and -2<=y<=65 and -2<=w<=64 and -2<=h<=64 and step in (0,1) and (present or capacity==count==0) and -2<=growth<=16)
 return f
def scenarios():
 for bits,clamp,alias in itertools.product((0,1,1048576000,1056964608,1057132380,1065353216,1069547520,3212836864,2139095040,2143289344),(0,1,128,255),(0,1)):
  yield 'world_coordinates_raw_clamp_and_alias',command(bits=bits,clamp=clamp,alias=alias)
 for x,y,ox,oy in ((-1,0,0,0),(255,256,0,0),(256,-256,0,0),(-2147483648,2147483647,2147483647,-2147483648),(2147483647,-2147483648,-1,1),(14784,22976,80,81)):
  for w,h,clamp in itertools.product((0,-1,64),(0,-1,48),(0,255)):
   yield 'wrapped_projection_and_sequential_degenerate_clamp',command(x=x,y=y,ox=ox,oy=oy,w=w,h=h,clamp=clamp)
 for capacity,count,owns,growth,failed,step in itertools.product((0,4),(0,4),(0,255),(-1,0,3),(0,1),(0,1)):
  if count>capacity:continue
  yield 'dirty_unique_duplicate_growth_failure_and_capacity_tails',command(mode=1,x=2,y=1,w=8,h=6,capacity=capacity,count=count,owns=owns,growth=growth,failed=failed,step=step,repeats=4,present=int(capacity!=0))
 for x,y,w,h in ((-1,1,8,6),(8,1,8,6),(1,-1,8,6),(1,6,8,6),(0,0,0,0),(0,0,-1,6),(7,5,8,6),(63,63,64,64)):
  yield 'out_of_bounds_short_circuit_and_bitmap_edges',command(mode=1,x=x,y=y,w=w,h=h,repeats=2)
 for mutation in (1,2,3):
  yield 'late_surface_and_point_rereads',command(mode=1,x=3,y=2,w=8,h=6,repeats=2,mutation=mutation)
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and row.count('R')==1);at=row.index('R');list(map(int,row[at+1:]));require(len(row)-at==5 if f[0]==0 else len(row)-at>=12)
 i=0
 while i<at:
  n=dict(I=2,W=3,H=3,F=4,P=5,A=3,D=2,B=3,S=2).get(row[i]);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_marker_placement.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-marker-placement-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_marker_placement import RadarMarkerPlacementOracle
  oracle=RadarMarkerPlacementOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  roots=sum(1 if parse(c)[0]==0 else parse(c)[15] for c in commands)
  require(oracle.audit_calls==roots and all(oracle.counts[hex(a)]>0 for a in (0x631ba0,0x632620,0x5b1b00,0x77f110)) and oracle.counts['allocations']>0 and oracle.counts['releases']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar marker helper sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
