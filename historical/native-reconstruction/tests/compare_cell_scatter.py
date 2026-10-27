#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Cell snapshot/dispatch proof, retaining explicit member/heap service boundaries."""
import argparse,copy,itertools,json,random,struct,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_cell_scatter import verify,RANGES
SOURCES=('src/sim/CellScatter.hpp','src/sim/Drive.hpp','src/sim/Targeting.hpp','src/sim/Facing.hpp',
 'tests/cell_scatter_vectors.cpp','tests/cell_scatter/CMakeLists.txt','tests/original_cell_scatter.py',
 'tests/compare_cell_scatter.py','tests/test_cell_scatter_evidence.py','tools/verify_cell_scatter.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py',
 'tests/compare_original.py','tools/verify_terrain_visibility.py')
def bits(n):return struct.unpack('<Q',struct.pack('<d',n))[0]
RANKS=[bits(n) for n in (-1.,0.,0.9999999999999999,1.,1.9999999999999998,2.,float('inf'))]+[0x7ff8000000000123]
MEMBERS=[[1,1,0,0,bits(0.)],[36,2,1,1,bits(0.)],[6,3,1,1,bits(0.)],[1,-1,0,0,bits(0.)]]
def command(h=None,types=None,houses=None,members=None,call=None,growth=None):
 members=MEMBERS if members is None else members
 h=[len(members),0,2,0,3] if h is None else h
 types=[[0,0],[0,0]] if types is None else types;houses=[0,5] if houses is None else houses
 call=[17,-19,23,0,0,0,0] if call is None else call;growth=[1] if growth is None else growth
 flat=lambda v:itertools.chain.from_iterable(v)
 return 'C '+' '.join(map(str,[*h,*flat(types),*houses,*flat(members),*call,len(growth),*growth]))
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Cell scatter input')
def parse(cmd):
 t=cmd.split();require(t and t[0]=='C');i=1
 def take(n):
  nonlocal i
  v=list(map(int,t[i:i+n]));i+=n;require(len(v)==n);return v
 byte=lambda n:0<=n<=255;i32=lambda n:-2147483648<=n<=2147483647
 h=take(5);n,p,e,flag,limit=h;require(0<=n<=32 and all(-1<=x<n for x in (p,e)) and byte(flag) and i32(limit))
 types=[take(2) for _ in range(2)];houses=take(2);require(all(byte(v) for row in types for v in row) and all(i32(v) for v in houses))
 members=[take(5) for _ in range(n)]
 for kind,next_,type_,owner,rank in members:require(kind in (1,6,36) and -1<=next_<n and type_ in (0,1) and owner in (0,1) and 0<=rank<1<<64)
 for at in range(n):
  seen=set()
  while at!=-1:require(at not in seen);seen.add(at);at=members[at][1]
 call=take(7);require(all(i32(v) for v in call[:3]) and all(byte(v) for v in call[3:6]) and 0<=call[6]<=5)
 count=take(1)[0];require(1<=count<=8);growth=take(count);require(all(0<=v<1<<32 for v in growth) and i==len(t))
 return h,types,houses,members,call,growth
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES})
FLAGS=dict(actual_complete_Cell_root=True,actual_cast_promotion_type_children=True,
 supplied_heap_and_member_Scatter_services=True,Unit_Scatter_executed=False,
 Advance6_executed=False,runtime_enabled=False,root_void_no_EAX_claim=True)
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006')
 require(e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('expected',[]))==len(e.get('labels',[])))
 for cmd,result in zip(e['commands'],e['expected']):
  parse(cmd);require(isinstance(result,list) and bool(result) and all(isinstance(v,str) for v in result) and result.count('state')==1)
