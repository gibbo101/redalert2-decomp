# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete observer definition enumeration with actual locale-zero comparison."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_observer_definitions import verify
ORIGINAL=('tests/compare_team_observer_definitions.py','tests/original_team_observer_definitions.py','tools/verify_team_observer_definitions.py')
NATIVE=('src/assets/TeamObserverDefinitions.hpp','src/assets/TeamObserverDefinitions.cpp','src/sim/TeamObserverConstruction.hpp','src/sim/TeamObserverConstruction.cpp','src/assets/TeamObserverInputs.hpp','src/assets/TeamObserverInputs.cpp','src/assets/UnitModelInputs.hpp','src/assets/UnitModelInputs.cpp','src/sim/TeamObserverTypes.hpp','src/sim/StringLookup.hpp','tests/team_observer_definitions_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_observer_enumeration=True,locale_zero_actual=True,INI_allocate_construct_load_boolean_children_supplied=True,scenario_startup_supplied=True,production_scheduling=False)
NAMES=('mode','profile','registry','allocation','loadResult','boolean','session','mutation','repeats')
DEFAULT=(0,2,1,0,1,0,0,0,1)
def require(v):
 if not v:raise ValueError('Team observer enumeration evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==9)
 require(0<=f[0]<2**32 and f[1] in range(9) and f[2] in range(4) and f[3] in range(3) and 0<=f[4]<2**32 and 0<=f[5]<2**32 and -2**31<=f[6]<2**31 and f[7] in range(7) and f[8] in (1,2))
 # Bounded fixtures refuse unsafe original null stores and invalid supplied heap
 # or registry setups. These are guards, not passing original executions.
 require(not(f[0]==1 and (f[1]==3 or f[3] or f[7]==6)))
 require(not(f[2]==3 and f[1] not in (0,6,8)))
 require(not(f[7]==6 and (f[0]!=2 or f[1]!=1 or f[2]!=1 or f[8]!=1)))
 return f
def scenarios():
 for mode,profile,registry,repeat in itertools.product((0,1,2,4294967295),range(9),range(4),(1,2)):
  c=command(mode=mode,profile=profile,registry=registry,repeats=repeat)
  try:parse(c)
  except ValueError:continue
  yield 'saved_sections_modes_existing_new_and_repeated_definitions',c
 for allocation,result in itertools.product((1,2),(0,1,256,257,4294967295)):
  yield 'allocation_failure_and_ignored_parser_result',command(profile=7,allocation=allocation,loadResult=result)
 for result in (0,1,256,257,4294967295):yield 'successful_allocation_and_ignored_parser_result',command(profile=7,loadResult=result)
 for value,session in itertools.product((0,1,256,257,4294967295),(-2147483648,0,1,2147483647)):
  yield 'enable_boolean_low_byte_and_live_session',command(profile=6,boolean=value,session=session)
 for mutation,mode,profile,registry in itertools.product(range(1,7),(0,1,2),(1,2,5,6),(1,2)):
  c=command(mode=mode,profile=profile,registry=registry,mutation=mutation)
  try:parse(c)
  except ValueError:continue
  yield 'live_backing_count_session_and_post_store_mutations',c

def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_observer_definitions.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+46)
 for j in range(0,i,4):
  k,a,b,c=map(int,row[j:j+4]);require(1<=k<=9 and 0<=a<2**64 and 0<=b<2**64 and 0<=c<2**64)
 require(row[i+1] in ('0','1'))
 for v in row[i+2:]:require(0<=int(v)<2**64)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_observer_definitions import TeamObserverDefinitionsOracle
  oracle=TeamObserverDefinitionsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team observer enumeration sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
