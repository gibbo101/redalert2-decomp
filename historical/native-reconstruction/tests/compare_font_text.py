#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original glyph pixel writes and inclusive clipping."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_font_text import verify
FONT_SHA='ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f'
NATIVE=('src/render/FontText.hpp','src/render/FontGlyph.hpp','src/assets/GameFont.hpp','src/assets/GameFont.cpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/sim/MessageFontMetrics.hpp','tests/font_text_vectors.cpp')
ORIGINAL=('tests/original_font_text.py','tests/original_font_glyph.py','tools/verify_font_text.py','tests/compare_font_text.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_text_to_actual_pixels=True,actual_glyph_intersection_metrics_color=True,actual_surface_binding_and_wrapper=True,initial_records_colors_SetRect_surface_methods_supplied=True,message_drawing_recovered=False,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('Font text input/evidence differs')
KEYS=('stock','fontPresent','present','fallback','bound','seed','x','y','color','spacing','tab','origin','count','reveal','clipping','left','top','right','bottom','pitch','width','height','mutation','rL','rR','bL','bR','gL','gR','targetR','targetG','targetB','offset')
def command(op='J',text='ab? aX\tba',**kwargs):
 values=dict(zip(KEYS,(0,1,1,1,1,71,1,1,0xabcd,1,8,0,0,0,1,0,0,31,23,64,32,24,0,11,3,0,3,5,2,255,255,255,0)));values.update(kwargs);require(set(values)==set(KEYS))
 return ' '.join([op,*[str(values[k]) for k in KEYS],''.join(f'{ord(c):04x}' for c in text) or '-'])
def scenarios():
 for op in ('D','J'):
  for text in ('','ab','a\r\nb','?X a','a\tb','aaaaaaaaaaaa','a\0b'):
   for reveal in (0,1,2,7,8,9,12,-1):
    yield 'complete_text_reveal_glyphs_and_metrics',command(op=op,text=text,reveal=reveal)
 for count in (1,2,3,5,0xffffffff):
  for reveal in (0,1,3,9):yield 'character_limits_include_control_units',command(text='a\r\nb\tab?',count=count,reveal=reveal)
 for reveal in (1,2,8,9):
  for offset in (0,256,4096):yield 'borrowed_next_text_address_return',command(reveal=reveal,text='aaaaaaaaaaaaaa',offset=offset)
 for color in (0,31,0x7fff,0xffff,0x1234):
  for target in ((0,0,0),(29,127,239),(255,255,255)):
   for packing in ((11,3,0,3,5,2),(10,3,0,3,5,3),(0,0,8,0,16,0),(32,40,15,33,7,34)):
    yield 'actual_fade_rounding_and_shift_widths',command(text='aaaaaaaaaa',reveal=7,color=color,**dict(zip(('targetR','targetG','targetB'),target)),**dict(zip(('rL','rR','bL','bR','gL','gR'),packing)))
 for clip in ((0,0,0,0),(2,2,17,15),(-8,-4,40,40),(80,80,90,90)):
  for mutation in (0,1,2):
   for pitch in (64,65):yield 'surface_binding_order_clip_and_late_services',command(mutation=mutation,pitch=pitch,**dict(zip(('left','top','right','bottom'),clip)))
 for width,height,pitch in ((0,0,0),(1,1,1),(-1,-1,0xffffffff),(40,30,81)):
  for mutation in (0,1,2):yield 'binding_only_arithmetic_and_alias',command(op='B',width=width,height=height,pitch=pitch,mutation=mutation)
 for stock in (0,1):
  for bound in (0,1):
   for fallback in (0,1):
    for reveal in (0,2,8):yield 'stock_or_missing_font_surface',command(op='D',stock=stock,bound=bound,fallback=fallback,reveal=reveal,text='Hello\t?X\uffff')
 for present in (0,1):
  for reveal in (0,1,-1):yield 'no_primary_or_no_wrapper_font',command(present=present,fallback=0,reveal=reveal)
 for fontPresent in (0,1):yield 'wrapper_font_admission',command(fontPresent=fontPresent)
 for x in (-4,0,25):
  for y in (-3,22):yield 'partial_clipping_and_negative_positions',command(x=x,y=y)
def parse(cmd,stock=b''):
 import struct
 parts=cmd.split();require(len(parts)==len(KEYS)+2 and parts[0] in ('J','D','B'));f=dict(zip(KEYS,map(int,parts[1:-1])));f['op']=parts[0]
 require(all(f[k] in (0,1) for k in ('stock','fontPresent','present','fallback','bound','clipping')) and 0<=f['seed']<=255 and 0<=f['color']<=65535 and 0<=f['offset']<=4096 and 0<=f['mutation']<=2)
 for k in ('targetR','targetG','targetB'):require(0<=f[k]<=255)
 for k in ('x','y','spacing','tab','origin','reveal','left','top','right','bottom','width','height'):require(-2**31<=f[k]<2**31)
 for k in ('count','pitch','rL','rR','bL','bR','gL','gR'):require(0<=f[k]<2**32)
 token=parts[-1];require(token=='-' or len(token)%4==0)
 text='' if token=='-' else ''.join(chr(int(token[i:i+4],16)) for i in range(0,len(token),4));require(len(text)<=4096)
 f['text']=text.encode('utf-16le',errors='surrogatepass');indices=bytearray(131072)
 for c,index in ((97,1),(98,2),(88,1),(32,2)):struct.pack_into('<H',indices,c*2,index)
 glyph=bytearray((i*37+f['seed'])&255 for i in range(66));glyph[0]=5;glyph[33]=7;fb=glyph[:1]+bytes(n^255 for n in glyph[1:10]);stride=3;rows=3;line=4;glyphStride=33
 if f['stock'] and stock:
  fields=struct.unpack_from('<6I',stock,4);indices=stock[28:28+131072];glyph=stock[28+131072:];stride,rows,line,glyphStride=fields[1],fields[2],fields[3],fields[5];ix=struct.unpack_from('<H',indices,88*2)[0];off=(ix-1)*glyphStride;fb=glyph[off:off+1]+bytes(n^255 for n in glyph[off+1:off+1+stride*rows])+b'\xa5'
 f.update(indices=bytes(indices),glyph=bytes(glyph),fb=bytes(fb),stride=stride,rows=rows,line=line,glyphStride=glyphStride,clip=[f[k] for k in ('left','top','right','bottom')],shifts=[f[k] for k in ('rL','rR','bL','bR','gL','gR')],target=[f[k] for k in ('targetR','targetG','targetB')]);return f
def identities(a):
 paths=python_closure(ROOT/'tests/compare_font_text.py',{'sources':dict.fromkeys(ORIGINAL)})
 require(hash_file(a.font_file)==FONT_SHA)
 return dict(original=dict(font_sha256=hash_file(a.font_file),inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and len(row)==15 and row[0]=='R' and row[2]=='B' and row[4]=='T' and row[6]=='S')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','font-file'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_font_text import FontTextOracle
  oracle=FontTextOracle(a.exe);stock=a.font_file.read_bytes();commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd,stock)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x4318e0','0x432000','0x431cc0','0x4314b0','0x63cf20','0x4320b0','0x432150','0x432350','supplied.SetRect','supplied.U')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.font_file)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Font text sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
