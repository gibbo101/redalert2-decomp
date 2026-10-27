#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock coverage parents around explicitly supplied leaf services."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_techno_coverage import verify
NATIVE=('src/sim/TechnoCoverage.hpp','tests/techno_coverage_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_techno_coverage.py','tools/verify_techno_coverage.py','tests/compare_techno_coverage.py','tests/test_techno_coverage.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_6C83F0_and_6C86F0=True,ordered_Cell_counter_and_flag_stores=True,virtual_House_height_map_refresh_children_supplied=True,production_or_SDL_adoption=False)
def require(ok):
 if not ok:raise ValueError('Techno coverage evidence/input differs')
def fixture():return [1,0,1,2,1,1,0,0,0,1,65535,-65535,728,107,108,31,0,0,0,0,0,1,1]
def command(f):return 'C '+' '.join(map(str,f))
def parse(cmd):
 t=cmd.split();require(len(t)==24 and t[0]=='C');f=list(map(int,t[1:]));require(all(-2**31<=v<2**31 for v in f))
 require(all(f[k] in (0,1) for k in (0,19)) and all(0<=f[k]<=255 for k in (1,4,6,7,8,9)) and -128<=f[3]<=62 and -64<=f[2]<=62 and 0<=f[5]<=2 and 0<=f[20]<=5 and all(f[k] in (1,2) for k in (21,22)))
 return f
def scenarios():
 for add in (0,1):
  for active in (0,1,255):
   for current in (0,1,2):
    for allowed in (0,1,255):
     f=fixture();f[0]=add;f[1]=active;f[5]=current;f[4]=allowed;yield 'initial_guards_raw_bytes',command(f)
 for add in (0,1):
  for local,ally,flag in ((0,0,0),(1,0,0),(0,1,0),(0,0,1),(255,255,255)):
   for radius in (-64,-3,-2,-1,0,1,2,3):
    f=fixture();f[0]=add;f[1]=1-add;f[2]=radius;f[6:9]=[local,ally,flag];yield 'signed_radius_and_privilege',command(f)
 for add in (0,1):
  for count in (-2**31,-1,0,1,2,2**31-1):
   for cycle in (0,1):
    f=fixture();f[0]=add;f[1]=1-add;f[16:19]=[count]*3;f[19]=cycle;yield 'wrapping_counters_repeated_lookup',command(f)
 for add in (0,1):
  for mode in range(1,6):
   for cycle in (0,1):
    f=fixture();f[0]=add;f[1]=1-add;f[2]=0 if mode==2 else 1;f[20]=mode;f[19]=cycle;yield 'late_diagnostic_service_mutation',command(f)
 for typ in (-128,-3,-1,0,1,2,3):
  for add in (0,1):
   f=fixture();f[0]=add;f[1]=1-add;f[2]=0;f[3]=typ;yield 'signed_type_byte_and_zero_reload',command(f)
 for coord in (-2**31,-65537,-257,-256,-255,-1,0,1,255,256,65535,2**31-1):
  f=fixture();f[10:15]=[coord,coord,coord,coord,coord];yield 'saved_signed_projection_and_word_wrap',command(f)
 rng=random.Random(0x6c83f0)
 for _ in range(48):
  f=fixture();f[0]=rng.randrange(2);f[1]=1-f[0];f[2]=rng.randrange(-3,4);f[19]=rng.randrange(2);f[20]=rng.randrange(6)
  for k in (10,11,12,13,14,15,16,17,18):f[k]=rng.randrange(-2**31,2**31)
  yield 'deterministic_full_width_arithmetic',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_techno_coverage.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0
 while i<len(row) and row[i]!='R':
  if row[i]=='W':
   require(i+4<len(row) and row[i+1] in ('A','H','C'));owner=row[i+1];identity,offset,value=map(int,row[i+2:i+5]);require(-2**31<=value<2**31)
   require((owner=='A' and identity==0 and offset in (0x1fd,0x200)) or (owner=='H' and identity in (1,2) and offset==0x188 and 0<=value<=255) or (owner=='C' and identity in (0,1,2) and offset in (0x12c,0x130,0x134,0x13c)));i+=5
  else:
   require(i+1<len(row) and row[i]=='E');tag=row[i+1];sizes={'P':1,'T':1,'Z':2,'O':1,'L':2,'B':3,'C':3,'F':0,'D':1};require(tag in sizes);n=sizes[tag];require(i+2+n<=len(row));v=list(map(int,row[i+2:i+2+n]));require(all(-2**31<=x<2**31 for x in v))
   if tag in ('P','L','B'):require(0<=v[-1]<=255)
   if tag=='T':require(-128<=v[0]<=127)
   if tag=='O':require(v[0] in (1,2))
   if tag=='C':require(all(-32768<=x<=32767 for x in v[:2]) and v[2] in (0,1,2))
   if tag=='D':require(v==[2])
   i+=2+n
 require(i<len(row) and row[i]=='R' and len(row)-i==23);v=list(map(int,row[i+1:]));require(all(-2**31<=x<2**31 for x in v) and 0<=v[0]<=255 and v[5] in (0,1,2) and v[6] in (1,2) and all(0<=x<=255 for x in v[7:9]) and v[9] in (0,1))
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_techno_coverage import TechnoCoverageOracle
  oracle=TechnoCoverageOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x6c83f0,0x6c86f0)) and current==identities(a) and runner==hash_file(a.native))
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
