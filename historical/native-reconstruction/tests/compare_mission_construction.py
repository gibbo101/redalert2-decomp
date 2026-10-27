# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Tag/Trigger/Script constructors and actual base/reset: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_mission_construction import verify
ORIGINAL=('tests/compare_mission_construction.py','tests/original_mission_construction.py','tools/verify_mission_construction.py')
NATIVE=('src/sim/MissionConstruction.hpp','src/sim/TeamConstruction.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','src/sim/MissionTag.hpp','src/sim/MissionTagExpiration.hpp','tests/mission_construction_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_tag_trigger_script_construction=True,actual_base_reset=True,heap_resize_and_timer_padding_supplied=True,production_membership=False)
def require(v):
 if not v:raise ValueError('Mission construction evidence/domain differs')
def command(**kw):
 names=('op','type','chain','difficulty','permissions','trueByte','event','value','frame','flags','profile','resize','mutation','scratch')
 values=(3,1,1,0,15,1,7,1,123,255,0,1,0,0x5a5a5a5a)
 require(not set(kw)-set(names));return ' '.join(str(kw.get(k,v)) for k,v in zip(names,values))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==14 and 0<=v[0]<=3 and v[1] in (0,1) and 0<=v[2]<=2 and -2**31<=v[3]<2**31 and 0<=v[4]<=15 and 1<=v[5]<=255 and v[6] in (4,7,13,47) and all(-2**31<=v[k]<2**31 for k in (7,8,13)) and 0<=v[9]<=255 and 0<=v[10]<=5 and 0<=v[11]<2**32 and 0<=v[12]<=5);return v
def scenarios():
 for difficulty in (-1,0,1,2,3):
  for permissions in range(16):
   for trueByte in (1,128):yield 'trigger_raw_permission_bytes_and_out_of_range_difficulty',command(op=1,difficulty=difficulty,permissions=permissions,trueByte=trueByte)
 for op in range(4):
  for type in (0,1):
   for chain in (0,1,2):yield 'complete_constructors_null_types_and_reversed_live_trigger_links',command(op=op,type=type,chain=chain)
 for profile in range(5):
  for resize in (0,1,256,257):
   for mutation in (0,1,5):yield 'shared_physical_registries_growth_low_byte_and_late_count',command(profile=profile,resize=resize,mutation=mutation,chain=2)
 for mutation in (2,3,4):
  for chain in (1,2):yield 'tag_saved_type_live_head_and_next_after_constructor',command(chain=chain,mutation=mutation)
 for event in (7,13):
  for value in (-2147483648,-1,0,1,2147483647):
   for flags in (0,7,128,255):yield 'actual_reset_or_skip_with_supplied_timer_padding_and_base_mask',command(event=event,value=value,flags=flags,chain=2,frame=-2147483648,scratch=-1)
 yield 'actual_team_children_adopted_arguments_and_registry_counts',command(frame=0,flags=0,profile=5)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_construction.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+167)
 for j in range(0,i,6):
  require(1<=int(row[j])<=4)
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_construction import MissionConstructionOracle
  oracle=MissionConstructionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(2 if parse(c)[0]==3 else 1 for c in commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[hex(a)]>0 for a in (0x6b3870,0x6ed220,0x668730,0x40ff10,0x6ed680)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission construction sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
