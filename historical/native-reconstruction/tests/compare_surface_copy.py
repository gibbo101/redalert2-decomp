#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock software surface copy and zero-plane pixel transfers."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_surface_copy import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceFill.hpp','src/render/SurfaceClip.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceCopy.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/surface_copy_vectors.cpp')
ORIGINAL=('tests/original_surface_copy.py','tools/verify_surface_copy.py','tests/compare_surface_copy.py','tests/test_surface_copy.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_copy_parent=True,actual_clip_lock_blitters=True,zero_alpha_depth_profile=True,ordered_pixel_and_lock_stores=True,stock_surface_association_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Surface copy input/evidence differs')
def command(f=None):return 'C '+' '.join(map(str,f if f is not None else [0,0,16,12,2,256,0,1,16,12,2,256,0,1,0,0,8,8,0,0,8,8,0,1]))
def parse(cmd):
 t=cmd.split();require(len(t)==25 and t[0]=='C');f=list(map(int,t[1:]));require(f[0] in (0,1) and f[1] in (0,1))
 for j in range(2):
  w,h,bpp,off,lock,present=f[2+6*j:8+6*j];require(-4<=w<=96 and -4<=h<=32 and 0<=bpp<=4 and 0<=off<=259 and -2**31<=lock<2**31 and present in (0,1));require(present or off==0)
 require(all(-2**31<=x<2**31 for x in f[14:22]) and all(0<=x<2**32 for x in f[22:]));return f
def scenarios():
 for words in (0,1):
  for bpp in (1,2):
   for flag in (0,1,256,257,0xffffffff):
    for off in (256,257,258,259):
     for same in (0,1):
      for dr,sr in (([0,0,16,8],[0,0,16,8]),([1,2,7,5],[2,1,7,5]),([-2,-1,12,8],[0,0,12,8]),([0,0,12,8],[-2,-1,12,8]),([0,0,4,2],[1,1,7,5]),([14,10,8,8],[1,1,8,8]),([20,0,3,3],[0,0,3,3])):
       yield 'copy_formats_flags_clipping_flat_rows_and_overlap',command([same,words,16,12,bpp,off,0,1,16,12,bpp,off,0,1,*dr,*sr,flag,0xabcdef12])
 # Opaque reverse CRT alignment, tails and small/unrolled/rep dword thresholds.
 for words in (0,1):
  for bpp in (1,2):
   for off in (256,257,258,259):
    for count in range(1,81):
     for delta in (1,3):
      yield 'reverse_opaque_CRT_alignment_count_overlap',command([1,words,96,4,bpp,off,0,1,96,4,bpp,off,0,1,delta,0,count,1,0,0,count,1,0,0])
 for bpp in (0,1,2,3,4):
  for sourceBpp in (0,1,2,3,4):
   for words in (0,1):
    for flag in (0,1):
     yield 'independent_formats_unequal_pitch_source_width',command([0,words,16,12,bpp,256,0,1,13,11,sourceBpp,257,0,1,1,2,4,3,2,1,7,5,flag,0xabcdef12])
 for nullOwner in (0,1):
  for lock in (-2**31,-1,0,2**31-1):
   for flag in (0,1):
    f=[0,0,16,12,2,256,lock,1,16,12,2,256,lock,1,0,0,8,8,0,0,8,8,flag,0xabcdef12];f[5+6*nullOwner]=0;f[7+6*nullOwner]=0
    yield 'null_lock_partial_depth_and_source_failure_cleanup',command(f)
 for lock in (-2**31,-1,0,2**31-1):
  for same in (0,1):
   yield 'wrapped_double_lock_and_unlock_depth',command([same,0,16,12,2,256,lock,1,16,12,2,256,lock,1,0,1,16,8,0,0,16,8,0,0])
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list));i=0
 while i<len(row):
  tag=row[i];i+=1
  if tag=='Q':
   require(i+4<=len(row));require(row[i] in ('0','1') and row[i+1] in 'RBPWKU' and len(row[i+1])==1 and all(-2**31<=int(x)<2**31 for x in row[i+2:i+4]));i+=4
  elif tag=='L':require(i+2<=len(row) and row[i] in ('0','1') and -2**31<=int(row[i+1])<2**31);i+=2
  elif tag=='S':
   require(i+4<=len(row));owner,at,n,v=map(int,row[i:i+4]);require(owner in (0,1) and 0<=at and at+n<=8192 and n in (1,2,4) and 0<=v<2**(n*8));i+=4
  elif tag=='R':
   require(len(row)-i==5 and row[i] in ('0','1') and all(-2**31<=int(row[k])<2**31 for k in (i+1,i+3)) and all(len(row[k])==64 and all(c in '0123456789abcdef' for c in row[k]) for k in (i+2,i+4)));return
  else:raise ValueError('Unexpected copy trace')
 raise ValueError('Missing copy final state')
def identities(a):
 paths=python_closure(ROOT/'tests/compare_surface_copy.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_surface_copy import SurfaceCopyOracle
  oracle=SurfaceCopyOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x774f00','0x434ae0','0x434b40','0x7753b0','0x775190','0x41fdf0','0x775980','0x775b00','0x775a60','0x775ab0','0x775a30','0x775b30','0x775a90','0x775ae0','0x783290')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Surface copy sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
