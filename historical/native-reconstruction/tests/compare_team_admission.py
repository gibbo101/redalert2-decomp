# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team admission parent with supplied child services: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_admission import verify
ORIGINAL=('tests/compare_team_admission.py','tests/original_team_admission.py','tools/verify_team_admission.py')
NATIVE=('src/sim/TeamAdmission.hpp','tests/team_admission_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_team_admission_parent=True,children_supplied=True,production_recruitment=False)
NAMES=('same','onmap','health','loading','limbo','house','radio','kind','airFlag','mission0','mission1','allow','eligible','teamFlag','script','action','recruit','prior','oldPriority','priority','airWord','airTarget','taskCount','match','count','required','mutation')
DEFAULT=(0,1,125,0,0,1,0,15,0,5,5,1,1,0,1,-1,1,0,1,5,0,0,1,0,0,4,0)
def require(v):
 if not v:raise ValueError('Team admission evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==len(NAMES) and all(-2**31<=x<2**31 for x in v));d=dict(zip(NAMES,v))
 require(all(d[k] in (0,1) for k in ('same','house','script','prior')) and all(0<=d[k]<=255 for k in ('onmap','limbo','airFlag','eligible','teamFlag','recruit')) and -1<=d['taskCount']<=6 and -1<=d['match']<6 and 0<=d['mutation']<=4)
 return v
def scenarios():
 yield 'actual_E1_admission_arguments_supplied_startup',command()
 for key,values in dict(same=(1,),onmap=(0,128),health=(0,-1,-2147483648),loading=(0,1,-1),limbo=(0,128),house=(0,1),radio=(0,1,256,257),kind=(2,15,37),airFlag=(0,128),mission0=(-1,0,5,12),mission1=(-1,0,5,12),allow=(0,1,256,257),eligible=(0,128),teamFlag=(0,128),script=(0,1),action=(-1,8,50),recruit=(0,128),prior=(0,1),oldPriority=(-2147483648,4,5,6,2147483647),priority=(-2147483648,0,2147483647),airWord=(0,1,-1),airTarget=(0,1),count=(-2147483648,-1,0,3,4,2147483647),required=(-2147483648,-1,0,4,2147483647)).items():
  for value in values:yield 'individual_live_gates_'+key,command(**{key:value})
 for radio in (0,1,256,257):
  for kind in (2,15):
   for airFlag in (0,128):
    for airWord in (0,1):
     for airTarget in (0,1):yield 'radio_aircraft_and_target_gate',command(radio=radio,kind=kind,airFlag=airFlag,airWord=airWord,airTarget=airTarget)
 for eligible in (0,128):
  for teamFlag in (0,128):
   for recruit in (0,128):
    for action in (-1,8,50):
     for kind in (2,15):yield 'recruitability_script8_and_aircraft_exceptions',command(eligible=eligible,teamFlag=teamFlag,recruit=recruit,action=action,kind=kind)
 for taskCount in (-1,0,1,2,6):
  for match in (-1,0,1,5):
   for count in (-2147483648,0,3,4,2147483647):yield 'exact_type_scan_signed_counts_and_capacity',command(taskCount=taskCount,match=match,count=count)
 for prior in (0,1):
  for oldPriority in (-2147483648,4,5,6,2147483647):
   for priority in (-2147483648,5,2147483647):yield 'existing_team_signed_priority_no_steal_on_equal',command(prior=prior,oldPriority=oldPriority,priority=priority)
 for mutation in (1,2,3,4):
  for action in (-1,8):
   for recruit in (0,1):yield 'late_child_mutation_no_recheck_and_live_taskforce',command(mutation=mutation,action=action,recruit=recruit,teamFlag=1)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_admission.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%2==0 and len(row)==i+14)
 for j in range(0,i,2):require(1<=int(row[j])<=12);int(row[j+1])
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_admission import TeamAdmissionOracle
  oracle=TeamAdmissionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x6b8dc0']==len(commands))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team admission sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
