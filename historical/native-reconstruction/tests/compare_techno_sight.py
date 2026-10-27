#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete base Techno sight with portable C++."""
import argparse,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_techno_sight import verify
NATIVE=('src/sim/TechnoSight.hpp','src/sim/TechnoSight.cpp','src/sim/OriginalMath.hpp','tests/techno_sight_vectors.cpp')
ORIGINAL=('tests/original_techno_sight.py','tools/verify_techno_sight.py','tools/verify_terrain_visibility.py','tests/compare_techno_sight.py')
SOURCES=(*NATIVE,*ORIGINAL)
FLAGS=dict(complete_Techno_sight_6D5C30=True,actual_Unit_type_timer_and_FTOL_children=True,ordered_sight_state_stores_and_four_argument_mapping=True,reveal_area_54A110_supplied=True,production_visibility_schedule=False)
def require(v):
 if not v:raise ValueError('Techno sight evidence/input differs')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
KEYS=('enabled','countryFlag','x','y','z','divisor','increase','sight','timerBits','veteran','elite','multiplierBits','active','lastX','lastY','lastZ','lastRange','arg1','arg2','arg3','house')
def command(v):return 'S '+' '.join(str(v[k]) for k in KEYS)
def parse(cmd):
 p=cmd.split();require(len(p)==22 and p[0]=='S');v=dict(zip(KEYS,map(int,p[1:])))
 require(v['enabled'] in (0,1) and v['countryFlag'] in (0,1) and v['veteran'] in (0,1) and v['elite'] in (0,1) and v['active'] in (0,1) and v['house'] in (0,1) and -128<=v['increase']<=127 and v['divisor']!=0 and not(v['z']==-2**31 and v['divisor']==-1))
 for k in ('x','y','z','divisor','sight','lastX','lastY','lastZ','lastRange'):require(-2**31<=v[k]<2**31)
 for k in ('timerBits','multiplierBits'):require(0<=v[k]<2**64)
 for k in ('arg1','arg2','arg3'):require(0<=v[k]<2**32)
 return v
def scenarios():
 rng=random.Random(0x6d5c30);timers=(0.,.5,1.,1.5,2.,3.,float('nan'));multipliers=(0.,1.,1.5,-.5,float('nan'))
 for case in range(96):
  v=dict(enabled=0 if case==0 else 1,countryFlag=1 if case==1 else 0,x=rng.randint(-200000,200000),y=rng.randint(-200000,200000),z=(-1024,-257,-1,0,255,256,4096,32767)[case%8],divisor=(256,-256,100,7)[case%4],increase=(-128,-10,0,10,127)[case%5],sight=(-50,0,3,5,12,100000)[case%6],timerBits=bits(timers[case%len(timers)]),veteran=(case//2)&1,elite=(case//3)&1,multiplierBits=bits(multipliers[case%len(multipliers)]),active=(case//5)&1,lastX=-101,lastY=202,lastZ=-303,lastRange=404,arg1=(0x12345600|(case&255)),arg2=(0x80000000+case),arg3=case&1,house=0 if case%3==0 else 1)
  yield 'gates_height_timer_multiplier_first_active_and_forwarded_arguments',command(v)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_techno_sight.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('S')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/techno-sight-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_techno_sight import TechnoSightOracle
  oracle=TechnoSightOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6d5c30']==len(commands) and oracle.counts['0x77f110']>0 and oracle.counts['0x7133a0']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-10):j+24],want[max(0,j-10):j+24]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Techno sight sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
