#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Original successful fonT loading, fallback ownership and joined metric consumers."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_game_font import verify
FONT_SHA='ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f'
NATIVE=('src/assets/GameFont.hpp','src/assets/GameFont.cpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/sim/MessageFontMetrics.hpp','tests/game_font_vectors.cpp')
ORIGINAL=('tests/original_game_font.py','tools/verify_game_font.py','tests/compare_game_font.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(successful_fonT_constructor_loader=True,actual_fallback_creation=True,actual_metric_consumers=True,file_heap_SetRect_and_fill_supplied=True,alternate_FoNt_and_failures_recovered=False,message_insertion_recovered=False,drawing_recovered=False,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('Game font input/evidence differs')
def scenarios():
 for fill in (0,55,165,255):yield 'stock_GAME_FNT',f'G {fill}'
 for columns,rows in ((0,0),(0,3),(3,0),(1,1),(3,4),(4,3)):
  for count,x in ((0,0),(1,0),(2,1),(4,1)):
   for fill in (0,165):yield 'synthetic_fonT_dimensions_indices_fallback',f'S {fill} {columns} {rows} {count} {x}'
def parse(cmd,stock=b''):
 import struct
 p=cmd.split();require(bool(p) and p[0] in ('G','S'));require(len(p)==(2 if p[0]=='G' else 6));v=list(map(int,p[1:]));fill=v[0];require(0<=fill<=255)
 if p[0]=='G':return dict(file=stock,fill=fill)
 columns,rows,count,x=v[1:];require(all(0<=n<=4 for n in (columns,rows,count)) and x in (0,1));stride=columns*rows+1
 indices=[0]*65536
 if count:
  for code,index in ((32,1),(97,count),(65535,count)):indices[code]=index
  if x:indices[88]=1
 payload=bytes((i*7+fill)&255 for i in range(count*stride))
 blob=struct.pack('<7I',0x546e6f66,20,columns,rows,rows+1,count,stride)+struct.pack('<65536H',*indices)+payload
 return dict(file=blob,fill=fill)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_game_font.py',{'sources':dict.fromkeys(ORIGINAL)})
 require(hash_file(a.font_file)==FONT_SHA)
 return dict(original=dict(font_sha256=hash_file(a.font_file),inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and 'R' in row and len(row)==36 and row[0]=='D' and row[8]=='I' and row[10]=='G' and row[12]=='F')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','font-file'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_game_font import GameFontOracle
  oracle=GameFontOracle(a.exe);stock=a.font_file.read_bytes();commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd,stock)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x431040','0x431150','0x431ec0','0x4314b0','0x431690','0x431710')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.font_file)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Game font sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
