#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Original command/Process/finalization/drawing and separate full native previews."""
import json,re,struct,subprocess,time
from collections import Counter
import compare_owned_advance_world as advance
import compare_owned_terrain_runtime as runtime
import compare_owned_orders_world as orders
from original_results import OriginalResults
from compare_original import PATCHED_EXPECTED,write_report
from owned_process_events import original as original_events,native as native_events
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination

INPUTS=ROOT/'private/unit-draw-1006/owned-advance-world-v1/expected.json'
SOURCES=tuple(dict.fromkeys((*advance.SOURCES,*runtime.SOURCES,
 'tests/original_owned_advance_runtime.py','tests/compare_owned_advance_runtime.py',
 'tests/test_owned_advance_runtime_evidence.py','tests/owned_advance_preview_checks.hpp',
 'tests/owned_advance_runtime/CMakeLists.txt')))

# Retain every quoted transitive native header, including platform/renderer roots.
def native_closure(sources):
 result=set(sources);pending=[p for p in result if p.endswith(('.cpp','.hpp','.h'))]
 while pending:
  path=pending.pop()
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name
   child=str(local.relative_to(ROOT)) if local.exists() else 'src/'+name
   if child not in result:result.add(child);pending.append(child)
 return tuple(sorted(result))
SOURCES=native_closure(SOURCES)

def parse(command):
 words=command.split()
 if words and words[0]=='K':return advance.parse(command)
 if words and words[0] in ('H','X'):
  if len(words)!=2:raise ValueError('Malformed admitted runtime step/preview')
  v=int(words[1])
  if not -2147483648<=v<=2147483647 or (words[0]=='X' and v not in (0,1)):raise ValueError('Runtime step/preview outside domain')
  return words[0],v
 op,v=orders.parse(command)
 if op in ('T','F','U'):raise ValueError('Complete admitted runtime H steps required')
 return op,v

def identities(a):
 return {'world':advance.identities(a),'runtime':runtime.identities(a),
  'authored_input_file_sha256':hash_file(INPUTS),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}

def authored_inputs(source,label):
 # Prior outputs are deliberately unavailable to this helper/caller.
 return [c for c,l in zip(source['commands'],source['labels']) if l==label]

def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Runtime engine/profile differs')
 proof=e['evidence']
 if proof.get('identities')!=current:raise ValueError('Runtime identity differs')
 for flag in ('same_schedule_original_Process0_Process1_finish0_finish1','runtime_owned_world_and_tick',
  'independent_original_order_calls_on_actual_actors','genuine_shared_world_Advance_admission','physical_target_membership_measured'):
  if not proof.get(flag):raise ValueError('Admitted runtime proof scope differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Runtime counts differ')
 phase=0;seed=None;last=None;warm=set();after=set();preview=False;continued=False;commands=set();steps=0;roles=set()
 def closed():
  if phase and (not preview or not continued or after!={0,1} or commands!={0,1} or not steps):raise ValueError('Complete warm preview/commands/later Process/drawing required')
 for cmd,result in zip(e['commands'],e['expected']):
  op,v=parse(cmd)
  shape={'events0','events1','state'} if op=='H' else {'state'} if op in ('I','J','K','M','S','B','V','X') else {'tokens'}
  if not isinstance(result,dict) or set(result)!=shape:raise ValueError('Malformed runtime expectation')
  if op=='P':
   closed();phase=1;seed=None;last=100;warm=set();after=set();preview=continued=False;commands=set();steps=0
  elif op=='O':
   if phase!=1:raise ValueError('Prepared map required')
   phase=2
  elif op=='I':
   if phase!=2:raise ValueError('Fresh reset required')
   phase=3
  elif op=='J':
   if phase!=3:raise ValueError('Both actors required')
   phase=4
  elif phase!=4:raise ValueError('Joined runtime required')
  elif op=='K':
   if seed is not None or steps or preview:raise ValueError('Initial curve seed required once')
   seed=v[0]
  elif seed is None:raise ValueError('Explicit admitted curve required')
  elif op=='M':commands.add(v[0])
  elif op=='D':
   warm.add(v[0])
   if preview:after.add(v[0])
  elif op=='X':
   if preview or warm!={0,1} or steps or v!=seed:raise ValueError('Initial warm matching preview required')
   preview=True;roles.add(v)
  elif op=='H':
   if v!=last+1:raise ValueError('Runtime requires consecutive scheduled ticks')
   last=v;steps+=1
   for id in (0,1):
    events=result['events'+str(id)]
    if not events or events[-1][:2]!=['R',id] or sum(x[0]=='R' for x in events)!=1:raise ValueError('Both original terminal Process returns required')
   if preview:continued=True
 closed()
 if roles!={0,1}:raise ValueError('Both admitted runtime actor roles required')

