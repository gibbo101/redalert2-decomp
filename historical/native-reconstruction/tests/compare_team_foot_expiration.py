# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Foot/Infantry expiration with a distinct Team34 subject."""
import itertools
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_foot_expiration import verify
ORIGINAL=('tests/compare_team_foot_expiration.py','tests/original_team_foot_expiration.py','tools/verify_team_foot_expiration.py')
import compare_mission_typed_tag_expiration as typed
import compare_mission_techno_tag_expiration as techno
NATIVE=typed.NATIVE
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_Foot_Infantry_Team_subject_expiration=True,actual_inherited_Object_Radio_Techno=True,non_Tag_subject_and_preserved_Object_Tag=True,named_children_and_startup_supplied=True,production_scheduling=False)
def require(v):
 if not v:raise ValueError('Team Foot expiration evidence/domain differs')
def command(**kw):
 f=techno.base();f.update(typed.defaults());f.update(root=5,subject=1,objectTag=2,flags=0,childMode=0,mode=0)
 f['typed'][9]=0;f['typed'][15]=0;f.update(kw);return typed.command(f)
def parse(c):
 f=typed.parse(c);require(f['root'] in (4,5) and f['subject']==1 and f['objectTag']!=1 and not f['flags']&3 and f['typed'][15]==0 and f['typed'][9]==0 and f['childMode']==0)
 # Team is not an Object/House; do not query invented Owner/coordinates or a
 # positive-health slave manager at this subject's offsets.
 require(all(v&255 for v in f['operations']) or f['fields'][6]!=1);return f
def scenarios():
 rng=random.Random(0x6ece5d)
 for root,flag,tag,removed in itertools.product((4,5),(0,128,252),(0,2),(1,257,0xffffffff)):
  yield 'distinct_Team_subject_and_preserved_Tag',command(root=root,flags=flag,objectTag=tag,operations=[removed])
 for root,case in itertools.product((4,5),range(96)):
  cmd=command(root=root);f=typed.parse(cmd);f['mode']=case%4;f['flags']=(0,4,128,252)[case%4]
  f['fields']=[rng.choice((0,1,2,9)) for _ in range(15)];f['fields'][0]=case%4;f['fields'][4]=8 if case&1 else 0;f['fields'][8]=6 if case&2 else 0;f['fields'][9]=7 if case&4 else 0;f['fields'][14]=case%4
  f['weapons']=[rng.choice((0,1,2,9)) for _ in range(8)];f['typed']=[rng.choice((0,1,2,9)) for _ in range(17)];f['typed'][0]=15;f['typed'][9]=0;f['typed'][15]=0;f['typed'][16]=(1,2,9)[case%3]
  f['counts']=[rng.randint(-2,8) for _ in range(4)];f['extraCounts']=[rng.randint(-2,8) for _ in range(3)];f['buffers']=[[rng.choice((0,1,2,9)) for _ in range(8)] for _ in range(4)];f['extraBuffers']=[[rng.choice((0,1,2,9)) for _ in range(8)] for _ in range(3)]
  f['operations']=[1,257] if case%3==0 else [0,256,1] if f['fields'][6]!=1 else [1]
  f['numbers']=[(-1,0,99,-2147483648)[case%4],-case,(0,10,11,2147483647)[case%4],(5,8,25)[case%3],44];f['session']=case%2;f['frame']=(-2147483648,0,100,2147483647)[case%4]
  f['predicate1']=(0,1,256,511)[case%4];f['predicateC']=(0,1,256,511)[(case//4)%4];f['queryResult']=(0,1,2)[case%3];f['queuedA0']=5
  yield 'shared_Team_reference_cleanup_live_children_and_repeated_calls',typed.command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_foot_expiration.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(isinstance(row,list) and all(isinstance(x,str) for x in row) and row.count('state')==1 and row.count('TYPED')==1 and row.count('R')>=1)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_foot_expiration import TeamFootExpirationOracle
  oracle=TeamFootExpirationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  require(all(oracle.counts[hex(entry)]>0 for entry in (0x5d3bd0,0x636ba0,0x6d2d10,0x4c8460,0x501cb0,0x468a70,0x468120,0x4d5b40)))
  require(not oracle.counts['0x548070'] and not oracle.counts['0x5d4e40'] and not oracle.counts['supplied.owner'])
  require(oracle.audit_calls==sum(len(parse(c)['operations']) for c in commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True,audited_original_calls=oracle.audit_calls,actual_entry_counts=dict(oracle.counts))
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team Foot expiration sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
