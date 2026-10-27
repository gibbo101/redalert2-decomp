#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Infantry admission with direct Cell permission/Foot override."""
import argparse,copy,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
import compare_infantry_admission as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_permission import verify
ORIGINAL=(*parent.ORIGINAL,'tests/original_infantry_permission.py','tests/compare_infantry_permission.py','tools/verify_infantry_permission.py')
NATIVE=(*parent.source_closure(),'src/sim/FootPermissionOverride.hpp','src/sim/FootPermissionOverride.cpp','src/assets/NearbyCellAdmission.hpp')
SOURCES=(*ORIGINAL,*NATIVE,'tests/test_infantry_permission.py','CMakeLists.txt')
FLAGS=dict(complete_ordinary_Infantry_admission=True,actual_direct_Cell_permission_no_extra_lookup=True,
 complete_Foot_permission_override=True,actual_type_and_mission_getters=True,nonnull_Team_predicate_supplied=True,
 initial_records_and_associations_supplied=True,runtime_sight_enabled=False)
def require(v):
 if not v:raise ValueError('Infantry permission evidence/input differs')
def command(train=0,flag32c=0,team=0,teamResult=0,shape=(56,3,19,50,44),**kwargs):
 return 'P '+' '.join(map(str,(train,flag32c,team,teamResult,*shape)))+' '+parent.command(**kwargs)
def parse(c):
 t=c.split(maxsplit=10);require(len(t)==11 and t[0]=='P');options=list(map(int,t[1:10]));require(all(0<=n<=255 for n in options[:4]) and all(-2**31<=n<2**31 for n in options[4:]))
 return options,parent.parse(t[10])
def scenarios():
 for permitted,train,flag,mission,team in itertools.product((False,True),(0,255),(0,128),(2,4),((0,0),(1,0),(1,255))):
  objects=copy.deepcopy(parent.parent.OBJECTS);objects[0][4]=mission
  yield 'actual_permission_then_ordered_override',command(train=train,flag32c=flag,team=team[0],teamResult=team[1],shape=(56,3,19,50,44) if permitted else (0,0,0,0,0),flag32d=255,loading=0,objects=objects)
 for active,loading in ((0,0),(0,1),(1,-1),(128,1),(255,2**31-1)):
  yield 'permission_bypassed_without_query',command(flag32d=active,loading=loading)
 for bit5,bits in itertools.product((0,32),(0,0x7f800001,0xbf800000,0x3f800000)):
  cells=copy.deepcopy(parent.parent.CELLS);cells[0][6]=bit5;speeds=[0x3f800000]*12;speeds[0]=bits
  yield 'allowed_permission_preserves_speed_and_occupation_tail',command(flag32d=1,loading=0,cells=cells,speeds=speeds)
 # Strict direct-permission geometry/level/ramp edges in complete caller roots.
 for x,y,level,ramp in ((51,43,0,0),(51,44,0,0),(51,45,0,1),(-32768,32767,-128,1),(32767,-32768,127,0)):
  cells=copy.deepcopy(parent.parent.CELLS);cells[0][:2]=[x,y];cells[0][3:5]=[level,ramp]
  yield 'live_direct_Cell_geometry_and_elevation',command(flag32d=1,loading=0,cells=cells,steps=[['U',0,0,2,level,-1,1,255]])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_permission.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'][k] is v)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 require(e['evidence']['audited_original_calls']==sum(len(parse(c)[1][1][-1]) for c in e['commands']))
 for c,row in zip(e['commands'],e['expected']):require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('R')==len(parse(c)[1][1][-1]))
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
  from original_infantry_permission import InfantryPermissionOracle
  o=InfantryPermissionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,c in scenarios():
   try:row=o.run_permission(*parse(c))
   except BaseException:print('Failed',label,c,flush=True);raise
   commands.append(c);labels.append(label);expected.append(row)
  generation=time.monotonic()-now;require(o.permissions>0 and o.overrides>0 and o.teams>0 and o.infantry_calls==o.audit_calls)
  meta=dict(FLAGS,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,receipt_contains_original_results_only=True,audited_original_calls=o.audit_calls,cases=len(commands),permission_calls=o.permissions,override_calls=o.overrides,supplied_team_calls=o.teams)
  source=folder/'expected.json';report=folder/'native-comparison.json'
  write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint))
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,commands[i],got,want))
 comparison=time.monotonic()-now;require(current==identities(a) and runner==hash_file(a.native))
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,expectations_sha256=fingerprint,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=len(commands) if a.expectations else 0,original_sequence_reuse_misses=0 if a.expectations else len(commands),original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start))
 print(len(commands),'complete Infantry permission roots PASS')
if __name__=='__main__':main()
