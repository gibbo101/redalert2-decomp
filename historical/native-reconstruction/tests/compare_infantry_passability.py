#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete base occupied passability with Infantry residents."""
import argparse,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_passability import verify
NATIVE=('src/assets/OccupiedCellPassability.hpp','src/assets/OccupiedCellPassability.cpp','src/assets/MapOverlay.hpp','src/assets/MapOverlay.cpp','tests/occupied_cell_vectors.cpp')
ORIGINAL=('tests/compare_infantry_passability.py','tests/original_infantry_passability.py','tools/verify_infantry_passability.py')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_passability_with_actual_Infantry_kind=True,initial_records_supplied=True,full_movement_original_proof=False)

from compare_occupied_cell import HEADER,command

def require(v):
 if not v:raise ValueError('Invalid Infantry passability evidence/input')
def parse(cmd):
 # Same bounded shape/header/list grammar, admitting the verified Infantry leaf.
 from compare_occupied_cell import parse as old_parse
 tokens=cmd.split();v=list(map(int,tokens[1:]));require(tokens[0]=='P' and len(v)>=31)
 actors=[v[i:i+8] for i in range(31,len(v),8)];require(all(len(a)==8 for a in actors))
 # Validate original grammar with Infantry represented by Unit only for syntax.
 check=v[:31]+[n for a in actors for n in ([1,*a[1:]] if a[0]==15 else a)]
 old_parse('P '+' '.join(map(str,check)))
 return v[:31],actors

def scenarios():
 def gi(next=-1):return [15,next,255,255,255,-2147483648,7,7]
 for count in range(1,9):
  yield 'Infantry_primary_Next_chain_ignores_type_House_mission',command(actors=[gi(i+1 if i+1<count else -1) for i in range(count)])
 for kind in (1,6,36):
  for position,flag,theater in itertools.product(range(3),(0,1,255),(0,1)):
   h=HEADER.copy();h[27]=theater;actors=[gi(1),gi(2),gi()];actors[position]=[kind,position+1 if position<2 else -1,1,flag,flag,0,7,8]
   yield 'mixed_Infantry_Building_Unit_Terrain_order',command(h,actors)
 for land,speed,mode in itertools.product((0,2,6,10),(0,0x3c23d70a,0x3f800000,0x7fc00001),range(6)):
  h=HEADER.copy();h[9]=land;h[16:27]=[speed]*11
  if mode:h[10:16]=[1,land,int(mode==1),int(mode==2),int(mode==3),int(mode==4)]
  yield 'early_land_speed_overlay_gates_before_Infantry',command(h,[gi(1),gi()])
 for shape in ([0,0,0,0,0],[80,0,0,1,1]):
  h=HEADER.copy();h[:5]=shape;yield 'permission_before_Infantry',command(h,[gi()])

def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_passability.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current,a):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('R')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/occupied-cell-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,a);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_passability import InfantryPassabilityOracle
  oracle=InfantryPassabilityOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(*parse(cmd)))
  generation=time.monotonic()-now;require(oracle.entries['0x478f40']>0 and oracle.entries['0x509800']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.entries),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-10):j+25],want[max(0,j-10):j+25]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry passability sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
