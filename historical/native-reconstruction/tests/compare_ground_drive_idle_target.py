#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inactive-track Process target interior, actual null destination, supplied mission414."""
import argparse,copy,itertools,json,random,re,subprocess,time
from pathlib import Path
import compare_unit_destination as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_ground_drive_idle_target import verify
NATIVE=('tests/ground_drive_idle_target_vectors.cpp','src/sim/UnitDiscovery.cpp','src/assets/MapFloorHeight.cpp','src/assets/MapCoordinateCell.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*source_closure(),'tests/ground_drive_idle_target/CMakeLists.txt',
 'tests/original_ground_drive_idle_target.py','tests/compare_ground_drive_idle_target.py','tests/test_ground_drive_idle_target_evidence.py',
 'tools/verify_ground_drive_idle_target.py'))))
FLAGS=dict(actual_Process_idle_interior=True,complete_Process_root=False,actual_target_kind_and_actor_Cell_words=True,
 direct_target_words_with_conditional_Y=True,raw_mission5_and_exact_XYZ=True,actual_null_Unit_Foot_Drive_destination=True,
 mission414_effect_supplied=True,heap_disposal_and_atomic_services_supplied=True,
 entry_context_and_initial_records_supplied=True,Advance_joined=False,
 owned_world_join=False,preview_join=False,SDL_join=False,runtime_enabled=False)
require=parent.require
bits=parent.bits
def command(track=-1,driving=0,effect=0,kinds=(11,11),**kw):
 values=dict(initial_target=1,count=0,position=[896,1152,900],destination=[8,9,-1000],head=[13,14,15],actions=[[1,0,1,100,-91]])
 values.update(kw)
 return 'I '+' '.join(map(str,(track,driving,effect,*kinds)))+' '+parent.command(**values)
def parse(cmd):
 t=cmd.split();require(len(t)>6 and t[0]=='I');track,driving,effect,k1,k2=map(int,t[1:6])
 require(-2147483648<=track<=2147483647 and driving in (0,1) and (track==-1 or driving==0))
 require(0<=effect<=255 and k1 in (1,11) and k2 in (1,11))
 c=parent.parse(' '.join(t[6:]));c.update(track=track,driving=driving,effect=effect,kinds=[k1,k2])
 require(all(a[:3]==[1,0,1] for a in c['actions']))
 return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006')
 require(e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):
  c=parse(cmd);require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('state')==row.count('retained')==1)
  require(row.count('flow')==len(c['actions']) and row.count('return-false')+row.count('continue')==len(c['actions']))
