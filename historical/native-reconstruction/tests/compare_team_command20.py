# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete active Team20 parent with actual House lookup and supplied transfer effects."""
import itertools
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_command20 import verify
ORIGINAL=('tests/compare_team_command20.py','tests/original_team_command20.py','tools/verify_team_command20.py')
NATIVE=('src/sim/TeamScript.hpp','src/sim/HouseAlliance.hpp','src/sim/TeamReadiness.hpp','src/sim/MissionScriptState.hpp','tests/team_command20_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(active_command20_complete_to_return=True,actual_house_country_lookup=True,anchor_and_transfer_children_supplied=True,saved_next_and_callee=True,production_scheduling=False)
NAMES=('members','readiness','complete','argument','oldD8','old1B0','reverse','typeAB','cursor','country','mutation','result')
DEFAULT=(4,0,1,13,70,1,0,0,0,13,0,1)
def require(v):
 if not v:raise ValueError('Team command20 evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(map(str,(kw.get(k,v) for k,v in zip(NAMES,DEFAULT))))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==12 and all(-2**31<=v<2**31 for v in f))
 require(1<=f[0]<=4 and all(0<=f[i]<=255 for i in (1,2,7)) and f[5] in (0,1) and f[6] in (0,1) and f[8] in (-1,0) and f[10] in range(8))
 require(f[2]!=0 or f[8]==0);return f
def scenarios():
 for members,complete,readiness,reverse,result in itertools.product(range(1,5),(0,1,128,255),(0,1,255),(0,1),(0,256,1,-1)):
  yield 'complete_active20_and_reevaluation_ignores_transfer_result',command(members=members,complete=complete,readiness=readiness,reverse=reverse,result=result,cursor=-1 if complete else 0)
 for argument,country,typeAB in itertools.product((-2147483648,-17,-1,0,13,2147483647),(-17,13),(0,1,255)):
  yield 'actual_house_first_match_signed_and_missing_country',command(argument=argument,country=country,typeAB=typeAB,readiness=255)
 for mutation,members,reverse,complete,result in itertools.product(range(1,8),(1,2,4),(0,1),(0,255),(0,257)):
  yield 'saved_next_callee_and_live_house_diagnostics',command(mutation=mutation,members=members,reverse=reverse,complete=complete,cursor=0,result=result)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_command20.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+40 and row[i+28]=='X')
 for j in range(0,i,6):require(1<=int(row[j])<=13);[int(v) for v in row[j+1:j+6]]
 for v in row[i+1:]:
  if v!='X':int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_command20 import TeamCommand20Oracle
  oracle=TeamCommand20Oracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x4ed760']>0 and oracle.counts['0x6b7ad0']>0 and oracle.counts['0x6b79e0']>0 and oracle.counts['0x6d6e50']>0)
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team command20 sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
