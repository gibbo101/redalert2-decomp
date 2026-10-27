#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original stock pixel reader and ordinary lock/format/pitch chain."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_surface_get_pixel import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceFill.hpp','src/render/SurfacePixel.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/surface_get_pixel_vectors.cpp')
ORIGINAL=('tests/original_surface_get_pixel.py','tools/verify_surface_get_pixel.py','tests/compare_surface_get_pixel.py','tests/test_surface_get_pixel.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_stock_pixel_reader=True,actual_lock_bpp_pitch_width_unlock=True,no_clipping_and_wrapped_addressing=True,null_lock_no_unlock=True,allocation_and_geometry_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Surface get pixel input/evidence differs')
def command(f=None):return 'G '+' '.join(map(str,f if f is not None else [7,3,2,256,0,1,2,0x12345678,1,0]))
def parse(cmd):
 t=cmd.split();require(len(t)==11 and t[0]=='G');f=list(map(int,t[1:]));require((-16<=f[0]<=16 or f[0]==2147483647) and -16<=f[1]<=16 and -3<=f[2]<=4 and 0<=f[3]<=259 and all(-2**31<=f[k]<2**31 for k in (4,5,6)) and 0<=f[7]<2**32 and f[8] in (0,1) and f[9] in (0,1));require(f[8] or f[3]==f[5]==f[6]==0);return f
def scenarios():
 for bpp in (-3,-1,0,1,2,3,4):
  for offset in (256,257,258,259):
   for words in (0,1):
    for color in (0,0x12345678,0xffffffff):yield 'exact_format_branch_upper_color_alignment_and_numeric_words',command([7,3,bpp,offset,0,1,2,color,1,words])
 for x,y in ((-8,-8),(-1,0),(0,-1),(7,3),(0,3),(8,0),(0,0),(1,1)):
  for bpp in (1,2,3,4):
   for words in (0,1):yield 'no_clipping_and_borrowed_prefix',command([7,3,bpp,256,0,x,y,0xdeadbeef,1,words])
 for lock in (-2**31,-1,0,2**31-1):
  for offset in (256,257):yield 'wrapped_lock_stores',command([7,3,2,offset,lock,0,0,0xffff,1,0])
 for bpp in (-3,-1,0,1,2,3,4):
  for lock in (-2**31,-1,0,2**31-1):
   for words in (0,1):yield 'actual_null_lock_retains_increment_and_skips_unlock',command([7,3,bpp,0,lock,0,0,0xdeadbeef,0,words])
 for bpp in (1,2):
  for words in (0,1):yield 'wrapped_coordinate_and_pitch_products',command([2147483647,2,bpp,256,0,2147483647,1,0xdead1234,1,words])
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list));i=0
 while i<len(row):
  tag=row[i];i+=1
  if tag=='L':require(i<len(row) and -2**31<=int(row[i])<2**31);i+=1
  elif tag=='R':require(len(row)-i==3 and 0<=int(row[i])<=65535 and -2**31<=int(row[i+1])<2**31 and len(row[i+2])==64 and all(c in '0123456789abcdef' for c in row[i+2]));return
  else:raise ValueError('Unexpected pixel trace')
 raise ValueError('Missing pixel final state')
def identities(a):
 paths=python_closure(ROOT/'tests/compare_surface_get_pixel.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_surface_get_pixel import SurfaceGetPixelOracle
  oracle=SurfaceGetPixelOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x7741d0','0x411370','0x4112f0','0x4113b0','0x4113c0','0x4112c0')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Surface get pixel sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
