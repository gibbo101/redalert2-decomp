# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete frame depth refresh and actual stock surface children: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_terrain_depth_pass import verify
ORIGINAL=('tests/compare_terrain_depth_pass.py','tests/original_terrain_depth_pass.py','tools/verify_terrain_depth_pass.py')
NATIVE=('src/render/TerrainDepthPass.hpp','src/render/FrameDepthRefresh.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceFill.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/terrain_depth_pass_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_cell_caller_entered_tmp_depth_profile=True,actual_stock_surface_children=True,actual_depth_alpha_address=True,retained_hit_cache=True,ordered_depth_stores=True,frame_scheduling=False)
ASSET=ROOT/'private/migration/supplied-ra2-1006/composition/assets/clear01.tem'
def require(v):
 if not v:raise ValueError('Terrain depth evidence/domain differs')
def command(x=18,y=20,cx=0,cy=0,cw=96,ch=96,offset=0,vy=0,bpp=2,nullc=0,nullh=0,level=0,brightness=1000,refs=100,bypass=0):
 return ' '.join(map(str,(x,y,cx,cy,cw,ch,offset,vy,bpp,nullc,nullh,level,brightness,refs,bypass)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==15 and all(-2**31<=n<2**31 for n in v) and -128<=v[11]<=127 and -32768<=v[12]<=32767 and v[13]!=0 and all(v[i] in (0,1) for i in (9,10,14)));return v
def scenarios():
 for x in (-61,-60,-59,-30,-1,0,1,18,36,95,96):
  for y in (-30,-29,-28,-1,0,20,67,95,96):
   yield 'full_clip_edges_and_empty',command(x=x,y=y)
 for cx,cy,cw,ch in ((5,6,32,21),(28,14,1,1),(0,0,96,0),(0,0,0,96),(12,15,55,30),(30,21,4,5)):
  for x,y in ((0,0),(18,20),(25,10),(-5,2),(95,95)):
   yield 'offset_partial_thin_clip',command(x=x,y=y,cx=cx,cy=cy,cw=cw,ch=ch)
 for offset in (4,2,18432-768,18432-2,18432):
  for x,y in ((0,0),(18,20),(36,67),(60,80)):
   for bypass in (0,1):yield 'single_wrap_alignment_and_fast_gate',command(x=x,y=y,offset=offset,bypass=bypass)
 for level in (-128,-1,0,127):
  for bright in (-32768,-1,0,1000,32767):yield 'signed_cell_fields',command(level=level,brightness=bright)
 for refs in (1,100,-1,2147483647,-2147483648):yield 'retained_cache_wrapping',command(refs=refs)
 for bpp,nullc,nullh in ((1,0,0),(2,1,0),(2,0,1)):
  yield 'early_return_cache_lifetime',command(bpp=bpp,nullc=nullc,nullh=nullh)
 rng=random.Random(0x4754b0)
 for _ in range(120):
  yield 'seeded_clipped_diamond',command(x=rng.randrange(-59,97),y=rng.randrange(-28,97),cx=rng.randrange(25),cy=rng.randrange(25),cw=rng.randrange(73),ch=rng.randrange(73),offset=rng.choice((0,18430)),level=rng.randrange(-128,128),brightness=rng.randrange(-32768,32768),bypass=rng.randrange(2))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_terrain_depth_pass.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},asset_sha256=hash_file(ASSET),environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(len(row)==i+8)
 for value in row[i+1:i+5]:int(value)
 for value in row[i+5:]:require(len(value)==64 and all(c in '0123456789abcdef' for c in value))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_terrain_depth_pass import TerrainDepthOracle
  oracle=TerrainDepthOracle(a.exe,ASSET.read_bytes());commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x4754b0','0x52c230','0x776340','0x411230','0x41e3e0','0x41e510','0x52cf48','0x52c8cf')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),ordered_depth_store_count=oracle.stores,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Terrain depth sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
