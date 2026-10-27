#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original message font metrics and prefix-fitting comparison."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_message_font import verify
NATIVE=('src/sim/MessageFontMetrics.hpp','tests/message_font_vectors.cpp')
ORIGINAL=('tests/original_message_font.py','tools/verify_message_font.py','tests/compare_message_font.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_measurement_4314B0=True,complete_width_wrapper_431690=True,complete_prefix_fitting_431710=True,actual_glyph_index_and_width_reads=True,initial_font_associations_supplied=True,message_insertion_recovered=False,font_loader_and_drawing_recovered=False,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('Message font input/evidence differs')
def encoded(text):return text.encode('utf-16le','surrogatepass').hex() if text else '-'
def command(op='M',present=1,hasText=1,fallback=-1,line=12,tab=8,spacing=0,stride=4,base=0x3732000,limit=0,max=0,wrap=0,output=3,text='',rows=None):
 if rows is None:rows=[(32,1,3),(97,2,4),(98,3,6),(99,4,5),(120,5,8),(256,6,7),(55296,7,9),(65535,8,2)]
 return ' '.join([op,*map(str,(present,hasText,fallback,line,tab,spacing,stride,base,limit,max,wrap,output,len(rows))),encoded(text),*[str(v) for row in rows for v in row]])
def parse(cmd):
 p=cmd.split();require(len(p)>=15 and p[0] in ('M','W','F'));values=list(map(int,p[1:14]));present,hasText,fallback,line,tab,spacing,stride,base,limit,max,wrap,output,n=values
 require(present in (0,1) and hasText in (0,1) and -1<=fallback<=255 and all(-2**31<=v<2**31 for v in (line,tab,spacing,limit)) and all(0<=v<2**32 for v in (stride,base,max,wrap)) and 0<=output<=4 and 0<=n<=32 and len(p)==15+n*3)
 try:text=b'' if p[14]=='-' else bytes.fromhex(p[14])
 except ValueError:raise ValueError('Message font UTF16 bytes differ')
 require(len(text)%2==0 and len(text)<=254);rows=[]
 for i in range(n):
  code,index,width=map(int,p[15+i*3:18+i*3]);address=(base+stride*(index-1))&0xffffffff if index else 0;require(0<=code<=65535 and 0<=index<=65535 and 0<=width<=255 and (not address or 0x3732000<=address<0x3733000));rows.append((code,index,width))
 return dict(op=p[0],present=present,hasText=hasText,fallback=fallback,line=line,tab=tab,spacing=spacing,stride=stride,base=base,limit=limit,max=max,wrap=wrap,output=output,rows=rows,text=text)
def scenarios():
 for present,hasText in ((0,0),(0,1),(1,0)):
  for output in range(5):
   for op in ('M','W','F'):yield 'absent_primary_or_text_and_output_order',command(op,present=present,hasText=hasText,output=output,text='a',limit=7)
 texts=('', 'a','ab','aaab','a b','a  b x',' a','a\tb','a\rb','a\nb','a\r\nb','a\r\rb','a b\ncxx','\u0100\ud800\uffff','? a?','a\0b')
 for fallback in (-1,0,7):
  for spacing in (-6,0,3):
   for text in texts:
    for limit in (-1,0,1,6,12,100):
     for op in ('M','W'):yield 'complete_multiline_width_height_and_wrapper',command(op,fallback=fallback,spacing=spacing,text=text,limit=limit)
     for maximum,wrap in ((0,0),(0,1),(2,1),(3,0),(0,256)):yield 'complete_prefix_count_overflow_and_whitespace_retreat',command('F',fallback=fallback,spacing=spacing,text=text,limit=limit,max=maximum,wrap=wrap)
 for op in ('M','W','F'):
  for output in range(5):
   for tab in (-8,-3,3,2147483647):yield 'signed_tab_and_output_alias',command(op,tab=tab,spacing=-3,output=output,text='a\tb\t',limit=100,wrap=1)
  for line,spacing in ((2147483647,2147483647),(-2147483648,-2147483648)):
   yield 'wrapped_signed_dimensions',command(op,line=line,spacing=spacing,text='aa\ra\n',limit=0)
  for fallback in (-1,0,255):
   yield 'computed_zero_glyph_pointer_falls_back',command(op,stride=16,base=0xfffffff0,fallback=fallback,text='aa?',rows=[(97,2,9)],limit=100)
   yield 'zero_stride_aliases_glyph_bytes',command(op,stride=0,fallback=fallback,text='ab',rows=[(97,65535,3),(98,1,7)],limit=100)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_message_font.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and 'R' in row and 'FW' in row and 'FH' in row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_message_font import MessageFontOracle
  oracle=MessageFontOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x4314b0','0x431690','0x431710')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Message font sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
