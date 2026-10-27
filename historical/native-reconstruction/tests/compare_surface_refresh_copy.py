#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock software surface copy and zero-plane pixel transfers."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_surface_refresh_copy import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceFill.hpp','src/render/SurfaceClip.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceCopy.hpp','src/render/SurfaceCopyBinding.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/surface_copy_vectors.cpp','tests/surface_refresh_copy_vectors.cpp')
ORIGINAL=('tests/original_surface_refresh_copy.py','tools/verify_surface_refresh_copy.py','tests/compare_surface_refresh_copy.py','tests/test_surface_refresh_copy.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_zero_mode_refresh_copy=True,finish_marks_supplied=True,complete_copy_parent=True,actual_clip_lock_blitters=True,zero_alpha_depth_profile=True,ordered_pixel_and_lock_stores=True,stock_surface_association_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Surface refresh copy input/evidence differs')
import compare_surface_copy as base
def command(f=None):return 'J '+base.command(f)[2:]
def parse(cmd):
 require(cmd.startswith('J '));return base.parse('C '+cmd[2:])
def scenarios():
 for same in (0,1):
  for words in (0,1):
   for bpp in (1,2,3,4):
    for sourceBpp in (1,2):
     for off in (256,257,258,259):
      for dw,dh,sw,sh in ((16,12,16,12),(5,2,13,4),(13,4,5,2),(0,3,5,2),(-1,3,5,2)):
       yield 'refresh_stock_copy_shared_geometry_pixels_and_locks',command([same,words,dw,dh,bpp,off,2147483647,1,sw,sh,sourceBpp,off,-2147483648,1,0,0,1,1,0,0,1,1,0,1])
 for nullOwner in (0,1):
  f=base.parse(base.command());f[5+6*nullOwner]=0;f[7+6*nullOwner]=0
  yield 'refresh_continues_to_finish_after_failed_copy_lock',command(f)
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>=7 and row[-7]=='F' and row.count('F')==1)
 base.validate_row(base.command(f),row[:-7]+row[-6:])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_surface_refresh_copy.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_surface_refresh_copy import SurfaceRefreshCopyOracle
  oracle=SurfaceRefreshCopyOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x774f00','0x434ae0','0x434b40','0x7753b0','0x775190','0x41fdf0','0x775a60','0x775ab0','0x634030','supplied_6324A0')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Surface refresh copy sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
