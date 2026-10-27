# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Team constructor and actual abstract base: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_construction import verify
ORIGINAL=('tests/compare_team_construction.py','tests/original_team_construction.py','tools/verify_team_construction.py')
NATIVE=('src/sim/TeamConstruction.hpp','tests/team_construction_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_team_constructor=True,actual_abstract_base=True,heap_tag_script_waypoint_map_supplied=True,production_member_creation=False)
def require(v):
 if not v:raise ValueError('Team construction evidence/domain differs')
def command(**kw):
 names=('type','house','flag','count','frame','argument','flags','point','second','tag','script','allocation','tagResult','scriptResult','profile','resize','mutation','expire')
 values=(1,1,128,0,123,0,255,0x7fff7fff,0x00590039,1,1,3,1,1,0,1,0,0)
 require(not set(kw)-set(names));return ' '.join(str(kw.get(k,v)) for k,v in zip(names,values))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==18 and all(v[k] in (0,1) for k in (0,1,9,10)) and all(0<=v[k]<=255 for k in (2,6)) and -2**31<=v[3]<2**31 and -2**31<=v[4]<2**31 and all(0<=v[k]<2**32 for k in (5,7,8,15)) and 0<=v[11]<=3 and all(0<=v[k]<=2 for k in (12,13)) and 0<=v[14]<=6 and 0<=v[16]<=7 and 0<=v[17]<=7 and (not v[17] or v[5]==0));return v
def scenarios():
 for type in (0,1):
  for house in (0,1):
   for flag in (0,1,128):
    for count in (-2147483648,-1,0,2147483647):yield 'type_house_raw_flags_and_wrapped_count',command(type=type,house=house,flag=flag,count=count)
 for point in (0x7fff7fff,0x7fff0039,0x00597fff,0x00590039,0xffffffff):
  for second in (0,0x7fff7fff,0xffff8000):
   for mutation in (0,3,7):yield 'independent_waypoints_live_type_and_empty_cell',command(point=point,second=second,mutation=mutation)
 for allocation in range(4):
  for tag in (0,1):
   for script in (0,1):
    for tagResult in range(3):
     for scriptResult in range(3):yield 'tag_script_allocation_failure_and_child_return_identity',command(allocation=allocation,tag=tag,script=script,tagResult=tagResult,scriptResult=scriptResult)
 for profile in range(6):
  for resize in (0,1,256,257):
   for mutation in (0,2,6):yield 'five_ordered_registries_live_count_backing_and_low_byte_resize',command(profile=profile,resize=resize,mutation=mutation)
 for mutation in (1,3,4,5,7):
  for flags in (0,7,128,255):yield 'late_frame_type_and_allocation_dependencies',command(mutation=mutation,flags=flags,point=0x00590039,argument=0xffffffff,frame=-2147483648)
 for expire in range(1,8):
  for point in (0x7fff7fff,0x00590039):
   for allocation in range(4):yield 'constructed_team_tag_expiration_live_reference_order',command(expire=expire,point=point,allocation=allocation)
 yield 'actual_objective_team_constructor_inputs_and_registry_counts',command(flag=0,flags=0,profile=6,frame=0,expire=1)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_construction.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+113)
 for j in range(0,i,6):
  require(1<=int(row[j])<=8)
  for v in row[j+1:j+6]:int(v)
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_construction import TeamConstructionOracle
  oracle=TeamConstructionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(1+bool(parse(c)[17]) for c in commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['0x6b7430']==len(commands) and oracle.counts['0x40ff10']==len(commands))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team construction sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
