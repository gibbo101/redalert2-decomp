#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the complete primary/secondary Overlay radar color."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_overlay_radar_color import verify

NATIVE=('src/render/OverlayRadarColor.hpp','src/assets/OverlayTypeInputs.hpp','tests/overlay_radar_color_vectors.cpp')
ORIGINAL=('tests/original_overlay_radar_color.py','tools/verify_overlay_radar_color.py','tests/compare_overlay_radar_color.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_overlay_radar_color.py')
FLAGS=dict(complete_5DD000=True,initialized_primary_getter=True,authored_alternate_getter_binding=True,wrapped_frame_offset=True,late_index_and_animation=True,authored_images=True,demand_loading_or_production=False)
def require(value):
 if not value:raise ValueError('Overlay radar color evidence/input differs')
def command(seed,index,frame,primary,alternate,animation,frames,altFrames,mutate=0,lateIndex=127):return 'O '+' '.join(map(str,(seed,index,frame,primary,alternate,animation,frames,altFrames,mutate,lateIndex)))
def parse(cmd):
 f=cmd.split();require(len(f)==11 and f[0]=='O');v=list(map(int,f[1:]));seed,index,frame,primary,alternate,animation,frames,altFrames,mutate,lateIndex=v
 require(0<=seed<=255 and -2**31<=index<2**31 and 0<=frame<2**32 and all(x in (0,1) for x in (primary,alternate,animation)) and all(-32768<=x<=32767 for x in (frames,altFrames)) and 0<=mutate<=3 and -2**31<=lateIndex<2**31)
 effective=frames if primary else altFrames if bool(alternate)^bool(mutate&2) and animation else None
 # Reject unsafe admitted pointers before entering the original. Wrapped offsets
 # that remain in the actual backed image (notably frame0x80000000) are covered.
 if effective is not None and frame<(effective&0xffffffff):require(((frame*24+20)&0xffffffff)+3<=215)
 return v
def scenarios():
 for index in (-2**31,-1,0,126,127,138,139,146,147,158,159,2**31-1):
  for primary,alternate,animation in ((0,0,0),(0,1,0),(0,1,1),(1,0,0),(1,1,1)):
   for frame in (0,1,3,4):yield 'image_and_index_policy',command((index*13+frame*7)&255,index,frame,primary,alternate,animation,4,2)
 for frames in (-32768,-2,-1,0,1,32767):
  for frame in (0,1,7,0x80000000,0xffffffff):
   for index in (127,147,0):
    cmd=command(73,index,frame,1,0,0,frames,4)
    try:parse(cmd)
    except ValueError:continue
    yield 'signed_count_and_wrapped_offset',cmd
 for mutate in (1,2,3):
  for primary in (0,1):
   for alternate in (0,1):
    for index,late in ((0,127),(127,0),(147,159)):
     yield 'getter_side_effect_order',command(91,index,1,primary,alternate,1,4,4,mutate,late)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_overlay_radar_color.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},
  environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),
  unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for key,value in FLAGS.items():require(e['evidence'].get(key) is value)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(row[:1]==['I'] and row.count('R')==1 and row[-6]=='R' and row.count('S')==2)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-radar-color-vectors')
 for key in ('output','expectations','report'):p.add_argument('--'+key,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_overlay_radar_color import OverlayRadarColorOracle
  oracle=OverlayRadarColorOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():
   commands.append(cmd);labels.append(label);expected.append(oracle.run(*parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['roots']==len(commands) and oracle.counts['primary']==len(commands) and oracle.counts['alternate']>0 and oracle.counts['zero_constructor']>0 and oracle.counts['output_stores']==2*len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta))
  fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True)
 report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,
  native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Overlay radar color sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
