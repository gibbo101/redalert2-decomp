#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original634030 refresh, saved identities and ordered supplied effects."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_surface_refresh import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceRefresh.hpp','tests/surface_refresh_vectors.cpp')
ORIGINAL=('tests/original_surface_refresh.py','tools/verify_surface_refresh.py','tests/compare_surface_refresh.py','tests/test_surface_refresh.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_surface_refresh_parent=True,actual_stock_geometry_getters=True,copy_and_pixel_finish_effects_supplied=True,initial_associations_and_scratch_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Surface refresh input/evidence differs')
def command(f=None):return 'R '+' '.join(map(str,f if f is not None else [0,1,3,2,2,3,0,0,0,0,0,7]))
def parse(cmd):
 t=cmd.split();require(len(t)==13 and t[0]=='R');f=list(map(int,t[1:]));require(-2**31<=f[0]<2**31 and f[1] in (0,1) and all(-16<=v<=8 for v in f[2:6]) and 0<=f[6]<=6 and 0<=f[7]<=63 and all(0<=v<=3 for v in f[8:10]) and f[10] in (0,1) and 0<=f[11]<=1000);return f
def scenarios():
 for mode in (0,1,-1,-2**31):
  for stock in (0,1):
   for same in (0,1):
    for stage in range(7):
     for mask in (0,1,2,4,8,16,32,63):
      yield 'saved_late_surface_table_slot_dimensions_and_mode',command([mode,stock,3,2,2,3,stage,mask,0,0,same,7])
 for r1 in range(4):
  for r2 in range(4):
   for same in (0,1):
    yield 'returned_rect_identity_null_alias_and_retained_scratch',command([0,0,3,2,2,3,1,63,r1,r2,same,99])
 for w in (-16,-1,0,1,2,7,8):
  for h in (-16,-1,0,1,3,8):
   for stock in (0,1):
    yield 'signed_dimensions_and_Y_outer_X_inner',command([255,stock,w,h,2,3,0,0,0,0,0,1000])
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list));i=0
 def take(n):
  nonlocal i
  require(i+n<=len(row));v=list(map(int,row[i:i+n]));i+=n;require(all(-2**31<=x<2**32 for x in v));return v
 def rect():
  v=take(1)[0];require(v in (0,1,2,3))
  if v:take(4)
 while i<len(row):
  tag=row[i];i+=1
  if tag=='G':v=take(2);require(v[0] in (0,1) and 0<=v[1]<4);rect()
  elif tag=='O':rect()
  elif tag in ('W','H'):v=take(3);require(v[0] in (0,1) and 0<=v[1]<4)
  elif tag=='C':v=take(2);require(0<=v[0]<=2 and 0<=v[1]<4);rect();require(0<=take(1)[0]<4);rect();require(take(2)==[0,1])
  elif tag=='F':pass
  elif tag=='P':rect()
  elif tag=='R':
   v=take(4);require(0<=v[1]<4 and 0<=v[2]<4 and v[3] in (0,1));v=take(12);require(all(v[k] in (0,1) for k in (0,3,6,9)))
   for _ in range(3):rect()
   require(i==len(row));return
  else:raise ValueError('Unexpected refresh trace')
 raise ValueError('Missing refresh final state')
def identities(a):
 paths=python_closure(ROOT/'tests/compare_surface_refresh.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_surface_refresh import SurfaceRefreshOracle
  oracle=SurfaceRefreshOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x634030','0x411290','0x4112c0','0x4112d0','supplied_copy8','supplied_632000','supplied_6324A0')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Surface refresh sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
