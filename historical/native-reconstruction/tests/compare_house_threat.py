#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete House threat grid, score/enemy and projection differential proof."""
import argparse,copy,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_house_threat import verify,table_values
NATIVE=('src/sim/HouseThreat.hpp','tests/house_threat_vectors.cpp','CMakeLists.txt')
ORIGINAL=('tests/original_house_threat.py','tools/verify_house_threat.py','tests/compare_house_threat.py','tests/test_house_threat.py')
SOURCES=NATIVE+ORIGINAL
FLAGS=dict(complete_4F3420_grid=True,complete_4EEBA0_score_enemy=True,complete_54E370_projection=True,virtual_children_and_initial_owners_supplied=True,MakeAlly_parent_and_production_adoption=False)
def require(ok):
 if not ok:raise ValueError('House threat evidence/input differs')
def fixture(tables):
 return dict(root=0,current=1,target=2,delta=1,count=8,registryCount=3,mode=0,mutation=0,ix=-32768,iy=-32768,px=0,py=0,slots=[1,2,3,1,2,3,1,2],houses=[[i,0,0,0,0,91] for i in range(4)],scores=[[2,3],[3,5],[2,7],[4,5],[1,100],[3,-1],[4,0],[2,0]],actors=[[0,1,16,15,1,2,2,128,128,160,160],[0,1,32,0,1,2,3,128,128,160,160],[0,1,64,0,0,0,1,128,128,160,160]],tables=tables[:])
def command(f):
 keys=('root','current','target','delta','count','registryCount','mode','mutation','ix','iy','px','py')
 values=[f[k] for k in keys]+f['slots']+[v for name in ('houses','scores','actors') for row in f[name] for v in row]+f['tables']
 return 'T '+' '.join(map(str,values))
def parse(cmd):
 t=cmd.split();require(len(t)==112 and t[0]=='T');v=list(map(int,t[1:]));keys=('root','current','target','delta','count','registryCount','mode','mutation','ix','iy','px','py');f=dict(zip(keys,v[:12]));f['slots']=v[12:20];f['houses']=[v[i:i+6] for i in range(20,44,6)];f['scores']=[v[i:i+2] for i in range(44,60,2)];f['actors']=[v[i:i+11] for i in range(60,93,11)];f['tables']=v[93:111]
 signed=lambda x:-2**31<=x<2**31;word=lambda x:-32768<=x<=32767;byte=lambda x:0<=x<=255
 require(f['root'] in (0,1,2) and 1<=f['current']<=4 and 0<=f['target']<=4 and signed(f['delta']) and -2<=f['count']<=8 and -2<=f['registryCount']<=8 and signed(f['mode']) and 0<=f['mutation']<=6)
 require(all(word(f[k]) for k in ('ix','iy','px','py')) and all(1<=s<=3 for s in f['slots']))
 for index,field,a,b,mask,enemy in f['houses']:require(signed(index) and all(byte(x) for x in (field,a,b)) and 0<=mask<2**32 and signed(enemy))
 for h,value in f['scores']:require(0<=h<=4 and signed(value))
 for a in f['actors']:require(byte(a[0]) and byte(a[1]) and all(signed(x) for x in a[2:6]) and 0<=a[6]<=4 and all(word(x) for x in a[7:11]))
 require(all(signed(x) for x in f['tables']))
 if f['root']==1:
  for h,value in f['scores'][:max(0,f['count'])]:
   if h==f['target']:value=((value+f['delta']+2**31)%2**32)-2**31
   require(h!=0 or value<=0)
 return f

