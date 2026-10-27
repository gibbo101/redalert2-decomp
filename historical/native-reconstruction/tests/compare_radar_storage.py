#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Joined original radar startup with explicit supported original-result reuse."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_storage import verify
NATIVE=('src/render/RadarStorage.hpp','src/render/RadarSurfaceStartup.hpp','src/render/RadarProjection.hpp','src/render/SurfaceStartup.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/render/SurfacePixel.hpp','src/sim/OriginalMath.hpp','tests/radar_storage_vectors.cpp')
ORIGINAL=('tests/original_radar_storage.py','tools/verify_radar_storage.py','tests/compare_radar_storage.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_radar_storage.py')
FLAGS=dict(complete_startup_projection_initializer=True,source_region_alias=True,shared_native_storage=True,terrain_platform_device_clear_destroy_finish_supplied=True,device_lock_copy_unbound=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Radar storage input/evidence differs')
def command(*v):return 'J '+' '.join(map(str,v))
def parse(cmd):
 p=cmd.split();require(len(p)==9 and p[0]=='J');f=list(map(int,p[1:]));w,h,x,y,seed,fmt,forced,repeats=f
 require(1<=w<=32 and 1<=h<=32 and -2**31<=x<2**31 and -2**31<=y<2**31 and 0<=seed<=255 and fmt in (0,1) and 0<=forced<=255 and repeats in (1,2));return f
def scenarios():
 for i,(w,h) in enumerate(((1,1),(8,6),(31,7),(5,32),(32,32),(32,1),(1,32),(7,19))):
  yield 'startup_alias_both_scales_formats_reinitialization',command(w,h,(-2147483648,-9,0,2147483647)[i%4],(2147483647,11,0,-2147483648)[i%4],(i*43+17)&255,i%2,(0,1,2,255)[i%4],2 if i%2 else 1)
def validate_row(cmd,row):
 f=parse(cmd);require(row.count('R')==row.count('I')==f[-1] and row.count('K')==row.count('N')==row.count('U')==f[-1]);i=0
 while i<len(row):
  tag=row[i];n=dict(I=2,R=16,A=2,U=1,Z=2,M=3,S=4,C=6,P=4,B=4,W=2,H=2,K=3,N=1,O=4,D=4,G=2,L=2,X=3,F=2).get(tag)
  # Z with no arguments is startup's finish; projection clear has one zero.
  if tag=='Z' and (i+1==len(row) or row[i+1]=='R'):n=1
  # RGB buffer stores also use C, disambiguated by the next tag position.
  if tag=='C' and i+4<len(row) and row[i+4] in ('C','M','A','U','S','Z'):n=4
  require(n is not None and i+n<=len(row));list(map(int,row[i+1:i+n]));i+=n
  if tag=='R':
   v=list(map(int,row[i-15:i]));require(v[7:9]==f[:2] and v[9:11]==[2,0] and all(0<=d<2**64 for d in v[11:]))
 require(i==len(row))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_storage.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-storage-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_storage import RadarStorageOracle
  oracle=RadarStorageOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  roots=sum(parse(c)[-1] for c in commands)
  require(oracle.counts['startup']==oracle.counts['projection']==oracle.counts['device_initializer']==oracle.audit_calls==roots and oracle.counts['lock']==oracle.counts['unlock']==roots and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar storage sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
