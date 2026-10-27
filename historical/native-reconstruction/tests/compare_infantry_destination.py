#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete bounded Infantry/Foot destination roots through actual Walk commands."""
import argparse,copy,itertools,json,re,struct,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_infantry_destination import verify
NATIVE=('tests/infantry_destination_vectors.cpp','src/sim/WalkCommands.cpp','src/sim/UnitDiscovery.cpp')
ORIGINAL=('tests/compare_infantry_destination.py','tests/original_infantry_destination.py','tools/verify_infantry_destination.py',
 'tests/original_walk_commands.py','tools/verify_walk_commands.py','tests/original_presentation.py',
 'tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
SCALARS='mission queued session human human2 state flag jump c0d c00 field initial suspended reached refs globalrefs moving processing really reset frozen disabled disabled2 tick delay mask flags'.split()
ARRAYS=dict(destination=3,head=3,points=6,route=24,retry=3,wait=3)
FLAGS=dict(complete_Infantry_and_Foot_roots=True,actual_Walk_commands=True,actual_House_mission_QI_class_references=True,
 shared_Foot_kernel_with_Unit=True,late_target_and_two_clock_reads=True,selected_ordered_stores=True,
 initial_records_coordinates_map_animation_and_scratch_supplied=True,moving_parent_nonnull_retarget_supported=False,
 JumpJet_and_transport_supported=False,complete_Process_join=False,production_world_join=False,runtime_enabled=False)
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_infantry_destination.py','tests/compare_unit_destination_current.py','tools/run_evidence.py','CMakeLists.txt')
def require(ok):
 if not ok:raise ValueError('Infantry destination evidence/input differs')
def dbits(x):return struct.unpack('<Q',struct.pack('<d',x))[0]
def defaults():return dict(mission=2,queued=2,session=0,human=1,human2=0,state=0,flag=0,jump=0,c0d=0,c00=0,field=391,initial=0,
 suspended=0,reached=173,refs=3,globalrefs=7,moving=0,processing=197,really=255,reset=128,frozen=0,disabled=0,disabled2=0,
 tick=100,delay=8,mask=0,flags=0,destination=[17,23,31],head=[0,0,0],points=[[896,-1152,7],[1408,1664,-31]],
 route=[3,5,-1,*range(21)],retry=[-1,-91,17],wait=[123,99,-31],scale=dbits(1.),actions=[[1,1,1,23]])
def command(**kw):
 c=defaults();c.update(kw);values=[c[k] for k in SCALARS]
 for k in ARRAYS:values.extend(itertools.chain.from_iterable(c[k]) if k=='points' else c[k])
 values+=[c['scale'],len(c['actions'])];values.extend(itertools.chain.from_iterable(c['actions']))
 return 'F '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='F');v=list(map(int,t[1:]));at=len(SCALARS);require(len(v)>=at+sum(ARRAYS.values())+2)
 c=dict(zip(SCALARS,v))
 for k,n in ARRAYS.items():c[k]=v[at:at+n];at+=n
 c['points']=[c['points'][:3],c['points'][3:]];c['scale'],count=v[at:at+2];at+=2
 require(1<=count<=32 and len(v)==at+4*count);c['actions']=[v[i:i+4] for i in range(at,len(v),4)]
 require(all(-2**31<=n<=0xffffffff for k,n in c.items() if k in SCALARS))
 for k in ('human','human2','flag','jump','c0d','c00','suspended','reached','moving','processing','really','reset','disabled','disabled2'):require(0<=c[k]<=255)
 require(c['jump']==0 and 0<c['refs']<0x7fffffff and 0<=c['globalrefs']<=0xffffffff and c['initial'] in (0,1,2) and 0<=c['mask']<=63)
 require(all(-2**31<=n<2**31 for k in ('destination','head','route','retry','wait') for n in c[k]))
 require(all(-2**31<=n<2**31 for row in c['points'] for n in row) and 0<=c['scale']<=0xffffffffffffffff)
 for mode,target,flag,padding in c['actions']:require(mode in (0,1) and target in (0,1,2) and 0<=flag<=255 and -2**31<=padding<2**31)
 return c
