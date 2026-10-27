#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Focused complete original/native overlay admission, with strict replay."""
import argparse,copy,itertools,json,subprocess,time
from pathlib import Path
import compare_unit_admission as parent
from original_overlay_unit_admission import OverlayUnitAdmissionOracle
from verify_overlay_unit_admission import verify
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
SOURCES=(*parent.SOURCES,'tests/compare_overlay_unit_admission.py','tests/original_overlay_unit_admission.py',
 'tools/verify_overlay_unit_admission.py','tests/test_overlay_unit_admission.py')
require=parent.require
def command(override=0,human=0,control=0,weapon=(0,0),overlay_cells=None,types=None,**kw):
 overlay_cells=[[0,-1],[-1,-1],[-1,-1]] if overlay_cells is None else overlay_cells
 types=[[0,0,0,0],[0,0,0,0],[0,0,0,0]] if types is None else types
 values=[override,human,control,0,0,0,0,*weapon,*itertools.chain.from_iterable(overlay_cells),*itertools.chain.from_iterable(types)]
 return 'V '+' '.join(map(str,values))+' '+parent.command(**kw)
def parse(cmd):
 words=cmd.split();require(bool(words) and words[0]=='V' and len(words)>28)
 v=list(map(int,words[1:28]));i32=lambda n:-2147483648<=n<=2147483647
 require(i32(v[0]) and all(0<=b<=255 for b in v[1:9]))
 cells=[v[9+i*2:11+i*2] for i in range(3)];types=[v[15+i*4:19+i*4] for i in range(3)]
 require(all(-1<=index<3 and i32(owner) for index,owner in cells))
 require(all(all(0<=b<=255 for b in row[:3]) and i32(row[3]) for row in types))
 return (v[0],[v[1+i*2:3+i*2] for i in range(3)],v[7:9],cells,types),parent.parse(' '.join(words[28:]))
def scenarios():
 # Independent flags, raw bytes and global control bypass, including nonwalls.
 for flag,wall,crushable,crusher,owner in itertools.product((0,1,255),(0,1),(0,1),(0,1),(-1,0,1,33)):
  objects=copy.deepcopy(parent.OBJECTS);objects[0][9]=crusher
  yield 'overlay_flags_crusher_owner',command(human=1,weapon=(1,0),overlay_cells=[[0,owner],[-1,-1],[-1,-1]],
   types=[[flag,wall,crushable,0],[0,0,0,0],[0,0,0,0]],objects=objects)
 for override,human,control in itertools.product((0,1,-1),(0,1,255),(0,1,255)):
  yield 'House_control_and_global',command(override=override,human=human,control=control,types=[[1,0,0,0]]*3)
 for present,flag144,flag146,armor,owner in itertools.product((0,1),(0,1,255),(0,1,255),(0,5,6,7),(-1,0,1)):
  objects=copy.deepcopy(parent.OBJECTS);objects[0][15]=present
  yield 'wall_weapon_armor_owner',command(weapon=(flag144,flag146),overlay_cells=[[2,owner],[-1,-1],[-1,-1]],
   types=[[0,0,0,0],[0,0,0,0],[0,1,0,armor]],objects=objects)
 # Result4/5 must still pass through actual resident and speed/occupation tails.
 for owner,head,speed,occ in itertools.product((0,1),(-1,0,1,3),(0,0x3f800000,0x7fc00001),(0,32)):
  cells=copy.deepcopy(parent.CELLS);cells[0][11]=head;cells[0][6]=occ
  speeds=parent.SPEEDS.copy();speeds[0]=speed
  yield 'overlay_before_resident_speed_and_occupation',command(weapon=(1,0),overlay_cells=[[0,owner],[-1,-1],[-1,-1]],
   types=[[0,1,0,0]]*3,**{'objects':copy.deepcopy(parent.OBJECTS),'speeds':speeds,'h':parent.HEADER,'steps':[parent.STEP],
   'cells':cells})
 # Registry/Foot short circuits must not consult an overlay, even a blocking one.
 for direction in (8,2):
  cells=copy.deepcopy(parent.CELLS);cells[0][2]=0
  regs=copy.deepcopy(parent.REGS);regs[0][3]=6
  yield 'early_registry_no_overlay_query',command(types=[[1,1,0,0]]*3,cells=cells,regs=regs,
   steps=[['U',0,0,direction,0,-1,1,255]])
 cells=copy.deepcopy(parent.CELLS);cells[0][3]=5
 yield 'early_Foot_no_overlay_query',command(types=[[1,1,0,0]]*3,cells=cells)
 for target in range(3):
  yield 'absent_overlay',command(overlay_cells=[[-1,-1]]*3,steps=[['U',0,target,2,0,1,1,255]])
 # Target and opposite neighbor share the mutable fallback, including word wrap.
 for point in ((-32768,32767),(32767,0),(-1,1),(512,0)):
  for flag in (0,255):
   h=parent.HEADER.copy();h[1:3]=[-1,-1]
   cells=copy.deepcopy(parent.CELLS);cells[2][:2]=point
   yield 'shared_fallback_overlay_identity',command(h=h,cells=cells,human=255,weapon=(255,0),
    overlay_cells=[[-1,-1],[-1,-1],[1,33]],types=[[0,0,0,0],[flag,255,0,6],[0,0,0,0]],
    steps=[['U',0,2,2,0,-1,1,255],['U',0,2,7,0,-1,0,128]])
 for owner,index,mask in itertools.product((-2147483648,-33,-1,0,31,32,33,2147483647),(-1,0,33),(0,1,0x80000000)):
  houses=copy.deepcopy(parent.HOUSES);houses[0]=[index,mask]
  yield 'overlay_owner_index_wrapping',command(houses=houses,weapon=(255,0),
   overlay_cells=[[0,owner],[-1,-1],[-1,-1]],types=[[0,1,0,0]]*3)
