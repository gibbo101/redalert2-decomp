#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete waypoint reveal orchestration exact-original comparison."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_scenario_waypoint import verify
NATIVE=('CMakeLists.txt','src/sim/MissionWaypointReveal.hpp','src/sim/ScenarioWaypoint.hpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp','tests/mission_waypoint_lookup_vectors.cpp')
ORIGINAL=('tests/original_mission_waypoint_lookup.py','tools/verify_scenario_waypoint.py','tests/compare_mission_waypoint_lookup.py')
FLAGS=dict(complete_6B0670_waypoint_reveal=True,complete_663180_with_aliasing=True,repeated_Cell_queries_and_signed_height=True,live_globals_reloaded_for_second_reveal=True,actual_scenario_waypoint_getter=True,map_reveal_children_supplied=True,production_action_association=False)
def require(ok):
 if not ok:raise ValueError('Mission waypoint reveal evidence/input differs')
def command(disabled=0,waypoint=6,x=71,y=92,flags=(0,0,0),levels=(11,13,2),scale=104,range=5,mutation=0):
 return 'W '+' '.join(map(str,(disabled,waypoint,x,y,*flags,*levels,scale,range,mutation)))
def parse(cmd):
 t=cmd.split()
 if t and t[0]=='G':
  require(len(t)==3);index,out=map(int,t[1:]);require(-2**31<=index<2**31 and 0<=out<=0xffc and ((0x632+index*4)&0xffffffff)+4<=0x1000);return dict(getter=True,waypoint=index,out=out)
 require(len(t)==14 and t[0]=='W');v=list(map(int,t[1:]));disabled,waypoint,x,y=v[:4];flags=v[4:7];levels=v[7:10];scale,distance,mutation=v[10:]
 require(0<=disabled<=255 and all(-2**31<=n<2**31 for n in (waypoint,scale,distance)) and all(-32768<=n<=32767 for n in (x,y)) and all(0<=n<2**32 for n in flags) and all(-128<=n<=127 for n in levels) and mutation in (0,1,2))
 require(((0x632+waypoint*4)&0xffffffff)+4<=0x1000)
 return dict(disabled=disabled,waypoint=waypoint,x=x,y=y,flags=flags,levels=levels,scale=scale,range=distance,mutation=mutation)
def scenarios():
 for index in (-396,-1,0,6,255,0x3fffffff,0x40000000,-2147483648):
  offset=(0x632+index*4)&0xffffffff
  for out in (offset,max(0,offset-1),offset+1,offset+3,0xffc):
   yield 'complete_getter_return_and_overlapping_output',f'G {index} {out}'
 for waypoint in (-396,-1,0,6,255,0x40000000,-2147483648):
  yield 'wrapping_index_actual_waypoint_child',command(waypoint=waypoint,x=-32768,y=32767)
 for disabled in range(1,256):yield 'disabled_House_early_return',command(disabled=disabled)
 for flags in ((0x100,0,0),(0,0x400,0),(0x400,0x100,0),(0xffffffff,0xffffffff,0xffffffff)):
  for level in range(-128,128):
   yield 'signed_height_and_repeated_live_Cell_queries',command(flags=flags,levels=(17,level,level),mutation=(level+128)%3)
 for x,y in ((-32768,32767),(32767,-32768),(-1,-1),(0,0)):
  for scale in (0,-1,-2147483648,2147483647):
   for mutation in (0,1,2):
    yield 'word_coordinate_wrap_and_dword_height_product',command(waypoint=-2147483648,x=x,y=y,levels=(127,-128,-127),scale=scale,range=-2147483648,mutation=mutation)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_waypoint_lookup.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  q=parse(cmd)
  if q.get('getter'):require(isinstance(row,list) and row[:4]==['W',str(q['waypoint']),'D',str(q['out'])] and len(row)==4102 and row[-2:]==['R','1'] and all(0<=int(v)<=255 for v in row[4:-2]));continue
  require(isinstance(row,list) and row[-2:]==['R','1'] and row.count('W')==(0 if q['disabled'] else 1) and row.count('A')==(0 if q['disabled'] else 2) and row.count('L')==(0 if q['disabled'] else 2 if q['flags'][0]&0x100 else 3))

def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_waypoint_lookup import MissionWaypointLookupOracle
  oracle=MissionWaypointLookupOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6b0670']==sum(not parse(c).get('getter') for c in commands) and oracle.counts['supplied.reveal']==2*sum(not parse(c).get('getter') and not parse(c)['disabled'] for c in commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission waypoint reveal sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
