#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Waypoint discovery and typed recipients with actual Building target services."""
import argparse,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_waypoint_building_services import verify
NATIVE=('CMakeLists.txt','src/sim/MissionWaypointDiscovery.hpp','src/sim/WaypointResidentDiscovery.hpp','src/sim/WaypointTaggedDiscovery.hpp','src/sim/MissionTagExpiration.hpp','src/sim/MissionTagObjectExpiration.hpp','src/sim/MissionTechnoTagExpiration.hpp','src/sim/MissionTypedTagExpiration.hpp','src/sim/MissionBuildingTarget.hpp','tests/mission_waypoint_building_services_fixture.hpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp','src/sim/BuildingDiscovery.hpp','src/sim/BuildingDiscovery.cpp','src/sim/BuildingCoordinates.hpp','src/sim/BuildingCoordinates.cpp','src/sim/CellVisibilityDiscovery.hpp','src/sim/CellVisibilityDiscovery.cpp','src/sim/CellClosestResident.hpp','src/sim/MissionWaypointVisibility.hpp','src/sim/CellVisibilityChange.hpp','src/sim/CellVisibilityChange.cpp','src/sim/CellVisibilityMask.hpp','src/sim/CellVisibilityMask.cpp','src/sim/MissionWaypointRevealArea.hpp','src/sim/MissionWaypointReveal.hpp','src/sim/ScenarioWaypoint.hpp','src/sim/RevealArea.hpp','src/sim/RevealArea.cpp','src/sim/CellVisibilityState.hpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp','src/sim/OriginalMath.hpp','tests/mission_waypoint_building_services_vectors.cpp')
ORIGINAL=('tests/original_mission_waypoint_building_services.py','tools/verify_mission_waypoint_building_services.py','tests/compare_mission_waypoint_building_services.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_waypoint_building_services.py','tools/run_evidence.py')
FLAGS=dict(complete_waypoint_scenario_map_reveal_area_join=True,actual_height_projection_table_sqrt_and_FTOL=True,shared_Cell_flags_fallback_and_two_passes=True,fixed_Map_138_and_global_832618_table_alias=True,actual_counter_changes_and_visibility_masks=True,actual_Cell_discovery_closest_and_coordinates=True,actual_common_and_Building_discovery_and_coordinates=True,actual_Tag_Trigger_event_and_retirement=True,actual_packed_location_not_force=True,actual_generic_Tag44_broadcast_and_typed_recipients=True,shared_visibility_expiration_Cell_point_storage=True,typed_Infantry_Building_expiration_overrides=True,shared_Owner_Mission_radio_Next_and_Cell_fields=True,actual_stock_Building_null_target_availability_pending_and_getters=True,named_terminal_expiration_children_supplied=True,scenario_startup_House_residents_action_RTTI_selection_activation_redraw_notify_refresh_supplied=True,production_visibility_schedule=False)
def require(v):
 if not v:raise ValueError('Reveal-area evidence/input differs')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
