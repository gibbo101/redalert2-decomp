#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete base post-sight refresh with portable C++."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_post_sight_refresh import verify
NATIVE=('src/sim/PostSightRefresh.hpp','src/sim/PostSightRefresh.cpp','src/sim/VisibilityStartup.hpp','src/sim/VisibilityStartup.cpp','src/sim/CellVisibilityState.hpp','tests/post_sight_refresh_vectors.cpp')
ORIGINAL=('tests/original_post_sight_refresh.py','tools/verify_post_sight_refresh.py','tests/compare_post_sight_refresh.py')
FLAGS=dict(complete_post_sight_parent_54A550=True,unchanged_height_projection_6A2970=True,exact_radius_clamp_and_slice=True,ordered_cell_mask_store_mark_redraw=True,mask_and_redraw_children_supplied=True,production_arrival_schedule=False)
def require(v):
 if not v:raise ValueError('Post-sight evidence/input differs')
def spread():
 out=[(0,0)]
 for radius in range(1,11):
  x,y=-1,-radius;has_two=had_two=True
  while True:
   out.append((x,y))
   if x==1 and y==radius:break
   if has_two:x+=1;has_two=x==0;continue
   if x<0:x=-x;has_two=had_two;continue
   y+=1;reflected=y>0
   if reflected:y=-y
   x=-2*(radius+y)-1;difference=x-y;has_two=difference>=0;had_two=has_two
   if difference==-1:x+=1
   elif difference<0:x=(-y)//2-radius
   if reflected:y=-y
 out[1],out[3]=out[3],out[1]
 def quartet(x,y):out.extend(((-x,y),(x,y),(-x,-y),(x,-y)))
 out.extend(((0,11),(0,-11)))
 for x in range(1,4):
  quartet(x,11)
  if x==3:out[-1]=(-3,11)
 for x in range(4,6):quartet(x,9)
 for x in range(6,8):quartet(x,8)
 for y in range(7,5,-1):quartet(8,y)
 for y in range(5,3,-1):quartet(9,y)
 for y in range(3,1,-1):quartet(10,y)
 quartet(11,1);out.extend(((11,0),(-11,0)))
 require(len(out)==369)
 raw=b''.join(struct.pack('<hh',*p) for p in out);require(hashlib.sha256(raw).hexdigest()=='fc228aefe48c2afdb75e7077a94831099277038652eb81eb0314536609d72942')
 return out
OFFSETS=spread();SCALE=0x3fc25e5374344960
def command(v):return 'P '+' '.join(str(v[k]) for k in ('x','y','z','inner','outer','disabled','scaleBits','mode','maskSeed','primarySeed'))
def parse(cmd):
 p=cmd.split();require(len(p)==11 and p[0]=='P');v=list(map(int,p[1:]));out=dict(zip(('x','y','z','inner','outer','disabled','scaleBits','mode','maskSeed','primarySeed'),v));require(out['disabled'] in (0,1) and out['mode'] in (0,1,2) and 0<=out['scaleBits']<2**64);out['offsets']=OFFSETS;return out
def scenarios():
 rng=random.Random(0x54a550);inners=(-5,-1,0,1,3,8,9,20);outers=(-7,2,3,4,8,11,12,2**31-1);zs=(-1200,-400,-1,0,416,727,728,1200);scales=(SCALE,0,0x3f847ae147ae147b,0xbf947ae147ae147b)
 for i in range(64):
  inner=inners[i%len(inners)];outer=outers[(i//2)%len(outers)];clamped=max(3,min(11,outer));effective=max(0,min(8,inner));disabled=(i//3)&1
  if not disabled and effective and effective-1>clamped:disabled=1
  v=dict(x=20*256+rng.randint(-255,255),y=20*256+rng.randint(-255,255),z=zs[i%len(zs)],inner=inner,outer=outer,disabled=disabled,scaleBits=scales[i%len(scales)],mode=i%3,maskSeed=(i*19)&255,primarySeed=(i*31)&255)
  yield 'post_sight_refresh',command(v)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_post_sight_refresh.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),spread_sha256='fc228aefe48c2afdb75e7077a94831099277038652eb81eb0314536609d72942',sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/post-sight-refresh-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_post_sight_refresh import PostSightRefreshOracle
  oracle=PostSightRefreshOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts[hex(0x54a550)]==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()]
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],at,got[max(0,at-12):at+30],want[max(0,at-12):at+30]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and len(actual)==len(expected) and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'post-sight refresh sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
