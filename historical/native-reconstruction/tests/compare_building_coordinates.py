#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete supplied-base Building coordinates, foundation helpers and mixed closest-resident dispatch."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_building_coordinates import verify

NATIVE=('src/sim/BuildingCoordinates.hpp','src/sim/BuildingCoordinates.cpp','src/sim/CellClosestResident.hpp','src/sim/CellVisibilityDiscovery.hpp','src/sim/CellVisibilityDiscovery.cpp','tests/building_coordinates_vectors.cpp')
ORIGINAL=('tests/original_building_coordinates.py','tools/verify_building_coordinates.py','tests/compare_building_coordinates.py')
FLAGS=dict(complete_Building444080=True,complete_type458930_458940=True,mixed_closest471660=True,original_tables_unmodified=True,complete_visibility568520=True,discovery180_supplied=True,production_schedule=False)
def require(v):
 if not v:raise ValueError('Building coordinate evidence/input differs')
def parse(cmd):
 p=cmd.split();require(len(p)==60 and p[0] in ('C','H','W','R','V'));v=list(map(int,p[1:]));require(all(-2**31<=x<2**31 for x in v))
 index,extra,include=v[:3];require(0<=index<22 and 0<=extra<=255 and 0<=include<=255 and all(0<=x<=255 for x in v[9:11]) and v[13] in (0,1) and v[14] in (-1,0,1) and all(-32<=x<=32 for x in v[11:13]));return dict(op=p[0],index=index,extra=extra,include=include,point=v[3:6],common=v[6:9],flags=v[9:11],query=v[11:13],elevated=v[13],ignore=v[14],tables=v[15:])
def scenarios(data):
 import itertools
 from verify_building_coordinates import tables
 widths,heights=tables(data);tail=[*widths,*heights]
 def cmd(op,index,extra=0,include=0,point=(128,128,0),common=(32,64,7),flags=(1,1),query=(0,0),elevated=0,ignore=-1):
  return op+' '+' '.join(map(str,[index,extra,include,*point,*common,*flags,*query,elevated,ignore,*tail]))
 for index in range(22):
  yield 'actual_foundation_width',cmd('W',index)
  for extra,include in itertools.product((0,255),(0,1,255)):
   yield 'actual_foundation_height_extra_row',cmd('H',index,extra,include)
  for extra,point in itertools.product((0,255),((0,0,0),(128,128,104),(2147483647,-2147483648,-2147483648),(-2147483648,2147483647,2147483647),(-129,-257,-7),(32767,-32768,0))):
   yield 'complete_Building_wrapped_coordinates',cmd('C',index,extra,point=point)
  for flags,ignore,elevated in itertools.product(((1,1),(0,1),(1,0),(255,255)),(-1,0,1),(0,1)):
   yield 'mixed_Infantry_Building_closest_dispatch',cmd('R',index,point=(128,128,104),common=(64,64,-17),flags=flags,ignore=ignore,elevated=elevated)
 for index,flags in itertools.product(range(22),((1,1),(0,1),(1,0),(255,255))):
  yield 'complete_visibility_mixed_coordinate_dispatch',cmd('V',index,flags=flags)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_coordinates.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current,data):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios(data));require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/building-coordinates-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,a.exe.read_bytes());commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_coordinates import BuildingCoordinatesOracle
  oracle=BuildingCoordinatesOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(a.exe.read_bytes()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  require(oracle.counts['0x444080']>0 and oracle.counts['0x471660']==616 and oracle.counts['0x568520']==88 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building coordinates sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
