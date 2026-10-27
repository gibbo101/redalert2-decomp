#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base next-Cell early paths, immutable arenas and ordered lookup evidence."""
import argparse,copy,itertools,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_next_cell import verify
SOURCES=('src/sim/UnitNextCell.hpp','src/sim/UnitNextCell.cpp','src/sim/UnitAdmission.hpp',
 'src/sim/MovementGate.hpp','src/sim/UnitDiscovery.hpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/Targeting.hpp','src/sim/OriginalMath.hpp',
 'tests/unit_next_cell_vectors.cpp','tests/original_unit_next_cell.py','tests/compare_unit_next_cell.py',
 'tests/test_unit_next_cell_evidence.py','tools/verify_unit_next_cell.py','tests/original_presentation.py',
 'tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py','CMakeLists.txt')
SLOTS=[72*512+51,72*512+50]
# x/y, signed level, flags, primary/elevated occupation and ignored resident pointers.
CELLS=[[51,72,0,0,0,0,0xdeadbeef,0x80000000],
 [50,72,4,0,0,0,0x80000000,0xdeadbeef],[-7,5,-4,0,0,0,0xdeadbeef,0xdeadbeef]]
ACTOR=[50*256+128,72*256+128,0,0,1]
STEPS=[[51,72,1]]
def command(slots=None,cells=None,actor=None,steps=None):
 steps=STEPS if steps is None else steps;flat=lambda rows:itertools.chain.from_iterable(rows)
 return 'N '+' '.join(map(str,[*(SLOTS if slots is None else slots),*flat(CELLS if cells is None else cells),
  *(ACTOR if actor is None else actor),len(steps),*flat(steps)]))
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported next-Cell command')
def parse(cmd):
 t=cmd.split();require(t and t[0]=='N');i=1
 def read(n):
  nonlocal i
  v=list(map(int,t[i:i+n]));require(len(v)==n);i+=n;return v
 slots=read(2);cells=[read(8) for _ in range(3)];actor=read(5);count=read(1)[0]
 require(all(-1<=x<262144 for x in slots) and (slots[0]==-1 or slots[0]!=slots[1]))
 for c in cells:require(all(-32768<=x<=32767 for x in c[:2]) and -128<=c[2]<=127 and all(0<=x<1<<32 for x in c[3:]))
 require(all(-2147483648<=x<=2147483647 for x in actor[:3]) and all(0<=x<=255 for x in actor[3:]))
 require(1<=count<=128);steps=[read(3) for _ in range(count)]
 for x,y,w in steps:require(-32768<=x<=32767 and -32768<=y<=32767 and 0<=w<1<<32 and (not actor[4] or w&255))
 require(i==len(t));return slots,cells,actor,steps
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Next-Cell engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Next-Cell identity differs')
 if not(e.get('commands') and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[]))):raise ValueError('Next-Cell counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (ValueError,IndexError,TypeError,OverflowError):raise ValueError('Malformed next-Cell command') from None
def generate(a):
 from original_unit_next_cell import UnitNextCellOracle
 o=UnitNextCellOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,**kwargs):
  cmd=command(**kwargs);result=o.run(*parse(cmd));commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1
 for crusher,bridge,flags,warning in itertools.product((0,1,255),(0,1,128,255),(0,0x100,0x200,0x300,0x80000100),(1,2,255,0x10001)):
  cells=copy.deepcopy(CELLS);cells[0][3]=flags
  # Different nonselected occupation tests distinguish primary and elevated.
  if flags&0x100:cells[0][4]=31;cells[0][5]=0xffffffe0
  else:cells[0][4]=0xffffffe0;cells[0][5]=31
  actor=ACTOR.copy();actor[3:]=[bridge,crusher]
  add('crusher_raw_bytes_warning_low_byte_layer_selection_and_ignored_lists',cells=cells,actor=actor,steps=[[51,72,warning]])
 for target,current in itertools.product((-128,-127,-4,0,1,123,124,127),repeat=2):
  cells=copy.deepcopy(CELLS);cells[0][2:4]=[target,0x100];cells[1][2]=current
  # High occupation and bit5 must not deliver a warning or traverse the lists.
  cells[0][4:6]=[0x80000020,0x7fffffe0]
  add('signed_byte_level_plus_four_without_byte_wrap',cells=cells)
 for x,y in itertools.product((-2147483648,-65537,-65536,-257,-256,-255,-1,0,1,255,256,257,65535,65536,2147483647),repeat=2):
  cells=copy.deepcopy(CELLS);cells[0][3]=cells[2][3]=0x100
  actor=ACTOR.copy();actor[:3]=[x,y,-2147483648]
  add('signed_divide_toward_zero_then_word_projection_and_current_fallback',cells=cells,actor=actor)
 for slots,point in itertools.product(([-1,-1],[0,262143],[511,512]),((-32768,32767),(32767,-32768),(512,-1),(-1,1),(511,511),(0,0),(51,72))):
  cells=copy.deepcopy(CELLS);cells[2][3]=0x100
  add('combined_signed_word_index_sparse_slots_and_shared_fallback_sequences',slots=slots,cells=cells,
   steps=[[*point,1],[51,72,255],[*point,0x10001]])
 for warning,occ in itertools.product((0,256,0xffffffff),(0,1,31,32,0xffffffff)):
  actor=ACTOR.copy();actor[4]=0;cells=copy.deepcopy(CELLS);cells[0][3:6]=[0x100,occ,occ]
  add('noncrusher_actual_unpromoted_ability_before_warning_or_occupation',actor=actor,cells=cells,steps=[[51,72,warning]])
 # Bridge byte short-circuits coordinate lookup, but target lookup still executes.
 for bridge in (0,1):
  actor=ACTOR.copy();actor[3]=bridge;cells=copy.deepcopy(CELLS);cells[2][3]=0x100
  add('target_and_current_fallback_alias_retains_identity_and_final_coordinates',slots=[-1,-1],actor=actor,cells=cells,
   steps=[[1,-1,1],[-32768,32767,1],[51,72,1]])
 require(all(o.entries.values()) and all(o.locations.values()))
 return commands,expected,labels,{'groups':groups,'audited_original_calls':o.audit_calls,'actual_entries':o.entries,
  'selected_instruction_counts':o.locations,'entered_distinct_instructions':len(o.instructions),'fallback_stores':o.stores,
  'immutable_arena_checks':o.audit_calls,'initial_associations_supplied':True,'runtime_excluded':True,
  'root_is_void_no_EAX_return_claim':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-next-cell-vectors');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-next-cell-v2')
 p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or dest.exists():raise ValueError('Fresh next-Cell destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native next-Cell: '+proc.stderr.strip())
 actual=[line.split() for line in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Next-Cell result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Next-Cell {i} {labels[i]} {commands[i]}: {x} != {y}')
 cells=copy.deepcopy(CELLS);cells[0][4]=1
 safety=['','N 0','bad',command()+' trailing',command(steps=[]),command(steps=[[51,72,0]]),command(cells=cells)]
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Next-Cell refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Next-Cell run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,
  'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} Unit next-Cell results / {metadata["audited_original_calls"]:,} original calls: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
