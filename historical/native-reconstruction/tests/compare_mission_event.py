#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare Boot Camp event dependencies; replay originals, execute current C++."""
import argparse,itertools,json,subprocess,time
from pathlib import Path
from original_mission_event import MissionEventOracle
from verify_mission_event import verify
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
SOURCES=('src/sim/MissionEvent.hpp','tests/mission_event_vectors.cpp','tests/original_mission_event.py',
 'tests/compare_mission_event.py','tools/verify_mission_event.py','tests/test_mission_event.py')
def require(ok):
 if not ok:raise ValueError('Mission event evidence differs')
def parse(command):
 t=command.split();require(len(t)>=9 and t[0]=='E');v=list(map(int,t[1:]));require(len(v)==8+v[7])
 require(v[0] in (4,13,33,47) and 0<=v[3]<=255 and 0<=v[7]<=16)
 require(all(-2147483648<=n<=2147483647 for n in v))
 return (*v[:7],v[8:])
def scenarios():
 def command(k,v=0,p=0,s=0,f=0,start=-1,remaining=0,h=()):return 'E '+' '.join(map(str,(k,v,p,s,f,start,remaining,len(h),*h)))
 for k,p,s,v,h in itertools.product((4,33),(0,4,33,47),(0,1,255),(-9,0,13,33), ((),(-9,0,13,33),(33,0,0,-9))):
  yield 'pulse_match_suppression_and_late_House',command(k,v,p,s,h=h)
 edges=(-2147483648,-2147483647,-16,-15,-14,-1,0,1,14,15,16,2147483646,2147483647)
 for frame,value in itertools.product(edges,edges):yield 'signed_scenario_seconds',command(47,value,f=frame)
 for frame,start,remaining in itertools.product(edges,(-2147483648,-15,-1,0,15,2147483647),(-2147483648,-1,0,1,15,2147483647)):
  yield 'timer_wrap_signed_compare_and_inactive',command(13,99,f=frame,start=start,remaining=remaining)
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['evidence']['identities']==current)
 require(e['evidence']['scheduler_and_runtime_excluded'] is True)
 require(len(e['commands'])==len(e['labels'])==len(e['expected'])>0)
 for cmd in e['commands']:parse(cmd)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 for name in ('output','expectations','report'):p.add_argument('--'+name,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  folder=private_path(a.output,a.exe);require(not folder.exists() and not a.report);report=folder/'report.json'
  oracle=MissionEventOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,command in scenarios():commands.append(command);labels.append(label);expected.append(oracle.run(*parse(command)))
  generation=time.monotonic()-now
  meta=dict(cases=len(commands),counts=dict(oracle.counts),audited_complete_roots=oracle.audit_calls,scheduler_and_runtime_excluded=True,identities=current)
 require(meta['audited_complete_roots']==len(commands) and all(meta['counts'].get('kind'+str(k),0)>0 for k in (4,13,33,47)))
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True,check=True)
 actual=[line.split() for line in run.stdout.splitlines()];require(actual==expected);comparison=time.monotonic()-now
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout)
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(len(commands),'complete mission-event roots PASS')
if __name__=='__main__':main()
