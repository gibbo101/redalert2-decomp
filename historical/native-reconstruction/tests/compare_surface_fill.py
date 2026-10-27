#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original software surface fill and ordered raster stores."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_surface_fill import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceFill.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','tests/surface_fill_vectors.cpp')
ORIGINAL=('tests/original_surface_fill.py','tools/verify_surface_fill.py','tests/compare_surface_fill.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_software_fill=True,actual_BSurface_children=True,ordered_byte_word_dword_stores=True,whole_backing_and_arena_guards=True,initial_allocation_geometry_supplied=True,message_global_surface_identified=False,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('Surface fill input/evidence differs')
def command(op='F',width=17,height=12,bpp=2,offset=16,lock=3,color=0x1234,clip=(0,0,17,12),rect=(1,2,7,5)):
 return ' '.join(map(str,(op,width,height,bpp,offset,lock,color,*clip,*rect)))
def scenarios():
 for bpp in (1,2):
  for offset in (16,17,18,19):
   for width in (16,17):
    for color in (0,0xff,0x1234,0xffff,0xdead1234,0xffffffff):
     for count in (1,2,3,4,5,7,8):
      yield 'store_alignment_color_width_odd_pitch_and_retained_lock',command(bpp=bpp,offset=offset,width=width,color=color,rect=(1,2,count,5))
 for rect in ((-8,-3,12,7),(-1,2,3,4),(15,10,7,8),(17,0,1,1),(0,12,1,1),(0,0,0,1),(0,0,1,-1),(0,0,17,12)):
  for op in ('E','F'):
   for clip in ((0,0,17,12),(3,2,8,7),(-2,-3,19,15),(0,0,0,8)):
    yield 'clipping_translation_and_early_returns',command(op=op,clip=clip,rect=rect)
 for width,height in ((0,12),(17,0),(1,1)):
  for lock in (-2147483648,-1,0,2147483647):yield 'empty_surface_and_wrapped_lock_level',command(width=width,height=height,lock=lock,rect=(0,0,2,2))
 for clip,rect in (((2147483647,0,2,2),(0,0,2,2)),((-2147483648,0,1,1),(0,0,1,1)),((0,0,17,12),(2147483647,0,2,2))):
  yield 'wrapped_rectangle_rejection',command(op='E',clip=clip,rect=rect)
def parse(cmd):
 p=cmd.split();require(len(p)==15 and p[0] in ('E','F'));v=list(map(int,p[1:]));width,height,bpp,offset,lock,color,*rects=v
 require(0<=width<=32 and 0<=height<=24 and bpp in (1,2) and 16<=offset<=19 and -2**31<=lock<2**31 and 0<=color<2**32 and all(-2**31<=n<2**31 for n in rects))
 return dict(op=p[0],width=width,height=height,bpp=bpp,offset=offset,lock=lock,color=color,clip=rects[:4],rect=rects[4:])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_surface_fill.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and len(row)==8 and row[6]=='L' and row[0]=='R' and row[2]=='B' and row[4]=='T')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_surface_fill import SurfaceFillOracle
  oracle=SurfaceFillOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x774390','0x7743c0','0x41fdf0','0x411370','0x4112f0')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Surface fill sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
