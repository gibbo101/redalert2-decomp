#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete device-surface initializer with explicit original expectation reuse."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_surface_startup import verify
NATIVE=('src/render/SurfaceStartup.hpp','src/render/RadarSurfaceStartup.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','tests/radar_surface_startup_vectors.cpp')
ORIGINAL=('tests/original_radar_surface_startup.py','tools/verify_radar_surface_startup.py','tests/compare_radar_surface_startup.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_radar_surface_startup.py')
FLAGS=dict(complete_radar_startup_parent=True,actual_device_initializer_and_stock_getters=True,projection_and_allocation_device_destruction_clear_finish_supplied=True,shared_native_geometry_owners=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Radar surface startup input/evidence differs')
def command(*v):return 'R '+' '.join(map(str,v))
def parse(cmd):
 p=cmd.split();require(len(p)==13 and p[0]=='R');f=list(map(int,p[1:]));require(all(-2**31<=v<2**31 for v in f[:6]) and 0<=f[6]<16 and 0<=f[7]<=255 and all(v in (0,1) for v in f[8:10]) and all(0<=v<2**32 for v in f[10:]));return f
def scenarios():
 edges=(-2**31,-1,0,1,107,108,109,139,140,141,2**31-1)
 for i in range(176):
  yield 'complete_radar_parent_device_initializer',command((0,-1,1,320)[i%4],(0,-1,1,200)[(i//4)%4],edges[(i//3)%11],edges[(i//7)%11],edges[i%11],edges[(i//11)%11],i%16,(0,1,128,255)[i%4],int(i%5!=0),int(i%3!=0),(0,1,15,16,24,32,0xffffffff)[i%7],(0,0x4000,0x800,0xffffffff)[(i//3)%4])
 for i in range(128):
  yield 'entered_all_old_resource_masks_and_geometry_edges',command(320,200,edges[(i//3)%11],edges[(i//7)%11],edges[i%11],edges[(i//11)%11],i%16,(0,1,128,255)[i%4],int(i%5!=0),int(i%3!=0),(0,1,15,16,24,32,0xffffffff)[i%7],(0,0x4000,0x800,0xffffffff)[(i//3)%4])
def validate_row(cmd,row):
 f=parse(cmd);require(row.count('R')==1);at=row.index('R');require(len(row)-at==14);v=list(map(int,row[at+1:]));require(all(-2**31<=x<2**32 for x in v))
 if f[0]<=0 or f[1]<=0:require(at==0 and v[:4]==[17,19,*f[:2]] and v[4:8]==[6 if f[6]&1 else 0,7 if f[6]&2 else 0,int(bool(f[6]&4)),int(bool(f[6]&8))])
 else:require(v[2:4]==f[4:6] and v[4:8]==[1,5,0,0] and v[8:10]==f[4:6] and row.count('W')==row.count('H')==2 and row.count('B')==row.count('Z')==row.count('L')==1)
 i=0
 while i<at:
  tag=row[i];n=dict(O=4,D=4,A=2,C=6,G=2,M=3,X=3,F=2,B=6,W=2,H=2,L=2,Z=1).get(tag);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
 require(i==at)
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_surface_startup.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-surface-startup-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_surface_startup import RadarSurfaceStartupOracle
  oracle=RadarSurfaceStartupOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  require(oracle.counts['parent']==len(commands) and oracle.audit_calls==len(commands) and oracle.counts['root']==sum(parse(c)[0]>0 and parse(c)[1]>0 for c in commands) and oracle.counts['supplied_create']>0 and oracle.counts['supplied_describe']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar surface startup sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
