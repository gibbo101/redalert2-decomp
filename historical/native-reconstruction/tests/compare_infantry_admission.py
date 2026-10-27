#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete ordinary Infantry admission with actual shared Foot/map children."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
import copy
import compare_unit_admission as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_infantry_admission import verify
NATIVE=('tests/infantry_admission_vectors.cpp',)
ORIGINAL=('tests/original_infantry_admission.py','tools/verify_infantry_admission.py','tests/compare_infantry_admission.py',
 'tests/original_unit_admission.py','tools/verify_unit_admission.py','tests/compare_unit_admission.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_infantry_admission.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_ordinary_Infantry_admission=True,actual_Foot_registry_neighbor_map_House_children=True,
 borrowed_existing_Cell_occupation_and_owners=True,empty_or_self_selected_lists=True,
 initial_records_directions_speed_tables_associations_supplied=True,entered_permission_overlay_other_resident_hostile_weapon=False,
 complete_Process_join=False,production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Infantry admission evidence/input differs')
def command(flag32d=0,flag370=0,speedType=1,loading=1,origins=((0,0),(0,0),(0,0)),overlays=(-1,-1,-1),**kw):
 return 'I '+' '.join(map(str,(flag32d,flag370,speedType,loading,*itertools.chain.from_iterable(origins),*overlays)))+' '+parent.command(**kw)
def parse(cmd):
 t=cmd.split();require(len(t)>15 and t[0]=='I' and t[14]=='W');o=list(map(int,t[1:14]));v=parent.parse(' '.join(t[14:]))
 require(all(-2147483648<=n<=2147483647 for n in o) and all(0<=o[i]<=255 for i in (0,1)) and all(-32768<=n<=32767 for n in o[4:10]))
 return o,v
def scenarios():
 for level,delta,pflags,tflags,ramp in itertools.product((-2147483648,-1,0,1,4,2147483647),(-5,-4,-1,0,1,4,5),(0,0x100,0x300),(0,0x100,0x200,0x300),(0,1)):
  cells=copy.deepcopy(parent.CELLS);cells[0][3:6]=[0,ramp,tflags];cells[1][3:6]=[delta,ramp,pflags]
  yield 'shared_Foot_wrapped_early_level_and_elevated_lane',command(cells=cells,steps=[['U',0,0,2,level,1,1,255],['U',0,0,-1,level,1,0,128]])
 for occupation,owner in itertools.product(range(64),(-1,0,32)):
  cells=copy.deepcopy(parent.CELLS);cells[0][6:10]=[0x12340000|occupation,0x98760000|(occupation^31),owner,owner]
  yield 'low_byte_masks_full_allied_unowned_and_bit5_priority',command(cells=cells)
 for head,ehead,flag in itertools.product((-1,0),(-1,0),(0,256,768)):
  cells=copy.deepcopy(parent.CELLS);cells[0][11:13]=[head,ehead];cells[0][5]=flag;cells[1][5]=flag;cells[0][3]=cells[1][3]=0
  yield 'self_is_skipped_and_late_elevated_occupation',command(cells=cells,steps=[['U',0,0,2,0,-1,0,1],['U',0,0,2,4,-1,255,128]])
 for bits,land,flag370,speedType in itertools.product((0,0x80000000,0x3f800000,0xbf800000,0x7f800000,0xff800000,0x7f800001,0xffc12345),(0,1,11),(0,255),(0,1,8)):
  cells=copy.deepcopy(parent.CELLS);cells[0][10]=land
  speeds=[0x3f800000]*12;speeds[land]=bits
  yield 'speed_zero_unordered_negative_infinite_and_full_row_columns',command(cells=cells,speeds=speeds,flag370=flag370,speedType=speedType)
 for land,speed in ((0,107),(1,-8),(11,-99),(11,8),(1,2**31-1)):
  cells=copy.deepcopy(parent.CELLS);cells[0][10]=land
  yield 'combined_index_wrap_or_entered_bypass',command(cells=cells,speedType=speed,flag370=255 if speed==2**31-1 else 0)
 for d,reg,reverse in itertools.product((-2147483648,-1,0,2,7,8,2147483647),(-32768,-1,0,1,2,3,32767),(-1,0,1)):
  cells=copy.deepcopy(parent.CELLS);cells[0][2]=reg;cells[1][2]=cells[2][2]=reverse
  yield 'registry_bounds_raw_direction_and_both_neighbor_queries',command(cells=cells,steps=[['U',0,0,d,0,-1,1,255]])
 for a,b in itertools.product(((0,0),(1,0),(0,-1),(-32768,32767)),repeat=2):
  cells=copy.deepcopy(parent.CELLS);cells[0][2]=0;regs=copy.deepcopy(parent.REGS);regs[0][1:3]=b
  yield 'direction8_compares_two_distinct_registry_words',command(cells=cells,regs=regs,origins=(a,(0,0),(0,0)),steps=[['U',0,0,8,0,-1,1,0]])
 for owner,index,mask in itertools.product((-2147483648,-2,0,1,31,32,33,2147483647),(-1,0,33),(0xffffffff,)):
  cells=copy.deepcopy(parent.CELLS);cells[0][6]=28;cells[0][8]=owner;houses=copy.deepcopy(parent.HOUSES);houses[0]=[index,mask]
  yield 'actual_House_index_equality_and_wrapped_alliance',command(cells=cells,houses=houses)
 for slot,x,y,d in itertools.product((-1,0),(-32768,32767),(-32768,32767),(-2147483648,-1,2,7,2147483647)):
  cells=copy.deepcopy(parent.CELLS);cells[2][:2]=[x,y];h=parent.HEADER.copy();h[1:3]=[-1,-1]
  yield 'shared_fallback_mutates_across_complete_calls',command(h=h,cells=cells,steps=[['U',0,2,d,0,slot,0,197],['U',0,2,d,-1,-1,255,173]])
 for flag,loading in itertools.product((0,1,128,255),(-1,1,2147483647)):
  yield 'raw_permission_flag_bypassed_during_loading',command(flag32d=flag,loading=loading)
def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_original_calls']==sum(len(parse(cmd)[1][-1]) for cmd in e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  count=len(parse(cmd)[1][-1]);require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('z')==count and row.count('R')==count)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_infantry_admission import InfantryAdmissionOracle
  o=InfantryAdmissionOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_infantry(*parse(cmd))
   except BaseException:print('Failed Infantry admission scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.entries))
  require(o.infantry_calls==o.audit_calls and o.speed_loads>0 and set(o.root_results)=={0,2,7})
  require(current==identities(a) and runner==hash_file(a.native))
  meta.update(infantry_roots=o.infantry_calls,speed_loads=o.speed_loads,results=o.root_results)
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=origin))
  fingerprint=hash_file(source);write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
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
 write_report(a.exe,report,result);print(len(commands),'Infantry admission sequences PASS;',meta['audited_original_calls'],'audited original calls; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
