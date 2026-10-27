#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Unit/Building/Terrain occupied Cell passability."""
import argparse,itertools,json,subprocess,time
from pathlib import Path
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_unit_membership_discovery import SOURCES as MEMBERSHIP_SOURCES
from compare_resident_cell import SOURCES as CELL_SOURCES
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_occupied_cell import verify
SOURCES=tuple(dict.fromkeys((*MEMBERSHIP_SOURCES,*CELL_SOURCES,
 'src/assets/OccupiedCellPassability.hpp','src/assets/OccupiedCellPassability.cpp',
 'tests/occupied_cell_vectors.cpp','tests/original_occupied_cell.py','tests/compare_occupied_cell.py','tools/verify_occupied_cell.py')))
HEADER=[80,0,0,80,85,51,72,4,0,0,0,0,0,0,0,0,*([0x3f800000]*11),0,17,0]
UNIT=[1,-1,0,0,0,0,0,0]
def command(h=None,actors=None):
 actors=[UNIT] if actors is None else actors
 return 'P '+' '.join(map(str,[*(HEADER if h is None else h),len(actors),*[n for r in actors for n in r]]))
def parse(cmd):
 p=cmd.split();assert p[0]=='P';v=list(map(int,p[1:]));h=v[:31];assert len(h)==31
 assert all(-2147483648<=n<=2147483647 for n in h[:16]) and all(0<=n<1<<32 for n in h[16:27]) and all(-2147483648<=n<=2147483647 for n in h[27:30])
 x,y,level,ramp,land,present,ol,crush,wall,rock,rubble=h[5:16]
 assert -32768<=x<=32767 and -32768<=y<=32767 and 0<=y*512+x<262144 and -128<=level<=127 and 0<=ramp<=255 and 0<=land<11 and present in (0,1) and 0<=ol<11 and all(0<=n<=255 for n in (crush,wall,rock,rubble))
 count=h[30];assert 0<=count<=8 and -1<=h[29]<count and len(v)==31+8*count
 actors=[v[i:i+8] for i in range(31,len(v),8)]
 for kind,next,b,a,human,mission,t,s in actors:assert kind in (1,6,36) and -1<=next<count and all(0<=n<=255 for n in (b,a,human)) and all(-2147483648<=n<=2147483647 for n in (mission,t,s))
 seen=set();node=h[29]
 while node!=-1:assert node not in seen;seen.add(node);node=actors[node][1]
 return h,actors
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Occupied Cell engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Occupied Cell identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Occupied Cell counts differ')
 for c in e['commands']:
  try:parse(c)
  except (AssertionError,ValueError,IndexError,OverflowError):raise ValueError('Malformed occupied Cell command') from None
def generate(a):
 from original_occupied_cell import OccupiedCellOracle
 o=OccupiedCellOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,h=None,actors=None):
  cmd=command(h,actors);args=parse(cmd);commands.append(cmd);expected.append(o.run(*args));labels.append(label);groups[label]=groups.get(label,0)+1
 for land,speed,overlay in itertools.product(range(11),(0,0x80000000,0x3c23d70a,0x3c23d70b,0x3f800000,0xbf800000,0x7fc00001),range(6)):
  h=HEADER.copy();h[9]=land;h[16:27]=[speed]*11
  if overlay:h[10:16]=[1,land,int(overlay==1),int(overlay==2),int(overlay==3),int(overlay==4)]
  add('permission_overlay_land_speed_gates_precede_Unit_list',h,[[1,1,0,0,0,0,0,0],UNIT])
 for a,b,owner,mission in itertools.product((0,1,255),(0,1,255),(0,1,255),(-1,0,8,12,15,2147483647)):
  add('Building_type_House_mission_and_overwritten_intermediate_six',actors=[[1,1,0,0,0,0,0,0],[6,2,b,a,owner,mission,0,0],UNIT])
 for theater,t,s in itertools.product((-2147483648,-1,0,1,2,2147483647),(-1,0,7,8,2147483647),(-1,0,7,8,2147483647)):
  h=HEADER.copy();h[27]=theater;add('Terrain_exact_theater_one_type_field_and_early_return',h,[[1,1,0,0,0,0,0,0],[36,2,0,0,0,0,t,s],UNIT])
 for early,terrain,theater in itertools.product((0,1,255),(0,7,8),(0,1)):
  h=HEADER.copy();h[27]=theater
  add('mixed_list_order_and_intermediate_then_Terrain_final_store',h,[[6,1,1,0,0,0,0,0],[6,2,0,1,early,0,0,0],[36,3,0,0,0,0,terrain,7],UNIT])
 for shape in ([0,0,0,0,0],[80,0,0,1,1],[-2147483648,2147483647,-2147483648,2147483647,2147483647]):
  h=HEADER.copy();h[:5]=shape;add('permission_outside_and_wrapped_shape_before_any_kind',h)
 h=HEADER.copy();h[29]=-1;add('empty_list_final_zero',h,[])
 assert all(o.entries[hex(a)] for a in (0x478f40,0x55a660,0x70a2d0,0x453c40,0x6e4b00))
 return commands,expected,labels,{'groups':groups,'audited_original_calls':o.audit_calls,'actual_entries':o.entries,'selected_original_stores':o.selected_stores,
  'actual_permission_lookup_and_kind_leaves':True,'initial_actor_type_House_scenario_map_speed_inputs_supplied':True,'Process_runtime_frame_parity_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/occupied-cell-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/occupied-cell-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh occupied Cell destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native occupied Cell: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Occupied Cell result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   first=next((j for j,(xx,yy) in enumerate(zip(x,y)) if xx!=yy),min(len(x),len(y)))
   raise AssertionError(f'Occupied Cell {i} {labels[i]} at {first}: {x[max(0,first-8):first+12]} != {y[max(0,first-8):first+12]}; {commands[i]}')
 safety=['','P 0',command()+' trailing',command(actors=[[1,0,0,0,0,0,0,0]]),command(actors=[[2,-1,0,0,0,0,0,0]])]
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Occupied Cell safety refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Occupied Cell run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} occupied Cell results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
