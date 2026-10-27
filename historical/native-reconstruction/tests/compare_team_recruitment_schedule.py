# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team recruitment schedule parent with supplied child services: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_recruitment_schedule import verify
ORIGINAL=('tests/compare_team_recruitment_schedule.py','tests/original_team_recruitment_schedule.py','tools/verify_team_recruitment_schedule.py')
NATIVE=('src/sim/TeamRecruitmentSchedule.hpp','src/sim/TeamReadiness.hpp','src/sim/UnitDiscovery.cpp','tests/team_recruitment_schedule_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(initial_preready_complete_paths=True,actual_readiness_house_member_continuation=True,anchor_selector_supplied=True,production_team_ai=False)
NAMES=('quantity','head','anchored','refresh','filled78','old7a','old7b','timer82','timer64','remaining6C','created50','frame','mode','taskCount','current','required','human','control','successful','blocked','mutation','timeout','direct','target3C')
DEFAULT=(0,0,0,1,0,1,0,0,-1,0,0,0,0,1,0,4,0,0,1,0,0,150,0,0)
def require(v):
 if not v:raise ValueError('Team recruitment schedule evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==len(NAMES) and all(-2**31<=x<2**31 for x in v));d=dict(zip(NAMES,v))
 require(all(d[k] in (0,1) for k in ('head','anchored','successful','direct')) and all(0<=d[k]<=255 for k in ('refresh','filled78','old7a','old7b','timer82','human','control','blocked')) and -1<=d['taskCount']<=6 and 0<=d['mutation']<=3)
 if d['direct']:require(not d['head'] or d['target3C']==0);return v
 require(d['target3C']==0)
 # Readiness may destroy an empty previously-filled Team. Otherwise this lane
 # excludes activation/full quantity and empty expiry; entered paths stay honest.
 remaining=d['remaining6C']&0xffffffff
 if d['timer64']!=-1:
  elapsed=(d['frame']-d['timer64']+2**31)%2**32-2**31
  remaining=0 if elapsed>=d['remaining6C'] else (remaining-elapsed)&0xffffffff
 if d['timer82'] and remaining:return v
 destroyed=d['refresh'] and d['quantity']<=0 and d['filled78']
 if destroyed:return v
 if d['refresh'] and d['quantity']>0:
  required=(max(0,d['taskCount'])*d['required']+2**31)%2**32-2**31;require(d['quantity']!=required)
 willHaveHead=d['head'] or d['successful'] and d['taskCount']>0 and d['current']<d['required'] and (not(d['human'] if d['mode'] else d['human'] or d['control']) or not d['filled78'])
 if not willHaveHead:require(not d['filled78'] and (not d['mode'] or (d['frame']-d['created50']+2**31)%2**32-2**31<=d['timeout']))
 return v
def scenarios():
 yield 'actual_first_Team_tick',command()
 for head in (0,1):
  for anchored in (0,1):
   for refresh in (0,128):
    for qty in (-1,0,1,2):
     for success in (0,1):yield 'initial_recruitment_and_null_continuation',command(head=head,anchored=anchored,refresh=refresh,quantity=qty,successful=success)
 for slots in (-1,0,1,2,6):
  for current in (-2147483648,-1,0,3,4,2147483647):
   for mutation in (0,1,2,3):yield 'signed_counts_live_TaskForce_reload',command(head=1,taskCount=slots,current=current,mutation=mutation)
 for mode in (0,1,-1):
  for human in (0,128):
   for control in (0,255):
    for filled in (0,128):yield 'House_filled_gate_and_raw_bytes',command(quantity=1,head=1,mode=mode,human=human,control=control,filled78=filled)
 for start in (-2147483648,-1,0,2147483647):
  for frame in (-2147483648,-1,0,1,2147483647):
   for remaining in (-2147483648,-1,0,1,2,2147483647):yield 'signed_wrapped_timer_gate',command(head=1,timer82=128,timer64=start,frame=frame,remaining6C=remaining)
 for refresh in (0,128):
  for old7a in (0,1,128,255):
   for old7b in (0,1,128,255):yield 'readiness_flag_and_anchor_order',command(head=1,refresh=refresh,old7a=old7a,old7b=old7b)
 for filled in (1,128):yield 'readiness_destruction_short_circuit',command(filled78=filled)
 for head in (0,1):yield 'complete_null_target_continuation',command(direct=1,head=head)
 yield 'empty_head_bypasses_nonnull_target',command(direct=1,target3C=17)
 for elapsed in (-1,0,150):yield 'empty_Team_timeout_nonexpired',command(successful=0,mode=1,frame=elapsed)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_recruitment_schedule.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+33)
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_recruitment_schedule import TeamRecruitmentScheduleOracle
  oracle=TeamRecruitmentScheduleOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x6b7ad0']>0 and oracle.counts['0x6ba1a0']>0 and oracle.counts['0x4f52f0']>0)
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team recruitment schedule sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
