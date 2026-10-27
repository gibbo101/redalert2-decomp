#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Trigger destruction, Tag detachment and Trigger-then-Tag cleanup proof."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_trigger_destruction import verify
NATIVE=('src/sim/MissionTriggerDestruction.hpp','src/sim/MissionDeferredCleanup.hpp','src/sim/MissionTagDestruction.hpp','src/sim/MissionTagExpiration.hpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/mission_trigger_destruction_vectors.cpp')
ORIGINAL=('tests/original_mission_trigger_destruction.py','tools/verify_mission_trigger_destruction.py','tools/verify_mission_tag_destruction.py','tests/compare_mission_trigger_destruction.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_trigger_destruction.py','tests/mission_tag_lifetime_world.cpp','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Trigger_deleting_destructor=True,complete_Tag_pointer_expiration_recipient=True,actual_Trigger_then_Tag_cleanup=True,
 generic_kind38_non_Tag_recipients_RTTI_free_and_initial_records_supplied=True,discovery_actions_and_runtime_join=False)
def require(ok):
 if not ok:raise ValueError('Mission Trigger destruction evidence/input differs')
def command(op,type_mode,first,destroyed,deleting,removed,qcount,q,regs):
 return ' '.join(map(str,[op,type_mode,first,destroyed,deleting,removed,qcount,*q,*sum(([count,*slots] for count,slots in regs),[])]))
def parse(cmd):
 t=cmd.split();require(len(t)==1+6+8+4*7);op=t[0];v=list(map(int,t[1:]));type_mode,first,destroyed,deleting,removed,qcount=v[:6];q=v[6:14];cursor=14;regs=[]
 require(op in ('P','D','C') and type_mode in (0,1,2) and first in (0,1) and 0<=destroyed<=255 and 0<=deleting<2**32 and 0<=removed<2**32 and 0<=qcount<=8 and all(0<=x<=2 for x in q))
 for _ in range(4):count=v[cursor];slots=v[cursor+1:cursor+7];cursor+=7;require(0<=count<=6 and all(0<=x<=2 for x in slots));regs.append((count,slots))
 if op=='C':require(type_mode==1 and first==1 and qcount>0 and all(q[:qcount]))
 return dict(op=op,typeMode=type_mode,firstPresent=first,destroyed=destroyed,deleting=deleting,removed=removed,qcount=qcount,q=q,rcount=[x[0] for x in regs],r=[x[1] for x in regs])
def scenarios():
 empty=[(0,[0]*6) for _ in range(4)];queue_patterns=[(0,[0]*8),(1,[2,0,0,0,0,0,0,0]),(2,[2,2,1,0,0,0,0,0])]
 for type_mode in (0,1,2):
  for first in (0,1):
   for destroyed in (0,255):
    for removed in (0,1,256,257):
     for qcount,q in queue_patterns:yield 'complete_Tag_pointer_expiration_type_head_and_missing_type_scheduling',command('P',type_mode,first,destroyed,1,removed,qcount,q,empty)
 registry_patterns=[empty,
  [(1,[1,0,0,0,0,0]),(2,[1,2,0,0,0,0]),(2,[2,1,0,0,0,0]),(1,[2,0,0,0,0,0])],
  [(3,[1,1,2,0,0,0]),(4,[2,1,2,1,0,0]),(4,[1,2,1,2,0,0]),(3,[2,2,1,0,0,0])],
  [(2,[2,1,2,1,0,0]),(3,[1,2,1,2,0,0]),(3,[2,1,1,2,0,0]),(2,[1,2,1,2,0,0])]]
 for type_mode in (0,1,2):
  for first in (0,1):
   for deleting in (0,1,256,257):
    for regs in registry_patterns:yield 'complete_Trigger_deleting_destructor_broadcast_registry_base_and_low_bit_free',command('D',type_mode,first,0,deleting,1,0,[0]*8,regs)
 cleanup_queues=[(2,[1,2,0,0,0,0,0,0]),(3,[1,1,2,0,0,0,0,0]),(3,[1,2,2,0,0,0,0,0]),(4,[1,1,2,2,0,0,0,0])]
 for qcount,q in cleanup_queues:
  for regs in registry_patterns:yield 'actual_cleanup_destroys_Trigger_detaches_Tag_then_destroys_Tag_without_requeue',command('C',1,1,0,1,1,qcount,q,regs)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_trigger_destruction.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_trigger_destruction import MissionTriggerDestructionOracle
  oracle=MissionTriggerDestructionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6b4040']>0 and oracle.counts['0x6edba0']>0 and oracle.counts['0x6ecf10']>0 and oracle.counts['0x6b42e0']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),selected_stores=dict(oracle.stores),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission Trigger destruction sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