FIELDS=('x','y','z','range','house','trim','unused','fog','heightCheck','child','divisor','scaleBits','rule1432','rule142b','origin','extent','primaryMode','secondaryMode','predicate','allied','flagsSeed','levelSeed','size')
def command(v):return 'J '+' '.join(map(str,[v['disabled'],v['waypoint'],v['heightScale'],v['bridge'],*[v[k] for k in FIELDS],*v['counts'],*[n for pair in zip(v['offsets'],v['heightOffsets']) for p in pair for n in p],*v['widths'],*v['heights'],v['tagMode']]))+' : '+str(v['serviceMode'])
def parse(cmd):
 chunks=cmd.split(' : ');require(len(chunks)==2);serviceMode=int(chunks[1]);require(serviceMode in range(5));p=chunks[0].split();require(p and p[0]=='J');nums=list(map(int,p[1:]));require(len(nums)>=38);disabled,waypoint,heightScale,bridge=nums[:4];nums=nums[4:];v=dict(zip(FIELDS,nums[:len(FIELDS)]));at=len(FIELDS);v['counts']=nums[at:at+11];at+=11;n=v['size'];require(0<=n<=4096 and n>=max(v['counts']) and len(nums)==at+n*4+45);v['offsets']=[];v['heightOffsets']=[]
 for i in range(n):v['offsets'].append((nums[at],nums[at+1]));v['heightOffsets'].append((nums[at+2],nums[at+3]));at+=4
 require(0<=disabled<256 and -2**31<=waypoint<2**31 and ((0x632+waypoint*4)&0xffffffff)+4<=0x1000 and -2**31<=heightScale<2**31 and bridge in (0,0x100,0x400))
 require(v['primaryMode']==v['secondaryMode'] and v['house'] in (0,1,2) and all(v[k] in (0,1) for k in ('trim','fog','heightCheck','rule1432','rule142b','predicate','allied')) and v['primaryMode'] in (0,1,2) and v['secondaryMode'] in (0,1,2) and v['divisor']!=0 and 0<=v['range']<2**31 and 0<=v['scaleBits']<2**64 and all(-32768<=n<=32767 for p in v['offsets']+v['heightOffsets'] for n in p))
 v['widths']=nums[at:at+22];v['heights']=nums[at+22:at+44];require(all(-2**31<=x<2**31 for x in v['widths']+v['heights']))
 v['tagMode']=nums[at+44];require(v['tagMode'] in range(7))
 v.update(disabled=disabled,waypoint=waypoint,heightScale=heightScale,bridge=bridge,serviceMode=serviceMode);return v
def scenarios(exe):
 import compare_mission_waypoint_typed as parent
 for label,cmd in parent.scenarios(exe):
  f=parent.parse(cmd);f['serviceMode']=0;yield 'actual_Building_services_'+label,command(f)
  if (f['flagsSeed'] in (286,442,910) and f['tagMode'] in (5,6)) or (f['flagsSeed']==442 and f['tagMode']==0):
   for mode in range(1,5):
    f['serviceMode']=mode;yield 'shared_late_count_pending_target_attachment_and_power',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_waypoint_building_services.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current,a):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios(a.exe));require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('Z')==1 and row.count('TYPED')==1 and row.count('SERVICES')==1 and row[-2:]==['END','1'])
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/mission-waypoint-building-services-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,a);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_waypoint_building_services import MissionWaypointBuildingServicesOracle
  oracle=MissionWaypointBuildingServicesOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(a.exe):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;print('Original counts',dict(oracle.counts),flush=True);require(oracle.counts['0x6ecb90']>0 and oracle.counts['0x5d3bd0']==34*oracle.counts['0x6ecb90'] and oracle.counts['0x501cb0']==17*oracle.counts['0x6ecb90'] and oracle.counts['0x449e40']==17*oracle.counts['0x6ecb90'] and oracle.counts['0x6d2d10']==34*oracle.counts['0x6ecb90'] and oracle.counts['supplied.nested']>0 and oracle.counts['supplied.animation']>0 and oracle.counts['supplied.range']>0 and oracle.counts['Tag.coordinates']>0 and oracle.counts['0x559d80']>0 and oracle.counts['0x53e110']>0 and oracle.counts['0x6b3df0']>0 and oracle.counts['0x6ed740']>0 and oracle.counts['0x6ed990']>0 and oracle.counts['0x5d4430']>0 and oracle.counts['0x47a460']>0 and oracle.counts['0x448fe0']>0 and oracle.counts['0x6c2440']>oracle.counts['0x448fe0'] and oracle.counts['0x444080']>0 and oracle.counts['0x6b0670']==len(commands) and oracle.counts['0x54a110']==2*sum(not parse(c)['disabled'] for c in commands) and oracle.counts['0x6a2970']==2*oracle.counts['0x54a110'] and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[hex(address)]>0 for address in (0x440450,0x6c9af0,0x450360,0x6c5070,0x594d80,0x6cd880,0x453c60,0x5950e0,0x41b410,0x41b2e0)))
  require(all(oracle.counts['power.mode'+str(mode)]>0 for mode in range(5)))
  require(all(oracle.counts[k]>0 for k in ('supplied.buildingPower','supplied.buildingClear','supplied.buildingIndex','supplied.buildingPermission','supplied.buildingRelease','supplied.buildingExpirationService')))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],j,got[max(0,j-12):j+30],want[max(0,j-12):j+30]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'waypoint Building service sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
