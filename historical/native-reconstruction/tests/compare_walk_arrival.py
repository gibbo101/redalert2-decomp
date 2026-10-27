#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual selected-head Walk arrival and late completion continuation."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
import compare_walk_movement as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_walk_arrival import verify
ORIGINAL=(*parent.ORIGINAL,'tests/original_walk_arrival.py','tools/verify_walk_arrival.py','tests/compare_walk_arrival.py')
def source_closure():
 pending=[*parent.NATIVE,'tests/walk_arrival_vectors.cpp','src/sim/FootCoordinates.cpp'];seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_walk_arrival.py','CMakeLists.txt')
FLAGS=dict(complete_selected_head_Walk_Process=True,actual_empty_head_helper_Stop_Foot_coordinates=True,
 queue_shift_and_late_guards=True,occupation_notification_destination_reset_and_initial_records_supplied=True,
 nonempty_subcell_preparation=False,production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Walk arrival evidence/input differs')
def command(*,route=None,destination=(128,128,0),cell=(-7,9),onMap=1,flag76=0,flag7a=0,levelHeight=104,servicePolicy=0,**kw):
 initial=dict(head=(128,128,29));initial.update(kw)
 base=parent.command(**initial).split()[1:]
 if route is None:route=[-1,*range(101,124)]
 return 'A '+' '.join(map(str,(*base,*route,*destination,*cell,onMap,flag76,flag7a,levelHeight,servicePolicy)))
def parse(cmd):
 t=cmd.split();require(len(t)==60 and t[0]=='A');v=list(map(int,t[1:]));require(all(-2147483648<=n<=2147483647 for n in v))
 require(v[3:6]!=[0,0,0] and all(0<=v[i]<=255 for i in (8,9,10,11,12,54,55,56)))
 require(all(-128<=v[i]<=127 for i in (15,16)) and 0<=v[19]<=7 and all(0<=v[i]<=65535 for i in (20,21)))
 require(all(-32768<=v[i]<=32767 for i in (52,53)) and 0<=v[58]<=511)
 require(all(abs(v[i]-v[i+3])<=1<<20 for i in (0,1)))
 return v
def scenarios():
 for q0,q1 in itertools.product((-2147483648,-1,0,7),repeat=2):
  yield 'route_shift_clear_tail_and_duplicate_q1',command(route=[q0,q1,*range(102,124)])
 for on,a,b,policy in itertools.product((0,1,128,255),(0,1),(0,255),(0,1,2,4,8)):
  yield 'late_notification_bytes_and_early_returns',command(onMap=on,flag76=a,flag7a=b,servicePolicy=policy)
 for marked,bridge,policy in itertools.product((0,1,128,255),(0,1,128,255),range(8)):
  yield 'nested_Mark_height_and_claim_live_position',command(marked=marked,bridge=bridge,policy=policy,servicePolicy=128|256,floor=-77)
 for point,head in (((-255,-1,-17),(-240,0,29)),((255,256,99),(256,256,29)),((0,0,0),(0,0,1)),((128,128,29),(144,128,0)),((128,128,29),(145,128,0))):
  for dest in ((0,0,0),(128,128,0),(-128,-128,0),(256,256,0),(1024,1024,0)):
   yield 'signed_cells_sentinel_and_distance16_17',command(position=point,head=head,destination=dest)
 for height,delta in itertools.product((-2147483648,-104,-1,0,1,104,0x40000000,2147483647),(-2147483648,-209,-208,-207,-1,0,1,207,208,209,2147483647)):
  yield 'strict_height_wrapped_abs_and_doubled_threshold',command(destination=(128,128,delta),levelHeight=height)
 for policy in (0,16,32,64,128,256,16|32,64|128|256,511):
  for dest in ((0,0,0),(128,128,208),(384,128,0)):
   yield 'late_occupation_notification_mutations',command(servicePolicy=policy,destination=dest)
 for moving in range(0,256,17):yield 'raw_moving_result_and_unconditional_Stop_reset',command(moving=moving)
def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},
  data={k:hash_file(getattr(a,k)) for k in ('render_data','raster_data','direction_data')}),
  native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_complete_roots']==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('R')==1)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','raster-data','direction-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_walk_arrival import WalkArrivalOracle
  o=WalkArrivalOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_arrival(parse(cmd))
   except BaseException:print('Failed Walk arrival scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_complete_roots=o.audit_calls,counts=dict(o.counts))
  require(all(o.counts.get(k,0)>0 for k in ('0x71dff0','0x71e220','0x71f590','0x71e110','0x4ca6f0','0x71df70','notification','completion','reset','release','occupy')))
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data),str(a.raster_data),str(a.direction_data)],
  input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True)
 require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(len(commands),'complete selected-head Walk arrival roots PASS')
if __name__=='__main__':main()
