#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Unit Mark/map/Cell membership with actual occupation/floors."""
import argparse,itertools,json,math,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_unit_mark import SOURCES as MARK_SOURCES
from compare_unit_occupation import SOURCES as OCC_SOURCES
from compare_map_floor_height import number
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_membership import verify
SOURCES=tuple(dict.fromkeys((*MARK_SOURCES,*OCC_SOURCES,'src/sim/UnitMembership.hpp','src/sim/UnitMembership.cpp',
 'tests/unit_membership_vectors.cpp','tests/original_unit_membership.py','tests/compare_unit_membership.py','tools/verify_unit_membership.py')))
HEADER=[0,0,1,0,1,0,17,128,0]
RECORDS=[[4,0,0,0xaabbcc01,0x12345678,-1,-1],[2,7,0x100,0x99887766,0xabcdef01,-1,-1],
 [3,13,0,0x87654321,0x13579bdf,-1,-1],[1,20,0x100,0x24681357,0xfedcba98,-1,-1]]
FIELDS=('root','mode','actor','cell','x','y','z','alt','eligible')
DEFAULT=[4,1,0,0,51*256+128,72*256+128,416,0,1]
def row(**kwargs):
 v=DEFAULT.copy()
 for k,n in kwargs.items():v[FIELDS.index(k)]=n
 return v
def command(rows=None,header=None,records=None,links=None,planes=None):
 rows=[row()] if rows is None else rows
 return 'U '+' '.join(map(str,[*(HEADER if header is None else (header+[0] if len(header)==8 else header)),*[v for r in (RECORDS if records is None else records) for v in r],
  *([-1]*4 if links is None else links),*([0]*100 if planes is None else planes),len(rows),*[n for r in rows for n in r]]))
