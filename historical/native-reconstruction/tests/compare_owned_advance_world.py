#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Opt-in Advance0/2/7 on two genuine actors, mutable membership and complete draws."""
import json,re,struct,subprocess,time
from collections import Counter
import pefile
import compare_owned_command_world as command_world
import compare_owned_unit_processes as processes
import compare_owned_unit_world as owned
from original_results import OriginalResults
from compare_original import PATCHED_EXPECTED,write_report
from owned_process_events import original as original_events,native as native_events
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_process_advance_admission import verify as inspect_advance

SOURCES=tuple(dict.fromkeys((*command_world.SOURCES,'tests/original_owned_advance_world.py',
 'tests/compare_owned_advance_world.py','tests/test_owned_advance_world_evidence.py',
 'tests/owned_advance_world/CMakeLists.txt','tools/verify_process_advance_admission.py',
 'tools/verify_advance_admission.py','tests/owned_advance_checks.hpp','tests/owned_world_snapshot.hpp')))

# Complete quoted-header closure for every retained native fixture/library source.
SOURCES=tuple(dict.fromkeys((*SOURCES,
 'src/assets/ArchiveSequence.hpp',
 'src/assets/BorrowedPreparedUnitAdmission.hpp',
 'src/assets/AdvanceCellScatterWorld.hpp',
 'src/assets/AdvanceNearbyScatterWorld.hpp',
 'src/assets/AdvanceTerminalScatterWorld.hpp',
 'src/assets/AdvanceTerminalWorld.hpp',
 'src/assets/BorrowedCellUnitScatterWorld.hpp',
 'src/assets/CellNearbyScatterWorld.hpp',
 'src/assets/CellUnitScatterWorld.hpp',
 'src/assets/NearbyCellAdmission.hpp',
 'src/assets/NearbyLocationMap.hpp',
 'src/assets/OwnedUnitScatter.hpp',
 'src/assets/ProcessTerminalScatterWorld.hpp',
 'src/assets/ScatterProjection.hpp',
 'src/assets/UnitNearbyScatterWorld.hpp',
 'src/assets/UnitScatterWorld.hpp',
 'src/assets/UnitDrawMetadata.hpp',
 'src/sim/BorrowedUnitAdmission.hpp',
 'src/sim/MembershipPolicy.hpp',
 'src/sim/UnitDestination.hpp',
 'src/sim/FootDestination.hpp',
 'src/sim/CellScatter.hpp',
 'src/sim/CellClosestResident.hpp',
 'src/sim/FootCoordinates.hpp',
 'src/sim/FootLayer.hpp',
 'src/sim/GroundDriveIdleTarget.hpp',
 'src/sim/GroundDriveTerminal.hpp',
 'src/sim/NearbyLocation.hpp',
 'src/sim/NearbyLocationPolicy.hpp',
 'src/sim/OriginalRandomRange.hpp',
 'src/sim/UnitCellDestination.hpp',
 'src/sim/UnitScatter.hpp',
 'src/platform/OwnedUnitOrders.hpp',
 'src/platform/OwnedUnitSchedule.hpp',
 'src/render/CachedVoxelShadow.hpp',
 'src/render/FootLitDraw.hpp',
 'src/render/FootVoxelStaging.hpp',
 'src/render/PlayerColor.hpp',
 'src/render/PreparedUnitDepth.hpp',
 'src/render/ShadowCache.hpp',
 'src/render/ShadowVoxelWorld.hpp',
 'src/render/UnitLighting.hpp',
 'src/render/UnitStaging.hpp',
 'src/render/UnitSurfaceDraw.hpp',
 'src/render/UnitSurfaceSplit.hpp',
 'src/render/UnitTypeVisibility.hpp',
 'src/render/UnitVoxelDraw.hpp',
 'src/render/UnitVoxelShadowWorld.hpp',
 'src/render/UnitVoxelStaging.hpp',
 'src/render/UnitVoxelWorld.hpp',
 'src/render/VoxelCache.hpp',
 'src/render/VoxelPartDraw.hpp',
 'src/render/VoxelPartStaging.hpp',
 'src/render/VoxelShadow.hpp',
 'src/render/VoxelSnapshot.hpp',
)))

