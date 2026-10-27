#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Tag expiration original-only expectations and current native comparisons."""
import argparse,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_tag_expiration import verify
NATIVE=('src/sim/MissionTagExpiration.hpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/mission_tag_expiration_vectors.cpp')
ORIGINAL=('tests/original_mission_tag_expiration.py','tools/verify_mission_tag_expiration.py','tests/compare_mission_tag_expiration.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_tag_expiration.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Tag44_expiration_broadcast_map_logic_and_Cell=True,actual_Tag_kind_and_vector_find=True,
 borrowed_live_registry_map_Cell_Tag_and_global_fields=True,ordered_selected_stores_and_retained_vector_tails=True,
 supplied_RTTI_recipient_selection_effects_and_initial_associations=True,
 RaiseEvent_drain_destructor_discovery_scheduler_actions_and_runtime_join=False)
def require(ok):
 if not ok:raise ValueError('Tag expiration evidence/input differs')
def command(instances=(5,7),globals=(1,1),mode=0,selection=0,
            cells=((0x10001,513,1,1,2,0),(0x10002,514,2,0,1,1)),
            fallback=(0x1234abcd,1,1,1,1),points=(0x10001,0x10002,0xffffffff),
            maps=(1,2,1),logic=(1,1,2,1),recipients=(1,2,3),operations=((0,1,0xffffffff),)):
 values=[*instances,*globals,mode,selection,len(cells),*itertools.chain.from_iterable(cells),*fallback,
         len(points),*points,len(maps),*maps,len(logic),*logic,len(recipients),*recipients,
         len(operations),*itertools.chain.from_iterable(operations)]
 return 'X '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='X');v=list(map(int,t[1:]));position=0
 def take(n=1):
  nonlocal position
  require(n>=0 and position+n<=len(v));r=v[position:position+n];position+=n;return r
 instances=take(2);globals=take(2);mode,selection=take(2);require(all(-2**31<=x<2**31 for x in instances) and all(x in (0,1,2) for x in globals))
 require(mode in range(6) and selection in (0,1));n=take()[0];require(0<=n<=4);cells=[take(6) for _ in range(n)];fallback=take(5)
 for point,slot,tag,a,b,content in cells:require(0<=point<2**32 and -1<=slot<262144 and all(x in (0,1,2) for x in (tag,a,b)) and content in (0,1))
 require(0<=fallback[0]<2**32 and all(x in (0,1,2) for x in fallback[1:4]) and fallback[4] in (0,1))
 vectors=[]
 for role in range(4):
  count=take()[0];require(0<=count<=16);values=take(count)
  require(all(0<=x<2**32 for x in values) if role==0 else all(x in ((1,2,3) if role==3 else (0,1,2)) for x in values));vectors.append(values)
 count=take()[0];require(1<=count<=16);operations=[take(3) for _ in range(count)]
 for root,subject,removed in operations:require(root in range(5) and (0<=subject<=n if root==3 else subject in (1,2)) and 0<=removed<2**32)
 require(position==len(v));return dict(instances=instances,globals=globals,mode=mode,selection=selection,cells=cells,fallback=fallback,
  points=vectors[0],maps=vectors[1],logic=vectors[2],recipients=vectors[3],operations=operations)
def scenarios():
 for a,b,mode,removed in itertools.product((0,1,2),(0,1,2),range(6),(0,1,128,0xdead0100)):
  yield 'complete_broadcast_live_recipients_globals_and_raw_flag',command(globals=(a,b),mode=mode,selection=mode%2,operations=((0,1,removed),(0,2,removed)))
 for old,a,b,content,count in itertools.product((0,1,2),(0,1,2),(0,1,2),(0,1),(-2**31,0,2**31-1)):
  yield 'fallback_matching_and_unrelated_links_wrapped_counts',command(instances=(count,count),fallback=(0xffffffff,old,a,b,content),points=(0xffffffff,0x1234abcd,0xffffffff),operations=((3,2,0),(3,2,0)))
 for stored,query,slot in itertools.product((0x10001,0x10002,0xffffffff),(0x10001,0x0001fe00,0xffffffff,0x80000000,0x02000000,0x01ff01ff),(-1,0,513,514,262143)):
  yield 'signed_combined_index_stored_point_mismatch_and_shared_fallback',command(cells=((stored,slot,1,1,1,1),),fallback=(0x1234abcd,2,1,2,1),points=(query,stored,query),operations=((1,1,255),(1,1,0)))
 for registry in ((),(0,),(1,),(1,1),(2,1,2,1),(1,2,1,2,1),(0,1,0,1,0)):
  for subject in (1,2):
   yield 'map_removes_first_logic_removes_every_duplicate_and_retains_tails',command(maps=registry,logic=registry,operations=((1,subject,0),(2,subject,0),(4,subject,0)))
 for points in ((),(0x10001,),(0x10001,0x10001),(0x10002,0x10001,0x10002,0x10001),(0xffffffff,0xffffffff)):
  yield 'revisited_points_empty_registry_duplicate_and_alternate_tags',command(points=points,operations=((1,1,0),(1,2,0)))
 yield 'empty_registries',command(cells=(),points=(),maps=(),logic=(),recipients=(),operations=((0,1,0),(2,2,1)))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_tag_expiration.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},
  environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),
  native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('state')==1 and row.count('R')==len(parse(cmd)['operations']))
 require(e['evidence']['audited_original_calls']==sum(len(parse(c)['operations']) for c in e['commands']))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists())
  from original_mission_tag_expiration import MissionTagExpirationOracle
  oracle=MissionTagExpirationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=oracle.run(parse(cmd))
   except BaseException:print('Failed Tag expiration scenario',label,cmd,flush=True);raise
   commands.append(cmd);labels.append(label);expected.append(row)
  generation=time.monotonic()-now
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x6ecb90,0x559d80,0x53e110,0x47a340,0x47a460,0x42d120,0x4d5b40,0x6b42d0)))
  require(all(oracle.counts.get(k,0)>0 for k in ('supplied_RTTI','supplied_recipient','supplied_selection')))
  require(current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),selected_stores=dict(oracle.stores),audited_original_calls=oracle.audit_calls,
   evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta))
  fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr)
 require(run.returncode==0);actual=[r.split() for r in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True)
 require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),
  original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint)
 write_report(a.exe,report,result);print(len(commands),'Tag expiration sequences PASS;',meta['audited_original_calls'],'complete roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
