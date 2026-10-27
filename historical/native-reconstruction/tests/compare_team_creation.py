# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete TeamType factory and joined action4: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_creation import verify
ORIGINAL=('tests/compare_team_creation.py','tests/original_team_creation.py','tools/verify_team_creation.py')
NATIVE=('src/sim/TeamCreation.hpp','src/sim/MissionCreateTeamAction.hpp','tests/team_creation_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_team_factory=True,joined_action4=True,constructor_and_heap_supplied=True,production_member_creation=False)
def require(v):
 if not v:raise ValueError('Team creation evidence/domain differs')
def command(**kw):
 names=('joined','depth','mode','maximum','count','defaultHouse','explicitHouse','allocate','result','mutation','houseCount')
 values=(0,0,0,1,0,1,0,1,1,0,0)
 require(not set(kw)-set(names));return ' '.join(str(kw.get(k,v)) for k,v in zip(names,values))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==11 and v[0] in (0,1) and 0<=v[1]<2**32 and all(-2**31<=v[k]<2**31 for k in (2,3,4,10)) and all(v[k] in (0,1,2) for k in (5,6,8)) and v[7] in (0,1) and 0<=v[9]<=5);return v
def scenarios():
 for joined in (0,1):
  for depth in (0,1,2**32-1):
   for mode in (0,1,-1):
    for maximum in (-1,0,1,2147483647):
     for count in (-1,0,1,2147483647):yield 'complete_factory_limits_or_action4_bypass',command(joined=joined,depth=depth,mode=mode,maximum=maximum,count=count,houseCount=count)
 for defaultHouse in (0,1,2):
  for explicitHouse in (0,1,2):
   for allocate in (0,1):
    for result in (0,1,2):yield 'house_selection_allocation_failure_constructor_return',command(depth=1,defaultHouse=defaultHouse,explicitHouse=explicitHouse,allocate=allocate,result=result)
 for joined in (0,1):
  for mutation in range(1,6):
   for depth in (0,1):
    for mode in (0,1):yield 'late_logger_count_allocation_constructor_mutation',command(joined=joined,mutation=mutation,depth=depth,mode=mode,maximum=2147483647)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_creation.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+7)
 for j in range(0,i,6):
  require(1<=int(row[j])<=7)
  for v in row[j+1:j+6]:int(v)
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_creation import TeamCreationOracle
  oracle=TeamCreationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x6bec80']==len(commands))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team creation sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