def scenarios(tables):
 def emit(label,f):return label,command(f)
 # Projection is independently callable even where grid access would be refused.
 edges=(-32768,-32767,-513,-5,-4,-3,-1,0,1,3,4,5,511,512,32766,32767)
 for x in edges:
  for y in edges:
   f=fixture(tables);f.update(root=2,px=x,py=y);yield emit('signed_word_projection_toward_zero',f)
 for count in (-2,0,1,3,8):
  for kinds in ([15,0,0],[0,1,0],[0,0,2],[0,0,0],[1,15,2]):
   f=fixture(tables);f['registryCount']=count
   for a in f['actors']:a[3:6]=kinds[:]
   yield emit('reverse_saved_registry_and_repeated_kinds',f)
 for value in range(256):
  f=fixture(tables);f['actors'][0][0]=value;f['actors'][1][1]=value;f['houses'][2][2]=value;yield emit('all_raw_active_flags',f)
 for mode in (0,1,-1):
  for flags in ((0,0),(0,1),(1,0),(255,255)):
   for owner in range(5):
    for mask in (0,0xffffffff):
     f=fixture(tables);f['mode']=mode;f['houses'][0][2:4]=flags;f['houses'][0][4]=mask
     for a in f['actors']:a[6]=owner
     yield emit('mode_owner_filter_only_stored_cell_branch',f)
 for mutation in range(7):
  for kinds in ([15,0,0],[0,1,0],[0,0,2],[0,0,0]):
   f=fixture(tables);f['mutation']=mutation
   for a in f['actors']:a[3:6]=kinds[:]
   yield emit('late_shared_fields_and_registry_diagnostic',f)
 for strength in (-2**31,-1,0,1,3,4,2**30,2**31-1):
  f=fixture(tables);f.update(registryCount=8,mutation=4)
  for a in f['actors']:a[2]=strength;a[3:6]=[15,1,2]
  yield emit('signed_threat_snapshot_wrapped_add_zero_clamp',f)
 for x,y in ((-3,-3),(-4,4),(528,-4),(0,0),(511,511)):
  f=fixture(tables)
  for a in f['actors']:a[7:11]=[x,y,x,y]
  yield emit('stencil_near_edge_negative_division',f)
 f=fixture(tables);f.update(ix=128,iy=128);yield emit('invalid_stored_cell_skip_only',f)
 # Complete score update: duplicates, signed wrapping, filtering and first tie.
 for count in (-2,0,1,2,5,8):
  for delta in (-2**31,-7,-1,0,1,2**31-1):
   for target in (1,2,3,4):
    f=fixture(tables);f.update(root=1,count=count,delta=delta,target=target);yield emit('all_matches_wrapped_score_update_and_enemy',f)
 for index in (-2**31,-33,-32,-2,-1,0,1,31,32,33,2**31-1):
  for mask in (0,1,0x80000000,0xffffffff):
   f=fixture(tables);f.update(root=1,delta=0);f['houses'][1][0]=index;f['houses'][0][4]=mask;yield emit('enemy_wrapped_alliance_shift_and_same_index',f)
 for value in range(256):
  f=fixture(tables);f.update(root=1,delta=0);f['houses'][1][1]=value;yield emit('enemy_raw13D_filter',f)
 for order in ((2,3),(3,2)):
  for blocked in (0,1,255):
   f=fixture(tables);f.update(root=1,target=4,delta=0,count=2);f['scores'][:2]=[[order[0],9],[order[1],9]];f['houses'][order[0]-1][1]=blocked;yield emit('first_equal_maximum_and_earlier_exclusion',f)
 f=fixture(tables);f.update(root=1,target=0,delta=-1);f['scores']=[[0,-1] for _ in range(8)];yield emit('nonnull_guard_not_entered_for_nonpositive_null',f)
 rng=random.Random(0x4f3420)
 for _ in range(64):
  f=fixture(tables);f.update(root=rng.randrange(2),current=rng.randrange(1,5),delta=rng.choice([-2**31,-1,0,1,2**31-1]),registryCount=rng.randrange(-2,9),count=rng.randrange(-2,9),mutation=rng.randrange(7),slots=[rng.randrange(1,4) for _ in range(8)])
  for h in f['houses']:h[:]=[rng.choice([-32,-1,0,1,31,32]),rng.choice([0,1]),rng.choice([0,255]),rng.choice([0,1]),rng.getrandbits(32),-1]
  for a in f['actors']:a[0:7]=[rng.randrange(2),rng.randrange(2),rng.choice([-1,0,1,2**31-1]),rng.choice([0,1,2,15]),rng.choice([0,1,2,15]),rng.choice([0,1,2,15]),rng.randrange(5)]
  for s in f['scores']:s[:]=[rng.randrange(1,5),rng.choice([-2**31,-1,0,1,2**31-1])]
  yield emit('deterministic_shared_aliases',f)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_house_threat.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate_row(cmd,row):
 f=parse(cmd);require(isinstance(row,list) and all(isinstance(x,str) for x in row));i=0
 while i<len(row) and row[i]=='V':
  require(i+3<len(row) and 1<=int(row[i+1])<=3 and int(row[i+2]) in (672,44,420) and -2**31<=int(row[i+3])<2**31);i+=4
 require(i<=8*5*4 and len(row)>=i+85 and row[i]=='R' and row[i+2]=='S')
 require(int(row[i+1])==0 or f['root']==2)
 values=list(map(int,row[i+3:i+82]));require(len(values)==79 and all(-2**31<=v<2**32 for v in values))
 require(row[i+82]=='G' and int(row[i+83])==(0 if f['root']==0 else 0x77777777));n=int(row[i+84]);require(0<=n<=0x4204 and len(row)==i+85+2*n)
 previous=-1
 for j in range(i+85,len(row),2):
  index,value=map(int,row[j:j+2]);require(previous<index<0x4204 and -2**31<=value<2**31 and value!=int(row[i+83]));previous=index
 if f['root']!=0:require(i==0)
def validate(e,r,f,current,tables):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios(tables));require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);tables=table_values(a.exe.read_bytes());runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,tables);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_house_threat import HouseThreatOracle
  oracle=HouseThreatOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios(tables):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and all(oracle.counts[hex(p)]>0 for p in (0x4f3420,0x4eeba0,0x54e370)) and all(oracle.counts['supplied_'+str(k)]>0 for k in (672,44,420)) and current==identities(a) and runner==hash_file(a.native))
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'House threat sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
