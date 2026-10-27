#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete6324A0 marks, standalone and joined to zero-mode634030."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_surface_refresh_marks import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceRefresh.hpp','src/render/SurfaceRefreshMarks.hpp','tests/surface_refresh_marks_vectors.cpp')
ORIGINAL=('tests/original_surface_refresh_marks.py','tools/verify_surface_refresh_marks.py','tests/compare_surface_refresh_marks.py','tests/test_surface_refresh_marks.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_mark_rebuild=True,complete_zero_mode_parent_join=True,actual_stock_geometry_getters=True,actor_virtuals_resolver_copy_pixel_supplied=True,initial_owners_and_palettes_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Surface marks input/evidence differs')
def command(f=None):return 'M '+' '.join(map(str,f if f is not None else [1,8,4,2,0,1,2,0,0,0,4,0,1,0]))
def parse(cmd):
 t=cmd.split();require(len(t)==15 and t[0]=='M');f=list(map(int,t[1:]));require(f[0] in (0,1) and (-16<=f[1]<=16 or f[1]==2147483647) and -16<=f[2]<=16 and -1<=f[3]<=4 and 0<=f[4]<=255 and f[5] in (0,1) and 0<=f[6]<=2 and 0<=f[7]<=9 and 0<=f[8]<=511 and 0<=f[9]<=4 and -1<=f[10]<=4 and 0<=f[11]<=255 and 0<=f[12]<=7 and 0<=f[13]<=2);return f
def scenarios():
 for join in (0,1):
  for stage in range(10):
   for mask in (0,1,2,4,8,16,32,64,128,256,511):
    for path in (0,1,2):
     f=parse(command());f[0]=join;f[4:7]=[(0,1,255)[path],int(path!=1),2];f[7:9]=[stage,mask];yield 'saved_buckets_backing_actor_surface_and_late_owners',command(f)
 for join in (0,1):
  for fmt in (-1,0,1,2,3,4):
   for index in (0,1,7):
    for owner in range(3):
     f=parse(command());f[0]=join;f[3]=fmt;f[12:14]=[index,owner];yield 'exact_byte_or_little_endian_word_color_index',command(f)
 for join in (0,1):
  for width,height in ((-8,1),(-1,8),(0,0),(0,8),(1,-8),(-7,1),(8,0),(8,1),(8,4),(16,8)):
   f=parse(command());f[0:3]=[join,width,height];yield 'wrapped_geometry_and_signed_clear_division',command(f)
  for count in (-1,0,1,2,4):
   for layout in (0,1,3,4):
    for seed in (0,1,127,255):
     f=parse(command());f[0]=join;f[9:12]=[layout,count,seed];yield 'duplicate_cross_bucket_negative_index_and_padding',command(f)
  f=parse(command());f[0:3]=[join,2147483647,2];f[9:11]=[2,1];yield 'wrapped_product_and_negative_arithmetic_bit_offset',command(f)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list));i=0
 def take(n):
  nonlocal i
  require(i+n<=len(row));v=list(map(int,row[i:i+n]));i+=n;require(all(-2**31<=x<2**32 for x in v));return v
 while i<len(row):
  tag=row[i];i+=1
  if tag in ('W','H'):v=take(2);require(v[0] in (0,1))
  elif tag=='G':v=take(3);require(v[0] in (0,1))
  elif tag=='B':v=take(4);require(v[0] in (0,1) and 0<=v[1]<64 and v[2] in (1,4) and v[1]+v[2]<=64 and 0<=v[3]<2**(8*v[2]))
  elif tag=='C':v=take(12);require(v[0] in (0,1) and v[5] in (0,1) and v[-2:]==[0,1])
  elif tag=='A':v=take(2);require(0<=v[0]<4 and 0<=v[1]<=255)
  elif tag=='O':v=take(3);require(0<=v[0]<4 and v[1]==0 and -1<=v[2]<=2)
  elif tag=='D':require(take(2)==[1,1])
  elif tag=='P':v=take(5);require(v[0] in (0,1) and 0<=v[1]<16 and 0<=v[4]<=65535)
  elif tag=='R':
   require(all(v in (0,1) for v in take(5)));require(all(0<=v<=255 for v in take(128)));v=take(48);require(all(0<=v[k]<4 for k in range(0,48,3)));require(all(0<=v<=2 for v in take(4)));v=take(2);require(-1<=v[0]<=4 and v[1] in (0,4));v=take(6);require(all(v[k] in (0,1) and 0<=v[k+1]<=7 for k in (0,2,4)));require(i==len(row));return
  else:raise ValueError('Unexpected mark trace')
 raise ValueError('Missing mark final state')
def identities(a):
 paths=python_closure(ROOT/'tests/compare_surface_refresh_marks.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_surface_refresh_marks import SurfaceRefreshMarksOracle
  oracle=SurfaceRefreshMarksOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x6324a0','0x634030','0x411290','0x4112c0','0x4112d0','supplied_copy8','supplied_C0','supplied_CC','supplied_663D30','supplied_pixel24')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Surface refresh marks sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