def check_coverage(meta):
 require(meta['audited_original_calls']>=387 and {0,4,5,6,7}<=set(map(int,meta['root_returns'])))
 counts=meta['overlay_instruction_counts']
 require(all(counts.get(k,0)>0 for k in ('overlay_registry','House_control','0x703368','0x70338f','0x7033c1','0x703406','0x703428','0x703451')))
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']==current and e['evidence']['overlay_admission_only'] is True)
 require(bool(e['commands']) and len(e['commands'])==len(e['expected'])==len(e['labels']))
 for cmd in e['commands']:parse(cmd)
 check_coverage(e['evidence'])
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for name in ('exe','native','output','expectations','report'):p.add_argument('--'+name,type=Path,required=name in ('exe','native'))
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);e=json.loads(source.read_text());fingerprint=hash_file(source)
  validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  folder=private_path(a.output,a.exe);require(not folder.exists() and not a.report)
  oracle=OverlayUnitAdmissionOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   overlay,fixture=parse(cmd);oracle.overlay=overlay
   try:answer=oracle.run(*fixture)
   except BaseException:print('Failed overlay admission',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(answer);labels.append(label)
  generation=time.monotonic()-now;report=folder/'report.json'
  meta=dict(overlay_admission_only=True,Process_runtime_excluded=True,initial_records_and_associations_supplied=True,
   audited_original_calls=oracle.audit_calls,overlay_instruction_counts=dict(oracle.overlay_counts),root_returns=oracle.root_results)
 check_coverage(meta)
 for label,row in zip(labels,expected):
  if label.startswith('early_'):require('o' not in row[::4] and 'u' not in row[::4])
  if label=='absent_overlay':require('o' in row[::4] and 'u' not in row[::4])
 now=time.monotonic();proc=subprocess.run([str(a.native),'--overlay'],input='\n'.join(commands)+'\n',text=True,capture_output=True)

 if proc.returncode:raise RuntimeError(proc.stderr)
 actual=[row.split() for row in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(row,wanted) in enumerate(zip(actual,expected)):
  if row!=wanted:raise AssertionError((i,labels[i],row,wanted))
 safety=[([],command()),(['--overlay'],parent.command()),(['--overlay'],'V 0'),
  (['--overlay'],command()+' trailing'),(['--overlay'],command(human=256)),
  (['--overlay'],command(overlay_cells=[[3,0],[-1,-1],[-1,-1]]))]
 for args,cmd in safety:
  refused=subprocess.run([str(a.native),*args],input=cmd+'\n',text=True,capture_output=True)
  require(refused.returncode!=0 and bool(refused.stderr.strip()))
 comparison=time.monotonic()-now;require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=len(commands),executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),
  original_instructions_modified=False,native_safety_refusals=len(safety),original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(len(commands),'complete overlay admission calls PASS')
if __name__=='__main__':main()
