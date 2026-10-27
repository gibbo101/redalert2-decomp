#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete grid/threat/Object current-Cell/coordinate map differential proof."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
import compare_house_actor_threat as base
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_actor_threat_cells import verify,table_values
NATIVE=('src/sim/HouseActorThreatCells.hpp','src/sim/ObjectCurrentCell.hpp','src/sim/HouseActorThreat.hpp','src/sim/HouseThreat.hpp','src/sim/TechnoThreat.hpp','src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp','tests/house_actor_threat_cells_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_house_actor_threat_cells.py','tools/verify_house_actor_threat_cells.py','tests/compare_house_actor_threat_cells.py','tests/test_house_actor_threat_cells.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_4F3420_grid=True,actual_stock_threat_type_kind=True,actual_Object_currentCell_and_map=True,initial_owners_and_map_associations_supplied=True,production_and_diplomacy_adoption=False)
def require(ok):
 if not ok:raise ValueError('House threat evidence/input differs')
def map_fixture(f):
 f.update(mapCount=262144,mapMutation=0,coordinates=[[160*256,160*256,i*17] for i in range(3)],mapCells=[[128*512+128,128,128],[160*512+160,160,160],[-1,32,32]],fx=-7,fy=5)
 return f
def fixture(tables):return map_fixture(base.fixture(tables))
def command(f):
 extra=[f['mapCount'],f['mapMutation']]+[v for row in f['coordinates']+f['mapCells'] for v in row]+[f['fx'],f['fy']]
 return base.command(f)+' '+' '.join(map(str,extra))
def parse(cmd):
 t=cmd.split();require(len(t)==147);f=base.parse(' '.join(t[:125]));v=list(map(int,t[125:]));f.update(mapCount=v[0],mapMutation=v[1],coordinates=[v[i:i+3] for i in range(2,11,3)],mapCells=[v[i:i+3] for i in range(11,20,3)],fx=v[20],fy=v[21])
 require(f['mutation']==0 and 0<=f['mapCount']<=262144 and 0<=f['mapMutation']<=3 and all(-2**31<=n<2**31 for row in f['coordinates'] for n in row) and all(-32768<=f[k]<=32767 for k in ('fx','fy')))
 slots=[]
 for index,x,y in f['mapCells']:
  require(-1<=index<262144 and -32768<=x<=32767 and -32768<=y<=32767)
  if index>=0:require(index not in slots);slots.append(index)
 return f
def scenarios(tables):
 for label,cmd in base.scenarios(tables):
  f=base.parse(cmd)
  if f['mutation']==0:yield label+'_actual_map',command(map_fixture(f))
 for x,y in ((0,0),(-1,-1),(-255,-255),(-256,-256),(-768,768),(128*256,128*256),(160*256,160*256),(512*256,0),(-512*256,8*256),(-2**31,0),(2**31-1,0),(0,-2**31),(0,2**31-1),(2**31-1,2**31-1)):
  for count in (0,1,128*512+129,262144):
   f=fixture(tables);f['mapCount']=count
   for a in f['actors']:a[3:6]=[6]*3
   f['coordinates']=[[x,y,z] for z in (-2**31,0,2**31-1)]
   yield 'full_signed_coordinate_wrapped_index_and_shared_fallback',command(f)
 for mutation in (1,2,3):
  for count in (0,262144):
   f=fixture(tables);f.update(mapMutation=mutation,mapCount=count,registryCount=8,slots=[1,2,3,1,2,3,1,2])
   for a in f['actors']:a[3:6]=[6]*3
   f['coordinates']=[[-256,0,1],[160*256,160*256,2],[128*256,128*256,3]]
   if mutation==3:f['coordinates'][1]=[-256,0,2]
   yield 'diagnostic_first_miss_coordinate_count_or_backing_change',command(f)
 for resident in (False,True):
  f=fixture(tables)
  for a in f['actors']:a[3:6]=[6]*3
  if not resident:f['mapCells']=[[-1,0,0],[-1,0,0],[-1,0,0]]
  f['registryCount']=8;f['fx']=32767;f['fy']=-32768
  yield 'repeated_actors_two_queries_and_fallback_padding',command(f)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_actor_threat_cells.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row) and len(row)>=15 and row[-15]=='F');tail=list(map(int,row[-14:]));require(all(-32768<=n<=32767 for n in tail[:2]) and 0<=tail[2]<=262144 and tail[3] in (0,1) and tail[4] in (0,1) and all(-2**31<=n<2**31 for n in tail[5:]))
 i=0;rest=[];row=row[:-15]
 while i<len(row) and row[i] in ('E','L','B','C'):
  tag=row[i]
  if tag=='E':
   require(i+2<len(row) and 1<=int(row[i+1])<=3)
   if int(row[i+2])!=0x5d51e0:rest.extend(row[i:i+3])
   i+=3
  elif tag=='L':require(i+4<len(row) and 1<=int(row[i+1])<=3 and all(-2**31<=int(n)<2**31 for n in row[i+2:i+5]));i+=5
  elif tag=='B':require(i+1<len(row) and 0<=int(row[i+1])<2**32);i+=2
  else:require(i+1<len(row) and -1<=int(row[i+1])<=2);i+=2
 require(i<8*48 and i<len(row) and row[i]=='R');base.validate_row(base.command(f),rest+row[i:])
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_actor_threat_cells import HouseActorThreatCellsOracle
  oracle=HouseActorThreatCellsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(tables):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x4f3420,0x54e370,0x6d3e50,0x4532f0,0x6c12c0,0x506950,0x453c60,0x509800,0x453c40,0x5d51e0,0x548000)) and oracle.counts['supplied_420']==0 and oracle.counts['0x548000']==2*oracle.counts['0x5d51e0'] and oracle.counts['supplied_672']==0 and oracle.counts['supplied_44']==0 and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House actor threat Cells sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
