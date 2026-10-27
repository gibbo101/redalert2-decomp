#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare base visibility, stock initialization and Unit discovery to original."""
import argparse,itertools,json,random,subprocess,time
from pathlib import Path
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_ramp_geometry import SOURCES as GEOMETRY_SOURCES
from compare_unit_membership import SOURCES as MEMBERSHIP_SOURCES
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_discovery import verify
SOURCES=tuple(dict.fromkeys((*GEOMETRY_SOURCES,*MEMBERSHIP_SOURCES,
 'src/sim/HouseIndexAlliance.hpp','src/sim/MapVisibility.hpp','src/sim/MapVisibility.cpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp',
 'tests/unit_discovery_vectors.cpp','tests/original_unit_discovery.py','tests/compare_unit_discovery.py','tools/verify_unit_discovery.py')))
DHEADER=[0,0,17,0,0,0,0,0,14,-1,255,0,0]
HOUSES=[[0,0,7,0,8,9],[1,0,10,0,11,12]]
VRECORDS=[[72*512+51,51,72,0,0],[73*512+52,52,73,0,0],[-1,32767,-32768,0,0],[-1,-7,5,0,0]]
def visibility(h,records=None):return 'V '+' '.join(map(str,[*h,*[v for r in (VRECORDS if records is None else records) for v in r]]))
def discovery(h=None,houses=None,discoverers=None):
 ds=[0,0,1,1,-1] if discoverers is None else discoverers
 return 'D '+' '.join(map(str,[*(DHEADER if h is None else h),*[v for r in (HOUSES if houses is None else houses) for v in r],len(ds),*ds]))
def parse(cmd):
 p=cmd.split();kind=p[0];v=list(map(int,p[1:]));i32=lambda n:-2147483648<=n<=2147483647;byte=lambda n:0<=n<=255
 assert kind in ('S','V','D','H','Q')
 if kind=='S':assert len(v)==1 and v[0] in range(4);return kind,v
 if kind=='H':assert len(v)==3 and i32(v[0]) and all(byte(n) for n in v[1:]);return kind,v
 if kind=='Q':assert len(v)==4 and all(i32(v[i]) for i in (0,1,3)) and byte(v[2]);return kind,v
 if kind=='V':
  assert len(v)==28;h=v[:8];r=[v[i:i+5] for i in range(8,28,5)]
  secondary,d,mode,override,h13,x,y,z=h;assert secondary in (0,1) and all(i32(n) for n in h) and byte(h13)
  shortcut=secondary and mode and override and h13
  assert shortcut or (d!=0 and not(z==-2147483648 and d==-1))
  slots=[]
  for i,(slot,x,y,a,b) in enumerate(r):
   assert -1<=slot<262144 and -32768<=x<=32767 and -32768<=y<=32767 and 0<=a<1<<32 and 0<=b<1<<32 and (i!=3 or slot==-1)
   if slot!=-1:assert slot not in slots;slots.append(slot)
  return kind,(h,r)
 assert len(v)>=27;h=v[:13];houses=[v[13:19],v[19:25]];count=v[25];ds=v[26:]
 assert all(i32(n) for n in h) and h[3] in (-1,0,1) and h[4] in (0,1) and all(byte(h[i]) for i in (5,6,7,10)) and h[11] in (0,1) and h[12] in (0,1)
 assert all(byte(n) for r in houses for n in r) and 1<=count<=128 and len(ds)==count and all(d in (-1,0,1) for d in ds)
 return kind,(h,houses,ds)
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
 'prepared_inputs':{k:hash_file(getattr(a,k+'_data')) for k in ('geometry','render','raster','direction')}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Discovery engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Discovery identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Discovery counts differ')
 for c in e['commands']:
  try:parse(c)
  except (AssertionError,ValueError,IndexError,OverflowError):raise ValueError('Malformed discovery command') from None
