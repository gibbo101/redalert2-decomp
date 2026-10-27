#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Terminal Cell-target continuation with actual coordinates and supplied effects."""
import argparse,copy,json,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_advance_terminal import verify
NATIVE=('tests/advance_terminal_vectors.cpp','src/sim/FootCoordinates.cpp','src/assets/MapFloorHeight.cpp','src/sim/UnitDiscovery.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  p=pending.pop()
  if p in seen:continue
  seen.add(p)
  for n in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
   local=(ROOT/p).parent/n;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+n)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*source_closure(),'tests/advance_terminal/CMakeLists.txt','tests/original_advance_terminal.py',
 'tests/compare_advance_terminal.py','tests/test_advance_terminal_evidence.py','tools/verify_advance_terminal.py',
 'tools/verify_map_floor_height.py','tools/verify_terrain_visibility.py','tests/original_presentation.py',
 'tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py'))))
FLAGS=dict(actual_terminal_interior=True,actual_Cell_Foot_Drive_registry_coordinates=True,
 actual_mission_getter_and_target_clears=True,result_bearing_returns=True,
 entry_associations_and_divisor_supplied=True,notification_and_mission_effects_supplied=True,
 complete_Advance=False,Process_joined=False,production_owned_world_join=False,runtime_enabled=False)
SCALARS=('target','field490','registry','mission','queued','divisor','residual','acc','driving','mission_return','post_return','height','fp_mode')
ARRAYS={'flags':3,'notify_flags':3,'post_flags':3,'position':3,'head':3,'destination':3,'pool':2,'cell':4,'queue':24}
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported terminal evidence/input')
def defaults():return dict(target=1,field490=17,registry=-1,mission=0,queued=7,divisor=104,residual=23,acc=91,driving=0,
 mission_return=0,post_return=0,height=104,fp_mode=0,flags=[1,0,0],notify_flags=[-1]*3,post_flags=[-1]*3,
 position=[12928,12928,0],head=[0,0,0],destination=[12928,12928,0],pool=[50,50],cell=[50,50,0,0],queue=[3,*range(1,24)])
def command(**kw):
 c=defaults();c.update(kw);return 'T '+' '.join(map(str,[*[c[k] for k in SCALARS],*[x for k in ARRAYS for x in c[k]]]))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='T' and len(t)==1+len(SCALARS)+sum(ARRAYS.values()))
 v=list(map(int,t[1:]));require(all(-2147483648<=n<=2147483647 for n in v));c=dict(zip(SCALARS,v));i=len(SCALARS)
 for k,n in ARRAYS.items():c[k]=v[i:i+n];i+=n
 require(c['target'] in (0,1) and -128<=c['registry']<=127 and -1<=c['mission']<=31 and -1<=c['queued']<=31)
 require(0<c['divisor']<=2147483647 and c['driving'] in (0,1) and 0<=c['fp_mode']<=3)
 require(all(0<=c[k]<=255 for k in ('mission_return','post_return')) and all(0<=n<=255 for n in c['flags']))
 for k in ('notify_flags','post_flags'):require(c[k]==[-1]*3 or all(0<=n<=255 for n in c[k]))
 require(all(-32768<=n<=32767 for n in c['pool']+c['cell'][:2]) and -128<=c['cell'][2]<=127 and 0<=c['cell'][3]<=20)
 return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(row.count('state')==row.count('return')==row.count('floor')==1)
def generate(a):
 from original_advance_terminal import AdvanceTerminalOracle
 o=AdvanceTerminalOracle(a.exe);commands=[];expected=[];labels=[];groups={};coverage=[]
 def add(label,**kw):
  cmd=command(**kw);before=o.counts.copy()
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed terminal case',len(commands),label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
  coverage.append({k:v-before[k] for k,v in o.counts.items() if v!=before[k]})
 add('null_target_still_notifies_and_returns',target=0)
 for x,y in ((49,50),(50,49),(-50,50),(50,-50)):
  add('target_X_Y_word_comparisons',cell=[x,y,0,0])
 for z in (-2147483648,-2147483441,-209,-208,-207,-1,0,1,207,208,209,2147483440,2147483647):
  add('wrapped_signed_height_strict_threshold',position=[12928,12928,z])
 for z,d in ((2147483647,-1),(-2147483648,0),(2147483647,-2147483648),(-2147483648,2147483647)):
  add('wrapped_height_subtract_and_INT_MIN_absolute',position=[12928,12928,z],destination=[12928,12928,d])
 for divisor in (1,2,103,104,1073741823,1073741824,2147483647):
  for z in (0,1,2,207,208):add('wrapped_double_divisor_threshold',divisor=divisor,position=[12928,12928,z])
 for flags in ([0,0,0],[255,0,0],[1,1,0],[1,0,255],[0,1,1]):
  for target in (0,1):add('live_terminal_eligibility_flags',flags=flags,target=target)
 for mission,queued in ((0,2),(2,7),(-1,2),(-1,7),(31,2)):
  for value in (0,1,255):add('actual_current_or_queued_mission_and_supplied_effect_return',mission=mission,queued=queued,mission_return=value)
 for result in (0,1,255):
  for flags in ([-1]*3,[0,0,0],[1,255,255]):add('result_bearing_post_effect_and_late_onMap',post_return=result,post_flags=flags)
 for flags in ([0,0,0],[1,1,0],[1,0,1],[1,0,0]):add('diagnostic_notification_late_flag_mutation',notify_flags=flags,flags=[255,0,0])
 for registry in (-128,-1,0,127):
  for pool in ([50,50],[-32768,32767]):add('independent_Foot_registry_query',registry=registry,pool=pool,position=[12928,12928,208])
 for head in ([0,0,0],[12928,12928,207],[12928,12928,208],[0,0,-2147483648]):
  for driving in (0,1):add('diagnostic_supplied_head_repeated_clear_order',head=head,driving=driving)
 for x in (-16777216,-16776960,-385,-384,-383,-257,-256,-255,-129,-128,-127,-1,0,127,128,16777216):
  cx=int(x/256);word=(cx+32768)%65536-32768
  # Cell centers that are negative can divide into the following word. These
  # scenarios deliberately retain the actual signed projection, not x==Cell.x.
  add('signed_division_before_word_wrap',position=[x,12928,0],cell=[word,50,0,0])
 for ramp in range(21):
  for level in (-4,0,127):add('actual_target_floor_all_ramps',cell=[50,50,level,ramp])
 for mode in range(4):
  for acc,residual in ((-2147483648,2147483647),(0,-1),(91,0)):
   add('native_FP_mode_and_signed_residual_retention',fp_mode=mode,acc=acc,residual=residual)
 require(o.counts['arrived'] and o.counts['clears'] and o.counts['supplied.0x6fd630'] and o.counts['true_return'])
 return commands,expected,labels,dict(FLAGS,groups=groups,per_case_counts=coverage,actual_counts=dict(o.counts),audited_terminal_blocks=o.audit_blocks,distinct_original_instructions=len(o.instructions))
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Terminal native runner failed',p.returncode,p.stderr[:1000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Terminal differs',i,j,got[max(0,j-7):j+12],want[max(0,j-7):j+12]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
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
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'terminal target/return continuations PASS')
if __name__=='__main__':main()
