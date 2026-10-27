#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete ordinary Infantry admission with friendly E1 resident lists."""
import argparse,copy,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
import compare_infantry_permission as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_resident import verify
ORIGINAL=(*parent.ORIGINAL,'tests/original_infantry_resident.py','tests/compare_infantry_resident.py','tools/verify_infantry_resident.py')
NATIVE=parent.NATIVE
SOURCES=(*ORIGINAL,*NATIVE,'tests/test_infantry_resident.py','CMakeLists.txt')
FLAGS=dict(complete_Infantry_admission=True,ordinary_friendly_E1_lists=True,actual_mission_kind_House_Walk_children=True,startup_and_associations_supplied=True,runtime_enabled=False)
def require(v):
 if not v:raise ValueError('Infantry resident evidence/input differs')
def command(moving=(0,0,0,0,0),typeFlags=(0,0,0),**kwargs):
 return 'J '+' '.join(map(str,(*moving,*typeFlags)))+' '+parent.command(**kwargs)
def parse(c):
 t=c.split(maxsplit=9);require(len(t)==10 and t[0]=='J');options=list(map(int,t[1:9]));require(all(0<=n<=255 for n in options))
 return options,parent.parse(t[9])
def scenarios():
 base=parent.parent.parent
 # Actual Team anchor: one stationary friendly E1, mission Return12, no overlay,
 # one occupied subcell. Fixture list and House identities are supplied inputs.
 for n,moving,mission,occupation,owner in itertools.product(range(5),(0,1,255),(0,5,12,25),(0,4,28,32),(-1,0)):
  objects=copy.deepcopy(base.OBJECTS);cells=copy.deepcopy(base.CELLS)
  for i,o in enumerate(objects):o[1]=-1;o[2]=0;o[4]=mission
  cells[0][11]=1 if n else -1;cells[0][6]=occupation;cells[0][8]=owner
  for i in range(1,n+1):objects[i][1]=i+1 if i<n else -1
  yield 'friendly_stationary_count_and_occupation_tail',command(moving=(0,)+(moving,)*4,objects=objects,cells=cells,loading=0,steps=[['U',0,0,-1,-1,-1,1,0]])
 for head in (0,1,2,3,4):
  objects=copy.deepcopy(base.OBJECTS);cells=copy.deepcopy(base.CELLS)
  order=[head]+[i for i in range(5) if i!=head]
  for i,o in enumerate(objects):o[1]=-1;o[2]=0;o[4]=12
  for i,j in zip(order,order[1:]):objects[i][1]=j
  cells[0][11]=head;cells[0][6]=28;cells[0][8]=0
  yield 'self_skip_and_reordered_live_lists',command(objects=objects,cells=cells)
 # Mixed moving/stationary lists also exercise count3 versus count4 on the
 # elevated list and allied distinct House identities (including shifted index33).
 for mask,elevated in itertools.product(range(16),(False,True)):
  objects=copy.deepcopy(base.OBJECTS);cells=copy.deepcopy(base.CELLS)
  for i,o in enumerate(objects):o[1]=i+1 if 1<=i<4 else -1;o[2]=1 if i else 0;o[4]=12
  cells[0][12 if elevated else 11]=1;cells[0][7 if elevated else 6]=28;cells[0][9 if elevated else 8]=0
  if elevated:cells[0][5]=0x100
  yield 'mixed_raw_moving_counts_and_elevated_list',command(moving=(0,)+tuple(128 if mask&(1<<i) else 0 for i in range(4)),
   typeFlags=(255,255,0),objects=objects,cells=cells,houses=[[0,2],[33,0],[2,4]],
   steps=[['U',0,0,-1,-1,-1,1,0]])
 # Native-observed activation argument profile; associations/neighbor fixture
 # remain supplied. This also enters actual direct permission before residents.
 objects=copy.deepcopy(base.OBJECTS);cells=copy.deepcopy(base.CELLS)
 for o in objects:o[1]=-1;o[2]=0;o[4]=12
 cells[0]=[71,94,-1,2,0,3,4,0,6,-1,7,3,-1]
 cells[1]=[72,95,-1,2,0,3,0,0,-1,-1,7,-1,-1]
 yield 'actual_anchor_arguments_permission_then_resident',command(flag32d=1,loading=0,speedType=0,
  objects=objects,cells=cells,houses=[[6,64],[0,1],[33,0]],h=[0,94*512+71,95*512+72,0],
  steps=[['U',0,0,-1,-1,-1,1,0]])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_resident.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'][k] is v)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 require(e['evidence']['audited_original_calls']==sum(len(parse(c)[1][1][1][-1]) for c in e['commands']))
 for c,row in zip(e['commands'],e['expected']):require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('R')==len(parse(c)[1][1][1][-1]))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for name in ('exe','native'):p.add_argument('--'+name,type=Path,required=True)
 for name in ('output','expectations','report'):p.add_argument('--'+name,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(a.output is None and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and a.report is None);folder=private_path(a.output,a.exe);require(not folder.exists())
  from original_infantry_resident import InfantryResidentOracle
  o=InfantryResidentOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,c in scenarios():
   try:row=o.run_resident(*parse(c))
   except BaseException:print('Failed',label,c,flush=True);raise
   commands.append(c);labels.append(label);expected.append(row)
  generation=time.monotonic()-now;require(o.ally_calls>0 and o.moving_calls>0 and o.resident_missions>0 and o.infantry_calls==o.audit_calls)
  meta=dict(FLAGS,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,receipt_contains_original_results_only=True,audited_original_calls=o.audit_calls,cases=len(commands),resident_mission_calls=o.resident_missions,ally_calls=o.ally_calls,moving_calls=o.moving_calls)
  source=folder/'expected.json';report=folder/'native-comparison.json'
  write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint))
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,commands[i],got,want))
 comparison=time.monotonic()-now;require(current==identities(a) and runner==hash_file(a.native))
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,expectations_sha256=fingerprint,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=len(commands) if a.expectations else 0,original_sequence_reuse_misses=0 if a.expectations else len(commands),original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start))
 print(len(commands),'complete Infantry resident sequences PASS')
if __name__=='__main__':main()
