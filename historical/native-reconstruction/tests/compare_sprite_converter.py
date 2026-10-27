# SPDX-License-Identifier: GPL-3.0-or-later
"""Two live converter word owners through complete original49EEA0 calls."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from compare_building_sprite_pixels import verify
from original_results import python_closure
ORIGINAL=('tests/compare_sprite_converter.py','tests/original_sprite_converter.py')
NATIVE=('src/render/Scenery.hpp','src/render/Scenery.cpp','tests/sprite_converter_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(actual_complete_wrapper=True,actual_zero_word17c_store=True,two_converter_owners=True,null_before_word_store=True,clipped_draw_still_stores=True,actual_raw_rle_pixels=True,converter_lifetime=False,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Sprite converter evidence/domain differs')
def scenarios():
 for fmt in (1,3):
  for nulls in (0,1,2,5,10,15):
   for clips in (0,3,15):
    for initial in (-2147483648,-1,0,0x12345678):
     for gradient in (0,2):yield 'interleaved_null_clipped_flags_and_pixels',[fmt,nulls,clips,initial,gradient]
def parse(v):
 require(len(v)==5 and v[0] in (1,3) and 0<=v[1]<=15 and 0<=v[2]<=15 and -2**31<=v[3]<2**31 and v[4] in (0,2));return v
def validate_row(row,cmd):
 index=0
 for call in range(4):
  if not cmd[1]&(1<<call):
   require(row[index]=='W' and int(row[index+1])==call%2);int(row[index+2]);index+=3
  require(row[index]=='R');[int(v) for v in row[index+1:index+35]];require(len(row[index:index+35])==35);index+=35
 require(index==len(row))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_sprite_converter.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_sprite_converter import SpriteConverterOracle
  oracle=SpriteConverterOracle(a.exe,[0]*768,allow_patched=True);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),complete_wrapper_calls=len(commands)*4,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(' '.join(map(str,c)) for c in commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,commands[i],got,want))
 require(current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'sprite converter word sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