def parse(command):
 words=command.split()
 if words and words[0]=='X':
  if len(words)!=3:raise ValueError('Malformed owned Advance preview')
  id,tick=map(int,words[1:])
  if id not in (0,1) or not -2147483648<=tick<=2147483647:raise ValueError('Owned Advance preview outside domain')
  return 'X',(id,tick)
 if words and words[0]=='K':
  if len(words)!=9:raise ValueError('Malformed owned Advance seed')
  v=list(map(int,words[1:]))
  if not(all(-2147483648<=n<=2147483647 for n in v) and v[0] in (0,1) and 0<=v[4]<64 and 0<=v[5]<128 and v[7] in (0,1)):
   raise ValueError('Owned Advance seed outside domain')
  return 'K',v
 return processes.parse(command)

def identities(a):
 return {'world':command_world.identities(a),'Advance':inspect_advance(a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES}}

def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Owned Advance engine/profile differs')
 proof=e['evidence']
 if proof.get('identities')!=current:raise ValueError('Owned Advance identity differs')
 for flag in ('genuine_shared_world_Advance_admission','physical_target_membership_measured','distinct_original_Process_records_shared_owned_world'):
  if not proof.get(flag):raise ValueError('Owned Advance scope differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Owned Advance counts differ')
 stage='none';seeded=False;pending=None;paired=False;drawn=False;warm=False;previewed=False
 for cmd,result in zip(e['commands'],e['expected']):
  try:op,v=parse(cmd)
  except (ValueError,AssertionError,TypeError,OverflowError,struct.error):raise ValueError('Malformed owned Advance command') from None
  if op=='P':
   if pending is not None:raise ValueError('Incomplete Process pair')
   if stage!='none' and not(paired and drawn):raise ValueError('Process/drawing join required')
   stage='prepared';seeded=paired=drawn=warm=previewed=False
  elif op=='O':
   if stage!='prepared':raise ValueError('Fresh preparation required')
   stage='reset'
  elif op=='I':
   if stage!='reset':raise ValueError('Fresh reset required')
   stage='initialized'
  elif op=='J':
   if stage!='initialized':raise ValueError('Both original actors required')
   stage='joined'
  elif op=='K':
   if stage!='joined' or seeded or paired or pending is not None:raise ValueError('Initial Drive seed required once')
   seeded=True
  elif op=='T':
   if stage!='joined' or not seeded:raise ValueError('Explicit owned Advance seed required')
   id,tick=v
   if id==0:
    if pending is not None:raise ValueError('Process1 must follow Process0')
    pending=tick
   else:
    if pending!=tick:raise ValueError('Paired Process tick differs')
    pending=None;paired=True
  elif op=='D':
   if stage!='joined' or not seeded or pending is not None:raise ValueError('Complete owned records required before drawing')
   if paired:drawn=True
   warm=True
  elif op=='X':
   if stage!='joined' or not seeded or not warm or paired or pending is not None or previewed:raise ValueError('Initial warm discarded preview required')
   previewed=True
  required={'events','state'} if op=='T' else {'state'} if op in ('I','J','K','X') else {'tokens'}
  if not isinstance(result,dict) or set(result)!=required:raise ValueError('Malformed owned Advance expectation')
 if pending is not None or not(paired and drawn):raise ValueError('Complete Process/drawing join required')

def native_args(a):return [*command_world.native_args(a),'--advance-admission']

