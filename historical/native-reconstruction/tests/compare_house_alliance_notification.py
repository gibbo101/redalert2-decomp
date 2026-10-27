#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base complete House alliance notification differential proof."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_alliance_notification import verify
NATIVE=('src/sim/HouseAllianceNotification.hpp','tests/house_alliance_notification_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_house_alliance_notification.py','tools/verify_house_alliance_notification.py','tests/compare_house_alliance_notification.py','tests/test_house_alliance_notification.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_4EC5E0=True,recursive_diplomacy_and_session_supplied=True,production_adoption=False)
def require(ok):
 if not ok:raise ValueError('Alliance notification evidence/input differs')
def fixture():return dict(enabled=1,session=1,result=1,mode=0,count=4,mutation=0,slots=[1,2,3,4,1,0,3,4],houses=[[0,0,0,37],[0,1,0,41],[0,0,1,43],[1,0,0,47]])
def command(f):return 'N '+' '.join(map(str,[f[k] for k in ('enabled','session','result','mode','count','mutation')]+f['slots']+[v for h in f['houses'] for v in h]))
def parse(cmd):
 t=cmd.split();require(len(t)==31 and t[0]=='N');v=list(map(int,t[1:]));f=dict(zip(('enabled','session','result','mode','count','mutation'),v[:6]));f['slots']=v[6:14];f['houses']=[v[i:i+4] for i in range(14,30,4)]
 require(0<=f['enabled']<=255 and f['session'] in (0,1) and 0<=f['result']<2**32 and -2**31<=f['mode']<2**31 and -2<=f['count']<=8 and 0<=f['mutation']<=6 and all(0<=x<=4 for x in f['slots']) and all(0<=x<=255 for h in f['houses'] for x in h));return f
def scenarios():
 for enabled in (0,1,255):
  for session in (0,1):
   for result in (0,1,255,256,257,0x80000000,0xffffffff):
    for mode in (0,1,-1):
     f=fixture();f.update(enabled=enabled,session=session,result=result,mode=mode);yield 'entry_cached_rule_session_low_byte',command(f)
 for value in range(256):
  for column in range(3):
   f=fixture();f['houses'][0][column]=value;f['houses'][1][column]=value;yield 'all_raw_exclusion_local_flags',command(f)
 for count in (-2,0,1,3,8):
  for mutation in range(7):
   for mode in (0,1):
    f=fixture();f.update(count=count,mutation=mutation,mode=mode);yield 'live_registry_count_backing_flags',command(f)
 for mutation in range(7):
  for enabled in (0,1):
   for result in (0,1,256):
    f=fixture();f.update(enabled=enabled,result=result,mutation=mutation);yield 'saved_rules_before_query_and_live_diplomacy',command(f)
 rng=random.Random(0x4ec5e0)
 for _ in range(96):
  f=fixture();f.update(enabled=rng.choice([0,1,255]),session=rng.randrange(2),result=rng.choice([0,1,256,257]),mode=rng.choice([0,1,-1]),count=rng.randrange(-2,9),mutation=rng.randrange(7),slots=[rng.randrange(5) for _ in range(8)],houses=[[rng.choice([0,1,255]) for _ in range(4)] for _ in range(4)]);yield 'deterministic_alias_null_and_late_mutation',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_alliance_notification.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0;events=0
 while i<len(row) and row[i]!='S':
  tag=row[i];require(tag in ('Q','W','A','E'));n={'Q':2,'W':3,'A':4,'E':4}[tag];require(i+n<=len(row));v=list(map(int,row[i+1:i+n]))
  if tag=='Q':require(i==0 and 0<=v[0]<2**32)
  elif tag=='W':require(1<=v[0]<=4 and v[1]==1)
  else:require(1<=v[0]<=4 and 1<=v[1]<=4 and v[2]==0)
  i+=n;events+=1;require(events<=73)
 require(len(row)==i+22 and row[i]=='S');v=list(map(int,row[i+1:]));require(0<=v[0]<=255 and v[1] in (0,1) and -2**31<=v[2]<2**31 and -2<=v[3]<=8 and v[4] in (0,1) and all(0<=x<=255 for x in v[5:]))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_alliance_notification import HouseAllianceNotificationOracle
  oracle=HouseAllianceNotificationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x4ec5e0,0x4e5660,0x4e5a70)) and oracle.counts[hex(0x3006200)]>0 and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House alliance notification sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