def scenarios():
 for mode,target,suspended,initial,flag in itertools.product((0,1),(0,1,2),(0,173),(0,1,2),(0,255)):
  yield 'complete_roots_target_null_suspended_flag',command(initial=initial,suspended=suspended,actions=[[mode,target,flag,-91]])
 for session,human,human2,state in itertools.product((0,1,-1),(0,1,128),(0,255),(0,26,27,28,29,30,31)):
  yield 'actual_House_raw_mode_and_Infantry_state_early_return',command(session=session,human=human,human2=human2,state=state)
 for initial,flag,c0d,c00 in itertools.product((0,1,2),(0,128),(0,255),(0,173)):
  yield 'same_target_animation_and_repeated_House',command(initial=initial,flag=flag,c0d=c0d,c00=c00,mask=32)
 for frozen,disabled,disabled2 in itertools.product((-2147483648,0,1,2147483647),(0,255),(0,128)):
  yield 'actual_Walk_live_guards_after_target_store',command(frozen=frozen,disabled=disabled,disabled2=disabled2)
 for head,moving in itertools.product(([0,0,0],[0,0,1],[7,9,11]),(0,1,173,255)):
  yield 'null_parent_Stop_retains_committed_head_and_raw_bytes',command(head=head,moving=moving,actions=[[1,0,255,17],[1,0,0,-31]])
 for mask,suspended in itertools.product(range(64),(0,128)):
  yield 'late_target_suspend_coordinate_timer_and_named_mutations',command(mask=mask,suspended=suspended,actions=[[0,1,0,-91],[0,2,1,17],[0,0,255,23]])
 for tick,delay,globalrefs in itertools.product((-2147483648,-1,0,2147483647),(-2147483648,0,2147483647),(0,0xffffffff)):
  yield 'wrapped_clock_reference_and_signed_delay',command(tick=tick,delay=delay,globalrefs=globalrefs,mask=12)
 for flags,scale,z in itertools.product((0,256,0x80000100),(0.,1.,-1.,4294967296.,float('nan')),(-2147483648,2147483647)):
  yield 'Walk_bridge_late_Z_after_Foot_coordinate_copy',command(flags=flags,scale=dbits(scale),points=[[1,-31,z],[3,4,0]],mask=16)
 for mission in (-1,0,1,2,5,16,31):
  yield 'actual_mission_getter_nontransport_and_empty_coordinate',command(mission=mission,points=[[0,0,0],[1,2,3]])
def identities(a):return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 pairs=list(scenarios());require(list(zip(e['labels'],e['commands']))==pairs and len(e['expected'])==len(pairs))
 require(e['evidence']['audited_original_calls']==sum(len(parse(c)['actions']) for _,c in pairs))
 for cmd,row in zip(e['commands'],e['expected']):require(isinstance(row,list) and all(isinstance(x,str) for x in row) and row.count('Z')==1 and row.count('R')==len(parse(cmd)['actions']))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_infantry_destination import InfantryDestinationOracle
  o=InfantryDestinationOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run(parse(cmd))
   except BaseException:print('Failed Infantry destination scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.counts),writes=dict(o.writes),distinct_instructions=len(o.instructions))
  require(all(o.counts.get(hex(k),0)>0 for k in (0x501ce0,0x4c8030,0x4f52f0,0x71fab0,0x71f900,0x53d250,0x53d270,0x71e020,0x71e110,0x594770,0x509800)))
  require(current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,
   original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=origin))
  fingerprint=hash_file(source);write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
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
 write_report(a.exe,report,result);print(len(commands),'Infantry destination sequences PASS;',meta['audited_original_calls'],'complete original roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
