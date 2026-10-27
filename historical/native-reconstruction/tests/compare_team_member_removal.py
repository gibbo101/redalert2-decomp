# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team RemoveMember parent with supplied named children."""
import itertools
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_member_removal import verify
ORIGINAL=('tests/compare_team_member_removal.py','tests/original_team_member_removal.py','tools/verify_team_member_removal.py')
NATIVE=('src/sim/TeamMemberRemoval.hpp','src/sim/TeamConstruction.hpp','tests/team_member_removal_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_remove_member_parent=True,named_children_supplied=True,production_scheduling=False)
NAMES=('members','target','reverse','slot','leaders','taskCount','match','taskPresent','initialCount','initialThreat','threat','slotValue','owns','tag','controlled','loading','onMap','busy','limbo','suppress','mutation')
DEFAULT=(4,0,0,-1,1,1,0,2,4,1000,598,4,1,1,1,0,1,0,0,0,0)
def require(v):
 if not v:raise ValueError('Team removal evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(map(str,(kw.get(k,v) for k,v in zip(NAMES,DEFAULT))))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==21 and all(-2**31<=v<2**31 for v in f))
 require(1<=f[0]<=4 and 0<=f[1]<4 and f[2] in (0,1) and -1<=f[3]<=6 and 0<=f[4]<16 and -1<=f[5]<=6 and -1<=f[6]<6 and f[7] in (0,1,2) and f[12] in (0,1) and f[13] in (0,1,2) and all(0<=f[i]<=255 for i in (16,17,18)) and 0<=f[20]<=5);require(not (f[3]==6 and f[5]<0 and f[7]==2));return f
def scenarios():
 for members,target,reverse,leaders in itertools.product(range(1,5),range(4),(0,1),(0,1,15)):
  yield 'head_middle_tail_absent_and_leadership',command(members=members,target=target,reverse=reverse,leaders=leaders)
 for slot,count,match,present in itertools.product((-1,0,2,5,6),(-1,0,1,6),(-1,0,5),(0,1,2)):
  if not (slot==6 and count<0 and present==2):yield 'signed_scan_unsigned_final_slot_and_nullable_task',command(slot=slot,taskCount=count,match=match,taskPresent=present)
 for controlled,tag,owns in itertools.product((0,1,256,-1),(0,1,2),(0,1)):
  yield 'raw_house_control_tag_and_foreign_team',command(controlled=controlled,tag=tag,owns=owns)
 for loading,onMap,busy,limbo,suppress in itertools.product((0,1),(0,255),(0,128),(0,255),(0,256,1,-1)):
  yield 'late_resume_raw_low_byte_gates',command(loading=loading,onMap=onMap,busy=busy,limbo=limbo,suppress=suppress)
 for mutation,target,reverse in itertools.product(range(1,6),range(4),(0,1)):
  yield 'saved_task_and_late_threat_head_tag_diagnostics',command(mutation=mutation,target=target,reverse=reverse,controlled=0)
 for count,threat,total,slots in itertools.product((-2147483648,0,-1,2147483647),(-2147483648,-1,0,2147483647),(0,-1),(0,-1)):
  yield 'wrapping_member_threat_task_counts',command(initialCount=count,threat=threat,initialThreat=total,slotValue=slots)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_member_removal.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+50)
 for j in range(0,i,6):require(int(row[j]) in (1,2,3,4,5,6,9));[int(v) for v in row[j+1:j+6]]
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_member_removal import TeamMemberRemovalOracle
  oracle=TeamMemberRemovalOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team member removal sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
