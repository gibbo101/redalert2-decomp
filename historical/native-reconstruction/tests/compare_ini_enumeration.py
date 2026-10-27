# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete observer definition enumeration with actual locale-zero comparison."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_ini_enumeration import verify
ORIGINAL=('tests/compare_ini_enumeration.py','tests/original_ini_enumeration.py','tools/verify_ini_enumeration.py')
NATIVE=('src/assets/IniEnumeration.hpp','src/assets/IniEnumeration.cpp','tests/ini_enumeration_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_count_key_index_cache=True,CRC_actual=True,CRT_qsort_supplied=True,text_and_index_list_construction_unjoined=True,production_scheduling=False)
NAMES=('name','profile','count','sorted','hot','list','index','mutation','repeats','operation')
DEFAULT=(b'AITriggerTypes',4,4,0,0,0,0,0,1,0)
def require(v):
 if not v:raise ValueError('INI enumeration evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));f=[kw.get(k,v) for k,v in zip(NAMES,DEFAULT)];f[0]='~' if f[0] is None else f[0].hex() or '-';return ' '.join(map(str,f))
def parse(c):
 f=c.split();require(len(f)==10);f[0]=None if f[0]=='~' else b'' if f[0]=='-' else bytes.fromhex(f[0]);f[1:]=map(int,f[1:])
 require(f[1] in range(7) and -1<=f[2]<=4 and 0<=f[3]<=255 and f[4] in range(5) and f[5] in range(6) and -2**31<=f[6]<2**31 and f[7] in range(7) and f[8] in (1,2) and f[9] in range(6))
 require(not(f[2]<0 and f[3]==0 and f[9]<4));require(f[0] is None or len(f[0])<1024)
 return f
def scenarios():
 for operation,profile,count,sort,hot in itertools.product(range(5),range(7),(0,1,4),(0,1),(0,1,4)):
  yield 'count_key_value_find_hot_live_index_profiles',command(operation=operation,profile=profile,count=count,sorted=sort,hot=hot,repeats=2)
 for name in (None,b'',b'a',b'ab',b'abc',b'abcd',b'abcde',b'alpha',b'ALPHA',b'AITriggerTypesEnable',b'a\0ignored',bytes(range(1,33)),bytes((128,255,129)),b'Z'*255):
  for op in (0,1,5):yield 'zero_state_CRC_NUL_padding_case_and_name_edges',command(name=name,operation=op,hot=4)
 for which,index in itertools.product(range(6),(-2147483648,-2,-1,0,1,2,3,4,2147483647)):
  yield 'linked_key_order_missing_links_null_names_signed_index',command(operation=1,list=which,index=index,hot=4,sorted=1)
 for mutation,op,profile in itertools.product(range(1,7),range(4),(0,2,4)):
  yield 'sort_and_store_change_live_backing_count_hot_and_section',command(operation=op,profile=profile,mutation=mutation,repeats=2)
 for op,hot,sort in itertools.product(range(5),(0,4),(1,128)):
  yield 'negative_count_and_raw_sorted_byte',command(operation=op,count=-1,hot=hot,sorted=sort)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_ini_enumeration.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+27)
 for j in range(0,i,4):
  k,a,b,c=map(int,row[j:j+4]);require(1<=k<=4 and 0<=a<2**64 and 0<=b<2**64 and 0<=c<2**64)
 for v in row[i+1:]:require(0<=int(v)<2**64)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_ini_enumeration import IniEnumerationOracle
  oracle=IniEnumerationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'INI enumeration sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
