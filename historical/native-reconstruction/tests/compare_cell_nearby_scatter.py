#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Cell dispatch into actual zero-point Unit nearby destinations."""
import argparse,copy,itertools,json,re,subprocess,time
from pathlib import Path
import compare_cell_unit_scatter_world as parent
import compare_unit_nearby_scatter as unit
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_cell_nearby_scatter import verify
NATIVE=('tests/cell_nearby_scatter_vectors.cpp',*parent.NATIVE[1:])
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  p=pending.pop()
  if p in seen:continue
  seen.add(p)
  for n in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
   local=(ROOT/p).parent/n;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+n)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*unit.SOURCES,*source_closure(),'tests/cell_nearby_scatter/CMakeLists.txt','tests/original_cell_nearby_scatter.py','tests/compare_cell_nearby_scatter.py','tests/test_cell_nearby_scatter_evidence.py','tools/verify_cell_nearby_scatter.py'))))
FLAGS=dict(actual_complete_Cell_dispatch_to_zero_point_Unit_nearby=True,actual_shared_type_aliases_and_speed_inputs=True,
 actual_nearby_permission_rectangle_Cell_projection_destinations=True,prior_nonzero_Track_profile_retained=True,
 supplied_heap_atomic_padding_and_initial_associations=True,Advance6_executed=False,Process_joined=False,
 production_owned_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Cell nearby evidence/input')
def defaults():
 c=parent.defaults();c.update(dimension1=0,fp_mode=0,speed_type=1,speed_types=[1]*5,type_indexes=list(range(5)),nearby_speeds=[0x3f800000]*108,actions=[[0,0,0,1,1,100]])
 return c
def command(**kw):
 c=defaults();c.update(kw);v=[c['dimension1'],c['fp_mode'],*c['speed_types'],*c['type_indexes'],*c['nearby_speeds']]
 return 'N '+' '.join(map(str,v))+' '+parent.command(**{k:v for k,v in c.items() if k in parent.defaults()})
def parse(cmd):
 t=cmd.split();require(len(t)>121 and t[0]=='N');v=list(map(int,t[1:121]));dim,mode=v[:2];speeds=v[2:7];indexes=v[7:12];table=v[12:120]
 require(-2147483648<=dim<=2147483647 and 0<=mode<=3 and all(0<=n<=8 for n in speeds) and all(0<=n<5 for n in indexes) and all(0<=n<=0xffffffff for n in table))
 core,extra=' '.join(t[121:]).split(' X ');require(core.startswith('J '))
 world=parent.parent.parse('P '+core[2:]);actual=world['actions'];world['projection']=False
 world['actions']=[[1,0,0,*a[3:]] if a[:3]==[0,0,0] else a for a in actual]
 c=parent.parse(parent.parent.command(**world)+' X '+extra);c['actions']=actual
 require(all(a[5]>=0 for a in actual))
 # Both original children read one shared land table. The retained nonzero
 # Unit profile consumes column1; other columns belong to nearby admission.
 require(all(table[i*9+1]==c['speeds'][i] for i in range(12)))
 for i in range(5):
  j=indexes[i]
  require(all(c['objects'][i][k]==c['objects'][j][k] for k in (3,8,9,10,11,15,16)))
 c.update(dimension1=dim,fp_mode=mode,speed_type=1,speed_types=speeds,type_indexes=indexes,nearby_speeds=table);return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},direction_data_sha256=hash_file(a.direction_data),render_data_sha256=hash_file(a.render_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and all(isinstance(n,str) for n in row) and row.count('state')==1 and row.count('actor')==4)

