#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare all five ordered early returns of complete base47BB30."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_cell_dirty_effect import verify
NATIVE=('src/sim/CellDirtyEffect.hpp','src/sim/CellDirtyEffect.cpp','tests/cell_dirty_effect_vectors.cpp')
ORIGINAL=('tests/original_cell_dirty_effect.py','tools/verify_cell_dirty_effect.py','tests/compare_cell_dirty_effect.py')
FLAGS=dict(complete_47BB30_bytes=True,all_five_ordered_early_returns=True,resident_bearing_effect=False,production_Cell_owner=False)
def require(v):
 if not v:raise ValueError('Cell dirty-effect evidence/input differs')
def command(o,d,s,f,r):return 'D '+' '.join(map(str,(o,d,s,f,r)))
def parse(c):
 p=c.split();require(len(p)==6 and p[0]=='D');v=list(map(int,p[1:]));require(-2**31<=v[0]<2**31 and all(0<=x<=255 for x in v[1:3]) and 0<=v[3]<2**32 and v[4] in (0,1));
 f=dict(zip(('overlay','data','slope','flags','resident'),v));require(not(f['overlay']==0x7e and f['data']>=0x30 and not f['slope'] and not(f['flags']&0x20000) and f['resident']));return f
def exit_code(f):return 0 if f['overlay']!=0x7e else 1 if f['data']<0x30 else 2 if f['slope'] else 3 if f['flags']&0x20000 else 4
def scenarios():
 fixed=((-1,255,255,0xffffffff,1),(0x7d,0x30,0,0,1),(0x7e,0x2f,0,0,1),(0x7e,0x30,1,0,1),(0x7e,0x30,255,0xffffffff,1),(0x7e,0x30,0,0x20000,1),(0x7e,0xff,0,0xffffffff,1),(0x7e,0x30,0,0,0))
 for v in fixed:yield 'ordered_Cell_dirty_early_returns',command(*v)
 rng=random.Random(0x47bb30)
 for i in range(56):
  gate=i%5;o=rng.randint(-2**31,2**31-1);d=rng.randrange(256);s=rng.randrange(256);f=rng.randrange(2**32);r=rng.randrange(2)
  if gate==0:o=0x7d if i&1 else -1
  elif gate==1:o=0x7e;d=rng.randrange(0x30)
  elif gate==2:o=0x7e;d=rng.randrange(0x30,256);s=rng.randrange(1,256)
  elif gate==3:o=0x7e;d=rng.randrange(0x30,256);s=0;f|=0x20000
  else:o=0x7e;d=rng.randrange(0x30,256);s=0;f&=~0x20000;r=0
  yield 'ordered_Cell_dirty_early_returns',command(o,d,s,f,r)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_dirty_effect.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(row==['R',str(exit_code(parse(cmd)))])
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/cell-dirty-effect-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_dirty_effect import CellDirtyEffectOracle
  oracle=CellDirtyEffectOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['roots']==len(commands) and all(oracle.counts[k]>0 for k in ('overlay','data','slope','flags','head')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0 and [x.split() for x in run.stdout.splitlines()]==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell dirty-effect sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
