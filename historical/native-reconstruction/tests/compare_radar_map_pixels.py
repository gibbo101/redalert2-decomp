#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete nonzero radar pixel and caller with named child services."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_map_pixels import verify
NATIVE=('CMakeLists.txt','src/render/SurfaceRadarPixel.hpp','src/render/SurfacePixel.hpp','src/render/RadarSurfacePixels.hpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/render/SurfaceRefreshMarks.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/surface_radar_pixel_vectors.cpp','tests/surface_radar_pixels_vectors.cpp','tests/radar_discovery_pixels_vectors.cpp','tests/radar_map_pixels_vectors.cpp','src/render/RadarMap.hpp','src/assets/MapFloorHeight.hpp','src/assets/MapFloorHeight.cpp','src/assets/MapCellInputs.hpp','src/render/RadarDiscovery.hpp','src/sim/MapVisibility.hpp','src/sim/MapVisibility.cpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp')
ORIGINAL=('tests/original_radar_map_pixels.py','tools/verify_radar_map_pixels.py','tests/compare_radar_map_pixels.py','tests/test_radar_map_pixels.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_radar_pixel_parent=True,complete_nonzero_refresh_parent_join=True,actual_stock_geometry_and_FTOL=True,finite_nonzero_scale_53_bit_toward_zero_profile=True,actual_stock_pixel_read_write_join=True,actual_shared_map_discovery_join=True,actual_floor_and_shared_cache_join=True,other_named_children_and_initial_records_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Radar map pixels input/evidence differs')
import compare_radar_discovery_pixels as parent
import compare_surface_radar_pixels as pixels
def command(f=None):
 if f is None:f=parent.parse(parent.command())+[104,0,0,0,1,1,-1,2,2,3,0,208]
 return 'M '+' '.join(map(str,f))
def parse(cmd):
 t=cmd.split();require(len(t)==52 and t[0]=='M');f=parent.parse('U '+' '.join(t[1:40]))+list(map(int,t[40:]));require(-2**31<=f[39]<2**31 and 0<=f[40]<=255 and 0<=f[49]<=8 and -2**31<=f[50]<2**31)
 for i in range(4):require(-128<=f[41+2*i]<=127 and 0<=f[42+2*i]<=20)
 return f
def scenarios():
 for i,(label,cmd) in enumerate(parent.scenarios()):
  f=parent.parse(cmd)+[(104,208,-104,2147483647)[i%4],(0,1,2,3,4,5,6,7,248,255)[i%10],(0,1,-1,127)[i%4],i%21,1,(i+1)%21,-1,(i+7)%21,(-128,-1,1,127)[i%4],(i+13)%21,i%5,(-104,104,208,-2147483648)[i%4]]
  yield 'actual_floor_'+label,command(f)
 # Every ramp and independent lazy flag, full refresh reuse, negative levels and
 # live height changes after the first query. These are supplied diagnostics.
 for ramp in range(21):
  for flags in (0,1,2,3,4,5,6,7,248,255):
   f=parse(command());f[0]=1;f[9]=1;f[13]=3;f[41:49]=[-1,ramp,1,(ramp+1)%21,127,ramp,-128,ramp];f[40]=flags;f[49]=2;f[50]=-104
   yield 'all_ramps_independent_lazy_bits_and_warm_parent',command(f)
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>6 and row[-3]=='O' and -2**31<=int(row[-2])<2**31 and len(row[-1])==64 and all(c in '0123456789abcdef' for c in row[-1]));body=row[:-3];require(body[-3]=='Y' and all(-32768<=int(v)<=32767 for v in body[-2:]));filtered=[];i=0
 while i<len(body)-3:
  tag=body[i]
  if tag in ('i','w','f'):require(i+3<=len(body)-3 and all(-32768<=int(v)<=32767 for v in body[i+1:i+3]));i+=3
  elif tag in ('n','c'):
   require(i+4<=len(body)-3 and all(-32768<=int(v)<=32767 for v in body[i+1:i+3]) and (int(body[i+3])==3 if tag=='n' else -2**31<=int(body[i+3])<2**31));i+=4
  elif tag in ('g','t'):require(i+2<=len(body)-3 and -2**31<=int(body[i+1])<2**31);i+=2
  else:filtered.append(tag);i+=1
 pixels.validate_row(pixels.command(f[:36]),filtered)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_map_pixels.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_map_pixels import RadarMapPixelsOracle
  oracle=RadarMapPixelsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(not any(oracle.counts.get(k,0) for k in ('supplied_get28','supplied_set24','supplied_discovery0','supplied_discovery1','supplied_floor')));require(oracle.audit_calls==len(commands) and all(oracle.counts[a]>0 for a in ('0x632000','0x634030','0x77f110','0x55a280','0x4706c0','0x568140','0x568280','0x476ac0','0x548070','supplied_type80','supplied_local','supplied_alliedObject','supplied_C0','supplied_CC','supplied_resolver','0x7741d0','0x774220','0x411370','0x4112f0','0x4113b0','0x4113c0')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,lazy_state_stores=oracle.lazyStores,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar map pixels sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
