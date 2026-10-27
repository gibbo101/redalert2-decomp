#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare ordinary stock-E1 Cell visibility change with portable C++."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_cell_visibility_change import verify
NATIVE=('src/sim/CellVisibilityChange.hpp','src/sim/CellVisibilityChange.cpp','tests/cell_visibility_change_vectors.cpp')
ORIGINAL=('tests/original_cell_visibility_change.py','tools/verify_cell_visibility_change.py','tools/verify_terrain_visibility.py','tests/compare_cell_visibility_change.py')
FLAGS=dict(complete_wrapper_62FCA0_and_parent_499FC0=True,actual_map_lookup_counter_decrement_47C840_and_increment_47C8A0=True,low_byte_final_argument_selection=True,visibility_mask_redraw_discovery_and_refresh_children_supplied=True,production_visibility_schedule=False)
KEYS=('x','y','present','primary','secondary','flags12c','counter','maximum','flags140','primaryValue','secondaryValue','house','refreshRules','finalArgument')
def require(v):
 if not v:raise ValueError('Cell visibility change evidence/input differs')
def command(v):return 'C '+' '.join(str(v[k]) for k in KEYS)
def parse(cmd):
 p=cmd.split();require(len(p)==15 and p[0]=='C');v=dict(zip(KEYS,map(int,p[1:])));require(-32768<=v['x']<=32767 and -32768<=v['y']<=32767 and v['present'] in (0,1) and all(0<=v[k]<256 for k in ('primary','secondary','primaryValue','secondaryValue')) and all(0<=v[k]<2**32 for k in ('flags12c','flags140','refreshRules','finalArgument')) and -2**31<=v['counter']<2**31 and -2**31<=v['maximum']<2**31 and -2**31<=v['house']<2**31);return v
def scenarios():
 rng=random.Random(0x499fc0)
 counters=(1,0,-1,2,17,-2147483648,2147483647)
 for case in range(192):
  x=13+(case%9);y=17+(case%7);primary=(case*17)&255;secondary=(case*29)&255
  v=dict(x=x,y=y,present=0 if case%11==0 else 1,primary=primary,secondary=secondary,flags12c=(0xa5a50000|((case*5)&255)),counter=counters[case%len(counters)],maximum=(case%9)-4,flags140=(0x5a5a0000|((case*13)&255)),primaryValue=primary if case%4==0 else ((case*31)&255),secondaryValue=secondary if case%5==0 else ((case*43)&255),house=-200+case,refreshRules=0x1000 if case%3==0 else 0,finalArgument=0 if case<96 else (1,0x100,0x101,0xffffff00,0xffffffff)[case%5])
  if case%13==0:v['primaryValue']=255
  if case%17==0:v['secondaryValue']=255
  if case>=90:
   v['flags12c']|=8;v['flags140']|=2;v['primaryValue']=v['primary'];v['secondaryValue']=v['secondary']
  yield 'both_counter_branches_flags_visibility_bytes_discovery_and_refresh',command(v)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_visibility_change.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current,a):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(isinstance(row,list) and row.count('Z')==1)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/cell-visibility-change-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current,a);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_visibility_change import CellVisibilityChangeOracle
  oracle=CellVisibilityChangeOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.counts['0x62fca0']==len(commands) and oracle.counts['0x499fc0']==len(commands) and oracle.counts['0x47c840']>0 and oracle.counts['0x47c8a0']>0 and oracle.counts['0x47c840']+oracle.counts['0x47c8a0']==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-10):j+25],want[max(0,j-10):j+25]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell visibility change sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
