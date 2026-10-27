#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete ordinary Walk heads with actual Infantry/selector children."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
import compare_infantry_subcell as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_walk_head import verify
NATIVE=tuple(p for p in parent.NATIVE if p!='tests/infantry_subcell_vectors.cpp')+('tests/walk_head_vectors.cpp','src/sim/WalkHead.cpp','src/sim/UnitDiscovery.cpp')
ORIGINAL=(*parent.ORIGINAL,'tests/original_walk_head.py','tools/verify_walk_head.py','tests/compare_walk_head.py')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_walk_head.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_ordinary_Walk_head=True,actual_Infantry_release_selector_claim=True,actual_mission_and_overlay_free_Cell=True,
 ordered_occupation_and_head_stores=True,initial_records_map_floor_and_seeding_supplied=True,
 entered_target_building_overlay_children=False,complete_Process_preparation=False,production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Walk head evidence/input differs')
def step(point=(384,128,0),kind=0,trigger=0,mutation=0,floor=0,threshold=104,house=3,height=104,level=104,mission=2,queued=-1):
 return (*point,kind,trigger,mutation,floor,threshold,house,height,level,mission,queued)
def command(steps=None,position=(128,128,0),head=(192,192,0),cells=parent.DEFAULT_CELLS,target=0,disabled=0,first=0,second=103,seed=0x71f590):
 steps=[step()] if steps is None else steps
 return 'H '+' '.join(map(str,(disabled,first,second,seed,*position,*head,*itertools.chain.from_iterable(cells),target,len(steps),*itertools.chain.from_iterable(steps))))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='H');v=list(map(int,t[1:]));require(len(v)>=22)
 disabled,first,second,seed=v[:4];require(0<=disabled<=255 and 0<=first<250 and 0<=second<250 and 0<=seed<=0xffffffff)
 require(all(-2147483648<=n<=2147483647 for n in v[4:10]));position=v[4:7];head=v[7:10];cells=[v[10:15],v[15:20]]
 for c in cells:require(all(0<=n<=0xffffffff for n in c[:3]) and all(-2147483648<=n<=2147483647 for n in c[3:]))
 target,count=v[20:22];require(target in (0,1) and 1<=count<=512 and len(v)==22+13*count);steps=[v[22+13*i:35+13*i] for i in range(count)]
 for s in steps:require(all(-2147483648<=n<=2147483647 for n in s) and 0<=s[3]<=2 and 0<=s[4]<=8 and 0<=s[5]<=1023)
 return disabled,first,second,seed,position,head,cells,target,steps
def scenarios():
 for mask,flags,z in itertools.product(range(64),(0,256),(311,312,313)):
  cells=((0x12340000|mask,0x56780000|(mask^31),flags,17,23),(0x98760000|mask,0xabcd0000|(mask^31),flags,-7,9))
  yield 'shared_occupation_masks_bridge_strictness_and_empty_reclaim',command(position=(128,128,z),cells=cells,
   steps=[step(),step(point=(0,0,0)),step(point=(448,192,0))])
 for m,q,head in itertools.product((-2147483648,-1,0,2,7,8,9,11,25,28,2147483647),(-1,8),( (0,0,0),(192,192,0))):
  yield 'repeated_mission_queries_and_queued_fallback',command(head=head,steps=[step(mission=m,queued=q),step(point=(0,0,0),mission=m,queued=q)])
 for level,floor,delta in itertools.product((-2147483648,-104,0,104,0x40000000,2147483647),(-7,0,104),(-1,0,1)):
  boundary=(floor+3*level)&0xffffffff;z=((boundary+delta+0x80000000)&0xffffffff)-0x80000000
  cells=tuple((c[0],c[1],256,c[3],c[4]) for c in parent.DEFAULT_CELLS)
  yield 'saved_actor_Z_and_wrapped_triple_height',command(position=(128,128,z),cells=cells,steps=[step(level=level,floor=floor)])
 for mutation,trigger,kind in itertools.product((1,2,4,8,16,32,64,128,256,512,1023),(1,2,3,4),(0,1,2)):
  cells=tuple((c[0],c[1],256,c[3],c[4]) for c in parent.DEFAULT_CELLS)
  yield 'late_floor_changes_saved_points_and_request_aliases',command(position=(128,128,313),cells=cells,
   steps=[step(kind=kind,trigger=trigger,mutation=mutation),step(point=(0,0,0))])
 for disabled,head in itertools.product((0,1,128,255),((0,0,0),(192,192,0))):
  yield 'retained_random_state_and_index_wrap',command(disabled=disabled,head=head,first=249,second=102,steps=[step()]*32)
 for point,kind in itertools.product(((-1,-1,-7),(-257,-511,17),(2147483647,-2147483648,0),(0,0,0)),(0,1,2)):
  yield 'signed_bases_and_input_head_actor_aliases',command(position=(-255,-1,17),steps=[step(point=point,kind=kind),step(point=(0,0,0))])
 yield 'unconsumed_target_for_ordinary_mission',command(target=1,steps=[step(mission=2),step(point=(0,0,0),mission=8)])
def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},
  data={k:hash_file(getattr(a,k)) for k in ('render_data','subcell_data')}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_original_calls']==1+sum(len(parse(cmd)[-1]) for cmd in e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  count=len(parse(cmd)[-1]);require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('rng')==1 and row.count('R')==count)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','subcell-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_walk_head import WalkHeadOracle
  o=WalkHeadOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_head(*parse(cmd))
   except BaseException:print('Failed Walk head scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.counts))
  require(all(o.counts.get(hex(k),0)>0 for k in (0x71f590,0x4764b0,0x508410,0x5084a0,0x483390,0x6388a0,0x6c7420,0x594770,0x476cc0)))
  require(o.counts['0x71f590']==o.audit_calls-1 and current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=origin))
  fingerprint=hash_file(source);write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data),str(a.subcell_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
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
 write_report(a.exe,report,result);print(len(commands),'ordinary Walk head sequences PASS;',meta['audited_original_calls'],'audited original calls; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
