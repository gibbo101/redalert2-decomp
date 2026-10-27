#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete base visibility-mask calculation with portable C++."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_cell_visibility_mask import verify
NATIVE=('src/sim/CellVisibilityMask.hpp','src/sim/CellVisibilityMask.cpp','tests/cell_visibility_mask_vectors.cpp')
ORIGINAL=('tests/original_cell_visibility_mask.py','tools/verify_cell_visibility_mask.py','tools/verify_terrain_visibility.py','tests/compare_cell_visibility_mask.py')
FLAGS=dict(complete_visibility_mask_6A8D40=True,primary_and_secondary_center_gates=True,eight_wrapped_neighbor_lookups_and_exact_mask_bits=True,actual_map_lookup_and_fallback=True,startup_result_table_supplied=True,production_visibility_schedule=False)
def require(v):
 if not v:raise ValueError('Cell visibility mask evidence/input differs')
def command(v):return 'M '+' '.join(map(str,[v['x'],v['y'],v['mode'],*v['slots'],*v['flags12c'],*v['flags140'],v['seed']]))
def parse(cmd):
 p=cmd.split();require(len(p)==34 and p[0]=='M');n=list(map(int,p[1:]));v=dict(x=n[0],y=n[1],mode=n[2],slots=n[3:12],flags12c=n[12:22],flags140=n[22:32],seed=n[32]);require(-32768<=v['x']<=32767 and -32768<=v['y']<=32767 and v['mode'] in (0,1) and all(-1<=x<9 for x in v['slots']) and all(0<=x<2**32 for x in v['flags12c']+v['flags140']) and 0<=v['seed']<256);return v
def scenarios():
 rng=random.Random(0x6a8d40);bits=(0x40,0x80,1,0x20,2,0x10,8,4)
 for case in range(128):
  x=32767 if case%29==27 else -32768 if case%29==28 else 20+(case%11);y=32767 if case%31==29 else -32768 if case%31==30 else 30+(case%13);mode=case&1;slots=[8,*range(8)]
  if case%11==0:slots[0]=-1
  if case%7==0:slots[1+(case%8)]=-1
  if case%13==0:slots[1+(case%8)]=slots[1+((case+3)%8)]
  f12=[rng.getrandbits(32) for _ in range(10)];f14=[rng.getrandbits(32) for _ in range(10)];center=9 if slots[0]<0 else slots[0]
  if case<6:
   if case==0:f12[center]&=~0x18
   elif case==1:f14[center]&=~3
   elif case==2:f12[center]=(f12[center]&~0x18)|0x10
   elif case==3:f14[center]=(f14[center]&~3)|1
   elif case==4:f12[center]|=8
   else:f14[center]|=2
  elif case%5==0:
   if mode:f14[center]=(f14[center]&~3)|1
   else:f12[center]=(f12[center]&~0x18)|0x10
  else:
   if mode:f14[center]|=2
   else:f12[center]|=8
  desired=(case*73)&255
  for i,bit in enumerate(bits):
   cid=9 if slots[i+1]<0 else slots[i+1]
   if mode:
    if desired&bit:f14[cid]&=~2
    else:f14[cid]|=2
   else:
    if desired&bit:f12[cid]&=~8
    else:f12[cid]|=8
  yield 'center_minus2_minus1_and_full_primary_secondary_neighbor_masks',command(dict(x=x,y=y,mode=mode,slots=slots,flags12c=f12,flags140=f14,seed=(case*19)&255))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_visibility_mask.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current,a):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('R')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/cell-visibility-mask-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,a);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_visibility_mask import CellVisibilityMaskOracle
  oracle=CellVisibilityMaskOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6a8d40']==len(commands) and oracle.counts['0x548070']>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-10):j+30],want[max(0,j-10):j+30]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell visibility mask sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
