#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete nonzero radar pixel and caller with named child services."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_surface_radar_pixels import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceRadarPixel.hpp','src/render/SurfacePixel.hpp','src/render/RadarSurfacePixels.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/surface_radar_pixel_vectors.cpp','tests/surface_radar_pixels_vectors.cpp')
ORIGINAL=('tests/original_surface_radar_pixels.py','tools/verify_surface_radar_pixels.py','tests/compare_surface_radar_pixels.py','tests/test_surface_radar_pixels.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_radar_pixel_parent=True,complete_nonzero_refresh_parent_join=True,actual_stock_geometry_and_FTOL=True,finite_nonzero_scale_53_bit_toward_zero_profile=True,actual_stock_pixel_read_write_join=True,other_named_children_and_initial_records_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Surface radar pixels input/evidence differs')
import compare_surface_radar_pixel as parent
def command(f=None):
 if f is None:f=parent.parse(parent.command())+[2,256,0]
 return 'J '+' '.join(map(str,f))
def parse(cmd):
 t=cmd.split();require(len(t)==37 and t[0]=='J');f=parent.parse('R '+' '.join(t[1:34]))+list(map(int,t[34:]));require(f[33] in (1,2) and 256<=f[34]<=259 and -2**31<=f[35]<2**31);return f
def scenarios():
 for i,(label,cmd) in enumerate(parent.scenarios()):yield 'actual_pixels_'+label,command(parent.parse(cmd)+[1+i%2,256+i%4,(-2**31,-1,0,2**31-1)[i%4]])
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>5 and row[-5]=='Z');require(all(-2**31<=int(x)<2**31 for x in row[-4:-2]) and all(len(x)==64 and all(c in '0123456789abcdef' for c in x) for x in row[-2:]));filtered=[];i=0
 while i<len(row)-5:
  if row[i]=='E':require(i+2<=len(row)-5 and 0<=int(row[i+1])<=65535);i+=2
  elif row[i]=='K':require(i+3<=len(row)-5 and int(row[i+1]) in (0,1) and -2**31<=int(row[i+2])<2**31);i+=3
  elif row[i]=='N':
   require(i+5<=len(row)-5);surface,offset,n,value=map(int,row[i+1:i+5]);require(surface in (0,1) and n in (1,2) and 0<=offset<=2048-n and 0<=value<2**(8*n));i+=5
  else:filtered.append(row[i]);i+=1
 parent.validate_row(parent.command(f[:33]),filtered)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_surface_radar_pixels.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_surface_radar_pixels import SurfaceRadarPixelsOracle
  oracle=SurfaceRadarPixelsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(not oracle.counts.get('supplied_get28',0) and not oracle.counts.get('supplied_set24',0));require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x632000','0x634030','0x77f110','supplied_floor','supplied_discovery0','supplied_discovery1','supplied_type80','supplied_local','supplied_alliedObject','supplied_C0','supplied_CC','supplied_resolver','0x7741d0','0x774220','0x411370','0x4112f0','0x4113b0','0x4113c0')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Surface radar pixels sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
