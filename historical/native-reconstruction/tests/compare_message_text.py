#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original RGB/alignment caller through actual text-to-pixels."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_message_text import verify
FONT_SHA='ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f'
NATIVE=('src/render/MessageText.hpp','src/render/FontAlignment.hpp','src/render/FontText.hpp','src/render/FontGlyph.hpp','src/assets/GameFont.hpp','src/assets/GameFont.cpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/sim/MessageFontMetrics.hpp','tests/font_text_vectors.cpp')
ORIGINAL=('tests/original_message_text.py','tests/original_font_alignment.py','tests/original_font_text.py','tests/original_font_glyph.py','tools/verify_message_text.py','tests/compare_message_text.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_scratch_scroll_segment_consumer=True,actual_CRT_stack_probe_fit_width_alignment_pixels=True,actual_zero_context_IME_update=True,nonzero_IME_fill_cursor_services_supplied=True,initial_records_globals_surface_SetRect_supplied=True,node_consumer_recovered=False,production_UI_enabled=False)
import compare_font_text as base
def require(v):
 if not v:raise ValueError('Message text input/evidence differs')
PREFIX=('enabled','rgb','boxX','boxY','boxW','boxH','caret','scroll','ime','mask','background','nullText','imeContext','compositionCursor','extra','suppression','highlight','cursorRgb')
def command(text='ab a?X',enabled=1,rgb=0x123456,box=(2,2,24,16),caret=0,scroll=0,ime=0,mask=0,background=1,nullText=0,imeContext=0,compositionCursor=0,extra=0,suppression=0,highlight=0xabcdef,cursorRgb=0x789abc,composition='',**kwargs):
 common=base.command(text=text,clipping=kwargs.pop('clipping',0),**kwargs).split(' ',1)[1]
 token=''.join(f'{ord(c):04x}' for c in composition) or '-'
 return ' '.join(map(str,('C',enabled,rgb,*box,caret,scroll,ime,mask,background,nullText,imeContext,compositionCursor,extra,suppression,highlight,cursorRgb,token)))+' '+common
def scenarios():
 for text in ('','a','ab a?X','a\tba','a\r\nb','a\0b'):
  for caret in (-1,0,1,len(text),len(text)+1):
   for width in (0,5,12,24):yield 'scratch_copy_caret_validation_and_five_unit_scroll',command(text=text,caret=caret,box=(2,2,width,16))
 for scroll in (0,1,3,7,20,2047):
  for caret in (0,3,6,10):
   for width in (5,24):yield 'live_scroll_adjustment_and_prefix_fit',command(text='ab ab ab a',scroll=scroll,caret=caret,box=(2,2,width,16))
 for mask in (0,1):
  for background in (0,1):
   for ime in (0,1):
    for extra in (0,1):
     for suppression in (0,1):yield 'mask_background_zero_context_and_late_cursor_suppression',command(caret=3,mask=mask,background=background,ime=ime,extra=extra,suppression=suppression,composition='stale',compositionCursor=3)
 for composition in ('a','ab?X'):
  for cursor in (-1,0,1,len(composition),len(composition)+1):
   for caret in (0,2,6):
    for width in (5,12,24):yield 'supplied_nonzero_IME_actual_splice_scroll_segments_and_cursor',command(ime=1,imeContext=1,composition=composition,compositionCursor=cursor,caret=caret,box=(2,2,width,16))
 for stock in (0,1):
  for reveal in (0,1,3,8,-1):
   for mask in (0,1):yield 'stock_or_synthetic_pixels_with_per_segment_reveal',command(text='Hello a?X',caret=4,stock=stock,reveal=reveal,mask=mask)
 for enabled in (0,2,255):
  for nullText in (0,1):
   for mutation in (0,1,2):yield 'gate_null_source_and_surface_service_order',command(enabled=enabled,nullText=nullText,mutation=mutation,caret=2)
 for length in (2046,2047,2048,4096):
  for caret in (0,length):yield 'scratch_2048_copy_and_forced_final_zero',command(text='a'*length,caret=caret,box=(2,2,24,16))
 for caret,composition in ((2046,'a'),(2046,'ab'),(2047,'a')):yield 'composition_at_scratch_boundary',command(text='a'*2047,caret=caret,ime=1,imeContext=1,composition=composition,compositionCursor=1)
 for width in (-2147483648,-1,2147483647):
  for height in (-2147483648,-1,2147483647):yield 'wrapped_background_and_box_no_raster',command(text='',box=(2147483647,-2147483648,width,height))
def parse(cmd,stock=b''):
 p=cmd.split();require(len(p)>len(PREFIX)+2 and p[0]=='C');prefix=dict(zip(PREFIX,map(int,p[1:len(PREFIX)+1])));token=p[len(PREFIX)+1]
 require(token=='-' or len(token)%4==0);composition='' if token=='-' else ''.join(chr(int(token[i:i+4],16)) for i in range(0,len(token),4));require(len(composition)<=256 and '\0' not in composition)
 f=base.parse('J '+' '.join(p[len(PREFIX)+2:]),stock)
 require(0<=prefix['enabled']<=255 and all(prefix[k] in (0,1) for k in ('ime','mask','background','nullText','imeContext')) and 0<=prefix['scroll']<2048)
 for k in ('rgb','highlight','cursorRgb'):require(0<=prefix[k]<2**32)
 for k in ('boxX','boxY','boxW','boxH','caret','compositionCursor','extra','suppression'):require(-2**31<=prefix[k]<2**31)
 f.update(prefix);f.update(op='C',fontChoice=0,surfaceChoice=0,diagnostic=0,composition=composition.encode('utf-16le',errors='surrogatepass'));f['box']=[prefix[k] for k in ('boxX','boxY','boxW','boxH')];return f
def identities(a):
 paths=python_closure(ROOT/'tests/compare_message_text.py',{'sources':dict.fromkeys(ORIGINAL)})
 require(hash_file(a.font_file)==FONT_SHA)
 return dict(original=dict(font_sha256=hash_file(a.font_file),inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and len(row)==27 and row[0]=='R' and row[2]=='B' and row[4]=='T' and row[6]=='S' and row[15]=='Q' and row[20]=='Z')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','font-file'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_message_text import MessageTextOracle
  oracle=MessageTextOracle(a.exe);stock=a.font_file.read_bytes();commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd,stock)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x600830','0x783605','0x783622','0x783850','0x737e30','0x431710','0x431690','supplied.IME','supplied.fill','supplied.line','0x5fe1b0','0x431430','0x431450','0x431460','0x4318e0','0x432000','0x431cc0','0x4314b0','0x63cf20','0x4320b0','0x432150','0x432350','supplied.SetRect','supplied.U')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.font_file)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Message text sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
