#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete nonzero radar refresh with shared actual map/actor/House/schemes."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_refresh import verify
NATIVE_EXTRA=('src/render/RadarRefresh.hpp','src/render/SurfaceRefreshPixels.hpp','src/render/SurfaceCopyBinding.hpp','src/render/SurfaceCopy.hpp','src/render/SurfaceClip.hpp','src/render/SurfaceMarkPixels.hpp','tests/radar_refresh_vectors.cpp','tests/radar_refresh_fixture.inc','tests/radar_refresh_guards.inc')
NATIVE=('CMakeLists.txt','src/render/SurfaceRadarPixel.hpp','src/render/SurfacePixel.hpp','src/render/RadarSurfacePixels.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/surface_radar_pixel_vectors.cpp','tests/surface_radar_pixels_vectors.cpp','tests/radar_discovery_pixels_vectors.cpp','tests/radar_map_pixels_vectors.cpp','tests/radar_refresh_vectors.cpp','tests/radar_actor_pixels_fixture.inc','tests/radar_actor_pixels_guards.inc','src/render/RadarActors.hpp','src/render/ActorRadarColor.hpp','src/render/SchemeResolver.hpp','src/render/UnitTypeVisibility.hpp','src/render/UnitTypeVisibility.cpp','src/sim/StringLookup.hpp','src/render/RadarMap.hpp','src/assets/MapFloorHeight.hpp','src/assets/MapFloorHeight.cpp','src/assets/MapCellInputs.hpp','src/render/RadarDiscovery.hpp','src/sim/MapVisibility.hpp','src/sim/MapVisibility.cpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp')
NATIVE=NATIVE+NATIVE_EXTRA
ORIGINAL=('tests/original_radar_refresh.py','tools/verify_radar_refresh.py','tests/compare_radar_refresh.py','tests/test_radar_refresh.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_zero_and_nonzero_refresh_join=True,actual_copy_mark_and_nonzero_pixels=True,shared_software_pixel_and_scheme_owners=True,zero_alpha_depth_planes=True,complete_radar_pixel_parent=True,complete_nonzero_refresh_parent_join=True,actual_stock_geometry_and_FTOL=True,finite_nonzero_scale_53_bit_toward_zero_profile=True,actual_stock_pixel_read_write_join=True,actual_shared_map_discovery_join=True,actual_floor_and_shared_cache_join=True,actual_stock_actor_House_type_owner_and_scheme_children=True,other_named_children_and_initial_records_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Radar refresh input/evidence differs')
import compare_radar_actor_pixels as parent
def command(f=None):
 if f is None:
  f=parent.parse(parent.command());f[0]=1;f[13]=3;f[31]=0
  f += [0,2,2,0,165]
 return 'X '+' '.join(map(str,f))
def parse(cmd):
 t=cmd.split();require(len(t)==66 and t[0]=='X');f=parent.parse('A '+' '.join(t[1:61]))+list(map(int,t[61:]));v=f[60:]
 require(v[0] in (0,1) and v[1] in (1,2) and 0<=v[2]<=2 and v[3] in (0,1) and 0<=v[4]<=255)
 require(f[0]==1 and 1<=f[2]<=5 and 1<=f[3]<=3 and f[31]==0 and f[56]==0 and f[59]==0)
 return f
def scenarios():
 i=0
 for start in (0,1):
  for stages in (1,2):
   for kind in range(4):
    for flagged in (0,7):
     for palette in (0,1,2):
      f=parse(command());f[1]=(-1,0,2)[i%3];f[17]=flagged;f[15]=i%8;f[53]=kind;f[54]=(0,7,0xffffffff)[i%3];f[55]=i%4;f[33]=1+i%2;f[34]=256+i%4;f[35]=(-1,0,1,2147483647)[i%4];f[40]=i%8;f[60:]=[start,stages,palette,i%2,(0,165,255)[i%3]]
      yield 'both_modes_same_stock_owners_and_backing',command(f);i+=1
 for start in (0,1):
  for count in (-1,0,1):
   for flags in (0,8,24):
    for empty in (0,3):
     f=parse(command());f[12]=empty;f[37]=flags;f[38]=count;f[60]=start
     yield 'copy_and_discovery_with_retained_shared_state',command(f)
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>513 and row[-513]=='U' and all(0<=int(v)<=255 for v in row[-512:]));body=row[:-513];filtered=[];i=0;steps=[]
 while i<len(body):
  tag=body[i]
  if tag=='step':require(i+2<=len(body) and int(body[i+1]) in (0,1));steps.append(int(body[i+1]));i+=2
  elif tag=='m':require(i+4<=len(body));at,n,value=map(int,body[i+1:i+4]);require(n in (1,4) and 0<=at<=512-n and 0<=value<2**(8*n));i+=4
  elif tag=='copy':require(i+13<=len(body));v=list(map(int,body[i+1:i+13]));require(v[0] in (0,1) and v[5] in (0,1) and v[-2:]==[0,1] and all(-2**31<=x<2**31 for x in v));i+=13
  elif tag=='P':require(i+6<=len(body));v=list(map(int,body[i+1:i+6]));require(v[0] in (0,1) and 0<=v[1]<3 and all(-2**31<=x<2**31 for x in v[2:4]) and 0<=v[4]<2**32);i+=6
  elif tag=='N' and i+5<=len(body) and body[i+3]=='4':
   v=list(map(int,body[i+1:i+5]));require(v[0] in (0,1) and 0<=v[1]<=2044 and 0<=v[3]<2**32);i+=5
  else:filtered.append(tag);i+=1
 require(steps==[f[60]^stage for stage in range(f[61])]);at=filtered.index('R');filtered[at+8:at+8]=['0']*4
 parent.validate_row(parent.command(f[:60]),filtered)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_refresh.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_refresh import RadarRefreshOracle
  oracle=RadarRefreshOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;print('Original branch counts',dict(oracle.counts),flush=True);require(not any(oracle.counts.get(k,0) for k in ('supplied_get28','supplied_set24','supplied_discovery0','supplied_discovery1','supplied_floor','supplied_type80','supplied_local','supplied_alliedObject','supplied_C0','supplied_CC','supplied_resolver')));require(oracle.audit_calls==sum(parse(cmd)[61] for cmd in commands) and all(oracle.counts[a]>0 for a in ('0x6324a0','mark_pixels','zero_0x774f00','0x632000','0x634030','0x77f110','0x55a280','0x4706c0','0x568140','0x568280','0x476ac0','0x548070','0x6c12c0','0x506950','0x453c60','0x6c7430','0x4f52b0','0x4e5580','0x41b410','0x509270','0x41b2e0','0x4e5540','0x663d30','0x781f20','0x7741d0','0x774220','0x411370','0x4112f0','0x4113b0','0x4113c0')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,lazy_state_stores=oracle.lazyStores,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar refresh sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
