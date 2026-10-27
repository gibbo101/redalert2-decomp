#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original message lifecycle and drawing through actual text-to-pixels."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_message_pipeline import verify
FONT_SHA='ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f'
NATIVE=('CMakeLists.txt','src/render/MessageListDrawing.hpp','src/sim/MessageExpiry.hpp','src/render/MessageNodeDrawing.hpp','src/render/PlayerColor.hpp','src/render/PlayerColor.cpp','src/sim/MessageList.hpp','src/render/MessageText.hpp','src/render/FontAlignment.hpp','src/render/FontText.hpp','src/render/FontGlyph.hpp','src/assets/GameFont.hpp','src/assets/GameFont.cpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/sim/MessageFontMetrics.hpp','tests/message_pipeline_vectors.cpp')
ORIGINAL=('tests/original_message_pipeline.py','tests/original_message_node.py','tests/original_message_list.py','tools/verify_message_expiry.py','tools/verify_message_list.py','tools/verify_message_node.py','tests/original_message_text.py','tools/verify_message_text.py','tests/original_font_alignment.py','tests/original_font_text.py','tests/original_font_glyph.py','tools/verify_message_pipeline.py','tests/compare_message_pipeline.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(actual_shared_insertion_expiry_list_gadget_node_pixels=True,complete_gadget_low_byte_force_and_late_Next=True,ordinary_list_editor_byte_zero=True,actual_original_text_node_vtable=True,same_node_slot_focus_font_records=True,heap_time_audio_surface_IME_fill_line_initial_records_supplied=True,diagnostic_late_callback_link_head_changes=True,production_UI_enabled=False)
import compare_font_text as base
def require(v):
 if not v:raise ValueError('Message pipeline input/evidence differs')
PREFIX=('stock','listX','listY','listWidth','capacity','lineStep','mode','mode3','mode4','start','accum','milliseconds','timeStep','colorCount','missing','pipelineMutation')
def text_token(text):return ''.join(f'{ord(c):04x}' for c in text) or '-'
def insert(text='ab',prefix=None,lifetime=-1,color=1,flags=0x12345678,silent=0):return ('I','~' if prefix is None else text_token(prefix),text_token(text),lifetime,color,flags,silent)
def command(actions=(),**kwargs):
 values=dict(zip(PREFIX,(0,1,1,88,4,5,1,0,0,0xffffffff,0,31,16,2,0,0)));values.update(kwargs);require(set(values)==set(PREFIX))
 return ' '.join(map(str,('P',*[values[k] for k in PREFIX],len(actions),*[part for action in actions for part in action])))
def scenarios():
 for stock in (0,1):
  for lifetime in (-1,0,1,10,-2147483648,2147483647):
   for start in (0xffffffff,0):
    for accum in (0,1,0xfffffff8):yield 'joined_lifecycle_clocks_expiry_and_later_insertion',command([insert('ab a?X',lifetime=lifetime),('D',),('E',),('T',160,0),('D',),('E',),('D',),insert('baX'),('D',)],stock=stock,start=start,accum=accum)
 for stock in (0,1):
  for width in (40,64,88):
   for capacity in (-1,0,1,2,4):yield 'recursive_wrapping_capacity_removal_and_drawing',command([insert('ab ab ab ab ab ab',prefix='X'),('D',),insert('ba ab',silent=1),('E',),('D',)],stock=stock,listWidth=width,capacity=capacity)
 for force in (0,1,2,255,256,257,0x80000100,0xffffffff):
  for hidden in (0,1):
   for focus in (0,3):yield 'low_byte_force_refusal_does_not_stop_chain',command([insert('a',silent=1),insert('b',silent=1),insert('X',silent=1),('H',1,0,hidden,0,0,0,0),('H',2,1,0,0,0,0,0),('H',3,0,0,0,0,0,0),('F',focus),('G',force),('G',force),('D',)])
 for mutation in (1,2,3,4,8,16,31):
  for focus in (0,1):
   for stock in (0,1):yield 'live_Next_head_eligibility_focus_and_expiry_after_callbacks',command([insert('a'),insert('b'),insert('X'),('H',3,0,1,1,0,0,0),('F',focus),('D',),('D',),('E',),('D',)],pipelineMutation=mutation,stock=stock)
 for stock in (0,1):yield 'destroy_focus_and_reuse_slot_preserves_uncleared_tail',command([insert('ab'*55,lifetime=0),('F',1),('D',),('E',),insert('a',lifetime=-1),('D',),('E',)],stock=stock,listWidth=900,start=0,milliseconds=16,timeStep=16)
 for mode in (1,3,4):
  for mode3 in (0,1):
   for mode4 in (0,1):yield 'shared_mode_typewriter_insertion_and_raw_draw_clock',command([insert('ab'),('D',),('D',),('T',0,15),('D',)],mode=mode,mode3=mode3,mode4=mode4)
 for missing in (0,1,2,3):
  for count in (-1,0,1,2):
   for selector in (-1,0,1,2):yield 'color_refusal_keeps_traversal_and_shared_dirty_state',command([insert('a',color=selector,silent=1),insert('b',color=1,silent=1),('H',1,2,0,0,0,0,0),('D',)],missing=missing,colorCount=count)
 yield 'empty_list_and_null_chain_roots',command([('D',),('G',0xffffffff),('E',)])
 yield 'prefix_colon_empty_body_and_control_units',command([insert('',prefix=''),insert('a\r\nb\tX',prefix='ab'),('D',),('E',)])
def parse(cmd,stock=b''):
 p=cmd.split();require(len(p)>=len(PREFIX)+2 and p[0]=='P');prefix=dict(zip(PREFIX,map(int,p[1:len(PREFIX)+1])));n=int(p[len(PREFIX)+1]);require(0<=n<=64)
 require(prefix['stock'] in (0,1) and 0<=prefix['mode3']<=255 and 0<=prefix['mode4']<=255 and 0<=prefix['missing']<=3 and 0<=prefix['pipelineMutation']<=31)
 for k in ('listX','listY','listWidth','capacity','lineStep','mode','colorCount'):require(-2**31<=prefix[k]<2**31)
 for k in ('start','accum','milliseconds','timeStep'):require(0<=prefix[k]<2**32)
 i=len(PREFIX)+2;actions=[]
 def take():
  nonlocal i
  require(i<len(p));v=p[i];i+=1;return v
 def unsigned():
  value=int(take());require(0<=value<2**32);return value
 def signed():
  value=int(take());require(-2**31<=value<2**31);return value
 def text(token):
  require(token=='-' or len(token)%4==0);value='' if token=='-' else ''.join(chr(int(token[j:j+4],16)) for j in range(0,len(token),4));require(len(value)<=4096);return value.encode('utf-16le',errors='surrogatepass')
 for _ in range(n):
  op=take()
  if op=='I':
   prefixToken=take();pr=None if prefixToken=='~' else text(prefixToken);body=text(take());life=signed();color=signed();flags=unsigned();silent=unsigned();require(silent<=255 and (pr is None or len(pr)<=320));actions.append((op,pr,body,life,color,flags,silent))
  elif op in ('D','E'):actions.append((op,))
  elif op=='G':actions.append((op,unsigned()))
  elif op=='F':value=unsigned();require(value<=256);actions.append((op,value))
  elif op=='T':actions.append((op,unsigned(),unsigned()))
  elif op=='H':
   values=[unsigned() for _ in range(7)];require(1<=values[0]<=256 and all(v<=255 for v in values[1:4]));actions.append((op,*values))
  else:raise ValueError('Unknown pipeline operation')
 require(i==len(p));f=base.parse(base.command(text='',stock=prefix['stock'],clipping=0),stock);f.update(prefix);f.update(actions=actions,fontChoice=0,surfaceChoice=0,diagnostic=0,imeContext=0,nodeMutation=0,enabled=1,box=[0,0,0,0]);return f
def identities(a):
 paths=python_closure(ROOT/'tests/compare_message_pipeline.py',{'sources':dict.fromkeys(ORIGINAL)})
 require(hash_file(a.font_file)==FONT_SHA)
 return dict(original=dict(font_sha256=hash_file(a.font_file),inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  n=len(parse(cmd)['actions']);require(isinstance(row,list) and len(row)==4+2*n and row[:2]==['R',str(n)] and row[-2]=='T')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','font-file'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_message_pipeline import MessagePipelineOracle
  oracle=MessagePipelineOracle(a.exe);stock=a.font_file.read_bytes();commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd,stock)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x5b4da0','0x5b5610','0x5b5b30','0x4cf260','0x6f1620','0x4cf190','0x539020','0x6f15c0','0x6f17f0','supplied.allocate','supplied.free','0x4cf240','0x497a50','0x4ff050','0x4cf630','supplied.timeGetTime','supplied.sound','0x600830','0x783605','0x783622','0x783850','0x737e30','0x431710','0x431690','supplied.fill','supplied.line','0x5fe1b0','0x4318e0','0x432000','0x431cc0','0x4314b0','0x63cf20','0x4320b0','0x432150','0x432350','supplied.SetRect','supplied.U')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.font_file)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Message pipeline sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
