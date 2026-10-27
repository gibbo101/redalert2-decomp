#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Deferred cleanup and ordinary-session Tag destruction differential proof."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_tag_destruction import verify
NATIVE=('src/sim/MissionDeferredCleanup.hpp','src/sim/MissionTagDestruction.hpp','src/sim/MissionTagExpiration.hpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/mission_tag_destruction_vectors.cpp')
ORIGINAL=('tests/original_mission_tag_destruction.py','tools/verify_mission_tag_destruction.py','tests/compare_mission_tag_destruction.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_tag_destruction.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_deferred_cleanup=True,ordinary_inactive_session_Tag_deleting_destructor=True,actual_release_search_and_base_destructor=True,
 expiration_RTTI_free_and_initial_records_supplied=True,Trigger_destructor_discovery_actions_and_runtime_join=False)
def require(ok):
 if not ok:raise ValueError('Mission Tag destruction evidence/input differs')
def command(instances,qcount,q,first,next2,next3,regs):
 return 'D '+' '.join(map(str,[instances,qcount,*q,first,next2,next3,*sum(([count,*slots] for count,slots in regs),[])]))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='D');v=list(map(int,t[1:]));require(len(v)==2+8+3+3*7);instances,qcount=v[:2];q=v[2:10];first,next2,next3=v[10:13];cursor=13;regs=[]
 require(-2**31<=instances<2**31 and 0<=qcount<=8 and all(0<=x<=4 for x in q) and all(x for x in q[:qcount]))
 require(first in (0,2,3) and 0<=next2<=3 and 0<=next3<=3 and next2!=2 and next3!=3)
 require(first!=2 or (next2!=3 or next3==0));require(first!=3 or (next3!=2 or next2==0))
 for _ in range(3):
  count=v[cursor];slots=v[cursor+1:cursor+7];cursor+=7;require(0<=count<=6 and all(0<=x<=3 for x in slots));regs.append((count,slots))
 return dict(instances=instances,qcount=qcount,q=q,first=first,next2=next2,next3=next3,rcount=[x[0] for x in regs],r=[x[1] for x in regs])
def scenarios():
 queues=[(1,[1,0,0,0,0,0,0,0]),(2,[1,1,0,0,0,0,0,0]),(4,[2,1,3,1,0,0,0,0]),(3,[4,1,4,0,0,0,0,0]),(3,[2,3,1,3,2,1,0,0]),(3,[2,4,3,1,1,0,0,0]),(1,[4,3,2,1,0,0,0,0]),(3,[1,2,3,3,2,1,3,2])]
 chains=[(0,0,0),(2,0,0),(2,3,0),(3,0,2)]
 patterns=[[(0,[0]*6),(0,[0]*6),(0,[0]*6)],[(1,[1,0,0,0,0,0])]*3,
  [(3,[2,1,1,3,0,0]),(2,[1,2,3,0,0,0]),(3,[1,3,1,2,0,0])],
  [(6,[1,2,1,3,1,2]),(4,[3,1,2,1,3,0]),(5,[2,3,1,1,2,0])]]
 values=(-2**31,-1,0,2**31-1);index=0
 for qcount,q in queues:
  for first,next2,next3 in chains:
   for regs in patterns:
    label='cleanup_retains_active_removes_all_inactive_duplicates_and_destroys_Tag' if 1 in q[:qcount] else 'cleanup_active_and_release_zero_without_Tag_destruction'
    yield label,command(values[index%len(values)],qcount,q,first,next2,next3,regs);index+=1
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_tag_destruction.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and row.count('state')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_tag_destruction import MissionTagDestructionOracle
  oracle=MissionTagDestructionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6ecf10']==len(commands) and oracle.counts['0x6b42e0']>0 and oracle.counts['0x6b39f0']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),selected_stores=dict(oracle.stores),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission Tag destruction sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
