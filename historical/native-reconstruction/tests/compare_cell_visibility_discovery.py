#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare base Cell visibility discovery projection with portable C++."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_cell_visibility_discovery import verify
NATIVE=('src/sim/CellClosestResident.hpp','src/sim/CellVisibilityDiscovery.hpp','src/sim/CellVisibilityDiscovery.cpp','tests/cell_visibility_discovery_vectors.cpp')
ORIGINAL=('tests/original_cell_visibility_discovery.py','tools/verify_cell_visibility_discovery.py','tools/verify_terrain_visibility.py','tests/compare_cell_visibility_discovery.py')
SOURCES=(*NATIVE,*ORIGINAL)
FLAGS=dict(complete_visibility_change_projection_568520=True,seven_Cell_diagonal_and_signed_level_windows=True,actual_closest_resident_coordinate_and_numeric_children=True,Cell_notification_and_DiscoveredBy_effects_supplied=True,reveal_area_and_Techno_sight_parents_unjoined=True,production_discovery_schedule=False)
def require(v):
 if not v:raise ValueError('Cell visibility discovery evidence/input differs')
def command(sx,sy,house,notify,records):return 'V '+' '.join(map(str,[sx,sy,house,notify,*[v for r in records for v in (r['present'],r['level'],r['members'],r['active'],r['ax'],r['ay'],r['bx'],r['by'])]]))
def parse(cmd):
 p=cmd.split();require(len(p)==69 and p[0]=='V');v=list(map(int,p[1:]));sx,sy,house,notify=v[:4];require(-32768<=sx<=32761 and -32768<=sy<=32761 and -2147483648<=house<=2147483647 and notify in (0,1));records=[]
 for i in range(4,68,8):
  present,level,members,active,ax,ay,bx,by=v[i:i+8];require(present in (0,1) and -128<=level<=127 and 0<=members<4 and 0<=active<4 and all(-2147483648<=x<=2147483647 for x in (ax,ay,bx,by)));records.append(dict(present=present,level=level,members=members,active=active,ax=ax,ay=ay,bx=bx,by=by))
 return dict(sx=sx,sy=sy,house=house,notify=notify,records=records)
def scenarios():
 rng=random.Random(0x568520)
 for case in range(64):
  sx=9+(case%7);sy=11+(case%5);records=[]
  for i in range(8):
   upper=2*i+1 if i<7 else 5
   level=(upper-2,upper,upper+1,-128,127)[(case+i)%5];members=(case+i*3)%4;active=(case*3+i)%4
   if case<4:level=upper-(case&1)*2;members=1;active=1
   records.append(dict(present=1 if i==7 else int((case+i)%4!=0),level=level,members=members,active=active,ax=rng.randint(-512,512),ay=rng.randint(-512,512),bx=rng.randint(-512,512),by=rng.randint(-512,512)))
  yield ('all_windows_and_notifications' if case<4 else 'fallback_level_filter_active_lists_low_byte_distance'),command(sx,sy,-17+case,case&1,records)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_visibility_discovery.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row[-1:] == ['R'] and row.count('C')==7 and row.count('L')==7)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/cell-visibility-discovery-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_visibility_discovery import CellVisibilityDiscoveryOracle
  oracle=CellVisibilityDiscoveryOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x568520']==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell visibility discovery sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
