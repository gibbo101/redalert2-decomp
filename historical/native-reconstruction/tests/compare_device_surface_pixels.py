#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete device Lock/Unlock with explicit original-answer reuse."""
import argparse,json,platform,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_device_surface_pixels import verify
NATIVE=('src/render/DeviceSurfacePixels.hpp','src/render/SurfaceStartup.hpp','src/render/SurfaceFill.hpp','src/render/SurfaceRefresh.hpp','tests/device_surface_pixels_vectors.cpp')
ORIGINAL=('tests/original_device_surface_pixels.py','tools/verify_device_surface_pixels.py','tests/compare_device_surface_pixels.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_device_surface_pixels.py')
FLAGS=dict(complete_device_lock_unlock=True,actual_device_metadata_getters=True,lost_recovery_and_nested_locks=True,platform_status_restore_lock_unlock_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Device pixel input/evidence differs')
def command(**kw):
 d=dict(enabled=1,secondary=0,present=1,count=0,x=1,y=2,status=0,restore=0,failed=0,bits=16,caps=0x2040,pitch=32,offset=128,initialBytes=2,operations='LLUU')
 require(not set(kw)-set(d));d.update(kw);return 'D '+' '.join(map(str,d.values()))
def parse(cmd):
 p=cmd.split();require(len(p)==16 and p[0]=='D');v=list(map(int,p[1:-1]));enabled,secondary,present,count,x,y,status,restore,failed,bits,caps,pitch,offset,initialBytes=v;ops=p[-1]
 require(0<=enabled<=255 and 0<=secondary<=255 and present in (0,1) and all(-2**31<=n<2**31 for n in (count,x,y)) and 0<=status<=3 and restore in (0,1) and failed in (0,1) and all(0<=n<2**32 for n in (bits,caps,initialBytes)) and 0<=pitch<=4096 and 0<=offset<=4096 and 1<=len(ops)<=8 and set(ops)<=set('LU'));return [*v,ops]
def scenarios():
 for (enabled,secondary),count,status,ops in itertools.product(((0,0),(1,0),(0,2),(255,1)),(-2147483648,-1,0,1,2,2147483647),range(4),('L','U','LLUU','ULUL')):
  yield 'raw_gates_signed_nested_counts_and_lost_recovery',command(enabled=enabled,secondary=secondary,count=count,status=status,operations=ops)
 for status,restore,failed in itertools.product(range(4),(0,1),(0,1)):
  for count in (0,2):yield 'platform_failure_and_recovery_tail',command(status=status,restore=restore,failed=failed,count=count,operations='LULU')
 for x,y in ((-1,0),(0,-1),(-2147483648,2147483647),(2147483647,2147483647),(0,0)):
  for status,count in itertools.product((0,3),(0,2)):yield 'negative_after_status_and_wrapped_address',command(x=x,y=y,status=status,count=count,operations='LU')
 for bits,caps in itertools.product((0,1,8,15,16,24,32,0xfffffff9,0xffffffff),(0,0x2040,0x4000,0xffffffff)):
  yield 'descriptor_copy_wrapped_bitcount_and_video',command(bits=bits,caps=caps,initialBytes=0xffffffff,operations='LLUU')
 for enabled,count,ops in ((0,0,'L'),(1,2,'L'),(1,-1,'L'),(1,0,'U'),(1,2,'U')):
  yield 'null_device_cached_or_unentered_paths',command(present=0,enabled=enabled,count=count,operations=ops)
def validate_row(cmd,row):
 f=parse(cmd);require(row.count('I')==row.count('R')==len(f[-1]) and row.count('F')==1);i=0
 while i<len(row):
  n=dict(I=2,R=6,F=28,H=2,T=2,K=3,N=2,O=4,B=4).get(row[i]);require(n is not None and i+n<=len(row));list(map(int,row[i+1:i+n]));i+=n
 require(i==len(row) and row[-28]=='F')
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_device_surface_pixels.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/device-surface-pixels-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_device_surface_pixels import DeviceSurfacePixelsOracle
  oracle=DeviceSurfacePixelsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  roots=sum(len(parse(c)[-1]) for c in commands)
  require(oracle.audit_calls==roots and all(oracle.counts[hex(a)]>0 for a in (0x4aac80,0x4aae40,0x4aac60,0x4aac70)) and oracle.counts['restore']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Device surface pixel sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
