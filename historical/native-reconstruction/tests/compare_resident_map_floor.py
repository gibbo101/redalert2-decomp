#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual shared Cell floor height inside later map finalization."""
import argparse,json,math,struct,subprocess,time
from pathlib import Path
import pefile
import compare_resident_map_finalization as parent
from compare_map_floor_height import bits,number,SOURCES as FLOOR_SOURCES
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_resident_map_floor import verify
SOURCES=tuple(dict.fromkeys((*parent.SOURCES,*FLOOR_SOURCES,
 'src/assets/ResidentMapFloor.hpp','src/assets/ResidentMapFloor.cpp',
 'tests/compare_resident_map_floor.py','tests/original_resident_map_floor.py',
 'tools/verify_resident_map_floor.py')))
def command(flags,h,scale,planes,current,args):
 return 'F '+' '.join(map(str,[flags,h,scale,*planes,current]))+' '+parent.command(*args)[2:]
def parse(cmd):
 p=cmd.split();assert p[0]=='F';v=list(map(int,p[1:105]));assert len(v)==104
 flags,h,scale=v[:3];planes=v[3:103];current=v[103]
 assert 0<=flags<=255 and -2147483648<=current<=2147483647
 assert all(0<=n<1<<64 and math.isfinite(number(n)) for n in [h,scale,*planes])
 args=parent.parse('G '+' '.join(p[105:]))
 assert all(row[16]==0 and 0<=row[8]<=20 for row in args[3])
 assert all(0<=row[i]<=20 for row in args[2] for i in range(7,len(row),6))
 return flags,h,scale,planes,current,*args

def identities(a):
 # Historical parent receipt supplies scenario INPUTS only, not behavior proof.
 e=json.loads(a.parent_fixture.read_text())
 validate_receipt(e,json.loads((a.parent_fixture.parent/'report.json').read_text()),hash_file(a.parent_fixture))
 return {**parent.identities(a),'inspection':verify(a.exe.read_bytes()),
  'sources':{p:hash_file(ROOT/p) for p in SOURCES},'parent_input_snapshot_sha256':hash_file(a.parent_fixture)}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Floor-finalization engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Floor-finalization source/inspection/input identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Floor-finalization counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,struct.error,OverflowError):raise ValueError('Malformed floor-finalization command') from None

def generate(a):
 from original_resident_map_floor import ResidentMapFloorOracle
 o=ResidentMapFloorOracle(a.exe);pe=pefile.PE(str(a.exe));template=list(struct.unpack('<100Q',pe.get_data(0x7d27e8-0x400000,800)))
 source=json.loads(a.parent_fixture.read_text());commands=[];expected=[];labels=[];groups={};owners=[]
 def add(label,args,flags=0xa0,h=17.25,scale=-0.125,planes=None,current=104):
  cmd=command(flags,bits(h),bits(scale),template if planes is None else planes,current,args);parsed=parse(cmd)
  result=o.run_floor(*parsed);commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1
  owners.append([int.from_bytes(o.u.mem_read(0x2400000+i*512+0x50,4),'little',signed=True) for i in range(len(args[3]))])
 for index,cmd in enumerate(source['commands']):
  args=list(parent.parse(cmd));args[3]=[r[:16]+[0] for r in args[3]]
  add('owned_all_positions_actual_floor_cliff_'+str(args[0][4]) if index>=32 else 'shared_mutation_actual_floor_and_wall_owner',args)
 common=list(parent.parse(source['commands'][0])[0]);common[:5]=[2,2,0,-1,0];common[27:42]=[-1]*15;common[50:61]=[1065353216]*11
 w,h=struct.unpack('<i',pe.get_data(0x7cfc70-0x400000,4))[0],struct.unpack('<i',pe.get_data(0x7cfcc8-0x400000,4))[0]
 buildings=[[1,255,2,owner,0,w,h,384-w*128+128,640-h*128+128,z] for owner,z in ((7,0),(9,832))]
 # Heights straddle the two candidates. At level four, ramp-zero ties (first
 # owner seven); a positive center ramp selects nine. Initial slope differs.
 warm=[bits(n) for _ in range(20) for n in (1,0,0,104,0)]
 for ramp in range(21):
  for lazy in range(8):
   level=(0,4,8,31)[lazy%4]
   types=[[1,1,1,60,30,1,0,ramp,0,0,0]]
   cells=[[1,2,0,0,level,0xffffffff,-1,0,(ramp+7)%21,0,0,0,17,91,0,41,0]]
   add('post_recalculation_ramp_level_and_independent_lazy_bits',
    [common,[2,0,0,2,2],types,cells,[[4,0,1,0,1,0,0]],[],o.frames,buildings],
    flags=0xa0|lazy,h=104,scale=104/256,planes=warm,current=104 if lazy<4 else 208)
 for ramp in range(21):
  for mode in ('cleared_wall','empty_registry','ineligible_registry'):
   types=[[1,1,1,60,30,1,0,ramp,0,0,0]]
   cells=[[1,2,0,0,4,0xffffffff,-1,0,0,0,0,0,17,91,0,41,0]]
   flags=[4,0,1,int(mode=='cleared_wall'),1,0,0]
   candidates=[] if mode=='empty_registry' else [r.copy() for r in buildings]
   if mode=='ineligible_registry':
    for r in candidates:r[0]=0
   add('no_floor_when_'+mode,[common,[2,0,0,2,2],types,cells,[flags],[[0,0,1,0,1,0]] if mode=='cleared_wall' else [],o.frames,candidates])
 # Explicit same-XY zero-floor tie versus positive-center ramp owner change.
 decisive=[]
 for ramp in (0,1):
  cells=[[1,2,0,0,4,0xffffffff,-1,0,20,0,0,0,17,91,0,41,0]]
  add('height_changes_owner_at_same_XY',[common,[2,0,0,2,2],[[1,1,1,60,30,1,0,ramp,0,0,0]],cells,[[4,0,1,0,1,0,0]],[],o.frames,buildings])
  decisive.append(owners[-1][0])
 assert decisive==[7,9],decisive
 return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_entries':o.entries,
  'audited_guest_writes':o.stores,'buffer_stores':o.buffer_stores,'actual_floor_calls':o.floor_calls,
  'lazy_flag_stores':o.flag_stores,'plane_stores':o.plane_stores,'floor_level_ramp_samples':sorted(set(map(tuple,o.floor_samples))),
  'wall_owner_calls':o.owner_calls,'actual_distances':o.distances,'height_decisive_owners':decisive,
  'initial_global_template_type_actor_house_terrain_and_resource_records_supplied':True,
  'parent_fixture_is_scenario_input_only':True,'earlier_reader_original_startup_and_runtime_not_executed':True,
  'initializer_split_store_order_not_compared':True,'palette_disabled':True}

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/resident-map-finalization-vectors')
 p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--terrain-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-map-v6/expected.json');p.add_argument('--overlay-fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json')
 p.add_argument('--parent-fixture',type=Path,default=ROOT/'private/map-depth-1006/resident-finalization-v1/expected.json');p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/resident-floor-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current);report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh floor-finalization destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native floor-finalization: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Floor-finalization result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Floor-finalization run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(f'{len(commands):,} map finalization / actual floor results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
