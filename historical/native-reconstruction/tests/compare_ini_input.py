# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete INI line reader, buffered pipe and source forwarding."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_ini_input import verify
ORIGINAL=('tests/compare_ini_input.py','tests/original_ini_input.py','tools/verify_ini_input.py')
NATIVE=('src/assets/IniInput.hpp','src/assets/IniInput.cpp','tests/ini_input_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_line_reader=True,actual_buffered_pipe_source_forwarding=True,upstream_and_memcpy_supplied=True,parser_and_startup_unjoined=True,production_scheduling=False)
NAMES=('data','mode','capacity','bufferSize','chunk','cursor','available','eof','failure','mutation','reads')
DEFAULT=(b'alpha=one\r\nzeta=two\n',1,512,8,3,0,0,0,0,0,1)
def require(v):
 if not v:raise ValueError('INI input evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));f=[kw.get(k,v) for k,v in zip(NAMES,DEFAULT)];f[0]=f[0].hex() or '-';return ' '.join(map(str,f))
def parse(c):
 f=c.split();require(len(f)==11);f[0]=b'' if f[0]=='-' else bytes.fromhex(f[0]);f[1:]=map(int,f[1:])
 require(len(f[0])<=1024 and f[1] in range(4) and -2**31<=f[2]<2**31 and -2<=f[3]<=64 and 1<=f[4]<=64 and 0<=f[5]<64 and 0<=f[6]<=64 and f[5]+f[6]<=64 and -3<=f[7]<=255 and f[8] in range(4) and f[9] in range(7) and f[10] in (1,2,3))
 # Null EOF is tested only in a no-read original domain. Original null stores
 # and physical-copy overflows are refusals, never passing guest executions.
 require(f[7]!=-1 or f[1]<=1 and f[2]==0)
 return f
def scenarios():
 values=(b'',b'a',b'abc\n',b'a\r\nb\n',b'\r\r\n',b'a\0b\n',b'\x80\xff=\xfe\n',b'first\nsecond\nthird')
 for mode,data,capacity in itertools.product(range(4),values,(-1,0,1,2,5,512)):
  yield 'direct_line_composed_pipe_buffer_and_forward_roots',command(mode=mode,data=data,capacity=capacity,reads=3)
 for mode,size,chunk in itertools.product((1,2),(-2,0,1,2,8,64),(1,3,64)):
  yield 'logical_buffer_size_refill_chunk_and_long_line_consumption',command(mode=mode,bufferSize=size,chunk=chunk,capacity=5,reads=3)
 for mode,cursor,available in itertools.product((1,2),(0,2),(0,1,3)):
  yield 'preloaded_cursor_available_persist_across_calls',command(mode=mode,cursor=cursor,available=available,capacity=5,reads=3)
 for mode,failure in itertools.product(range(4),range(1,4)):
  yield 'raw_nonone_negative_and_zero_source_returns',command(mode=mode,failure=failure,capacity=5,reads=3)
 for mode,eof,data in itertools.product((0,1),(0,128,255,-2,-3),(b'ab\n',b'ab')):
  yield 'raw_EOF_byte_output_alias_and_LF_vs_EOF',command(mode=mode,eof=eof,data=data,reads=2)
 for mode in (0,1):yield 'zero_capacity_null_EOF_no_child',command(mode=mode,capacity=0,eof=-1)
 for mode,mutation in itertools.product(range(4),range(1,7)):
  yield 'source_and_ordered_store_change_pipe_fields',command(mode=mode,mutation=mutation,capacity=5,reads=3)
 for mode,n in itertools.product((0,1),(510,511,512,600)):
  yield 'original_512_byte_parser_line_limit_discards_remainder',command(mode=mode,data=b'X'*n+b'\nnext\n',capacity=512,reads=3)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_ini_input.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+658)
 for j in range(0,i,4):
  k,a,b,c=map(int,row[j:j+4]);require(1<=k<=6 and 0<=a<2**64 and 0<=b<2**64 and 0<=c<2**64)
 for v in row[i+1:]:require(0<=int(v)<2**64)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_ini_input import IniInputOracle
  oracle=IniInputOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'INI input sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
