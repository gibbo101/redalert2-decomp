#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the complete overlay image loading."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_overlay_image import verify

NATIVE=('src/assets/OverlayImage.hpp','src/assets/OverlayTypeInputs.hpp','tests/overlay_image_vectors.cpp')
ORIGINAL=('tests/original_overlay_image.py','tools/verify_overlay_image.py','tests/compare_overlay_image.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_overlay_image.py')
FLAGS=dict(complete_5DD150=True,complete_5D7BD0=True,crt_file_storage_lifetime_services_supplied=True,neither_flag_demand_refused=True,base_loader_inspection_only=True,production_startup_or_IO_fidelity=False)
def require(value):
 if not value:raise ValueError('Overlay image evidence/input differs')
def command(theater,demand,theaterFlag,newFlag,initial,owned,success,repeat,name):return 'I '+' '.join(map(str,(theater,demand,theaterFlag,newFlag,initial,owned,success,repeat,name)))
def parse(cmd):
 f=cmd.split();require(len(f)==10 and f[0]=='I');v=list(map(int,f[1:9]));theater,demand,theaterFlag,newFlag,initial,owned,success,repeat=v;name=f[9]
 require(-1<=theater<=2 and all(0<=x<=255 for x in (demand,theaterFlag,newFlag,owned)) and initial in (0,1) and success in (0,1) and 1<=repeat<=3 and 1<=len(name)<=24 and all(x.isascii() and (x.isalnum() or x=='_') for x in name))
 if not initial and demand:require((theaterFlag and theater>=0) or (not theaterFlag and newFlag))
 return (*v,name)
def scenarios():
 for initial in (0,1):
  for demand in (0,1,255):
   for theater in (-1,0,1,2):
    for theaterFlag,newFlag in ((0,0),(1,0),(0,1),(255,128)):
     for success in (0,1):
      cmd=command(theater,demand,theaterFlag,newFlag,initial,173,success,3,'GASAND')
      try:parse(cmd)
      except ValueError:continue
      yield 'complete_image_gate_filename_stores_retry',cmd
 for name in ('GASAND','gTsand','NAWALL','nAwall','CASAND','cTsand','GXSAND','XaWALL','TIB01','LOBRDG10','a','G','123','_'+23*'a'):
  for theater in (-1,0,1,2):
   for success in (0,1):yield 'new_theater_prefix_and_case',command(theater,1,0,255,0,0,success,2,name)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_overlay_image.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},
  environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),
  unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for key,value in FLAGS.items():require(e['evidence'].get(key) is value)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parsed=parse(cmd);require(row.count('R')==parsed[7] and row[-5]=='R')
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-image-vectors')
 for key in ('output','expectations','report'):p.add_argument('--'+key,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_overlay_image import OverlayImageOracle
  oracle=OverlayImageOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():
   commands.append(cmd);labels.append(label);expected.append(oracle.run(*parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['roots']==sum(parse(cmd)[7] for cmd in commands) and oracle.counts['load']>0 and oracle.counts['new_theater']>0 and oracle.counts['cleanup']==2*oracle.counts['load'] and current==identities(a) and runner==hash_file(a.native))
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
  native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Overlay image sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
