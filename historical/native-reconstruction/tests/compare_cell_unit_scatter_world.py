#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Cell dispatch to actual Unit Scatter/world and live admission."""
import argparse,copy,itertools,json,random,re,struct,subprocess,time
import pefile
from pathlib import Path
import compare_unit_scatter_world as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_cell_unit_scatter_world import verify
SECOND='queued queued_byte forced suspended field5b9 field599 target bridge registry references initial_target buffer owned capacity count field490 powered field5c8 field5c0 field3fc guard_start guard_remaining disabled1bc disabled1c0 desired start timer duration rate padding'.split()
NATIVE=('tests/cell_unit_scatter_world_vectors.cpp',*parent.NATIVE[1:],'src/render/Lighting.cpp','src/assets/RenderData.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  p=pending.pop()
  if p in seen:continue
  seen.add(p)
  for n in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
   local=(ROOT/p).parent/n;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+n)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*source_closure(),'src/sim/CellScatter.hpp','tests/cell_unit_scatter_world/CMakeLists.txt','tests/original_cell_unit_scatter_world.py','tests/compare_cell_unit_scatter_world.py','tests/test_cell_unit_scatter_world_evidence.py','tools/verify_cell_unit_scatter_world.py','tools/verify_cell_scatter.py','tools/verify_moving_unit_admission.py'))))
FLAGS=dict(actual_complete_Cell_dispatch_and_Unit_Scatter_world=True,actual_live_moving_admission=True,
 shared_distinct_actors_Drives_targets_queues_RNG_and_fallback=True,supplied_heap_services=True,
 initial_records_and_associations_supplied=True,zero_point_pathfinder_supported=False,
 Building_Scatter_supported=False,Advance6_executed=False,Process_joined=False,
 production_owned_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Cell Unit Scatter world evidence/input')
def bits(n):return struct.unpack('<Q',struct.pack('<d',n))[0]
def defaults():
 c=parent.defaults()
 c['objects']=[[1,i+1 if i<1 else -1,0,0,2,0,0,5,0,0,0,0,0,-1,-1,0,0] for i in range(5)]
 c['cells'][4][7]=0
 secondary=[]
 for i in range(1,5):
  a={k:copy.deepcopy(c[k]) for k in (*SECOND,'position','head','destination','queue')}
  a['position']=[12928,12928+i*64,0];a['queue']=[(i+3)%8,*range(100*i,100*i+23)];a['references']=3+i;a['padding']=-31-i;secondary.append(a)
 c.update(cell=4,elevated=0,rule=1,threshold=3,growth=[1],houses=[0,5,7],types=[[0,0] for _ in range(5)],ranks=[bits(0.)]*5,eligibility=[1]*5,short=[0]*5,track=[2]*5,index=[9]*5,secondary=secondary)
 return c
def command(**kw):
 c=defaults();c.update(kw)
 core=parent.command(**{k:v for k,v in c.items() if k in parent.defaults()})
 v=[c['cell'],c['elevated'],c['rule'],c['threshold'],len(c['growth']),*c['growth'],*c['houses'],*itertools.chain.from_iterable(c['types']),*c['ranks'],*c['eligibility'],*c['short'],*c['track'],*c['index']]
 for a in c['secondary']:
  v.extend(a[k] for k in SECOND)
  for k in ('position','head','destination','queue'):v.extend(a[k])
 return core+' X '+' '.join(map(str,v))
def parse(cmd):
 parts=cmd.split(' X ');require(len(parts)==2);c=parent.parse(parts[0]);require(not c['projection']);v=list(map(int,parts[1].split()));at=0
 def take(n):
  nonlocal at
  r=v[at:at+n];at+=n;require(len(r)==n);return r
 c['cell'],c['elevated'],c['rule'],c['threshold'],n=take(5);require(0<=c['cell']<=9 and 0<=c['elevated']<=255 and 0<=c['rule']<=255 and -2147483648<=c['threshold']<=2147483647 and 1<=n<=8)
 c['growth']=take(n);c['houses']=take(3);c['types']=[take(2) for _ in range(5)];c['ranks']=take(5);c['eligibility']=take(5);c['short']=take(5);c['track']=take(5);c['index']=take(5);c['secondary']=[]
 require(all(0<=x<=0xffffffff for x in c['growth']) and all(-2147483648<=x<=2147483647 for x in (*c['houses'],*c['index'])))
 require(all(0<=x<=255 for x in (*itertools.chain.from_iterable(c['types']),*c['eligibility'],*c['short'])) and all(0<=x<64 for x in c['track']) and all(0<=x<1<<64 for x in c['ranks']))
 require(all(row[0]==1 and row[13]==-1 for row in c['objects']))
 for i in range(1,5):
  a=dict(zip(SECOND,take(len(SECOND))))
  for k,n in (('position',3),('head',3),('destination',3),('queue',24)):a[k]=take(n)
  # Reuse the parent's input-domain checks on each separately supplied actor.
  test={k:copy.deepcopy(v) for k,v in c.items() if k in parent.defaults()};test.update(a);test['objects'][0]=copy.deepcopy(c['objects'][i]);test['objects'][0][1]=-1
  parent.parse(parent.command(**test));c['secondary'].append(a)
 require(at==len(v));return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},direction_data_sha256=hash_file(a.direction_data),render_data_sha256=hash_file(a.render_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and all(isinstance(n,str) for n in row) and row.count('state')==1 and row.count('actor')==4)
