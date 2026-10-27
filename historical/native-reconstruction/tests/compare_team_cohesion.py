# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team cohesion parent with supplied child services: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_cohesion import verify
ORIGINAL=('tests/compare_team_cohesion.py','tests/original_team_cohesion.py','tools/verify_team_cohesion.py')
NATIVE=('src/sim/TeamCohesion.hpp','src/sim/TeamReadiness.hpp','src/sim/MissionScriptState.hpp','src/sim/UnitDiscovery.cpp','tests/team_cohesion_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_cohesion=True,activation_complete_to_return=True,actual_readiness_script_mission=True,distance_commands_nearby_anchor_supplied=True,script_dispatch_unjoined=True)
NAMES=('mode','members','onmap','health','flag76','leaders','distance','normal','relaxed','action','loading','kind','mission','queued','queuedA4','target','alternate','old75','blocked','old7b')
DEFAULT=(0,4,1,125,0,1,128,512,768,-1,0,15,12,-1,128,0,0,128,0,0)
def require(v):
 if not v:raise ValueError('Team cohesion evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==len(NAMES) and all(-2**31<=x<2**31 for x in v));d=dict(zip(NAMES,v))
 require(d['mode'] in (0,1) and 0<=d['members']<=4 and 0<=d['leaders']<=15 and all(0<=d[k]<=255 for k in ('onmap','flag76','queuedA4','old75','blocked','old7b')) and all(d[k] in (0,1) for k in ('target','alternate')))
 require(d['mode'] or d['members']>0)
 return v
def scenarios():
 yield 'actual_full_Team_activation_regroup',command()
 for mode in (0,1):
  for members in range(1,5):
   for leaders in (0,1,7):
    for distance in (-2147483648,0,512,513,768,769,2147483647):yield 'activation_or_complete_regroup_distance',command(mode=mode,members=members,leaders=leaders,distance=distance)
 for action in (-1,0,50,53,54,55):
  for distance in (512,513,768,769):yield 'current_script_selects_normal_relaxed',command(mode=1,action=action,distance=distance)
 for mission in (-1,2,5,11,12,19,28):
  for queued in (-1,2,5,11):
   for distance in (0,513):yield 'actual_mission_queue_and_repeated_query',command(mode=1,leaders=7,mission=mission,queued=queued,distance=distance,alternate=1)
 for onmap in (0,128):
  for health in (-1,0,125):
   for flag76 in (0,128):
    for loading in (0,1):yield 'eligibility_raw_gate',command(mode=1,onmap=onmap,health=health,flag76=flag76,loading=loading)
 for kind in (2,15):
  for target in (0,1):
   for alternate in (0,1):
    for leaders in (0,7):yield 'far_member_command_gates',command(mode=1,distance=513,kind=kind,target=target,alternate=alternate,leaders=leaders)
 for old75 in (0,1,128,255):
  for old7b in (0,1,128,255):yield 'activation_and_regroup_flag_order',command(old75=old75,old7b=old7b)
 yield 'empty_Team_regroup_clears75',command(mode=1,members=0)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_cohesion.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+39)
 for j in range(0,i,6):require(1<=int(row[j])<=16);[int(v) for v in row[j+1:j+6]]
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_cohesion import TeamCohesionOracle
  oracle=TeamCohesionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x6b7ad0']>0 and oracle.counts['0x6b9f40']>0 and oracle.counts['0x594cb0']>0)
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team cohesion sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
