# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Unit/Aircraft expiration with a distinct Team34 subject."""
import itertools
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_vehicle_expiration import verify
ORIGINAL=('tests/compare_team_vehicle_expiration.py','tests/original_team_vehicle_expiration.py','tools/verify_team_vehicle_expiration.py')
import compare_mission_typed_tag_expiration as typed
import compare_mission_techno_tag_expiration as techno
NATIVE=typed.NATIVE
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_Unit_Aircraft_Team_subject_expiration=True,actual_inherited_Object_Radio_Techno_Foot=True,non_Tag_subject_and_preserved_Object_Tag=True,named_children_and_startup_supplied=True,production_scheduling=False)
import compare_team_foot_expiration as foot

def require(v):
 if not v:raise ValueError('Team vehicle expiration evidence/domain differs')
def command(base,vehicle=0,derived=0,link=0,mutation=0):
 return base+' V '+str(vehicle)+' '+str(derived)+' '+str(link)+' '+str(mutation)
def parse(c):
 base,extra=c.rsplit(' V ',1);f=foot.parse(base);values=list(map(int,extra.split()));require(len(values)==4)
 vehicle,derived,link,mutation=values;require(f['root']==4 and vehicle in (0,1) and 0<=derived<=16 and 0<=link<=16 and mutation in (0,1,2));f.update(vehicle=vehicle,derived=derived,link=link,mutation=mutation);return f
def scenarios():
 for vehicle,derived,link,removed,mutation in itertools.product((0,1),(0,1,2,9),(0,1,2,9),(0,256,1,257,0xffffffff),(0,1,2)):
  base=foot.command(root=4,operations=[removed,1],fields=[0]*15)
  yield 'derived_live_fields_low_removal_and_repeated_calls',command(base,vehicle,derived,link,mutation)
 for label,base in foot.scenarios():
  if foot.parse(base)['root']==4:
   for vehicle in (0,1):yield 'inherited_'+label,command(base,vehicle,1,1,vehicle+1)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_vehicle_expiration.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(isinstance(row,list) and all(isinstance(x,str) for x in row) and row.count('state')==1 and row.count('TYPED')==1 and row.count('VEHICLE')==1 and row.count('R')>=1)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_vehicle_expiration import TeamVehicleExpirationOracle
  oracle=TeamVehicleExpirationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  require(all(oracle.counts[hex(entry)]>0 for entry in (0x5d3bd0,0x636ba0,0x6d2d10,0x4c8460,0x707e90,0x41adb0,0x468a70,0x468120,0x4d5b40)))
  require(not oracle.counts['0x548070'] and not oracle.counts['0x5d4e40'] and not oracle.counts['supplied.owner'])
  require(oracle.audit_calls==sum(len(parse(c)['operations']) for c in commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True,audited_original_calls=oracle.audit_calls,actual_entry_counts=dict(oracle.counts))
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team vehicle expiration sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
