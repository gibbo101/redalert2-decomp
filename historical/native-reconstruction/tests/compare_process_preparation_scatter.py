#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Focused complete Process proof of supplied positive-route preparation."""
import argparse,copy,json,time
from pathlib import Path
import compare_borrowed_process_scatter as parent
from original_process_preparation_scatter import ProcessPreparationScatterOracle
from verify_process_preparation_scatter import verify
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
SOURCES=tuple(sorted(set((*parent.SOURCES,
 'tests/compare_process_preparation_scatter.py','tests/original_process_preparation_scatter.py',
 'tools/verify_process_preparation_scatter.py','tests/test_process_preparation_scatter_evidence.py'))))
FLAGS=dict(actual_positive_route_preparation=True,actual_closest_resident=True,
 actual_Crushable_neighbor=True,overlay_traversal_excluded=True,
 supplied_route_finder=True,complete_Process1_verified=False,production_runtime_enabled=False)
require=parent.require
def command(c,route=None,threshold=256,counter=-31,neighbor=None):
 route=[2,3,4]+[-1]*21 if route is None else route
 prefix='' if neighbor is None else 'L '+' '.join(map(str,neighbor))+' '
 return prefix+'R '+' '.join(map(str,[threshold,counter,*route]))+' '+parent.command(**c)
def parse(cmd):
 parts=cmd.split();require(bool(parts));neighbor=None
 if parts[0]=='L':
  require(len(parts)>3);neighbor=list(map(int,parts[1:3]));require(0<=neighbor[0]<9 and 0<=neighbor[1]<=255);parts=parts[3:]
 require(parts[0]=='R' and len(parts)>27);values=list(map(int,parts[1:27]));c=parent.parse(' '.join(parts[27:]))
 require(all(-2147483648<=n<=2147483647 for n in values[:2]))
 require(values[2] in range(8) and values[-1]==-1 and all(-1<=d<=7 for d in values[2:]))
 c.update(close_enough=values[0],route_counter=values[1],supplied_route=values[2:])
 if neighbor is not None:c['neighbor_overlay']=neighbor
 return c
def scenarios():
 def base():
  c=parent.parent.defaults();c.update(process_track=-1,head=[0,0,0],cell=9,position=[12672,12928,0],
   destination=[13184,13184,0],desired=16384,start=16384,queue=[-1]*24)
  for row in c['cells']:row[7]=row[8]=-1
  c['secondary'][0]['position']=[12928,12928,0]
  return c
 yield 'successful_empty_candidate',command(base())
 for second in (False,True):
  for mission in (0,2):
   for threshold in (0,256,572,573,2147483647):
    c=base();c['cells'][8 if second else 4][7]=1;c['objects'][1][4]=mission
    c['secondary'][0]['position']=[13184,13184,0] if second else [12928,12928,0]
    yield f'{"second" if second else "first"}_resident_mission{mission}_close{threshold}',command(c,threshold=threshold)
 for mode in range(4):
  c=base();c['cells'][4][7]=1;c['objects'][1][4]=0;c['fp_mode']=mode
  yield 'preparation_FP_mode'+str(mode),command(c)
 for second in (False,True):
  for z in (-312,-208,-207,207,208,312):
   c=base();idx=8 if second else 4;c['cells'][idx][5]=0x100;c['cells'][idx][7]=c['cells'][idx][8]=1
   c['objects'][1][4]=0;c['position'][2]=z
   yield f'candidate_flags_{"second" if second else "first"}_savedZ{z}',command(c,threshold=0)
 for count in (0,3):
  for result in (0,1,255):
   c=base();c['cells'][4][7]=1;c.update(count=count,mission_return=result,initial_target=6)
   yield f'close_target_vector{count}_missionAL{result}',command(c,threshold=573)
 for count in (0,3):
  c=base();c['cells'][4][7]=1;c.update(count=count,mission_return=1,initial_target=6,head=[12345,12928,17])
  yield f'close_nonzero_head_order_vector{count}',command(c,threshold=573)
 directions=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))
 for first,(dx,dy) in enumerate(directions):
  for second,(nx,ny) in enumerate(directions):
   if second==(first+4)%8:continue # The source Cell must remain overlay-free.
   for flag in (0,1,255):
    # A zero flag retains second: differing directions enter overlay admission,
    # outside this complete Process proof. Interior zero controls cover all64.
    if not flag and second!=first:continue
    # Cross a Cell boundary during this complete Process call, reaching the
    # actual absent-overlay bypass of the downstream curve64 consumer.
    c=base();c.update(speed=255,position=[12928-dx*256,12928-dy*256,0],
     destination=[12928+nx*256,12928+ny*256,0],desired=first<<13,start=first<<13)
    yield f'neighbor_{first}_{second}_Crushable{flag}',command(c,
     route=[first,second]+[-1]*22,neighbor=((ny+1)*3+nx+1,flag))
def generate(a):
 o=ProcessPreparationScatterOracle(a.exe);commands=[];expected=[];labels=[];per=[]
 for label,cmd in scenarios():
  before=o.counts.copy()
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed focused preparation',label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);per.append(dict(o.counts-before))
 return commands,expected,labels,dict(FLAGS,actual_counts=dict(o.counts),per_case_counts=per,
  audited_complete_Process_calls=sum(o.counts['Process_return.'+str(i)] for i in (0,1)),
  distinct_original_instructions=len(o.instructions))
def identities(a):
 result=parent.identities(a);result['sources']={p:hash_file(ROOT/p) for p in SOURCES};result['preparation_inspection']=verify(a.exe.read_bytes());return result
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']==current)
 for k,v in FLAGS.items():require(e['evidence'][k] is v and r[k] is v)
 require(e['commands'] and len(e['commands'])==len(e['labels'])==len(e['expected'])==len(e['evidence']['per_case_counts']))
 require(e['evidence']['audited_complete_Process_calls']==len(e['commands']))
 for cmd,row,counts in zip(e['commands'],e['expected'],e['evidence']['per_case_counts']):
  c=parse(cmd);require(row.count('route-counter')==row.count('process-return')==1 and row.count('actor')==4)
  if 'neighbor_overlay' in c:
   require(counts.get('preparation.actual_overlay_neighbor')==1)
   require(counts.get('preparation.curve64.'+str(int(bool(c['neighbor_overlay'][1]))))==1)
   require(counts.get('Advance.overlay_absent',0)>0)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for name in ('exe','native','legacy-native'):p.add_argument('--'+name,type=Path,required=True)
 for name,file in [('direction','direction-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('geometry','ramp-geometry-data.bin')]:p.add_argument('--'+name+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/file)
 for name in ('output','expectations','report'):p.add_argument('--'+name,type=Path)
 a=p.parse_args();a.pilot=False;a.pilot_limit=None;start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=parent.compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'positive-route preparation sequences PASS')
if __name__=='__main__':main()
