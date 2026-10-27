#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original message expiry and joined insertion/list sequences."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_message_expiry import verify
NATIVE=('src/sim/MessageExpiry.hpp','src/sim/MessageList.hpp','src/sim/MessageFontMetrics.hpp','tests/message_expiry_vectors.cpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp')
ORIGINAL=('tests/original_message_expiry.py','tools/verify_message_expiry.py','tests/compare_message_expiry.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_expiry_5B5610=True,actual_insertion_and_shared_node_children=True,actual_signed_strict_comparison_and_late_reads=True,initial_records_and_heap_clock_audio_leaves_supplied=True,glyph_drawing_recovered=False,production_scheduling_enabled=False)
def require(v):
 if not v:raise ValueError('Message expiry input/evidence differs')
def encoded(text):return text.encode('utf-16le','surrogatepass').hex() if text else '-'
def command(expiries=(99,100,101),start=0,accum=0,times=(1600,),y=23,step=19,res19=0,res1a=0,focus=0,mutation=0,slots=None,operations=(('U',),('U',))):
 if slots is None:slots=range(len(expiries))
 records=[v for e,slot in zip(expiries,slots) for v in (e,slot)];p=[*map(str,(len(expiries),start,accum,y,step,res19,res1a,focus,mutation,*records,len(times),*times,len(operations)))]
 for op in operations:p.extend(['U'] if op[0]=='U' else ['I',str(op[1]),encoded(op[2])])
 return ' '.join(p)
def parse(cmd):
 p=cmd.split();require(len(p)>=12);cursor=0
 def number():
  nonlocal cursor
  require(cursor<len(p));v=int(p[cursor]);cursor+=1;return v
 n,start,accum,y,step,res19,res1a,focus,mutation=[number() for _ in range(9)];require(0<=n<=14 and all(0<=v<2**32 for v in (start,accum)) and all(-2**31<=v<2**31 for v in (y,step)) and 0<=res19<=255 and 0<=res1a<=255 and 0<=focus<=7 and 0<=mutation<=7)
 nodes=[]
 for _ in range(n):
  expiry,slot=number(),number();require(0<=expiry<2**32 and -1<=slot<14);nodes.append((expiry,slot))
 nt=number();require(1<=nt<=32);times=[number() for _ in range(nt)];require(all(0<=v<2**32 for v in times));no=number();require(1<=no<=32);operations=[]
 for _ in range(no):
  require(cursor<len(p));op=p[cursor];cursor+=1;require(op in ('I','U'))
  if op=='I':
   duration=number();require(-2**31<=duration<2**31 and cursor<len(p));body=b'' if p[cursor]=='-' else bytes.fromhex(p[cursor]);cursor+=1;require(len(body)%2==0 and len(body)<=1024);operations.append(('I',duration,body))
  else:operations.append(('U',))
 require(cursor==len(p));return dict(nodes=nodes,start=start,accum=accum,y=y,step=step,res19=res19,res1a=res1a,focus=focus,mutation=mutation,times=times,operations=operations)
def scenarios():
 patterns=((),(0,),(99,),(100,),(101,),(0,99,101),(99,100,0xffffffff,0x80000000),(101,0,99,102),(99,)*14)
 clocks=((0xffffffff,0,(0,)),(0xffffffff,100,(0,)),(0xffffffff,0xffffffff,(0,)),(0xffffffff,0x80000000,(0,)),(0,0,(1600,)),(123,0xffffffff,(0xffffffff,)),(0,0,(1600,1616,1632)),(0xfffffffe,0xffffffff,(0,0xffffffff)))
 for expiries in patterns:
  for start,accum,times in clocks:
   for reserved in ((0,0),(1,0),(0,255),(1,255)):
    for focus in (0,7):yield 'strict_signed_expiry_zero_equality_wrapping_and_focus',command(expiries=expiries,start=start,accum=accum,times=times,res19=reserved[0],res1a=reserved[1],focus=focus)
 for slots in ((-1,2,2),(13,0,6)):
  for reserve in (0,1):yield 'slot_identity_and_wrapped_post_removal_layout',command(expiries=(99,1000,1000),slots=slots,y=2147483647,step=2147483647,res19=reserve,res1a=255)
 for mutation in range(1,8):
  for focus in (0,7):yield 'diagnostic_clock_expiry_next_head_and_release_late_reads',command(expiries=(50,75,100,200),times=(1600,1760),mutation=mutation,focus=focus)
 for duration in (-1,0,60,-2,-2147483648,2147483647):
  for body in ('Hello','a '*90):
   yield 'complete_insertion_then_repeated_expiry',command(expiries=(),times=(1600,1600,1616,3200),operations=(('I',duration,body),('U',),('U',),('I',-1,'Done'),('U',)))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_message_expiry.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and 'R' in row and row[0]=='R' and 'END' in row and row.count('END')==len(parse(cmd)['operations']))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_message_expiry import MessageExpiryOracle
  oracle=MessageExpiryOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(all(oracle.counts[a]>0 for a in ('0x5b5610','0x5b4da0','0x6f17f0','0x69a430')) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Message expiry sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
