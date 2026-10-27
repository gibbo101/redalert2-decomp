#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare one complete original Walk/position/sight root with the native join."""
import argparse,json,platform,re,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
import compare_infantry_update_position_effects_e1 as child
import compare_walk_arrival as walk
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_walk_arrival import verify as verify_walk
from verify_infantry_update_position_effects_e1 import verify as verify_child
from verify_walk_update_position_schedule import verify as verify_schedule
ORIGINAL=('tests/compare_walk_update_position.py','tests/original_walk_update_position.py',*child.ORIGINAL,*walk.ORIGINAL,'tools/verify_walk_update_position_schedule.py')
NATIVE=tuple(sorted(set((*child.NATIVE,*walk.source_closure(),'tests/walk_update_position_vectors.cpp'))))
def native_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*ORIGINAL,*native_closure(),'tests/test_walk_update_position.py','CMakeLists.txt')
FLAGS=dict(complete_original_Walk_to_position_sight=True,single_native_movement_kernel_callback=True,
 shared_actor_and_Walk_owners=True,late_reads_after_complete_child=True,
 Mark_occupation_floor_and_initial_records_supplied=True,reveal_mask_redraw_supplied=True,
 post_return_flag_probes_diagnostic=True,production_schedule=False,runtime_enabled=False)
def require(v):
 if not v:raise ValueError('Joined Walk/position evidence differs')
def scenarios():
 for distance in (0,1,16):
  for flags in ((1,0,0),(0,0,0),(1,255,0),(1,0,128)):
   for enabled in (0,1):
    for active in (0,1):
     f=child.command(15040,22976,208,59,89,2,8,-1,1,17,23,1,active,1,enabled)
     yield 'ordinary_return' if flags==(1,0,0) else 'diagnostic_post_child_late_flags',' '.join(map(str,(distance,*flags)))+' '+f

def parse(c):
 fields=c.split(maxsplit=4);require(len(fields)==5)
 distance,*flags=map(int,fields[:4]);require(distance in (0,1,16) and tuple(flags) in ((1,0,0),(0,0,0),(1,255,0),(1,0,128)))
 f=child.parse(fields[4]);require(f['onMap']==1 and f['fullPost']==1 and (f['x'],f['y'],f['z'],f['tx'],f['ty'],f['tz'],f['range'],f['queued'],f['permission'])==(15040,22976,208,59,89,2,8,-1,1))
 return distance,tuple(flags),f

def flatten(row):
 w=row['walk'];return [*row['child'],'Z',*map(str,(w['result'],*w['position'],*w['route'],*w['head'],*w['destination'],*w['moving'],*w['flags'],w['callbacks'])),*w['events']]

def validate_row(row,flags):
 w=row['walk'];require(w['callbacks']==1 and w['position']==[15040,22976,208] and w['head']==[0,0,0])
 require(w['flags']==list(flags) and w['route']==[-1,*range(102,124),-1])
 expected=[['0x71f19f',flags[0]]]
 if flags[0]:
  expected.append(['0x71f1aa',flags[1]])
  if not flags[1]:expected.append(['0x71f1b5',flags[2]])
 require(w['late']==expected)
 require(w['events']==['mark0','release','occupy','child','return']+(['mark1'] if flags==(1,0,0) else []))
 require(row['child'].count('H')==3 and row['child'].count('W')==6 and row['child'].count('M')==1 and row['child'].count('P')==1)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_walk_update_position.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=dict(walk=verify_walk(a.exe.read_bytes()),child=verify_child(a.exe.read_bytes()),schedule=verify_schedule(a.exe.read_bytes())),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in native_closure()},data={k:hash_file(getattr(a,k)) for k in ('render_data','raster_data','direction_data')})

def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','raster-data','direction-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();identity=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(a.output is None and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate_receipt(e,json.loads((source.parent/'report.json').read_text()),fingerprint)
  require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==identity['original'] and e['evidence']['identities']['data']==identity['data'])
  for k,v in FLAGS.items():require(e['evidence'][k] is v)
  commands,labels,rows=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0
  require(list(zip(labels,commands))==list(scenarios()) and len(rows)==len(commands) and meta['audited_complete_roots']==len(commands))
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and a.report is None);folder=private_path(a.output,a.exe);require(not folder.exists())
  from original_walk_update_position import WalkUpdatePositionOracle
  oracle=WalkUpdatePositionOracle(a.exe);commands=[];labels=[];rows=[];now=time.monotonic()
  for label,c in scenarios():
   distance,flags,f=parse(c);commands.append(c);labels.append(label);rows.append(oracle.run_joined(f,distance=distance,late_flags=flags))
  # JSON normalizes tuples so the same validator covers generation and replay.
  rows=json.loads(json.dumps(rows));generation=time.monotonic()-now
  require(oracle.audit_calls==len(commands) and oracle.counts['walk.0x71dff0']==len(commands) and oracle.counts['walk.0x71e220']==len(commands) and oracle.counts['0x500aa0']==len(commands) and oracle.counts['post_sight']==len(commands))
  meta=dict(FLAGS,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,identities=identity,counts=dict(oracle.counts),audited_complete_roots=oracle.audit_calls,cases=len(commands),receipt_contains_original_results_only=True)
  source=folder/'expected.json';report=folder/'native-comparison.json'
 for c,row in zip(commands,rows):validate_row(row,parse(c)[1])
 require(identity==identities(a) and runner==hash_file(a.native))
 if not a.expectations:
  write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=rows,evidence=meta));fingerprint=hash_file(source)
  write_report(a.exe,source.parent/'report.json',dict(meta,expectations_sha256=fingerprint))
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data),str(a.raster_data),str(a.direction_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[line.split() for line in proc.stdout.splitlines()];expected=[flatten(row) for row in rows]
 if actual!=expected:
  for i,(got,want) in enumerate(zip(actual,expected)):
   if got!=want:raise AssertionError((i,commands[i],got,want))
  raise AssertionError(('Row count',len(actual),len(expected)))
 comparison=time.monotonic()-now;require(identity==identities(a) and runner==hash_file(a.native))
 write_report(a.exe,report,dict(meta,identities=identity,native_sha256=runner,expectations_sha256=fingerprint,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start))
 print(len(rows),'complete joined Walk/position/sight roots PASS')
if __name__=='__main__':main()
