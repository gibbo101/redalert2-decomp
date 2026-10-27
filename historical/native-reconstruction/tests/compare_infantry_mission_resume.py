# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete503C00 and bounded4C6F10 decisions; supplied named locomotor/effect services."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_infantry_mission_resume import verify
ORIGINAL=('tests/compare_infantry_mission_resume.py','tests/original_infantry_mission_resume.py','tools/verify_infantry_mission_resume.py')
NATIVE=('src/sim/InfantryMissionResume.hpp','tests/infantry_mission_resume_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_infantry_parent=True,bounded_foot_parent=True,complete_techno_parent=True,locomotor_effects_supplied=True,production_transfer_unjoined=True)
def require(v):
 if not v:raise ValueError('Infantry resume evidence/domain differs')
def command(root=0,raw=0,queued=-1,special=-1,entered=0,pending=0,status=0,animation=-1,arg=1,alternate=0,target=0,team=0,controlled=1,house=0,limit=1,predicate=0,c11=0,c14=0,ability=0,b00=0,control5=0,control7=0,mutation=0):
 return ' '.join(map(str,(root,raw,queued,special,entered,pending,status,animation,arg,alternate,target,team,controlled,house,limit,predicate,c11,c14,ability,b00,control5,control7,mutation)))
def parse(cmd):
 f=list(map(int,cmd.split()));require(len(f)==23 and all(-2**31<=x<2**31 for x in f) and f[0] in range(4) and -1<=f[1]<=28 and -1<=f[2]<=28 and f[3] in (-1,0) and 0<=f[4]<=255 and f[5]<=0 and f[9] in (0,1) and f[10] in (0,1) and f[11] in (0,1) and all(0<=f[i]<=255 for i in (16,17,19,20,21)) and f[22] in range(5))
 require(f[4] or f[0] in (2,3) or f[7]==-1 or not f[8]&255 or (f[1]==25 and f[6]!=0))
 return f
def scenarios():
 for raw,queued,root in itertools.product((-1,0,1,2,5,8,11,17,25,28),(-1,0,8,17),(0,3)):
  for alternate,target in ((0,0),(1,0),(0,1)):
   yield 'mission_priority_return',command(root=root,raw=raw,queued=queued,alternate=alternate,target=target)
 for controlled,team,house,limit,predicate,c11,c14,ability,b00 in itertools.product((0,1,256),(0,1),(-1,0,1),(0,1),(0,256,128),(0,128),(0,255),(0,256,128),(0,255)):
  # Pairwise coverage of the remaining flags plus exhaustive raw low-byte gates.
  if (house+limit+c11+c14+b00)%3:continue
  yield 'idle_control_type_team',command(controlled=controlled,team=team,house=house,limit=limit,predicate=predicate,c11=c11,c14=c14,ability=ability,b00=b00)
 for entered,root in itertools.product(range(256),(0,1,2)):
  yield 'entry_latch',command(root=root,entered=entered)
 for off,value in itertools.product((5,7),(0,1,128,255)):
  yield 'mission_control_byte',command(control5=value if off==5 else 0,control7=value if off==7 else 0)
 for root,special,arg in itertools.product((0,1,2,3),(-1,0),(0,1,256,-1)):
  yield 'root_special_argument',command(root=root,special=special,arg=arg)
 for mutation in range(1,5):
  for raw in (0,1,-1):
   yield 'diagnostic_live_reads',command(raw=raw,queued=0,team=1,ability=128,mutation=mutation)
 for pending in (-2**31,-1,0):
  yield 'signed_empty_count',command(root=1,pending=pending)
 for arg,raw,status in ((256,0,0),(1,25,1),(1,25,-1)):
  yield 'animation_bypass',command(root=1,arg=arg,raw=raw,status=status,animation=7)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_mission_resume.py',{'sources':dict.fromkeys(ORIGINAL)})
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
 i=row.index('F');require(i%3==0 and len(row)==i+7)
 for j in range(0,i,3):require(1<=int(row[j])<=19 and all(0<=int(x)<2**32 for x in row[j+1:j+3]))
 require(all(0<=int(x)<2**32 for x in row[i+1:]) and 0<=int(row[i+1])<=255 and 0<=int(row[i+2])<=255 and all(int(x) in (0,1) for x in row[-2:]))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();verify(a.exe.read_bytes());start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_mission_resume import InfantryMissionResumeOracle
  oracle=InfantryMissionResumeOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x503c00,0x4c6f10,0x6d48f0,0x4cdd70,0x6d1460,0x615360,0x6d1430,0x594770,0x5950d0,0x4cdaa0)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry mission resume change sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
