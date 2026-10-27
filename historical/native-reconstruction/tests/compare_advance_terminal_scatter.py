#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Advance with actual terminal coordinates, clears and AL returns."""
import argparse,copy,json,re,subprocess,time
from pathlib import Path
import compare_cell_nearby_scatter as parent
import compare_advance_cell_scatter as block
import compare_advance_admission as advance
import compare_advance_nearby_scatter as legacy
from compare_advance_admission import track_cases
import struct,pefile
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_advance_terminal_scatter import verify
NATIVE=('tests/advance_terminal_scatter_vectors.cpp',*parent.NATIVE[1:],'src/render/RampGeometry.cpp','src/assets/RampGeometryData.cpp','src/assets/RasterData.cpp','src/sim/Drive.cpp','src/sim/ActorGroundState.cpp','src/sim/GroundMovementPlacement.cpp','src/sim/GroundDriveAdvance.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  p=pending.pop()
  if p in seen:continue
  seen.add(p)
  for n in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
   local=(ROOT/p).parent/n;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+n)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*block.SOURCES,*advance.SOURCES,*source_closure(),*legacy.SOURCES,'tests/advance_terminal_scatter/CMakeLists.txt','tests/original_advance_terminal_scatter.py','tests/compare_advance_terminal_scatter.py','tools/verify_advance_terminal_scatter.py','tools/verify_advance_terminal.py','tools/verify_ramp_geometry.py','tools/verify_voxel_ramp_shadow.py','tools/verify_advance_admission.py','tools/verify_ground_drive_stores.py','tools/verify_ground_drive_advance.py','tools/verify_ground_movement_placement.py','tools/verify_actor_ground_state.py','tools/verify_moving_resident_process.py','tools/verify_ground_drive_admission_process.py','tools/verify_ground_drive_gate_process.py','tests/test_advance_terminal_scatter_evidence.py'))))
BASELINE=ROOT/'private/map-depth-1006/advance-nearby-scatter-v1/expected.json'
BASELINE_SHA256='97d063a2ddead3c6958f14d629e9e761b9fa055c5a719e32c00f32fd0423c7f7'
FLAGS=dict(complete_Advance=True,actual_admission=True,actual_Cell_Unit_nearby_destination_children=True,
 actual_terminal_coordinates_clears_and_returns=True,notification_and_mission_effects_supplied=True,
 initial_associations_supplied=True,retained_173_legacy_commands_and_projections=True,
 Process_joined=False,production_owned_world_join=False,runtime_enabled=False)
TERMINAL_KEYS=('terminal_flags','mission_return','post_return','notify_flags','post_flags')
def terminal_defaults():return dict(terminal_flags=[1,0,0],mission_return=0,post_return=0,notify_flags=[-1]*3,post_flags=[-1]*3)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported complete terminal Advance evidence/input')
def command(**kw):
 t=terminal_defaults();t.update({k:v for k,v in kw.items() if k in t})
 values=[*t['terminal_flags'],t['mission_return'],t['post_return'],*t['notify_flags'],*t['post_flags']]
 return 'T '+' '.join(map(str,values))+' '+legacy.command(**{k:v for k,v in kw.items() if k not in t})
def parse(cmd):
 parts=cmd.split()
 if parts and parts[0]=='T':
  require(len(parts)>12);v=list(map(int,parts[1:12]));c=legacy.parse(' '.join(parts[12:]));c.update(terminal_defaults())
  c.update(terminal_flags=v[:3],mission_return=v[3],post_return=v[4],notify_flags=v[5:8],post_flags=v[8:11],terminal_record=True)
  require(0<c['terminal_flags'][0]<=255 and c['terminal_flags'][1:]==[0,0] and all(0<=c[k]<=255 for k in ('mission_return','post_return')))
  for k in ('notify_flags','post_flags'):require(c[k]==[-1]*3 or all(0<=n<=255 for n in c[k]))
  return c
 c=legacy.parse(cmd);c.update(terminal_defaults());c['terminal_record']=False;return c
