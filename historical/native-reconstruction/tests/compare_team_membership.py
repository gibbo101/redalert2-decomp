# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team membership parent with supplied child services: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_membership import verify
ORIGINAL=('tests/compare_team_membership.py','tests/original_team_membership.py','tools/verify_team_membership.py')
NATIVE=('src/sim/TeamMembership.hpp','src/sim/TeamConstruction.hpp','src/sim/TeamAdmission.hpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','src/sim/MissionTagExpiration.hpp','tests/team_membership_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_team_membership_parent=True,children_supplied=True,production_recruitment=False)
NAMES=('op','nonnull','admit','slot','prior','head','anchor','tag','group','tfGroup','hasTF','b3','count52c','ed','threat','quantity','threatTotal','slotCount','script','weight','weighted','kind','onmap','health','limbo','leader','active','flagADA','permission','mutation','removed','subject','positionProfile')
DEFAULT=(0,1,1,0,0,0,0,1,-2,-1,1,0,0,0,0,0,0,0,-1,0,0,15,1,125,0,0,1,0,0,0,1,0,0)
def require(v):
 if not v:raise ValueError('Team membership evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==len(NAMES) and all(-2**31<=x<2**31 for x in v));d=dict(zip(NAMES,v))
 require(d['op'] in range(4) and all(d[k] in (0,1) for k in ('nonnull','prior','tag','hasTF','positionProfile')) and 0<=d['slot']<6 and 0<=d['head']<=3 and 0<=d['anchor']<=2 and 0<=d['subject']<8 and 0<=d['mutation']<=4)
 require(all(0<=d[k]<=255 for k in ('b3','ed','weight','onmap','limbo','leader','active','flagADA')) and d['script']!=10)
 require(not(d['op']==0 and d['head']==1) and not(d['op']==3 and d['head']) and not(d['op']==2 and d['subject']==1 and not d['head']))
 return v
def scenarios():
 yield 'actual_E1_explicit_add_supplied_children',command()
 for key,values in dict(nonnull=(0,),admit=(0,1,256,257,-1),slot=(0,5),prior=(0,1),head=(0,2,3),anchor=(0,1,2),tag=(0,1),group=(-2,-1,0,7),tfGroup=(-1,7),hasTF=(0,1),b3=(0,128),count52c=(-1,0,1),ed=(0,128),threat=(-2147483648,-1,2147483647),quantity=(-1,2147483647),threatTotal=(-1,2147483647),slotCount=(-1,2147483647),mutation=(1,2,3,4)).items():
  for value in values:yield 'add_ordered_fields_'+key,command(**{key:value})
 for b3 in (0,128):
  for count52c in (-1,0,1):
   for mutation in (0,2,3):yield 'late_tag_and_type_children',command(b3=b3,count52c=count52c,mutation=mutation)
 for head in (0,1,2,3):
  for key,values in dict(kind=(2,15),onmap=(0,128),health=(0,-1,125),limbo=(0,128),leader=(0,128),active=(0,128),weight=(0,128),weighted=(0,1,256,257),count52c=(-1,0,1),flagADA=(0,128),permission=(0,1,-1),positionProfile=(0,1),mutation=(0,2,4)).items():
   for value in values:yield 'normal_anchor_'+key,command(op=1,head=head,**{key:value})
 for count52c in (0,1):
  for flagADA in (0,128):
   for permission in (0,1):yield 'passenger_fallback_live_head',command(op=1,head=1,kind=2,count52c=count52c,flagADA=flagADA,permission=permission,mutation=4,weight=128,weighted=257,positionProfile=1)
 for subject in range(8):
  for removed in (0,1,256,257):yield 'populated_expiration_low_byte',command(op=2,head=1,anchor=2,subject=subject,removed=removed)
 for permission in (0,1):
  for ed in (0,128):yield 'three_distinct_members_prepend_and_first_anchor',command(op=3,permission=permission,ed=ed,threat=-1)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_membership.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+44)
 for j in range(0,i,6):require(1<=int(row[j])<=3);[int(v) for v in row[j+1:j+6]]
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_membership import TeamMembershipOracle
  oracle=TeamMembershipOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(3 if parse(c)[0]==3 else 1 for c in commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x6b8cc0']>0 and oracle.counts['0x6b9610']>0 and oracle.counts['0x6b9590']>0)
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team membership sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
