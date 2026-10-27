#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Infantry Mark/membership with actual visibility and discovery."""
import argparse,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_membership_discovery import verify
from compare_infantry_membership import source_closure,plane_data
import compare_unit_membership_discovery as parent
from compare_unit_membership import row,RECORDS
NATIVE=(*source_closure(),'src/sim/UnitDiscovery.cpp','src/sim/MapVisibility.cpp')
ORIGINAL=('tests/compare_infantry_membership_discovery.py','tests/original_infantry_membership_discovery.py','tools/verify_infantry_membership_discovery.py')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_Infantry_Mark_membership_visibility_discovery=True,null_Tag_initial_records_recalculation_atexit_supplied=True,full_Walk_sight_schedule=False)
def require(v):
 if not v:raise ValueError('Invalid Infantry membership discovery evidence/input')
def parse(command):
 require(command.startswith('D '));return parent.parse('J '+command[2:])
def command(**kw):return 'D '+parent.command(**kw)[2:]
def scenarios(planes):
 for mode,current,primary,secondary,level in itertools.product((0,1,-1),(0,1),(0,8),(0,2),(-1,0,4)):
  fields=parent.FIELDS.copy();fields[:4]=[primary]*4;records=[r.copy() for r in RECORDS]
  for r in records:r[0]=level;r[2]=secondary
  yield 'complete_Infantry_Mark_visibility_discovery_repeated_floor_and_House',command(fields=fields,header=[0,0,1,mode,0,0,current,128,0],records=records,planes=planes,rows=[row(root=4,mode=m,z=level*104+128) for m in (1,0,1,0)])
 for current,owner,mission,human,control in itertools.product((0,1),(0,1),(-1,14,15,19),(0,255),(0,128)):
  fields=parent.FIELDS.copy();fields[4:8]=[human,control,human,control];fields[10:13]=[owner,mission,14]
  yield 'actual_Infantry_Mission_and_House_discovery_children',command(fields=fields,header=[0,0,255,1,0,0,current,128,0],planes=planes,rows=[row(root=r) for r in (2,3,2,3)])
 for upper,alternate in itertools.product((0,1,255),(0,255)):
  fields=parent.FIELDS.copy();fields[13:]=[upper,upper,alternate]
  yield 'raw_discovery_bytes_and_alternate_list',command(fields=fields,header=[0,0,1,1,0,0,0,128,0],planes=planes,rows=[row(root=r,alt=alternate) for r in (2,3,2)])

def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_membership_discovery.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE},native_inputs={'render_data':hash_file(a.render_data)})
def validate(e,r,f,current,a):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios(plane_data(a.exe)));require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('S')==len(parse(cmd)[-1]))
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/infantry-membership-vectors');p.add_argument('--render-data',type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,a);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_membership_discovery import InfantryMembershipDiscoveryOracle
  oracle=InfantryMembershipDiscoveryOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(plane_data(a.exe)):commands.append(cmd);labels.append(label);expected.append(oracle.run_joined(*parse(cmd)))
  generation=time.monotonic()-now;require(all(oracle.entries[hex(root)]>0 for root in (0x4c2e60,0x54ab70,0x54af70,0x473b30,0x568140,0x5683c0,0x6c2440,0x594cb0)) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.entries),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-10):j+25],want[max(0,j-10):j+25]))
 comparison=time.monotonic()-now;guard=subprocess.run([str(a.native),str(a.render_data)],input='D 0\n',capture_output=True,text=True);require(guard.returncode!=0 and bool(guard.stderr.strip()) and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry membership discovery sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
