#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original message-node drawing through actual text-to-pixels."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_message_node import verify
FONT_SHA='ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f'
NATIVE=('CMakeLists.txt','src/render/MessageNodeDrawing.hpp','src/render/PlayerColor.hpp','src/render/PlayerColor.cpp','src/sim/MessageList.hpp','src/render/MessageText.hpp','src/render/FontAlignment.hpp','src/render/FontText.hpp','src/render/FontGlyph.hpp','src/assets/GameFont.hpp','src/assets/GameFont.cpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/sim/MessageFontMetrics.hpp','tests/message_node_vectors.cpp')
ORIGINAL=('tests/original_message_node.py','tests/original_message_text.py','tools/verify_message_text.py','tests/original_font_alignment.py','tests/original_font_text.py','tests/original_font_glyph.py','tools/verify_message_node.py','tests/compare_message_node.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_message_node_parent=True,actual_admission_focus_font_HSV_consumer_pixels=True,same_mutable_list_node_slot_focus_records=True,actual_original_text_node_vtable=True,time_audio_surface_IME_fill_cursor_initial_records_supplied=True,diagnostic_late_service_mutations=True,production_UI_enabled=False)
import compare_font_text as base
def require(v):
 if not v:raise ValueError('Message node input/evidence differs')
PREFIX=('force','dirty','hidden','typewriter','selector','colorCount','missing','nodeX','nodeY','maximumWidth','initialScroll','initialReveal','initialTime','milliseconds','timeStep','focus','repeats','nodeMutation','enabled','lineOverride','h0','s0','v0','h1','s1','v1')
def command(text='ab a?X',force=1,dirty=2,hidden=0,typewriter=0,selector=1,colorCount=2,missing=0,nodeX=2,nodeY=2,maximumWidth=24,initialScroll=0,initialReveal=0,initialTime=0,milliseconds=31,timeStep=16,focus=0,repeats=1,nodeMutation=0,enabled=1,lineOverride=2147483647,hsv0=(0,255,255),hsv1=(137,211,239),**kwargs):
 common=base.command(text=text,clipping=kwargs.pop('clipping',0),**kwargs).split(' ',1)[1]
 return ' '.join(map(str,('N',force,dirty,hidden,typewriter,selector,colorCount,missing,nodeX,nodeY,maximumWidth,initialScroll,initialReveal,initialTime,milliseconds,timeStep,focus,repeats,nodeMutation,enabled,lineOverride,*hsv0,*hsv1)))+' '+common
def scenarios():
 for force in (0,1,0xffffffff):
  for dirty in (0,1,255):
   for hidden in (0,1,255):
    for count in (0,2):yield 'hidden_force_dirty_then_color_admission',command(force=force,dirty=dirty,hidden=hidden,colorCount=count,repeats=2)
 for selector in (-2147483648,-1,0,1,2,2147483647):
  for count in (-1,0,1,2):
   for missing in (0,1,2,3):yield 'signed_color_index_fallback_and_null_scheme',command(selector=selector,colorCount=count,missing=missing)
 for maximum in (-1,0,1,24,40):
  for x in (-3,0,31,32,40):yield 'negative_width_double_query_and_conditional_right_clip_rejection',command(maximumWidth=maximum,nodeX=x)
 for text in ('','a','a\r\nb','a\tba','a\0b','a'*160):
  for initial in (0,1,6,0x7fffffff,0xffffffff):
   for focus in (0,1):yield 'complete_node_consumer_actual_pixels_and_signed_reveal',command(text=text,initialReveal=initial,focus=focus)
 for now,last in ((0,0),(15,0),(16,0),(31,0),(32,0),(0,0xfffffff0),(0xffffffff,0),(0x80000000,0),(0,1)):
  for initial in (0,1,6,0x7fffffff,0xffffffff):yield 'raw_unsigned_time_delta_before_shift_and_signed_sound_bound',command(typewriter=1,initialReveal=initial,initialTime=last,milliseconds=now,repeats=3,timeStep=7)
 for mutation in (1,2,3,4,5,6,7):
  for focus in (0,1):
   for maximum in (-1,24):yield 'late_time_audio_width_text_focus_and_saved_font_box',command(typewriter=1,nodeMutation=mutation,focus=focus,maximumWidth=maximum,repeats=2)
 for hue in (0,42,43,84,85,127,128,169,170,212,213,254,255):
  for saturation,value in ((0,151),(255,255),(211,239)):yield 'actual_base_HSV_inside_complete_parent',command(hsv1=(hue,saturation,value))
 for stock in (0,1):
  for mutation in (0,1,2):
   for focus in (0,1):yield 'stock_font_and_late_surface_services',command(stock=stock,mutation=mutation,focus=focus,typewriter=1,repeats=3)
 for height in (-1,0,1):
  for width in (0,24,40):yield 'nonpositive_font_height_rejected_only_after_right_clip',command(text='',lineOverride=height,maximumWidth=width)
 for enabled in (0,2,255):yield 'lower_text_gate_keeps_node_success_and_background',command(enabled=enabled)
def parse(cmd,stock=b''):
 p=cmd.split();require(len(p)>len(PREFIX)+1 and p[0]=='N');prefix=dict(zip(PREFIX,map(int,p[1:len(PREFIX)+1])));f=base.parse('J '+' '.join(p[len(PREFIX)+1:]),stock)
 require(all(0<=prefix[k]<=255 for k in ('dirty','hidden','typewriter','enabled','h0','s0','v0','h1','s1','v1')) and prefix['focus'] in (0,1) and 1<=prefix['repeats']<=3 and 0<=prefix['missing']<=3 and 0<=prefix['nodeMutation']<=7)
 for k in ('selector','colorCount','nodeX','nodeY','maximumWidth','lineOverride'):require(-2**31<=prefix[k]<2**31)
 for k in ('force','initialScroll','initialReveal','initialTime','milliseconds','timeStep'):require(0<=prefix[k]<2**32)
 require(len(f['text'])<=322)
 if prefix['lineOverride']!=2147483647:f['line']=prefix['lineOverride']
 f.update(prefix);f.update(op='N',fontChoice=0,surfaceChoice=0,diagnostic=0,imeContext=0);f['hsv']=[[prefix[k+str(i)] for k in ('h','s','v')] for i in range(2)];f['box']=[0,0,0,0];return f
def identities(a):
 paths=python_closure(ROOT/'tests/compare_message_node.py',{'sources':dict.fromkeys(ORIGINAL)})
 require(hash_file(a.font_file)==FONT_SHA)
 return dict(original=dict(font_sha256=hash_file(a.font_file),inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  f=parse(cmd);n=f['repeats'];require(isinstance(row,list) and len(row)==52+n and row[:2]==['R',str(n)] and row[2+n]=='B' and row[4+n]=='T' and row[6+n]=='S' and row[15+n]=='D' and row[24+n]=='E' and row[27+n]=='O' and row[38+n]=='F' and row[40+n]=='G' and row[42+n]=='H' and row[45+n]=='C')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','font-file'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_message_node import MessageNodeOracle
  oracle=MessageNodeOracle(a.exe);stock=a.font_file.read_bytes();commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd,stock)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x6f1620','0x4cf240','0x497a50','0x4ff050','0x4cf630','supplied.timeGetTime','supplied.sound','0x600830','0x783605','0x783622','0x783850','0x737e30','0x431710','0x431690','supplied.fill','supplied.line','0x5fe1b0','0x4318e0','0x432000','0x431cc0','0x4314b0','0x63cf20','0x4320b0','0x432150','0x432350','supplied.SetRect','supplied.U')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.font_file)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Message node sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
