#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock coverage parents around explicitly supplied leaf services."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_stock_techno_coverage import verify,scale_bits
import compare_techno_coverage_world as base
import struct,math
NATIVE=('src/sim/StockTechnoCoverage.hpp','src/sim/MissionBuildingTarget.hpp',*base.NATIVE[:-2],'tests/stock_techno_coverage_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_stock_techno_coverage.py','tools/verify_stock_techno_coverage.py','tests/compare_stock_techno_coverage.py','tests/test_stock_techno_coverage.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_coverage_stock_virtuals=True,actual_Building_availability=True,actual_House_height_FTOL_and_packed_map=True,House_power_refresh_redraw_initialization_supplied=True,production_or_SDL_adoption=False)
def require(ok):
 if not ok:raise ValueError('Stock coverage evidence/input differs')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def fixture(scale=4593671619917905920):return dict(world=base.fixture(scale),stock=[6,100,1,2,0,1,0,0,0,0,0,-2,0],power=bits(1.))
def command(f):return 'K '+base.command(f['world'])[2:]+' '+' '.join(map(str,[*f['stock'],f['power']]))
def parse(cmd):
 t=cmd.split();require(len(t)==48 and t[0]=='K');f=dict(world=base.parse('J '+' '.join(t[1:34])),stock=list(map(int,t[34:47])),power=int(t[47]));s=f['stock'];require(s[0] in (6,15) and all(-2**31<=s[k]<2**31 for k in (1,3,4,7)) and all(0<=s[k]<=255 for k in (2,5,6,8,9)) and s[10] in (0,1) and -128<=s[11]<=62 and s[12]==0 and 0<=f['power']<2**64);return f
def scenarios(scale):
 for label,cmd in base.scenarios(scale):
  for kind in (6,15):
   f=fixture(scale);f['world']=base.parse(cmd);f['stock'][0]=kind;yield 'stock_dispatch_'+label,command(f)
 for health in (-1,0,100):
  for enabled in (0,255):
   for count in (-2**31,0,1,2,2**31-1):
    for disabled in (-1,0,1):
     f=fixture(scale);f['world']['base'][2]=0;f['stock'][1:5]=[health,enabled,count,disabled];yield 'complete_Building_initial_availability',command(f)
 for ratio in (-math.inf,-1.,0.,math.nextafter(1.,0.),1.,math.nextafter(1.,2.),math.inf,math.nan):
  for count in (0,1,2):
   for mutation in (0,1):
    for operational in (0,255):
     f=fixture(scale);f['world']['base'][2]=0;f['stock'][3]=count;f['stock'][5:11]=[operational,1,1,1,0,mutation];f['power']=bits(ratio);yield 'actual_availability_power_unordered_late_type_count_owner',command(f)
 for flag in (0,1,255):
  for count in (-1,0,1):
   for special in (0,255):
    f=fixture(scale);f['world']['base'][2]=0;f['stock'][6:10]=[flag,count,flag,special];yield 'saved_type_flags_and_signed_type_count',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_stock_techno_coverage.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>4 and row[-4]=='V');v=list(map(int,row[-3:]));require(-2**31<=v[0]<2**31 and v[1] in (0,1) and v[2] in (0,1));filtered=[];i=0
 while i<len(row)-4:
  if row[i]=='G':require(i+1<len(row)-4 and int(row[i+1]) in (1,2));i+=2
  else:filtered.append(row[i]);i+=1
 base.validate_row(base.command(f['world']),filtered)
def validate(e,r,f,current,scale):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios(scale));require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);scale=scale_bits(a.exe.read_bytes());runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,scale);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_stock_techno_coverage import StockTechnoCoverageOracle
  oracle=StockTechnoCoverageOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(scale):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x6c83f0,0x6c86f0,0x4f52b0,0x4e5540,0x6a2970,0x77f110,0x548070,0x450360,0x6cd6e0,0x6c12c0,0x506950,0x453c60,0x6c7430)) and all(oracle.counts[k]==0 for k in ('supplied_0x30c','supplied_0x80','supplied_0x3c')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Techno coverage sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
