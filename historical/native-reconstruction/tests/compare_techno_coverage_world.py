#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock coverage parents around explicitly supplied leaf services."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_techno_coverage_world import verify,scale_bits
import compare_techno_coverage as base
import struct,math
NATIVE=('src/platform/TechnoCoverageWorld.hpp','src/sim/TechnoCoverage.hpp','src/sim/RevealArea.cpp','src/sim/RevealArea.hpp','src/render/UnitTypeVisibility.cpp','tests/techno_coverage_world_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_techno_coverage_world.py','tools/verify_techno_coverage_world.py','tests/compare_techno_coverage_world.py','tests/test_techno_coverage_world.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_coverage_parents=True,actual_House_height_FTOL_and_packed_map=True,virtual_permission_type_owner_refresh_redraw_supplied=True,production_or_SDL_adoption=False)
def require(ok):
 if not ok:raise ValueError('Coverage world evidence/input differs')
def fixture(scale=4593671619917905920):return dict(base=base.fixture(),scale=scale,houses=[0,1,0,0,0,2,0,0,0])
def command(f):return 'J '+' '.join(map(str,[f['scale'],*f['base'],*f['houses']]))
def parse(cmd):
 t=cmd.split();require(len(t)==34 and t[0]=='J');n=list(map(int,t[1:]));require(0<=n[0]<2**64);scale=struct.unpack('<d',struct.pack('<Q',n[0]))[0];require(math.isfinite(scale) and abs(scale)<=1)
 f=dict(scale=n[0],base=base.parse('C '+' '.join(map(str,n[1:24]))),houses=n[24:]);h=f['houses'];require(-2**31<=h[0]<2**31)
 for at in (1,5):require(-2**31<=h[at]<2**31 and all(0<=x<=255 for x in h[at+1:at+3]) and 0<=h[at+3]<2**32)
 return f
def scenarios(scale):
 for label,cmd in base.scenarios():
  f=fixture(scale);f['base']=base.parse(cmd);yield 'actual_children_'+label,command(f)
 for mode in (0,1,-1):
  for index in (-1,0,1,31,32,-32):
   for human,control in ((0,0),(1,0),(0,255)):
    for add in (0,1):
     f=fixture(scale);f['base'][0]=add;f['base'][1]=1-add;f['base'][19]=1;f['houses']=[mode,index,human,control,2**32-1,1,0,0,0];yield 'actual_House_mode_index_mask_bytes',command(f)
 for coord in (-2**31,-65537,-256,-1,0,1,256,65535,2**31-1):
  for cycle in (0,1):
   f=fixture(scale);f['base'][10:13]=[coord,coord,coord];f['base'][19]=cycle;yield 'actual_projection_wrapping_and_shared_fallback',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_techno_coverage_world.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and len(row)>4 and row[-4]=='F');tail=list(map(int,row[-3:]));require(all(-32768<=v<=32767 for v in tail[:2]) and 0<=tail[2]<=100000);filtered=[];i=0
 while i<len(row)-4:
  if row[i:i+2]==['W','F']:
   require(i+4<len(row)-4 and row[i+2:i+4]==['0','36'] and -2**31<=int(row[i+4])<2**31);i+=5
  else:filtered.append(row[i]);i+=1
 base.validate_row(base.command(f['base']),filtered)
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_techno_coverage_world import TechnoCoverageWorldOracle
  oracle=TechnoCoverageWorldOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(scale):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x6c83f0,0x6c86f0,0x4f52b0,0x4e5540,0x6a2970,0x77f110,0x548070)) and current==identities(a) and runner==hash_file(a.native))
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
