#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete scheme resolver with actual locale-zero comparison."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_scheme_resolver import verify
NATIVE=('CMakeLists.txt','src/render/SchemeResolver.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceRefreshMarks.hpp','src/sim/StringLookup.hpp','tests/scheme_resolver_vectors.cpp')
ORIGINAL=('tests/original_scheme_resolver.py','tools/verify_scheme_resolver.py','tests/compare_scheme_resolver.py','tests/test_scheme_resolver.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_scheme_resolver=True,actual_locale_zero_comparison=True,late_registry_count_category_and_saved_slots=True,initial_records_and_associations_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Scheme resolver input/evidence differs')
def command(f=None):return 'S '+' '.join(map(str,f if f is not None else [0,1,6,0,0,0,0,6,1,1,1,1]))
def parse(cmd):
 t=cmd.split();require(len(t)==13 and t[0]=='S');f=list(map(int,t[1:]));require(0<=f[0]<8 and -2**31<=f[1]<2**31 and -2<=f[2]<=6 and f[3] in (0,1) and 0<=f[4]<=2 and 0<=f[5]<6 and 0<=f[6]<64 and -2<=f[7]<=6 and -2**31<=f[8]<2**31 and 0<=f[9]<8 and 0<=f[10]<6 and f[11] in (0,1));return f
def scenarios():
 for key in range(8):
  for category in (-2147483648,-1,0,1,2,2147483647):
   for count in (-2,-1,0,1,2,3,6):
    for table in (0,1):yield 'names_categories_signed_count_registry_and_repeated_calls',command([key,category,count,table,0,0,0,6,1,1,1,1])
 for stage in (1,2):
  for index in range(6):
   for mask in (1,2,4,8,16,32,63):
    for count in (-1,0,1,6):
     for key in (0,2,3,4,6):
      f=parse(command());f[0]=key;f[4:8]=[stage,index,mask,count];f[8:11]=[1,(key+1)%8,(index+1)%6];yield 'late_registry_count_name_category_and_saved_slots',command(f)
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list));i=0;returns=0
 while i<len(row):
  tag=row[i];i+=1
  if tag in ('T','U'):
   require(i+3<=len(row));index,record,value=map(int,row[i:i+3]);require(0<=index<6 and 0<=record<6 and (value in (-1,0,1) if tag=='T' else -2**31<=value<2**31));i+=3
  elif tag=='R':require(i<len(row) and -1<=int(row[i])<6);i+=1;returns+=1
  elif tag=='F':
   require(returns==1+f[11] and len(row)-i==27);v=list(map(int,row[i:]));require(v[0] in (0,1) and -2<=v[1]<=6 and v[2] in (0,1) and all(0<=x<8 for x in v[3:9]) and all(-2**31<=x<2**31 for x in v[9:15]) and all(0<=x<6 for x in v[15:]));return
  else:raise ValueError('Unexpected scheme trace')
 raise ValueError('Missing scheme final state')
def identities(a):
 paths=python_closure(ROOT/'tests/compare_scheme_resolver.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_scheme_resolver import SchemeResolverOracle
  oracle=SchemeResolverOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(1+parse(cmd)[11] for cmd in commands) and all(oracle.counts[a]>0 for a in ('0x663d30','0x781f20')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Scheme resolver sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