def identities(a):
 require(hash_file(BASELINE)==BASELINE_SHA256)
 return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},legacy_commands_sha256=hash_file(BASELINE),direction_data_sha256=hash_file(a.direction_data),render_data_sha256=hash_file(a.render_data),raster_data_sha256=hash_file(a.raster_data),geometry_data_sha256=hash_file(a.geometry_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(row.count('state')==1 and row.count('actor')==4 and row.count('geometry')==row.count('scratch')==row.count('moving') and row.count('return')==(len(parse(cmd)['actions']) if parse(cmd)['terminal_record'] else 0))
def generate(a):
 from original_advance_terminal_scatter import AdvanceTerminalScatterOracle
 o=AdvanceTerminalScatterOracle(a.exe);commands=[];expected=[];labels=[];groups={};coverage=[]
 def add_cmd(label,cmd,want=None):
  before=o.counts.copy()
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed complete terminal Advance',len(commands),label,flush=True);raise
  if want is not None:require(row==want)
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
  coverage.append({k:v-before[k] for k,v in o.counts.items() if v!=before[k]})
 old=json.loads(BASELINE.read_text());require(len(old['commands'])==173)
 for label,cmd,want in zip(old['labels'],old['commands'],old['expected']):add_cmd(label,cmd,want)
 p=pefile.PE(str(a.exe));tracks=[]
 for i in range(64):
  raw=p.get_data(0x7a0180+12*i-0x400000,12);track=struct.unpack_from('<b',raw)[0]
  if not 1<=track<=6:continue
  base=struct.unpack('<I',p.get_data(0x7a00a0+16*track-0x400000,4))[0]
  for j in range(1,128):
   if p.get_data(base+12*j-0x400000,8)==bytes(8):tracks.append((i,j));break
 def add(label,**kw):
  c=legacy.defaults();c['index'][0]=dict(tracks)[c['track'][0]];c['queue'][0]=-1;c['initial_target']=5;c.update(kw)
  add_cmd(label,command(**c))
 for track,index in tracks:
  indexes=legacy.defaults()['index'];indexes[0]=index;which=legacy.defaults()['track'];which[0]=track
  add('all_ordinary_tracks_terminal_target_from_full_root',track=which,index=indexes)
 for z in (-2147483648,-209,-208,-207,-1,0,1,207,208,209,2147483647):
  add('full_root_late_destination_height_threshold',destination=[12928,12928,z])
 for target in (0,1,3,5,10):add('full_root_null_distinct_and_fallback_Cell_targets',initial_target=target)
 for mission,queued in ((0,2),(2,7),(-1,2),(-1,7),(31,2)):
  for result in (0,1,255):
   c=legacy.defaults();c['objects'][0][4]=mission
   add('full_root_actual_mission_getter_and_supplied414_result',objects=c['objects'],queued=queued,mission_return=result)
 for value in (0,1,255):
  for flags in ([-1]*3,[0,0,0],[1,255,255]):add('full_root_result_bearing490_and_late_flags',post_return=value,post_flags=flags)
 for flags in ([0,0,0],[1,1,0],[1,0,1],[255,0,0]):add('full_root_notification_changes_live_flags',notify_flags=flags)
 for registry in (-128,-1,0,127):
  for pool in ([50,50],[-32768,32767]):add('full_root_independent_registry_height',registry=registry,poolx=pool[0],pooly=pool[1],destination=[12928,12928,208])
 for ramp in range(21):
  cells=legacy.defaults()['cells'];cells[4][4]=ramp
  add('full_root_placement_and_target_floor_share_live_ramps',cells=cells)
 for n in (2,8):add('later_full_calls_retain_cleared_targets_queues_and_returns',actions=[[0,0,0,1,1,100+i] for i in range(n)],mission_return=1)
 for mode in range(4):add('complete_terminal_native_FP_modes',fp_mode=mode)
 require(o.counts['terminal_arrived'] and o.counts['terminal_clears'] and o.counts['root_return.1'])
 return commands,expected,labels,dict(FLAGS,groups=groups,per_case_counts=coverage,actual_counts=dict(o.counts),audited_complete_Advance_calls=o.audit_calls-11,geometry_entries=o.geometry_entries,geometry_stores=o.geometry_stores,geometry_values=o.geometry_values,direction_initializer_calls=o.direction_entries,distinct_original_instructions=len(o.instructions))
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.exe),str(a.direction_data),str(a.render_data),str(a.raster_data),str(a.geometry_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Complete terminal Advance native runner failed',p.returncode,p.stderr[:1000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Complete terminal Advance differs',i,j,got[max(0,j-7):j+12],want[max(0,j-7):j+12]))
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'complete terminal Advance sequences PASS')
if __name__=='__main__':main()
