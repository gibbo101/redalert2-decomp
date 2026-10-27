#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete target references with the original compiled sort and comparator."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_target_reference import verify
NATIVE=('src/sim/TargetReference.hpp','tests/target_reference_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_target_reference.py','tools/verify_target_reference.py','tests/compare_target_reference.py','tests/test_target_reference.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_target_construction_and_registry_resolution=True,complete_Techno_cast=True,actual_compiled_sort_and_signed_comparator=True,virtual_kind_ID_and_initial_owners_supplied=True,MakeAlly_parent_and_production_adoption=False)
def require(ok):
 if not ok:raise ValueError('Target reference evidence/input differs')
def fixture():
 return dict(root=1,token=0,object=1,count=32,sorted=0,backing=1,cacheBacking=0,cacheIndex=0,fallback=4,mutation=0,tokens=[[7,52,165,0,255],[99,52,1,2,3]],objects=[[1,7,-32768,32767],[2,99,32767,-32768],[6,-1,0,-1],[15,0,-1,0]],primary=[[31-i,1+i%4] for i in range(32)],alternate=[[i,4-i%4] for i in range(32)],detached=[[7,3]])
KEYS=('root','token','object','count','sorted','backing','cacheBacking','cacheIndex','fallback','mutation')
def command(f):
 return 'J '+' '.join(map(str,[f[k] for k in KEYS]+[v for name in ('tokens','objects','primary','alternate','detached') for row in f[name] for v in row]))
def parse(cmd):
 t=cmd.split();require(len(t)==167 and t[0]=='J');v=list(map(int,t[1:]));f=dict(zip(KEYS,v[:10]));offset=10
 for name,count,width in (('tokens',2,5),('objects',4,4),('primary',32,2),('alternate',32,2),('detached',1,2)):
  f[name]=[v[i:i+width] for i in range(offset,offset+count*width,width)];offset+=count*width
 signed=lambda x:-2**31<=x<2**31;byte=lambda x:0<=x<=255
 require(f['root'] in range(4) and f['token'] in range(2) and f['object'] in range(5) and -2<=f['count']<=32 and byte(f['sorted']) and f['backing'] in (1,2) and f['cacheBacking'] in range(4) and f['cacheIndex'] in range(32) and (f['cacheBacking']!=3 or f['cacheIndex']==0) and f['fallback'] in range(5) and f['mutation'] in range(9))
 for row in f['tokens']:require(signed(row[0]) and all(byte(x) for x in row[1:]))
 for kind,uid,x,y in f['objects']:require(signed(kind) and signed(uid) and -32768<=x<=32767 and -32768<=y<=32767)
 for key,obj in f['primary']+f['alternate']+f['detached']:require(signed(key) and obj in range(5))
 return f

def scenarios():
 def emit(label,f):return label,command(f)
 for n in range(33):
  for mode in range(7):
   f=fixture();f['count']=n
   keys=[31-i for i in range(32)] if mode==0 else list(range(32)) if mode==1 else [7]*32 if mode==2 else [i%3-1 for i in range(32)] if mode==3 else [(-2**31,2**31-1,0,-1)[i%4] for i in range(32)] if mode==4 else [0]*32 if mode==5 else [((i*17)%32)-16 for i in range(32)]
   f['primary']=[[key,1+i%4] for i,key in enumerate(keys)];f['tokens'][0][0]=7 if mode in (0,1,2) else -1 if mode in (3,4) else 0
   yield emit('compiled_sort_threshold_ties_and_order',f)
 for kind in (-2**31,-1,*range(18),2**31-1):
  for obj in range(5):
   for root in (0,2,3):
    f=fixture();f.update(root=root,object=obj)
    for o in f['objects']:o[0]=kind
    yield emit('complete_construction_cast_null_and_signed_kinds',f)
 for obj in range(5):
  for kind in (0,1,2,6,11,15,16):
   f=fixture();f.update(count=1,fallback=4);f['primary'][0]=[7,obj];f['tokens'][1][0]=7
   if obj:f['objects'][obj-1][0]=kind
   yield emit('selected_null_or_nonTechno_never_uses_fallback',f)
 for tag in range(256):
  f=fixture();f['tokens'][0][1]=tag;yield emit('raw_token_tags',f)
 for sorted in (0,1,255):
  for count in (-2,0,1,8,9,32):
   for backing in (1,2):
    for cached in range(4):
     if count<0 and sorted==0:continue
     f=fixture();f.update(count=count,sorted=sorted,backing=backing,cacheBacking=cached)
     yield emit('cache_before_sort_old_backing_zero_count_and_fallback',f)
 for mutation in range(9):
  for root in range(4):
   for kind in (1,11,0):
    f=fixture();f.update(mutation=mutation,root=root);f['objects'][0][0]=kind;yield emit('late_callback_token_and_registry_mutations',f)
 for x,y in ((-32768,-32768),(-32768,32767),(32767,-32768),(32767,32767),(0,0),(-1,1)):
  f=fixture();f.update(root=0);f['objects'][0][0]=11;f['objects'][0][2:]=[x,y];yield emit('signed_Cell_word_encoding',f)
 rng=random.Random(0x6b5910)
 for _ in range(192):
  f=fixture();f.update(count=rng.randrange(33),sorted=rng.choice([0,1,255]),cacheBacking=rng.randrange(4),cacheIndex=0,mutation=rng.randrange(9),fallback=rng.randrange(5),backing=rng.choice([1,2]),root=rng.randrange(4),object=rng.randrange(5),token=rng.randrange(2))
  for name in ('primary','alternate','detached'):f[name]=[[rng.choice([-2**31,-7,-1,0,1,7,99,2**31-1]),rng.randrange(5)] for _ in f[name]]
  for t in f['tokens']:t[:2]=[rng.choice([-2**31,-7,0,7,99,2**31-1]),rng.choice([0,11,52,255])]
  for o in f['objects']:o[0]=rng.choice([0,1,2,6,11,15,16])
  yield emit('deterministic_shared_registry_mix',f)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_target_reference.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0;results=0;events=0;signed=lambda x:-2**31<=x<2**31;byte=lambda x:0<=x<=255
 while i<len(row) and row[i]!='F':
  event=row[i];size={'K':7,'I':4,'C':6,'R':2}.get(event);require(size is not None and i+size<=len(row));v=list(map(int,row[i+1:i+size]));require(all(signed(x) for x in v))
  if event=='K':require(1<=v[0]<=4 and v[2] in range(4) and v[3] in range(32) and (v[2]!=3 or v[3]==0) and byte(v[4]) and -2<=v[5]<=32)
  if event=='I':require(1<=v[0]<=4 and byte(v[1]))
  if event=='C':require(v[0] in (1,2) and v[1] in range(32) and v[2] in range(32))
  if event=='R':require(v[0] in range(5));results+=1
  i+=size;events+=1
 require(events<=10000 and results==(3 if f['root'] in (1,3) else 1) and len(row)-i==164 and row[i]=='F');v=list(map(int,row[i+1:]));require(len(v)==163 and -2<=v[0]<=32 and byte(v[1]) and v[2] in (1,2) and v[3] in range(4) and v[4] in range(32) and (v[3]!=3 or v[4]==0) and v[5] in range(5) and v[6] in (0,1))
 for j in (7,12):require(signed(v[j]) and all(byte(x) for x in v[j+1:j+5]))
 for j in range(17,33,4):require(signed(v[j]) and signed(v[j+1]) and -32768<=v[j+2]<=32767 and -32768<=v[j+3]<=32767)
 for j in range(33,163,2):require(signed(v[j]) and v[j+1] in range(5))
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_target_reference import TargetReferenceOracle
  oracle=TargetReferenceOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(3 if parse(c)['root'] in (1,3) else 1 for c in commands) and all(oracle.counts[hex(p)]>0 for p in (0x6b54a0,0x6b5910,0x40dc20,0x41ba10,0x781d46,0x781e9a,0x781ee8)) and oracle.counts['supplied_kind']>0 and oracle.counts['supplied_secondary_ID']>0 and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Target reference sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
