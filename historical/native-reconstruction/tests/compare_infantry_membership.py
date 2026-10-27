#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual Infantry Mark/map/Cell/subcell occupation on production map owners."""
import argparse,itertools,json,re,subprocess,time,struct
import pefile
from pathlib import Path
import compare_unit_membership as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_infantry_membership import verify
NATIVE=('tests/infantry_membership_vectors.cpp','src/sim/UnitMark.cpp','src/sim/InfantrySubcell.cpp',
 'src/assets/MutableUnitMap.cpp','src/assets/MapFloorHeight.cpp','src/assets/MapCoordinateCell.cpp',
 'src/assets/MapCellChildren.cpp','src/assets/MovementData.cpp','src/assets/RenderData.cpp',
 'src/assets/PreparedData.cpp','src/assets/Formats.cpp','src/render/Lighting.cpp','src/render/Redraw.cpp')
ORIGINAL=tuple(p for p in parent.SOURCES if not p.startswith('src/') and not p.endswith('_vectors.cpp'))+(
 'tests/original_infantry_membership.py','tests/compare_infantry_membership.py','tools/verify_infantry_membership.py',
 'tools/verify_infantry_mark.py','tools/verify_infantry_subcell.py')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_infantry_membership.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(actual_Infantry_foundation_Mark_map_Cell_and_floors=True,actual_Infantry_membership_skips_occupation_and_eligibility=True,
 borrowed_production_map_actor_occupation_and_Next=True,supplied_visibility_notification_recalculation_atexit_and_initial_records=True,
 actual_Walk_Process_join=False,runtime_enabled=False,full_frame_fidelity=False)
def require(v):
 if not v:raise ValueError('Infantry membership evidence/input differs')
def scenarios(planes):
 for root,alt,eligible,profile in itertools.product((0,1),(0,1,255),(0,1,255),range(4)):
  records=[r.copy() for r in parent.RECORDS];links=[-1]*4
  if profile==1:records[0][5:7]=[1,1];links[1]=0
  elif profile==2:records[0][5:7]=[2,2];links[2]=1;links[1]=0
  elif profile==3:records[0][5:7]=[1,1];links[1]=2
  yield 'actual_Cell_link_profiles_and_late_eligibility',parent.command([parent.row(root=root,alt=alt,eligible=eligible)],records=records,links=links,planes=planes)
 for root,of,inf,flag in itertools.product((2,3,4),(0,128,255),(0,128,255),(0,1,255)):
  header=parent.HEADER.copy();header[0]=of;header[1]=inf;header[2]=flag
  rows=[parent.row(root=root,mode=m) for m in ((1,0,3,2,0) if root==4 else (1,))]
  yield 'actual_separate_Infantry_lazy_foundation_and_Mark_map_parents',parent.command(rows,header=header,planes=planes)
 for x,y,z,flags,threshold in itertools.product((64,128,192),(64,128,192),(415,416,544),(0,256),(128,2147483647)):
  records=[r.copy() for r in parent.RECORDS];records[0][2]=flags
  header=parent.HEADER.copy();header[7]=threshold
  rows=[parent.row(root=4,mode=m,x=51*256+x,y=72*256+y,z=z) for m in (1,0)]
  yield 'Infantry_membership_skips_subcell_occupation_House_and_height_policy',parent.command(rows,header=header,records=records,planes=planes)
 for mutation,eligible in itertools.product((1,2,4,7),(0,1)):
  header=parent.HEADER.copy();header[4:6]=[0,0];header[8]=mutation
  yield 'notification_late_actor_eligibility_and_map_slot_reload',parent.command([parent.row(root=2,eligible=eligible)],header=header,planes=planes)
 for root,(x,y) in itertools.product((0,1,2,3),((-256,256),(-1,0),(0,0),(16777216,0))):
  yield 'word_membership_and_shared_fallback_without_occupation',parent.command([parent.row(root=root,x=x,y=y)],planes=planes)
def plane_data(exe):
 p=pefile.PE(data=exe.read_bytes());return list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},render_data=hash_file(a.render_data),planes=plane_data(a.exe)),
  native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(list(zip(e['labels'],e['commands']))==list(scenarios(current['original']['planes'])))
 require(e['evidence']['audited_original_calls']==sum(len(parent.parse(c)[4]) for c in e['commands']))
 for c,row in zip(e['commands'],e['expected']):
  require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('S')==len(parent.parse(c)[4]))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_infantry_membership import InfantryMembershipOracle
  o=InfantryMembershipOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios(current['original']['planes']):
   header,records,links,planes,rows=parent.parse(cmd);commands.append(cmd);labels.append(label);expected.append(o.run_membership(header,records,links,planes,rows))
  generation=time.monotonic()-now
  require(all(o.entries[hex(a)]>0 for a in (0x4c2e60,0x54ab70,0x54af70,0x473b30,0x473d20,0x50a000)))
  require(all(o.entries[hex(a)]==0 for a in (0x41b470,0x508410,0x5084a0)))
  meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,actual_entries=o.entries,
   service_counts=o.service_counts,selected_stores=o.selected_stores)
  require(current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
   commands=commands,expected=expected,labels=labels,evidence=origin));fingerprint=hash_file(source)
  write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 comparison=time.monotonic()-now;require(current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,
  native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint)
 write_report(a.exe,report,result);print(len(commands),'Infantry membership sequences PASS;',meta['audited_original_calls'],
  'complete original roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
