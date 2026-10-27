#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual Infantry commands, Walk retry/refill and complete ordinary Process."""
import argparse,itertools,json,re,struct,subprocess,time
from pathlib import Path
import compare_infantry_subcell as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_walk_route import verify
import compare_walk_arrival as movement
NATIVE=tuple(p for p in set((*parent.NATIVE,*movement.parent.NATIVE,'src/sim/WalkHead.cpp','src/sim/UnitDiscovery.cpp','src/sim/FootCoordinates.cpp')) if not p.startswith('tests/'))+('tests/walk_queued_vectors.cpp','src/sim/InfantrySpeed.cpp','src/sim/WalkCommands.cpp')
import compare_walk_speed as speed
import compare_infantry_destination as destination
ORIGINAL=tuple(sorted(set((*speed.ORIGINAL,*destination.ORIGINAL,'tests/original_walk_route.py',
 'tools/verify_walk_route.py','tests/compare_walk_route.py'))))
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_walk_route.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Walk_retry_or_successful_refill_Process=True,actual_Infantry_Foot_initial_and_arrival_commands=True,
 actual_Infantry_admission_speed_head_occupation=True,same_actor_Walk_route_timers_and_distinct_House=True,
 selected_ordered_stores_all_queue_words_and_full_rng=True,supplied_route_provider_coordinates_map_floor_Mark_notification_animation_and_initial_records=True,
 failed_routes_and_JumpJet_children_supported=False,original_pathfinding_recovered=False,production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Walk route evidence/input differs')
def bits(x):return struct.unpack('<Q',struct.pack('<d',x))[0]
def command(order=1,interval=.01,start=-1,padding=-91,remaining=0,counter=19,state=0,scratch=0x12345678,length=1,response=1,tick=0,target=0,diagnostic=0,**kw):
 return 'F'+speed.command(**kw)[1:]+' '+' '.join(map(str,(order,bits(interval),start,padding,remaining,counter,state,scratch,length,response,tick,target,diagnostic)))
def parse(cmd):
 t=cmd.split();require(len(t)==68 and t[0]=='F');v,o,s=speed.parse('V '+' '.join(t[1:55]));f=list(map(int,t[55:]))
 require(f[0] in (0,1) and 0<=f[1]<2**64 and all(-2**31<=f[i]<2**31 for i in range(2,13)))
 require(1<=f[8]<=24 and 1<=f[9]<=255 and f[11] in (0,1) and 0<=f[12]<=3)
 return v,o,s,f
def scenarios():
 for direction,base in itertools.product(range(8),(16,32,64)):
  yield 'actual_Infantry_order_refill_interpolation_arrival_null_order',command(direction=direction,speed=base,calls=40)
 for direction,length in itertools.product(range(8),(1,2)):
  dx,dy=((0,-256),(256,-256),(256,0),(256,256),(0,256),(-256,256),(-256,0),(-256,-256))[direction]
  yield 'two_Cell_order_refills_consumed_queue_before_actual_arrival',command(direction=direction,destination=(128+2*dx,128+2*dy,0),length=length,calls=80)
 for state in (-2147483648,-1,0,2,3,6,17,27,2147483647):
  for start,remaining,tick in ((-1,1,0),(-1,-7,0),(0,7,2),(2147483647,7,-2147483648)):
   yield 'timer_wait_actual_Infantry_state_reset_and_raw_moving',command(order=0,start=start,remaining=remaining,state=state,tick=tick,calls=2)
 for start,remaining,tick in ((-1,0,0),(0,0,0),(0,7,7),(0,-7,0),(2147483647,0,-2147483648),(-2147483648,0,2147483647)):
  yield 'signed_wrapped_expired_timer_or_wait',command(order=0,start=start,remaining=remaining,tick=tick,calls=1)
 for interval in (0.,-.5,.001,.0011111111111111111,.0011111111111111113,.5,1.,-1.,4294967296.,1e30,float('inf'),float('-inf'),float('nan')):
  yield 'original_FTOL_signed64_low32_retry_duration',command(order=0,interval=interval,calls=1)
 for length,target,response in itertools.product((1,3,4,23,24),(0,1),(1,128,255)):
  yield 'actual_post_route_target_queue_scan_and_counter',command(order=0,length=length,target=target,response=response,counter=-31,calls=1)
 for position,direction in itertools.product(((-255,-1,17),(-257,-511,-17),(8388607,-8388608,0),(2147483647,-2147483648,7)),range(8)):
  yield 'signed_destination_division_word_and_wrapped_candidate',command(position=position,direction=direction,on=0,calls=1)
 for diagnostic in (1,2,3):
  yield 'late_clock_interval_or_destination_after_saved_route_input',command(order=0,diagnostic=diagnostic,calls=1)
 for direction in (-2147483648,-17,9,25,2147483647):
  yield 'supplied_raw_route_direction_is_masked_only_for_offset',command(order=0,direction=direction,calls=1)

def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},
  data={k:hash_file(getattr(a,k)) for k in ('render_data','raster_data','direction_data','subcell_data')}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_original_calls']==3+sum(parse(cmd)[0][7]+parse(cmd)[3][0] for cmd in e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  count=parse(cmd)[0][7];require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('rng')==1 and row.count('R')==count)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','raster-data','direction-data','subcell-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_walk_route import WalkRouteOracle
  o=WalkRouteOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_route(*parse(cmd))
   except BaseException:print('Failed queued Walk scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.counts))
  require(all(o.counts.get(hex(k),0)>0 for k in (0x71dff0,0x71e220,0x5d47d0,0x5d51e0,0x71f590,0x4764b0,0x508410,0x5084a0,0x483390,0x4916d0,0x6388a0,0x6c7420,0x594770,0x476cc0,0x503190,0x4c8730,0x47a130,0x476ac0,0x4e5500,0x491620,0x508980,0x4c9b10,0x4f5a20,0x6d7910,0x7133a0,0x713420)))
  require(o.audit_calls==3+sum(parse(c)[0][7]+parse(c)[3][0] for c in commands))
  require(o.counts['supplied_route']>0 and o.counts['actual_process_reset']>0 and o.counts['route_0x508730']>0 and current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=origin))
  fingerprint=hash_file(source);write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data),str(a.raster_data),str(a.direction_data),str(a.subcell_data),'--route'],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True)
 require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint)
 write_report(a.exe,report,result);print(len(commands),'Infantry command/Walk route sequences PASS;',meta['audited_original_calls'],'audited original calls; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
