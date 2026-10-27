#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Walk commands with actual Infantry guards/reset/projection."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
import copy
import struct,math
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_walk_commands import verify
NATIVE=('src/sim/WalkCommands.cpp','tests/walk_command_vectors.cpp')
ORIGINAL=('tests/original_walk_commands.py','tools/verify_walk_commands.py','tests/compare_walk_commands.py',
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
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_walk_commands.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Walk_MoveTo_Stop_immediate_head=True,actual_Infantry_guards_and_reset=True,
 actual_projection_signed64_conversion=True,selected_ordered_stores_and_late_live_fields=True,
 map_animation_initial_records_and_scale_supplied=True,Infantry_Foot_destination_join=False,complete_Process_join=False,production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Walk command evidence/input differs')
def dbits(n):return struct.unpack('<Q',struct.pack('<d',n))[0]
def fbits(n):return struct.unpack('<I',struct.pack('<f',n))[0]
def command(destination=(17,23,31),head=(0,0,0),moving=173,processing=197,really=255,frozen=0,disabled=0,disabled2=0,resetFlag=0,flags=0,scale=1.,empty=(0,0,0),mutation=0,ops=((0,(128,256,17)),)):
 v=(*destination,*head,moving,processing,really,frozen,disabled,disabled2,resetFlag,flags,dbits(scale),*empty,mutation)
 return 'C '+' '.join(map(str,((n&0xffffffff if i!=14 else n) for i,n in enumerate(v))))+' '+str(len(ops))+' '+' '.join(str(n&0xffffffff) for op,p in ops for n in (op,*p))
def parse(cmd):
 t=cmd.split();require(len(t)>=25 and t[0]=='C');v=list(map(int,t[1:20]));count=int(t[20]);tail=list(map(int,t[21:]))
 require(all(0<=n<=0xffffffffffffffff for n in v) and all(n<=0xffffffff for i,n in enumerate(v) if i!=14))
 require(all(v[i]<=255 for i in (6,7,8,10,11,12)) and v[18]<=31 and 1<=count<=16 and len(tail)==4*count)
 ops=[]
 for i in range(count):
  op,*point=tail[4*i:4*i+4];require(0<=op<=2 and all(0<=n<=0xffffffff for n in point));ops.append((op,point))
 return v,ops
def scenarios():
 zero=(0,0,0)
 for frozen,disabled,disabled2,request in itertools.product((-2147483648,-1,0,1,2147483647),(0,1,128,255),(0,1,255),(zero,(128,256,17))):
  yield 'actual_Infantry_guard_short_circuits',command(frozen=frozen,disabled=disabled,disabled2=disabled2,ops=((0,request),))
 for head,destination,moving,resetFlag in itertools.product((zero,(0,0,1),(1,0,0),(0,1,0)),(zero,(17,23,31)),(0,1,173,255),(0,128)):
  yield 'empty_head_full_coordinate_comparison_and_retained_raw_bytes',command(head=head,destination=destination,moving=moving,resetFlag=resetFlag,ops=((0,zero),(1,zero),(2,zero),(1,zero),(1,zero)))
 for flags,scale,z in itertools.product((0,1,256,0x80000100),(0.,.5,1.,1.25,-1.,2147483648.,4294967296.,2.**63,float('inf'),float('nan')),(-2147483648,0,2147483647)):
  yield 'bridge_projection_signed64_conversion_and_wrapped_Z',command(flags=flags,scale=scale,ops=((0,(1,2,z)),(0,(3,4,z))))
 for mask,flags in itertools.product(range(32),(0,256)):
  yield 'live_map_scale_destination_and_reset_effect_mutations',command(flags=flags,mutation=mask,resetFlag=255,ops=((0,(1,2,3)),(1,zero),(2,zero),(1,zero)))
 for empty in ((7,9,11),(-2147483648,2147483647,-1)):
  yield 'supplied_nonzero_empty_sentinel',command(empty=empty,head=empty,destination=empty,resetFlag=255,ops=((0,empty),(2,empty),(1,empty)))

def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_original_calls']==sum(len(parse(cmd)[1]) for cmd in e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  count=len(parse(cmd)[1]);require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('R')==count)
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
  from original_walk_commands import WalkCommandsOracle
  o=WalkCommandsOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_commands(*parse(cmd))
   except BaseException:print('Failed Walk command scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.counts))
  require(all(o.counts.get('command_'+hex(k),0)>0 for k in (0x71e020,0x71e110,0x71e1a0,0x6d8e80,0x6d6df0,0x6d6e00,0x508750,0x6a29b0,0x77f110)))
  require(current==identities(a) and runner==hash_file(a.native))
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
 write_report(a.exe,report,result);print(len(commands),'Walk command sequences PASS;',meta['audited_original_calls'],'audited original calls; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
