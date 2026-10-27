#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete MakeAlly with recovered eligibility, score and target children."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_make_ally import verify
NATIVE=('src/sim/HouseMakeAlly.hpp','src/sim/HouseAlliance.hpp','src/sim/HouseThreat.hpp','src/sim/TargetReference.hpp','src/sim/MissionTextAction.hpp','src/sim/OriginalMath.hpp','src/sim/MissionBuildingTarget.hpp','src/sim/MissionTypedTagExpiration.hpp','src/sim/MissionTechnoTagExpiration.hpp','src/sim/MissionExpirationPointerView.hpp','tests/house_make_ally_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_house_make_ally.py','tools/verify_house_make_ally.py','tests/compare_house_make_ally.py','tests/test_house_make_ally.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_MakeAlly_parent=True,actual_eligibility_score_target_sort_cast_and_null_clear=True,map_grid_notification_UI_and_virtual_leaves_supplied=True,production_adoption=False)
def require(ok):
 if not ok:raise ValueError('House MakeAlly evidence/input differs')
def bits(v):
 import struct
 return struct.unpack('<Q',struct.pack('<d',v))[0]
KEYS=('current','target','announce','mode','unrestricted','houseCount','typeCount','actorCount','actorBacking','currentHouse','quiet','rule','delayBits','mutation')
LAYOUT=(('houseSlots',1,8),('typeSlots',1,4),('actorSlots',2,8),('types',4,5),('houses',5,9),('scores',20,2),('actors',4,14),('registry',64,2),('registryConfig',1,6),('scratch',1,5))
def fixture():
 return dict(current=1,target=2,announce=1,mode=4,unrestricted=0,houseCount=5,typeCount=4,actorCount=4,actorBacking=1,currentHouse=1,quiet=0,rule=1,delayBits=bits(.6),mutation=0,houseSlots=[[1,2,3,4,5,1,2,3]],typeSlots=[[1,2,3,4]],actorSlots=[[1,2,3,4,0,1,2,3],[4,3,2,1,0,4,3,2]],types=[[0,-1,0,1,10],[13,-1,0,1,20],[2,-1,0,0,30],[3,-1,0,1,40]],houses=[[i,i if i<5 else 1,0,1 if i==2 else 0,0,1 if i==1 else 0,0,2,4] for i in range(1,6)],scores=[[j+1,(j+1)*7] for i in range(5) for j in range(4)],actors=[[k,100+i,0,0,0,1,2 if i<3 else 3,2 if i!=2 else 3,255,77,1,1,3,0] for i,k in enumerate((1,2,6,15),1)],registry=[[100+i%4+1,i%4+1] for i in range(64)],registryConfig=[[32,0,1,0,0,4]],scratch=[[123,255,165,0,255]])
def command(f):return 'B '+' '.join(map(str,[f[k] for k in KEYS]+[v for name,_,_ in LAYOUT for row in f[name] for v in row]))
def parse(cmd):
 t=cmd.split();require(len(t)==343 and t[0]=='B');v=list(map(int,t[1:]));f=dict(zip(KEYS,v[:14]));offset=14
 for name,count,width in LAYOUT:f[name]=[v[i:i+width] for i in range(offset,offset+count*width,width)];offset+=count*width
 signed=lambda x:-2**31<=x<2**31;byte=lambda x:0<=x<=255;u32=lambda x:0<=x<2**32
 require(all(signed(f[k]) for k in ('mode','unrestricted','quiet')) and all(f[k] in range(1,6) for k in ('current','target','currentHouse')) and byte(f['announce']) and -2<=f['houseCount']<=8 and -2<=f['typeCount']<=4 and -2<=f['actorCount']<=8 and f['actorBacking'] in (1,2) and byte(f['rule']) and 0<=f['delayBits']<2**64 and f['mutation'] in range(16))
 for row in f['houseSlots']:require(all(x in range(1,6) for x in row))
 for row in f['typeSlots']:require(all(x in range(1,5) for x in row))
 for row in f['actorSlots']:require(all(x in range(5) for x in row))
 for a,b,c,d,e in f['types']:require(signed(a) and signed(b) and byte(c) and signed(d) and signed(e))
 for i,t,d,a,m,x,y,e,n in f['houses']:require(signed(i) and t in range(1,5) and byte(d) and u32(a) and u32(m) and byte(x) and byte(y) and signed(e) and -2<=n<=4)
 for h,v in f['scores']:require(h in range(1,6) and signed(v))
 for k,uid,x,y,flag,country,owner,target,clear,timer,service,attached,index,permission in f['actors']:require(signed(k) and signed(uid) and -32768<=x<=32767 and -32768<=y<=32767 and byte(flag) and signed(country) and owner in range(6) and target in range(5) and byte(clear) and signed(timer) and service in (0,1) and attached in range(5) and signed(index) and signed(permission))
 for k,o in f['registry']:require(signed(k) and o in range(5))
 n,s,b,c,i,o=f['registryConfig'][0];require(0<=n<=32 and byte(s) and b in (1,2) and c in range(3) and i in range(32) and o in range(5))
 value,*flags=f['scratch'][0];require(signed(value) and all(byte(x) for x in flags));return f

def scenarios():
 def emit(label,f):return label,command(f)
 for mode in (0,1,4,-1):
  for unrestricted in (0,1,-1):
   for current in range(1,6):
    for target in range(1,6):
     f=fixture();f.update(mode=mode,unrestricted=unrestricted,current=current,target=target);yield emit('complete_parent_eligibility_and_mode_paths',f)
 for mutation in range(16):
  for mode in (0,1,4):
   for announce in (0,1,255):
    f=fixture();f.update(mutation=mutation,mode=mode,announce=announce);yield emit('live_children_and_repeated_resolution',f)
 for permission in (-256,-1,0,1,255,256,257):
  for service in (0,1):
   for attached in (0,1,4):
    f=fixture()
    for actor in f['actors']:actor[10]=service;actor[11]=attached;actor[13]=permission
    yield emit('null_clear_service_attachment_and_permission_low_byte',f)
 for value in range(256):
  f=fixture();f['actors'][0][4]=value;f['houses'][0][5]=value;f['types'][1][2]=value;f['actors'][1][13]=value;yield emit('raw_actor_House_type_and_weapon_bytes',f)
 for n in (-2,0,1,4,8):
  for reg in (0,1,8,9,32):
   for cache in range(3):
    f=fixture();f['actorCount']=n;f['registryConfig'][0]=[reg,0,1,cache,0,4];yield emit('live_registry_cache_and_actor_count',f)
 for index in (-2**31,-33,-32,-2,-1,0,1,31,32,33,2**31-1):
  for score in (-2**31,-1,0,1,2**31-1):
   f=fixture();f['houses'][1][0]=index;f['scores'][1]=[2,score];f['scores'][2]=[2,7];yield emit('wrapped_masks_duplicate_score_and_negation',f)
 for delay in (0.,.6,1.,-1.,1.125,2**22+0.5):
  for announce in (0,1,255):
   f=fixture();f.update(delayBits=bits(delay),announce=announce);yield emit('message_duration_and_speech',f)
 for h in range(1,6):
  for mask in (0,1,2,0xffffffff):
   for quiet in (0,1):
    f=fixture();f.update(currentHouse=h,quiet=quiet);f['houses'][1][3]=mask;f['houses'][h-1][3]=mask;yield emit('reciprocal_alliance_and_current_House_speech',f)
 rng=random.Random(0x4e5660)
 for _ in range(128):
  f=fixture();f.update(mode=rng.choice([0,1,4,-1]),mutation=rng.randrange(16),actorCount=rng.randrange(-2,9),unrestricted=rng.randrange(2),actorBacking=rng.randrange(1,3),currentHouse=rng.randrange(1,6))
  for a in f['actors']:a[0]=rng.choice([0,1,2,6,11,15]);a[4]=rng.randrange(2);a[5]=rng.choice([1,2,-1]);a[6]=rng.randrange(6);a[7]=rng.randrange(5);a[11]=rng.randrange(5);a[13]=rng.choice([0,1,255,-1])
  for e in f['registry']:e[1]=rng.randrange(5)
  yield emit('deterministic_shared_owner_mix',f)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_make_ally.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0
 services={1,2,3,4,5,6,7,8,9,10,16,44,56,60,240,696,848,0x404,0x228,0x310,0x25c,0x41ba10,0x781f20}
 while i<len(row) and row[i]=='E':
  require(i+6<=len(row));service,a,b,allies,mask=map(int,row[i+1:i+6]);require(service in services and -2**31<=a<2**31 and -2**31<=b<2**32 and 0<=allies<2**32 and 0<=mask<2**32);i+=6
 require(i<=60000 and row[i:i+3]==['R','0','F'] and len(row)-i==313);v=list(map(int,row[i+3:]));require(len(v)==310 and all(-2**31<=x<2**64 for x in v))
 require(v[3] in (1,2) and v[4] in range(1,6) and v[8] in (0,1) and v[9] in (0,1) and 0<=v[10]<=32 and 0<=v[11]<=255 and v[12] in (1,2) and v[13] in range(3) and v[14] in range(32) and v[15] in range(5))
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_make_ally import HouseMakeAllyOracle
  oracle=HouseMakeAllyOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x4e5660,0x4ec4e0,0x4eeba0,0x6b54a0,0x6b5910,0x40dc20,0x41ba10,0x781d46,0x6c9af0,0x6c5070,0x77f110)) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House MakeAlly sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
