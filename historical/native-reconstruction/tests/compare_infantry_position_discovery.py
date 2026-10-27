#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the bounded complete base4C7220 + base6C2B40 ordinary-E1 path."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_position_discovery import verify

NATIVE=('src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp','src/sim/InfantryPositionEffectsE1.hpp','src/sim/InfantryPositionEffectsE1.cpp','src/sim/CellResidentKind6.hpp','src/sim/CellResidentKind6.cpp','src/sim/InfantryWeaponSelection.hpp','src/sim/InfantryWeaponSelection.cpp','src/sim/PositionCloakEffect.hpp','src/sim/PositionCloakEffect.cpp','src/sim/CellDirtyEffect.hpp','src/sim/CellDirtyEffect.cpp','tests/infantry_position_effects_e1_vectors.cpp')
ORIGINAL=('tests/original_infantry_position_discovery.py','tools/verify_infantry_position_discovery.py','tests/compare_infantry_position_discovery.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_infantry_position_discovery.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_4C7220_and_6C2B40=True,actual_Infantry_discovery_dispatch=True,
 complete_Techno_Object_House_Mission_QueueMission=True,null_Tag_only=True,
 production_visibility_binding=False,production_position_effect_schedule=False)
def require(v):
 if not v:raise ValueError('Infantry position-discovery evidence/input differs')
def cell(v):return ((int(v/256)+0x8000)&0xffff)-0x8000
def parse(cmd):
 p=cmd.split();require(len(p)==16 and p[0]=='D');v=list(map(int,p[1:]));require(all(-2**31<=x<2**31 for x in v[:3]) and v[3:5]==[cell(v[0]),cell(v[1])]);require(all(0<=v[i]<=255 for i in (5,6,9,10,12,13)) and v[7] in (0,1) and v[8] in (0,1) and v[11] in (2,14,19) and v[14] in (0,1,-1));return dict(zip(('x','y','z','cellX','cellY','state59a','state59c','onMap','permission','revealed','discovered','mission','human','field372','loading'),v))
def scenarios():
 import itertools
 for on,flags,seen,mission,human,field in itertools.product((0,1),(0,8,16,24,255),(0,1,255),(2,14,19),(0,1),(0,255)):
  values=[57*256+192,89*256+192,0,57,89,127,255,on,1,flags,seen,mission,human,field,0]
  yield 'Infantry_revealed_Cell_discovery_and_late_skip', 'D '+' '.join(map(str,values))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_position_discovery.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  f=parse(cmd);entered=bool(f['onMap'] and not f['discovered'] and f['revealed']&16)
  require(row.count('d')==int(entered) and row.count('D')==f['onMap'] and row.count('C')==1+(3-int(bool(f['discovered'])))*f['onMap'])
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/infantry-position-effects-e1-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_position_discovery import InfantryPositionDiscoveryOracle
  oracle=InfantryPositionDiscoveryOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  require(oracle.counts['0x4c7220']==len(commands) and oracle.counts['discovery']==36 and oracle.counts['queue']==6 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),ordered_stores=['actor+59C=0','actor+59A=0','scratch_A35E24=0'],evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry position-discovery sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
