#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inclusive range results, raw rejection sequence and full retained RNG state."""
import argparse,itertools,json,random,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_random_range import verify
SOURCES=('src/sim/OriginalRandomRange.hpp','src/sim/OriginalRandom.hpp','src/sim/OriginalRandom.cpp',
 'tests/random_range_vectors.cpp','tests/random_range/CMakeLists.txt','tests/original_random_range.py',
 'tests/compare_random_range.py','tests/test_random_range_evidence.py','tools/verify_random_range.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py',
 'tests/compare_original.py','tools/verify_terrain_visibility.py')
FLAGS=dict(actual_complete_range_root=True,actual_inlined_XOR_step=True,
 supplied_initial_state=True,seeding_recovered=False,scenario_association_recovered=False,
 Unit_Scatter_executed=False,Advance6_executed=False,runtime_enabled=False,
 native_liveness_guard_not_original=True)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported random-range evidence/input')
def command(disabled=0,first=0,second=103,ranges=None,table=None):
 ranges=[(0,2),(1,4)] if ranges is None else ranges;table=[0]*250 if table is None else table
 return 'R '+' '.join(map(str,[disabled,first,second,len(ranges),*itertools.chain.from_iterable(ranges),*table]))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='R');v=list(map(int,t[1:]));require(len(v)>=4)
 disabled,first,second,count=v[:4];require(0<=disabled<=255 and -2147483648<=first<=2147483647 and -2147483648<=second<=2147483647 and 1<=count<=1024 and len(v)==4+2*count+250)
 ranges=[tuple(v[4+2*i:6+2*i]) for i in range(count)];table=v[4+2*count:]
 require(all(-2147483648<=x<=2147483647 for row in ranges for x in row) and all(0<=n<=0xffffffff for n in table))
 require(all(abs(a-b)<=0x7fffffff for a,b in ranges))
 if not disabled and any(0<abs(a-b)<0x7fffffff for a,b in ranges):require(0<=first<250 and 0<=second<250)
 return disabled,first,second,ranges,table
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006')
 require(e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(isinstance(row,list) and bool(row) and all(isinstance(v,str) for v in row) and row.count('state')==1)
def generate(a):
 from original_random_range import RandomRangeOracle
 o=RandomRangeOracle(a.exe);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x6388a0)
 def add(label,**kw):
  cmd=command(**kw);expected.append(o.run(*parse(cmd)));commands.append(cmd);labels.append(label);groups[label]=groups.get(label,0)+1
 indices=(0,1,102,103,248,249)
 for disabled,first,second in itertools.product((0,1,128,255),indices,indices):
  add('Scatter_ranges_both_orders_index_ties_wrap_and_disabled',disabled=disabled,first=first,second=second,
   ranges=[(0,2),(1,4),(2,0),(4,1)]*3,table=[rng.getrandbits(32) for _ in range(250)])
 for n in (0,1,2,3,7,8,15,16,31,32,63,64,127,128,255,256,1023,1024,65534,65535,65536,0x3ffffffe,0x3fffffff,0x40000000,0x7ffffffe):
  for low in (-2147483648,-1234567,0,2147483647-n):
   if low+n>2147483647:continue
   add('signed_endpoints_and_mask_power_boundaries',first=249,second=102,ranges=[(low,low+n),(low+n,low)],table=[rng.getrandbits(32) for _ in range(250)])
 for disabled,first,second in itertools.product((0,255),(-2147483648,0,249,2147483647),(-1,103,250)):
  add('equal_and_signed_overflow_bypass_without_generator_access',disabled=disabled,first=first,second=second,
   ranges=[(17,17),(-2147483648,-2147483648),(2147483647,2147483647),(0,2147483647),(-2147483648,-1),(-1,-2147483648),(-2147483647,0),(0,-2147483647)])
 for rejects in (0,1,2,3,9,31,100):
  table=[0]*250;table[:rejects]=[3]*rejects
  add('authored_rejection_prefix_for_0_through_2',first=0,second=103,table=table,ranges=[(0,2),(1,4)])
 for i in range(96):
  ranges=[]
  for j in range(rng.choice((1,2,7,32,251))):
   width=rng.choice((0,1,2,3,4,7,15,255,256,65535,0x7ffffffe));low=rng.randint(-2147483648,2147483647-width)
   ranges.append((low+width,low) if j&1 else (low,low+width))
  add('seeded_heterogeneous_retained_sequences',disabled=rng.choice((0,0,0,1,255)),first=rng.choice(indices),second=rng.choice(indices),ranges=ranges,table=[rng.getrandbits(32) for _ in range(250)])
 require(o.counts['root']==o.audit_calls and o.counts['rejected']>0 and max(o.attempts)>=101 and 0 in o.attempts)
 require(all(o.writes.get(hex(a),0) for a in (0x63890b,0x63891e,0x638921,0x638926,0x638935)))
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_original_calls=o.audit_calls,
  original_write_counts=dict(o.writes),actual_attempts_per_call=o.attempts,distinct_original_instructions=len(o.instructions),
  full_arena_and_caller_checks=o.audit_calls,full_state_at_sequence_end=True,
  selected_native_write_order_claim=False)
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 require(p.returncode==0);rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Random range differs',i,j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/random-range/random-range-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/random-range-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
 start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'random-range sequences PASS')
if __name__=='__main__':main()
