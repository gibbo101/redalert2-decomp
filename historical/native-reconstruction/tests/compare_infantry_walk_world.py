#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Infantry orders/Walk Process on shared production map owners."""
import argparse,itertools,json,re,struct,subprocess,time
from pathlib import Path
import pefile
import compare_walk_route as walking
import compare_infantry_membership as membership
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_infantry_walk_world import verify
NATIVE=(*walking.NATIVE,*membership.NATIVE,'tests/infantry_walk_world_vectors.cpp','src/assets/PreparedTerrainMap.cpp')
ORIGINAL=tuple(sorted(set((*walking.ORIGINAL,*membership.ORIGINAL,'tests/original_infantry_walk_world.py',
 'tests/compare_infantry_walk_world.py','tools/verify_infantry_walk_world.py'))))
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
# Native includes this composition header directly; its recursively borrowed
# kernels are guarded alongside the earlier standalone diagnostic consumers.
NATIVE=(*NATIVE,'src/assets/PreparedInfantryWalk.hpp')
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_infantry_walk_world.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(actual_complete_Infantry_orders_and_queued_Walk_Process=True,actual_shared_production_map_floor_Mark_membership_occupation_admission_speed=True,
 supplied_route_target_coordinates_visibility_notification_recalculation_dirty_animation_and_initial_state=True,
 actual_Infantry_membership_occupation_bypass=True,original_pathfinding_recovered=False,E1_startup_verified=False,runtime_enabled=False,full_frame_fidelity=False)
def require(v):
 if not v:raise ValueError('Infantry Walk world evidence/input differs')
def command(direction=2,speed=32,length=1,calls=40,level=0,flags=0,x=128,y=128,mutation=0,stop=-1):
 return 'J '+' '.join(map(str,(direction,speed,length,calls,level,flags,x,y,mutation,stop)))
def parse(c):
 t=c.split();require(len(t)==11 and t[0]=='J');v=list(map(int,t[1:]))
 require(0<=v[0]<8 and 1<=v[1]<=64 and v[2] in (1,2) and 1<=v[3]<=96 and -128<=v[4]<=127 and v[5] in (0,768))
 require(all(1<=v[i]<=255 for i in (6,7)) and 0<=v[8]<=3 and -1<=v[9]<v[3]);return v
def scenarios():
 for d,s in itertools.product(range(8),(16,32,64)):yield 'complete_original_order_map_membership_Walk_interpolation_and_arrival',command(direction=d,speed=s)
 for d in range(8):yield 'two_Cell_head_claim_queue_and_membership_transfers',command(direction=d,length=2,calls=64)
 for d,l,f in itertools.product(range(8),(-1,4),(0,768)):yield 'actual_signed_floor_and_bridge_flag_owners',command(direction=d,level=l,flags=f)
 for d,(x,y) in itertools.product((0,2,4,6),((64,64),(64,192),(192,64),(192,192))):yield 'subcell_occupation_and_House_owners_across_crossings',command(direction=d,x=x,y=y)
 for d,m in itertools.product((2,3),(1,2,3)):yield 'late_arrival_flags_before_final_Mark',command(direction=d,mutation=m,calls=24)
 for d in (0,2,3,4,6,7):yield 'actual_Stop_retains_committed_head_before_arrival',command(direction=d,stop=5)
def identities(a):
 p=pefile.PE(data=a.exe.read_bytes());planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 # The existing map preparation owns these exact plane inputs; no new runtime
 # executable read or default table is introduced by the composition.
 raw=a.map_data.read_bytes();require(len(raw)==940 and list(struct.unpack('<100Q',raw[140:]))==planes)
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},planes=planes,
  data={k:hash_file(getattr(a,k)) for k in ('render_data','raster_data','direction_data','subcell_data','map_data')}),
  native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['commands'])==len(e['expected']))
 require(e['evidence']['audited_original_calls']==3+sum(parse(c)[3]+3+int(parse(c)[9]>=0) for c in e['commands']))
 for c,row in zip(e['commands'],e['expected']):require(isinstance(row,list) and all(isinstance(x,str) for x in row) and row.count('P')==parse(c)[3] and row.count('Z')==row.count('rng')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','raster-data','direction-data','subcell-data','map-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_infantry_walk_world import InfantryWalkWorldOracle
  o=InfantryWalkWorldOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run(parse(cmd),current['original']['planes'])
   except BaseException:print('Failed original Infantry Walk world',label,cmd,flush=True);raise
   commands.append(cmd);labels.append(label);expected.append(row)
  generation=time.monotonic()-now
  require(all(o.counts[hex(root)]>0 for root in (0x501ce0,0x71dff0,0x71e220,0x503190,0x508980,0x71f590,0x508410,0x5084a0,0x4c2e60,0x54ab70,0x54af70,0x473b30,0x473d20,0x50a000,0x548000,0x548070,0x55a280,0x4706c0)))
  require(o.audit_calls==3+sum(parse(c)[3]+3+int(parse(c)[9]>=0) for c in commands))
  meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,actual_entries=dict(o.counts))
  require(current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,
   original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=origin));fingerprint=hash_file(source)
  write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();args=[str(a.native),*[str(getattr(a,k)) for k in ('render_data','raster_data','direction_data','subcell_data','map_data')]]
 proc=subprocess.run(args,input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True)
 report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr);require(proc.returncode==0)
 actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+15],want[max(0,j-8):j+15]))
 comparison=time.monotonic()-now;require(current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint))
 print(len(commands),'Infantry Walk world journeys PASS;',meta['audited_original_calls'],'complete original roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