def compare(a,commands,expected,diagnostic):
 p=subprocess.run(advance.native_args(a),input='\n'.join(commands)+'\n',text=True,capture_output=True)
 diagnostic.parent.mkdir(parents=True,exist_ok=True)
 diagnostic.with_suffix('.stdout').write_text(p.stdout);diagnostic.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise RuntimeError(f'Admitted runtime native row {len(p.stdout.splitlines())}: {p.stderr}')
 rows=p.stdout.splitlines()
 if len(rows)!=len(commands):raise AssertionError('Runtime result count differs')
 counts=Counter()
 for i,(cmd,row,result) in enumerate(zip(commands,rows,expected)):
  op,v=parse(cmd);words=row.split();counts[op]+=1
  if 'state' in result:
   at=words.index('actor-state')
   if words[at:]!=result['state']:
    n=next((n for n,(x,y) in enumerate(zip(words[at:],result['state'])) if x!=y),min(len(words)-at,len(result['state'])))
    raise AssertionError(('Runtime state',i,cmd,n,words[at+max(0,n-3):at+n+8],result['state'][max(0,n-3):n+8]))
   if op=='H':
    if words[0]!='phase0':raise AssertionError('Process0 must run first')
    one,end=words.index('phase1'),words.index('finish')
    for id,segment in ((0,words[1:one]),(1,words[one+1:end])):
     events=native_events(segment,id)
     if events!=result['events'+str(id)]:raise AssertionError(('Runtime ordered Process events',i,cmd,id))
     counts['Process_calls']+=1;counts['selected_Process_stores']+=sum(x[0] in ('w','A','L') for x in events);counts['logged_queries']+=sum(x[0]=='Q' for x in events)
    if end+1!=at:raise AssertionError('Unexpected finalization output')
  elif words!=result['tokens']:raise AssertionError(('Runtime drawing/preparation',i,cmd[:100]))
 previews=re.findall(r'Warm full Advance preview actor ([01]): (\d+) isolation checks: PASS\n',p.stderr)
 if len(previews)!=counts['X'] or {int(id) for id,n in previews}!={0,1} or any(int(n)!=18 for id,n in previews):raise AssertionError('Full warm preview evidence missing: '+p.stderr)
 guard=re.search(r'Owned world guards: (\d+); unknown actor: (\d+); warm clone pairs: 0; actual Advance6/7 clone refusals: 0: PASS\n$',p.stderr)
 if not guard or list(map(int,guard.groups()))!=[counts['I']*6,counts['I']]:raise AssertionError('Runtime guards missing: '+p.stderr)
 return {**dict(counts),'warm_full_preview_checks':sum(int(n) for id,n in previews)}

