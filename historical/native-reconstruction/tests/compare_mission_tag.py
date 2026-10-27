#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Tag/retirement calls; original-only expectations and native replays."""
import argparse,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_tag import verify
NATIVE=('src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/mission_tag_vectors.cpp')
ORIGINAL=('tests/original_mission_tag.py','tools/verify_mission_tag.py','tests/compare_mission_tag.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_tag.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Tag_RaiseEvent_and_Trigger_Destroy=True,actual_Trigger_event_action_traversal=True,
 actual_Object_tag_assignment_null_Cell_clear_and_word_lookup=True,shared_deferred_queue_and_ordered_stores=True,
 supplied_expiration_broadcast_heap_action_effects_and_initial_records=True,
 deferred_drain_discovery_scheduler_and_runtime_join=False)
def require(ok):
 if not ok:raise ValueError('Mission Tag evidence/input differs')
def op(kind=0,frame=0,suppress=0,pulse=4,present=1,location=0x10001,force=0,source=1,subject=0):return (kind,frame,suppress,pulse,present,location,force,source,subject)
def command(persistence=(0,2),instances=(2,7),executing=0,destroyed=0,owner=1,cell=1,fallback=2,
            capacity=8,count=0,growth=2,owns=1,grow_result=1,grow_mode=0,notify_mode=0,map_slot=513,
            triggers=((1,0,4,13,0,0),),operations=None):
 triggers=[(i+1 if i+1<len(triggers) else -1,*t) for i,t in enumerate(triggers)]
 operations=[op(),op(frame=15)] if operations is None else operations
 values=[*persistence,*instances,executing,destroyed,owner,cell,fallback,capacity,count,growth,owns,grow_result,grow_mode,notify_mode,map_slot,
  len(triggers),*itertools.chain.from_iterable(triggers),len(operations),*itertools.chain.from_iterable(operations)]
 return 'G '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='G');v=list(map(int,t[1:]));position=0
 def take(n=1):
  nonlocal position
  require(n>=0 and position+n<=len(v));r=v[position:position+n];position+=n;return r
 persistence=take(2);instances=take(2)
 executing,destroyed,owner,cell,fallback,capacity,count,growth,owns,grow_result,grow_mode,notify_mode,map_slot=take(13)
 require(all(-2**31<=n<2**31 for n in (*persistence,*instances,growth)))
 require(all(0<=n<=255 for n in (executing,destroyed,owns)) and all(0<=n<=2 for n in (owner,cell,fallback)))
 require(0<=capacity<=128 and 0<=count<=128 and 0<=grow_result<2**32 and grow_mode in (0,1,2) and notify_mode in (0,1) and -1<=map_slot<262144)
 count_triggers=take()[0];require(0<=count_triggers<=3);triggers=[take(7) for _ in range(count_triggers)]
 for i,(link,enabled,dead,kind,value,result,mode) in enumerate(triggers):
  require((link==-1 or i<link<count_triggers) and all(0<=n<=255 for n in (enabled,dead,result)) and kind in (4,13,33,47) and -2**31<=value<2**31 and 0<=mode<=8)
 count_ops=take()[0];require(1<=count_ops<=32);operations=[take(9) for _ in range(count_ops)]
 for kind,frame,suppress,pulse,present,location,force,source,subject in operations:
  require(kind in (0,1,2,3) and -2**31<=frame<2**31 and -2**31<=pulse<2**31 and 0<=suppress<=255 and present in (0,1) and source in (0,1) and 0<=location<2**32 and 0<=force<2**32)
  if kind==1:require(0<=subject<count_triggers)
  if kind==2:require(0<=subject<=2)
  if kind==3:require(subject in (0,1))
 require(position==len(v))
 return dict(persistence=persistence,instances=instances,executing=executing,destroyed=destroyed,owner=owner,cell=cell,fallback=fallback,
  capacity=capacity,count=count,growth=growth,owns=owns,grow_result=grow_result,grow_mode=grow_mode,notify_mode=notify_mode,map_slot=map_slot,
  triggers=triggers,operations=operations)
