#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original glyph pixel writes and inclusive clipping."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_font_glyph import verify
FONT_SHA='ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f'
NATIVE=('src/render/FontGlyph.hpp','src/assets/GameFont.hpp','src/assets/GameFont.cpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/sim/MessageFontMetrics.hpp','tests/font_glyph_vectors.cpp')
ORIGINAL=('tests/original_font_glyph.py','tools/verify_font_glyph.py','tests/compare_font_glyph.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_glyph_raster=True,actual_inclusive_intersection=True,ordered_reads_and_pixel_writes=True,whole_surface_and_arena_guards=True,initial_font_surface_and_SetRect_supplied=True,text_drawing_recovered=False,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('Font glyph input/evidence differs')
def command(op='G',code=65,present=1,fallback=1,surface=1,index=1,width=9,rows=3,stride=3,pattern=71,x=4,y=3,color=-1,spacing=1,tab=64,origin=0,clipping=0,clip=(0,0,31,23)):
 return ' '.join(map(str,(op,code,present,fallback,surface,index,width,rows,stride,pattern,x,y,color,spacing,tab,origin,int(clipping),*clip)))
def scenarios():
 for width in (0,1,7,8,9,15,16,17,24):
  for pattern in (0,255,71):
   for clip in (None,(0,0,31,23),(6,4,11,5),(0,0,2,2),(4,3,4,3)):
    yield 'bitmap_width_zero_bytes_and_inclusive_edges',command(width=width,pattern=pattern,clipping=clip is not None,clip=clip or (0,0,31,23))
 for x,y in ((-7,-2),(-1,2),(25,3),(2,22),(40,2),(2,-8)):
  for width in (1,9,17):
   for pattern in (0,255,33):yield 'partial_or_rejected_negative_and_surface_edges',command(x=x,y=y,width=width,pattern=pattern,clipping=1)
 for index in (0,1):
  for fallback in (0,1):
   for surface in (0,1):
    for color in (-1,0,65535,0x12345678,-2147483648):yield 'fallback_color_toggle_and_no_surface',command(index=index,fallback=fallback,surface=surface,color=color)
 for rows in (0,1,5):
  for stride in (0,1,4):yield 'independent_rows_and_byte_stride',command(rows=rows,stride=stride)
 for present in (0,1):
  for fallback in (0,1):yield 'absent_primary_early_exit',command(present=present,fallback=fallback,surface=0)
 for x in (-2147483648,-100,-1,0,1,99,2147483647):
  for tab in (-64,-1,1,7,64):
   for origin in (-7,0,19):
    rel=signed((x+tab-origin)&0xffffffff)
    if rel==-2147483648 and tab==-1:continue
    yield 'signed_wrapped_tabs_relative_origin',command(code=0xabcd0009,x=x,tab=tab,origin=origin,present=0)
 for spacing in (-2147483648,-5,0,2147483647):yield 'wrapped_advance',command(spacing=spacing)
 for code in (32,65,88,97,0x4e00,0xffff):
  for index in (0,1):
   yield 'stock_GAME_FNT_pixels',command(op='T',code=code,fallback=index,x=1,y=1,clipping=1)
def signed(v):return v if v<2**31 else v-2**32
def parse(cmd,stock=b''):
 import struct
 p=cmd.split();require(len(p)==21 and p[0] in ('G','T'));v=list(map(int,p[1:]));code,present,fallback,surface,index,width,rows,stride,pattern,x,y,color,spacing,tab,origin,clipping,*clip=v
 require(all(n in (0,1) for n in (present,fallback,surface,index,clipping)) and 0<=width<=24 and 0<=rows<=5 and 0<=stride<=4 and 0<=pattern<=255)
 indices=bytearray(131072);struct.pack_into('<H',indices,(code&65535)*2,index)
 glyph=bytes([width])+bytes(0 if pattern==0 else 255 if pattern==255 else (i*37+pattern)&255 for i in range(1,129));fb=glyph[:1]+bytes(n^255 for n in glyph[1:]);glyphStride=129
 if p[0]=='T' and stock:
  fields=struct.unpack_from('<6I',stock,4);indices=stock[28:28+131072];glyph=stock[28+131072:];stride,rows,glyphStride=fields[1],fields[2],fields[5];ix=struct.unpack_from('<H',indices,88*2)[0];off=(ix-1)*glyphStride;fb=glyph[off:off+1]+bytes(n^255 for n in glyph[off+1:off+1+stride*rows])+b'\xa5'
 return dict(code=code,present=present,fallback=fallback,surface=surface,index=index,width=width,rows=rows,stride=stride,pattern=pattern,x=x,y=y,color=color,spacing=spacing,tab=tab,origin=origin,clipping=clipping,clip=clip,indices=bytes(indices),glyph=glyph,fb=fb,glyphStride=glyphStride)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_font_glyph.py',{'sources':dict.fromkeys(ORIGINAL)})
 require(hash_file(a.font_file)==FONT_SHA)
 return dict(original=dict(font_sha256=hash_file(a.font_file),inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and len(row)==6 and row[0]=='R' and row[2]=='B' and row[4]=='T')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','font-file'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_font_glyph import FontGlyphOracle
  oracle=FontGlyphOracle(a.exe);stock=a.font_file.read_bytes();commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd,stock)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x4318e0','0x432000','supplied.SetRect')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.font_file)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Font glyph sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
