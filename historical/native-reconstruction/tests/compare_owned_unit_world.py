#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare owned Process -> two complete draws -> Process in one original guest."""
import json,struct,subprocess,time
import compare_shared_ground_world as shared
import compare_owned_unit_resident as resident
from original_results import OriginalResults
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_owned_unit_world import verify
SOURCES=tuple(dict.fromkeys((*shared.SOURCES,*resident.SOURCES,
 'src/assets/OwnedUnitDrawingMap.hpp','src/assets/OwnedUnitDrawingMap.cpp','src/assets/OwnedUnitProcesses.hpp',
 'src/render/OwnedUnitDrawScene.hpp','tests/owned_unit_world_vectors.cpp',
 'tests/original_owned_unit_world.py','tests/compare_owned_unit_world.py',
 'tests/test_owned_unit_world_evidence.py','tools/verify_owned_unit_world.py','tools/verify_unit_models.py')))
def parse(cmd):
 words=cmd.split()
 if not words:raise ValueError('Empty owned world command')
 op=words[0]
 if op in ('P','O','D'):
  parsed=shared.parse(cmd)
  if op=='O' and parsed[1][0]!=0:raise ValueError('Owned world requires normal remap')
  if op=='D' and parsed[1][2]!=0:raise ValueError('Owned contact association must remain empty')
  return parsed
 if op=='I':
  if len(words)!=55:raise ValueError('Malformed owned initialization')
  _,v=resident.parse('R '+' '.join(words[1:-2]));head,route,numeric,crusher,parked,heading,first,second,order=v
  turrets=list(map(int,words[-2:]))
  if head[10:16]!=[1,0,1,0,1,0] or crusher!=1 or order!=0 or any(not 0<=t<=65535 for t in turrets):raise ValueError('Owned initialization outside domain')
  return op,(*v,turrets)
 if op=='T' and len(words)==2:
  tick=int(words[1])
  if -2147483648<=tick<=2147483647:return op,tick
 raise ValueError('Malformed owned world command')