def generate(a):
 from original_cell_nearby_scatter import CellNearbyScatterOracle
 o=CellNearbyScatterOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,**kw):
  cmd=command(**kw)
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed Cell nearby case',len(commands),label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
 add('two_distinct_zero_point_Unit_destinations')
 for mode in range(4):
  for tick in (0,1,7,24,2147483647):add('native_FP_and_frame_selection',fp_mode=mode,actions=[[0,0,0,1,1,tick]])
 for elevated,im,dest in itertools.product((0,1,255),(0,1),(0,1)):
  cells=defaults()['cells'];cells[4][8]=1
  add('actual_Cell_heads_and_raw_controls',cells=cells,elevated=elevated,actions=[[0,0,0,im,dest,100]])
 for n in (0,1,2,5):
  objects=defaults()['objects'];cells=defaults()['cells'];cells[4][7]=0 if n else -1
  for i in range(5):objects[i][1]=i+1 if i+1<n else -1
  add('actual_snapshot_count_independent_actor_state',objects=objects,cells=cells)
 for indexes in ([0,0,0,0,0],[0,0,2,2,0],[4,3,2,1,0]):
  objects=defaults()['objects']
  for i in range(5):objects[i][1]=i+1 if i<4 else -1
  add('actual_shared_type_aliases_distinct_actors_Drives',objects=objects,type_indexes=indexes,speed_types=[1,4,3,0,2],actions=[[0,0,0,1,1,100],[0,0,0,1,1,101]])
 for speed in range(9):
  table=defaults()['nearby_speeds']
  for land in range(12):
   for col in range(9):table[land*9+col]=0 if col not in (1,4) else 0x3f800000
  add('borrowed_distinct_type_speeds_one_shared_land_table',speed_types=[speed,4,1,1,1],nearby_speeds=table)
 for growth in ([0],[256],[0,1],[256,257],[0xffffffff],[255],[0,0,1]):add('growth_low_byte_and_snapshot',growth=growth)
 for mission in (-1,0,2,6,7,16,19,31):
  objects=defaults()['objects'];objects[0][4]=mission;objects[1][4]=7 if mission==2 else 2
  add('independent_missions_and_all_queue_words',objects=objects,actions=[[0,0,0,1,1,100],[0,0,0,1,1,101]])
 for rank in (-1.,0.,1.,1.9999999999999998,2.,float('inf')):
  for ability in ((0,0),(1,0),(0,255)):
   types=defaults()['types'];types[1]=list(ability)
   add('original_promotion_prepass_and_late_House_eligibility',rule=0,types=types,ranks=[parent.bits(0.),parent.bits(rank),parent.bits(0.),parent.bits(0.),parent.bits(0.)],actions=[[0,0,0,0,0,100]])
 for ramp in range(21):
  cells=defaults()['cells']
  for c in cells:c[4]=ramp
  add('actual_destination_floor_and_shared_cache_ramps',cells=cells)
 for missing in range(9):
  cells=defaults()['cells'];cells[missing][0]=-1;add('missing_slots_shared_fallback',cells=cells)
 for key in ('suspended','field5c8','field5b9','forced','buffer','disabled1bc'):
  second=defaults()['secondary'];second[0][key]=1;add('second_actor_guard_isolation',secondary=second)
 for bridge in (0,1,2,255):
  second=defaults()['secondary'];second[0].update(position=[-257,-65537,33],bridge=bridge,suspended=1)
  add('signed_secondary_source_and_alternate_upper_bytes',secondary=second,position=[-1,-257,0],bridge=bridge,suspended=1,dimension1=-64)
 for occupancy,elevated,flags in ((1,0,0),(0,1,0x100),(0x100,0,0),(32,32,0x100)):
  cells=defaults()['cells']
  for c in cells:c[9]=occupancy;c[10]=elevated;c[5]=flags
  add('actual_Cell_occupation_selection_and_type4_bypass',cells=cells,speed_types=[1,4,1,1,1],suspended=1)
 # Keep original nonzero Track behavior reachable in the same new composition.
 for actionSet in ([[12672,12928,0,1,1,100],[0,0,0,1,1,101]],[[0,0,0,1,1,100],[12672,12928,0,1,1,101]]):
  add('interleaved_actual_zero_and_nonzero_Track_branches',actions=actionSet)
 require(all(o.counts[k]>0 for k in ('zero_dispatch_no_RNG_or_queue','nearby_calls','0x7053f0','permission.0','permission.1','Cell_return.0','Cell_return.1','chosen.empty','chosen.nonempty')))
 require(all(o.counts['nearby.actor.'+str(i)]>0 for i in range(5)))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,original_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),selected_native_machine_write_order_claim=False)

def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.exe),str(a.direction_data),str(a.render_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Cell nearby Scatter runner failed',p.returncode,p.stderr[:2000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Cell nearby Scatter differs',i,j,got[max(0,j-8):j+15],want[max(0,j-8):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin');p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/cell-nearby-scatter-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'cell-nearby-scatter sequences PASS')
if __name__=='__main__':main()
