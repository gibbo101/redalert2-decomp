# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete alpha drawing and table initialization: originals separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_alpha_animation import verify
ORIGINAL=('tests/compare_alpha_animation.py','tests/original_alpha_animation.py','tools/verify_alpha_animation.py')
NATIVE=('src/render/AlphaAnimation.hpp','src/render/CellVisibilityDraw.hpp','src/render/FrameDepthRefresh.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/alpha_animation_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_alpha_drawing=True,complete_forced_table=True,actual_intersections_and_addressing=True,type_and_registry_startup_supplied=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Alpha animation evidence/domain differs')
def command(kind=0,mutation=0,cached=1,expired=0,frames=1,bounds=(2,3,50,20),origin=(0,0),viewport=(0,0),frame=(-2,-1,64,32),clip=(0,0,60,30),screen=(0,0),offset=0,stride=64,count=3,words=0):
 return ' '.join(map(str,(kind,mutation,cached,expired,frames,*bounds,*origin,*viewport,*frame,*clip,*screen,offset,stride,count,words)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==27 and all(-2**31<=n<2**31 for n in v) and 0<=v[0]<=2 and 0<=v[1]<=6 and v[2] in (0,1) and 0<=v[3]<=255 and -32768<=v[4]<=32767 and 0<v[15]<=64 and 0<v[16]<=32 and 0<=v[23]<8192 and v[24]==64 and 0<=v[25]<=3 and v[26] in (0,1));return v
def scenarios():
 yield 'complete_forced_table_all_ordered_stores',command(kind=2)
 for kind in (0,1):
  for cached in ((0,1) if kind==0 else (1,)):
   for expired in (0,1,128,255):
    for offset in (0,8000,8190):
     for words in (0,1):yield 'nonempty_cached_lazy_expired_fast_wrapped_and_backing',command(kind=kind,cached=cached,expired=expired,offset=offset,words=words)
 for mutation in range(1,7):
  for offset in (0,8000):
   for words in (0,1):yield 'saved_slot_cache_live_registry_count_backing_and_globals',command(mutation=mutation,cached=0,count=1 if mutation==1 else 3,offset=offset,words=words)
 for kind in (0,1):
  for frames in (-32768,-1,0,1,32767):
   for count in (0,1,3):yield 'signed_frame_count_unsigned_gate_and_zero_registry',command(kind=kind,frames=frames,count=count)
 for kind in (0,1):
  for clip in ((-10,-10,30,30),(7,9,14,13),(0,0,0,0),(0,0,-1,20),(60,30,10,10),(0,0,60,30)):
   for frame in ((-2,-1,64,32),(3,5,20,15),(0,0,1,1)):
    for offset in (0,8000):yield 'frame_crop_tile_mask_origin_and_viewport_difference',command(kind=kind,clip=clip,frame=frame,origin=(7,-5),viewport=(3,5),bounds=(10,3,40,22),offset=offset)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_alpha_animation.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+18)
 for j in range(0,i,5):
  require(1<=int(row[j])<=9)
  for v in row[j+1:j+5]:int(v)
 for v in row[i+1:-2]:int(v)
 for digest in row[-2:]:require(len(digest)==64 and all(c in "0123456789abcdef" for c in digest))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_alpha_animation import AlphaAnimationOracle
  oracle=AlphaAnimationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x41f1c0','0x41f5e0','0x41f950','0x41fdf0','0x411230','supplied-type')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 import pefile
 report.parent.mkdir(parents=True,exist_ok=True)
 mask=report.with_suffix('.tile-mask.bin');mask.write_bytes(pefile.PE(data=a.exe.read_bytes()).get_data(0x79b850-0x400000,1800))
 now=time.monotonic();run=subprocess.run([str(a.native),str(mask)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Alpha animation sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
