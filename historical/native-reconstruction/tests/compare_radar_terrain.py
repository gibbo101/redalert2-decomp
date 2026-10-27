#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Terrain traversal joined to projection, with guarded original-result reuse."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_terrain import verify
NATIVE=('src/render/RadarTerrain.hpp','src/render/RadarProjection.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/render/SurfacePixel.hpp','src/sim/OriginalMath.hpp','src/assets/TileSweep.hpp','src/assets/TileSweep.cpp','tests/radar_terrain_vectors.cpp')
ORIGINAL=('tests/original_radar_terrain.py','tools/verify_radar_terrain.py','tests/compare_radar_terrain.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_radar_terrain.py')
FLAGS=dict(complete_terrain_parent=True,actual_iterator_reset_and_intersection=True,joined_projection_same_map_and_rgb=True,cell_colors4712C0_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Radar terrain input/evidence differs')
def command(*v):return 'T '+' '.join(map(str,v))
def parse(cmd):
 p=cmd.split();require(len(p)>=14 and p[0]=='T');f=list(map(int,p[1:]));joined,width,origin,minimum,sw,sh,x,y,rw,rh,seed,hole,count=f[:13];require(len(f)==13+count*3 and joined in (0,1) and 2<=width<=8 and -32<=origin<=32 and -64<=minimum<=64 and 1<=sw<=32 and 1<=sh<=32 and 0<=x<=x+rw<=sw and 0<=y<=y+rh<=sh and 0<=seed<=255 and 0<=count<=64 and -1<=hole<count)
 cells=[f[i:i+3] for i in range(13,len(f),3)];require(len({c[0] for c in cells})==count and all(0<=slot<512*512 and -32768<=cx<=32767 and -32768<=cy<=32767 for slot,cx,cy in cells));return [*f[:12],cells]
def cursor_positions(width,count):
 # Authored iterator input slots. Original and native traversal execute separately;
 # this is not a native input producer or an expectation implementation.
 x,y,left=1,width,width-1;positions=[]
 for _ in range(count):
  positions.append((y*512+x,x,y))
  if left:x+=1;y-=1;left-=1
  else:
   oldX,oldY=x,y;x,y=oldY,oldX
   if (oldY-width+oldX-1)&1:y+=1;left=width-1
   else:x+=1;left=width-2
 return positions
def scenarios():
 for width in (2,3,5,8):
  cells=cursor_positions(width,12)
  for joined in (0,1):
   for variant in range(10):
    origin=(0,width//2,width)[variant%3];minimum=(0,width+1,width*2+3)[variant%3]
    region=((0,0,16,16),(1,0,1,16),(2,1,5,7),(0,0,0,0),(0,2,16,1))[variant%5]
    data=cells if variant!=9 else [(slot,-32768 if i%2 else 32767,y) for i,(slot,x,y) in enumerate(cells)]
    yield 'complete_terrain_and_shared_projection',command(joined,width,origin,minimum,16,16,*region,(variant*43+width)&255,(-1,0,5)[variant%3],len(data),*[v for row in data for v in row])
 # Explicit left-clipped, right-clipped and full two-pixel cases on the same Cell.
 for joined in (0,1):
  for x,rw in ((1,4),(0,1),(0,4)):
   yield 'both_clipped_edges_and_two_pixel_store',command(joined,3,0,0,8,8,x,0,rw,8,91,-1,1,1537,1,3)
 # No residents is a successful terminal iterator call, with no color dependency.
 for joined in (0,1):yield 'empty_map_terminal_iterator',command(joined,3,0,0,8,6,0,0,8,6,37,-1,0)
def validate_row(cmd,row):
 f=parse(cmd);require(row.count('R')==1);at=row.index('R');require(len(row)-at==17);v=list(map(int,row[at+1:]));require(v[12]==0 and all(0<=d<2**64 for d in v[13:]));require(row.count('U')==1 and row.count('V')>=1 and row.count('K')==row.count('N')==f[0])
 require(v[4:8]==([0,0,*f[4:6]] if f[0] and (not f[8] or not f[9]) else f[6:10]))
 i=0
 while i<at:
  n=dict(U=1,V=6,Q=2,C=4,P=4,S=4,W=2,H=2,K=3,N=1).get(row[i]);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
 require(i==at)
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_terrain.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-terrain-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_terrain import RadarTerrainOracle
  oracle=RadarTerrainOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  require(oracle.counts['terrain']==len(commands) and oracle.audit_calls==len(commands) and oracle.counts['projection']==sum(parse(c)[0] for c in commands) and oracle.counts['lock']==oracle.counts['unlock']==oracle.counts['projection'] and oracle.counts['supplied_colors']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar terrain sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
