#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Process with actual shared ordinary Advance and terminal/nearby children."""
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
from verify_process_terminal_scatter import verify
import compare_advance_terminal_scatter as terminal
NATIVE=('tests/process_terminal_scatter_vectors.cpp',*parent.NATIVE[1:],'src/render/RampGeometry.cpp','src/assets/RampGeometryData.cpp','src/assets/RasterData.cpp','src/sim/Drive.cpp','src/sim/ActorGroundState.cpp','src/sim/GroundMovementPlacement.cpp','src/sim/GroundDriveAdvance.cpp','src/sim/GroundDriveProcess.cpp','src/sim/UnitNextCell.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  p=pending.pop()
  if p in seen:continue
  seen.add(p)
  for n in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
   local=(ROOT/p).parent/n;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+n)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*block.SOURCES,*advance.SOURCES,*source_closure(),*terminal.SOURCES,
 'tests/process_terminal_scatter/CMakeLists.txt','tests/original_process_terminal_scatter.py','tests/compare_process_terminal_scatter.py','tools/verify_process_terminal_scatter.py','tools/verify_ground_drive_process.py','tools/verify_ground_drive_idle_target.py','tools/verify_unit_next_cell.py','tests/test_process_terminal_scatter_evidence.py'))))
FLAGS=dict(complete_Process=True,actual_result_bearing_Advance=True,actual_shared_Cell_Unit_nearby_destination_children=True,
 actual_idle_terminal_and_Move_To=True,borrowed_actor_timer_words=True,named_effects_and_initial_records_supplied=True,
 healthy_initial_state_and_per_Advance_frame_bytes_supplied=True,
 special_flags_and_wake_excluded=True,production_owned_world_join=False,runtime_enabled=False)
PROCESS_KEYS=('process_track','process_padding','process_ramp','process_rotating','process_percentage','process_first_padding','process_second_padding','process_wait_duration','process_wait_padding','process_wait_flag')
def defaults():
 c=legacy.defaults();c.update(terminal.terminal_defaults());c.update(process_track=19,process_padding=7,process_ramp=0,process_rotating=0,process_percentage=4607182418800017408,
  process_first_padding=11,process_second_padding=13,process_wait_duration=5,process_wait_padding=17,process_wait_flag=173,process_retry_timer=[-1,19,0],process_wait_timer=[-1,23,0])
 c['queue']=[1]+[-1]*23
 return c
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported complete Process evidence/input')
def command(**kw):
 c=defaults();c.update(kw)
 vals=[*[c[k] for k in PROCESS_KEYS],*c['process_retry_timer'],*c['process_wait_timer']]
 return 'P '+' '.join(map(str,vals))+' '+terminal.command(**{k:v for k,v in c.items() if k not in (*PROCESS_KEYS,'process_retry_timer','process_wait_timer')})
def parse(cmd):
 parts=cmd.split();require(len(parts)>18 and parts[0]=='P');v=list(map(int,parts[1:17]));c=terminal.parse(' '.join(parts[17:]))
 c.update(zip(PROCESS_KEYS,v[:10]));c['process_retry_timer']=v[10:13];c['process_wait_timer']=v[13:16]
 require(0<=c['process_wait_flag']<=255)
 require(-1<=c['process_track']<=63 and -1<=c['process_ramp']<=20 and c['process_rotating'] in (0,1))
 require(all(-2147483648<=v<=2147483647 for k in ('process_padding','process_first_padding','process_second_padding','process_wait_duration','process_wait_padding','process_retry_timer','process_wait_timer') for v in (c[k] if isinstance(c[k],list) else [c[k]])))
 require(0<=c['process_percentage']<1<<64 and __import__('math').isfinite(struct.unpack('<d',struct.pack('<Q',c['process_percentage']))[0]))
 require(not c['objects'][0][5] and not c['objects'][0][6] and not c['disabled1bc'] and not c['disabled1c0'] and c['field5c0']==-1 and c['field3fc']<=0 and c['guard_start']==-1 and c['guard_remaining']==0)
 require(c['queue'][-1]==-1 and all(-1<=q<=7 for q in c['queue']) and c['owned']==0)
 return c