def compare(a,commands,expected,report):return parent.compare(a,commands,expected,report)
def generate(a):
 from original_ground_drive_idle_target import GroundDriveIdleTargetOracle
 o=GroundDriveIdleTargetOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x4a0770)
 def add(label,**kw):
  cmd=command(**kw);expected.append(o.run(parse(cmd)));commands.append(cmd);labels.append(label);groups[label]=groups.get(label,0)+1
 for target,kind,count,driving,track in itertools.product((0,1,2),(1,11),(0,-1,3),(0,1),(-1,2)):
  if driving and track!=-1:continue
  pos=[896,1152,900] if target!=2 else [1408,1664,-900]
  add('actual_kind_inactive_track_direct_target_and_count',initial_target=target,kinds=(kind,kind),count=count,driving=driving,track=track,position=pos)
 for x,y in itertools.product((-32768,-2,-1,0,1,32767),(-32768,-1,0,1,32767)):
  for rx,ry in ((0,0),(65536,-65536)):
   add('signed_division_word_wrap_direct_negative_Cell_not_center',cells=[[x,y,-128,20,0,1],[5,6,127,1,0,1]],
    position=[(x+rx)*256+(-255 if x+rx<0 else 255),(y+ry)*256+(-255 if y+ry<0 else 255),2147483647],count=-7)
 for xyz in ((-2147483648,2147483647,-2147483648),(-257,-255,0),(-256,-1,7),(2147483647,-2147483648,2147483647)):
  def word(n):return ((abs(n)//256*(-1 if n<0 else 1)+32768)%65536)-32768
  x,y=map(word,xyz[:2]);add('extreme_signed_location_division_then_word_truncation',position=xyz,cells=[[x,y,127,20,0,1],[5,6,0,0,0,1]],count=1)
 for dx,dy in ((1,0),(0,1),(1,1)):
  add('conditional_target_Y_word_read',position=[896+256*dx,1152+256*dy,900],count=1)
 for mission,queued,driving,count,target,kind in itertools.product((-1,2,5),(2,5),(0,1),(0,-1,3),(0,1),(1,11)):
  add('raw_mission5_not_getter_exact_destination_fallback',mission=mission,queued=queued,driving=driving,count=count,
   initial_target=target,kinds=(kind,kind),position=[128,128,9],destination=[128,128,9])
 for position,destination in itertools.product(([0,0,0],[0,0,1],[1,2,3]),([0,0,0],[0,0,1],[1,2,3],[1,2,4],[1,3,3],[2,2,3])):
  add('empty_destination_and_all_three_component_equality',mission=5,initial_target=0,position=position,destination=destination,count=1)
 for effect,count in itertools.product((0,1,2,128,255),(-2147483648,-1,1,2147483647)):
  add('ordered_clear_then_supplied414_result_ignored',effect=effect,count=count,queue=[31-i for i in range(24)])
 for forced,suspended,buffer,owned in itertools.product((0,255),(0,173),(0,1),(0,1,255)):
  add('actual_null_destination_vector_clear_retained_head_and_timer',forced=forced,suspended=suspended,buffer=buffer,owned=owned)
 for fraction,tick,padding in itertools.product((-1.,-0.,0.,.1,.30000001192092896,1.,2.),(-2147483648,2147483647),(-2147483648,-31,2147483647)):
  add('actual_null_stop_cap_signed_timer_and_padding',percentage_bits=bits(fraction),actions=[[1,0,1,tick,padding]])
 for ramp in range(21):
  add('no_target_center_height_or_floor_query',cells=[[3,4,-128,ramp,0,1],[5,6,127,20-ramp,0,1]],count=1,height=-2147483648)
 for forced,count in itertools.product((0,255),(0,-1,3)):
  add('later_interior_calls_after_actual_and_supplied_effects',mission=5,count=count,forced=forced,destination=[896,1152,900],actions=[[1,0,1,100+i,-91+i] for i in range(4)])
 for _ in range(80):
  target=rng.randrange(3);mission=rng.choice((-1,2,5));pos=[rng.randint(-2147483648,2147483647) for _ in range(3)]
  add('retained_random_targets_queue_tails_timers_and_reference_state',initial_target=target,mission=mission,queued=rng.choice((2,5)),
   count=rng.choice((0,-1,1)),forced=rng.choice((0,255)),buffer=rng.randrange(2),owned=rng.choice((0,1,255)),
   position=pos,destination=pos if rng.randrange(2) else [0,0,0],effect=rng.randrange(256),
   global_references=rng.choice((0,0xffffffff)),references=rng.choice((1,3,0x7ffffffe)),
   queue=[rng.randint(-2147483648,2147483647) for _ in range(24)],actions=[[1,0,1,rng.randint(-2147483648,2147483647),rng.randint(-2147483648,2147483647)] for _ in range(rng.randint(2,8))])
 add('long_same_null_target_fast_return_retains_nonempty_destination',initial_target=0,mission=5,destination=[896,1152,900],actions=[[1,0,1,i,-i] for i in range(64)])
 require(all(o.counts[k]>0 for k in ('0x4a0770','0x41b320','0x4cd9b0','cell_match','raw5_xyz_match',
  'actual.destination410','supplied.mission414','target_word.0','target_word.1','continue','return_false','0x7053f0','0x4c8030','0x49fef0','0x4cde30')))
 require(o.counts['target_word.0']>o.counts['target_word.1'])
 require(all(o.counts[hex(a)]==0 for a in (0x410290,0x4706c0,0x548000,0x4a1000,0x4a05f0)))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_blocks=o.audit_blocks,
  original_arena_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),
  full_arena_and_caller_checks=o.audit_blocks,selected_native_machine_write_order_claim=False)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/ground-drive-idle-target-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'idle Process target sequences PASS')
if __name__=='__main__':main()
