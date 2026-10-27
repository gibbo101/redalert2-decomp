#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete House grid joined to actual stock actor threat differential proof."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
import compare_house_threat as base
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_actor_threat import verify,table_values
NATIVE=('src/sim/HouseActorThreat.hpp','src/sim/HouseThreat.hpp','src/sim/TechnoThreat.hpp','tests/house_actor_threat_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_house_actor_threat.py','tools/verify_house_actor_threat.py','tests/compare_house_actor_threat.py','tests/test_house_actor_threat.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_4F3420_grid=True,actual_stock_threat_type_kind=True,objectCell_and_initial_owners_supplied=True,production_and_diplomacy_adoption=False)
def require(ok):
 if not ok:raise ValueError('House threat evidence/input differs')
def fixture(tables):
 f=base.fixture(tables);f.update(rule=2,types=[17,31,65],threats=[[1,1,0],[2,1,3],[1,1,0]])
 for a,kind in zip(f['actors'],(15,6,15)):a[3:6]=[kind]*3
 return f
def command(f):
 return base.command(f)+' '+' '.join(map(str,[f['rule']]+f['types']+[v for row in f['threats'] for v in row]))
def parse(cmd):
 t=cmd.split();require(len(t)==125);f=base.parse(' '.join(t[:112]));v=list(map(int,t[112:]));f.update(rule=v[0],types=v[1:4],threats=[v[i:i+3] for i in range(4,13,3)])
 require(f['root']==0 and f['mutation'] in (0,3) and all(-2**31<=x<2**31 for x in [f['rule']]+f['types']))
 for t,present,field in f['threats']:require(1<=t<=3 and present in (0,1) and -2**31<=field<2**31)
 for a in f['actors']:require(a[3] in (6,15) and a[3:6]==[a[3]]*3)
 return f
def scenarios(tables):
 edges=(-2**31,-1,0,1,2,65537,2**30,2**31-1)
 for kind in (6,15):
  for present in (0,1):
   for field in edges:
    for rule in edges:
     f=fixture(tables);f['rule']=rule
     for a,t in zip(f['actors'],f['threats']):a[3:6]=[kind]*3;t[1:]=[present,field]
     yield 'actual_stock_threat_inside_grid',command(f)
 for value in edges:
  for count in (-2,0,1,3,8):
   f=fixture(tables);f.update(types=[value]*3,registryCount=count);yield 'saved_reverse_count_shared_type_signed_threat',command(f)
 for mode in (0,1,-1):
  for flags in ((0,0),(0,1),(1,0),(255,255)):
   for owner in range(5):
    for mask in (0,0xffffffff):
     f=fixture(tables);f['mode']=mode;f['houses'][0][2:4]=flags;f['houses'][0][4]=mask
     for a in f['actors']:a[6]=owner
     yield 'stored_Cell_owner_filter_and_Building_bypass',command(f)
 for value in range(256):
  f=fixture(tables);f['actors'][0][0]=value;f['actors'][1][1]=value;yield 'all_raw_active_flags',command(f)
 for x,y in ((-3,-3),(-4,4),(528,-4),(0,0),(511,511)):
  f=fixture(tables)
  for a in f['actors']:a[7:11]=[x,y,x,y]
  yield 'signed_Cell_projection_stencil',command(f)
 f=fixture(tables);f.update(ix=128,iy=128);yield 'invalid_stored_Cell_only',command(f)
 f=fixture(tables);f.update(mutation=3,registryCount=8);yield 'supplied_objectCell_child_late_owner_flags_and_Cell',command(f)
 rng=random.Random(0x4f6d3e50)
 for _ in range(64):
  f=fixture(tables);f.update(rule=rng.choice(edges),types=[rng.choice(edges) for _ in range(3)],registryCount=rng.randrange(-2,9),slots=[rng.randrange(1,4) for _ in range(8)])
  for a,t in zip(f['actors'],f['threats']):
   kind=rng.choice([6,15]);a[0:2]=[rng.randrange(2),rng.randrange(2)];a[3:6]=[kind]*3;a[6]=rng.randrange(5);t[:]=[rng.randrange(1,4),rng.randrange(2),rng.choice(edges)]
  yield 'deterministic_shared_type_actor_aliases',command(f)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_actor_threat.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0;rest=[]
 while i<len(row) and row[i] in ('E','V'):
  if row[i]=='E':
   require(i+2<len(row) and 1<=int(row[i+1])<=3 and int(row[i+2]) in (0x6d3e50,0x6c12c0,0x453c60,0x506950,0x453c40,0x509800));i+=3
  else:
   require(i+3<len(row) and row[i+2]=='420');rest.extend(row[i:i+4]);i+=4
 require(i<=8*8*3);base.validate_row(base.command(f),rest+row[i:])
def validate(e,r,f,current,tables):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios(tables));require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);tables=table_values(a.exe.read_bytes());runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,tables);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_actor_threat import HouseActorThreatOracle
  oracle=HouseActorThreatOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(tables):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x4f3420,0x54e370,0x6d3e50,0x4532f0,0x6c12c0,0x506950,0x453c60,0x509800,0x453c40)) and oracle.counts['supplied_420']>0 and oracle.counts['supplied_672']==0 and oracle.counts['supplied_44']==0 and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House actor threat sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
