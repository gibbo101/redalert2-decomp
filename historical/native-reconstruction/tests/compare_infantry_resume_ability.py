# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual promotion/Type/QueueMission under bounded Foot and complete Infantry resume."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_infantry_resume_ability import verify
import compare_walk_mission_resume as parent
ORIGINAL=('tests/compare_infantry_resume_ability.py','tests/original_infantry_resume_ability.py','tools/verify_infantry_resume_ability.py')
NATIVE=('src/sim/TechnoAbility.hpp','src/sim/UnitDiscovery.cpp','src/sim/WalkMissionResume.hpp','src/sim/InfantryMissionResume.hpp','src/sim/WalkMovement.hpp','src/sim/FootDestination.hpp','tests/infantry_resume_ability_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_infantry_parent=True,bounded_foot_parent=True,actual_walk_query_predicate_release=True,actual_promotion_type_ability=True,actual_queue_zero_argument=True,atomic_services_supplied=True,production_transfer_unjoined=True)
def require(v):
 if not v:raise ValueError('Infantry resume ability evidence/domain differs')
def command(root=0,index=16,vet=0,vflag=0,eflag=0,mutation=0,at=0,**kw):
 f=parent.command(root=0,**kw).split();f[0]=str(root)
 return ' '.join(f)+' '+' '.join(map(str,(index,vet,vflag,eflag,mutation,at)))
def parse(cmd):
 f=list(map(int,cmd.split()));require(len(f)==35 and f[0] in (0,5));base=f[:29].copy();base[0]=0;parent.parse(' '.join(map(str,base)))
 require(f[18]==0 and f[22]==0 and f[28]==0 and f[29] in range(18) and 0<=f[30]<2**64 and 0<=f[31]<=255 and 0<=f[32]<=255 and f[33] in range(4) and f[34] in range(9))
 require(f[0]==5 or f[29]==16);return f
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def scenarios():
 values=(0,0x8000000000000000,1,bits(-1.),bits(1.)-1,bits(1.),bits(1.5),bits(2.)-1,bits(2.),bits(2.5),bits(float('inf')),bits(-float('inf')),0x7ff8000000000000,0xfff8000012345678)
 for vet,vflag,eflag in itertools.product(values,(0,1,128,255),(0,1,128,255)):
  yield 'complete_ability16_predicates_raw_type_bytes',command(root=5,vet=vet,vflag=vflag,eflag=eflag)
 for index,vet,vflag,eflag in itertools.product((0,5,17),(bits(1.5),bits(2.5)),(0,255),(0,128)):
  yield 'ability_offset_and_elite_inheritance',command(root=5,index=index,vet=vet,vflag=vflag,eflag=eflag)
 for raw,team,b00,vet,flags in itertools.product(range(-1,29),(0,1),(0,1,128,255),(bits(0.),bits(1.5),bits(2.5)),((0,0),(1,0),(0,1),(255,128))):
  yield 'complete_resume_actual_ability_and_queue',command(raw=raw,team=team,b00=b00,vet=vet,vflag=flags[0],eflag=flags[1])
 for root,vet,mutation,at in itertools.product((0,5),(bits(0.),bits(1.5),bits(2.5)),(1,2,3),range(1,9)):
  yield 'live_veterancy_saved_type_and_byte_diagnostic',command(root=root,raw=12,team=1,vet=vet,vflag=0,eflag=255,mutation=mutation,at=at)
 for raw,control5,control7,entered in itertools.product((0,5,11,12,25,28),(0,128),(0,255),(0,1)):
  yield 'resume_early_exits_and_reentry',command(raw=raw,control5=control5,control7=control7,entered=entered)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_resume_ability.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('F')==1 and row.count('A')==1)
 i=row.index('F');j=row.index('A');require(i%3==0 and j==i+12 and len(row)==j+10)
 for k in range(0,i,3):require(1<=int(row[k])<=33 and all(0<=int(x)<2**32 for x in row[k+1:k+3]))
 require(all(v in ('F','A') or 0<=int(v)<2**32 for v in row))
 require(int(row[i+1])<=255 and int(row[i+2])<=255 and all(int(row[i+k]) in (0,1) for k in (5,6)) and int(row[j+3]) in (0,1) and all(int(row[j+k])<=255 for k in (4,5,6,7,9)))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();verify(a.exe.read_bytes());start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_resume_ability import InfantryResumeAbilityOracle
  oracle=InfantryResumeAbilityOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x503c00,0x4c6f10,0x6d7910,0x7133a0,0x713420,0x6c12c0,0x506950,0x594cb0)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry resume ability sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
