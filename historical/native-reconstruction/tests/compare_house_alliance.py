#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete House eligibility, House lookup and country ordinal differential proof."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_alliance import verify
NATIVE=('src/sim/HouseAlliance.hpp','tests/house_alliance_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_house_alliance.py','tools/verify_house_alliance.py','tests/compare_house_alliance.py','tests/test_house_alliance.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_nonnull_4EC4E0_eligibility=True,complete_4ED760_house_lookup=True,complete_67AF90_country_ordinal=True,string_comparison_and_initial_owners_supplied=True,MakeAlly_mutation_and_production_adoption=False)
def require(ok):
 if not ok:raise ValueError('House alliance evidence/input differs')
def fixture():
 return dict(root=0,current=1,target=2,country=13,mode=0,unrestricted=0,houseCount=5,typeCount=4,mutation=0,houseSlots=[1,2,3,4,5,1,2,3],typeSlots=[1,2,3,4],types=[[13,9,0,1],[7,9,0,1],[13,9,0,0],[-1,9,0,1]],houses=[[i,i%4+1,0,0] for i in range(5)])
def command(f):
 keys=('root','current','target','country','mode','unrestricted','houseCount','typeCount','mutation')
 values=[f[k] for k in keys]+f['houseSlots']+f['typeSlots']+[v for row in f['types'] for v in row]+[v for row in f['houses'] for v in row]
 return 'H '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(len(t)==58 and t[0]=='H');v=list(map(int,t[1:]));require(all(-2**31<=x<2**31 for x in v[:9]))
 keys=('root','current','target','country','mode','unrestricted','houseCount','typeCount','mutation');f=dict(zip(keys,v[:9]));f['houseSlots']=v[9:17];f['typeSlots']=v[17:21];f['types']=[v[i:i+4] for i in range(21,37,4)];f['houses']=[v[i:i+4] for i in range(37,57,4)]
 require(f['root'] in (0,1,2) and 1<=f['current']<=5 and 1<=f['target']<=5 and -2<=f['houseCount']<=8 and -2<=f['typeCount']<=4 and 0<=f['mutation']<=4)
 require(all(1<=x<=5 for x in f['houseSlots']) and all(1<=x<=4 for x in f['typeSlots']))
 for country,parent,passive,comparison in f['types']:require(-2**31<=country<2**31 and -2**31<=parent<2**31 and 0<=passive<=255 and -2**31<=comparison<2**31)
 for index,kind,field,mask in f['houses']:require(-2**31<=index<2**31 and 1<=kind<=4 and 0<=field<=255 and 0<=mask<2**32)
 return f

def scenarios():
 def emit(label,f):return label,command(f)
 # Signed House keys, first duplicate country match, saved registry count.
 for count in (-2,0,1,2,5,8):
  for country in (-2**31,-1,0,7,13,2**31-1):
   f=fixture();f.update(root=1,houseCount=count,country=country);yield emit('house_first_match_signed_count_country',f)
 # Country finder returns slot ordinal and rereads count/backing after comparison.
 for count in (-2,0,1,4):
  for match in (-1,0,1,2,3):
   for mutation in range(5):
    f=fixture();f.update(root=2,typeCount=count,mutation=mutation)
    for i,t in enumerate(f['types']):t[3]=0 if i==match else (-2**31 if i%2 else 2**31-1)
    yield emit('country_ordinal_live_backing_count',f)
 # Early returns must bypass all comparison callbacks.
 for target in (1,2):
  for index in (-2**31,-33,-32,-2,-1,0,1,31,32,33,2**31-1):
   for mask in (0,1,0x80000000,0xffffffff):
    f=fixture();f.update(target=target,mutation=4);f['houses'][target-1][0]=index;f['houses'][0][3]=mask;yield emit('entry_identity_index_and_x86_shift',f)
 # Distinguish Civilian ordinal2 from typeB8=13 and no-match ordinal -1.
 for match in (False,True):
  for parent in (-1,0,2,13):
   for mode in (0,1,-2**31):
    for unrestricted in (0,1,-1):
     f=fixture();f.update(mode=mode,unrestricted=unrestricted);f['types'][1][1]=parent
     if not match:
      for t in f['types']:t[3]=1
     yield emit('civilian_ordinal_before_unrestricted',f)
 # Every raw byte: zero/nonzero eligibility, passive filtering and late current flag.
 for byte in range(256):
  for field in ('current','candidate','passive'):
   f=fixture()
   if field=='current':f['houses'][0][2]=byte
   elif field=='candidate':f['houses'][1][2]=byte
   else:f['types'][1][2]=byte
   yield emit('raw_byte_'+field,f)
 # Empty registry true; exactly one eligible nonally false; aliases count per slot.
 for count in (-2,0,1,2,3,5,8):
  for slots in ([1]*8,[2]*8,[1,2,3,4,5,1,2,3]):
   f=fixture();f.update(houseCount=count,houseSlots=slots);yield emit('eligible_not_allied_plus_one',f)
 # Late comparator writes touch the same borrowed records, never repeat entry guards.
 for mutation in range(5):
  for match in (-1,0,1,3):
   for count in (0,1,5):
    f=fixture();f.update(mutation=mutation,houseCount=count)
    for i,t in enumerate(f['types']):t[3]=0 if i==match else 1
    yield emit('late_shared_owners_after_comparison',f)
 rng=random.Random(0x4ec4e0)
 for _ in range(160):
  f=fixture();f.update(root=rng.randrange(3),current=rng.randrange(1,6),target=rng.randrange(1,6),mode=rng.choice([0,1,-1]),unrestricted=rng.choice([0,1]),mutation=rng.randrange(5),houseCount=rng.randrange(-2,9),typeCount=rng.randrange(-2,5),houseSlots=[rng.randrange(1,6) for _ in range(8)],typeSlots=[rng.randrange(1,5) for _ in range(4)])
  for t in f['types']:t[:]=[rng.choice([-1,0,13]),rng.choice([-1,0,1,2,3,13]),rng.choice([0,1,255]),rng.choice([0,1,-1])]
  for h in f['houses']:h[:]=[rng.choice([-2**31,-32,-2,-1,0,1,31,32,2**31-1]),rng.randrange(1,5),rng.choice([0,1,255]),rng.getrandbits(32)]
  yield emit('deterministic_mixed_aliases_and_late_fields',f)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_alliance.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0
 while i<len(row) and row[i]=='C':
  require(i+2<len(row) and 1<=int(row[i+1])<=4 and -2**31<=int(row[i+2])<2**31);i+=3
 require(i<=12 and len(row)-i==37 and row[i]=='R' and row[i+2]=='S')
 result=int(row[i+1]);require(result in (0,1) if f['root']==0 else 0<=result<=5 if f['root']==1 else -1<=result<=3)
 values=list(map(int,row[i+3:]));require(len(values)==34 and values[4] in (0,1) and values[5] in (0,1))
 require(all(-2**31<=v<2**31 for v in values[:4]))
 for j in range(6,26,4):require(-2**31<=values[j]<2**31 and 1<=values[j+1]<=4 and 0<=values[j+2]<=255 and 0<=values[j+3]<2**32)
 for j in range(26,34,2):require(-2**31<=values[j]<2**31 and 0<=values[j+1]<=255)
 if f['root']==1:require(i==0)
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_alliance import HouseAllianceOracle
  oracle=HouseAllianceOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x4ec4e0,0x4ed760,0x67af90)) and oracle.counts['supplied_compare']>0 and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House alliance sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
