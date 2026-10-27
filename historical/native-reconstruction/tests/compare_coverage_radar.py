#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete coverage parents call actual nonzero radar on shared owners."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_coverage_radar import verify
NATIVE_EXTRA=('src/platform/CoverageRadar.hpp','src/sim/StockTechnoCoverage.hpp','src/sim/MissionBuildingTarget.hpp','src/sim/MissionTypedTagExpiration.hpp','src/sim/TechnoCoverage.hpp','src/sim/RevealArea.hpp','src/sim/RevealArea.cpp','tests/coverage_radar_vectors.cpp','tests/coverage_radar_fixture.inc','tests/coverage_radar_guards.inc')
NATIVE=('CMakeLists.txt','src/render/SurfaceRadarPixel.hpp','src/render/SurfacePixel.hpp','src/render/RadarSurfacePixels.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/surface_radar_pixel_vectors.cpp','tests/surface_radar_pixels_vectors.cpp','tests/radar_discovery_pixels_vectors.cpp','tests/radar_map_pixels_vectors.cpp','tests/radar_actor_pixels_vectors.cpp','tests/radar_actor_pixels_fixture.inc','tests/radar_actor_pixels_guards.inc','src/render/RadarActors.hpp','src/render/ActorRadarColor.hpp','src/render/SchemeResolver.hpp','src/render/UnitTypeVisibility.hpp','src/render/UnitTypeVisibility.cpp','src/sim/StringLookup.hpp','src/render/RadarMap.hpp','src/assets/MapFloorHeight.hpp','src/assets/MapFloorHeight.cpp','src/assets/MapCellInputs.hpp','src/render/RadarDiscovery.hpp','src/sim/MapVisibility.hpp','src/sim/MapVisibility.cpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp')
NATIVE=NATIVE+NATIVE_EXTRA
ORIGINAL=('tests/original_coverage_radar.py','tools/verify_coverage_radar.py','tests/compare_coverage_radar.py','tests/test_coverage_radar.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(actual_coverage_parent_and_nonzero_refresh_join=True,shared_mutable_Cell_flags12C_count13C=True,actual_stock_coverage_permission_type_owner=True,redraw_initialization_supplied=True,complete_radar_pixel_parent=True,complete_nonzero_refresh_parent_join=True,actual_stock_geometry_and_FTOL=True,finite_nonzero_scale_53_bit_toward_zero_profile=True,actual_stock_pixel_read_write_join=True,actual_shared_map_discovery_join=True,actual_floor_and_shared_cache_join=True,actual_stock_actor_House_type_owner_and_scheme_children=True,other_named_children_and_initial_records_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Coverage radar input/evidence differs')
import compare_radar_actor_pixels as parent
def command(f=None):
 if f is None:
  f=parent.parse(parent.command());f[0]=1;f[13]=3;f[31]=0
  f += [0,1,1,1,1,0,0,0,0,1,0,0,0]
 return 'C '+' '.join(map(str,f))
def parse(cmd):
 t=cmd.split();require(len(t)==74 and t[0]=='C');f=parent.parse('A '+' '.join(t[1:61]))+list(map(int,t[61:]));v=f[60:]
 require(v[0] in (0,1) and 0<=v[1]<=255 and all(-3<=x<=2 for x in v[2:4]) and 0<=v[4]<=255 and all(-2**31<=x<2**31 for x in v[5:8]) and all(0<=x<=255 for x in v[8:10]) and all(-2**31<=x<2**31 for x in v[10:12]) and 0<=v[12]<3)
 require(f[0]==1 and f[9]!=0 and f[31]==0 and f[56]==0 and f[59]==0)
 return f
def scenarios():
 for kind in (0,1):
  for addition in (0,1):
   for privileged in (0,1,2,3):
    for count in (-2**31,-1,0,1,2**31-1):
     for radius in (-3,0,1,2):
      f=parse(command());f[1]=0;f[14]=1 if privileged==0 else 0;f[51]=0;f[54]=1 if privileged==1 else 0
      f[53]=kind;f[37]=24;f[38]=count;f[60:]=[addition,0 if addition else 1,radius,1,255,0,0,0,int(privileged==2),1,0,0,2]
      if privileged==3:f[1]=2
      yield 'counter_flags_and_visibility_transition',command(f)
 for active in (0,1,255):
  for permission in (0,1,255):
   for current in (-1,0,2):
    for addition in (0,1):
     f=parse(command());f[1]=current;f[53]=int(permission!=255);f[60]=addition;f[61]=active;f[64]=permission
     yield 'coverage_entry_guards',command(f)
 for x,y,z in ((0,0,0),(-1,-257,727),(256,256,728),(512,512,729),(2**31-1,-2**31,-2**31)):
  for count in (-1,0,1):
   for mode in (1,-1):
    f=parse(command());f[38]=count;f[9]=mode;f[65:68]=[x,y,z];f[51]=1
    yield 'shared_fallback_height_and_projection',command(f)
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>22 and row[-22]=='Q');q=list(map(int,row[-21:]));require(0<=q[0]<=255 and -2**31<=q[1]<2**31 and all(0<=v<=255 for v in q[2:5]) and all(-2**31<=v<2**31 for v in q[5:]))
 body=row[:-22];filtered=[];i=0
 while i<len(body):
  tag=body[i]
  if tag=='u':require(i+4<=len(body) and body[i+1] in ('A','C','H') and int(body[i+2]) in dict(A=(0x1fd,0x200),H=(0x188,),C=(0x12c,0x130,0x134,0x13c))[body[i+1]] and -2**31<=int(body[i+3])<2**31);i+=4
  elif tag in ('p','a','o','d'):require(i+2<=len(body) and -128<=int(body[i+1])<=255);i+=2
  elif tag in ('l','z'):require(i+3<=len(body) and all(-2**31<=int(v)<2**31 for v in body[i+1:i+3]));i+=3
  elif tag=='b':require(i+4<=len(body) and all(-1<=int(v)<=2 for v in body[i+1:i+3]) and int(body[i+3]) in (0,1));i+=4
  else:filtered.append(tag);i+=1
 at=filtered.index('R');filtered[at+10:at+10]=['0','0']
 parent.validate_row(parent.command(f[:60]),filtered)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_coverage_radar.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_coverage_radar import CoverageRadarOracle
  oracle=CoverageRadarOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(not any(oracle.counts.get(k,0) for k in ('supplied_coverage_type','supplied_coverage_permission','supplied_get28','supplied_set24','supplied_discovery0','supplied_discovery1','supplied_floor','supplied_type80','supplied_local','supplied_alliedObject','supplied_C0','supplied_CC','supplied_resolver')));require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('coverage_0x6c83f0','coverage_0x6c86f0','coverage_0x6a2970','coverage_type','coverage_permission_0x450360','coverage_permission_0x6cd6e0','0x632000','0x634030','0x568140','0x568280','0x7741d0','0x774220')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,lazy_state_stores=oracle.lazyStores,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Coverage radar sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
