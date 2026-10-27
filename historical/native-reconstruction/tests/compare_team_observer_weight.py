# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete observer callbacks in a bounded finite,53-bit FP domain."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_team_observer_weight import verify
ORIGINAL=('tests/compare_team_observer_weight.py','tests/original_team_observer_weight.py','tools/verify_team_observer_weight.py')
NATIVE=('src/sim/TeamObserverWeight.hpp','src/sim/TeamObserverWeight.cpp','tests/team_observer_weight_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_observer_callbacks=True,arithmetic_children_supplied=False,precision_bits=53,finite_profile=True,caller_fp_startup_supplied=True,production_scheduling=False)
NAMES=('success','rounding','total','count','weight','minimum','maximum','successRule','failureRule','coefficient','alias','mutation','repeats')
DEFAULT=(1,1,3,2,10.,0.,100.,1.,-1.,.5,0,0,1)
def require(v):
 if not v:raise ValueError('Team observer weight evidence/domain differs')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def command(**kw):
 require(not set(kw)-set(NAMES));f=[kw.get(k,v) for k,v in zip(NAMES,DEFAULT)]
 for i in range(4,10):f[i]=bits(f[i])
 return ' '.join(map(str,f))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==13)
 require(f[0] in (0,1) and f[1] in (0,1) and all(-2**31<=f[i]<2**31 for i in (2,3)) and f[10] in (0,1) and f[11] in range(4) and f[12] in range(1,4))
 for v in f[4:10]:
  require(0<=v<2**64);d=struct.unpack('<d',struct.pack('<Q',v))[0];require(d==0 or 1e-100<=abs(d)<=1e100)
 return f
def scenarios():
 for success,rounding,total,count in itertools.product((0,1),(0,1),(-2147483648,-1,0,1,3,2147483647),(-2147483648,-1,0,1,2,2147483647)):
  yield 'signed_counters_ratio_rounding_wrap',command(success=success,rounding=rounding,total=total,count=count,repeats=3)
 for success,rounding,weight,minimum,maximum in itertools.product((0,1),(0,1),(-0.,-10.,0.,1.,100.),(0.,10.),(-1.,100.)):
  yield 'ordered_clamps_and_signed_zero',command(success=success,rounding=rounding,weight=weight,minimum=minimum,maximum=maximum)
 for success,rounding,rule,coefficient in itertools.product((0,1),(0,1),(-1e90,-1.,-0.,1e-90,1.,1e90),(-1e90,-.5,0.,.5,1e90)):
  yield 'bounded_exponents_coefficients_and_cancellation',command(success=success,rounding=rounding,successRule=rule,failureRule=rule,coefficient=coefficient,minimum=-1e100,maximum=1e100)
 for success,rounding,alias,mutation in itertools.product((0,1),(0,1),(0,1),range(4)):
  yield 'Rules_alias_late_bounds_and_saved_counter',command(success=success,rounding=rounding,alias=alias,mutation=mutation,minimum=20.,maximum=30.,repeats=2)
 for success,rounding,weight,rule in itertools.product((0,1),(0,1),(math.nextafter(1.,0.),1.,math.nextafter(1.,2.)),(-2.**-53,2.**-53)):
  yield 'adjacent_binary64_and_half_ulp_clamps',command(success=success,rounding=rounding,total=0,count=0,weight=weight,minimum=1.,maximum=math.nextafter(1.,2.),successRule=rule,failureRule=rule)
 rng=random.Random(0x41dfb0)
 for i in range(180):
  yield 'deterministic_binary64_edges',command(success=i%2,rounding=(i//2)%2,total=rng.randint(1,2147483647),count=rng.randint(-2147483648,2147483647),weight=rng.uniform(-100,100),minimum=-100.,maximum=100.,successRule=rng.uniform(-5,5),failureRule=rng.uniform(-5,5),coefficient=rng.uniform(-2,2))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_team_observer_weight.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%3==0 and len(row)==i+7)
 for j in range(0,i,3):
  off,n,v=map(int,row[j:j+3]);require((off,n) in ((184,8),(184,4),(188,4),(260,4),(264,4)) and 0<=v<2**(8*n))
 for v in row[i+1:i+4]:require(0<=int(v)<2**64)
 for v in row[i+4:i+6]:require(0<=int(v)<2**32)
 require(row[i+6] in ('0','1'))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_team_observer_weight import TeamObserverWeightOracle
  oracle=TeamObserverWeightOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Team observer weight sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
