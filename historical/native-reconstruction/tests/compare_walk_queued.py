#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete ordinary queued Walk Process with actual head/level children."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
import compare_infantry_subcell as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_walk_queued import verify
import compare_walk_arrival as movement
NATIVE=tuple(p for p in set((*parent.NATIVE,*movement.parent.NATIVE,'src/sim/WalkHead.cpp','src/sim/UnitDiscovery.cpp','src/sim/FootCoordinates.cpp')) if not p.startswith('tests/'))+('tests/walk_queued_vectors.cpp',)
ORIGINAL=tuple(sorted(set((*parent.ORIGINAL,*movement.ORIGINAL,'tests/original_walk_head.py','tools/verify_walk_head.py','tests/original_walk_queued.py','tools/verify_walk_queued.py','tests/compare_walk_queued.py'))))
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_walk_queued.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_ordinary_queued_Walk_Process=True,actual_head_and_Infantry_subcells=True,
 actual_level_and_double_current_Cell_lookup=True,selected_ordered_stores_and_full_rng=True,
 admission_speed_Mark_map_floor_notification_destination_reset_initial_records_supplied=True,
 route_finding_special8_nonzero_admission=False,production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Queued Walk evidence/input differs')
def command(position=(128,128,0),direction=2,calls=1,speed=32,destination=None,floor=0,height=104,level=104,threshold=104,
 bridge=0,on=1,moving=173,frozen=0,mutation=0,trigger=0,levels=(0,0),cells=None,house=3,mission=2,queued=-1,percent=1):
 offsets=((0,-256),(256,-256),(256,0),(256,256),(0,256),(-256,256),(-256,0),(-256,-256))
 if destination is None:
  x,y=offsets[direction&7];destination=(((position[0]+x+2**31)%2**32)-2**31,((position[1]+y+2**31)%2**32)-2**31,position[2])
 if cells is None:cells=((0x12340000,0x56780000,0,17,23),(0x98760000,0xabcd0000,0,-7,9))
 return 'Q '+' '.join(map(str,(*position,*destination,direction,calls,speed,floor,height,level,threshold,bridge,on,moving,frozen,mutation,trigger,*levels,*itertools.chain.from_iterable(cells),house,mission,queued,percent)))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='Q' and len(t)==36);v=list(map(int,t[1:]))
 words=(21,22,23,26,27,28)
 require(all((0<=n<=0xffffffff) if i in words else (-2147483648<=n<=2147483647) for i,n in enumerate(v)))
 require(all(0<=v[i]<=255 for i in (13,14,15)) and all(-128<=v[i]<=127 for i in (19,20)))
 require(1<=v[7]<=128 and 0<=v[8]<=256 and 0<=v[17]<=511 and 0<=v[18]<=32)
 require(v[6] not in (-1,8) or v[3:6]==[0,0,0]);return v
def scenarios():
 for d,bridge,flags,level in itertools.product(range(8),(0,1,128,255),(0,256),(-128,-1,0,4,127)):
  cells=((0x12340000,0x56780000,flags,17,23),(0x98760000,0xabcd0000,flags,-7,9))
  yield 'ordinary_directions_raw_bridge_signed_level',command(direction=d,bridge=bridge,levels=(level,-level-1),cells=cells)
 for d in (*range(-17,-1),*range(9,26),-2147483648,2147483647):
  yield 'mask_offsets_but_retain_raw_admission_direction',command(direction=d)
 for mask in range(32):
  cells=((0x12340000|mask,0x56780000|mask,0,17,23),(0x98760000|mask,0xabcd0000|mask,0,-7,9))
  yield 'selected_occupation_and_failed_head',command(cells=cells,calls=2)
 for d,speed in itertools.product(range(8),(16,32,64)):
  yield 'preparation_then_actual_interpolation_arrival_Stop_and_idle',command(direction=d,speed=speed,calls=40)
 for m,trigger in itertools.product((1,2,4,8,16,32,64,128,256,511),range(1,9)):
  yield 'late_lookup_mutations_saved_candidate_direction_and_bridge',command(mutation=m,trigger=trigger)
 for p,d in itertools.product(((-255,-1,17),(-257,-511,-17),(8388607,-8388608,0),(2147483647,-2147483648,7)),range(8)):
  yield 'wrapped_candidate_signed_division_word_cells_offmap',command(position=p,direction=d,on=0)
 for on,moving,frozen in itertools.product((0,1,128,255),(0,1,173,255),(-1,0,1)):
  yield 'late_onmap_raw_return_and_no_first_call_interpolation',command(on=on,moving=moving,frozen=frozen)
 for percent,direction in itertools.product((-1,0,1),(-1,8,2)):
  yield 'empty_destination_skips_queue_and_does_not_change_reallyMoving',command(destination=(0,0,0),percent=percent,direction=direction,calls=2)
def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},
  data={k:hash_file(getattr(a,k)) for k in ('render_data','raster_data','direction_data','subcell_data')}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_original_calls']==2+sum(parse(cmd)[7] for cmd in e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  count=parse(cmd)[7];require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('rng')==1 and row.count('R')==count)
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
  from original_walk_queued import WalkQueuedOracle
  o=WalkQueuedOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_queued(parse(cmd))
   except BaseException:print('Failed queued Walk scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.counts))
  require(all(o.counts.get(hex(k),0)>0 for k in (0x71dff0,0x71e220,0x5d47d0,0x5d51e0,0x71f590,0x4764b0,0x508410,0x5084a0,0x483390,0x4916d0,0x6388a0,0x6c7420,0x594770,0x476cc0)))
  require(o.counts['0x71dff0']==o.audit_calls-2 and current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=origin))
  fingerprint=hash_file(source);write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data),str(a.raster_data),str(a.direction_data),str(a.subcell_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
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
 write_report(a.exe,report,result);print(len(commands),'queued Walk Process sequences PASS;',meta['audited_original_calls'],'audited original calls; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
