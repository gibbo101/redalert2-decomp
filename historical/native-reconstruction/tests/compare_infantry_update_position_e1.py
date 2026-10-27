#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the complete bounded ordinary-E1 path through base500AA0."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_update_position_e1 import verify,START
NATIVE=('src/sim/InfantryUpdatePositionE1.hpp','src/sim/InfantryUpdatePositionE1.cpp','src/sim/InfantrySightSchedule.hpp','src/sim/InfantrySightSchedule.cpp','src/sim/CellResidentKind6.hpp','src/sim/CellResidentKind6.cpp','tests/infantry_update_position_e1_vectors.cpp')
ORIGINAL=('tests/original_infantry_update_position_e1.py','tools/verify_infantry_update_position_e1.py','tests/compare_infantry_update_position_e1.py')
FLAGS=dict(complete_500AA0_parent_range_pinned=True,complete_bounded_argument2_ordinary_E1_path=True,three_independent_current_Cell_service_calls=True,actual_mission_and_initialized_empty_Cell_resident_helpers=True,ordered_sight_suffix_and_post_tail=True,supplied_map_target_coordinate_sight_and_4C7220_children=True,alternate_parent_branches=False,production_visibility_schedule=False)
def require(v):
 if not v:raise ValueError('Infantry E1 update-position evidence/input differs')
def command(x,y,z,tx,ty,tz,r,q,b,o):return 'U '+' '.join(map(str,(x,y,z,tx,ty,tz,r,q,b,o)))
def parse(cmd):
 p=cmd.split();require(len(p)==11 and p[0]=='U');v=list(map(int,p[1:]));require(all(-2**31<=x<2**31 for x in v[:8]) and v[8] in (0,1) and v[9] in (0,1));return dict(zip(('x','y','z','tx','ty','tz','range','queued','bridge','onMap'),v))
def scenarios():
 rng=random.Random(0x500aa0);edges=(-2**31,-3,-1,0,1,2**31-4,2**31-1)
 for i in range(64):
  points=[rng.randint(-2**31,2**31-1) for _ in range(6)]
  yield 'complete_bounded_argument2_E1_parent',command(*points,edges[i%len(edges)],-1 if i%3 else 2,i&1,(i>>1)&1)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_update_position_e1.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(row.count('m')==7 and row.count('C')==3 and row.count('M')==1 and row[-2:] in (['L','1'],['U','2']))
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/infantry-update-position-e1-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_update_position_e1 import InfantryUpdatePositionE1Oracle
  oracle=InfantryUpdatePositionE1Oracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts[hex(START)]==len(commands) and oracle.counts['mission']==7*len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry E1 update-position sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