def generate(a,progress):
 from original_owned_advance_runtime import OwnedAdvanceRuntimeOracle
 from original_owned_advance_world import ACTORS,DRIVES
 o=OwnedAdvanceRuntimeOracle(a.exe,a.assets,a.palette.read_bytes());m=o.movement
 source=json.loads(INPUTS.read_text());commands=[];expected=[];labels=[];samples=[];tick=100;label=''
 progress.update(commands=commands,expected=expected,labels=labels)
 def state():return list(map(str,[*o.process_snapshot(),*o.turret_views(tick),*o.command_views()]))
 def record(cmd):
  nonlocal tick
  progress.update(case=label,command=cmd[:100],tick=tick);op,v=parse(cmd)
  if op=='P':result={'tokens':list(map(str,o.prepare_map(v)))}
  elif op=='O':result={'tokens':['reset']}
  elif op=='I':
   head,queue,numeric,crusher,parked,h,first,second,order,turrets=v
   o.initialize(head,queue,numeric,parked,h,turrets);m.put(0x1c01000+0x13d0,8);result={'state':state()}
  elif op=='J':
   m.u.mem_write(DRIVES[1]+0x34,struct.pack('<3i',*v[:3]));m.u.mem_write(ACTORS[1]+0x4d0,struct.pack('<24i',*v[3:27]));m.u.mem_write(ACTORS[1]+0x530,struct.pack('<3i',*v[27:]));result={'state':state()}
  elif op=='K':
   id,*s=v;d=DRIVES[id];m.u.mem_write(d+0x40,struct.pack('<3i',*s[:3]));m.put(d+0x58,s[3]);m.put(d+0x5c,s[4]);m.put(d+0x4c,s[5]);m.put(d+0x63,s[6],'B');result={'state':state()}
  elif op=='H':
   tick=v;events=[original_events(m.advance_actor(id,tick)) for id in (0,1)]
   for id in (0,1):o.finish_tick(id,tick)
   result={'events0':events[0],'events1':events[1],'state':state()}
  elif op=='X':result={'state':state()}
  elif op=='D':
   id,*values=v;before=len(o.relative_heights);draw=o.draw_shared(id,tick,values)
   samples.append({'case':label,'actor':id,'tick':tick,'relative_heights':o.relative_heights[before:]})
   result={'tokens':list(map(str,[*draw,*o.process_snapshot(),*o.turret_views(tick),*o.command_views()]))}
  else:
   id,tick=v[:2]
   if op=='M':o.order(id,tick,v[2:5],v[6:])
   elif op=='S':o.stop_order(id,tick)
   elif op=='B':o.turn_body(id,tick,v[2])
   elif op=='V':o.command_turret(id,tick,v[2])
   else:raise ValueError('Unexpected admitted runtime command')
   result={'state':state()}
  commands.append(cmd);expected.append(result);labels.append(label)
 scenarios=[(id,ramp) for ramp in (0,1) for id in (0,1)]
 if a.pilot:scenarios=scenarios[:2]
 for mover,ramp in scenarios:
  label=f'actor{mover}_ramp{ramp}_residentY3392_heading57344_Advance7';tick=100
  rows=authored_inputs(source,label)
  for op in ('P','O','I','J','K'):record(next(c for c in rows if c.startswith(op+' ')))
  for id in (0,1):
   target=struct.unpack('<3i',o.u.mem_read(DRIVES[id]+0x34,12));route=list(struct.unpack('<24i',o.u.mem_read(ACTORS[id]+0x4d0,96)));route=route[:route.index(-1)]
   record('M '+' '.join(map(str,[id,100,*target,len(route),*route])))
  draws=[next(c for c in rows if c.startswith(f'D {id} ')) for id in (0,1)]
  def draw():
   for id in (0,1,0):record(draws[id])
  draw();record(f'X {mover}');draw();start=len(m.advance_targets)
  for at in range(101,165):
   if at==102:record(f'B {mover} {at} 8192')
   if at==113:record(f'S {1-mover} {at}')
   if at==114:record(f'V {mover} {at} -32768')
   if at==150:
    for id in (0,1):
     where=DRIVES[id]+0x40 if m.get(DRIVES[id]+0x63,'B') else ACTORS[id]+0x88
     x,y,z=struct.unpack('<3i',o.u.mem_read(where,12));record(f'M {id} {at} {x+256} {y} 0 1 2')
   record(f'H {at}')
   if at in (101,116,150,164):draw()
   if at%16==4:print(label,'tick',at,flush=True)
  measured=m.advance_targets[start:];assert measured and any(r['actor']==mover and r['result']==7 for r in measured),(label,measured)
  print(label,'complete',dict(m.process_counts),o.shared_calls,'draws',flush=True)
 for row in m.advance_targets:
  if row['result']==7:
   assert not row['fallback'] and 1-row['actor'] in row['members'],row
   assert all([(abs(p[0])//256)*(1 if p[0]>=0 else -1),(abs(p[1])//256)*(1 if p[1]>=0 else -1)]==list(row['target']) for p in row['member_locations']),row
 for id in (0,1):assert m.default_stores[id]==m.default_continuations[id]>0 and o.order_counts[(id,'applied-deferred-body')]>0
 assert dict(m.root_entries)==dict(m.process_counts)
 return commands,expected,labels,{'same_schedule_original_Process0_Process1_finish0_finish1':True,'runtime_owned_world_and_tick':True,
  'independent_original_order_calls_on_actual_actors':True,'genuine_shared_world_Advance_admission':True,'physical_target_membership_measured':True,
  'native_full_preview_policy_separate_from_original_evidence':True,'draws':o.shared_calls,'selected_draw_stores':o.selected_writes,
  'process_counts':dict(m.process_counts),'actual_Process_entries':dict(m.root_entries),'actual_Advance_targets':m.advance_targets,
  'actual_default_continuations':dict(m.default_continuations),'actual_default_index_stores':dict(m.default_stores),
  'order_counts':[[id,k,n] for (id,k),n in sorted(o.order_counts.items())],'draw_samples':samples,
  'actual_Mark_calls':m.actual_marks,'actual_recalculations':m.actual_recalculations,
  'initial_curves_routes_commands_finalization_scheduling_and_services_supplied':True,'pilot':a.pilot}

def main():
    args = advance.owned.shared.arguments(original_cache=True)
    if args.native == ROOT/'build/native/shared-ground-world-vectors':
        args.native = ROOT/'build/owned-advance-runtime/owned-advance-runtime-vectors'
    if args.output == ROOT/'private/unit-draw-1006/shared-ground-world-v1':
        args.output = ROOT/'private/unit-draw-1006/owned-advance-runtime-v1'
    start = time.monotonic(); current = identities(args); runner = hash_file(args.native)
    reuse = OriginalResults(args, current, __file__)
    if args.expectations:
        source = private_path(args.expectations, args.exe); receipt = source.parent/'report.json'
        fingerprint = hash_file(source); envelope = json.loads(source.read_text())
        reuse.validate(validate, envelope, json.loads(receipt.read_text()), fingerprint, current)
        commands, expected, labels = [envelope[k] for k in ('commands','expected','labels')]
        metadata = envelope['evidence']; generation = 0
        report = private_path(args.report, args.exe); check_replay_destination(report, source, receipt)
    else:
        folder = private_path(args.output, args.exe)
        if args.report or (folder/'expected.json').exists() or (folder/'report.json').exists():
            raise ValueError('Fresh orders destination invalid or exists')
        now = time.monotonic(); progress = {}
        try: commands, expected, labels, metadata = generate(args, progress)
        except BaseException as error:
            folder.mkdir(parents=True, exist_ok=True)
            write_report(args.exe, folder/'partial-diagnostic.json', {**progress, 'accepted_proof': False, 'error': repr(error), 'identities': current})
            raise
        generation = time.monotonic()-now; report = folder/'report.json'
        write_report(args.exe, folder/'original-diagnostic.json', {'commands':commands,'expected':expected,'labels':labels,'metadata':metadata,'accepted_proof':False,'identities':current})
    now = time.monotonic(); checks = compare(args, commands, expected, report.with_name(report.stem+'-native'))
    comparison = time.monotonic()-now
    if identities(args) != current or hash_file(args.native) != runner:
        raise ValueError('Orders sources/inputs/runner changed during invocation')
    result = {**metadata, 'identities':current,'native_sha256':runner,'cases':len(commands),
              'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006', 'native_checks':checks,
              'evidence_mode':'cached-original-replay' if args.expectations else 'fresh-original',
              'original_instructions_executed':not bool(args.expectations),'original_instructions_modified':False,
              'original_generation_seconds':generation,'native_comparison_seconds':comparison,'elapsed_seconds':time.monotonic()-start}
    reuse.annotate(result)
    if not args.expectations:
        source = folder/'expected.json'
        write_report(args.exe, source, {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                    'commands':commands,'expected':expected,'labels':labels,'evidence':result})
        fingerprint = hash_file(source)
    result['expectations_sha256'] = fingerprint; write_report(args.exe, report, result)
    reuse.finish(source, report, validate)
    print(f'{len(commands)} scheduled world results / {metadata["draws"]} complete draws: PASS')


if __name__ == '__main__': main()
