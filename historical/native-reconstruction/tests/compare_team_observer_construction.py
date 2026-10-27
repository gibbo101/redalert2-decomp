# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete observer/base construction with supplied CRT and resize services."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_observer_construction import verify
ORIGINAL=('tests/compare_team_observer_construction.py','tests/original_team_observer_construction.py','tools/verify_team_observer_construction.py')
NATIVE=('src/sim/TeamObserverConstruction.hpp','src/sim/TeamObserverConstruction.cpp','src/sim/TeamConstruction.hpp','src/sim/TeamObserverWeight.hpp','src/sim/TeamObserverWeight.cpp','tests/team_observer_construction_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_observer_constructor=True,abstract_type_parent_actual=True,abstract_base_actual=True,primary_type_setter_actual=True,registry_initializer_actual=True,CRT_resize_atexit_supplied=True,scenario_startup_supplied=True,production_scheduling=False)
NAMES=('name','baseProfile','observerProfile','resizeResult','mutation','flags','type','update','initialize','rounding')
DEFAULT=(2,0,0,1,0,255,1,1,0,1)
def require(v):
 if not v:raise ValueError('Team observer construction evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(map(str,(kw.get(k,v) for k,v in zip(NAMES,DEFAULT))))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==10 and all(-2**31<=v<2**31 for v in f))
 require(0<=f[0]<=7 and 0<=f[1]<6 and 0<=f[2]<6 and 0<=f[4]<=4 and 0<=f[5]<=255 and f[6] in (0,1,2) and f[7] in (0,1,2) and f[8] in (0,1) and f[9] in (0,1));return f
def scenarios():
 for name,base,observer in itertools.product(range(8),range(6),range(6)):
  yield 'name_lengths_aliases_and_two_registries',command(name=name,baseProfile=base,observerProfile=observer)
 for result,base,observer in itertools.product((0,1,256,257,-1),(3,4,5),(3,4,5)):
  yield 'resize_low_byte_wrapped_growth_and_retained_fields',command(resizeResult=result,baseProfile=base,observerProfile=observer)
 for mutation,name in itertools.product(range(1,5),range(8)):
  yield 'live_name_backing_and_count_mutations',command(name=name,baseProfile=4,observerProfile=4,mutation=mutation)
 for flags,type,update,rounding in itertools.product((0,7,128,255),range(3),range(3),(0,1)):
  yield 'primary_Type_and_actual_constructed_weight_callback',command(flags=flags,type=type,update=update,rounding=rounding)
 for name,result,update in itertools.product((0,5,6),(0,1,256,257),range(3)):
  yield 'actual_static_initializer_before_construction',command(name=name,resizeResult=result,update=update,initialize=1)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_observer_construction.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+137)
 for j in range(0,i,5):
  k,owner,off,n,v=map(int,row[j:j+5]);require(k in (1,2,4,5) and owner in (0,1,91,92) and n in (0,1,4,8) and 0<=v<2**64)
 for v in row[i+1:]:require(0<=int(v)<2**64)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_observer_construction import TeamObserverConstructionOracle
  oracle=TeamObserverConstructionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team observer construction sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
