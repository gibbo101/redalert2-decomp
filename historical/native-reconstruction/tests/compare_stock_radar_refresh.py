#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual stock actor C0/CC and alliance below complete copy/mark refresh."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_stock_radar_refresh import verify
import compare_surface_refresh_marks as base
NATIVE=('CMakeLists.txt','src/render/SurfaceFill.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceMarkPixels.hpp','src/render/SurfaceClip.hpp','src/render/SurfaceCopy.hpp','src/render/SurfaceCopyBinding.hpp','src/render/SurfaceRefreshPixels.hpp','src/render/ActorRadarColor.hpp','src/render/UnitTypeVisibility.hpp','src/render/UnitTypeVisibility.cpp','src/sim/Facing.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/surface_refresh_marks_vectors.cpp','tests/stock_radar_refresh_vectors.cpp')
ORIGINAL=('tests/original_stock_radar_refresh.py','tools/verify_stock_radar_refresh.py','tests/compare_stock_radar_refresh.py','tests/test_stock_radar_refresh.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_stock_pixel_mark_join=True,complete_zero_mode_parent_join=True,actual_stock_lock_bpp_pitch_width_unlock=True,actual_copy_clip_lock_blitters=True,zero_alpha_depth_profile=True,actual_stock_actor_C0_CC_and_alliance=True,resolver_supplied=True,initial_owners_and_palettes_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Stock radar refresh input/evidence differs')
import compare_surface_copy_mark_pixels as refresh_base
def command(f=None):
 if f is None:f=refresh_base.parse(refresh_base.command())+[1,-1,2,0,0]
 return 'V '+' '.join(map(str,f))
def parse(cmd):
 t=cmd.split();require(len(t)==23 and t[0]=='V');f=refresh_base.parse('X '+' '.join(t[1:18]))+list(map(int,t[18:]));require(all(-1<=x<=2 for x in f[17:19]) and 0<=f[19]<=3 and 0<=f[20]<2**32 and 0<=f[21]<=15);return f
def scenarios():
 for i,(label,cmd) in enumerate(refresh_base.scenarios()):
  f=refresh_base.parse(cmd)+[(-1,0,1,2)[i%4],(-1,0,1,2)[i//4%4],i//16%4,(0,1,2,4,0xffffffff)[i%5],i%16]
  yield 'stock_actor_'+label,command(f)
 # Ensure both classes, null/current/alternate returns, and repeated late probes
 # are exercised beneath a complete parent with ordinary positive dimensions.
 for kind in (0,1,2,3):
  for current in (-1,0,1,2):
   for alternate in (-1,0,1,2):
    for mutation in (0,1,2,4,8,15):
     f=refresh_base.parse(refresh_base.command());f[0]=1;f[4]=255;yield 'complete_parent_stock_class_and_late_color_fields',command(f+[current,alternate,kind,2,mutation])
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>21 and row[-21]=='Y');y=list(map(int,row[-20:]));require(-1<=y[0]<=2 and y[1] in (0,1))
 for i in range(4):k=2+i*3;require(y[k] in (0,1) and 0<=y[k+1]<=255 and -1<=y[k+2]<=2)
 for i in range(3):k=14+i*2;require(-2**31<=y[k]<2**31 and 0<=y[k+1]<2**32)
 filtered=[];i=0
 while i<len(row)-21:
  if row[i]=='J':
   require(i+5<=len(row)-21);actor,owner,current,result=map(int,row[i+1:i+5]);require(0<=actor<4 and 0<=owner<3 and -1<=current<3 and result in (0,1));i+=5
  else:filtered.append(row[i]);i+=1
 refresh_base.validate_row(refresh_base.command(f[:17]),filtered)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_stock_radar_refresh.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_stock_radar_refresh import StockRadarRefreshOracle
  oracle=StockRadarRefreshOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(not oracle.counts.get('supplied_C0',0) and not oracle.counts.get('supplied_CC',0));require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x6324a0','0x634030','0x411290','0x4112c0','0x4112d0','0x774220','0x411370','0x4112f0','0x4113b0','0x4113c0','0x774f00','0x434ae0','0x434b40','0x7753b0','0x775a60','0x775ab0','0x775190','0x41fdf0','0x41b410','0x509270','0x41b2e0','0x4e5540','supplied_663D30')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Stock radar refresh sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