def parse(cmd):
 p=cmd.split();assert p[0]=='U';v=list(map(int,p[1:]));h=v[:9];records=[v[i:i+7] for i in range(9,37,7)];links=v[37:41];planes=v[41:141];count=v[141]
 assert len(h)==9 and all(-2147483648<=n<=2147483647 for n in h) and all(0<=n<=255 for n in h[:3])
 assert h[8] in range(8)
 assert len(links)==4 and all(-1<=n<=3 for n in links)
 for l,r,f,g,e,a,b in records:assert -128<=l<=127 and 0<=r<=20 and all(0<=n<1<<32 for n in (f,g,e)) and -1<=a<=3 and -1<=b<=3
 assert len(planes)==100 and all(0<=n<1<<64 and math.isfinite(number(n)) for n in planes)
 assert 1<=count<=128 and len(v)==142+9*count
 rows=[v[i:i+9] for i in range(142,len(v),9)]
 for r in rows:
  assert all(-2147483648<=n<=2147483647 for n in r)
  root,mode,actor,cell,x,y,z,alt,eligible=r
  assert root in range(5) and actor in (-1,0) and cell in range(4) and 0<=alt<=255 and 0<=eligible<=255 and (root!=4 or actor==0)
  if root in (2,3,4) and actor==0 and h[2] and (root!=4 or mode in (0,1,3)):
   def div(n):return n//256 if n>=0 else -((-n)//256)
   xx=((div(x)+32768)%65536)-32768;yy=((div(y)+32768)%65536)-32768
   assert 0<=yy*512+xx<262144
 return h,records,links,planes,rows
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Unit membership engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Unit membership source/inspection identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Unit membership counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed Unit membership command') from None
def generate(a):
 from original_unit_membership import UnitMembershipOracle
 o=UnitMembershipOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];groups={};steps=0;rng=random.Random(0x54ab70)
 def add(label,rows,header=None,records=None,links=None):
  nonlocal steps
  cmd=command(rows,header,records,links,planes);h,r,l,p,rs=parse(cmd);commands.append(cmd);expected.append(o.run_membership(h,r,l,p,rs));labels.append(label)
  groups[label]=groups.get(label,0)+1;steps+=len(rs)
 for root,alt,eligible,profile in itertools.product((0,1),(0,1,255),(0,1,128,255),range(5)):
  rec=[r.copy() for r in RECORDS];links=[-1]*4
  if profile==1:rec[0][5+bool(alt)]=0;links=[1,2,3,-1]
  elif profile==2:rec[0][5+bool(alt)]=1;links=[3,2,0,-1]
  elif profile==3:rec[0][5+bool(alt)]=1;links=[3,2,3,-1]
  elif profile==4:rec[0][5+bool(alt)]=1;links=[3,0,-1,-1]
  add('actual_Unit_list_empty_head_middle_absent_and_head_next_guard',
   [row(root=root,alt=alt,eligible=eligible),row(root=1,alt=alt,eligible=eligible)],records=rec,links=links)
 for v1,v2,gate in itertools.product((0,1,255,256,-1),(0,1,255,256,-1),(0,1,-1)):
  add('visibility_low_byte_short_circuit_repeat_center_floor_and_notification_gate',
   [row(root=0),row(root=1)],header=[0,0,1,gate,v1,v2,-2147483648,128])
 for ramp,level,flags in itertools.product(range(21),(-1,0,4),(0,0x100)):
  rec=[r.copy() for r in RECORDS];rec[0][:3]=[level,ramp,flags];z=level*104+128
  add('joined_actual_Cell_floor_Unit_occupation_ramps_signed_levels_and_bridge_asymmetry',
   [row(root=0,z=z),row(root=1,z=z),row(root=0,z=z),row(root=1,z=z)],records=rec)
 for of,uf,tf in itertools.product((0,1,128,255),(0,1,128,255),(0,1,128,255)):
  add('actual_map_parents_type_gate_lazy_Object_Unit_foundation_atexit_and_warm_copy',
   [row(root=root) for root in (2,3,2,3)],header=[of,uf,tf,0,1,0,17,128])
 coords=[(51*256+128,72*256+128),(52*256+1,72*256+255),(53*256,72*256),(54*256,72*256),
  (16777216+51*256+128,72*256+128),(-256,256),(0,0),(2147483647,256)]
 for (x,y),alt,eligible in itertools.product(coords,(0,1,255),(0,1,255)):
  add('map_word_coordinates_full_occupation_coordinates_null_slots_and_shared_fallback',
   [row(root=root,x=x,y=y,alt=alt,eligible=eligible) for root in (2,3,2,3)])
 for alt,tf,eligible in itertools.product((0,1,255),(0,1,255),(0,1,255)):
  add('complete_Mark_map_Cell_occupation_cycles_mode2_bypass_rejection_and_redraw',
   [row(mode=mode,alt=alt,eligible=eligible) for mode in (1,1,2,0,0,3,2,0,4,3,0)],header=[0,0,tf,1,0,0,17,128])
 for root in range(4):add('null_actor_parent_and_Cell_gates',[row(root=root,actor=-1)])
 for case in range(64):
  rec=[r.copy() for r in RECORDS]
  for r in rec:r[:5]=[rng.randrange(-128,128),rng.randrange(21),rng.getrandbits(32),rng.getrandbits(32),rng.getrandbits(32)]
  alt=rng.choice((0,1,255));x=rng.choice((51,52,53))*256+rng.randrange(256);y=72*256+rng.randrange(256)
  add('long_actual_Mark_shared_occupation_and_upper_bits_with_warm_lazy_planes',
   [row(mode=(1,2,0,3,0)[i%5],x=x,y=y,z=rng.randint(-2147483648,2147483647),alt=alt,eligible=rng.choice((0,1,255))) for i in range(30)],records=rec,
   header=[rng.randrange(256),rng.randrange(256),255,rng.choice((0,1,-1)),rng.choice((0,1,256)),rng.choice((0,1,256)),rng.randint(-2147483648,2147483647),rng.randint(-2147483648,2147483647)])
 for mutation,eligible,root in itertools.product(range(1,8),(0,1),(0,2,4)):
  add('diagnostic_notification_live_eligibility_coordinates_slot_replacement_and_fallback_reload',
   [row(root=root,eligible=eligible),row(root=3 if root==2 else 1 if root==0 else 4,mode=0,eligible=eligible)],
   header=[0,0,1,1,1,0,17,128,mutation])
 return commands,expected,labels,{'groups':groups,'query_steps':steps,'audited_complete_roots':o.audit_calls,'actual_entries':o.entries,
  'actual_selected_stores':o.selected_stores,'supplied_service_calls':o.service_counts,
  'initial_records_and_visibility_notification_recalculation_atexit_effects_supplied':True,
  'diagnostic_notification_mutation_sequences':42,'diagnostic_mutations_are_supplied_not_gameplay_observations':True,'Process_runtime_startup_and_frames_unverified':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-membership-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-membership-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Unit membership destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native Unit membership: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Unit membership result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Unit membership {i} {labels[i]}: {x} != {y}; {commands[i]}')
 safety=['','U 0',command(header=[256,*HEADER[1:]]),command([row(root=5)]),command([row(actor=1)]),command([row(alt=256)]),command([row(eligible=-1)]),command([row(root=2,x=-256,y=0)]),command(rows=[]),command()+' trailing']
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Native Unit membership refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Unit membership run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} Unit membership sequences: PASS ({result["evidence_mode"]}, {metadata["query_steps"]:,} calls, {elapsed:.3f}s native)')
if __name__=='__main__':main()