def compare(a,commands,expected,diagnostic):
 proc=subprocess.run(native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True)
 diagnostic.parent.mkdir(parents=True,exist_ok=True)
 diagnostic.with_suffix('.stdout').write_text(proc.stdout);diagnostic.with_suffix('.stderr').write_text(proc.stderr)
 if proc.returncode:raise RuntimeError(f'Owned Advance native command {len(proc.stdout.splitlines())}: {proc.stderr.strip()}')
 lines=proc.stdout.splitlines()
 if len(lines)!=len(commands):raise AssertionError('Owned Advance result counts differ')
 counts=Counter()
 for i,(cmd,line,result) in enumerate(zip(commands,lines,expected)):
  op,v=parse(cmd);words=line.split();counts[op]+=1
  if 'state' in result:
   at=words.index('actor-state')
   if words[at:]!=result['state']:
    n=next((n for n,(x,y) in enumerate(zip(words[at:],result['state'])) if x!=y),min(len(words)-at,len(result['state'])))
    raise AssertionError(('Owned Advance state',i,cmd,n,words[at+max(0,n-4):at+n+10],result['state'][max(0,n-4):n+10]))
   if op=='T':
    events=native_events(words[:at],v[0])
    if events!=result['events']:
     n=next((n for n,(x,y) in enumerate(zip(events,result['events'])) if x!=y),min(len(events),len(result['events'])))
     raise AssertionError(('Owned Advance ordered events',i,cmd,n,events[max(0,n-3):n+6],result['events'][max(0,n-3):n+6]))
    if not events or events[-1][0]!='R' or sum(x[0]=='R' for x in events)!=1:raise AssertionError('Actual Process return required')
    counts['selected_Process_stores']+=sum(x[0] in ('w','A','L') for x in events)
    counts['logged_queries']+=sum(x[0]=='Q' for x in events)
  elif words!=result['tokens']:raise AssertionError(('Owned Advance complete drawing/preparation',i,cmd[:100]))
 guard=re.fullmatch(r'Owned world guards: (\d+); unknown actor: (\d+); warm clone pairs: (\d+); actual Advance6/7 clone refusals: (\d+); Advance preview checks: (\d+): PASS\n',proc.stderr)
 if guard is None:raise AssertionError('Owned Advance guard evidence missing: '+proc.stderr)
 guards,unknown,clones,refusals,previews=map(int,guard.groups())
 if guards!=counts['I']*7 or unknown!=counts['I'] or clones!=counts['I'] or refusals or previews!=counts['X']*6:raise AssertionError('Owned Advance guards not entered')
 return {**dict(counts),'constructor_refusals':guards,'unknown_actor_refusals':unknown,'warm_clone_pairs':clones,'warm_discarded_preview_checks':previews}

def track_seed(exe):
 p=pefile.PE(str(exe));stream,_,_,_,flags=struct.unpack('<BBHii',p.get_data(0x7a0180+19*12-0x400000,12))
 address,jump,_,_=struct.unpack('<4i',p.get_data(0x7a00a0+16*stream-0x400000,16))
 x,y,angle=struct.unpack('<3i',p.get_data(address+(jump-1)*12-0x400000,12))
 if flags&1:x,y,angle=y,x,(-64-angle)&255
 if flags&2:x,angle=-x,-angle&255
 if flags&4:y,angle=-y,(-128-angle)&255
 return (3200+x,3200+y,0),angle<<8,jump

