# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete INI buffer lifetime and pipe attachment/cleanup."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_ini_input_lifetime import verify
ORIGINAL=('tests/compare_ini_input_lifetime.py','tests/original_ini_input_lifetime.py','tools/verify_ini_input_lifetime.py')
NATIVE=('src/assets/IniInputLifetime.hpp','src/assets/IniInputLifetime.cpp','src/assets/IniInput.hpp','src/assets/IniInput.cpp','tests/ini_input_lifetime_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_buffer_lifetime=True,complete_pipe_attach_and_cleanup=True,heap_supplied=True,downstream_dispatch_profiles='supplied-and-actual',parser_and_startup_unjoined=True,production_scheduling=False)
NAMES=('op','size','owned','data','allocationFailure','source','graph','mutation','repeats','dispatch')
DEFAULT=(0,16,0,1,0,2,0,0,1,0)
def require(v):
 if not v:raise ValueError('INI lifetime evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==10)
 require(f[0] in range(4) and -2**31<=f[1]<2**31 and 0<=f[2]<=255 and f[3] in range(3) and f[4] in range(2) and f[5] in range(5) and f[6] in range(8) and f[7] in range(6) and f[8] in (1,2,3) and f[9] in range(2));return f
def scenarios():
 for size,fail in itertools.product((-2**31,-1,0,1,16,4096,2**31-1),range(2)):
  yield 'signed_constructor_size_and_allocation_failure',command(size=size,allocationFailure=fail,repeats=2)
 for owned,data in itertools.product((0,1,128,255),range(3)):
  yield 'raw_ownership_null_free_and_repeated_cleanup',command(op=1,owned=owned,data=data,repeats=3)
 for op,source,graph,dispatch in itertools.product((2,3),range(5),range(8),range(2)):
  yield 'pipe_attachment_cleanup_alias_and_actual_virtual_composition',command(op=op,source=source,graph=graph,dispatch=dispatch,repeats=2)
 for op,mutation,dispatch in itertools.product(range(4),range(1,6),range(2)):
  yield 'heap_child_and_post_store_live_owner_mutations',command(op=op,owned=255,source=2,graph=3,mutation=mutation,dispatch=dispatch,repeats=2)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_ini_input_lifetime.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+20)
 for j in range(0,i,5):
  k,*values=map(int,row[j:j+5]);require(1<=k<=6 and all(0<=v<2**64 for v in values))
 for v in row[i+1:]:require(0<=int(v)<2**64)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_ini_input_lifetime import IniInputLifetimeOracle
  oracle=IniInputLifetimeOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'INI input lifetime sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
