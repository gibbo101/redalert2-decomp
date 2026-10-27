#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete coverage parents call both actual radar refresh branches on shared owners."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_coverage_radar_refresh import verify
import compare_coverage_radar as coverage
import compare_radar_refresh as refresh
NATIVE=tuple(dict.fromkeys(coverage.NATIVE+refresh.NATIVE+('src/platform/CoverageRadarRefresh.hpp','tests/coverage_radar_refresh_vectors.cpp','tests/coverage_radar_refresh_guards.inc')))
ORIGINAL=('tests/original_coverage_radar_refresh.py','tools/verify_coverage_radar_refresh.py','tests/compare_coverage_radar_refresh.py','tests/test_coverage_radar_refresh.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(coverage.FLAGS,**{k:v for k,v in refresh.FLAGS.items() if k not in coverage.FLAGS},complete_stock_coverage_both_refresh_modes=True,alternating_add_remove_and_mode_schedule_supplied=True)
def require(v):
 if not v:raise ValueError('Coverage radar refresh input/evidence differs')
def command(f=None):
 if f is None:f=coverage.parse(coverage.command())+[0,2,2,0,165]
 return 'F '+' '.join(map(str,f))
def parse(cmd):
 t=cmd.split();require(len(t)==79 and t[0]=='F');f=coverage.parse('C '+' '.join(t[1:74]))+list(map(int,t[74:]));refresh.parse(refresh.command(f[:60]+f[73:]));return f
def scenarios():
 for start in (0,1):
  for i,(label,cmd) in enumerate(coverage.scenarios()):
   f=coverage.parse(cmd);f[15]=i%8;f[33]=1+i%2;f[34]=256+i%4
   yield 'complete_both_modes_'+label,command(f+[start,2 if i%2==0 else 1,i%3,i%2,(0,165,255)[i%3]])
 for label,cmd in refresh.scenarios():
  r=refresh.parse(cmd);base=coverage.parse(coverage.command());yield 'coverage_with_'+label,command(r[:60]+base[60:73]+r[60:])
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>535 and row[-535]=='Q');q=list(map(int,row[-534:-513]));require(0<=q[0]<=255 and -2**31<=q[1]<2**31 and all(0<=v<=255 for v in q[2:5]) and all(-2**31<=v<2**31 for v in q[5:]))
 body=row[:-535]+row[-513:];filtered=[];i=0
 while i<len(body):
  tag=body[i]
  if tag=='u':require(i+4<=len(body) and body[i+1] in ('A','C','H') and int(body[i+2]) in dict(A=(0x1fd,0x200),H=(0x188,),C=(0x12c,0x130,0x134,0x13c))[body[i+1]] and -2**31<=int(body[i+3])<2**31);i+=4
  elif tag in ('p','a','o','d'):require(i+2<=len(body) and -128<=int(body[i+1])<=255);i+=2
  elif tag in ('l','z'):require(i+3<=len(body) and all(-2**31<=int(v)<2**31 for v in body[i+1:i+3]));i+=3
  elif tag=='b':require(i+4<=len(body) and all(-1<=int(v)<=2 for v in body[i+1:i+3]) and int(body[i+3]) in (0,1));i+=4
  else:filtered.append(tag);i+=1
 refresh.validate_row(refresh.command(f[:60]+f[73:]),filtered)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_coverage_radar_refresh.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_coverage_radar_refresh import CoverageRadarRefreshOracle
  oracle=CoverageRadarRefreshOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(not any(oracle.counts.get(k,0) for k in ('supplied_coverage_type','supplied_coverage_permission','supplied_get28','supplied_set24','supplied_discovery0','supplied_discovery1','supplied_floor','supplied_type80','supplied_local','supplied_alliedObject','supplied_C0','supplied_CC','supplied_resolver')));require(oracle.audit_calls==sum(parse(cmd)[74] for cmd in commands) and all(oracle.counts[a]>0 for a in ('coverage_0x6c83f0','coverage_0x6c86f0','coverage_0x6a2970','zero_0x774f00','0x6324a0','mark_pixels','coverage_type','coverage_permission_0x450360','coverage_permission_0x6cd6e0','0x632000','0x634030','0x568140','0x568280','0x7741d0','0x774220')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,lazy_state_stores=oracle.lazyStores,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Coverage radar refresh sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
