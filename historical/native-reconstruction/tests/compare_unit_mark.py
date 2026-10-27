#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential complete Object/Techno/Foot Mark for ordinary base Units."""
import argparse,itertools,json,random,subprocess,time
from pathlib import Path
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_mark import verify
SOURCES=('src/sim/UnitMark.hpp','src/sim/UnitMark.cpp','src/sim/TerrainOccupation.hpp','src/sim/TerrainOccupation.cpp',
 'src/sim/Drive.hpp','src/sim/Facing.hpp','src/sim/OriginalMath.hpp',
 'src/render/Redraw.hpp','src/render/Redraw.cpp','src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp',
 'src/render/Composition.hpp','src/assets/Shp.hpp','src/assets/Formats.hpp',
 'tests/unit_mark_vectors.cpp','tests/original_unit_mark.py','tests/compare_unit_mark.py','tools/verify_unit_mark.py',
 'tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py','tests/compare_original.py',
 'tests/presentation_evidence.py','tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py')
FIELDS=('root','present','image','owner','tacticalPresent','mapMode','counter','tactical','marked','redraw')
DEFAULT=[2,1,17,0,1,2,255,9,0,0]
def row(mode=1,x=51*256+128,y=72*256+128,z=416,limbo=0,special=0,reset=-1):return [mode,x,y,z,limbo,special,reset]
def command(rows=None,**kwargs):
 v=DEFAULT.copy()
 for k,n in kwargs.items():v[FIELDS.index(k)]=n
 rows=[row()] if rows is None else rows
 return 'M '+' '.join(map(str,[*v,len(rows),*[n for r in rows for n in r]]))
def parse(cmd):
 p=cmd.split();assert p[0]=='M';v=list(map(int,p[1:]));h=v[:10];count=v[10]
 assert len(h)==10 and 1<=count<=128 and len(v)==11+7*count
 assert all(-2147483648<=n<=2147483647 for n in v)
 root,present,image,owner,tp,mm,counter,tactical,marked,redraw=h
 assert root in range(3) and present in (0,1) and tp in (0,1)
 assert all(0<=n<=255 for n in (counter,tactical,marked,redraw))
 rows=[v[i:i+7] for i in range(11,len(v),7)]
 for mode,x,y,z,limbo,special,reset in rows:assert 0<=limbo<=255 and 0<=special<=255 and -1<=reset<=255
 return h,rows
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Unit Mark engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Unit Mark source/inspection identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Unit Mark counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,OverflowError):raise ValueError('Malformed Unit Mark command') from None
def generate(a):
 from original_unit_mark import UnitMarkOracle
 o=UnitMarkOracle(a.exe);commands=[];expected=[];labels=[];groups={};steps=0;rng=random.Random(0x4c2e60)
 def add(label,rows,**kwargs):
  nonlocal steps
  cmd=command(rows,**kwargs);h,r=parse(cmd);commands.append(cmd);expected.append(o.run_mark(h,r));labels.append(label)
  groups[label]=groups.get(label,0)+1;steps+=len(r)
 modes=(-2147483648,-1,0,1,2,3,4,255,2147483647)
 for root,marked,redraw,limbo,special,mode in itertools.product(range(3),(0,1,2,255),(0,1,255),(0,1,128,255),(0,1,255),modes):
  add('complete_three_wrappers_byte_gates_mode2_bypass_unknown_modes_and_special_service',
   [row(mode,limbo=limbo,special=special)],root=root,marked=marked,redraw=redraw)
 for root,present,tp,image,owner in itertools.product(range(3),(0,1),(0,1),(-2147483648,0,2147483647),(-2147483648,-1,0,2147483647)):
  add('actual_nullable_type_image_owner_and_redraw_tactical_associations',
   [row(mode,special=(i%3)*127,reset=0 if i%4==0 else -1) for i,mode in enumerate((1,2,0,3,1,2,0,2,3,0))],
   root=root,present=present,tacticalPresent=tp,image=image,owner=owner,mapMode=rng.choice((-2147483648,-1,0,1,2,2147483647)),
   counter=rng.randrange(256),tactical=rng.randrange(256),marked=0,redraw=0)
 coords=[(-2147483648,2147483647),(-16777217,16777216),(-8388608,8388607),(-257,257),(-256,256),(-255,255),
  (-1,1),(0,0),(255,-255),(256,-256),(16777216,0),(51*256+128,72*256+128),(2147483647,-2147483648)]
 for root,(x,y) in itertools.product(range(3),coords):
  add('actual_signed_divide_before_word_truncation_and_repeated_membership_coordinates',
   [row(mode,x,y,rng.randint(-2147483648,2147483647),reset=0) for mode in (1,0,3,2,0)],root=root)
 for root,case in itertools.product(range(3),range(64)):
  add('long_mark_remove_redraw_cycles_with_supplied_frame_dirty_resets',
   [row(rng.choice(modes),rng.randint(-2147483648,2147483647),rng.randint(-2147483648,2147483647),rng.randint(-2147483648,2147483647),
    rng.choice((0,0,1,255)),rng.choice((0,0,2,255)),rng.choice((-1,-1,0,255))) for _ in range(32)],
   root=root,marked=rng.choice((0,1,128,255)),redraw=rng.choice((0,1,128,255)))
 return commands,expected,labels,{'groups':groups,'query_steps':steps,'audited_complete_roots':o.audit_calls,'actual_entries':o.entries,
  'actual_redraw_virtual_calls':o.redraw_calls,'actual_selected_byte_stores':o.stores,
  'supplied_map_membership_calls':o.membership_calls,'supplied_special_event_calls':o.event_calls,
  'initial_actor_type_house_nonnull_Drive_tactical_records_and_row_dirty_resets_supplied':True,
  'actual_membership_occupation_Process_startup_runtime_and_frames_unverified':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-mark-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-mark-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Unit Mark destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native Unit Mark: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Unit Mark result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Unit Mark {i} {labels[i]}: {x} != {y}; {commands[i]}')
 safety=['','M 0',command(root=3),command(present=2),command(marked=-1),command(redraw=256),command(tacticalPresent=2),command(counter=256),command(image=2147483648),command([row(limbo=256)]),command([row(reset=-2)]),command(rows=[]),command()+' trailing']
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Native Unit Mark refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Unit Mark run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} Unit Mark sequences: PASS ({result["evidence_mode"]}, {metadata["query_steps"]:,} calls, {elapsed:.3f}s native)')
if __name__=='__main__':main()
