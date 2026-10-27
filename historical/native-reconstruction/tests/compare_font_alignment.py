#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original RGB/alignment caller through actual text-to-pixels."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_font_alignment import verify
FONT_SHA='ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f'
NATIVE=('src/render/FontAlignment.hpp','src/render/FontText.hpp','src/render/FontGlyph.hpp','src/assets/GameFont.hpp','src/assets/GameFont.cpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/sim/MessageFontMetrics.hpp','tests/font_text_vectors.cpp')
ORIGINAL=('tests/original_font_alignment.py','tests/original_font_text.py','tests/original_font_glyph.py','tools/verify_font_alignment.py','tests/compare_font_alignment.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_RGB_alignment_parent=True,actual_text_glyph_metrics_setters_binding=True,distinct_default_explicit_fonts_and_surface_identities=True,initial_records_globals_colors_surface_SetRect_supplied=True,diagnostic_late_box_mutations=True,message_consumer_recovered=False,production_UI_enabled=False)
import compare_font_text as base
def require(v):
 if not v:raise ValueError('Font alignment input/evidence differs')
PREFIX=('enabled','fontChoice','surfaceChoice','rgb','horizontal','vertical','boxX','boxY','boxW','boxH','diagnostic')
def command(text='a b?X\tab',enabled=1,fontChoice=0,surfaceChoice=0,rgb=0x123456,horizontal=0,vertical=0,box=(2,2,24,16),diagnostic=0,**kwargs):
 common=base.command(text=text,clipping=kwargs.pop('clipping',0),**kwargs).split(' ',1)[1]
 return ' '.join(map(str,('A',enabled,fontChoice,surfaceChoice,rgb,horizontal,vertical,*box,diagnostic)))+' '+common
def scenarios():
 for horizontal in (-1,0,1,2,3,4,5):
  for vertical in (-1,0,1,2,3,4):
   for font in (0,1):
    for surface in (0,1):yield 'all_alignment_modes_distinct_font_and_surface_defaults',command(horizontal=horizontal,vertical=vertical,fontChoice=font,surfaceChoice=surface)
 for text in ('','a','ab','a b','a\r\nb','a\tb','a\0b'):
  for reveal in (0,1,3,-1):
   for count in (0,2):yield 'actual_measure_then_text_limits_reveal_and_controls',command(text=text,reveal=reveal,count=count,horizontal=1,vertical=1)
 for rgb in (0,0xffffffff,0xff0000,0x00ff00,0x0000ff,0xabcdef,0x12345678):
  for packing in ((11,3,0,3,5,2),(10,3,0,3,5,3),(0,0,8,0,16,0),(32,40,15,33,7,34)):
   for reveal in (0,4):yield 'packed_RGB_and_actual_fade_pixels',command(text='aaaaaaa',rgb=rgb,reveal=reveal,**dict(zip(('rL','rR','bL','bR','gL','gR'),packing)))
 for enabled in (0,2,255):
  for present in (0,1):
   for font in (0,1):
    if enabled and not present and not font:continue
    for surface in (0,1):yield 'early_gate_and_nonzero_flag_font_selection',command(enabled=enabled,fontPresent=present,fontChoice=font,surfaceChoice=surface)
 for w in (-2147483648,-1,0,1,2,25,2147483647):
  for h in (-2147483648,-1,0,1,2147483647):
   for horizontal in (1,2,3,4):
    for vertical in (1,2,3):yield 'signed_wrapped_alignment_and_inclusive_clip_no_raster',command(text='',box=(2,2,w,h),horizontal=horizontal,vertical=vertical)
 for w,h in ((3,5),(4,6),(23,15),(24,16)):
  for horizontal in (1,2,3,4):
   for vertical in (1,2,3):yield 'odd_even_signed_alignment_pixels',command(text='ab',box=(2,2,w,h),horizontal=horizontal,vertical=vertical)
 for diagnostic in (0,1):
  for font in (0,1):
   for surface in (0,1):
    for mutation in (0,1,2):yield 'saved_pen_sizes_late_clip_xy_and_surface_services',command(diagnostic=diagnostic,fontChoice=font,surfaceChoice=surface,mutation=mutation,horizontal=1,vertical=1)
 for font in (0,1):
  for reveal in (0,2,8):
   for text in ('Hello','a\tb\rX','?X\uffff'):yield 'stock_GAME_FNT_complete_alignment_pixels',command(stock=1,fontChoice=font,reveal=reveal,text=text)
def parse(cmd,stock=b''):
 p=cmd.split();require(len(p)>len(PREFIX)+1 and p[0]=='A');prefix=dict(zip(PREFIX,map(int,p[1:len(PREFIX)+1])));f=base.parse('J '+' '.join(p[len(PREFIX)+1:]),stock)
 require(0<=prefix['enabled']<=255 and prefix['fontChoice'] in (0,1) and prefix['surfaceChoice'] in (0,1) and 0<=prefix['rgb']<2**32 and prefix['diagnostic'] in (0,1))
 for k in ('horizontal','vertical','boxX','boxY','boxW','boxH'):require(-2**31<=prefix[k]<2**31)
 require(not(prefix['enabled'] and not prefix['fontChoice'] and not f['fontPresent']))
 f.update(prefix);f['op']='A';f['box']=[prefix[k] for k in ('boxX','boxY','boxW','boxH')];return f
def identities(a):
 paths=python_closure(ROOT/'tests/compare_font_alignment.py',{'sources':dict.fromkeys(ORIGINAL)})
 require(hash_file(a.font_file)==FONT_SHA)
 return dict(original=dict(font_sha256=hash_file(a.font_file),inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and len(row)==32 and row[0]=='R' and row[2]=='B' and row[4]=='T' and row[6]=='S' and row[15]=='D' and row[24]=='Q' and row[29]=='E')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','font-file'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_font_alignment import FontAlignmentOracle
  oracle=FontAlignmentOracle(a.exe);stock=a.font_file.read_bytes();commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd,stock)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x5fe1b0','0x431430','0x431450','0x431460','0x4318e0','0x432000','0x431cc0','0x4314b0','0x63cf20','0x4320b0','0x432150','0x432350','supplied.SetRect','supplied.U')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.font_file)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Font alignment sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
