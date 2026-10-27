# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building image getters predicate: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_image_selection import verify
ORIGINAL=('tests/compare_building_image_selection.py','tests/original_building_image_selection.py','tools/verify_building_image_selection.py')
NATIVE=('src/render/BuildingImage.hpp','src/render/BuildingImage.cpp','src/render/BuildingTypeBounds.hpp','src/assets/OverlayImage.hpp','src/sim/OriginalMath.hpp','tests/building_image_selection_vectors.cpp','src/render/BuildingImageSelection.hpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_primary_getter=True,complete_secondary_getter=True,actual_theater_transform=True,actual_generic_transform=True,actual_ftol=True,complete_image68_dispatcher=True,file_crt_lifetime_services_supplied=True,type_startup_supplied=True)
def require(v):
 if not v:raise ValueError('Building image getters evidence/domain differs')
from compare_building_image import command as getter_command,parse as getter_parse,scenarios as getter_scenarios
def command(stage=0,flag=0,**kwargs):return f'{stage} {flag} '+getter_command(**kwargs)
def parse(cmd):
 fields=cmd.split();require(len(fields)==22)
 stage,flag=map(int,fields[:2]);require(-2**31<=stage<2**31 and 0<=flag<=255)
 return [stage,flag,*getter_parse(' '.join(fields[2:]))]
def scenarios():
 for label,cmd in getter_scenarios():
  op=int(cmd.split()[0]);yield 'joined_'+label,f'{-1 if op==0 else 0} 128 '+cmd
 for stage in (0,1,-1,-2147483648,2147483647):
  for flag in (0,1,2,128,255):
   yield 'short_circuit_raw_stage_flag',command(stage=stage,flag=flag)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_image_selection.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1 and len(row)-row.index('F')==10)
 widths={'Q':2,'C':2,'K':2,'L':2,'D':2,'H':2,'T':0,'P':2,'S':3,'M':1,'R':1,'F':9}
 i=0
 while i<len(row):
  token=row[i];require(token in widths);n=widths[token];require(i+n<len(row))
  for j in range(1,n+1):
   if token!='C' or j!=2:int(row[i+j])
  i+=n+1
 require(i==len(row))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_image_selection import BuildingImageSelectionOracle
  oracle=BuildingImageSelectionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(parse(cmd)[19] for cmd in commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x44c5a0','0x458ce0','0x45e790','0x5d7bd0','0x5d7c20','0x77f110','load','cleanup')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building image selection sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
