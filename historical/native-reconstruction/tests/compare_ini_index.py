# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete INI index construction, append, growth and lookup."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_ini_index import verify
ORIGINAL=('tests/compare_ini_index.py','tests/original_ini_index.py','tools/verify_ini_index.py')
NATIVE=('src/assets/IniIndexStorage.hpp','src/assets/IniIndexStorage.cpp','src/assets/IniEnumeration.hpp','src/assets/IniEnumeration.cpp','src/assets/IniRecords.hpp','src/assets/IniRecords.cpp','tests/ini_index_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_index_construct_append_growth_lookup=True,heap_and_CRT_sort_supplied=True,parser_merge_removal_and_startup_unjoined=True,production_scheduling=False)
NAMES=('kind','op','pattern','count','capacity','sorted','hot','query','increment','allocation','mutation','repeats')
DEFAULT=(0,1,0,0,0,0,0,42,4,0,0,1)
def require(v):
 if not v:raise ValueError('INI index evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==12)
 require(f[0] in (0,1) and f[1] in range(6) and f[2] in range(4) and all(-2**31<=f[i]<2**31 for i in (3,4,7,8)) and 0<=f[5]<=255 and f[6] in range(5) and f[9] in range(3) and f[10] in range(10) and f[11] in (1,2))
 require(not (f[1] in (0,1) and f[0]) and not(f[1]==2 and not f[0]))
 require(not(f[1]>=3 and f[3]<0 and f[5]==0));return f
def scenarios():
 for hot,sorted in itertools.product(range(5),(0,128)):
  yield 'zero_constructor_shared_fields_preserves_fallback',command(op=0,count=4,capacity=-1,hot=hot,sorted=sorted,repeats=2)
 for count,capacity,allocation in itertools.product((0,1,2,4,-2**31),(-2**31,-1,0,1,2,4,2**31-1),range(3)):
  yield 'append_capacity_doubling_failure_alias_and_wrapped_slot',command(count=count,capacity=capacity,allocation=allocation,hot=1,sorted=128,repeats=2)
 for count,capacity,increment,allocation in itertools.product((0,2),(-2**31,-1,0,1,4,2**31-1),(-2**31,-1,0,1,4,2**31-1),range(3)):
  yield 'section_reserve_raw_byte_wrap_live_fields_and_failure',command(kind=1,op=2,count=count,capacity=capacity,increment=increment,allocation=allocation,sorted=128,hot=1,repeats=2)
 for kind,op,pattern,sorted,hot,query in itertools.product(range(2),(3,4,5),range(4),(0,1,128),(0,4),(-2**31,-1,0,16,42,2**31-1)):
  yield 'key_section_signed_search_cold_hot_duplicate_and_missing',command(kind=kind,op=op,pattern=pattern,count=4,capacity=4,sorted=sorted,hot=hot,query=query,repeats=2)
 for kind,op,count,hot,query in itertools.product(range(2),(3,4,5),(-1,0,1),(0,1,2,3,4),(0,42)):
  yield 'zero_negative_count_and_detached_or_backing_hot',command(kind=kind,op=op,pattern=1,count=count,capacity=4,sorted=1,hot=hot,query=query,repeats=2)
 for kind,op in ((0,0),(0,1),(1,2),(0,3),(1,3),(0,4),(1,4),(0,5),(1,5)):
  for mutation in range(1,10):yield 'heap_sort_copy_store_mutation_saved_and_late_reads',command(kind=kind,op=op,pattern=2,count=2,capacity=2,mutation=mutation,repeats=2)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_ini_index.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+271)
 for j in range(0,i,5):
  k,*values=map(int,row[j:j+5]);require(1<=k<=7 and all(0<=v<2**64 for v in values))
 for v in row[i+1:]:require(0<=int(v)<2**64)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_ini_index import IniIndexOracle
  oracle=IniIndexOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'INI index sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
