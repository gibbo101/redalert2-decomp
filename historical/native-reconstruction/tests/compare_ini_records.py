# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete INI record construction, insertion and scalar cleanup."""
import itertools,math
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_ini_records import verify
ORIGINAL=('tests/compare_ini_records.py','tests/original_ini_records.py','tools/verify_ini_records.py')
NATIVE=('src/assets/IniEnumeration.hpp','src/assets/IniRecords.hpp','src/assets/IniRecords.cpp','tests/ini_record_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_node_list_entry_lifetime=True,heap_free_supplied=True,parser_index_and_startup_unjoined=True,production_scheduling=False)
NAMES=('op','graph','anchor','member','flags','args','mutation','repeats')
DEFAULT=(0,0,3,4,0,0,0,1)
def require(v):
 if not v:raise ValueError('INI record evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(str(kw.get(k,v)) for k,v in zip(NAMES,DEFAULT))
def parse(c):
 f=list(map(int,c.split()));require(len(f)==8)
 require(f[0] in range(7) and f[1] in range(8) and f[2] in range(1,7) and f[3] in range(1,7) and 0<=f[4]<=255 and f[5] in range(3) and f[6] in range(7) and f[7] in (1,2,3));return f
def scenarios():
 for op,graph,anchor in itertools.product((0,2),range(8),range(1,7)):
  yield 'node_construction_cleanup_alias_graph_and_repeated_calls',command(op=op,graph=graph,anchor=anchor,repeats=2)
 for graph,anchor,member in itertools.product(range(8),range(1,7),range(1,7)):
  yield 'complete_insert_detach_and_neighbor_alias_order',command(op=1,graph=graph,anchor=anchor,member=member,repeats=2)
 for op,graph in itertools.product((3,4,5),range(8)):
  yield 'complete_base_and_entry_list_construction_cleanup',command(op=op,graph=graph,repeats=2)
 for op,flags in itertools.product((2,5),(0,1,2,128,255)):
  yield 'scalar_cleanup_low_bit_free_and_repeated_call',command(op=op,graph=1,flags=flags,repeats=2)
 for args in range(3):yield 'entry_constructor_pointer_metadata_and_store_order',command(op=6,args=args,repeats=2)
 for op,mutation in itertools.product(range(7),range(1,7)):
  yield 'post_store_and_free_mutation_saved_and_late_fields',command(op=op,graph=1,anchor=3,member=4,flags=1,mutation=mutation,repeats=2)

def identities(a):
 paths=python_closure(ROOT/'tests/compare_ini_records.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k)==v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+50)
 for j in range(0,i,5):
  k,*values=map(int,row[j:j+5]);require(1<=k<=4 and all(0<=v<2**64 for v in values))
 for v in row[i+1:]:require(0<=int(v)<2**64)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_ini_records import IniRecordOracle
  oracle=IniRecordOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'INI record sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
