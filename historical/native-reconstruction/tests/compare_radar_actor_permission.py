#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock actor permission with explicit original-only reuse."""
import argparse,json,platform,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_actor_permission import verify
NATIVE=('src/render/RadarActorPermission.hpp','src/render/RadarActorPlacement.hpp','src/render/UnitTypeVisibility.cpp','tests/radar_actor_permission_vectors.cpp')
ORIGINAL=('tests/original_radar_actor_permission.py','tools/verify_radar_actor_permission.py','tests/compare_radar_actor_permission.py')
SOURCES=(*NATIVE,*ORIGINAL)
FLAGS=dict(complete_Infantry_and_Building_permission=True,actual_stock_local_alliance_veterancy=True,coordinate_visibility_height_2FC_dimension_probes_supplied=True,production_scheduling=False)
def require(v):
 if not v:raise ValueError('Actor marker input/evidence differs')
def bits(n):
 import struct
 return struct.unpack('<Q',struct.pack('<d',n))[0]
def command(**kw):
 d=dict(kind=0,aa6=0,aa7=0,flag325=0,discovered=0,vbits=bits(0.),houseMode=0,owner=1,human=0,control=0,alliance=0,mode=0,session=0,mission=0,height=0,v277=0,e289=0,p1=0,p2=0,secondary=0,eligible=1,width=2,heightDim=3,b5bd=0,b5b7=0,status=0x12345,mutation=0)
 require(not set(kw)-set(d));d.update(kw);return 'Q '+' '.join(map(str,d.values()))
def parse(cmd):
 t=cmd.split();require(len(t)==28 and t[0]=='Q');f=list(map(int,t[1:]));require(f[0] in (0,1) and f[7] in (0,1) and 0<=f[26]<=5 and 0<=f[5]<2**64)
 for i,v in enumerate(f):
  if i==5:continue
  require(-2**31<=v<2**31)
 for i in (1,2,3,4,8,9,15,16,23,24):require(0<=f[i]<=255)
 for i in (17,18,19,20):require(0<=f[i]<=511)
 return f
def scenarios():
 for kind,aa6,aa7,flag325,discovered in itertools.product((0,1),(0,255),(0,128),(0,255),(0,255)):
  yield 'type_actor_and_discovery_early_return_status_preservation',command(kind=kind,aa6=aa6,aa7=aa7,flag325=flag325,discovered=discovered)
 for kind,houseMode,owner,human,control in itertools.product((0,1),(0,1),(0,1),(0,128),(0,255)):
  yield 'actual_House_mode_raw_flags_and_pointer_identity',command(kind=kind,houseMode=houseMode,owner=owner,human=human,control=control,discovered=255)
 for vbits,v277,e289,height,eligible in itertools.product((bits(0.),bits(1.),bits(1.9999999999999998),bits(2.),bits(float('nan')),bits(float('inf')),bits(-1.)),(0,255),(0,128),(-21,-20,0),(0,1,256,511)):
  yield 'actual_promotion_intervals_and_height_threshold_status',command(vbits=vbits,v277=v277,e289=e289,height=height,eligible=eligible)
 for kind,mission,mode,p1,p2,eligible in itertools.product((0,1),(0,2),(0,1),(0,1,256,511),(0,1),(0,1)):
  yield 'primary_visibility_mode_short_circuit_and_2FC_low_byte',command(kind=kind,mission=mission,mode=mode,p1=p1,p2=p2,eligible=eligible)
 for session,secondary,height,eligible,alliance in itertools.product((0,4096),(0,1,256,511),(-21,-20),(0,1),(0,2)):
  yield 'secondary_session_gate_and_directed_alliance',command(session=session,secondary=secondary,height=height,eligible=eligible,alliance=alliance,mission=2)
 for b5bd,b5b7,mission,alliance in itertools.product((0,15,255),(0,255),(0,2),(0,2)):
  yield 'Building_numeric_flags_and_status_store',command(kind=1,b5bd=b5bd,b5b7=b5b7,mission=mission,alliance=alliance)
 for kind,mutation in itertools.product((0,1),range(1,6)):
  yield 'late_child_owner_coordinates_type_and_flags',command(kind=kind,mutation=mutation,mission=2,p1=1,p2=1)
 for width,heightDim in itertools.product((-2147483648,0,2147483647),(-2147483648,0,2147483647)):
  yield 'Building_wrapped_dimension_offsets',command(kind=1,width=width,heightDim=heightDim,p1=1,p2=1)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and row.count('R')==1);at=row.index('R');require(len(row)-at==3);list(map(int,row[at+1:]));i=0
 while i<at:
  n=dict(T=2,H=2,F=2,Y=4,X=3,P=5,S=5,V=1,E=1,L=2,B=2,W=2,M=2).get(row[i]);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_actor_permission.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-actor-permission-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_actor_permission import RadarActorPermissionOracle
  oracle=RadarActorPermissionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar actor permission sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
