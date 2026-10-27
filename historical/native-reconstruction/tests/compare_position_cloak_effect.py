#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the two ordered early returns of complete base6C2990."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_position_cloak_effect import verify

NATIVE=('src/sim/PositionCloakEffect.hpp','src/sim/PositionCloakEffect.cpp','tests/position_cloak_effect_vectors.cpp')
ORIGINAL=('tests/original_position_cloak_effect.py','tools/verify_position_cloak_effect.py','tests/compare_position_cloak_effect.py')
FLAGS=dict(complete_6C2990_bytes=True,actual_coordinate_map_and_Cell_mask_helpers=True,
 supplied_actor_predicate280=True,global_object_and_actor_effects=False,production_schedule=False)
def require(v):
 if not v:raise ValueError('Position cloak-effect evidence/input differs')
def word(v):
 q=v//256 if v>=0 else -((-v)//256)
 return ((q+0x8000)&0xffff)-0x8000
def command(x,y,owner,mask,predicate):return 'C '+' '.join(map(str,(x,y,owner,mask,predicate)))
def parse(cmd):
 p=cmd.split();require(len(p)==6 and p[0]=='C');v=list(map(int,p[1:]));require(all(-2**31<=x<2**31 for x in v[:3]) and 0<=v[3]<2**32 and v[4] in (0,1));return dict(zip(('x','y','owner','mask','predicate'),v))
def scenarios():
 rng=random.Random(0x6c2990);owners=(0,1,6,7,15,23,31)
 for i in range(64):
  cellx=57+i%4;celly=89+(i//4)%4;x=cellx*256+(i*73&255);y=celly*256+(i*151&255);owner=owners[i%len(owners)]
  mask=rng.randrange(2**32);bit=1<<(owner&31)
  if i&1:mask|=bit;predicate=0
  else:mask&=~bit;predicate=(i>>1)&1
  yield 'ordered_Cell_cloak_mask_and_actor_predicate_exits',command(x,y,owner,mask,predicate)
def expected(cmd):
 f=parse(cmd);entered=bool(f['mask']&(1<<(f['owner']&31)));return ['R',str(1 if entered else 0),str(word(f['x'])),str(word(f['y'])),str(int(entered))]
def identities(a):
 paths=python_closure(ROOT/'tests/compare_position_cloak_effect.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(row==expected(cmd))
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/position-cloak-effect-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,answers=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_position_cloak_effect import PositionCloakEffectOracle
  oracle=PositionCloakEffectOracle(a.exe);commands=[];labels=[];answers=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);answers.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;entered=sum(row[-1]=='1' for row in answers);require(oracle.counts['roots']==len(commands) and oracle.counts['map']==oracle.counts['mask']==len(commands) and oracle.counts['predicate']==entered and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=answers,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0 and [x.split() for x in run.stdout.splitlines()]==answers)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'position cloak-effect sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
