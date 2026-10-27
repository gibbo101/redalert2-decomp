#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Action17 Reveal Around Waypoint exact-original comparison."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_reveal_action import verify
NATIVE=('src/sim/MissionRevealAction.hpp','tests/mission_reveal_action_vectors.cpp')
ORIGINAL=('tests/original_mission_reveal_action.py','tools/verify_mission_reveal_action.py','tools/verify_mission_trigger.py','tests/compare_mission_reveal_action.py')
FLAGS=dict(complete_action17_Reveal_Around_Waypoint_dispatch_branch=True,dispatcher_object_filter_and_four_argument_forwarding=True,child_result_low_byte_preserved=True,reveal_child_and_map_effects_supplied=True,production_action_association=False)
def require(ok):
 if not ok:raise ValueError('Mission Reveal action evidence/input differs')
def command(first,obj,third,fourth,result):return f'R {first} {obj} {third} {fourth} {result}'
def parse(cmd):
 t=cmd.split();require(len(t)==6 and t[0]=='R');first,obj,third,fourth,result=map(int,t[1:]);require(all(0<=v<2**32 for v in (first,third,fourth,result)) and obj in (0,1,2));return dict(first=first,object=obj,third=third,fourth=fourth,result=result)
def scenarios():
 for obj in (0,1,2):
  for first,third,fourth,result in ((0,0,0,0),(1,2,3,1),(0xffffffff,0x80000000,0x7fffffff,0x123456ab)):
   yield 'complete_action17_object_filter_forwarding_and_child_low_byte',command(first,obj,third,fourth,result)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_reveal_action.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  q=parse(cmd);require(isinstance(row,list) and row[-2:]==['R',str(q['result']&255)] and row.count('C')==1 and int(row[3])==(0x3001000 if q['object']==2 else 0))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_reveal_action import MissionRevealActionOracle
  oracle=MissionRevealActionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6adae0']==len(commands) and oracle.counts['0x6ae588']==len(commands) and oracle.counts['supplied_reveal']==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission Reveal action sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
