#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete base reveal-area parent with portable C++."""
import argparse,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_waypoint_expiration import verify
NATIVE=('CMakeLists.txt','src/sim/MissionWaypointDiscovery.hpp','src/sim/WaypointResidentDiscovery.hpp','src/sim/WaypointTaggedDiscovery.hpp','src/sim/MissionTagExpiration.hpp','src/sim/MissionTagObjectExpiration.hpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp','src/sim/BuildingDiscovery.hpp','src/sim/BuildingDiscovery.cpp','src/sim/BuildingCoordinates.hpp','src/sim/BuildingCoordinates.cpp','src/sim/CellVisibilityDiscovery.hpp','src/sim/CellVisibilityDiscovery.cpp','src/sim/CellClosestResident.hpp','src/sim/MissionWaypointVisibility.hpp','src/sim/CellVisibilityChange.hpp','src/sim/CellVisibilityChange.cpp','src/sim/CellVisibilityMask.hpp','src/sim/CellVisibilityMask.cpp','src/sim/MissionWaypointRevealArea.hpp','src/sim/MissionWaypointReveal.hpp','src/sim/ScenarioWaypoint.hpp','src/sim/RevealArea.hpp','src/sim/RevealArea.cpp','src/sim/CellVisibilityState.hpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp','src/sim/OriginalMath.hpp','tests/mission_waypoint_expiration_vectors.cpp')
ORIGINAL=('tests/original_mission_waypoint_expiration.py','tools/verify_mission_waypoint_expiration.py','tests/compare_mission_waypoint_expiration.py')
FLAGS=dict(complete_waypoint_scenario_map_reveal_area_join=True,actual_height_projection_table_sqrt_and_FTOL=True,shared_Cell_flags_fallback_and_two_passes=True,fixed_Map_138_and_global_832618_table_alias=True,actual_counter_changes_and_visibility_masks=True,actual_Cell_discovery_closest_and_coordinates=True,actual_common_and_Building_discovery_and_coordinates=True,actual_Tag_Trigger_event_and_retirement=True,actual_packed_location_not_force=True,actual_generic_Tag44_broadcast_and_base_Object_recipients=True,shared_visibility_expiration_Cell_point_storage=True,typed_Infantry_Building_expiration_overrides=False,scenario_startup_House_residents_action_RTTI_selection_activation_redraw_notify_refresh_supplied=True,production_visibility_schedule=False)
def require(v):
 if not v:raise ValueError('Reveal-area evidence/input differs')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
FIELDS=('x','y','z','range','house','trim','unused','fog','heightCheck','child','divisor','scaleBits','rule1432','rule142b','origin','extent','primaryMode','secondaryMode','predicate','allied','flagsSeed','levelSeed','size')
def command(v):return 'J '+' '.join(map(str,[v['disabled'],v['waypoint'],v['heightScale'],v['bridge'],*[v[k] for k in FIELDS],*v['counts'],*[n for pair in zip(v['offsets'],v['heightOffsets']) for p in pair for n in p],*v['widths'],*v['heights'],v['tagMode']]))
def parse(cmd):
 p=cmd.split();require(p and p[0]=='J');nums=list(map(int,p[1:]));require(len(nums)>=38);disabled,waypoint,heightScale,bridge=nums[:4];nums=nums[4:];v=dict(zip(FIELDS,nums[:len(FIELDS)]));at=len(FIELDS);v['counts']=nums[at:at+11];at+=11;n=v['size'];require(0<=n<=4096 and n>=max(v['counts']) and len(nums)==at+n*4+45);v['offsets']=[];v['heightOffsets']=[]
 for i in range(n):v['offsets'].append((nums[at],nums[at+1]));v['heightOffsets'].append((nums[at+2],nums[at+3]));at+=4
 require(0<=disabled<256 and -2**31<=waypoint<2**31 and ((0x632+waypoint*4)&0xffffffff)+4<=0x1000 and -2**31<=heightScale<2**31 and bridge in (0,0x100,0x400))
 require(v['primaryMode']==v['secondaryMode'] and v['house'] in (0,1,2) and all(v[k] in (0,1) for k in ('trim','fog','heightCheck','rule1432','rule142b','predicate','allied')) and v['primaryMode'] in (0,1,2) and v['secondaryMode'] in (0,1,2) and v['divisor']!=0 and 0<=v['range']<2**31 and 0<=v['scaleBits']<2**64 and all(-32768<=n<=32767 for p in v['offsets']+v['heightOffsets'] for n in p))
 v['widths']=nums[at:at+22];v['heights']=nums[at+22:at+44];require(all(-2**31<=x<2**31 for x in v['widths']+v['heights']))
 v['tagMode']=nums[at+44];require(v['tagMode'] in range(7))
 v.update(disabled=disabled,waypoint=waypoint,heightScale=heightScale,bridge=bridge);return v
