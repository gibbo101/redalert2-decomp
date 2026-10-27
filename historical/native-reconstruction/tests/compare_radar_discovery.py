#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original signed-count radar discovery and shared primary query."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_discovery import verify
NATIVE=('CMakeLists.txt','src/sim/MapVisibility.hpp','src/sim/MapVisibility.cpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp','tests/radar_discovery_vectors.cpp')
ORIGINAL=('tests/original_radar_discovery.py','tools/verify_radar_discovery.py','tests/compare_radar_discovery.py','tests/test_radar_discovery.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_count568280=True,actual_primary_neighbor_word_lookup=True,shared_cells_and_fallback=True,initial_state_and_direction_supplied=True,production_or_SDL_adoption=False)
def require(v):
 if not v:raise ValueError('Radar discovery input/evidence differs')
def command(f=None):return 'V '+' '.join(map(str,f if f is not None else [104,256,256,0,0,513,1,1,0,2,1,1026,2,2,8,0,1,-1,0,0,0,0,-1,-1,-7,5,0,0,1]))
def parse(cmd):
 t=cmd.split();require(len(t)==30 and t[0]=='V');f=list(map(int,t[1:]));require(all(-2**31<=v<2**31 for v in f[:4]) and f[0]!=0 and not(f[0]==-1 and f[3]==-2**31) and f[4] in (0,1,2));slots=[]
 for i in range(4):
  slot,x,y,a,b,c=f[5+6*i:11+6*i];require(-1<=slot<262144 and -32768<=x<=32767 and -32768<=y<=32767 and 0<=a<2**32 and 0<=b<2**32 and -2**31<=c<2**31)
  if slot!=-1:require(slot not in slots);slots.append(slot)
 return f
def scenarios():
 for z in (-2147483648,-729,-312,-208,-105,-104,-103,-1,0,1,103,104,105,208,312,729,2147483647):
  for count in (-2147483648,-1,0,1,2147483647):
   for flags in (0,8,0xffffffff):
    for order in (0,1,2):
     f=parse(command());f[3]=z;f[4]=order;f[10]=count;f[8]=flags;f[16]=count;f[28]=count;yield 'signed_height_count_and_independent_primary_flags',command(f)
 for x,y in ((-2147483648,2147483647),(-257,-255),(-1,0),(0,-1),(8388607,-8388608),(131072,0),(0,131072),(2147483647,-2147483648)):
  for z in (-104,0,104,312):
   for order in (0,1,2):
    f=parse(command());f[1:5]=[x,y,z,order];yield 'signed_division_word_wrap_combined_index_and_fallback',command(f)
 for stored in ((1,1),(32767,32767),(-32768,-32768),(512,0),(-512,2)):
  for a in (-1,0,1):
   for b in (-1,0,1):
    for order in (0,1,2):
     f=parse(command());f[3]=104;f[4]=order;f[5]=0;f[6:8]=stored;f[10]=a;f[16]=b;yield 'neighbor_uses_stored_coordinates_and_late_count',command(f)
 for divisor in (-2147483648,-104,-1,1,2147483647):
  for z in (-2147483647,-104,-1,0,1,104,2147483647):
   f=parse(command());f[0]=divisor;f[3]=z;f[4]=2;yield 'supplied_divisor_signed_extremes',command(f)
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list));i=0;returns=0
 while i<len(row):
  tag=row[i];i+=1
  if tag in ('i','w','f'):require(len(row)-i>=2 and all(-32768<=int(v)<=32767 for v in row[i:i+2]));i+=2
  elif tag in ('c','n'):
   require(len(row)-i>=2 and 0<=int(row[i])<=3 and (-2**31<=int(row[i+1])<2**31 if tag=='c' else int(row[i+1])==3));i+=2
  elif tag=='R':require(len(row)-i>=3 and int(row[i]) in (0,1) and all(-32768<=int(v)<=32767 for v in row[i+1:i+3]));i+=3;returns+=1
  else:raise ValueError('Unexpected discovery trace')
 require(returns==(1 if f[4]==0 else 2) and row[-4]=='R')
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_discovery.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_discovery import RadarDiscoveryOracle
  oracle=RadarDiscoveryOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(1 if parse(c)[4]==0 else 2 for c in commands) and all(oracle.counts[a]>0 for a in ('0x568280','0x568140','0x476ac0','0x548070')) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar discovery sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
