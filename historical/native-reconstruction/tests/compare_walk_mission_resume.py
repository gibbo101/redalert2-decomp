# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual Walk IPiggyback under bounded Foot/complete Infantry resume; explicit original reuse."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_walk_mission_resume import verify
import compare_infantry_mission_resume as parent
ORIGINAL=('tests/compare_walk_mission_resume.py','tests/original_walk_mission_resume.py','tools/verify_walk_mission_resume.py')
NATIVE=('src/sim/WalkMissionResume.hpp','src/sim/InfantryMissionResume.hpp','src/sim/WalkMovement.hpp','src/sim/FootDestination.hpp','tests/walk_mission_resume_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_infantry_parent=True,bounded_foot_parent=True,actual_walk_query_predicate_release=True,actual_zero_percentage=True,empty_refill_profile=True,atomic_services_supplied=True,positive_unstack_unjoined=True,production_transfer_unjoined=True)
def require(v):
 if not v:raise ValueError('Walk resume evidence/domain differs')
def command(moving=0,piggy=0,flag=0,refs=3,globalrefs=7,diagnostic=0,**kw):
 return parent.command(**kw)+' '+' '.join(map(str,(moving,piggy,flag,refs,globalrefs,diagnostic)))
def parse(cmd):
 f=list(map(int,cmd.split()));require(len(f)==29 and f[0] in range(5) and all(-2**31<=x<2**31 for x in f))
 base=f[:23];base[0]=0 if base[0]==4 else base[0];parent.parse(' '.join(map(str,base)))
 require(0<=f[23]<=255 and f[24] in (0,1) and 0<=f[25]<=255 and 1<=f[26]<=0x7ffffffe and f[28] in range(4))
 require(f[0] in (2,3,4) or f[4] or not f[24] or f[23] or f[25] or f[28]==2)
 return f
def scenarios():
 for label,cmd in parent.scenarios():yield 'actual_walk_'+label,cmd+' 0 0 0 3 7 0'
 for moving,piggy,flag in itertools.product(range(256),(0,1),(0,1,128,255)):
  yield 'complete_predicate_raw_bytes',command(root=4,moving=moving,piggy=piggy,flag=flag)
 for moving,piggy,flag,refs,globalrefs in itertools.product((0,1,128,255),(0,1),(0,1,128,255),(1,3,0x7ffffffe),(-1,0,7,0x7fffffff)):
  if piggy and not moving and not flag:continue
  yield 'actual_retained_query_release',command(root=1,moving=moving,piggy=piggy,flag=flag,refs=refs,globalrefs=globalrefs)
 for diagnostic,root in itertools.product((1,2,3),(0,1)):
  yield 'diagnostic_ordered_lifetime_stores',command(root=root,diagnostic=diagnostic,piggy=1 if diagnostic==2 else 0)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_walk_mission_resume.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('F')==1)
 i=row.index('F');require(i%3==0 and len(row)==i+12)
 for j in range(0,i,3):require(1<=int(row[j])<=25 and all(0<=int(x)<2**32 for x in row[j+1:j+3]))
 require(all(0<=int(x)<2**32 for x in row[i+1:]) and 0<=int(row[i+1])<=255 and 0<=int(row[i+2])<=255 and all(int(x) in (0,1) for x in row[i+5:i+7]) and int(row[i+11])<=255 and 0<int(row[i+8])<2**31)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();verify(a.exe.read_bytes());start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_walk_mission_resume import WalkMissionResumeOracle
  oracle=WalkMissionResumeOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x503c00,0x4c6f10,0x6d48f0,0x4cdd70,0x6d1460,0x615360,0x6d1430,0x594770,0x5950d0,0x4cdaa0,0x454c70,0x71fab0,0x53d2b0,0x53d250,0x53d270,0x71fba0,0x71dea0,0x4c2df0,0x4c8b00)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Walk mission resume change sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
