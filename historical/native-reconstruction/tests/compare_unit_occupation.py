#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Unit occupation writes with actual map/Cell floor children."""
import argparse,itertools,json,math,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_map_floor_height import SOURCES as FLOOR_SOURCES,number
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_occupation import verify
SOURCES=tuple(dict.fromkeys((*FLOOR_SOURCES,'src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp',
 'src/sim/UnitOccupation.hpp','src/sim/UnitOccupation.cpp','tests/unit_occupation_vectors.cpp',
 'tests/original_unit_occupation.py','tests/compare_unit_occupation.py','tools/verify_unit_occupation.py')))
FIELDS=('op','x','y','z','resident','level','ramp','otherLevel','otherRamp','flevel','framp',
 'flags','otherFlags','fflags','threshold','mutation','current')
DEFAULT=[1,51*256+128,72*256+128,416,3,4,0,2,7,3,13,0,0x100,0,128,0,104]
INITIAL=[0xaabbcc21,0x12345678,0x99887766,0xabcdef01,0x87654321,0x13579bdf]
def row(**kwargs):
 v=DEFAULT.copy()
 for k,n in kwargs.items():v[FIELDS.index(k)]=n
 return v
def command(rows=None,initial=None,planes=None,mode=0):
 return 'U '+' '.join(map(str,[mode,*(INITIAL if initial is None else initial),*([0]*100 if planes is None else planes),len(rows or [DEFAULT]),*[v for r in (rows or [DEFAULT]) for v in r]]))
def parse(cmd):
 p=cmd.split();assert p[0]=='U';v=list(map(int,p[1:]));mode=v[0];initial=v[1:7];planes=v[7:107];count=v[107]
 assert mode in range(4) and len(initial)==6 and all(0<=n<1<<32 for n in initial)
 assert len(planes)==100 and all(0<=n<1<<64 and math.isfinite(number(n)) for n in planes)
 assert 1<=count<=64 and len(v)==108+17*count
 rows=[v[i:i+17] for i in range(108,len(v),17)]
 for r in rows:
  assert all(-2147483648<=n<=2147483647 for i,n in enumerate(r) if i not in (11,12,13))
  op,x,y,z,resident,level,ramp,ol,orr,fl,fr,flags,of,ff,threshold,mutation,current=r
  assert op in (0,1) and resident in range(4) and mutation in range(4)
  assert all(-128<=n<=127 for n in (level,ol,fl)) and all(n in range(21) for n in (ramp,orr,fr))
  assert all(0<=n<1<<32 for n in (flags,of,ff))
 return mode,initial,planes,rows
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Unit occupation engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Unit occupation source/inspection identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Unit occupation counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed Unit occupation command') from None
def generate(a):
 from original_unit_occupation import UnitOccupationOracle
 o=UnitOccupationOracle(a.exe);pe=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',pe.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];groups={};steps=0;probes=0;rng=random.Random(0x707980)
 def add(label,rows,initial=None,mode=None):
  nonlocal steps
  cmd=command(rows,initial,planes,len(commands)%4 if mode is None else mode);_,ini,pl,rs=parse(cmd)
  commands.append(cmd);expected.append(o.run_occupation(ini,pl,rs));labels.append(label);groups[label]=groups.get(label,0)+1;steps+=len(rs)
 def signed(n):return ((n+0x80000000)&0xffffffff)-0x80000000
 for ramp,level in itertools.product(range(21),(-1,0,4)):
  pilot=o.run_occupation(INITIAL,planes,[row(ramp=ramp,level=level)]);height=int(pilot[pilot.index('H')+1]);probes+=1
  for flags,threshold,delta in itertools.product((0,0x100),(-2147483648,-1,0,128,2147483647),(-1,0,1)):
   z=signed(height+threshold+delta)
   add('actual_floor_boundaries_signed_wrap_bridge_asymmetry_repeated_dword_writes',
    [row(op=op,ramp=ramp,level=level,flags=flags,z=z,threshold=threshold) for op in (1,1,0,0)])
 coords=[(-2147483648,-2147483648),(2147483647,2147483647),(-257,256),(-256,256),(-255,-1),(-1,-1),(0,0),
  (255,255),(256,256),(131072,-256),(-131072,256),(16777216,0),(0,16777216),(51*256+128,72*256+128)]
 for (x,y),resident in itertools.product(coords,range(4)):
  add('actual_full_signed_division_combined_alias_fallback_identity_and_both_fields',
   [row(op=op,x=x,y=y,resident=resident,z=rng.choice((-2147483648,-1,0,1,2147483647)),
    ramp=rng.randrange(21),otherRamp=rng.randrange(21),framp=rng.randrange(21),
    flags=rng.getrandbits(32),otherFlags=rng.getrandbits(32),fflags=rng.getrandbits(32)) for op in (1,0,1,0)])
 for case in range(128):
  add('arbitrary_upper_bits_no_reference_counts_and_warm_lazy_floor_state',
   [row(op=(i+case)%2,current=(104,208,-104)[i%3],ramp=rng.randrange(21),level=rng.randrange(-128,128),
    z=rng.randint(-2147483648,2147483647),threshold=rng.randint(-2147483648,2147483647),flags=rng.getrandbits(32)) for i in range(8)],
   initial=[rng.getrandbits(32) for _ in range(6)])
 for mutation,resident,flags,op in itertools.product((1,2,3),range(4),(0,0x100),(0,1)):
  add('diagnostic_boundary_mutation_saved_Cell_and_delayed_coordinate_flag_threshold_reads',
   [row(op=op,mutation=mutation,resident=resident,flags=flags,fflags=flags,z=z) for z in (-1,415,416,2147483647)])
 for mode,ramp in itertools.product(range(4),(0,1,7,13,20)):
  add('four_incoming_native_FP_modes_restore_with_actual_floor',
   [row(op=op,ramp=ramp,level=-1,z=z,flags=0x100) for op,z in ((1,1),(0,-1),(1,2147483647))],mode=mode)
 return commands,expected,labels,{'groups':groups,'query_steps':steps,'original_floor_boundary_discovery_calls':probes,
  'audited_complete_roots':o.audit_calls,'actual_entries':o.entries,'actual_map_queries':o.map_queries,'actual_floor_queries':o.floor_queries,
  'actual_occupation_dword_stores':o.occupation_stores,'actual_elevated_mark_stores':o.elevated_marks,'actual_elevated_unmark_stores':o.elevated_unmarks,
  'diagnostic_supplied_scalar_stores':o.diagnostic_stores,'initial_cell_map_global_and_occupation_state_supplied':True,
  'actual_Mark_membership_admission_reservation_runtime_and_frames_unverified':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-occupation-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-occupation-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Unit occupation destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native Unit occupation: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Unit occupation result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Unit occupation {i} {labels[i]}: {x} != {y}; {commands[i]}')
 safety=['','U 0',command([row(op=2)]),command([row(resident=4)]),command([row(ramp=21)]),command([row(mutation=4)]),command([row(x=2147483648)]),command(mode=4),command(initial=[-1]*6),command()+' trailing']
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Native Unit occupation refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Unit occupation run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} Unit occupation sequences: PASS ({result["evidence_mode"]}, {metadata["query_steps"]:,} queries, {elapsed:.3f}s native)')
if __name__=='__main__':main()