def generate(a):
 from original_cell_scatter import CellScatterOracle
 o=CellScatterOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,**kw):
  cmd=command(**kw);result=o.run(*parse(cmd));commands.append(cmd);expected.append(result);labels.append(label);groups[label]=groups.get(label,0)+1
 for im,dest,layer,flag in itertools.product((0,1,128,255),repeat=4):
  add('raw_control_bytes_and_distinct_primary_elevated_lists',h=[4,0,2,flag,3],call=[17,-19,23,im,dest,layer,0])
 for rank,layer,im,dest in itertools.product(RANKS,(0,1),(0,1),(0,1)):
  rows=copy.deepcopy(MEMBERS);rows[3][4]=rank
  add('elite_prepass_early_exit_and_cached_force_including_NaN',members=rows,call=[0,0,0,im,dest,layer,0])
 for kind,rank,v,e in itertools.product((1,6),RANKS,(0,1,128,255),(0,1,128,255)):
  add('actual_promotion_ability3_type_and_House_children',h=[1,0,-1,0,3],types=[[v,e],[255,255]],houses=[-1,5],members=[[kind,-1,0,0,rank]],call=[17,-19,23,0,0,0,0])
 for kind,v,e in itertools.product((1,6),(0,1,128,255),(0,1,128,255)):
  add('diagnostic_growth_promotion_reaches_late_elite_ability3',h=[1,0,-1,0,3],types=[[v,e],[0,0]],houses=[-1,5],members=[[kind,-1,0,0,bits(0.)]],call=[17,-19,23,0,0,0,5])
 for threshold,left,right in itertools.product((-2147483648,-1,0,1,2147483647),repeat=3):
  add('signed_House194_and_rules10b4_comparison',h=[4,0,2,0,threshold],houses=[left,right],call=[17,-19,23,0,1,0,0])
 for n,pattern in itertools.product((0,1,9,10,11,19,20,21,31,32),([1],[0],[256],[257],[255,0],[0,1],[1,0,1])):
  rows=[[1,i+1 if i+1<n else -1,i&1,i&1,bits(0.)] for i in range(n)]
  add('snapshot_capacity_ten_growth_failures_low_byte_and_cleanup',h=[n,0 if n else -1,-1,1,0],members=rows,growth=pattern)
 for mutation,im,dest,layer in itertools.product(range(1,5),(0,1),(0,1),(0,1)):
  add('diagnostic_service_mutations_preserve_snapshot_and_live_late_reads',h=[4,0,2,1,3],call=[-2147483648,2147483647,-1,im,dest,layer,mutation])
 for point in ((0,0,0),(-2147483648,2147483647,-2147483648),(2147483647,-2147483648,2147483647)):
  add('borrowed_full_signed_coordinate_forwarding',h=[4,0,2,1,0],call=[*point,255,128,255,4])
 rng=random.Random(0x476920)
 for _ in range(160):
  n=rng.randrange(33);order=list(range(n));rng.shuffle(order);rows=[]
  nexts={a:b for a,b in zip(order,order[1:]+[-1])}
  for i in range(n):rows.append([rng.choice((1,6,36)),nexts[i],rng.randrange(2),rng.randrange(2),rng.choice(RANKS)])
  add('seeded_ordered_heterogeneous_lists_and_shared_type_House_inputs',h=[n,order[0] if n else -1,order[-1] if n else -1,rng.randrange(256),rng.choice((-2147483648,-1,0,1,2147483647))],
   types=[[rng.randrange(256),rng.randrange(256)] for _ in range(2)],houses=[rng.choice((-2147483648,0,2147483647)) for _ in range(2)],members=rows,
   call=[rng.randrange(-2147483648,2147483648) for _ in range(3)]+[rng.randrange(256) for _ in range(3)]+[rng.randrange(5)],growth=rng.choice(([0,1],[256,255],[1],[0])))
 require(all(o.entries.get(hex(k),0) for k in RANGES))
 require(all(o.returns.get((k,n),0) for k in ('veteran','elite','ability3') for n in (0,1)))
 return commands,expected,labels,dict(FLAGS,groups=groups,audited_original_calls=o.audit_calls,
  actual_entries=dict(o.entries),actual_returns=[[k,v,n] for (k,v),n in sorted(o.returns.items())],
  selected_snapshot_stores=o.snapshot_stores,distinct_original_instructions=len(o.instructions),
  supplied_service_calls=dict(o.service_counts),diagnostic_mutations_not_gameplay_observations=True,
  full_arena_and_caller_checks=o.audit_calls)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise RuntimeError(('Cell scatter native failure',len(p.stdout.splitlines()),p.stderr))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(cmd,row,wanted) in enumerate(zip(commands,rows,expected)):
  result=row.split()
  if result!=wanted:
   at=next((j for j,(x,y) in enumerate(zip(result,wanted)) if x!=y),min(len(result),len(wanted)))
   raise AssertionError(('Cell scatter differs',i,cmd,at,result[max(0,at-6):at+12],wanted[max(0,at-6):at+12]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/cell-scatter/cell-scatter-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/cell-scatter-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'report.json').exists() and not(folder/'expected.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(identities(a)==current and hash_file(a.native)==runner)
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'complete Cell scatter calls: PASS (member/heap services supplied)')
if __name__=='__main__':main()