def scenarios(exe):
 from verify_building_coordinates import tables
 widths,heights=tables(exe.read_bytes());counts=verify(exe.read_bytes())['counts'];rng=random.Random(0x54a110);n=max(counts)
 for case in range(96):
  offsets=[];height=[]
  for i in range(n):offsets.append((((i*7+case*3)%13)-6,((i*11+case)%13)-6));height.append((((i*5+case)%9)-4,((i*3+case*2)%9)-4))
  v=dict(x=(20*256+rng.randint(-255,255)),y=(20*256+rng.randint(-255,255)),z=(-400,-1,0,416,727,728,1200)[case%7],range=(0,1,2,3,4,5,6,11,15)[case%9],house=case%3,trim=(case//2)&1,unused=0x80000000+case,fog=(case//3)&1,heightCheck=(case//4)&1,child=0x12340000+case,divisor=(104,256,-104)[case%3],scaleBits=bits((0.,.01,-.02)[case%3]),rule1432=(case//5)&1,rule142b=(case//7)&1,origin=100 if case==2 else 10,extent=80,primaryMode=case%3,secondaryMode=(case//3)%3,predicate=(case//2)&1,allied=1 if case%11==0 else 0,flagsSeed=case*13,levelSeed=case*5,size=n,counts=counts,offsets=offsets,heightOffsets=height)
  v.update(x=20*256+128,y=20*256+128,disabled=0 if case<72 else (1,255)[case&1],waypoint=(6,-1,-2147483648)[case%3],heightScale=(104,-104,2147483647)[case%3],bridge=(0,0x100,0x400)[case%3])
  v['widths']=widths;v['heights']=heights;v['primaryMode']=v['secondaryMode']
  v['tagMode']=(case//5)%3
  yield 'actual_waypoint_visibility_discovery_Tag_Trigger',command(v)
  if case in (22,34,70):
   for mode in (3,4,5,6):
    v['tagMode']=mode;yield 'Tag_guard_single_instance_and_empty_location',command(v)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_waypoint_expiration.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current,a):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios(a.exe));require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('Z')==1 and row[-2:]==['END','1'])
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/mission-waypoint-expiration-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,a);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_waypoint_expiration import MissionWaypointExpirationOracle
  oracle=MissionWaypointExpirationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(a.exe):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6ecb90']>0 and oracle.counts['0x5d3bd0']==34*oracle.counts['0x6ecb90'] and oracle.counts['0x559d80']>0 and oracle.counts['0x53e110']>0 and oracle.counts['0x6b3df0']>0 and oracle.counts['0x6ed740']>0 and oracle.counts['0x6ed990']>0 and oracle.counts['0x5d4430']>0 and oracle.counts['0x47a460']>0 and oracle.counts['0x448fe0']>0 and oracle.counts['0x6c2440']>oracle.counts['0x448fe0'] and oracle.counts['0x444080']>0 and oracle.counts['0x6b0670']==len(commands) and oracle.counts['0x54a110']==2*sum(not parse(c)['disabled'] for c in commands) and oracle.counts['0x6a2970']==2*oracle.counts['0x54a110'] and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],j,got[max(0,j-12):j+30],want[max(0,j-12):j+30]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'reveal-area sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
