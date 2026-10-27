# SPDX-License-Identifier: GPL-3.0-or-later
"""Mission-control original/native comparison with explicit immutable original reuse."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_mission_control import verify
ORIGINAL=('tests/compare_mission_control.py','tests/original_mission_control.py','tools/verify_mission_control.py')
NATIVE=('src/sim/MissionControl.hpp','tests/mission_control_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_constructor=True,complete_ini_parent=True,complete_table_constructor=True,ini_results_supplied=True,rules_parent_slice_inspected_only=True,binary64_return_domain=True,production_scheduling_unjoined=True)
def require(v):
 if not v:raise ValueError('Mission control evidence/domain differs')
def command(root=1,index=12,present=1,flags=(0,0,1,0,1,1),rate=0x3f90624dd2f1a9fc,aa=0,initial=0x3fe400001234abcd,diag=0):
 return ' '.join(map(str,(root,index,present,*flags,rate,aa,initial,diag)))
def parse(cmd):
 f=list(map(int,cmd.split()));require(len(f)==13 and f[0] in range(4) and -1<=f[1]<30 and all(0<=v<2**32 for v in f[2:9]) and all(0<=v<2**64 for v in f[9:12]) and f[12] in range(6));return f
def scenarios():
 yield 'complete_table_constructor',command(root=2)
 for index in range(-1,30):
  yield 'constructor_untouched_padding',command(root=0,index=index)
  yield 'live_names_and_recruitable',command(root=3,index=index,flags=(239,0,0,0,0,0))
  if index>=0:yield 'wrapped_raw_address_alias',command(root=3,index=index,diag=1)
  for present in (0,1,256,0xffffffff):
   yield 'section_full_word_truth',command(index=index,present=present)
  for diag in range(1,6):yield 'late_read_and_store_diagnostic',command(index=index,diag=diag)
 values=(0,0x8000000000000000,1,0x8000000000000001,0x3f90624dd2f1a9fc,0x3ff0000000000000,0xbff0000000000000,0x7fefffffffffffff,0x7ff0000000000000,0xfff0000000000000,0x7ff8000000000000,0xfff8000012345678)
 rng=random.Random(0x4d435452)
 for i in range(512):
  yield 'raw_flag_bytes_double_bits_and_unordered_fallback',command(index=rng.randrange(-1,30),present=rng.choice((0,1,256,0xffffffff)),flags=tuple(rng.getrandbits(32) for _ in range(6)),rate=rng.choice(values),aa=rng.choice(values),initial=rng.choice(values),diag=i%6)
 for rate in values:
  for aa in values:yield 'double_cross_product',command(rate=rate,aa=aa)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_control.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);validate_row(row)
def validate_row(row):
 require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('F')==1)
 i=row.index('F');require(len(row)-i in (34,962));require(all(v=='F' or 0<=int(v)<2**32 for v in row));require(int(row[i+1])<=255 and all(int(v)<=255 for v in row[i+2:]))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();verify(a.exe.read_bytes());start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_control import MissionControlOracle
  oracle=MissionControlOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-8):at+8],want[max(0,at-8):at+8]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Mission control sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
