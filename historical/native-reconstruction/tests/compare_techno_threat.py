#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Stock Techno threat with actual type/kind/Building getter differential proof."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_techno_threat import verify
NATIVE=('src/sim/TechnoThreat.hpp','tests/techno_threat_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_techno_threat.py','tools/verify_techno_threat.py','tests/compare_techno_threat.py','tests/test_techno_threat.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_6D3E50_and_4532F0=True,actual_stock_type_kind_getters=True,initial_fields_and_associations_supplied=True,House_grid_or_runtime_adoption=False)
def require(ok):
 if not ok:raise ValueError('Techno threat evidence/input differs')
def fixture():return dict(root=0,kind=6,present=1,value=17,field=3,multiplier=5)
def command(f):return 'T '+' '.join(str(f[k]) for k in ('root','kind','present','value','field','multiplier'))
def parse(cmd):
 t=cmd.split();require(len(t)==7 and t[0]=='T');v=list(map(int,t[1:]));f=dict(zip(('root','kind','present','value','field','multiplier'),v));require(f['root'] in (0,1) and f['kind'] in (6,15) and f['present'] in (0,1) and all(-2**31<=f[k]<2**31 for k in ('value','field','multiplier')));return f
def scenarios():
 edges=(-2**31,-65537,-1,0,1,2,65537,2**30,2**31-1)
 for kind in (6,15):
  for present in (0,1):
   for value in edges:
    for field in edges:
     for multiplier in edges:
      f=fixture();f.update(kind=kind,present=present,value=value,field=field,multiplier=multiplier);yield 'stock_type_kind_saved_value_signed_wrapping',command(f)
 for value in edges:
  f=fixture();f.update(root=1,field=value);yield 'complete_direct_Building_getter',command(f)
 rng=random.Random(0x6d3e50)
 for _ in range(128):
  f=fixture();f.update(kind=rng.choice([6,15]),value=rng.randrange(-2**31,2**31),field=rng.randrange(-2**31,2**31),multiplier=rng.randrange(-2**31,2**31));yield 'deterministic_full_width_fields',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_techno_threat.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));prefix=[] if f['root'] else ['E','128']+(['E','44'] if f['present'] else [])
 require(row[:-2]==prefix and len(row)==len(prefix)+2 and row[-2]=='R' and -2**31<=int(row[-1])<2**31)
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_techno_threat import TechnoThreatOracle
  oracle=TechnoThreatOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x6d3e50,0x4532f0,0x6c12c0,0x506950,0x453c60,0x509800,0x453c40)) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Stock Techno threat sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
