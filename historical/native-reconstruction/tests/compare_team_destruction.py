# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team destructor and deleting wrapper with supplied named children."""
import itertools
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_destruction import verify
ORIGINAL=('tests/compare_team_destruction.py','tests/original_team_destruction.py','tools/verify_team_destruction.py')
NATIVE=('src/sim/TeamDestruction.hpp','src/sim/TeamConstruction.hpp','tests/team_destruction_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_team_destructor=True,complete_deleting_wrapper=True,named_children_supplied=True,production_scheduling=False)
NAMES=('type','house','houseFlag','active','members','tag','instances','deleteType','observerFlag','houseCount','typeCount','registry','observers','mutation','deleting')
DEFAULT=(1,1,1,1,4,1,0,0,1,1,1,0,4,0,1)
def require(v):
 if not v:raise ValueError('Team destruction evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(map(str,(kw.get(k,v) for k,v in zip(NAMES,DEFAULT))))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==15 and all(-2**31<=v<2**31 for v in f))
 require(f[0] in (0,1) and f[1] in (0,1) and all(0<=f[i]<=255 for i in (2,3,7,8)) and 0<=f[4]<=4 and 0<=f[5]<=2 and 0<=f[11]<=3 and 0<=f[12]<=4 and 0<=f[13]<=5);return f
def scenarios():
 for t,h,flag,active,members in itertools.product((0,1),(0,1),(0,128),(0,255),range(5)):
  yield 'nullable_owners_raw_session_and_members',command(type=t,house=h,houseFlag=flag,active=active,members=members)
 for tag,instances,deleteType,deleting in itertools.product(range(3),(0,1,-1),(0,128),(0,1,2,256,-1)):
  yield 'tag_instances_late_type_and_deleting_low_bit',command(tag=tag,instances=instances,deleteType=deleteType,deleting=deleting)
 for registry,observers,flag in itertools.product(range(4),range(5),(0,128)):
  yield 'duplicate_registries_live_observers',command(registry=registry,observers=observers,observerFlag=flag)
 for house,typeCount in itertools.product((-2147483648,-1,0,2147483647),repeat=2):
  yield 'wrapped_house_and_type_decrements',command(houseCount=house,typeCount=typeCount)
 for mutation,registry,members in itertools.product(range(1,6),range(4),(1,4)):
  yield 'live_observer_type_head_and_registry_mutations',command(mutation=mutation,registry=registry,members=members)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_destruction.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+57)
 for j in range(0,i,6):require(int(row[j]) in (1,2,3,4,5,6,7,8,9,10));[int(v) for v in row[j+1:j+6]]
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_destruction import TeamDestructionOracle
  oracle=TeamDestructionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team destruction sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
