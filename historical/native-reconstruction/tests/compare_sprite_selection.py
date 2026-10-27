# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete6D1480 with original field/call ordering and two House owners."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from verify_sprite_selection import verify
from original_results import python_closure
ORIGINAL=('tests/compare_sprite_selection.py','tests/original_sprite_selection.py')
NATIVE=('src/render/SpriteConverterSelection.hpp','tests/sprite_selection_vectors.cpp')
SOURCES=ORIGINAL+NATIVE+('tools/verify_sprite_selection.py',)
FLAGS=dict(complete_selection6d1480=True,saved_owner_index=True,two_houseCC_calls=True,wrapped_scaled_offsets=True,type_override=True,virtual_children_and_startup_supplied=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Sprite selection evidence/domain differs')
def scenarios():
 for over in (0,1):
  for own in (0,1,2):
   for pred in (0,1,128,255):
    for first,second in ((0,0),(1,1),(1,2),(2,1),(2,2)):
     for alt in (0,2):
      for mutation in range(5):
       for null in (0,1):yield 'tables_late_fields_repeated_CC_null_converter',[over,own,pred,first,second,alt,mutation,null]
 # The negative index is read/saved but not used on the alternate path.
 for second in (1,2):
  for mutation in (0,2,3,4):
   if second==2 or mutation in (2,3):yield 'unused_negative_saved_index',[0,-1,0,1,second,2,mutation,0]
 for index in (1073741824,1073741825,-2147483648,-1073741822):
  for over in (0,1):
   for pred in (0,128):
    yield 'wrapped_owner_scaled_offset',[over,index,pred,0,0,0,0,0]
  for second in (1,2):
   yield 'wrapped_alternate_scaled_offset',[0,index,0,1,second,index,0,0]
def parse(v):
 require(len(v)==8 and all(isinstance(n,int) for n in v))
 over,own,pred,first,second,alt,mutation,null=v
 require(over in (0,1) and -2**31<=own<2**31 and 0<=pred<=255 and 0<=first<=2 and 0<=second<=2 and -2**31<=alt<2**31 and 0<=mutation<=4 and null in (0,1));return v
def validate_row(row,cmd):
 require(row.count('F')==1);i=row.index('F');require(i%3==0 and len(row)==i+7)
 for j in range(0,i,3):require(int(row[j]) in (1,2));int(row[j+1]);int(row[j+2])
 for v in row[i+1:]:int(v)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_sprite_selection.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);validate_row(row,cmd)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_sprite_selection import SpriteSelectionOracle
  oracle=SpriteSelectionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands));require(current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),complete_selection_calls=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(' '.join(map(str,c)) for c in commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,commands[i],got,want))
 require(current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'sprite selection sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
