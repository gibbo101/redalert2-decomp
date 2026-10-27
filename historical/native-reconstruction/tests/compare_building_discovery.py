#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete supplied-base Building discovery and radio-link scanning."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_building_discovery import verify

NATIVE=('src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp','src/sim/BuildingDiscovery.hpp','src/sim/BuildingDiscovery.cpp','tests/building_discovery_vectors.cpp')
ORIGINAL=('tests/original_building_discovery.py','tools/verify_building_discovery.py','tests/compare_building_discovery.py')
FLAGS=dict(complete_Building448FE0=True,complete_common_discovery=True,complete_radio636F10=True,activation4426D0_supplied=True,typeB90_supplied=True,production_schedule=False)
def require(v):
 if not v:raise ValueError('Building discovery evidence/input differs')
def parse(cmd):
 p=cmd.split();require(len(p)>5 and p[0]=='B');v=list(map(int,p[1:]));require(all(-2**31<=x<2**31 for x in v))
 type_index,count,size=v[:3];require(0<=size<=8 and count<=size);links=v[3:3+size];require(all(x in (0,1) for x in links));v=v[3+size:];require(len(v)>=26)
 h=v[:13];require(h[3] in (-1,0,1) and h[4] in (0,1) and all(0<=h[i]<=255 for i in (5,6,7,10)) and h[11] in (0,1) and h[12] in (0,1));houses=[v[13:19],v[19:25]];require(all(0<=x<=255 for row in houses for x in row));n=v[25];require(1<=n<=128 and len(v)==26+n and all(x in (-1,0,1) for x in v[26:]))
 return dict(type=type_index,count=count,links=links,header=h,houses=houses,discoverers=v[26:])
def scenarios():
 import itertools
 radios=[(-1,[]),(0,[]),(3,[0,0,0]),(3,[1,0,0]),(3,[0,0,1])]
 for mode,loading,owner,control,mission,queued,radio in itertools.product((0,1),(0,1),(0,1),(0,1,255),(-1,14,18),(2,18),radios):
  count,links=radio;h=[mode,loading,17,0,owner,0,0,0,mission,queued,127,0,0];houses=[0,control,0,0,0,0]*2;ds=[0,0,1,1,-1]
  yield 'Building_wrapper_radio_mission_owner_sequence','B '+' '.join(map(str,[37,count,len(links),*links,*h,*houses,len(ds),*ds]))
 for current,seen,other,tag,mutation,type_index in itertools.product((-1,0,1),(0,255),(0,127),(0,1),(0,1),(-1,2147483647)):
  h=[0,0,-7,current,0,0,seen,other,14,-1,255,tag,mutation];houses=[0,0,0,0,0,0]*2;ds=[0,1,-1,0]
  yield 'Building_common_rejection_Tag_late_owner','B '+' '.join(map(str,[type_index,0,0,*h,*houses,len(ds),*ds]))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_discovery.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/building-discovery-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_discovery import BuildingDiscoveryOracle
  oracle=BuildingDiscoveryOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  require(oracle.counts['root']==sum(len(parse(cmd)['discoverers']) for cmd in commands) and oracle.counts['activation']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building discovery sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