def identities(a):
 return {'inputs':shared.identities(a),'inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Owned world engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Owned world identity differs')
 if not e['evidence'].get('same_guest_Process_interleaved_draws_Process'):raise ValueError('Owned world join differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[]))):raise ValueError('Owned world counts differ')
 ready=reset=initialized=False
 for cmd in e['commands']:
  try:op,v=parse(cmd)
  except (AssertionError,ValueError,TypeError,IndexError,OverflowError,struct.error):raise ValueError('Malformed owned world command') from None
  if op=='P':ready=True;reset=initialized=False
  elif op=='O':
   if not ready or reset:raise ValueError('Fresh prepared map required')
   reset=True;initialized=False
  elif op=='I':
   if not reset or initialized:raise ValueError('Fresh reset required')
   initialized=True
  elif not initialized:raise ValueError('Owned initialization required')
def generate(a,pilot=False):
 from original_owned_unit_world import OwnedUnitWorldOracle
 from original_shared_unit_staging import SUBJECTS,DRIVES
 from original_map_preparation import SLOTS
 from original_foot_lit import words,ints
 o=OwnedUnitWorldOracle(a.exe,a.assets,a.palette.read_bytes())
 commands=[];expected=[];labels=[];samples=[];groups={};draws=ticks=0;now=0
 def run(label,cmd):
  nonlocal draws,ticks,now
  op,v=parse(cmd)
  if op=='P':result=o.prepare_map(v)
  elif op=='O':o.reset_shared(v[1]);result=['reset']
  elif op=='I':
   head,route,numeric,crusher,parked,heading,first,second,order,turrets=v
   now=head[9];o.movement.retry_padding=(first,second);o.initialize(head,route,numeric,parked,heading,turrets)
   result=o.movement.events.copy()
  elif op=='T':now=v;result=o.movement.advance(now).copy();ticks+=1
  else:
   id=v[0];before=len(o.relative_heights);result=o.draw_shared(id,now,v[1:]);draws+=1
   actor,drive=SUBJECTS[id],DRIVES[id];x,y,z=ints(o.u,actor+0x88,3)
   cell=words(o.u,SLOTS+((y//256)*512+x//256)*4,1)[0]
   bi=result.index('body');matrix=list(map(int,result[bi+1:bi+13]))
   samples.append({'actor':id,'tick':now,'location':[x,y,z],'stored_ramp':words(o.u,drive+0x1c,1)[0],
    'Cell_ramp':o.u.mem_read(cell+0x11c,1)[0],'relative_heights':o.relative_heights[before:],'body_matrix_dwords':matrix})
  if op in ('I','T','D'):result=[*result,*o.movement.snapshot()]
  commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);groups[label]=groups.get(label,0)+1
  if op!='T' or ticks%16==0:print(label,ticks,'ticks',draws,'draws',flush=True)
 def draw(id,label):
  values=[shared.floor.bits(.125),0,0,0,1,0,7,1,0,1312,1,0,0,80+id*5,72,0,0,160,144]
  run(label,'D '+' '.join(map(str,[id,*values])))
 def scenario(label,f,steps=8,**kw):
  run(label+'_preparation','P '+shared.floor.command(*f[:5],f[5:]));run(label+'_reset','O 0 0')
  kw.update(steps=1,mode=0,marked=0,effect=1,present=1,key=0)
  init=resident.command(**kw);run(label+'_actual_placement','I '+init[2:]+' 0 32768')
  lag_draws=0
  for j in range(steps):
   run(label+'_Process','T '+str(100+j))
   x,y,_=ints(o.u,SUBJECTS[0]+0x88,3);cell=words(o.u,SLOTS+((y//256)*512+x//256)*4,1)[0]
   lag=words(o.u,DRIVES[0]+0x1c,1)[0]!=o.u.mem_read(cell+0x11c,1)[0]
   if j in (0,1,steps-1) or j%16==0 or (lag and lag_draws<2):
    for id in (0,1,0):draw(id,label+'_interleaved_complete_draw')
    lag_draws+=lag
 source=json.loads(a.depth_fixture.read_text());template,_=shared.prepared.parse(source['commands'][3]);common=list(template[5])
 common[:5]=[12,12,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 def fixture(ramp=0,level=0):
  types=[[1,1,1,60,30,1,0,0,0,0,0],[1,1,1,60,30,1,0,ramp,0,0,0]]
  cells=[[x,y,int(x==12),0,level if x==12 else 0,0,-1,0,0,0,0,0,17,91,-1,41,0] for y in range(25) for x in range(25) if x+y>12 and abs(x-y)<12 and x+y<=36]
  return (*template[:5],common,[12,0,0,12,12],types,cells,[],[],template[11],[])
 scenario('occupied_target',fixture(),at=(2944,3200,0),destination=(3968,3200,0),heading=16384,route=(2,-1,4,5),parked_at=(3200,3200,0),steps=2 if pilot else 8)
 if not pilot:
  scenario('second_target',fixture(),at=(2944,3200,0),destination=(3968,3200,0),heading=16384,route=(2,3,-1,4,5),parked_at=(3456,3456,0),steps=8)
  scenario('ramp_entry_exit',fixture(1,0),at=(2944,3200,0),destination=(3968,3200,0),heading=16384,route=(2,2,2,2),parked_at=(3712,3968,0),steps=96)
  # Require entered branches before spending time on the stock-map scenarios.
  # A nominal ramp combined with an impassable level step is not movement proof.
  assert any(s['stored_ramp']!=s['Cell_ramp'] for s in samples),'Ramp scenario never crossed a ramp'
  assert any(any(h>0 for h in s['relative_heights']) for s in samples),'Ramp scenario has no positive relative height'
  assert any(any(h<0 for h in s['relative_heights']) for s in samples),'Ramp scenario has no negative relative height'
  owned,_=shared.prepared.parse(source['commands'][0])
  scenario('stock_crossing',owned,at=(22144,25984,0),destination=(23680,25984,0),heading=16384,route=(2,2,2,2,2,2),parked_at=(23168,25984,0),steps=96)
  scenario('stock_cliff',owned,at=(13184,18560,-500),destination=(0,0,0),heading=49152,route=(),parked_at=(13440,18560,0),steps=2)
 coverage={'lagged_body_current_Cell_draws':sum(s['stored_ramp']!=s['Cell_ramp'] for s in samples),
  'positive_height_draws':sum(any(h>0 for h in s['relative_heights']) for s in samples),
  'negative_height_draws':sum(any(h<0 for h in s['relative_heights']) for s in samples)}
 if not pilot:assert all(coverage.values()) and all(o.movement.retry_loads.values()),coverage
 assert o.shared_calls==draws and o.selected_writes==draws*8 and o.movement.roots==ticks
 return commands,expected,labels,{'draws':draws,'movement_ticks':ticks,'groups':groups,'coverage':coverage,'samples':samples,
  'actual_admission_returns':o.movement.admission_returns,'resident_retry_loads':o.movement.retry_loads,
  'actual_Mark_calls':o.movement.actual_marks,'actual_recalculations':o.movement.actual_recalculations,
  'actual_type_kind_returns':o.movement.type_kind_calls,
  'actual_part_matrices':o.part_calls,'selected_ordered_draw_stores':o.selected_writes,
  'cross_actor_cache_hits':o.cross_actor_hits,'warm_matrix_shortcuts':o.warm_shortcuts,'cold_matrix_builds':o.cold_transforms,
  'audited_roots':o.audit_calls,'audited_map_roots':o.prepared.audit_calls,
  'same_guest_Process_interleaved_draws_Process':True,'initial_records_and_named_services_supplied':True,
  'no_construction_scheduling_or_full_frame_claim':True,'pilot':pilot}
def native_args(a):return [*shared.native_args(a),str(a.exe)]

def main():
 a=shared.arguments(original_cache=True);
 if a.native==ROOT/'build/native/shared-ground-world-vectors':a.native=ROOT/'build/native/owned-unit-world-vectors'
 if a.output==ROOT/'private/unit-draw-1006/shared-ground-world-v1':a.output=ROOT/'private/unit-draw-1006/owned-unit-world-v1'
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 reuse = OriginalResults(a, current, __file__)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());reuse.validate(validate,e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh owned unit world destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a,pilot=a.pilot);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run(native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native owned unit world command '+str(len(proc.stdout.splitlines()))+': '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Owned unit world result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   j=next((j for j,(m,n) in enumerate(zip(x,y)) if m!=n),min(len(x),len(y)))
   raise AssertionError(f'{i} {labels[i]} token {j}: {x[max(0,j-10):j+16]} != {y[max(0,j-10):j+16]}; counts {len(x)}/{len(y)}')
 print('All owned world commands, state snapshots and drawing outputs match native',flush=True)
 prefix='\n'.join(commands[:3])+'\n'
 safety=['','T 0 trailing','S 0','I 0',commands[2],commands[4].replace('D 0','D 2',1)]
 for cmd in safety:
  bad=subprocess.run(native_args(a),input=prefix+cmd+'\n',text=True,capture_output=True)
  if not bad.returncode or not bad.stderr.strip():raise AssertionError('Missing owned world native safety refusal')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Owned unit world run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 reuse.annotate(result)
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);reuse.finish(source,report,validate);print(f'{len(commands):,} owned unit world results / {metadata["draws"]:,} complete draws: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
