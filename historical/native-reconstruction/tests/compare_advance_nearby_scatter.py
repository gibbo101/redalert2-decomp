#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Advance with actual admission and zero-point Cell/Unit nearby children."""
import argparse,copy,json,re,subprocess,time
from pathlib import Path
import compare_cell_nearby_scatter as parent
import compare_advance_cell_scatter as block
import compare_advance_admission as advance
from compare_advance_admission import track_cases
import struct,pefile
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_advance_nearby_scatter import verify
NATIVE=('tests/advance_nearby_scatter_vectors.cpp',*parent.NATIVE[1:],'src/render/RampGeometry.cpp','src/assets/RampGeometryData.cpp','src/assets/RasterData.cpp','src/sim/Drive.cpp','src/sim/ActorGroundState.cpp','src/sim/GroundMovementPlacement.cpp','src/sim/GroundDriveAdvance.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  p=pending.pop()
  if p in seen:continue
  seen.add(p)
  for n in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
   local=(ROOT/p).parent/n;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+n)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*block.SOURCES,*advance.SOURCES,*source_closure(),'tests/advance_nearby_scatter/CMakeLists.txt','tests/original_advance_nearby_scatter.py','tests/compare_advance_nearby_scatter.py','tools/verify_advance_nearby_scatter.py','tools/verify_ramp_geometry.py','tools/verify_voxel_ramp_shadow.py','tools/verify_advance_admission.py','tools/verify_ground_drive_stores.py','tools/verify_ground_drive_advance.py','tools/verify_ground_movement_placement.py','tools/verify_actor_ground_state.py','tools/verify_moving_resident_process.py','tools/verify_ground_drive_admission_process.py','tools/verify_ground_drive_gate_process.py','tests/test_advance_nearby_scatter_evidence.py'))))
