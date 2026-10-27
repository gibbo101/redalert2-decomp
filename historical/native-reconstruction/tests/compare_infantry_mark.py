#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Verify reuse of the one Mark kernel against actual base Infantry/Walk dispatch."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
import compare_unit_mark as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_infantry_mark import verify
NATIVE=tuple(p for p in parent.SOURCES if p.startswith('src/') or p=='tests/unit_mark_vectors.cpp')
ORIGINAL=tuple(p for p in parent.SOURCES if p not in NATIVE)+(
 'tests/original_infantry_mark.py','tests/compare_infantry_mark.py','tools/verify_infantry_mark.py')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_infantry_mark.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(actual_Infantry_kind_type_getter_cast_and_Walk_layer=True,same_existing_native_Mark_kernel=True,
 supplied_membership_events_initial_records_and_dirty_resets=True,actual_Infantry_membership_join=False,
 runtime_enabled=False,full_frame_fidelity=False)
def require(v):
 if not v:raise ValueError('Infantry Mark evidence/input differs')
def scenarios():
 for root,marked,redraw,limbo,special,mode in itertools.product(range(3),(0,1,255),(0,1),(0,255),(0,255),(-2147483648,-1,0,1,2,3,4,2147483647)):
  yield 'Infantry_complete_Mark_roots_byte_gates_and_mode2_bypass',parent.command([parent.row(mode,limbo=limbo,special=special)],root=root,marked=marked,redraw=redraw)
 for root,present,tactical,owner,image in itertools.product(range(3),(0,1),(0,1),(-1,31),(-2147483648,2147483647)):
  yield 'actual_Infantry_nullable_type_image_owner_and_Walk',parent.command(
   [parent.row(mode,reset=0) for mode in (1,2,0,3,0)],root=root,present=present,tacticalPresent=tactical,owner=owner,image=image)
 for root,(x,y) in itertools.product(range(3),((-2147483648,2147483647),(-16777217,16777216),(-257,257),(-255,255),(-1,1),(16777216,0),(57*256+128,89*256+128))):
  yield 'actual_signed_coordinate_word_queries_and_membership_protocol',parent.command(
   [parent.row(mode,x,y,17,reset=0) for mode in (1,0,3,2,0)],root=root)
def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL}),
  native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
 require(e['evidence']['audited_original_calls']==sum(len(parent.parse(c)[1]) for c in e['commands']))
 for c,row in zip(e['commands'],e['expected']):
  require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('S')==len(parent.parse(c)[1]))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_infantry_mark import InfantryMarkOracle
  o=InfantryMarkOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   header,rows=parent.parse(cmd);commands.append(cmd);labels.append(label);expected.append(o.run_infantry_mark(header,rows))
  generation=time.monotonic()-now
  require(all(n>0 for n in o.entries.values()) and o.membership_calls>0 and o.event_calls>0 and o.redraw_calls>0)
  meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,actual_entries=o.entries,
   supplied_membership_calls=o.membership_calls,supplied_event_calls=o.event_calls,redraw_calls=o.redraw_calls,selected_stores=o.stores)
  require(current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
   commands=commands,expected=expected,labels=labels,evidence=origin));fingerprint=hash_file(source)
  write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True)
 require('PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,
  native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint)
 write_report(a.exe,report,result);print(len(commands),'Infantry Mark sequences PASS;',meta['audited_original_calls'],
  'complete original roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
