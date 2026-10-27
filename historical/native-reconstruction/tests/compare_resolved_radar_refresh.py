#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual stock actor and scheme resolver below complete copy/mark refresh."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_resolved_radar_refresh import verify
import compare_surface_refresh_marks as base
NATIVE=('CMakeLists.txt','src/render/SurfaceFill.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceMarkPixels.hpp','src/render/SurfaceClip.hpp','src/render/SurfaceCopy.hpp','src/render/SurfaceCopyBinding.hpp','src/render/SurfaceRefreshPixels.hpp','src/render/ActorRadarColor.hpp','src/render/SchemeResolver.hpp','src/sim/StringLookup.hpp','src/render/UnitTypeVisibility.hpp','src/render/UnitTypeVisibility.cpp','src/sim/Facing.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/surface_refresh_marks_vectors.cpp','tests/resolved_radar_refresh_vectors.cpp')
ORIGINAL=('tests/original_resolved_radar_refresh.py','tools/verify_resolved_radar_refresh.py','tests/compare_resolved_radar_refresh.py','tests/test_resolved_radar_refresh.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_stock_pixel_mark_join=True,complete_zero_mode_parent_join=True,actual_stock_lock_bpp_pitch_width_unlock=True,actual_copy_clip_lock_blitters=True,zero_alpha_depth_profile=True,actual_stock_actor_C0_CC_and_alliance=True,actual_scheme_resolver_and_locale_zero_CRT=True,initial_owners_and_palettes_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Resolved radar refresh input/evidence differs')
import compare_stock_radar_refresh as refresh_base
def command(f=None):
 if f is None:f=refresh_base.parse(refresh_base.command())+[0,0,0]
 return 'L '+' '.join(map(str,f))
def parse(cmd):
 t=cmd.split();require(len(t)==26 and t[0]=='L');f=refresh_base.parse('V '+' '.join(t[1:23]))+list(map(int,t[23:]));require(f[22] in (0,1) and 0<=f[23]<3 and 0<=f[24]<64 and (f[23]==0 or not f[24]&1) and (f[23]!=0 or not f[24]&8));return f
def safe_mask(at,mask):return mask&(~8 if at==0 else ~1)
def scenarios():
 for i,(label,cmd) in enumerate(refresh_base.scenarios()):yield 'resolved_'+label,command(refresh_base.parse(cmd)+[i%2,i%3,safe_mask(i%3,i%64)])
 for pattern in (0,1):
  for at in range(3):
   for mask in (0,1,2,4,7,8,16,32,56,63):
    for join in (0,1):
     f=refresh_base.parse(refresh_base.command());f[0]=join;f[4]=255;f[19]=1;yield 'actual_Building_null_CC_and_live_scheme_registry',command(f+[pattern,at,safe_mask(at,mask)])
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>9 and row[-9]=='Q');q=list(map(int,row[-8:]));require(q[0]==3 and q[1] in (0,1) and all(x in (0,1) for x in q[2:5]) and q[5:]==[0,q[6],1] and q[6] in (-1,1));filtered=[];i=0
 while i<len(row)-9:
  if row[i] in ('T','U'):
   tag=row[i];require(i+4<=len(row)-9);at,scheme,value=map(int,row[i+1:i+4]);require(0<=at<3 and 0<=scheme<3 and value in (-1,0,1));i+=4
  elif row[i]=='K':require(i+2<=len(row)-9 and 0<=int(row[i+1])<3);filtered+=['D','1','1'];i+=2
  else:filtered.append(row[i]);i+=1
 refresh_base.validate_row(refresh_base.command(f[:22]),filtered)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_resolved_radar_refresh.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_resolved_radar_refresh import ResolvedRadarRefreshOracle
  oracle=ResolvedRadarRefreshOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(not oracle.counts.get('supplied_C0',0) and not oracle.counts.get('supplied_CC',0) and not oracle.counts.get('supplied_663D30',0));require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x6324a0','0x634030','0x411290','0x4112c0','0x4112d0','0x774220','0x411370','0x4112f0','0x4113b0','0x4113c0','0x774f00','0x434ae0','0x434b40','0x7753b0','0x775a60','0x775ab0','0x775190','0x41fdf0','0x41b410','0x509270','0x41b2e0','0x4e5540','0x663d30','0x781f20')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Resolved radar refresh sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