FLAGS=dict(actual_Advance_result6_block=True,complete_Advance=True,actual_admission=True,actual_Cell_Unit_nearby_destination_children=True,
 actual_distinct_stock_Drive_geometry=True,initial_associations_and_incoming_scratch_high_word_supplied=True,
 actual_direction_initializer=True,terminal_nonnull_targets_supported=False,ordinary_Track_unpromoted_only=True,
 Process_joined=False,production_owned_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Advance Cell Scatter evidence/input')
ROOT_KEYS=('speed','acc','driving','suppress','marked','mark_effect','percentage','scratch')
def defaults():
 c=parent.defaults();c.update(speed=0,acc=8,driving=1,suppress=0,marked=1,mark_effect=0,
  percentage=struct.unpack('<Q',struct.pack('<d',1.))[0],scratch=0xaabbccdd,head=[12928,12928,0],track=[19,2,2,2,2],index=[37,9,9,9,9])
 c['queue'][0]=1;c['cells'][2][7]=1;c['objects'][1][7]=1
 return c
def command(**kw):
 c=defaults();c.update(kw)
 return 'F '+' '.join(map(str,[c[k] for k in ROOT_KEYS]))+' '+parent.command(**{k:v for k,v in c.items() if k in parent.defaults()})
def parse(cmd):
 t=cmd.split();require(len(t)>10 and t[0]=='F');v=list(map(int,t[1:9]));c=parent.parse(' '.join(t[9:]));c.update(zip(ROOT_KEYS,v))
 require(0<=c['speed']<=255 and -2147483648<=c['acc']<=2147483647 and c['driving'] in (0,1) and c['suppress'] in (0,1) and 0<=c['marked']<=255 and c['mark_effect'] in (0,1) and 0<=c['scratch']<=0xffffffff)
 require(0<=c['percentage']<1<<64 and __import__('math').isfinite(struct.unpack('<d',struct.pack('<Q',c['percentage']))[0]))
 require(struct.unpack('<d',struct.pack('<Q',c['ranks'][0]))[0]<1.)
 require(-1<=c['queue'][0]<=7 and c['bridge']==0 and c['short'][0]==0 and c['objects'][0][10]==0)
 require(all(a[:5]==[0,0,0,1,1] for a in c['actions']))
 x,y=c['head'][:2];index=((int(y/256)<<9)+int(x/256))&0xffffffff
 found=next((i for i,row in enumerate(c['cells'][:9]) if row[0]==index),9)
 require(c['cell']==found);return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},direction_data_sha256=hash_file(a.direction_data),render_data_sha256=hash_file(a.render_data),raster_data_sha256=hash_file(a.raster_data),geometry_data_sha256=hash_file(a.geometry_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(row.count('state')==1 and row.count('actor')==4 and row.count('geometry')==row.count('scratch')==row.count('moving'))
def generate(a):
 from original_advance_nearby_scatter import AdvanceNearbyScatterOracle
 o=AdvanceNearbyScatterOracle(a.exe);commands=[];expected=[];labels=[];groups={};coverage=[]
 def add(label,expected_code=6,**kw):
  cmd=command(**kw);before=o.counts.copy()
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed complete Advance case',len(commands),label,flush=True);raise
  measured={k:v-before[k] for k,v in o.counts.items() if v!=before[k]}
  if expected_code is not None:require(measured.get('Advance_admission.'+str(expected_code),0)>0)
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1;coverage.append(measured)
 p=pefile.PE(str(a.exe))
 for track,jump,candidates in track_cases(p):
  for q in candidates:
   c=defaults();c['track'][0]=track;c['index'][0]=jump;c['queue'][0]=q
   for row in c['cells']:row[7]=-1
   c['cells'][4][7]=0
   dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[q]
   c['cells'][(1+dy)*3+1+dx][7]=1
   add('all_ordinary_curved_transforms_queued_directions',**c)
 for speed,acc,suppress in ((0,0,0),(0,7,0),(0,8,0),(1,7,0),(15,7,0),(255,8,0),(255,8,1),(15,-16,0)):
  cells=defaults()['cells']
  if speed==255 and not suppress:cells[4][7]=1
  add('speed_suppression_residual_and_later_movement',cells=cells,speed=speed,acc=acc,suppress=suppress,expected_code=6 if acc+(0 if suppress else speed)>7 else None)
 for mode in range(4):
  for scratch in (0,1,0xffff0000,0xaabbccdd):add('caller_word_production_retained_high_word_and_FP',fp_mode=mode,scratch=scratch)
 for marked in (0,1,255):
  for effect in (0,1):add('named_Mark_effects_before_dispatch',marked=marked,mark_effect=effect,speed=15)
 for n in (1,2,16):
  cells=defaults()['cells'];cells[4][7]=1
  add('later_complete_Advance_calls_after_dispatch',cells=cells,actions=[[0,0,0,1,1,100+i] for i in range(n)],speed=15)
 add('self_destination_and_cleared_head_retained_next_call',actions=[[0,0,0,1,1,100],[0,0,0,1,1,101]],speed=15)
 for flags,level in ((0x100,0),(0x300,-4)):
  cells=defaults()['cells'];cells[2][5]=flags;cells[2][3]=level;cells[2][8]=1;cells[4][8]=1
  add('complete_caller_signed_level_and_elevated_dispatch',cells=cells)
 # Independent actual return0/2/7 roots retain the same complete kernel.
 c=defaults();c['cells'][2][7]=-1
 add('actual_admission_zero_retains_ordinary_continuation',expected_code=0,**c)
 c['cells'][2][9]=32
 add('actual_admission_two_retains_ordinary_continuation',expected_code=2,**c)
 c=defaults();c['speeds']=[0]*12;c['nearby_speeds']=[0]*108
 add('actual_admission_seven_skips_dispatch',expected_code=7,**c)
 for missing in (2,4):
  cells=defaults()['cells'];cells[missing][0]=-1;cells[9][7]=0 if missing==4 else 1
  add('complete_caller_shared_fallback_at_candidate_or_head',cells=cells,cell=9 if missing==4 else 4)
 add('inactive_complete_root_retains_incoming_scratch',driving=0,expected_code=None)
 for key in ('suspended','field5c8','field5b9'):
  c=defaults();c[key]=1;add('self_Scatter_guard_then_original_continuation',**c)
 require(all(o.counts['Advance_admission.'+str(code)] for code in (0,2,6,7)))
 require(o.counts['Advance6_continuation'] and o.counts['0x4a1000'])
 return commands,expected,labels,dict(FLAGS,groups=groups,per_case_counts=coverage,actual_counts=dict(o.counts),audited_complete_Advance_calls=o.audit_calls-11,geometry_entries=o.geometry_entries,geometry_stores=o.geometry_stores,geometry_values=o.geometry_values,direction_initializer_calls=o.direction_entries,distinct_original_instructions=len(o.instructions))
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.exe),str(a.direction_data),str(a.render_data),str(a.raster_data),str(a.geometry_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Advance Cell native runner failed',p.returncode,p.stderr[:1000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Advance Cell differs',i,j,got[max(0,j-7):j+12],want[max(0,j-7):j+12]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 for name,filename in [('direction','direction-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('geometry','ramp-geometry-data.bin')]:p.add_argument('--'+name+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/filename)
 p.add_argument('--output',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'complete Advance nearby Scatter sequences PASS')
if __name__=='__main__':main()
