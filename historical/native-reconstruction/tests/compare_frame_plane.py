# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete frame depth refresh and actual stock surface children: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_frame_plane import verify
ORIGINAL=('tests/compare_frame_plane.py','tests/original_frame_plane.py','tools/verify_frame_plane.py')
NATIVE=('src/render/FramePlane.hpp','src/render/FrameDepthRefresh.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceFill.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/frame_plane_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_depth_alpha_scroll_and_clear=True,actual_stock_surface_children=True,ordered_depth_stores=True,ordered_plane_fields=True,nonnull_bounded_common_allocation=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Frame plane evidence/domain differs')
def command(op=0,w=7,h=5,begin=64,offset=0,base=32768,dx=0,dy=0,color=65535,lock=0,words=0):
 return ' '.join(map(str,(op,w,h,begin,offset,base,dx,dy,color,lock,words)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==11 and 0<=v[0]<=3 and 0<=v[1]<=16 and 0<=v[2]<=16 and v[3] in (64,66) and 0<=v[4]<=v[1]*v[2]*2 and v[4]%2==0 and -2**31<=v[5]<2**31 and -32<=v[6]<=32 and -32<=v[7]<=32 and 0<=v[8]<=0xffffffff and -2**31<=v[9]<2**31 and v[10] in (0,1));require(v[0]>=2 or v[1]*v[2]>0);return v
def scenarios():
 for op in (0,1):
  for w,h in ((1,1),(2,2),(3,3),(4,3),(7,5),(8,6)):
   for offset in sorted({0,2,w*h*2-2}):
    for dx in sorted({-w,-1,0,1,w}):
     for dy in sorted({-h,-1,0,1,h}):
      for words in (0,1):yield 'complete_scroll_all_quadrants_ring_edges_and_small_spans',command(op=op,w=w,h=h,begin=64+op*2,offset=offset,dx=dx,dy=dy,words=words,color=65535 if op==0 else 127)
 for op in range(4):
  for color in (0,127,0x1234,65535,0xdead1234,0xffffffff):
   for words in (0,1):yield 'color_low_word_and_full_fallback',command(op=op,offset=12,dx=8,dy=-6,color=color,words=words)
 for op in (0,1):
  for base in (-2147483648,-1,0,2147483647):
   for dy in (-1,1):yield 'wrapped_signed_depth_base',command(op=op,base=base,dy=dy,offset=16)
 for op in (2,3):
  for w,h in ((0,0),(0,3),(3,0),(1,1)):
   yield 'complete_clear_empty_geometry',command(op=op,w=w,h=h)
 rng=random.Random(0x775d60)
 for _ in range(160):
  w=rng.randrange(1,17);h=rng.randrange(1,17)
  yield 'seeded_scroll_offsets_and_refusal_free_stock_backing',command(op=rng.randrange(2),w=w,h=h,offset=rng.randrange(w*h)*2,dx=rng.randrange(-w-1,w+2),dy=rng.randrange(-h-1,h+2),color=rng.randrange(2**32),lock=rng.choice((-2147483648,0,3,2147483647)),words=rng.randrange(2))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_frame_plane.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+5)
 for j in range(0,i,6):
  require(1<=int(row[j])<=4)
  for value in row[j+1:j+6]:int(value)
 for value in row[i+1:i+4]:int(value)
 require(len(row[-1])==64 and all(c in '0123456789abcdef' for c in row[-1]))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_frame_plane import FramePlaneOracle
  oracle=FramePlaneOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x775d60','0x410c50','0x776160','0x411050','0x774390','0x7743c0')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),pixel_stores=oracle.pixel_stores,field_stores=oracle.field_stores,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Frame plane sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
