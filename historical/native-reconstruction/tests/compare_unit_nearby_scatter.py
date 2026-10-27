#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual zero-point Unit Scatter through nearby search and Cell destinations."""
import argparse,copy,itertools,json,random,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
import compare_unit_scatter_world as parent
from verify_unit_nearby_scatter import verify
NATIVE=tuple(p for p in parent.NATIVE if p!='tests/unit_scatter_world_vectors.cpp')+('tests/unit_nearby_scatter_vectors.cpp','src/render/Lighting.cpp','src/assets/RenderData.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*source_closure(),'tests/unit_nearby_scatter/CMakeLists.txt','tests/original_unit_nearby_scatter.py','tests/compare_unit_nearby_scatter.py','tests/test_unit_nearby_scatter_evidence.py','tools/verify_unit_nearby_scatter.py','tools/verify_nearby_location_map.py','tools/verify_nearby_location.py','tools/verify_nearby_cell_admission.py'))))
FLAGS=dict(actual_complete_zero_point_Unit_Scatter=True,actual_nearby_permission_rectangle_Cell_projection=True,
 actual_Cell_destination_effects=True,shared_actor_Drive_map_fallback_type_input=True,
 initial_records_and_associations_supplied=True,Cell_dispatch_joined=False,Advance6_executed=False,
 Process_joined=False,production_owned_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Unit nearby Scatter evidence/input')
def defaults():
 c=parent.defaults();c.update(speed_type=1,dimension1=0,fp_mode=0,actions=[[0,0,0,0,0,100]])
 return c
def command(**kw):
 c=defaults();c.update(kw);return 'N '+str(c['speed_type'])+' '+str(c['dimension1'])+' '+str(c['fp_mode'])+' '+parent.command(**{k:v for k,v in c.items() if k not in ('speed_type','dimension1','fp_mode')})
def parse(cmd):
 t=cmd.split();require(len(t)>5 and t[0]=='N' and t[4]=='J');speed,dim,mode=map(int,t[1:4]);require(0<=speed<=8 and -2147483648<=dim<=2147483647 and 0<=mode<=3)
 # Reuse the complete parent fixture parser; P permits a zero point, but this
 # entry remains a genuine Unit call. Explicitly restrict every action to zero.
 c=parent.parse('P '+' '.join(t[5:]));require(all(a[:3]==[0,0,0] for a in c['actions']))
 require(all(a[5]>=0 for a in c['actions']))
 c.update(projection=False,speed_type=speed,dimension1=dim,fp_mode=mode);return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},direction_data_sha256=hash_file(a.direction_data),render_data_sha256=hash_file(a.render_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and all(isinstance(n,str) for n in row) and row.count('state')==1)

def generate(a):
 from original_unit_nearby_scatter import UnitNearbyScatterOracle
 o=UnitNearbyScatterOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,**kw):
  cmd=command(**kw)
  try:row=o.run(parse(cmd))
  except BaseException:
   print('Failed Unit nearby case',len(commands),label,flush=True);raise
  expected.append(row);commands.append(cmd);labels.append(label);groups[label]=groups.get(label,0)+1
 add('complete_zero_point_caller_and_destination')
 for mode in range(4):
  for tick in (0,1,2,7,23,24,25,2147483647):add('frame_selection_and_host_FP',fp_mode=mode,actions=[[0,0,0,0,0,tick]])
 for speed in range(9):
  for bits in (0,0x3f800000,0xbf800000,0x7fc00000):add('borrowed_type_speed_and_actual_Cell_admission',speed_type=speed,speeds=[bits]*12,dimension1=1)
 for mission in (-1,0,2,6,7,16,19,31):
  objects=defaults()['objects'];objects[0][4]=mission
  add('mission_eligibility_and_zero_path_no_queue',objects=objects)
 for key,value in (('control9',0),('control7',1),('field5b9',1),('field599',1),('field5c8',1),('suspended',1),('field5c0',0),('field3fc',1),('buffer',1),('forced',1),('global_references',0xffffffff)):
  add('zero_path_control_destination_guard',**{key:value})
 for bridge in (0,1,2,255):
  for point in ([12928,12928,0],[-1,-257,0],[-257,-65537,33],[2147483647,-2147483648,0]):
   add('signed_secondary_quotient_retained_alternate_bytes',position=point,bridge=bridge,suspended=1,shape=[64,-100,0,500,500],dimension1=-64)
 for head in ([12928,12928,1],[13184,12928,0],[12672,12928,0],[0,0,1]):add('head40_not_destination34',head=head,destination=[17,29,31])
 for registry in (-128,-1,0,127):
  add('actual_secondary_registry_source',registry=registry,poolx=51,pooly=49)
 for dimension in (-65,-64,-63,-62,0,64):add('loop_bound_and_no_candidates',dimension1=dimension,shape=[64,0,0,64,64])
 for i in range(9):
  cells=defaults()['cells'];cells[i][0]=-1;add('shared_fallback_source_destination',cells=cells)
 for occupation,elevated,flag in ((0,0,0),(1,0,0),(0x100,0,0),(32,0,0),(0,1,0x100),(1,0,0x100)):
  cells=defaults()['cells']
  for c in cells:c[9]=occupation;c[10]=elevated;c[5]=flag
  add('actual_primary_elevated_occupation',cells=cells,dimension1=0,suspended=1)
 for ramp in range(21):
  cells=defaults()['cells'];cells[0][3]=-1;cells[0][4]=ramp;cells[-1][3]=-1;cells[-1][4]=ramp
  add('actual_destination_floor_cache_ramp',cells=cells)
 for tick in (1,7,24):
  add('retained_search_command_lifetime_and_queues',actions=[[0,0,0,1,1,tick+i] for i in range(8)])
 require(o.counts['nearby_calls']>0 and o.counts['0x7053f0']>0 and o.counts['permission.0']>0 and o.counts['permission.1']>0 and o.counts['Cell_return.0']>0 and o.counts['Cell_return.1']>0)
 require(o.counts['0x6388a0']==0 and o.counts['0x594cb0']==0 and o.counts['0x4ba410']==0)
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,original_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),selected_native_machine_write_order_claim=False)

def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.direction_data),str(a.render_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Unit nearby Scatter runner failed',p.returncode,p.stderr[:2000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Unit nearby Scatter differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin');p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-nearby-scatter-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'unit-nearby-scatter sequences PASS')
if __name__=='__main__':main()
