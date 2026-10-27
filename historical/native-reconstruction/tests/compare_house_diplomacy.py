#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete composed House notification and diplomacy differential proof."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
import compare_house_make_ally as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_diplomacy import verify
NATIVE=parent.NATIVE+('src/sim/HouseDiplomacy.hpp','src/sim/HouseAllianceNotification.hpp','src/sim/HouseMakeEnemy.hpp','tests/house_diplomacy_vectors.cpp')
ORIGINAL=('tests/original_house_diplomacy.py','tools/verify_house_diplomacy.py','tests/compare_house_diplomacy.py','tests/test_house_diplomacy.py')+parent.ORIGINAL+('tools/verify_house_make_enemy.py','tools/verify_house_alliance_notification.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_notification_actual_MakeAlly_MakeEnemy=True,actual_eligibility_scores_targets_sort_clear_conversion=True,session_map_grid_ui_virtuals_and_startup_supplied=True,production_adoption=False)
def require(ok):
 if not ok:raise ValueError('House diplomacy evidence/input differs')
def fixture():
 f=parent.fixture();f.update(root=0,notifyRule=1,sessionPresent=1,sessionResult=1);return f
def command(f):return ' '.join(map(str,(f['root'],f['notifyRule'],f['sessionPresent'],f['sessionResult'])))+' '+parent.command(f)
def parse(cmd):
 t=cmd.split();require(len(t)==347);v=list(map(int,t[:4]));f=parent.parse(' '.join(t[4:]));f.update(zip(('root','notifyRule','sessionPresent','sessionResult'),v));require(f['root'] in range(3) and 0<=f['notifyRule']<=255 and f['sessionPresent'] in (0,1) and 0<=f['sessionResult']<2**32)
 # A supplied diagnostic writing the parent's fixed scratch is not a nested
 # scratch initializer. Keep that old mutation in its original standalone proof.
 require(f['mutation']!=5);return f
def scenarios():
 for root in range(3):
  for mode in (0,1,4):
   for unrestricted in (0,1):
    for count in (0,1,3,5,8):
     f=fixture();f.update(root=root,mode=mode,unrestricted=unrestricted,houseCount=count);yield 'shared_parent_entries_counts_aliases',command(f)
 for enabled in (0,1,255):
  for present in (0,1):
   for result in (0,1,255,256,257,0xffffffff):
    f=fixture();f.update(notifyRule=enabled,sessionPresent=present,sessionResult=result);yield 'actual_notification_entry_rule_session_low_byte',command(f)
 for value in range(256):
  f=fixture();f['houses'][2][2]=value;f['houses'][3][5]=value;f['houses'][1][6]=value;yield 'raw_shared_House_flags',command(f)
 for mutation in (0,1,2,3,4,6,7,8,9,10,11,12,14,15):
  for root in range(3):
   f=fixture();f.update(root=root,mutation=mutation);yield 'actual_nested_services_late_shared_mutation',command(f)
 for actorCount in (0,1,4,8):
  for reg in (0,1,8,32):
   for root in (0,1):
    f=fixture();f.update(root=root,actorCount=actorCount);f['registryConfig'][0][0]=reg;yield 'nested_target_registry_and_clearing',command(f)
 for index in (-33,-1,0,1,31,32):
  for mask in (0,1,0xffffffff):
   f=fixture();f['houses'][2][0]=index;f['houses'][3][3]=mask;yield 'nested_signed_House_indices_and_masks',command(f)
 rng=random.Random(0x4ec5e0)
 for _ in range(48):
  f=fixture();f.update(root=rng.randrange(3),mode=rng.choice([0,1,4]),unrestricted=rng.randrange(2),houseCount=rng.randrange(1,9),actorCount=rng.randrange(5),mutation=rng.choice([0,2,3,4,7,8,11,12]))
  for h in f['houses']:h[2]=rng.choice([0,0,1]);h[3]=rng.getrandbits(32);h[5]=rng.choice([0,0,1]);h[6]=rng.choice([0,1])
  yield 'deterministic_actual_shared_owner_join',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_diplomacy.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0
 while i<len(row) and row[i] in ('E','J'):
  if row[i]=='J':require(i+4<=len(row) and row[i+1] in ('N','A','E') and all(0<=int(v)<=5 for v in row[i+2:i+4]));i+=4
  else:
   require(i+6<=len(row));k,a,b,allies,mask=map(int,row[i+1:i+6]);require(k in {1,2,4,5,6,7,8,9,10,16,17,44,56,60,240,401,696,848,0x404,0x228,0x310,0x25c,0x41ba10,0x781f20} and -2**31<=a<2**31 and -2**31<=b<2**32 and 0<=allies<2**32 and 0<=mask<2**32);i+=6
  require(i<=500000)
 require(len(row)-i==324 and row[-11]=='D');parent.validate_row(parent.command(parse(cmd)),row[i:-11]);d=list(map(int,row[-10:]));require(0<=d[0]<=255 and d[1] in (0,1) and 0<=d[2]<2**32 and all(0<=v<=255 for v in d[3:8]) and -2<=d[8]<=8 and d[9] in (0,1))
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_diplomacy import HouseDiplomacyOracle
  oracle=HouseDiplomacyOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x4ec5e0,0x4e5a70,0x4e5660,0x4ec4e0,0x4eeba0,0x6b54a0,0x6b5910,0x40dc20,0x41ba10,0x781d46,0x6c9af0,0x6c5070,0x77f110)) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House diplomacy sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