def scenarios():
 for persistence,instances,present in itertools.product((-2**31,-1,0,1,2,3,255,256,258,2**31-1),(-2**31,-1,0,1,2,2**31-1),(0,1)):
  yield 'persistence_exact_equality_raw_upper_argument_and_wrapped_reference_counts',command(persistence=(persistence,2),instances=(instances,-2**31),operations=[op(present=present),op(pulse=33)])
 for executing,destroyed,n in itertools.product((0,1,128,255),(0,255),(0,1,3)):
  yield 'entry_executing_gate_and_unchanged_Tag_destroyed_byte',command(executing=executing,destroyed=destroyed,triggers=((1,0,4,13,0,0),)*n)
 for persistence,mode in itertools.product((0,1,2),range(9)):
  yield 'late_Tag_policy_trigger_link_reference_flags_and_by_value_Cell',command(persistence=(persistence,2),instances=(1,7),triggers=((1,0,4,13,0,mode),(255,0,4,-9,128,0),(1,0,4,13,255,0)))
 for enabled,destroyed,pulse,suppress,force in itertools.product((0,1,255),(0,1,255),(4,33),(0,255),(0,1,256)):
  yield 'actual_RegisterEvent_raw_gates_force_and_suppression',command(triggers=((enabled,destroyed,33,13,0,0),),operations=[op(pulse=pulse,suppress=suppress,force=force)])
 for kind,value,persistence in itertools.product((13,47),(-2**31,-1,0,2,2**31-1),(0,2)):
  yield 'timer_reset_scratch_and_scenario_condition_under_Tag',command(persistence=(persistence,2),triggers=((1,0,kind,value,0,0),)*3,
    operations=[op(frame=0),op(frame=30),op(frame=31,force=1)])
 for capacity,count,owns,growth,result in itertools.product((0,1,2),(0,1,3),(0,1,255),(-1,0,2),(0,1,128,256)):
  yield 'shared_vector_growth_policy_low_byte_and_failed_allocation',command(capacity=capacity,count=count,owns=owns,growth=growth,grow_result=result,
    triggers=((1,0,4,13,0,0),)*3,operations=[op()])
 for grow_mode,notify_mode in itertools.product((0,1,2),(0,1)):
  yield 'late_count_and_backing_after_growth_and_expiration',command(capacity=1,count=1,grow_mode=grow_mode,notify_mode=notify_mode,triggers=((1,0,4,13,0,0),)*3,operations=[op()])
 for owner,cell,fallback,location,map_slot in itertools.product((0,1,2),(0,1,2),(0,1,2),(0x7fff7fff,0x10001,0xffffffff,0x0001fe00),(0,513,-1)):
  yield 'owner_identity_empty_sentinel_combined_word_index_shared_fallback',command(owner=owner,cell=cell,fallback=fallback,map_slot=map_slot,operations=[op(location=location)])
 for old,new,instances in itertools.product((0,1,2),(0,1,2),(-2**31,-1,0,1,2**31-1)):
  yield 'complete_Object_same_tag_replace_null_and_wrapped_counters',command(owner=old,instances=(instances,instances),operations=[op(kind=2,subject=new),op(kind=2,subject=0)])
 for cell,instances in itertools.product((0,1,2),(-2**31,0,2**31-1)):
  yield 'actual_null_Cell_clear_retains_unrelated_Tag_identity',command(cell=cell,fallback=cell,instances=(instances,instances),operations=[op(kind=3,subject=0),op(kind=3,subject=1)])
 for result in (0,256):
  yield 'wrapped_requested_vector_capacity_and_low_byte_failure',command(capacity=1,count=1,growth=2**31-1,grow_result=result,operations=[op()])
 yield 'repeated_destroy_retains_duplicate_queue_entries',command(operations=[op(kind=1)]*3)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_tag.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},
  environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),
  native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['labels'])==len(e['expected']))
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
 for cmd,row in zip(e['commands'],e['expected']):
  f=parse(cmd);require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('state')==1 and row.count('R')==len(f['operations']))
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
  from original_mission_tag import MissionTagOracle
  oracle=MissionTagOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=oracle.run(parse(cmd))
   except BaseException:print('Failed Tag scenario',label,cmd,flush=True);raise
   commands.append(cmd);labels.append(label);expected.append(row)
  generation=time.monotonic()-now
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x6b3df0,0x6ed990,0x5d4430,0x47a460,0x548070,0x6ed740,0x6ed830,0x6e6050)))
  require(all(oracle.counts.get(k,0)>0 for k in ('supplied_action','supplied_growth','supplied_expiration')))
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
 write_report(a.exe,report,result);print(len(commands),'Tag sequences PASS;',meta['audited_original_calls'],'complete roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
