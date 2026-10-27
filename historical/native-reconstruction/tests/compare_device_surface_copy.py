#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Software-source device copy with explicit original-answer reuse."""
import argparse,json,platform,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_device_surface_copy import verify
NATIVE=('src/render/DeviceSurfaceCopy.hpp','src/render/DeviceSurfacePixels.hpp','src/render/SurfaceCopy.hpp','src/render/SurfaceClip.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceStartup.hpp','src/render/SurfaceFill.hpp','src/render/SurfaceRefresh.hpp','tests/device_surface_copy_vectors.cpp')
ORIGINAL=('tests/original_device_surface_copy.py','tools/verify_device_surface_copy.py','tests/compare_device_surface_copy.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_device_surface_copy.py')
FLAGS=dict(complete_device_copy_wrapper=True,complete_software_source_device_copy_path=True,actual_copy_clip_blitters_and_device_destination_locks=True,hardware_source_supported=False,platform_status_restore_lock_unlock_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Device pixel input/evidence differs')
def command(**kw):
 d=dict(enabled=1,secondary=0,count=0,status=0,restore=0,failed=0,bpp=2,width=8,height=6,sw=8,sh=6,sbpp=2,dx=0,dy=0,dw=5,dh=3,sx=0,sy=0,rw=5,rh=3,first=0,second=0)
 require(not set(kw)-set(d));d.update(kw);return 'C '+' '.join(map(str,d.values()))
def parse(cmd):
 t=cmd.split();require(len(t)==23 and t[0]=='C');f=list(map(int,t[1:]))
 require(all(0<=n<=255 for n in f[:2]) and -2**31<=f[2]<2**31 and 0<=f[3]<=3 and f[4] in (0,1) and f[5] in (0,1) and f[6] in (1,2,3) and all(0<=n<=16 for n in f[7:11]) and f[11] in (1,2,3) and all(-2**31<=n<2**31 for n in f[12:20]) and all(0<=n<2**32 for n in f[20:]));return f
def scenarios():
 for (e,s),status,restore,failed,first in itertools.product(((0,0),(1,0),(0,2),(255,1)),range(4),(0,1),(0,1),(0,1,256,257)):
  yield 'enable_recovery_failure_and_raw_transparency_flags',command(enabled=e,secondary=s,status=status,restore=restore,failed=failed,first=first,second=255)
 for count,bpp,sbpp,first in itertools.product((-2147483648,-1,1,2,2147483647),(1,2,3),(1,2,3),(0,1)):
  # Same-sized pitches in this matrix permit extreme depth without entering
  # unsigned area faults. Healthy and recovering nested depth are separate.
  yield 'signed_nested_depth_independent_formats',command(count=count,bpp=bpp,sbpp=sbpp,first=first)
 for count in (1,2):
  yield 'lost_recovery_on_positive_depth',command(count=count,status=3)
 for dx,dy,sx,sy in ((-2,0,0,0),(0,-2,0,0),(0,0,-2,0),(0,0,0,-2),(4,2,1,1),(30,0,0,0),(0,0,30,0)):
  for first,bpp in itertools.product((0,1),(1,2)):
   yield 'clipped_coordinates_and_unequal_regions',command(dx=dx,dy=dy,sx=sx,sy=sy,dw=6,dh=5,rw=4,rh=4,first=first,bpp=bpp,sbpp=bpp)
 for field in ('width','height','sw','sh','dw','dh','rw','rh'):
  yield 'early_nonpositive_dimensions',command(**{field:0})
 for field in ('dw','dh','rw','rh'):
  yield 'early_negative_dimensions',command(**{field:-1})
 for bpp in (1,2):
  yield 'contiguous_full_surface',command(bpp=bpp,sbpp=bpp,dw=8,dh=6,rw=8,rh=6)
def validate_row(cmd,row):
 parse(cmd);require(row[-38]=='R' and row.count('F')==1 and row[-31]=='F' and row[-3]=='P');i=0
 while i<len(row):
  tag=row[i]
  n=dict(Q=5,H=2,T=2,K=3,N=2,O=4,B=4,L=2,S=5,V=2,R=7,F=28,P=3).get(tag);require(n is not None and i+n<=len(row))
  if tag=='Q':require(row[i+2] in ('R','B','P','W','K','U'));list(map(int,[row[i+1],*row[i+3:i+n]]))
  else:list(map(int,row[i+1:i+n]))
  i+=n
 require(i==len(row))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_device_surface_copy.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/device-surface-copy-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_device_surface_copy import DeviceSurfaceCopyOracle
  oracle=DeviceSurfaceCopyOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  roots=len(commands)
  require(oracle.audit_calls==roots and all(oracle.counts[hex(a)]>0 for a in (0x4aaf80,0x4aafd0,0x774f00,0x775190,0x4aac80,0x4aae40,0x4aac60,0x4aac70)) and oracle.counts['restore']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Device surface copy sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
