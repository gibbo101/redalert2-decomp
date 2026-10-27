#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete exact-base MakeEnemy differential proof with actual score updates."""
import argparse,copy,json,platform,random,struct,subprocess,sys,time,math
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_make_enemy import verify
NATIVE=('src/sim/HouseMakeEnemy.hpp','src/sim/HouseThreat.hpp','src/sim/MissionTextAction.hpp','src/sim/OriginalMath.hpp','tests/house_make_enemy_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_house_make_enemy.py','tools/verify_house_make_enemy.py','tests/compare_house_make_enemy.py','tests/test_house_make_enemy.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_4E5A70_with_out_of_line_tail=True,actual_4EEBA0_score_and_77F110_conversion=True,map_grid_ui_and_initial_owners_supplied=True,production_adoption=False)
def require(ok):
 if not ok:raise ValueError('MakeEnemy evidence/input differs')
def bits(x):return struct.unpack('<Q',struct.pack('<d',x))[0]
def fixture():return dict(current=1,target=2,announce=1,mode=1,unrestricted=0,currentHouse=1,delayBits=bits(.6),mutation=0,houses=[[i,i,0,0xffffffff,0xa5a5a5a5,1 if i==1 else 0,0,91,2] for i in range(1,4)],types=[[0,i] for i in range(1,4)],scores=[[2,3],[3,5]]*3)
def command(f):return 'M '+' '.join(map(str,[f[k] for k in ('current','target','announce','mode','unrestricted','currentHouse','delayBits','mutation')]+[v for name in ('houses','types','scores') for row in f[name] for v in row]))
def parse(cmd):
 t=cmd.split();require(len(t)==54 and t[0]=='M');v=list(map(int,t[1:]));f=dict(zip(('current','target','announce','mode','unrestricted','currentHouse','delayBits','mutation'),v[:8]));f['houses']=[v[i:i+9] for i in range(8,35,9)];f['types']=[v[i:i+2] for i in range(35,41,2)];f['scores']=[v[i:i+2] for i in range(41,53,2)]
 signed=lambda x:-2**31<=x<2**31;byte=lambda x:0<=x<=255;mask=lambda x:0<=x<2**32
 require(1<=f['current']<=3 and 0<=f['target']<=3 and byte(f['announce']) and signed(f['mode']) and signed(f['unrestricted']) and 0<=f['currentHouse']<=3 and 0<=f['delayBits']<2**64 and 0<=f['mutation']<=12)
 delay=struct.unpack('<d',struct.pack('<Q',f['delayBits']))[0];require(math.isfinite(delay) and -2**63<=delay*900<2**63)
 require(f['target']!=0 or (f['mode']==0 and f['mutation']!=10))
 for h in f['houses']:require(signed(h[0]) and 1<=h[1]<=3 and byte(h[2]) and mask(h[3]) and mask(h[4]) and byte(h[5]) and byte(h[6]) and signed(h[7]) and -2<=h[8]<=2)
 for passive,color in f['types']:require(byte(passive) and signed(color))
 for h,value in f['scores']:require(0<=h<=3 and signed(value) and (h!=0 or value<=-1))
 return f
def scenarios():
 for mode in (0,1,4,-1):
  for unrestricted in (0,1,-1):
   for target in (1,2,3):
    for announce in (0,1,255):
     f=fixture();f.update(mode=mode,unrestricted=unrestricted,target=target,announce=announce);yield 'mode_identity_masks_announce',command(f)
 for value in range(256):
  for column in (2,5,6):
   for mode in (0,1):
    f=fixture();f['mode']=mode;f['houses'][0][column]=value;f['houses'][1][column]=value;yield 'all_raw_house_flags',command(f)
 for value in range(256):
  f=fixture();f['types'][1][0]=value;yield 'raw_target_passive',command(f)
 for value in (0,1,255):
  f=fixture();f['types'][0][0]=value;yield 'initiator_passive',command(f)
 for index in (-2**31,-33,-32,-2,-1,0,1,31,32,33,2**31-1):
  for mask in (0,1,0x80000000,0xffffffff):
   for unrestricted in (0,1):
    f=fixture();f['houses'][1][0]=index;f['houses'][0][3]=mask;f['unrestricted']=unrestricted;yield 'signed_wrapped_indices_and_full_mask120_clear',command(f)
 for mutation in range(13):
  for mode in (0,1):
   for target in (1,2):
    f=fixture();f.update(mutation=mutation,mode=mode,target=target);yield 'late_service_fields_and_out_of_line_speech',command(f)
 for currentHouse in (0,1,2,3):
  for reciprocal in (0,1):
   f=fixture();f['currentHouse']=currentHouse;f['houses'][1][3]=1<<1 if reciprocal else 0;yield 'speech_saved_reciprocal_late_current_house',command(f)
 for value in (-2**31,-1,0,1,2**31-1):
  f=fixture();f['scores']=[[2,value],[2,value]]*3;yield 'duplicate_score_wrapping',command(f)
 for delay in (-.6,0.,.1,.6,1.5,2**32/900):
  f=fixture();f['delayBits']=bits(delay);yield 'actual_x87_duration_conversion',command(f)
 f=fixture();f.update(target=0,mode=0);yield 'null_target_still_scores_before_noop',command(f)
 rng=random.Random(0x4e5a70)
 for _ in range(96):
  f=fixture();f.update(current=rng.randrange(1,4),target=rng.randrange(1,4),announce=rng.choice([0,1,255]),mode=rng.choice([0,1,4]),unrestricted=rng.choice([0,1]),mutation=rng.randrange(13))
  for h in f['houses']:h[0]=rng.choice([-33,-1,0,1,31,32]);h[2]=rng.choice([0,1]);h[3]=rng.getrandbits(32);h[4]=rng.getrandbits(32);h[5]=rng.choice([0,1,255]);h[6]=rng.choice([0,255]);h[8]=rng.randrange(-2,3)
  yield 'deterministic_alias_and_late_fields',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_make_enemy.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0;events=0
 while i<len(row) and row[i]!='S':
  tag=row[i];require(tag in ('E','W'));n=8 if tag=='E' else 4;require(i+n<=len(row));v=list(map(int,row[i+1:i+n]))
  if tag=='E':require(v[0] in (1,2,4,5,6,7,8,9) and all(-2**31<=x<2**32 for x in v[1:]))
  else:require(1<=v[0]<=3 and v[1] in (0x120,0x5674) and 0<=v[2]<2**32)
  i+=n;events+=1;require(events<=16)
 require(len(row)==i+51 and row[i]=='S');v=list(map(int,row[i+1:]));require(all(-2**31<=x<2**64 for x in v))
 require(-2**31<=v[0]<2**31 and -2**31<=v[1]<2**31 and 0<=v[2]<=3 and 0<=v[3]<2**64 and v[4] in (0,1))
 # Final fields are parsed through the same typed input guards.
 f=parse(cmd);f.update(mode=v[0],unrestricted=v[1],currentHouse=v[2],delayBits=v[3],houses=[v[j:j+9] for j in range(5,32,9)],types=[v[j:j+2] for j in range(32,38,2)],scores=[v[j:j+2] for j in range(38,50,2)])
 parse(command(f))
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_make_enemy import HouseMakeEnemyOracle
  oracle=HouseMakeEnemyOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x4e5a70,0x4eeba0,0x77f110)) and oracle.counts['out_of_line_tail']>0 and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House MakeEnemy sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
