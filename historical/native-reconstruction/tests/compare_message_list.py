#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original message insertion and actual metric/CRT/list children."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_message_list import verify
NATIVE=('src/sim/MessageList.hpp','src/sim/MessageFontMetrics.hpp','tests/message_list_vectors.cpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp')
ORIGINAL=('tests/original_message_list.py','tools/verify_message_list.py','tests/compare_message_list.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_insertion_5B4DA0=True,actual_metric_CRT_and_node_children=True,actual_list_removal_destruction_and_recursion=True,initial_records_and_heap_clock_audio_leaves_supplied=True,glyph_drawing_recovered=False,expiry_polling_recovered=False,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('Message list input/evidence differs')
def encoded(text):return text.encode('utf-16le','surrogatepass').hex() if text else '-'
def command(width=160,capacity=4,res19=0,res1a=0,mode=0,mode3=1,mode4=1,start=0xffffffff,accum=100,milliseconds=16000,glyphWidth=5,available=16383,initial=0,focus=0,present=1,bodyPresent=1,silent=0,lifetime=60,prefix=None,body='Hello',repeats=1,mutation=0):
 return ' '.join([*map(str,(width,capacity,res19,res1a,mode,mode3,mode4,start,accum,milliseconds,glyphWidth,available,initial,focus,present,bodyPresent,silent,lifetime)), '~' if prefix is None else encoded(prefix),encoded(body),str(repeats),str(mutation)])
def parse(cmd):
 p=cmd.split();require(len(p)==22);v=list(map(int,p[:18]));width,capacity,res19,res1a,mode,mode3,mode4,start,accum,milliseconds,glyphWidth,available,initial,focus,present,bodyPresent,silent,lifetime=v;repeats=int(p[20]);mutation=int(p[21]);require(0<=mutation<=15)
 require(-100<=width<2**31 and -1<=capacity<=20 and -2**31<=mode<2**31 and all(0<=n<=255 for n in (res19,res1a,mode3,mode4,glyphWidth,silent)) and all(0<=n<2**32 for n in (start,accum,milliseconds)) and 0<=available<=16383 and 0<=initial<=14 and 0<=focus<=7 and present in (0,1) and bodyPresent in (0,1) and -2**31<=lifetime<2**31 and 0<=repeats<=20)
 prefix=b'' if p[18] in ('~','-') else bytes.fromhex(p[18]);body=b'' if p[19]=='-' else bytes.fromhex(p[19]);require(len(prefix)%2==0 and len(prefix)<=100 and len(body)%2==0 and len(body)<=1024)
 return dict(zip(('width','capacity','res19','res1a','mode','mode3','mode4','start','accum','milliseconds','glyphWidth','available','initial','focus','present','bodyPresent','silent','lifetime'),v),hasPrefix=p[18]!='~',prefix=prefix,body=body,repeats=repeats,mutation=mutation)
def scenarios():
 for present,bodyPresent in ((0,0),(0,1),(1,0)):
  for initial in (0,3):yield 'null_text_or_selected_font',command(present=present,bodyPresent=bodyPresent,initial=initial,focus=7)
 texts=('', 'Hello','a b c d e f g h i j k l m n','\tA','A\r\nB','A\n\t\rB','A\x01 B','A\0B','\uffff\ud800X','a'*180,'a '*100,'\t\r\n')
 for prefix in (None,'','P','X\t'):
  for width in (-5,8,80,2000):
   for text in texts:yield 'prefix_fitting_control_units_and_recursive_storage',command(prefix=prefix,width=width,body=text,capacity=0)
 for mode in (-1,3,4,5):
  for enabled in (0,255):
   for silent in (0,1,255):
    for lifetime in (-1,0,-2,2147483647):yield 'mode_flags_sound_and_wrapped_expiry',command(mode=mode,mode3=enabled,mode4=enabled,silent=silent,lifetime=lifetime,start=123,accum=0xffffffff,milliseconds=0xffffffff,repeats=2)
 for initial in (0,1,3,14):
  for capacity in (0,1,2,14):
   for reserve in ((0,0),(1,0),(0,2),(1,255)):
    for focus in (0,7):yield 'capacity_eviction_reserved_rows_and_focus_ownership',command(initial=initial,capacity=capacity,res19=reserve[0],res1a=reserve[1],focus=focus,available=16383&~((1<<initial)-1),repeats=3)
 for available in (0,1,0x100,0x2000,0x1555):
  yield 'first_available_slot_and_exhaustion',command(available=available,capacity=0,repeats=4,body='a'*120,width=2000)
 for lifetime in (-1,0,-2147483648):
  yield 'stopped_clock_no_API_and_signed_duration',command(lifetime=lifetime,start=0xffffffff,accum=0xfffffff0)
 for mutation in (1,2,4,8,3,5,6,7,10,15):
  for initial in (0,3):yield 'diagnostic_late_heap_clock_sound_font_reads',command(mutation=mutation,initial=initial,available=16383&~((1<<initial)-1),body='a '*90,width=80,start=123)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_message_list.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and 'R' in row and row[0]=='R' and 'B' in row and 'N' in row and 'E' in row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_message_list import MessageListOracle
  oracle=MessageListOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x5b4da0','0x6f15c0','0x4cefe0','0x5390e0','0x539110','0x6f17f0','0x4314b0','0x431690','0x431710')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Message list sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
