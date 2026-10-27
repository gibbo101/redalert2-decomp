# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete frame alpha refresh and actual stock surface children: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_frame_alpha_refresh import verify
ORIGINAL=('tests/compare_frame_alpha_refresh.py','tests/original_frame_alpha_refresh.py','tools/verify_frame_alpha_refresh.py')
NATIVE=('src/render/FrameDepthRefresh.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceFill.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/frame_alpha_refresh_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_frame_alpha_refresh=True,actual_stock_surface_children=True,ordered_alpha_stores=True,live_surface_and_alpha_fields=True,nonnull_backing=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Frame alpha evidence/domain differs')
def command(mode=0,width=8,bpp=2,offset=64,lock0=0,lock1=0,delta=0,begin=64,end=192,extent=128,stride=8,x=0,y=0,w=8,h=3,words=0):
 return ' '.join(map(str,(mode,width,bpp,offset,lock0,lock1,delta,begin,end,extent,stride,x,y,w,h,words)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==16 and all(-2**31<=n<2**31 for n in v) and 0<=v[0]<=7 and -4<=v[2]<=4 and 0<=v[3]<=512 and 0<=v[7]<v[8]<=1024 and 1<=v[9]<=1024 and -32<=v[10]<=32 and -32<=v[11]<=32 and -4<=v[12]<=4 and -1<=v[13]<=64 and -1<=v[14]<=32 and v[15] in (0,1));return v
def scenarios():
 for alignment in range(4):
  for start in (0,1,3,30,31):
   for w in (0,1,2,3,4,7,8,16,32):
    for words in (0,1):
     yield 'alignment_prefix_pairs_omitted_single_tail_and_ring_split',command(begin=64+alignment,end=128+alignment,extent=64,offset=64+alignment+start*2,w=w,words=words)
 for mode in range(1,8):
  for h in (-1,0,1,3):
   for words in (0,1):yield 'live_surface_reload_geometry_and_lock_mutation',command(mode=mode,h=h,words=words)
 for h in (-1,0,1,4):
  for w in (-1,0,1,3):
   if h>0 and w<0:continue
   yield 'height_gate_and_zero_width',command(h=h,w=w)
 for lock in (-2147483648,-1,0,2147483647):
  for mode in (0,1,6):yield 'wrapped_distinct_lock_owners',command(mode=mode,lock0=lock,lock1=lock,w=3)
 for width,bpp,x,y in ((2147483647,2,0,2),(-8,2,0,-1),(8,-2,0,-1),(8,0,7,2),(8,1,-2,1)):
  yield 'stock_lock_wrapped_pitch_and_negative_coordinates',command(width=width,bpp=bpp,x=x,y=y,w=3)
 rng=random.Random(0x4110b0)
 for _ in range(160):
  a=rng.randrange(4);start=rng.randrange(64);mode=rng.randrange(8)
  yield 'seeded_ring_rows_and_mutable_services',command(mode=mode,offset=64+a+start*2,begin=64+a,end=192+a,extent=128,stride=rng.randrange(17),x=0,y=0,w=rng.randrange(33),h=rng.randrange(9),words=rng.randrange(2))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_frame_alpha_refresh.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+14)
 for j in range(0,i,5):
  require(1<=int(row[j])<=10)
  for v in row[j+1:j+5]:int(v)
 for v in row[i+1:-1]:int(v)
 require(len(row[-1])==64 and all(c in '0123456789abcdef' for c in row[-1]))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_frame_alpha_refresh import FrameAlphaOracle
  oracle=FrameAlphaOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x4110b0','0x411370','0x4112f0','0x4113b0','0x4113c0','0x4112c0')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Frame alpha sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