def generate(a):
 from original_cell_unit_scatter_world import CellUnitScatterWorldOracle
 o=CellUnitScatterWorldOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,**kw):
  cmd=command(**kw)
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed Cell world case',len(commands),label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
 add('two_distinct_Unit_commands')
 for elevated,im,dest in itertools.product((0,1,255),(0,1,255),(0,1,255)):
  cells=defaults()['cells'];cells[4][8]=1
  add('primary_elevated_raw_controls',cells=cells,elevated=elevated,actions=[[12672,12928,0,im,dest,100]])
 for rank in (-1.,0.,1.,1.9999999999999998,2.,float('inf')):
  for ability in ((0,0),(1,0),(0,255)):
   types=defaults()['types'];types[1]=list(ability)
   add('promotion_and_House_late_eligibility',rule=0,types=types,ranks=[bits(0.),bits(rank),bits(0.),bits(0.),bits(0.)])
 add('NaN_rank_not_elite',rule=0,ranks=[0x7ff8000000000123]*5)
 for growth in ([0],[256],[0,1],[256,257],[0xffffffff],[255],[0,0,1]):add('growth_failure_low_byte',growth=growth)
 for n in (0,1,2,5):
  objects=defaults()['objects'];cells=defaults()['cells'];cells[4][7]=0 if n else -1
  for i in range(5):objects[i][1]=i+1 if i+1<n else -1
  add('snapshot_size_and_separate_targets',objects=objects,cells=cells)
 # Candidate Cell lists include residents. First commands change live target
 # activity; later admissions must consume those actual earlier writes.
 for variant in range(12):
  cells=defaults()['cells'];secondary=defaults()['secondary'];objects=defaults()['objects']
  cells[5][7]=0 # supplied shared list identity in this diagnostic map
  if variant&1:
   for cell in cells:cell[7]=0
  if variant&2:secondary[0]['destination']=[17,29,31]
  if variant&4:secondary[0]['initial_target']=5
  if variant&8:secondary[0]['desired']=32768;secondary[0]['duration']=40;secondary[0]['timer']=90
  add('live_resident_activity_after_prior_command',cells=cells,secondary=secondary,objects=objects,actions=[[12672,12928,0,1,1,100],[12928,12672,1,1,1,101]])
 for distance in (0,1,255,510,511,512,513,1024):
  cells=defaults()['cells'];secondary=defaults()['secondary']
  for cell in cells:cell[7]=0
  secondary[0].update(position=[12928+distance,12928,0],destination=[17,29,31],desired=49152,start=49152)
  add('joined_actual_head_on_distance_cutoff',cells=cells,secondary=secondary,desired=16384,start=16384,actions=[[12672,12928,0,1,1,100]])
 # Derive ordinary pending-switch fixtures from the fingerprinted supplied data;
 # no extracted transition/descriptor constants are embedded in test source.
 pe=pefile.PE(str(a.exe));pending=[]
 for short in (0,):
  found=None
  for track in range(64):
   raw=pe.get_data(0x7a0180+12*track-0x400000,12);selected=raw[short]
   if not 1<=selected<=6:continue
   jump=struct.unpack('<i',pe.get_data(0x7a00a4+16*selected-0x400000,4))[0]
   direction=((((struct.unpack_from('<i',raw,4)[0]<<8)>>12)+1)>>1)&7
   for q in range(8):
    candidate=pe.get_data(0x7a0180+12*(q+8*direction)-0x400000,1)[0]
    if q==direction or not 1<=candidate<=6 or not jump:continue
    entry=struct.unpack('<i',pe.get_data(0x7a00a8+16*candidate-0x400000,4))[0]
    if entry:found=(track,q,jump);break
   if found:break
  require(found is not None);pending.append((short,*found))
 for short,track,q,jump in pending:
  for offset in (0,1):
   cells=defaults()['cells'];secondary=defaults()['secondary']
   for cell in cells:cell[7]=0
   secondary[0]['destination']=[17,29,31];secondary[0]['queue'][0]=q
   tracks=[2]*5;tracks[1]=track;indices=[9]*5;indices[1]=jump+offset;shorts=[0]*5;shorts[1]=short;eligibility=[1]*5;eligibility[1]=0
   add('joined_actual_pending_switch_both_results',cells=cells,secondary=secondary,track=tracks,index=indices,short=shorts,eligibility=eligibility,actions=[[12672,12928,0,1,1,100]])
 cells=defaults()['cells'];secondary=defaults()['secondary']
 for cell in cells:cell[7]=0
 secondary[0]['destination']=[17,29,31];secondary[0]['queue'][0]=-1
 add('joined_short_track_empty_queue_early_return',cells=cells,secondary=secondary,short=[0,1,0,0,0],eligibility=[1,0,1,1,1],actions=[[12672,12928,0,1,1,100]])
 for mission in (-1,0,2,6,7,16,19,31):
  objects=defaults()['objects'];objects[0][4]=mission;objects[1][4]=7 if mission==2 else 2
  add('per_actor_missions_and_queue_tails',objects=objects,actions=[[12672,12928,0,1,1,100],[12672,12928,0,1,1,101]])
 for ramp in range(21):
  cells=defaults()['cells']
  for cell in cells:cell[4]=ramp
  add('all_ramps_and_shared_floor_cache',cells=cells)
 for missing in range(9):
  cells=defaults()['cells'];cells[missing][0]=-1
  add('shared_fallback_and_missing_slot',cells=cells)
 for k in ('suspended','field5c8','field5b9','forced','buffer','disabled1bc'):
  secondary=defaults()['secondary'];secondary[0][k]=1
  add('independent_second_actor_guards',secondary=secondary)
 rng=random.Random(0x4769207072d0)
 for _ in range(40):
  objects=defaults()['objects'];order=list(range(5));rng.shuffle(order);cells=defaults()['cells'];cells[4][7]=order[0];cells[4][8]=order[-2]
  for i,j in enumerate(order):objects[j][1]=order[i+1] if i<4 else -1
  add('retained_random_order_RNG_and_actor_destinations',objects=objects,cells=cells,elevated=rng.randrange(2),table=[rng.getrandbits(32) for _ in range(250)],next1=248,next2=249,actions=[[12672,12928,1,1,1,100+i] for i in range(4)])
 require(all(o.counts[k]>0 for k in ('distance','switch.0','switch.1','0x703748','a.0','a.2','a.6','a.7')))
 require(all(o.counts['dispatch.'+str(i)]>0 for i in range(5)) and all(o.counts['ramp.'+str(i)]>0 for i in range(21)))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,original_write_counts=dict(o.writes),distinct_original_instructions=len(o.instructions),selected_native_machine_write_order_claim=False)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.exe),str(a.direction_data),str(a.render_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Cell Scatter world runner failed',p.returncode,p.stderr[:2000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Cell Scatter world differs',i,j,got[max(0,j-8):j+15],want[max(0,j-8):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 p.add_argument('--direction-data',type=Path,default=ROOT/'private/derived/ra2-1006/direction-data.bin');p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/cell-unit-scatter-world-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'cell-unit-scatter-world sequences PASS')
if __name__=='__main__':main()