def generate(a):
 from original_unit_discovery import UnitDiscoveryOracle
 o=UnitDiscoveryOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x568140)
 def add(cmd,label,result=None):
  kind,args=parse(cmd)
  if result is None:result={'V':lambda:o.visibility(*args),'D':lambda:o.discovery(*args),'H':lambda:o.house(*args),'Q':lambda:o.queue(*args)}[kind]()
  commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1
 for seed in range(4):
  result=o.stock_visibility(seed)
  for mode in range(4):add(f'S {mode}','third_stock_numeric_chain_and_actual_direction_initializer',result)
 assert o.stock_divisor==104
 for secondary,q,bits in itertools.product((0,1),range(-7,8),range(4)):
  # Keep projected input in Cell0; odd-path neighbor selects Cell1 from stored coords.
  shift=int(q/2)+int(q&1);rec=[r.copy() for r in VRECORDS]
  rec[0][3+secondary]=(8 if secondary==0 else 2) if bits&1 else 0;rec[1][3+secondary]=(8 if secondary==0 else 2) if bits&2 else 0
  add(visibility([secondary,104,0,0,0,(51+shift)*256+128,(72+shift)*256+128,q*104],rec),'signed_odd_even_projection_and_ordered_selected_neighbor_flags')
 for secondary,mode,h13,override in itertools.product((0,1),(0,1,-1),(0,1,255),(0,1,-1)):
  add(visibility([secondary,104,mode,override,h13,13184,18560,104]),'secondary_three_gate_shortcut_before_projection')
 for d,z in ((0,0),(-1,-2147483648)):
  add(visibility([1,d,1,-1,255,0,0,z]),'secondary_shortcut_before_unsafe_division')
 for secondary,(cx,cy),blocked in itertools.product((0,1),((32767,-32768),(-1,1),(0,0),(51,72),(-32768,32767)),(0,1)):
  rec=[r.copy() for r in VRECORDS];rec[0][1:3]=[cx,cy]
  nx=((cx+1+32768)%65536)-32768;ny=((cy+1+32768)%65536)-32768;index=ny*512+nx
  rec[1][0]=index if 0<=index<262144 and index!=rec[0][0] else -1
  rec[1][3+secondary]=rec[3][3+secondary]=(8 if secondary==0 else 2)*blocked
  add(visibility([secondary,104,0,0,0,52*256+128,73*256+128,104],rec),'neighbor_uses_stored_Cell_words_with_wrap_and_fallback_identity')
 coords=[(-2147483648,2147483647),(2147483647,-2147483648),(-257,-255),(-256,256),(0,0),(16777216+13184,18560),(13184,18560)]
 for secondary,(x,y),z in itertools.product((0,1),coords,(-2147483648,-313,-105,-104,-1,0,103,104,313,2147483647)):
  add(visibility([secondary,104,0,0,0,x,y,z]),'word_wrap_signed_divide_full_boundaries_and_shared_fallback_rewrites')
 for i in range(120):
  h=[rng.randrange(2),rng.choice((1,-1,2,-2,103,104,105,2147483647,-2147483648)),0,0,0,rng.randint(-2147483648,2147483647),rng.randint(-2147483648,2147483647),rng.randint(-2147483647,2147483647)]
  rec=[r.copy() for r in VRECORDS]
  for r in rec:r[1:]=[rng.randrange(-32768,32768),rng.randrange(-32768,32768),rng.getrandbits(32),rng.getrandbits(32)]
  add(visibility(h,rec),'supplied_divisor_stored_neighbor_coordinates_upper_flags_and_null_slots')
 for mode,a134,a135 in itertools.product((0,1,-1),(0,1,2,128,255),(0,1,128,255)):
  add(f'H {mode} {a134} {a135}','House_raw_nonzero_mode_and_normalized_zero_mode')
 for current,queued,requested in itertools.product((-2147483648,-1,5,14,15,19,28,2147483647),(-1,5,15,19),( -1,5,15,19,28)):
  add(f'Q {current} {queued} 255 {requested}','actual_QueueMission_second_argument_zero_rejections_and_ordered_writes')
 for current,owner,field,mission,mode in itertools.product((-1,0,1),(0,1),(0,1,255),(-1,14,15,19),(0,1)):
  h=DHEADER.copy();h[0]=mode;h[3:6]=[current,owner,field];h[8]=mission;h[9]=14
  add(discovery(h),'complete_discovery_current_other_null_repeat_owner_and_mission')
 for loading,tag,mutation,flags in itertools.product((0,1,-1),(0,1),(0,1),((0,0),(1,0),(0,255),(255,255))):
  h=DHEADER.copy();h[1]=loading;h[6:8]=flags;h[11:13]=[tag,mutation]
  add(discovery(h,discoverers=[0,0,1,-1]),'Tag_loading_already_discovered_and_diagnostic_owner_replacement')
 from verify_unit_discovery import NUMERIC,COMPLETE
 assert all(o.entries[hex(a)]>0 for a in (*NUMERIC,*COMPLETE))
 return commands,expected,labels,{'groups':groups,'audited_original_calls':o.audit_calls,'actual_entries':o.entries,
  'selected_original_stores':o.selected_stores,'supplied_Tag_calls':o.tag_calls,'stock_chain_calls':4,
  'stock_height_divisor':o.stock_divisor,'original_entry_FP':'53-bit_toward_zero',
  'initial_records_globals_CRT_flag_Tag_effects_supplied':True,'runtime_and_frame_parity_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
 p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-discovery-vectors')
 for kind,filename in (('geometry','ramp-geometry-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('direction','direction-data.bin')):p.add_argument('--'+kind+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/filename)
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-discovery-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh discovery destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 args=[str(a.native),*[str(getattr(a,k+'_data')) for k in ('geometry','render','raster','direction')]]
 now=time.monotonic();proc=subprocess.run(args,input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native discovery: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Discovery result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'Discovery {i} {labels[i]} {commands[i]}: {x} != {y}')
 safety=['','V 0','S 4','S 0 trailing','H 0 256 0','Q 14 -1 256 15',discovery()+' trailing',visibility([0,0,0,0,0,0,0,0]),visibility([0,-1,0,0,0,0,0,-2147483648])]
 for cmd in safety:
  r=subprocess.run(args,input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Discovery native refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Discovery run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),
  'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
  'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} base visibility/discovery results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
