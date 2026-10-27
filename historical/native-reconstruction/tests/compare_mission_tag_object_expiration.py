#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Object Tag-expiration original-only expectations and native comparisons."""
import argparse,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_tag_object_expiration import verify
NATIVE=('src/sim/MissionTagObjectExpiration.hpp','src/sim/MissionTagExpiration.hpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/mission_tag_object_expiration_vectors.cpp')
ORIGINAL=('tests/original_mission_tag_object_expiration.py','tools/verify_mission_tag_object_expiration.py','tests/compare_mission_tag_object_expiration.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_tag_object_expiration.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Object_pointer_expiration_with_Tag_subject=True,wrapped_Tag_reference_count_and_low_byte_link_splice=True,
 supplied_initial_associations=True,broadcast_RaiseEvent_drain_discovery_actions_and_runtime_join=False)
def require(ok):
 if not ok:raise ValueError('Object Tag expiration evidence/input differs')
def command(instances=(2,7),object_tag=1,object_link=1,subject=1,next=0,operations=(0,1,256,257)):
 return 'P '+' '.join(map(str,(*instances,object_tag,object_link,subject,next,len(operations),*operations)))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='P');v=list(map(int,t[1:]));require(len(v)>=7)
 a,b,object_tag,object_link,subject,next,count=v[:7];operations=v[7:]
 require(all(-2**31<=x<2**31 for x in (a,b)) and all(0<=x<=2 for x in (object_tag,object_link,next)) and subject in (1,2))
 require(1<=count<=32 and len(operations)==count and all(0<=x<2**32 for x in operations))
 return dict(instances=(a,b),object_tag=object_tag,object_link=object_link,subject=subject,next=next,operations=operations)
def scenarios():
 for instances,object_tag,object_link,subject,next in itertools.product(((-2**31,2),(-1,0),(0,0),(1,7),(2**31-1,-2**31)),range(3),range(3),(1,2),range(3)):
  yield 'independent_Tag_and_link_matching_wrapped_reference_count',command(instances,object_tag,object_link,subject,next,(0,))
 for removed in (0,1,2,255,256,257,0xffffff00,0xffffffff):
  for subject,next in itertools.product((1,2),range(3)):
   yield 'raw_removed_low_byte_and_live_subject_link',command((3,5),subject,subject,subject,next,(removed,))
 for operations in ((0,0),(1,1),(0,1),(1,0),(256,257,0xffffffff),(1,1,1,1)):
  yield 'repeated_callback_after_detachment_preserves_independent_link',command((1,-2**31),1,1,1,2,operations)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_tag_object_expiration.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):require(isinstance(row,list) and all(isinstance(x,str) for x in row) and row.count('state')==1 and row.count('R')==len(parse(cmd)['operations']))
 require(e['evidence']['audited_original_calls']==sum(len(parse(c)['operations']) for c in e['commands']))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_tag_object_expiration import MissionTagObjectExpirationOracle
  oracle=MissionTagObjectExpirationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x5d3bd0']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),selected_stores=dict(oracle.stores),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0)
 actual=[r.split() for r in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands);write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Object Tag expiration sequences PASS;',meta['audited_original_calls'],'complete roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
