#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Enable/Disable Trigger actions exact-original comparison."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_trigger_control import verify
NATIVE=('src/sim/MissionTriggerControl.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/mission_trigger_control_vectors.cpp')
ORIGINAL=('tests/original_mission_trigger_control.py','tools/verify_mission_trigger_control.py','tools/verify_mission_trigger.py','tests/compare_mission_trigger_control.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_action53_Enable_Trigger=True,complete_action54_Disable_Trigger=True,live_target_registry_type_and_difficulty=True,inherited_complete_timer_reset=True,other_actions_startup_and_runtime_join=False)
def require(ok):
 if not ok:raise ValueError('Mission Trigger control evidence/input differs')
def command(op,target,difficulty,allowed,event,value,frame,scratch,count,records):
 return ' '.join(map(str,['C',op,target,difficulty,*allowed,event,value,frame,scratch,count,*sum(([r['type'],r['enabled'],r['start'],r['padding'],r['remaining'],r['mask']] for r in records),[])]))
def parse(cmd):
 t=cmd.split();require(len(t)==12+24 and t[0]=='C' and t[1] in ('E','D'));v=list(map(int,t[2:]));target,difficulty,*rest=v;allowed=rest[:3];event,value,frame,scratch,count=rest[3:8];flat=rest[8:];records=[]
 require(target in (0,1,2) and all(0<=x<=255 for x in allowed) and event in (0,1) and 0<=count<=4)
 for i in range(4):
  x=flat[i*6:(i+1)*6];require(x[0] in (1,2) and 0<=x[1]<=255 and 0<=x[5]<2**32);records.append(dict(type=x[0],enabled=x[1],start=x[2],padding=x[3],remaining=x[4],mask=x[5]))
 return dict(op=t[1],targetMode=target,difficulty=difficulty,allowed=allowed,eventMode=event,timerValue=value,frame=frame,scratch=scratch,count=count,records=records)
def scenarios():
 patterns=[
  [dict(type=1,enabled=0,start=-1,padding=7,remaining=9,mask=0),dict(type=2,enabled=1,start=2,padding=3,remaining=4,mask=5),dict(type=1,enabled=255,start=6,padding=7,remaining=8,mask=0xffffffff),dict(type=2,enabled=0,start=9,padding=10,remaining=11,mask=12)],
  [dict(type=2,enabled=17,start=1,padding=2,remaining=3,mask=4),dict(type=1,enabled=34,start=-5,padding=-6,remaining=-7,mask=0x80000000),dict(type=2,enabled=51,start=8,padding=9,remaining=10,mask=11),dict(type=1,enabled=68,start=12,padding=13,remaining=14,mask=15)]]
 for op in ('E','D'):
  for target in (0,1,2):
   for difficulty in (-1,0,1,2,3):
    for allowed in ((0,0,0),(1,0,0),(0,1,0),(0,0,1),(255,2,128)):
     for event in (0,1):
      for count in (0,1,4):
       records=patterns[(target+count+event)&1]
       yield 'complete_Enable_Disable_live_registry_difficulty_and_timer_reset',command(op,target,difficulty,allowed,event,3,123,-1515870811,count,records)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_trigger_control.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and row.count('state')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_trigger_control import MissionTriggerControlOracle
  oracle=MissionTriggerControlOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6adae0']>0 and oracle.counts['0x6af1ea']>0 and oracle.counts['0x6af217']>0 and oracle.counts['0x6edb60']>0 and oracle.counts['0x6edb70']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),selected_stores=dict(oracle.stores),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission Trigger control sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
