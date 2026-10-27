#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete radar projection with explicit guarded original-result reuse."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_projection import verify
NATIVE=('src/render/RadarProjection.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/render/SurfacePixel.hpp','src/sim/OriginalMath.hpp','tests/radar_projection_vectors.cpp')
ORIGINAL=('tests/original_radar_projection.py','tools/verify_radar_projection.py','tests/compare_radar_projection.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_radar_projection.py')
FLAGS=dict(complete_projection=True,actual_buffer_constructor_and_stock_lock_and_numeric_children=True,terrain_colors_and_allocation_and_clear_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Radar projection input/evidence differs')
def command(*v):return 'P '+' '.join(map(str,v))
def parse(cmd):
 p=cmd.split();require(len(p)==13 and p[0]=='P');f=list(map(int,p[1:]));w,h,x,y,rw,rh,existing,colors,bitmap,update,seed,fmt=f
 require(1<=w<=32 and 1<=h<=32 and 0<=x<=x+rw<=w and 0<=y<=y+rh<=h and existing in (0,1) and colors in (0,1) and bitmap in (0,1) and 0<=update<=255 and 0<=seed<=255 and fmt in (0,1));return f
def scenarios():
 # Existing7x5 storage exercises downsampling, clamped/empty output and formats.
 for i,(w,h) in enumerate(((1,1),(8,6),(13,9),(14,10),(17,13),(31,29),(32,32))):
  for mask in range(8):
   region=(0,0,w,h) if mask<4 else (min(2,w),min(2,h),min(3,max(w-2,0)),min(2,max(h-2,0)))
   yield 'existing_downsample_and_resource_masks',command(w,h,*region,1,mask&1,(mask>>1)&1,(0,1,255,128)[mask%4],(i*37+mask*13)&255,mask>>2)
 # Complete fresh storage: both scale branches, thin maps, exact/fractional borders.
 for i,(w,h) in enumerate(((1,1),(8,6),(31,7),(5,32),(32,32),(32,1),(1,32),(7,19))):
  yield 'new_storage_scale_and_fractional_edges',command(w,h,0,0,w,h,0,i&1,(i>>1)&1,(0,1,255,128)[i%4],(i*43+17)&255,(i>>2)&1)
 # Degenerate region replacement is conditional on the raw update byte.
 for update in (0,1,255):
  for existing in (0,1):yield 'empty_region_update_gate',command(8,6,1,1,0,0,existing,1,1,update,91,0)
def validate_row(cmd,row):
 f=parse(cmd);require(row.count('R')==1);at=row.index('R');require(len(row)-at==18);v=list(map(int,row[at+1:]));require(v[11:13]==f[:2] and v[13]==0 and all(0<=d<2**64 for d in v[14:]))
 require(v[4:8]==([0,0,*f[:2]] if f[9] and (not f[4] or not f[5]) else f[2:6]));require(row.count('K')==row.count('N')==1 and row.count('Z')==1-f[6] and row.count('U')==int(bool(f[9])))
 i=0
 while i<at:
  tag=row[i];n=dict(A=2,U=1,Z=2,M=3,S=4,C=4,P=4,B=4,W=2,H=2,K=3,N=1).get(tag);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
 require(i==at)
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_projection.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-projection-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_projection import RadarProjectionOracle
  oracle=RadarProjectionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  require(oracle.counts['root']==len(commands) and oracle.audit_calls==len(commands) and oracle.counts['lock']==oracle.counts['unlock']==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar projection sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