def identities(a):
 return dict(scope='pilot' if a.pilot else 'full',pilot_limit=a.pilot_limit,inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},direction_data_sha256=hash_file(a.direction_data),render_data_sha256=hash_file(a.render_data),raster_data_sha256=hash_file(a.raster_data),geometry_data_sha256=hash_file(a.geometry_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 require(len(e['evidence'].get('per_case_counts',[]))==len(e['commands']))
 counts=e['evidence'].get('actual_counts',{})
 require(e['evidence'].get('audited_complete_Process_calls',0)>0 and sum(counts.get('Process_return.'+str(i),0) for i in (0,1))==e['evidence']['audited_complete_Process_calls'])
 if current.get('scope')=='full':
  require(all(counts.get(f'Advance_caller.{i}',0) and counts.get(f'Advance_return.{i}.1',0) for i in range(3)))
  require(all(counts.get(f'preparation_admission.{caller}.{code}',0) for caller in ('4a34f1','4a40ea') for code in (0,2,6,7)))
 for cmd,row in zip(e['commands'],e['expected']):
  c=parse(cmd);n=len(c['actions']);require(isinstance(row,list) and all(isinstance(s,str) for s in row) and row.count('state')==1 and row.count('actor')==4 and all(row.count(tag)==n for tag in ('geometry','scratch','moving','process-return','process-state')))
def generate(a):
 from original_process_terminal_scatter import ProcessTerminalScatterOracle
 o=ProcessTerminalScatterOracle(a.exe);commands=[];expected=[];labels=[];groups={};coverage=[]
 p=pefile.PE(str(a.exe))
 def terminal_index(i):
  track=struct.unpack('<b',p.get_data(0x7a0180+12*i-0x400000,1))[0]
  base=struct.unpack('<I',p.get_data(0x7a00a0+16*track-0x400000,4))[0]
  return next(j for j in range(1,128) if p.get_data(base+12*j-0x400000,8)==bytes(8))
 def add(label,required=None,**kw):
  if a.pilot_limit is not None and len(commands)>=a.pilot_limit:return
  cmd=command(**kw);before=o.counts.copy()
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed complete Process',len(commands),label,flush=True);raise
  measured={k:v-before[k] for k,v in o.counts.items() if v!=before[k]}
  if required:require(measured.get(required,0)>0)
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1;coverage.append(measured)
 for second in (False,True):
  for code in (2,6,7):
   c=defaults();c.update(process_track=-1,head=[0,0,0],cell=9,position=[12672,12928,0],destination=[13184,13184,0],desired=16384,start=16384,queue=[2,3,4,-1,*[-1]*20])
   for row in c['cells']:row[7]=-1
   c['cells'][8 if second else 4][7]=1
   if code==2:
    c['objects'][1][7]=5;c['secondary'][0]['destination']=[14000,15000,0]
   if code==7:
    if second:
     c['cells'][8][6]=2;c['speeds'][2]=0;c['nearby_speeds'][2*9+1]=0
    else:c['speeds']=[0]*12;c['nearby_speeds']=[0]*108
   required=f'preparation_admission.{"4a40ea" if second else "4a34f1"}.{code}'
   if code==2:
    for waitFlag,timer,clock in ((0,[-1,23,0],100),(1,[90,23,5],100),(255,[100,23,9],101)):
     q=copy.deepcopy(c);q.update(process_wait_flag=waitFlag,process_wait_timer=timer,actions=[[0,0,0,1,1,clock],[0,0,0,1,1,clock+1]])
     add('preparation_moving2_borrows_actual_wait_and_retry_words',required=required,**q)
    q=copy.deepcopy(c);q.update(process_wait_flag=0,process_retry_timer=[100,-2147483648,8])
    add('preparation_moving2_retry_timer_remains_live',required=required,**q)
   else:add('preparation_stationary6_or_zero_speed7_retry',required=required,**c)
 c=defaults();c.update(process_track=-1,head=[0,0,0],cell=9,position=[12672,12928,0],destination=[13184,13184,0],desired=16384,start=16384,queue=[2,3,4,-1,*[-1]*20])
 for row in c['cells']:row[7]=-1
 add('preparation_accepts_both_actual_Cell_admissions',required='preparation_admission.4a40ea.0',**c)
 for speed in (0,15,255):
  for acc in (0,512):
   c=defaults();c['process_track']=-1;c['head']=[0,0,0];c['cell']=9;c['destination']=[12928,12672,0];c['queue']=[0]+[-1]*23;c['speed']=speed;c['acc']=acc
   add('preparation_then_third_Advance_caller',**c)
   add('third_caller_terminal_AL1_ignored',**dict(c,initial_target=2,mission_return=1))
 for bits in (0,0x3f000000,0x3fa00000):
  c=defaults();c.update(process_track=-1,head=[0,0,0],cell=9,destination=[12928,12672,0],queue=[0]+[-1]*23,speed=15)
  c['speeds']=[bits]*12
  for land in range(12):c['nearby_speeds'][land*9+1]=bits
  add('preparation_borrows_shared_land_speed_column',**c)
 c=defaults();c['process_track']=0;c['track'][0]=0;c['index'][0]=terminal_index(0);c['queue']=[0]+[-1]*23;c['destination']=[12928,12672,0]
 add('first_Advance_then_prepare_second_caller',**c)
 add('second_Advance_AL1_is_ignored_after_actual_preparation',required='Advance_return.1.1',**dict(c,acc=512,initial_target=2,mission_return=1))
 for start,remaining in ((-1,0),(-1,5),(97,5),(100,0)):
  add('no_route_borrows_live_retry_timer',process_track=-1,head=[0,0,0],cell=9,queue=[-1]*24,process_retry_timer=[start,41,remaining])
 add('active_Advance6_to_actual_Cell_Unit_nearby',required='Advance_admission.6',actions=[[0,0,0,1,1,100],[0,0,0,1,1,101]])
 p=pefile.PE(str(a.exe));tracks=[]
 for t,jump,qs in track_cases(p):
  if a.pilot and t!=19:continue
  for q in qs:
   c=defaults();c['process_track']=t;c['track'][0]=t;c['index'][0]=jump;c['queue'][0]=q
   for row in c['cells']:row[7]=-1
   c['cells'][4][7]=0
   dx,dy=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))[q]
   c['cells'][(1+dy)*3+1+dx][7]=1
   add('all_curved_switches_in_complete_Process',**c)
 for i in range(64):
  track=struct.unpack('<b',p.get_data(0x7a0180+12*i-0x400000,1))[0]
  if not 1<=track<=6:continue
  base=struct.unpack('<I',p.get_data(0x7a00a0+16*track-0x400000,4))[0]
  for j in range(1,128):
   if p.get_data(base+12*j-0x400000,8)==bytes(8):tracks.append((i,j));break
 for track,index in tracks:
  if a.pilot and track!=19:continue
  for result in (0,1,255):
   c=defaults();c['process_track']=track;c['track'][0]=track;c['index'][0]=index;c['queue']=[-1]*24
   add('terminal_AL_and_later_Process_control',**dict(c,initial_target=5,mission_return=result))
 for code in (0,2,7):
  c=defaults();c['cells'][2][7]=-1
  if code==2:c['cells'][2][9]=32
  if code==7:c['speeds']=[0]*12;c['nearby_speeds']=[0]*108
  add('other_actual_Advance_admissions_in_Process',**c)
 for track in (-1,19):
  for driving in (0,1):
   if track==19 and driving:continue
   for count in (0,1,-3):
    for result in (0,1,255):
     add('idle_Cell_actual_null_command_or_clears',process_track=track,driving=driving,initial_target=5,count=count,mission_return=result)
 for target in (0,1,3,10):
  add('idle_continue_and_target_Move_To',process_track=-1,head=[0,0,0],cell=9,destination=[0,0,0],queue=[-1]*24,initial_target=target)
 for rotating in (0,1):
  for flags in ([-1]*3,[0,0,0],[1,1,0],[1,0,1]):
   add('post_rotation_live_eligibility',process_track=-1,process_rotating=rotating,head=[0,0,0],cell=9,destination=[0,0,0],queue=[-1]*24,notify_flags=flags)
 for mode in range(4):add('complete_Process_FP_mode',fp_mode=mode)
 for ramp in (1,7,20):
  c=defaults();c['cells'][4][4]=ramp
  add('initial_ramp_and_temporary_padding',**c)
 if not a.pilot:
  require(all(o.counts[f'Advance_caller.{i}'] for i in range(3)))
  require(all(o.counts[f'Advance_return.{i}.1'] for i in range(3)))
  require(all(o.counts[f'preparation_admission.{caller}.{code}'] for caller in ('4a34f1','4a40ea') for code in (0,2,6,7)))
 return commands,expected,labels,dict(FLAGS,groups=groups,per_case_counts=coverage,actual_counts=dict(o.counts),audited_complete_Process_calls=o.audit_calls-11,geometry_entries=o.geometry_entries,geometry_stores=o.geometry_stores,geometry_values=o.geometry_values,direction_initializer_calls=o.direction_entries,distinct_original_instructions=len(o.instructions))
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.exe),str(a.direction_data),str(a.render_data),str(a.raster_data),str(a.geometry_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Complete Process native runner failed',p.returncode,p.stderr[:1000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Complete Process differs',i,j,got[max(0,j-7):j+12],want[max(0,j-7):j+12]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True)
 require(guards.returncode==0 and 'checks PASS' in guards.stdout)
 for bad in ('P 0',commands[0]+' trailing'):
  rejected=subprocess.run([str(a.native),str(a.exe),str(a.direction_data),str(a.render_data),str(a.raster_data),str(a.geometry_data)],input=bad+'\n',capture_output=True,text=True)
  require(rejected.returncode!=0 and bool(rejected.stderr))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 for name,filename in [('direction','direction-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('geometry','ramp-geometry-data.bin')]:p.add_argument('--'+name+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/filename)
 p.add_argument('--pilot',action='store_true');p.add_argument('--pilot-limit',type=int);p.add_argument('--output',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();require(a.pilot_limit is None or a.pilot and a.pilot_limit>0);start=time.monotonic();current=identities(a);runner=hash_file(a.native)
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'complete Process sequences PASS')
if __name__=='__main__':main()
