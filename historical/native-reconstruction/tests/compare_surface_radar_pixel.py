#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete nonzero radar pixel and caller with named child services."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_surface_radar_pixel import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceRadarPixel.hpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/surface_radar_pixel_vectors.cpp')
ORIGINAL=('tests/original_surface_radar_pixel.py','tools/verify_surface_radar_pixel.py','tests/compare_surface_radar_pixel.py','tests/test_surface_radar_pixel.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_radar_pixel_parent=True,complete_nonzero_refresh_parent_join=True,actual_stock_geometry_and_FTOL=True,finite_nonzero_scale_53_bit_toward_zero_profile=True,named_children_and_initial_records_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Surface radar pixel input/evidence differs')
def command(f=None):return 'R '+' '.join(map(str,f if f is not None else [0,0,4,3,0,0,0,0,0,1,0,0,3,0,7,0,7,0,-1,-1,3,100,1,0xabcdef,0,0,0,0,0,0,0,0,0]))
def parse(cmd):
 t=cmd.split();require(len(t)==34 and t[0]=='R');f=list(map(int,t[1:]));require(all(-2**31<=x<(2**32 if i==23 else 2**31) for i,x in enumerate(f)) and f[0] in (0,1) and -1<=f[1]<3 and -2<=f[2]<=8 and -2<=f[3]<=8 and 0<=f[6]<7 and 0<=f[10]<=255 and 0<=f[11]<=255 and -1<=f[12]<=3 and 0<=f[13]<=3 and all(0<=x<8 for x in f[14:18]) and -1<=f[18]<3 and 0<=f[23]<2**32 and f[22]!=0 and 0<=f[24]<3 and 0<=f[31]<=12 and 0<=f[32]<65536 and (not f[0] or f[9]!=0) and (not f[32]&32768 or f[31]>=2));return f
def scenarios():
 for parent in (0,1):
  for stage in range(1,13):
   for mask in (0,1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,65535):
    for path in range(5):
     f=parse(command());f[0]=parent;f[10:12]=[(0,1,1,0,0)[path],(0,0,1,1,0)[path]];f[12]=0 if path in (2,3,4) else 3;f[15]=7 if path==1 else 0;f[17]=7 if path==0 else 0;f[31]=stage;f[32]=mask&(~32768 if stage==1 else 65535);yield 'complete_parent_ordered_services_live_owners_and_dirty',command(f)
 for current in (-1,0,2):
  for w,h in ((-2,3),(0,3),(1,1),(4,3),(8,8)):
   for x,y in ((-1,0),(0,-1),(0,0),(1,1),(3,2),(4,3),(2147483647,-2147483648)):
    f=parse(command());f[1:6]=[current,w,h,x,y];yield 'current_and_signed_geometry_rejections',command(f)
 for scale in range(7):
  for ox,oy in ((0,0),(1,-1),(-123,211),(2147483647,-2147483648)):
   for x,y in ((0,0),(1,1),(3,2)):
    f=parse(command());f[4:9]=[x,y,scale,ox,oy];f[12]=0;yield 'x87_projection_signed_word_and_indefinite_conversion',command(f)
 for start,remaining,frame in ((-1,-1,0),(-1,0,0),(-1,1,0),(-1,2,0),(0,3,0),(0,3,1),(0,3,3),(2147483647,5,-2147483648),(-2147483648,2147483647,2147483647)):
  for divisor in (-2147483648,-3,-1,1,2,3,2147483647):
   for owner in (0,1):
    f=parse(command());f[1]=owner;f[19:23]=[start,remaining,frame,divisor];yield 'timer_wrap_signed_division_parity_and_owner_flash',command(f)
 for shifts in range(3):
  for color in (0,1,65535,65536,0xabcdef,0xffffffff):
   for branch in (0,1):
    f=parse(command());f[24]=shifts;f[23]=color;f[12]=0;f[11]=branch;yield 'packed_pixel_and_byte_word_shift_counts',command(f)
 for dirty in ((0,0,0,0),(0,0,1,1),(10,10,2,2),(-2,-3,1,1),(2147483647,-2147483648,1,1),(-2147483648,2147483647,2147483647,2147483647)):
  for sx,sy in ((0,0),(-2,-3),(2147483647,-2147483648)):
   f=parse(command());f[25:31]=[*dirty,sx,sy];yield 'wrapped_dirty_union_and_asymmetric_right_extension',command(f)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list));i=0
 arity={'G':3,'F':3,'H':4,'I':4,'L':2,'T':1,'A':3,'C':2,'O':2,'S':0,'B':1,'V':5,'W':5,'D':2}
 while i<len(row):
  tag=row[i];i+=1
  if tag=='R':
   require(len(row)-i==43);v=list(map(int,row[i:]));require(-1<=v[0]<3 and all(x in (0,1) for x in v[2:7]) and all(-2**31<=x<2**32 for x in v));return
  require(tag in arity and i+arity[tag]<=len(row));v=list(map(int,row[i:i+arity[tag]]));i+=arity[tag];require(all(-2**31<=x<2**32 for x in v))
  if tag=='D':require(0<=v[0]<4)
  if tag in ('G','L','T','C','O'):require(0<=v[0]<(2 if tag=='G' else 3))
  if tag in ('H','I'):require(0<=v[-1]<=255)
  if tag=='A':require(-1<=v[0]<3 and 0<=v[1]<3 and v[2] in (0,1))
  if tag in ('V','W'):require(v[0] in (0,1) and v[1] in (0,1) and 0<=v[-1]<2**32)
 raise ValueError('Missing radar pixel final state')
def identities(a):
 paths=python_closure(ROOT/'tests/compare_surface_radar_pixel.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_surface_radar_pixel import SurfaceRadarPixelOracle
  oracle=SurfaceRadarPixelOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x632000','0x634030','0x77f110','supplied_floor','supplied_discovery0','supplied_discovery1','supplied_type80','supplied_local','supplied_alliedObject','supplied_C0','supplied_CC','supplied_resolver','supplied_get28','supplied_set24')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Surface radar pixel sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
