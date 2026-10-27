#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete House map sight scan differential proof with actual House predicates."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_map_refresh import verify
NATIVE=('src/sim/HouseMapRefresh.hpp','tests/house_map_refresh_vectors.cpp','src/render/UnitTypeVisibility.hpp','src/render/UnitTypeVisibility.cpp','src/sim/Facing.hpp','CMakeLists.txt')
ORIGINAL=('tests/original_house_map_refresh.py','tools/verify_house_map_refresh.py','tests/compare_house_map_refresh.py','tests/test_house_map_refresh.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_49E000_removal_scan=True,complete_49DE00_addition_scan=True,actual_4F52B0_and_4E5540_house_children=True,virtual_and_post_sight_effects_and_initial_owners_supplied=True,MakeAlly_parent_and_production_adoption=False)
def require(ok):
 if not ok:raise ValueError('House map refresh evidence/input differs')
def fixture():
 return dict(addition=0,skip=0,argument=0,count=3,mode=0,current=1,rule=1,mutation=0,slots=[1,2,3,0,1,2,3,0],houses=[[0,1,0,0],[1,0,0,1],[-1,0,0,0]],types=[[0,1],[1,0],[255,255]],actors=[[0,1,1,1,6,6,6,4,1,2,3],[0,1,2,2,6,6,6,8,4,5,6],[0,1,3,3,0,6,6,2**31-1,7,8,9]])
def command(f):
 values=[f[k] for k in ('addition','skip','argument','count','mode','current','rule','mutation')]+f['slots']+[v for name in ('houses','types','actors') for row in f[name] for v in row]
 return 'M '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(len(t)==68 and t[0]=='M');v=list(map(int,t[1:]));keys=('addition','skip','argument','count','mode','current','rule','mutation');f=dict(zip(keys,v[:8]));f['slots']=v[8:16];f['houses']=[v[i:i+4] for i in range(16,28,4)];f['types']=[v[i:i+2] for i in range(28,34,2)];f['actors']=[v[i:i+11] for i in range(34,67,11)]
 signed=lambda x:-2**31<=x<2**31;byte=lambda x:0<=x<=255
 require(f['addition'] in (0,1) and byte(f['skip']) and signed(f['argument']) and -2<=f['count']<=8 and signed(f['mode']) and 0<=f['current']<=3 and byte(f['rule']) and 0<=f['mutation']<=7 and all(0<=x<=3 for x in f['slots']))
 for index,a,b,mask in f['houses']:require(signed(index) and byte(a) and byte(b) and 0<=mask<2**32)
 for row in f['types']:require(all(byte(x) for x in row))
 for a in f['actors']:require(byte(a[0]) and byte(a[1]) and 1<=a[2]<=3 and 1<=a[3]<=3 and all(signed(x) for x in a[4:11]))
 return f

def scenarios():
 def emit(label,f):return label,command(f)
 for addition in (0,1):
  for count in (-2,0,1,3,8):
   for skip in (0,1,255):
    f=fixture();f.update(addition=addition,count=count,skip=skip);yield emit('complete_scan_saved_count_null_slots_and_skip_byte',f)
  for mode in (0,1,-1):
   for current in range(4):
    for owner in (1,2,3):
     for kinds in ([6,6,6],[0,6,0],[0,0,6]):
      for rule in (0,255):
       f=fixture();f.update(addition=addition,mode=mode,current=current,rule=rule)
       for a in f['actors']:a[2]=owner;a[4:7]=kinds[:]
       yield emit('local_allied_and_force_building_branch',f)
  for value in range(256):
   f=fixture();f['addition']=addition;f['actors'][0][0]=value;f['actors'][1][1]=value;f['types'][0][1]=value;f['types'][1][0]=value;f['houses'][1][2]=value;yield emit('raw_actor_visibility_type_and_House_bytes',f)
  for mutation in range(8):
   for kinds in ([6,6,6],[0,6,6],[0,0,6],[0,0,0]):
    f=fixture();f.update(addition=addition,mutation=mutation,count=8,argument=-2**31)
    for a in f['actors']:a[4:7]=kinds[:]
    yield emit('live_callbacks_backing_type_owner_point_and_radius',f)
  for index in (-2**31,-33,-32,-2,-1,0,1,31,32,33,2**31-1):
   for mask in (0,1,0x80000000,0xffffffff):
    f=fixture();f.update(addition=addition,argument=2**31-1);f['houses'][0][0]=index;f['houses'][1][3]=mask;yield emit('existing_House_kernel_wrapped_shifts',f)
  for radius in (-2**31,-4,-3,-1,0,1,2**31-3,2**31-1):
   f=fixture();f['addition']=addition
   for a in f['actors']:a[7]=radius;a[8:11]=[-2**31,0,2**31-1]
   yield emit('post_sight_saved_point_wrapped_plus_three',f)
 rng=random.Random(0x49de00)
 for _ in range(96):
  f=fixture();f.update(addition=rng.randrange(2),mode=rng.choice([-1,0,1]),count=rng.randrange(-2,9),current=rng.randrange(4),rule=rng.choice([0,1,255]),mutation=rng.randrange(8),slots=[rng.randrange(4) for _ in range(8)])
  for h in f['houses']:h[:]=[rng.choice([-32,-1,0,1,31,32]),rng.choice([0,1,255]),rng.choice([0,1]),rng.getrandbits(32)]
  for a in f['actors']:a[:4]=[rng.choice([0,1]),rng.choice([0,255]),rng.randrange(1,4),rng.randrange(1,4)];a[4:7]=[rng.choice([0,6,15]) for _ in range(3)]
  yield emit('deterministic_shared_alias_and_late_field_mix',f)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_map_refresh.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0;events=0;signed=lambda x:-2**31<=x<2**31;byte=lambda x:0<=x<=255
 while i<len(row) and row[i]!='R':
  event=row[i];size={'K':3,'T':3,'S':7,'P':8,'I':3,'H':2,'A':3}.get(event);require(size is not None and i+size<=len(row));values=list(map(int,row[i+1:i+size]));require(all(signed(v) for v in values))
  if event in ('K','T','S','P','I','H'):require(1<=values[0]<=3)
  if event=='T':require(1<=values[1]<=3)
  if event=='S':require(values[1]==(1048 if f['addition'] else 1052) and values[2]==0 and values[4] in (0,1) and 0<=values[5]<=3)
  if event=='P':require(f['addition']==1 and values[4]==0 and values[6]==0)
  if event=='I':require(values[1]==(940 if f['addition'] else 944))
  if event=='A':require(1<=values[0]<=3 and 0<=values[1]<=3)
  i+=size;events+=1
 require(events<=8*12 and len(row)-i==59 and row[i:i+3]==['R','0','F']);v=list(map(int,row[i+3:]));require(len(v)==56 and -2<=v[0]<=8 and signed(v[1]) and 0<=v[2]<=3 and byte(v[3]) and v[4] in (0,1))
 for j in range(5,17,4):require(signed(v[j]) and byte(v[j+1]) and byte(v[j+2]) and 0<=v[j+3]<2**32)
 require(all(byte(x) for x in v[17:23]))
 for j in range(23,56,11):require(byte(v[j]) and byte(v[j+1]) and 1<=v[j+2]<=3 and 1<=v[j+3]<=3 and all(signed(x) for x in v[j+4:j+11]))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_map_refresh import HouseMapRefreshOracle
  oracle=HouseMapRefreshOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x49e000,0x49de00,0x4f52b0,0x4e5540)) and all(oracle.counts['supplied_'+str(k)]>0 for k in (44,128,1048,1052,940,944)) and oracle.counts['supplied_post_sight']>0 and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House map refresh sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
