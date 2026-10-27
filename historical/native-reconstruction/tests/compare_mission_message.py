#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Actual mission action11 through localization/insertion/lifecycle and text pixels."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_message import verify
FONT_SHA='ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f'
NATIVE=('CMakeLists.txt','src/platform/MissionMessagePresentation.hpp','src/render/OwnedMessagePresentation.hpp','src/render/SurfaceFill.hpp','src/sim/StringLookup.hpp','src/sim/MessageColor.hpp','src/sim/MissionTextAction.hpp','src/sim/OriginalMath.hpp','src/render/MessageListDrawing.hpp','src/sim/MessageExpiry.hpp','src/render/MessageNodeDrawing.hpp','src/render/PlayerColor.hpp','src/render/PlayerColor.cpp','src/sim/MessageList.hpp','src/render/MessageText.hpp','src/render/FontAlignment.hpp','src/render/FontText.hpp','src/render/FontGlyph.hpp','src/assets/GameFont.hpp','src/assets/GameFont.cpp','src/assets/Bytes.hpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp','src/sim/MessageFontMetrics.hpp','tests/mission_message_vectors.cpp')
ORIGINAL=('tests/original_mission_message.py','tests/original_message_pipeline.py','tools/verify_mission_message.py','tests/compare_mission_message.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_action11_actual_color_found_localization_insertion=True,actual_shared_expiry_list_node_text_pixels=True,actual_global_list_receiver=True,owned_native_message_presentation=True,UTF8_conversion_supplied_host_adapter=True,heap_time_audio_surface_IME_fill_initial_records_supplied=True,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('Mission message input/evidence differs')
import struct
import compare_message_pipeline as pipeline
def encoded(b):return b.hex() or '-'
def decoded(t):return b'' if t=='-' else bytes.fromhex(t)
DEFAULT_ROWS=((b'K00',2,'ab X'),(b'K01',0,'Hello commander'),(b'K02',1,'Objective: move'))
def action(key=b'K00',delay=.6,alternate=0):return ('M',alternate,struct.unpack('<Q',struct.pack('<d',delay))[0],encoded(key))
def command(actions,capacity=3,width=88,mode=1,mode3=0,mode4=0,start=0xffffffff,accum=0,milliseconds=31,colors=(0,1,0,0,0,0,0,0,0),rows=DEFAULT_ROWS):
 return ' '.join(map(str,('W',capacity,width,mode,mode3,mode4,start,accum,milliseconds,*colors,len(rows),*[v for key,index,text in rows for v in (encoded(key),index,encoded(text.encode('utf-8')))],len(actions),*[v for a in actions for v in a])))
def scenarios():
 for width in (8,40,88,900):
  for capacity in (0,1,3,14):
   for mode in (1,3,4):
    yield 'actual_action_lookup_insertion_wrapping_capacity_and_pixels',command([action(),('D',),action(b'k02',0.,1),('D',),('E',),('T',160),('D',),('E',),action(b'K01'),('D',)],capacity=capacity,width=width,mode=mode,mode3=1,mode4=0)
 for delay in (0.,1/900,.6,-.6,2147483648/900,4294967295/900):
  for start in (0xffffffff,0):
   for accum in (0,1,0xfffffff8):
    yield 'raw_duration_signed_lifetime_clock_and_late_draw',command([action(delay=delay),('D',),('E',),('T',0xffffffff),('D',),('E',),action(delay=0.),('D',)],start=start,accum=accum)
 for color in (-128,-7,-1,0,1,2,127):
  for alternate in (0,1,255):
   yield 'signed_color_from_actual_lookup_not_selector',command([action(alternate=alternate),('D',),('D',)],colors=(0,color,1,0,0,0,0,0,0))
 for text in ('','ab\r\nb\tX','é Ω 中 😀','a\0b','ab '*50):
  for index in (0,1,2):
   rows=((b'K00',index,text),(b'K00',index,'X ab'),(b'K02',index,'a'))
   yield 'duplicate_lookup_slot_and_UTF16_message_storage',command([action(),('D',),('E',),action(b'k02'),('D',)],rows=rows)
 for alternate in (0,1,255):yield 'empty_key_color_only_no_message',command([action(b'',alternate=alternate),('D',),('E',)],rows=())
def parse(cmd,stock=b''):
 p=cmd.split();require(len(p)>19 and p[0]=='W');at=1
 def take():
  nonlocal at
  require(at<len(p));v=p[at];at+=1;return v
 values=[int(take()) for _ in range(8)];capacity,width,mode,mode3,mode4,start,accum,milliseconds=values
 require(all(-2**31<=v<2**31 for v in (capacity,width,mode)) and all(0<=v<=255 for v in (mode3,mode4)) and all(0<=v<2**32 for v in (start,accum,milliseconds)))
 colors=[int(take()) for _ in range(9)];require(all(-128<=v<=127 for v in colors));n=int(take());require(0<=n<=16);rows=[]
 for i in range(n):
  key=decoded(take());index=int(take());text=decoded(take());require(len(key)<=31 and b'\0' not in key and 0<=index<n);payload=text.decode('utf-8').encode('utf-16le');require(len(payload)<=1022);rows.append((key,index,payload))
 count=int(take());require(0<=count<=64);actions=[]
 for i in range(count):
  op=take()
  if op=='M':
   alternate=int(take());bits=int(take());key=decoded(take());require(0<=alternate<=255 and 0<=bits<2**64 and len(key)<=31 and b'\0' not in key);actions.append((op,alternate,bits,key))
  elif op in ('D','E'):actions.append((op,))
  elif op=='T':
   ms=int(take());require(0<=ms<2**32);actions.append((op,ms,0))
  else:raise ValueError('Mission message action differs')
 require(at==len(p));f=pipeline.parse(pipeline.command([],stock=1,capacity=capacity,listWidth=width,mode=mode,mode3=mode3,mode4=mode4,start=start,accum=accum,milliseconds=milliseconds,timeStep=0),stock)
 f.update(actions=actions,labels=rows,colorTable=colors,tab=64,bound=0,clipping=1,clip=[0,0,0,0]);return f
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_message.py',{'sources':dict.fromkeys(ORIGINAL)})
 require(hash_file(a.font_file)==FONT_SHA)
 return dict(original=dict(font_sha256=hash_file(a.font_file),inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  n=len(parse(cmd)['actions']);require(isinstance(row,list) and len(row)==2+2*n and row[:2]==['R',str(n)])
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','font-file'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_message import MissionMessageOracle
  oracle=MissionMessageOracle(a.exe);stock=a.font_file.read_bytes();commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd,stock)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x6adae0','0x6715d0','0x6f9ec0','0x782025','0x781f20','0x5b4da0','0x5b5610','0x5b5b30','0x4cf260','0x6f1620','0x4cf190','0x539020','0x6f15c0','0x6f17f0','supplied.allocate','supplied.free','0x4cf240','0x497a50','0x4ff050','0x4cf630','supplied.timeGetTime','supplied.sound','0x600830','0x783605','0x783622','0x783850','0x431710','0x431690','supplied.fill','0x5fe1b0','0x4318e0','0x432000','0x431cc0','0x4314b0','0x63cf20','0x4320b0','0x432150','0x432350','supplied.SetRect','supplied.U')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native),str(a.font_file)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission message sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
