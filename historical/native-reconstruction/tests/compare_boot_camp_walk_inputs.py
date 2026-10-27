#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Small exact-original Walk proof at Day1 E1 speed/subcell/height inputs.

Uses the unchanged world oracle and runner. The fixture is a translated flat
map, not original Boot Camp startup, pathfinding, scheduling or drawing.
"""
import argparse,json,subprocess,time
from pathlib import Path
import compare_infantry_walk_world as world
from compare_original import write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
SOURCES=(*world.SOURCES,'tests/compare_boot_camp_walk_inputs.py','tests/test_boot_camp_walk_inputs.py')
FLAGS=dict(actual_complete_Infantry_Walk_at_E1_speed10_subcell192_level2=True,
 supplied_translated_flat_map_route_initialization_and_services=True,
 original_Boot_Camp_startup_pathfinding_scheduler_drawing_verified=False)
def scenarios():
 for direction in range(8):
  yield 'E1_speed10_two_Cell_journey',world.command(direction=direction,speed=10,length=2,calls=96,level=2,x=192,y=192)
 for direction in (2,3):
  yield 'E1_speed10_Stop_with_committed_head',world.command(direction=direction,speed=10,length=2,calls=96,level=2,x=192,y=192,stop=16)
def identities(a):
 result=world.identities(a)
 result['original']['E1_driver_sources']={p:hash_file(ROOT/p) for p in ('tests/compare_boot_camp_walk_inputs.py','tests/test_boot_camp_walk_inputs.py')}
 return result
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 world.require(e['executable_sha256']==world.PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 world.require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():world.require(e['evidence'].get(k) is v)
 world.require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 world.require(e['evidence']['audited_original_calls']==3+sum(world.parse(c)[3]+3+int(world.parse(c)[9]>=0) for c in e['commands']))
 for c,row in zip(e['commands'],e['expected']):
  world.require(isinstance(row,list) and all(isinstance(x,str) for x in row) and row.count('P')==world.parse(c)[3] and row.count('Z')==row.count('rng')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','raster-data','direction-data','subcell-data','map-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  world.require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  world.require(a.output is not None and a.report is None);folder=private_path(a.output,a.exe);world.require(not folder.exists())
  from original_infantry_walk_world import InfantryWalkWorldOracle
  oracle=InfantryWalkWorldOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,command in scenarios():
   row=oracle.run(world.parse(command),current['original']['planes']);commands.append(command);labels.append(label);expected.append(row)
  generation=time.monotonic()-now
  world.require(oracle.audit_calls==3+sum(world.parse(c)[3]+3+int(world.parse(c)[9]>=0) for c in commands))
  meta=dict(FLAGS,cases=len(commands),audited_original_calls=oracle.audit_calls,actual_entries=dict(oracle.counts))
  world.require(current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,
   original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=world.PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=origin));fingerprint=hash_file(source)
  write_report(a.exe,folder/'report.json',dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic()
 proc=subprocess.run([str(a.native),*[str(getattr(a,k)) for k in ('render_data','raster_data','direction_data','subcell_data','map_data')]],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 world.require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];world.require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+15],want[max(0,j-8):j+15]))
 comparison=time.monotonic()-now;world.require(current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint))
 print(len(commands),'E1-input Walk sequences PASS;',meta['audited_original_calls'],'complete original roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
