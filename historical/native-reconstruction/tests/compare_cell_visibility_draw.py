# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Cell visibility draw caller: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_cell_visibility_draw import verify,ASSETS
ORIGINAL=('tests/compare_cell_visibility_draw.py','tests/original_cell_visibility_draw.py','tools/verify_cell_visibility_draw.py')
NATIVE=('src/render/CellVisibilityDraw.hpp','src/render/TerrainDepthPass.hpp','src/render/FrameDepthRefresh.hpp','src/render/SurfacePixel.hpp','tests/cell_visibility_draw_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_cell_visibility_parent=True,complete_shroud_and_fog_rasters=True,actual_stock_alpha_address=True,mask_and_loader_supplied=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Cell visibility draw evidence/domain differs')
def command(entry=1,flags=0,house=0,masks=(1,15),mutation=0,frame=1,screen=(2,3),clip=(0,0,64,64),bounds=(0,0,8,6),offset=0,stride=64,viewport=0,transparent=254,warm=0,asset=0,words=0):
 return ' '.join(map(str,(entry,flags,house,*masks,mutation,frame,*screen,*clip,*bounds,offset,stride,viewport,transparent,warm,asset,words)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==24 and all(-2**31<=n<2**31 for n in v) and v[0] in (0,1,2) and 0<=v[2]<=255 and 0<=v[5]<=4 and 0<v[15]<=60 and 0<v[16]<=30 and 0<=v[17]<8192 and v[18] in (0,64) and v[21] in (0,1,255) and v[22] in (0,1) and v[23] in (0,1));return v
def scenarios():
 for entry in (0,1,2):
  for flags in (0,0x1000):
   for offset in (0,4,8100,8190):
    for words in (0,1):
     for warm in (0,1,255):yield 'complete_parent_rasters_fast_wrap_lazy_warm',command(entry=entry,flags=flags,offset=offset,words=words,warm=warm)
 for p in (-2147483648,-258,-256,-255,-254,-2,-1,0,1,15,16,254,255,256,257,2147483647):
  for q in (-2,-1,0,15,254,256):
   for flags,house in ((0,0),(0x1000,0),(0x1000,1),(0x1000,128),(0x1000,255)):
    # Most invalid negative frames use the original empty default bounds and
    # return before address/payload access; keep the original screen positive.
    yield 'low_byte_signed_frames_and_independent_fog_gate',command(entry=0,masks=(p,q),flags=flags,house=house,clip=(2,3,62,61))
 for mutation in range(1,5):
  for flags in (0,0x1000):
   for house in (0,1):yield 'late_point_scenario_house_and_lazy_flags',command(entry=0,mutation=mutation,flags=flags,house=house)
 for entry in (1,2):
  for bounds in ((0,0,1,1),(-2,-1,8,6),(2,1,8,6)):
   for screen in ((2,3),(0,0),(-3,-2),(63,63),(70,70)):
    for clip in ((0,0,64,64),(3,4,2,2),(0,0,0,0),(4,5,-1,2)):
     early=(screen[1]+bounds[1]+bounds[3]<clip[1]+1 or screen[1]>=clip[1]+clip[3] or screen[0]+bounds[0]+bounds[2]<clip[0]+1 or screen[0]>=clip[0]+clip[2])
     left=max(clip[0],screen[0]+bounds[0]);right=min(clip[0]+clip[2],screen[0]+bounds[0]+bounds[2]);top=max(clip[1],screen[1]+bounds[1]);bottom=min(clip[1]+clip[3],screen[1]+bounds[1]+bounds[3])
     if not early and bottom>top and right<=left:continue # entered malformed/zero-width fast loop is outside safe domain
     for offset in (0,8190):yield 'cropped_raw_origins_and_clipping',command(entry=entry,bounds=bounds,screen=screen,clip=clip,offset=offset)
 for entry in (1,2):
  for transparent in (-1,0,127,254,255,256):
   for offset in (0,8190):yield 'fast_shroud_global_vs_wrapped_literal',command(entry=entry,transparent=transparent,offset=offset)
 for frame in range(48):
  for entry,flags in ((1,0),(1,0x1000),(2,0)):
   for offset in (0,8190):yield 'actual_owned_raw_visibility_assets',command(entry=entry,flags=flags,frame=frame,bounds=(0,0,60,30),offset=offset,asset=1,words=frame%2)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_visibility_draw.py',{'sources':dict.fromkeys(ORIGINAL)})
 assets={name:hash_file(a.assets/name) for name in ASSETS};require(assets==ASSETS)
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),assets=assets,sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+11)
 for j in range(0,i,5):
  require(1<=int(row[j])<=9)
  for v in row[j+1:j+5]:int(v)
 for v in row[i+1:-1]:int(v)
 require(len(row[-1])==64 and all(c in '0123456789abcdef' for c in row[-1]))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','assets'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_visibility_draw import VisibilityDrawOracle
  oracle=VisibilityDrawOracle(a.exe,[(a.assets/name).read_bytes() for name in ASSETS]);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x475520','0x474260','0x474510','0x411230','0x411370','supplied-mask','supplied-loader')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.assets)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell visibility draw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
