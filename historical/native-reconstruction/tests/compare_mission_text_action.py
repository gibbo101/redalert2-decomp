#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Action11 Text Trigger exact-original comparison."""
import argparse,json,platform,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_text_action import verify
NATIVE=('src/sim/MissionTextAction.hpp','src/sim/OriginalMath.hpp','tests/mission_text_action_vectors.cpp')
ORIGINAL=('tests/original_mission_text_action.py','tools/verify_mission_text_action.py','tools/verify_mission_trigger_control.py','tools/verify_mission_trigger.py','tests/compare_mission_text_action.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_action11_dispatch_branch=True,exact_x87_duration_conversion=True,color_localization_and_display_children_supplied=True,production_discovery_and_ui_join=False)
def require(ok):
 if not ok:raise ValueError('Mission text action evidence/input differs')
def encoded(raw):return raw.hex() if raw else '-'
def decoded(token):
 if token=='-':return b''
 require(len(token)%2==0)
 try:return bytes.fromhex(token)
 except ValueError:raise ValueError('Mission text hex differs')
def command(alternate,delay,color1,color2,key,localized):return f'T {alternate} {struct.unpack("<Q",struct.pack("<d",delay))[0]} {color1} {color2} {encoded(key)} {encoded(localized)}'
def parse(cmd):
 t=cmd.split();require(len(t)==7 and t[0]=='T');alternate=int(t[1]);bits=int(t[2]);colors=[int(t[3]),int(t[4])];key,localized=decoded(t[5]),decoded(t[6]);require(0<=alternate<=255 and len(key)<=31 and b'\0' not in key and len(localized)<=127 and b'\0' not in localized and all(-2**31<=x<2**31 for x in colors));return dict(alternate=alternate,delayBits=bits,colors=colors,key=key,localized=localized)
def scenarios():
 keys=(b'',b'MISSION:Objective1',b'A',b'1234567890123456789012345678901')
 localized=(b'',b'First Objective',b'X')
 delays=(0.,.6,-.6,1/900,4294967297/900,2147483648/900)
 colors=((-1,0),(7,11),(0x7fffffff,-0x80000000))
 for alternate in (0,1,2,255):
  for delay in delays:
   for pair in colors:
    for n,key in enumerate(keys):yield 'complete_action11_order_empty_key_and_x87_duration',command(alternate,delay,*pair,key,localized[(n+alternate)%len(localized)])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_text_action.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):require(parse(cmd) and isinstance(row,list) and row[-2:]==['R','1'])
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_text_action import MissionTextActionOracle
  oracle=MissionTextActionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x6adae0']==len(commands) and oracle.counts['0x6ae2ff']==len(commands) and oracle.counts['supplied_color']==len(commands) and oracle.counts['0x77f110']>0 and oracle.counts['supplied_localize']>0 and oracle.counts['supplied_display']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission text action sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
