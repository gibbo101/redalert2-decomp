#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete queued Walk Process with actual Infantry admission and speed."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
import compare_infantry_subcell as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_walk_command_process import verify
import compare_walk_arrival as movement
NATIVE=tuple(p for p in set((*parent.NATIVE,*movement.parent.NATIVE,'src/sim/WalkHead.cpp','src/sim/UnitDiscovery.cpp','src/sim/FootCoordinates.cpp')) if not p.startswith('tests/'))+('tests/walk_queued_vectors.cpp','src/sim/InfantrySpeed.cpp','src/sim/WalkCommands.cpp')
import compare_walk_admission as admission
import compare_infantry_speed as speed
ORIGINAL=tuple(sorted(set((*admission.ORIGINAL,*speed.ORIGINAL,'tests/original_walk_speed.py','tools/verify_walk_speed.py',
 'tests/compare_walk_speed.py','tests/original_walk_commands.py','tools/verify_walk_commands.py',
 'tests/original_walk_command_process.py','tools/verify_walk_command_process.py','tests/compare_walk_command_process.py'))))
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_walk_command_process.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Walk_interface_commands_then_queued_Process=True,actual_Infantry_admission_and_speed=True,
 same_actor_Walk_Cell_ownership=True,selected_ordered_stores_and_full_rng=True,
 supplied_route_map_floor_Mark_notification_destination_and_Process_reset=True,
 Infantry_Foot_destination_join=False,nonzero_admission_continuation=False,production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Walk command/Process evidence/input differs')
def command(stopAt=-1,**kw):
 import compare_walk_speed as base
 return 'W'+base.command(**kw)[1:]+' '+str(stopAt)
def parse(cmd):
 import compare_walk_speed as base
 t=cmd.split();require(len(t)==56 and t[0]=='W');v,o,s=base.parse('V '+' '.join(t[1:55]));stop=int(t[55]);require(-1<=stop<v[7]);return v,o,s,stop
def command_count(cmd):return 1+(parse(cmd)[3]>=0)
def scenarios():
 for direction,position,speed,stop in itertools.product(range(8),((128,128,0),(-255,-1,17)),(16,32,64),(-1,0,1,2,5)):
  yield 'Walk_MoveTo_then_ordinary_Process_or_committed_step_Stop',command(direction=direction,position=position,speed=speed,stopAt=stop,calls=40)
 for direction in range(8):
  yield 'actual_bridge_command_then_elevated_Process',command(direction=direction,bridge=1,cells=((0x12340000,0x56780000,0x300,3,3),(0x98760000,0xabcd0000,0x300,3,3)),calls=40,stopAt=2)
 for country,multiplier,veterancy,veteran,elite in ((.75,1.5,0.,0,0),(1.25,.5,1.5,1,0),(1.,1.,2.,0,128)):
  yield 'commands_share_actual_speed_and_promotion',command(country=country,multiplier=multiplier,veterancy=veterancy,veteran=veteran,elite=elite,calls=40)

def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},
  data={k:hash_file(getattr(a,k)) for k in ('render_data','raster_data','direction_data','subcell_data')}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_original_calls']==3+sum(parse(cmd)[0][7]+command_count(cmd) for cmd in e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  count=parse(cmd)[0][7];require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('rng')==1 and row.count('R')==count+command_count(cmd))
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
  from original_walk_command_process import WalkCommandProcessOracle
  o=WalkCommandProcessOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_command_process(*parse(cmd))
   except BaseException:print('Failed queued Walk scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.counts))
  require(all(o.counts.get(hex(k),0)>0 for k in (0x71dff0,0x71e220,0x5d47d0,0x5d51e0,0x71f590,0x4764b0,0x508410,0x5084a0,0x483390,0x4916d0,0x6388a0,0x6c7420,0x594770,0x476cc0,0x503190,0x4c8730,0x47a130,0x476ac0,0x4e5500,0x491620,0x508980,0x4c9b10,0x4f5a20,0x6d7910,0x7133a0,0x713420)))
  require(o.counts['0x71dff0']==sum(parse(cmd)[0][7] for cmd in commands) and o.counts['command_0x71e020']==len(commands) and o.counts['command_0x71e110']==sum(parse(cmd)[3]>=0 for cmd in commands) and current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=origin))
  fingerprint=hash_file(source);write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data),str(a.raster_data),str(a.direction_data),str(a.subcell_data),'--commands'],input='\n'.join(commands)+'\n',capture_output=True,text=True)
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
 write_report(a.exe,report,result);print(len(commands),'Walk command/Process sequences PASS;',meta['audited_original_calls'],'audited original calls; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
