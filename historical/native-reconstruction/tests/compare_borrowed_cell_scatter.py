#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Cell/Unit/nearby roots over two actual prepared actors (unwired)."""
import argparse,copy,itertools,json,re,subprocess,time
from pathlib import Path
import compare_cell_unit_scatter_world as parent
import compare_cell_nearby_scatter as nearby
import compare_borrowed_unit_admission as admission
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
NATIVE=('tests/borrowed_cell_scatter_vectors.cpp','tests/borrowed_cell_scatter_check.cpp',*parent.NATIVE[1:])
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  p=pending.pop()
  if p in seen:continue
  seen.add(p)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
   local=(ROOT/p).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*nearby.SOURCES,*admission.SOURCES,*source_closure(),
 'tests/borrowed_cell_scatter/CMakeLists.txt','tests/compare_borrowed_cell_scatter.py','tests/test_borrowed_cell_scatter_evidence.py'))))
FLAGS=dict(actual_prepared_Cell_Unit_nearby_owners=True,no_motion_or_target_refresh=True,
 two_distinct_actors_Drives_missions_queues_and_targets=True,initial_records_and_associations_supplied=True,
 named_heap_atomic_padding_services_supplied=True,Advance6_executed=False,Process_joined=False,
 production_runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported borrowed Cell Scatter evidence/input')
def parse(cmd):
 c=(nearby if cmd.startswith('N ') else parent).parse(cmd)
 require(all(row[7]<=1 and row[8]<=1 for row in c['cells']))
 require(all(o[1]<=1 and not o[3] and o[14]<=1 for o in c['objects'][:2]))
 require(all(o==parent.defaults()['objects'][i] for i,o in enumerate(c['objects']) if i>=2))
 require(all(row in (0,1) for row in c.get('type_indexes',[0,1])[:2]))
 return c
def identities(a):
 result=nearby.identities(a);result['sources']={p:hash_file(ROOT/p) for p in SOURCES};return result
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and all(isinstance(n,str) for n in row) and row.count('state')==1 and row.count('actor')==4)
def generate(a):
 from original_cell_unit_scatter_world import CellUnitScatterWorldOracle
 from original_cell_nearby_scatter import CellNearbyScatterOracle
 oracles={False:CellUnitScatterWorldOracle(a.exe),True:CellNearbyScatterOracle(a.exe)}
 commands=[];expected=[];labels=[];groups={}
 def add(label,search=False,**kw):
  driver=nearby if search else parent;cmd=driver.command(**kw)
  try:row=oracles[search].run(parse(cmd))
  except BaseException:print('Failed borrowed Cell case',len(commands),label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
 for search in (False,True):
  add('actual_two_actor_dispatch_'+str(search),search)
  for elevated,im,dest in itertools.product((0,1,255),(0,1),(0,1)):
   cells=parent.defaults()['cells'];cells[4][8]=1
   point=[0,0,0] if search else [12672,12928,0]
   add('actual_primary_elevated_and_raw_controls',search,cells=cells,elevated=elevated,actions=[[*point,im,dest,100]])
  for growth in ([0],[256],[0,1],[256,257],[0xffffffff]):add('snapshot_growth_low_byte',search,growth=growth)
  for n in (0,1,2):
   cells=parent.defaults()['cells'];objects=parent.defaults()['objects'];cells[4][7]=0 if n else -1
   objects[0][1]=1 if n==2 else -1
   add('snapshot_count',search,cells=cells,objects=objects)
  for ramp in range(21):
   cells=parent.defaults()['cells']
   for cell in cells:cell[4]=ramp
   add('actual_shared_floor_cache_all_ramps',search,cells=cells)
  for missing in range(9):
   cells=parent.defaults()['cells'];cells[missing][0]=-1
   add('actual_fallback_forwarding',search,cells=cells)
  for mission in (-1,0,2,6,7,16,19,31):
   objects=parent.defaults()['objects'];objects[0][4]=mission;objects[1][4]=7 if mission==2 else 2
   point=[0,0,0] if search else [12672,12928,0]
   add('independent_missions_and_all_queue_tails',search,objects=objects,actions=[[*point,1,1,100],[*point,1,1,101]])
  for key in ('suspended','field5c8','field5b9','forced','buffer','disabled1bc'):
   second=parent.defaults()['secondary'];second[0][key]=1
   add('second_actor_guard_isolation',search,secondary=second)
 # Preserve earlier writes across later roots and admission queries without a
 # callback refreshing copied motion/target state.
 for distance in (0,1,255,510,511,512,513,1024):
  cells=parent.defaults()['cells'];second=parent.defaults()['secondary']
  for cell in cells:cell[7]=0
  second[0].update(position=[12928+distance,12928,0],destination=[17,29,31],desired=49152,start=49152)
  add('actual_live_resident_distance',cells=cells,secondary=second,desired=16384,start=16384,actions=[[12672,12928,0,1,1,100],[12928,12672,1,1,1,101]])
 for mode,tick in itertools.product(range(4),(0,1,7,24,2147483647)):
  add('nearby_FP_and_frame_selection',True,fp_mode=mode,actions=[[0,0,0,1,1,tick]])
 for speed in range(9):add('actual_nearby_type_speed',True,speed_types=[speed,4,1,1,1])
 add('actual_two_actor_type_alias',True,type_indexes=[0,0,2,3,4])
 for actions in ([[12672,12928,0,1,1,100],[0,0,0,1,1,101]],[[0,0,0,1,1,100],[12672,12928,0,1,1,101]]):
  add('interleaved_zero_nonzero_roots_and_live_destinations',True,actions=actions)
 counts={str(k):dict(o.counts) for k,o in oracles.items()}
 require(all(oracles[k].counts['dispatch.'+str(i)]>0 for k in oracles for i in range(2)))
 require(oracles[False].counts['distance']>0 and oracles[True].counts['nearby_calls']>0)
 require(all(not o.counts['dispatch.'+str(i)] for o in oracles.values() for i in range(2,5)))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=counts,
  audited_original_calls=sum(o.audit_calls for o in oracles.values()),
  distinct_original_instructions=len(set().union(*(o.instructions for o in oracles.values()))))
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin');p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
 p.add_argument('--output',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=parent.compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 for bad in ('','J 0',parent.command()+' trailing',parent.command(objects=[[1,2,0,0,2,0,0,5,0,0,0,0,0,-1,-1,0,0],*parent.defaults()['objects'][1:]])):
  result=subprocess.run([str(a.native),str(a.exe),str(a.direction_data),str(a.render_data)],input=bad+'\n',text=True,capture_output=True)
  require(result.returncode!=0)
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'borrowed Cell Scatter sequences PASS')
if __name__=='__main__':main()
