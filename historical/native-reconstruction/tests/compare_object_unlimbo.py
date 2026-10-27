# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete non-radial Object Unlimbo: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_object_unlimbo import verify
ORIGINAL=('tests/compare_object_unlimbo.py','tests/original_object_unlimbo.py','tools/verify_object_unlimbo.py')
NATIVE=('src/sim/ObjectUnlimbo.hpp','src/render/ObjectAlphaPlacement.hpp','src/render/AlphaAnimationLifecycle.hpp','src/render/AlphaAnimation.hpp','src/sim/MissionTagExpiration.hpp','src/sim/MissionTag.hpp','tests/object_unlimbo_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_object_unlimbo_parent=True,radial_creation_excluded=True,children_supplied=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Object Unlimbo evidence/domain differs')
def command(**kw):
 names=('enabled','limbo','marked','redraw','active','loading','permission','mark','layer','hasType','logic','special','kind1','kind2','mode','aux','alpha','allocate','mutation','width','height','x','y','originX','originY')
 values=(1,1,0,128,1,0,0,1,2,1,0,0,6,6,0,0,1,1,0,60,30,101,-97,13,-17)
 require(not set(kw)-set(names));return ' '.join(str(kw.get(k,v)) for k,v in zip(names,values))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==25 and all(0<=v[k]<=255 for k in (0,1,2,3,4,10,11)) and all(-2**31<=v[k]<2**31 for k in (5,6,8,12,13,14,15,21,22,23,24)) and 0<=v[7]<2**32 and all(v[k] in (0,1) for k in (9,16,17)) and 0<=v[18]<=6 and all(-32768<=v[k]<=32767 for k in (19,20)));return v
def scenarios():
 for enabled in (0,1,128):
  for limbo in (0,1,128):
   for marked in (0,1,128):
    for permission in (0,1,-1,256):yield 'entry_and_permission_gates',command(enabled=enabled,limbo=limbo,marked=marked,permission=permission)
 for mark in (0,1,128,256,257):
  for active in (0,1,128):
   for hasType in (0,1):yield 'low_byte_Mark_restore_and_active_gate',command(mark=mark,active=active,hasType=hasType)
 for logic in (0,1,128):
  for special in (0,1,128):
   for kind1,kind2 in ((6,6),(36,36),(36,6)):
    for mode in (0,5,1,-1):
     for aux in (-2,-1,0):yield 'live_terrain_kind_session_logic_gates',command(logic=logic,special=special,kind1=kind1,kind2=kind2,mode=mode,aux=aux,alpha=0)
 for width,height in ((-32768,32767),(-7,11),(-1,-1),(0,0),(1,1),(60,30),(32767,-32768)):
  for x,y in ((101,-97),(-2147483648,2147483647),(2147483647,-2147483648)):
   for allocate in (0,1):
    for loading in (0,1,-1):yield 'signed_canvas_wrapped_centering_allocation_and_redraw',command(width=width,height=height,x=x,y=y,allocate=allocate,loading=loading)
 for mutation in range(1,7):
  for allocate in (0,1):
   for loading in (0,1):yield 'child_mutation_and_live_parent_fields',command(mutation=mutation,allocate=allocate,loading=loading)
 for layer in (-1,-2,0,2):
  for alpha in (0,1):yield 'layer_minus_one_only_and_alpha_gate',command(layer=layer,alpha=alpha)
 for originX,originY in ((-2147483648,2147483647),(2147483647,-2147483648)):
  for loading in (0,1):yield 'wrapped_origin_before_and_after_centering',command(originX=originX,originY=originY,loading=loading)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_object_unlimbo.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%6==0 and len(row)==i+10)
 for j in range(0,i,6):
  require(1<=int(row[j])<=18)
  for v in row[j+1:j+6]:int(v)
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_object_unlimbo import ObjectUnlimboOracle
  oracle=ObjectUnlimboOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.counts['parent']==len(commands))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Object Unlimbo sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
