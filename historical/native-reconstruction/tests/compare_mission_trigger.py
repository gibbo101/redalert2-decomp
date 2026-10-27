#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Trigger roots; reuse originals with current native execution."""
import argparse,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_trigger import verify
NATIVE=('src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/mission_trigger_vectors.cpp')
ORIGINAL=('tests/original_mission_trigger.py','tools/verify_mission_trigger.py','tests/compare_mission_trigger.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_trigger.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_ResetTimers_RegisterEvent_FireActions=True,actual_event4_13_33_47_persistence_and_House=True,
 selected_ordered_timer_and_event_mask_stores=True,full_original_arena_ABI_and_code_guards=True,
 supplied_action_dispatcher_initial_records_and_stack_scratch=True,random_timer51_supported=False,
 Tag_discovery_or_scheduler_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Mission trigger evidence/input differs')
def op(kind=1,frame=0,suppress=0,a=4,b=1,c=0,d=1,e=2):return (kind,frame,suppress,a&0xffffffff,b,c,d,e)
def command(enabled=1,destroyed=0,mask=0,start=-1,padding=-91,remaining=0,scratch=0x13579bdf,
            countries=(-9,13),houses=(13,-9,13,0),events=((4,13),),actions=(),operations=None):
 def linked(rows):return [(i+1 if i+1<len(rows) else -1,*r) for i,r in enumerate(rows)]
 events=[(k,v,link) for link,k,v in linked(events)];actions=linked(actions)
 operations=[op()] if operations is None else operations
 values=[enabled,destroyed,mask,start,padding,remaining,scratch,*countries,len(houses),*houses,len(events),
  *itertools.chain.from_iterable(events),len(actions),*itertools.chain.from_iterable(actions),len(operations),*itertools.chain.from_iterable(operations)]
 return 'T '+' '.join(map(str,values))
def parse(cmd):
 tokens=cmd.split();require(tokens and tokens[0]=='T');v=list(map(int,tokens[1:]));position=0
 def take(n=1):
  nonlocal position
  require(n>=0 and position+n<=len(v));r=v[position:position+n];position+=n;return r
 enabled,destroyed,mask,start,padding,remaining,scratch=take(7);countries=take(2)
 require(0<=enabled<=255 and 0<=destroyed<=255 and 0<=mask<2**32)
 require(all(-2**31<=n<2**31 for n in (start,padding,remaining,scratch,*countries)))
 count=take()[0];require(0<=count<=16);houses=take(count);require(all(-2**31<=n<2**31 for n in houses))
 count=take()[0];require(0<=count<=65);events=[take(3) for _ in range(count)]
 for i,(kind,value,link) in enumerate(events):require(kind in (4,13,33,47) and -2**31<=value<2**31 and (link==-1 or i<link<count))
 count=take()[0];require(0<=count<=16);actions=[take(3) for _ in range(count)]
 for i,(link,result,mode) in enumerate(actions):require((link==-1 or i<link<count) and 0<=result<=255 and 0<=mode<=5)
 count=take()[0];require(1<=count<=64);operations=[take(8) for _ in range(count)]
 for kind,frame,suppress,a,b,c,d,e in operations:
  require(kind in (0,1,2) and -2**31<=frame<2**31 and 0<=suppress<=255 and all(0<=n<2**32 for n in (a,b,c,d,e)))
  if kind==1:require(b<=2 and e<=2)
  if kind==2:require(a<=2)
 require(position==len(v))
 return dict(enabled=enabled,destroyed=destroyed,mask=mask,start=start,padding=padding,remaining=remaining,
  scratch=scratch,countries=countries,houses=houses,events=events,actions=actions,operations=operations)
def scenarios():
 for enabled,destroyed,persistent,force in itertools.product((0,1,128,255),(0,1,255),(0,1,256,257),(0,1,256)):
  yield 'raw_entry_flags_force_and_persistent_low_bytes',command(enabled=enabled,destroyed=destroyed,operations=[op(c=force,d=persistent)])
 for pulse,suppress,persistent in itertools.product((0,4,33),(0,1,255),(0,1,128,256)):
  yield 'all_events_continue_after_false_and_remember_true_bits',command(events=((4,13),(33,-9),(47,-1)),operations=[op(a=pulse,suppress=suppress,d=persistent),op(a=33,frame=15,d=persistent),op(a=4,frame=16,d=persistent)])
 for countries,houses in itertools.product(((-9,13),(13,0),(77,-9)),((),(13,-9,13,0),(0,13,-9,13))):
  yield 'parent_and_event_late_House_lookups_first_match_and_null',command(countries=countries,houses=houses,events=((4,13),(4,-9)),operations=[op(),op(a=33)])
 edges=(-2**31,-143165577,-16,-1,0,1,15,143165576,2**31-1)
 for value,frame in itertools.product(edges,(-2**31,-1,0,2**31-1)):
  yield 'reset_shared_timer_word_stores_wrapping_and_last_timer_wins',command(mask=0xffffffff,events=((13,value),(4,13),(13,-value if value!=-2**31 else value)),operations=[op(kind=0,frame=frame)])
 for count,last in itertools.product((1,2,31,32,33,64,65),(4,13,33,47)):
  events=[(4,13)]*(count-1)+[(last,2)]
  yield 'x86_shift_index32_alias_and_timer_bit_clear',command(events=events,operations=[op(),op(a=0,frame=31),op(c=1,frame=47),op(a=33,frame=48)])
 for frame,start,remaining in itertools.product((-2**31,-1,0,15,2**31-1),(-1,0,2**31-1),(-1,0,1,15)):
  yield 'actual_timer_and_scenario_event_in_parent',command(start=start,remaining=remaining,events=((13,2),(47,-1)),operations=[op(frame=frame),op(frame=frame,c=1)])
 for events,force,persistent in itertools.product(((),((4,13),(13,2))), (0,1,255,256),(0,1,255,256)):
  yield 'force_or_empty_events_and_conditional_timer_reset',command(events=events,operations=[op(c=force,d=persistent)])
 for actions in ((),((0,0),),((1,0),),((128,0),(0,0),(255,0)),((0,1),(128,0),(0,0)),
                 ((0,2),(1,0),(255,0)),((0,3),(0,3),(1,0)),((0,4),(0,0),(255,0)),((0,5),(1,0),(0,0))):
  for enabled,destroyed in ((0,0),(1,0),(255,0),(1,255)):
   yield 'ordered_actions_low_byte_OR_late_link_House_and_saved_Cell',command(enabled=enabled,destroyed=destroyed,actions=actions,
     operations=[op(kind=2,a=2,b=0x8000ffff),op(kind=2,a=0,b=0x7fff0001),op(a=4,frame=15)])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_trigger.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},
  environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),
   unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
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
  from original_mission_trigger import MissionTriggerOracle
  oracle=MissionTriggerOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=oracle.run(parse(cmd))
   except BaseException:print('Failed Trigger scenario',label,cmd,flush=True);raise
   commands.append(cmd);labels.append(label);expected.append(row)
  generation=time.monotonic()-now
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x6ed680,0x6ed740,0x6ed830,0x6e6050,0x6e6cf0,0x6e6d50,0x4ed760)))
  require(all(oracle.stores.get(hex(a),0)>0 for a in (0x6ed6b1,0x6ed6ba,0x6ed6bf,0x6ed6d0,0x6ed7ed)))
  require(current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),selected_stores=dict(oracle.stores),
   audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
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
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint)
 write_report(a.exe,report,result);print(len(commands),'Trigger sequences PASS;',meta['audited_original_calls'],'complete roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
