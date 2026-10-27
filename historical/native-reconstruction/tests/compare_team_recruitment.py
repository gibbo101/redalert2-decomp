# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team recruitment parent with supplied child services: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_recruitment import verify
ORIGINAL=('tests/compare_team_recruitment.py','tests/original_team_recruitment.py','tools/verify_team_recruitment.py')
NATIVE=('src/sim/TeamRecruitment.hpp','src/sim/TeamMembership.hpp','tests/team_recruitment_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(kind16_complete_path=True,ordinary_null_clear_actual=True,children_supplied=True,production_recruitment=False)
NAMES=('slot','count','required','current','group','typeA8','group0','group1','group2','admit0','admit1','admit2','outputSlot','profile','anchor','waypoint1','waypoint2','addResult','mutation','kind','tfGroup','hasTF','typeC0C','typeC12','health','state5AC','clearOnly','emptyProfile')
DEFAULT=(0,3,4,0,-2,0,-1,-1,-1,1,1,1,0,0,0,2147450879,2147450879,1,0,16,-1,1,0,0,125,0,0,0)
def require(v):
 if not v:raise ValueError('Team recruitment evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==len(NAMES) and all(-2**31<=x<2**31 for x in v));d=dict(zip(NAMES,v))
 require(0<=d['slot']<6 and -1<=d['count']<=3 and d['hasTF']==1 and all(d[k] in (0,1) for k in ('anchor','addResult','clearOnly','emptyProfile')))
 require(all(0<=d[k]<=255 for k in ('typeA8','typeC0C','typeC12')) and 0<=d['mutation']<=3 and 0<=d['profile']<=3 and d['state5AC'] not in (27,28,29,30))
 require(d['clearOnly'] or d['required']<=d['current'] or d['kind']==16)
 return v
def scenarios():
 yield 'actual_E1_candidate_selection_supplied_startup',command()
 for key,values in dict(slot=(0,5),count=(-1,0,1,2,3),required=(-2147483648,0,4,2147483647),current=(-2147483648,-1,0,4,2147483647),group=(-2,-1,0,7),typeA8=(0,128),group0=(-2,-1,7),group1=(-2,-1,7),group2=(-2,-1,7),admit0=(0,1,256,257,-1),admit1=(0,1,256,257,-1),admit2=(0,1,256,257,-1),outputSlot=(-1,0,5,2147483647),profile=(0,1,2,3),anchor=(0,1),waypoint1=(2147450879,0,65535,-2147483648),waypoint2=(0,65535,-2147483648,2147450879),addResult=(0,1),mutation=(0,1,2,3),tfGroup=(-2,-1,7),emptyProfile=(0,1)).items():
  for value in values:yield 'ordered_candidate_parent_'+key,command(**{key:value})
 for group in (-2,-1,7):
  for typeA8 in (0,128):
   for profile in (0,1,2,3):
    for admit0 in (0,1):yield 'group_penalty_wrap_ties_and_eligibility',command(group=group,typeA8=typeA8,profile=profile,admit0=admit0,group0=7,group1=-1,group2=7)
 for mutation in (1,2,3):
  for profile in (0,1,2,3):yield 'live_count_and_member_changes',command(count=2,mutation=mutation,profile=profile)
 for anchor in (0,1):
  for waypoint1 in (2147450879,0,65535):
   for waypoint2 in (0,65535,-2147483648):yield 'saved_anchor_and_repeated_waypoint',command(anchor=anchor,waypoint1=waypoint1,waypoint2=waypoint2)
 for typeC0C in (0,128):
  for typeC12 in (0,128):
   for health in (-1,0,125):
    for state5AC in (-1,0,26,31):yield 'complete_ordinary_E1_null_clear',command(clearOnly=1,typeC0C=typeC0C,typeC12=typeC12,health=health,state5AC=state5AC)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_recruitment.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+21)
 for j in range(0,i,6):require(1<=int(row[j])<=9);[int(v) for v in row[j+1:j+6]]
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_recruitment import TeamRecruitmentOracle
  oracle=TeamRecruitmentOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x6b91c0']>0 and oracle.counts['0x502470']>0 and oracle.counts['0x5d4e00']>0)
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team recruitment sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
