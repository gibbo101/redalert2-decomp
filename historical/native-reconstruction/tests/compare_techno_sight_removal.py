#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete base Techno old-sight removal with portable C++."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_techno_sight_removal import verify
NATIVE=('src/sim/TechnoSight.hpp','src/sim/TechnoSightRemoval.hpp','src/sim/TechnoSightRemoval.cpp','tests/techno_sight_removal_vectors.cpp')
ORIGINAL=('tests/original_techno_sight_removal.py','tools/verify_techno_sight_removal.py','tools/verify_terrain_visibility.py','tests/compare_techno_sight_removal.py')
SOURCES=(*NATIVE,*ORIGINAL)
FLAGS=dict(complete_Techno_sight_removal_6D5E90=True,actual_actor_owner_country_and_active_state=True,exact_House_forwarding_and_reveal_arguments=True,reveal_area_54A110_supplied=True,visibility_increment_and_production_schedule=False)
KEYS=('enabled','countryFlag','active','x','y','z','range','arg1','arg2','arg3','house')
def require(v):
 if not v:raise ValueError('Techno sight-removal evidence/input differs')
def command(v):return 'R '+' '.join(str(v[k]) for k in KEYS)
def parse(cmd):
 p=cmd.split();require(len(p)==12 and p[0]=='R');v=dict(zip(KEYS,map(int,p[1:])));require(all(v[k] in (0,1) for k in ('enabled','countryFlag','active','house')))
 for k in ('x','y','z','range'):require(-2**31<=v[k]<2**31)
 for k in ('arg1','arg2','arg3'):require(0<=v[k]<2**32)
 return v
def scenarios():
 rng=random.Random(0x6d5e90);ranges=(-2**31,-1,0,1,5,2**31-1);arg3s=(0,1,0x100,0x101,0xffffff00,0xffffffff)
 for case in range(96):
  v=dict(enabled=0 if case%17==0 else 1,countryFlag=1 if case%19==0 else 0,active=(case//2)&1,x=rng.randint(-2**31,2**31-1),y=rng.randint(-2**31,2**31-1),z=rng.randint(-2**31,2**31-1),range=ranges[case%len(ranges)],arg1=(0x12345600|case),arg2=(0x80000000+case),arg3=arg3s[case%len(arg3s)],house=0 if case%3==0 else 1)
  yield 'gates_active_range_explicit_House_and_forwarded_arguments',command(v)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_techno_sight_removal.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('S')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/techno-sight-removal-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_techno_sight_removal import TechnoSightRemovalOracle
  oracle=TechnoSightRemovalOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts[hex(0x6d5e90)]==len(commands) and oracle.counts['supplied.reveal54A110']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Techno sight-removal sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
