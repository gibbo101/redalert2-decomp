#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare ordinary stock-E1 Cell visibility change with portable C++."""
import argparse,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_scenario_special_flags import verify
NATIVE=('src/sim/ScenarioSpecialFlags.hpp','tests/scenario_special_flags_vectors.cpp')
ORIGINAL=('tests/compare_scenario_special_flags.py','tests/original_scenario_special_flags.py','tools/verify_scenario_special_flags.py')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_scenario_flags_initializer_and_reader=True,registry_and_GetBool_children_supplied=True,live_flags_and_session_reads=True,full_scenario_startup=False)
KEYS=('op','flags','open','query','type','data','session','override','mutation','mutationFlags','mutationSession','mutationOverride')
def require(v):
 if not v:raise ValueError('Invalid scenario flags evidence/input')
def command(**kw):
 v=dict(op=2,flags=0xffffffff,open=1,query=0,type=4,data=0,session=0,override=0,mutation=-1,mutationFlags=0,mutationSession=0,mutationOverride=0,answers=[-1]*13);require(not set(kw)-set(v));v.update(kw)
 return ' '.join(map(str,[*(v[k] for k in KEYS),*v['answers']]))
def parse(cmd):
 values=list(map(int,cmd.split()));require(len(values)==25);v=dict(zip(KEYS,values[:12]));v['answers']=values[12:]
 require(v['op'] in (0,1,2) and all(0<=v[k]<2**32 for k in ('flags','type','data','mutationFlags')) and all(-2**31<=v[k]<2**31 for k in ('open','query','session','mutationSession')) and all(0<=v[k]<256 for k in ('override','mutationOverride')) and -1<=v['mutation']<13 and all(-1<=x<2**32 for x in v['answers']));return v
def scenarios():
 for flags,opened,queried,kind,data in itertools.product((0,0xffffffff,0xa5a55a5a), (0,1,-1), (0,5), (0,4,7), (0,1,2,255,0x80000001)):
  yield 'complete_registry_paths_and_flags_masks',command(op=0,flags=flags,open=opened,query=queried,type=kind,data=data)
 for flags,session,override,answer in itertools.product((0,0xffffffff,0xa5a55a5a,0x1000), (0,1,-1), (0,1,255),(-1,0,1,2,255,256,257,0xffffffff)):
  yield 'complete_reader_lowbit_defaults_and_session_gate',command(op=1,flags=flags,session=session,override=override,answers=[answer]*13)
 for index,session,override in itertools.product(range(13),(0,1),(0,1)):
  yield 'live_word_and_late_session_mutation',command(op=1,flags=0xa5a55a5a,session=session,override=override,mutation=index,mutationFlags=0x5a5aa5a5,mutationSession=1-session,mutationOverride=1-override,answers=[0x101]*13)
 for flags in (0,0xffffffff,0x1000):
  yield 'joined_initializer_and_actual_training_flag_values',command(flags=flags,answers=[0,0,0,0,0,0,0,1,1,0,0,0,0])

def identities(a):
 paths=python_closure(ROOT/'tests/compare_scenario_special_flags.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current,a):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('Z')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/scenario-special-flags-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,a);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_scenario_special_flags import ScenarioSpecialFlagsOracle
  oracle=ScenarioSpecialFlagsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x68b320']>0 and oracle.counts['0x68b5a0']>0 and oracle.counts['supplied.GetBool']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-10):j+25],want[max(0,j-10):j+25]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Scenario special flags sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