def generate(a,progress):
 from original_owned_advance_world import OwnedAdvanceWorldOracle,ACTORS,DRIVES
 o=OwnedAdvanceWorldOracle(a.exe,a.assets,a.palette.read_bytes());m=o.movement
 source=json.loads(a.depth_fixture.read_text());template,_=owned.shared.prepared.parse(source['commands'][3])
 common=list(template[5]);common[:5]=[12,12,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 at,heading,jump=track_seed(a.exe);commands=[];expected=[];labels=[];samples=[]
 progress.update(commands=commands,expected=expected,labels=labels,stage='original_setup')
 scenarios=[(id,0,3392,57344,7) for id in (0,1)]+[(id,1,3392,57344,7) for id in (0,1)]+[(1,0,3328,57344,0)]+[(id,0,3392,49152,2) for id in (0,1)]
 if a.pilot:scenarios=scenarios[:2]
 def record(cmd,result,label):
  parse(cmd);commands.append(cmd);expected.append(result);labels.append(label)
 draws=0;cases=[]
 for mover,ramp,y,other_heading,required in scenarios:
  label=f'actor{mover}_ramp{ramp}_residentY{y}_heading{other_heading}_Advance{required}'
  progress.update(stage='original_scenario',case=label)
  types=[[1,1,1,60,30,1,0,0,0,0,0],[1,1,1,60,30,1,0,ramp,0,0,0]]
  cells=[[x,y,int(x==12),0,0,0,-1,0,0,0,0,0,17,91,-1,41,0] for y in range(25) for x in range(25) if x+y>12 and abs(x-y)<12 and x+y<=36]
  fixture=(*template[:5],common,[12,0,0,12,12],types,cells,[],[],template[11],[])
  record('P '+owned.shared.floor.command(*fixture[:5],fixture[5:]),{'tokens':list(map(str,o.prepare_map(fixture)))},label)
  record('O 0 0',{'tokens':['reset']},label)
  positions=[at,(3264,y,0)];headings=[heading,other_heading];routes=[(4,4,-1,7,6),(7,7,-1,5,6)];destinations=[(3200,3712,0),(2944,2944,0)]
  if mover:positions.reverse();headings.reverse();routes.reverse();destinations.reverse()
  cmd=owned.resident.command(at=positions[0],destination=destinations[0],heading=headings[0],route=routes[0],parked_at=positions[1],parked_heading=headings[1],steps=1,mode=0,marked=0,effect=1,present=1,key=0)
  _,v=owned.resident.parse(cmd);head,queue,numeric,crusher,parked,h,first,second,order=v
  o.initialize(head,queue,numeric,parked,h,[8192,40960]);m.put(0x1c01000+0x13d0,8)
  record('I '+cmd[2:]+' 8192 40960',{'state':list(map(str,o.process_snapshot()))},label)
  queue1=[*routes[1],*([-1]*(24-len(routes[1])))];j=[*destinations[1],*queue1,-1,-17,0]
  m.u.mem_write(DRIVES[1]+0x34,struct.pack('<3i',*j[:3]));m.u.mem_write(ACTORS[1]+0x4d0,struct.pack('<24i',*queue1));m.u.mem_write(ACTORS[1]+0x530,struct.pack('<3i',*j[27:]))
  record('J '+' '.join(map(str,j)),{'state':list(map(str,o.process_snapshot()))},label)
  seed=[mover,3200,3200,0,19,jump,7,1];drive=DRIVES[mover]
  m.u.mem_write(drive+0x40,struct.pack('<3i',*seed[1:4]));m.put(drive+0x58,seed[4]);m.put(drive+0x5c,seed[5]);m.put(drive+0x4c,seed[6]);m.put(drive+0x63,seed[7],'B')
  record('K '+' '.join(map(str,seed)),{'state':list(map(str,o.process_snapshot()))},label)
  def draw(tick):
   nonlocal draws
   for id in (0,1,0):
    v=[owned.shared.floor.bits(.125),0,0,0,1,0,7,1,0,1312,1,0,0,80+id*5,72,0,0,160,144]
    before=len(o.relative_heights);result=o.draw_shared(id,tick,v);draws+=1
    samples.append({'case':label,'actor':id,'tick':tick,'relative_heights':o.relative_heights[before:]})
    record('D '+' '.join(map(str,[id,*v])),{'tokens':list(map(str,[*result,*o.process_snapshot()]))},label)
  start=len(m.advance_targets);draw(100)
  if required==7:record(f'X {mover} 100',{'state':list(map(str,o.process_snapshot()))},label)
  for tick in range(100,124):
   for id in (0,1):
    progress.update(tick=tick,actor=id);events=m.advance_actor(id,tick)
    record(f'T {id} {tick}',{'events':original_events(events),'state':list(map(str,o.process_snapshot()))},label)
   if tick in (100,101,107,116,123):draw(tick)
   if tick%8==3:print(label,'tick',tick,flush=True)
  measured=m.advance_targets[start:]
  selected=[row for row in measured if row['actor']==mover]
  assert selected and selected[0]['result']==required,(label,measured)
  row=selected[0]
  if required in (2,7):
   assert not row['fallback'] and (1-mover) in row['members'],row
   for id,location in zip(row['members'],row['member_locations']):
    assert [int(location[0]/256),int(location[1]/256)]==list(row['target']),(label,id,row)
  else:assert not row['members'],row
  cases.append({'case':label,'mover':mover,'required_result':required,'actual_Advance_targets':measured})
  print(label,'complete',dict(m.process_counts),draws,'draws',flush=True)
 assert dict(m.root_entries)==dict(m.process_counts)
 for row in m.advance_targets:
  if row['result']==7:
   assert not row['fallback'] and 1-row['actor'] in row['members'],row
   for location in row['member_locations']:
    divided=[(abs(n)//256)*(-1 if n<0 else 1) for n in location[:2]]
    assert divided==list(row['target']),row
 assert all(m.default_continuations[id] and m.default_continuations[id]==m.default_stores[id] for id in (0,1))
 assert o.shared_calls==draws and o.selected_writes==draws*8
 return commands,expected,labels,{'process_counts':dict(m.process_counts),'actual_Process_entries':dict(m.root_entries),
  'actual_Advance_targets':m.advance_targets,'actual_default_continuations':dict(m.default_continuations),'actual_default_index_stores':dict(m.default_stores),
  'actual_result7_callers':[[id,hex(caller),n] for (id,caller),n in sorted(m.result7_callers.items())],
  'actual_admissions':[[id,hex(caller),result,n] for (id,caller,result),n in sorted(m.admissions.items())],
  'actual_bearings':m.bearings,'actual_distances':m.distances,'scenario_checks':cases,'draw_samples':samples,
  'actual_Mark_calls':m.actual_marks,'actual_recalculations':m.actual_recalculations,'draws':draws,'actual_shared_draw_entries':o.shared_calls,
  'selected_draw_stores':o.selected_writes,'genuine_shared_world_Advance_admission':True,'physical_target_membership_measured':True,
  'distinct_original_Process_records_shared_owned_world':True,'selected_stores_and_all_logged_queries_compared':True,
  'all_machine_stores_compared':False,'initial_records_padding_schedules_named_services_supplied':True,'runtime_unwired':True,'pilot':a.pilot}

def main():
 a=owned.shared.arguments(original_cache=True)
 if a.native==ROOT/'build/native/shared-ground-world-vectors':a.native=ROOT/'build/owned-advance-world/owned-advance-world-vectors'
 if a.output==ROOT/'private/unit-draw-1006/shared-ground-world-v1':a.output=ROOT/'private/unit-draw-1006/owned-advance-world-v1'
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 reuse = OriginalResults(a, current, __file__)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());reuse.validate(validate,e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh owned Advance output exists or is invalid')
  progress={};now=time.monotonic()
  try:commands,expected,labels,metadata=generate(a,progress)
  except BaseException as error:
   dest.mkdir(parents=True,exist_ok=True)
   with (dest/'partial-diagnostic.json').open('x') as f:json.dump({**progress,'error':type(error).__name__+': '+str(error),'accepted_proof':False},f,indent=2)
   raise
  generation=time.monotonic()-now;report=dest/'report.json';dest.mkdir(parents=True,exist_ok=True)
  with (dest/'original-diagnostic.json').open('x') as f:json.dump({'commands':commands,'expected':expected,'labels':labels,'metadata':metadata,'accepted_proof':False},f,indent=2)
 now=time.monotonic();counts=compare(a,commands,expected,report.with_name(report.stem+'-native'));elapsed=time.monotonic()-now
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Owned Advance run changed')
 result={**metadata,**counts,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'original_generation_seconds':generation,'native_comparison_seconds':elapsed,'elapsed_seconds':time.monotonic()-start}
 reuse.annotate(result)
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);reuse.finish(source,report,validate)
 print(f'{len(commands)} owned Advance world results / {sum(metadata["process_counts"].values())} original Process calls / {metadata["draws"]} complete draws: PASS ({result["evidence_mode"]})')
if __name__=='__main__':main()
