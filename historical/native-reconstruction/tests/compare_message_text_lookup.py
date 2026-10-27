#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete color roots and action11 through actual localization/CRT children."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_message_text_lookup import verify
NATIVE=('src/sim/StringLookup.hpp','src/sim/MessageColor.hpp','src/sim/MissionTextAction.hpp','src/sim/OriginalMath.hpp','tests/message_text_lookup_vectors.cpp')
ORIGINAL=('tests/original_message_text_lookup.py','tests/original_string_lookup.py','tests/original_mission_text_action.py','tools/verify_message_text_lookup.py','tools/verify_string_lookup.py','tools/verify_mission_text_action.py','tests/compare_message_text_lookup.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_action11_through_actual_color_and_found_lookup=True,complete_CRT_binary_search=True,actual_locale_zero_comparator=True,fixture_color_tables_and_initial_registry_supplied=True,message_insertion_and_display_recovered=False,production_UI_enabled=False)
def require(v):
 if not v:raise ValueError('Message text lookup input/evidence differs')
def encoded(b):return b.hex() if b else '-'
def decode(t):
 if t=='-':return b''
 try:return bytes.fromhex(t)
 except ValueError:raise ValueError('Message text lookup hex differs')
def command(alternate,delay,key,rows,colors):
 import struct
 return ' '.join(['J',str(alternate),str(struct.unpack('<Q',struct.pack('<d',delay))[0]),encoded(key),str(len(rows)),*[str(c) for c in colors],*[str(v) for k,i,t in rows for v in (encoded(k),i,encoded(t))]])
def parse(cmd):
 p=cmd.split();require(len(p)>=2 and p[0] in ('P','J'))
 if p[0]=='P':
  require(len(p)==11);selector=int(p[1]);colors=list(map(int,p[2:]));require(-2**31<=selector<2**31 and all(-128<=c<=127 for c in colors));return dict(op='P',selector=selector,colors=colors)
 require(len(p)>=14);alternate,bits=int(p[1]),int(p[2]);key=decode(p[3]);n=int(p[4]);colors=list(map(int,p[5:14]));require(0<=alternate<=255 and 0<=bits<2**64 and len(key)<=31 and b'\0' not in key and 0<=n<=16 and len(p)==14+n*3 and all(-128<=c<=127 for c in colors))
 rows=[]
 for i in range(n):
  label,index,payload=decode(p[14+i*3]),int(p[15+i*3]),decode(p[16+i*3]);require(len(label)<=31 and b'\0' not in label and 0<=index<n and len(payload)<=127 and b'\0' not in payload);rows.append((label,index,payload))
 return dict(op='J',alternate=alternate,delayBits=bits,key=key,colors=colors,rows=rows)
def scenarios():
 # Every signed byte reaches each selector; bypass cases must remain unchanged.
 for value in range(-128,128):
  table=[((value+i+128)%256)-128 for i in range(9)]
  for selector in (-2**31,-3,-2,-1,*range(11),2**31-1):yield 'complete_color_signed_byte_and_unsigned_selector', ' '.join(['P',str(selector),*map(str,table)])
 for n in range(1,9):
  for duplicate in (False,True):
   keys=[('K%02d'%(i//2 if duplicate else i)).encode() for i in range(n)]
   rows=[(key,(i*3)%n,('Payload-%d'%i).encode()) for i,key in enumerate(keys)]
   for alternate in (0,1,255):
    for delay in (0.,.6,-.6,1/900,2147483648/900):
     for key in (b'',keys[0],keys[-1].lower()):yield 'joined_action11_actual_color_search_comparison_and_message_arguments',command(alternate,delay,key,rows,[-128,-7,127,0,1,-1,32,64,-64])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_message_text_lookup.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  f=parse(cmd);require(isinstance(row,list) and len(row)>=2 and row[-2]=='R')
  require((len(row)==2) if f['op']=='P' else (row[:1]==['C'] and 'V' in row))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_message_text_lookup import MessageTextLookupOracle
  oracle=MessageTextLookupOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6715d0']>0 and oracle.counts['supplied.message_insertion']>0 and oracle.counts['0x6f9ec0']>0 and oracle.counts['0x782025']>0 and oracle.counts['0x781f20']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Message text lookup sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
