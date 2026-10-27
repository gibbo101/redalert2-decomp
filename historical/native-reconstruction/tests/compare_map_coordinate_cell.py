#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential full-coordinate map lookup, including signed index aliases/misses."""
import argparse,json,random,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_coordinate_cell import verify
SOURCES=('src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp','src/assets/MapFloorHeight.hpp','src/assets/MapCellInputs.hpp','src/sim/OriginalMath.hpp',
 'tests/compare_map_coordinate_cell.py','tests/original_map_coordinate_cell.py','tests/map_coordinate_cell_vectors.cpp','tests/original_presentation.py','tests/original_foot_lit.py','tools/verify_map_coordinate_cell.py')
def command(count,indexes,queries):return 'C '+' '.join(map(str,[count,len(indexes),*indexes,len(queries),*[v for q in queries for v in q]]))
def parse(cmd):
 p=cmd.split();assert p[0]=='C';v=list(map(int,p[1:]));count,n=v[:2];assert 0<=count<=262144 and 0<=n<=64
 indexes=v[2:2+n];assert len(set(indexes))==n and all(0<=i<262144 for i in indexes)
 q=v[2+n];tail=v[3+n:];assert 1<=q<=4096 and len(tail)==q*3 and all(-2147483648<=i<=2147483647 for i in tail)
 return count,indexes,[tail[i:i+3] for i in range(0,len(tail),3)]
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Coordinate lookup engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Coordinate lookup identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Coordinate lookup counts differ')
 for c in e['commands']:
  try:parse(c)
  except (AssertionError,ValueError,IndexError):raise ValueError('Malformed coordinate lookup command') from None
def generate(a):
 from original_map_coordinate_cell import MapCoordinateCellOracle
 o=MapCoordinateCellOracle(a.exe);commands=[];expected=[];labels=[];rng=random.Random(0x548000)
 indexes=[0,1,2,511,512,513,65535,65536,131071,262143]
 edges=[-2147483648,-16777216,-131328,-131072,-257,-256,-255,-1,0,1,255,256,257,131071,131072,16777215,16777216,2147483647]
 queries=[[x,y,(-2147483648,0,2147483647)[(i+j)%3]] for i,x in enumerate(edges) for j,y in enumerate(edges)]
 queries+=[[x*256,y*256,17] for x,y in ((-1,1),(512,-1),(-512,1),(65536,0),(0,128),(0,512),(511,511))]
 for index in indexes:
  x,y=index%512,index//512
  queries.extend([[x*256+d,y*256+e,0] for d,e in ((0,0),(128,128),(255,255))])
 queries += [[rng.randint(-2147483648,2147483647),rng.randint(-2147483648,2147483647),rng.randint(-2147483648,2147483647)] for _ in range(128)]
 for count in (0,1,512,65536,262144):
  c=command(count,indexes,queries);parse(c);commands.append(c);expected.append(o.run(count,indexes,queries));labels.append('signed_full_division_wrapped_combined_index_supplied_count_and_shared_fallback')
 return commands,expected,labels,{'queries':o.audit_calls,'fallback_stores':o.writes,'original_initial_table_Cell_storage_supplied':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/map-coordinate-cell-vectors');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/coordinate-cell-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current);report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh coordinate lookup destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native coordinate lookup: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if actual!=expected:raise AssertionError('Coordinate lookup original/native results differ')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Coordinate lookup run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{result["queries"]:,} coordinate Cell queries: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
