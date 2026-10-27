# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team readiness parent with supplied child services: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_readiness import verify
ORIGINAL=('tests/compare_team_readiness.py','tests/original_team_readiness.py','tools/verify_team_readiness.py')
NATIVE=('src/sim/TeamReadiness.hpp','src/sim/MissionScriptState.hpp','tests/team_readiness_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_readiness=True,actual_script_state=True,children_supplied=True,production_team_ai=False)
NAMES=('mode','quantity','taskCount','profile','ab','a7','old7a','filled78','notify81','old7b','old79','old76','old7d','old7e','tagCount','raiseReturn','tagMutation','scriptOp','cursor','scriptCount','typeNull','reserved','anchor','rounds','required')
DEFAULT=(0,0,1,0,0,0,1,0,0,0,0,1,1,1,0,1,0,0,-1,2,0,0,1,4,4)
def require(v):
 if not v:raise ValueError('Team readiness evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==len(NAMES) and all(-2**31<=x<2**31 for x in v));d=dict(zip(NAMES,v))
 require(d['mode'] in (0,1) and -1<=d['taskCount']<=6 and 0<=d['profile']<=3 and 0<=d['tagCount']<=3 and 0<=d['tagMutation']<=3 and d['reserved']==0)
 require(all(0<=d[k]<=255 for k in ('ab','a7','old7a','filled78','notify81','old7b','old79','old76','old7d','old7e')) and all(d[k] in (0,1) for k in ('typeNull','anchor')) and 0<=d['scriptOp']<=5 and 0<=d['rounds']<=6)
 if d['mode']:
  op=d['scriptOp'];cursor=d['cursor'];count=d['scriptCount'];n=(cursor+1+2**31)%2**32-2**31
  require(not d['typeNull'] or op==2 or op==0 and cursor==-1)
  if op==0:require(cursor==-1 or 0<=cursor<6)
  if op==1 and n<count:require(0<=n<6)
 return v
def scenarios():
 yield 'actual_empty_new_Team_readiness',command()
 for quantity in (-2147483648,-1,0,1,2,3,4,5,2147483647):
  for ab in (0,128):
   for a7 in (0,128):
    for filled78 in (0,128):yield 'complete_readiness_quantity_flags',command(quantity=quantity,ab=ab,a7=a7,filled78=filled78)
 for profile in range(4):
  for taskCount in (-1,0,1,2,6):
   for quantity in (0,1,3,4):yield 'signed_wrapped_TaskForce_sum',command(profile=profile,taskCount=taskCount,quantity=quantity,ab=128,a7=128,required=2147483647)
 for tagCount in (0,1,2,3):
  for raiseReturn in (0,1,256,257,-1):
   for tagMutation in (0,1,2,3):yield 'reverse_live_Tag_registry_destruction',command(quantity=0,filled78=128,notify81=128,tagCount=tagCount,raiseReturn=raiseReturn,tagMutation=tagMutation)
 for key in ('old7a','old7b','old79','old76','old7d','old7e'):
  for value in (0,1,128,255):
   for quantity in (0,1,4):yield 'raw_flag_retention_'+key,command(quantity=quantity,**{key:value})
 for scriptOp in (0,1,2,3,4):
  for cursor in (-2147483648,-2,-1,0,1,2,5,6,2147483647):
   for scriptCount in (-2147483648,-1,0,2,6,2147483647):
    cmd=command(mode=1,scriptOp=scriptOp,cursor=cursor,scriptCount=scriptCount)
    try:parse(cmd)
    except ValueError:continue
    yield 'Script_signed_unsigned_and_backing',cmd
 for scriptOp in (0,2):yield 'Script_null_Type_bypass',command(mode=1,scriptOp=scriptOp,typeNull=1)
 for scriptCount in (-1,0,1,2,6):
  for rounds in (0,1,2,3,6):yield 'actual_script_reset_advance_current_sequence',command(mode=1,scriptOp=5,scriptCount=scriptCount,rounds=rounds)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_readiness.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+28)
 for j in range(0,i,6):require(1<=int(row[j])<=6);[int(v) for v in row[j+1:j+6]]
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_readiness import TeamReadinessOracle
  oracle=TeamReadinessOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x6b8bb0']>0 and oracle.counts['0x668870']>0 and oracle.counts['0x668920']>0)
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team readiness sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
