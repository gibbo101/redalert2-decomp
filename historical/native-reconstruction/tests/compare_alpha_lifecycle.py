# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete alpha lifecycle: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_alpha_lifecycle import verify
ORIGINAL=('tests/compare_alpha_lifecycle.py','tests/original_alpha_lifecycle.py','tools/verify_alpha_lifecycle.py')
NATIVE=('src/render/AlphaAnimationLifecycle.hpp','src/render/AlphaAnimation.hpp','src/sim/MissionTagExpiration.hpp','src/sim/MissionTag.hpp','tests/alpha_lifecycle_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_alpha_lifecycle_parents=True,actual_base_and_find=True,type_resize_free_supplied=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Alpha lifecycle evidence/domain differs')
def command(op=0,initialized=1,flags=255,match=1,primary=(2,6,1,3),secondary=(2,6,1,3),resize=1,mutation=0,width=60,height=30,deleting=1,layout=0,expired=0,null=0):
 return ' '.join(map(str,(op,initialized,flags,match,*primary,*secondary,resize,mutation,width,height,deleting,layout,expired,null)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==20 and 0<=v[0]<=5 and 0<=v[1]<=255 and 0<=v[2]<=255 and 0<=v[3]<=2 and all(0<=v[k]<=6 for k in (4,5,8,9)) and all(0<=v[k]<=255 for k in (6,10)) and all(-2**31<=v[k]<2**31 for k in (7,11)) and 0<=v[12]<2**32 and 0<=v[13]<=5 and all(-32768<=v[k]<=32767 for k in (14,15)) and 0<=v[16]<2**32 and 0<=v[17]<=3 and 0<=v[18]<=7 and v[19] in (0,1));return v
def scenarios():
 for op in (0,1,4):yield 'lazy_table_publication_and_all_ordered_entries',command(op=op,initialized=0,expired=5)
 policies=((0,0,0,3),(0,0,0,0),(2,2,0,3),(2,2,1,0),(2,2,128,-1),(2,2,128,3),(2,6,0,3),(0,6,1,3))
 for op in (0,1):
  for primary in policies:
   for secondary in policies:
    for result in (0,1,256,257):yield 'independent_physical_registry_growth_and_low_byte_result',command(op=op,primary=primary,secondary=secondary,resize=result)
 for flags in (0,7,128,255):
  for width,height in ((-32768,32767),(-1,0),(0,-1),(60,30),(32767,-32768)):
   yield 'base_flag_mask_and_signed_canvas_dimensions',command(flags=flags,width=width,height=height)
 for null in (0,1):
  for match in (0,1,2):
   for expired in (0,1,7):
    for removed in (0,1,256,257):yield 'expiration_pointer_identity_null_match_and_ignored_removed',command(op=2,null=null,match=match,expired=expired,deleting=removed)
 for pattern in range(4):
  for count in (0,1,3,4):
   for deleting in (0,1,2,128,256,257):
    for mutation in (0,3,5):yield 'first_only_removal_retained_tails_and_live_backing',command(op=3,layout=pattern,primary=(count,6,1,3),secondary=(count,6,1,3),deleting=deleting,mutation=mutation)
 for pattern in range(4):
  for count in (0,1,3,4):
   for mask in range(8):yield 'reverse_saved_extent_complete_deleting_children',command(op=4,layout=pattern,primary=(count,6,1,3),secondary=(count,6,1,3),expired=mask)
 for op in (0,1,3,4,5):
  for mutation in range(1,6):
   for initialized in (1,128):yield 'late_type_growth_find_deleting_and_count_store_effects',command(op=op,mutation=mutation,initialized=initialized,primary=(2,2,1,3),secondary=(2,2,1,3),layout=1,expired=7)
 for match in (0,1):
  for layout in (0,1,2,3):yield 'complete_constructor_expiration_cleanup_sequence',command(op=5,match=match,layout=layout)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_alpha_lifecycle.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+85)
 for j in range(0,i,5):
  require(1<=int(row[j])<=9)
  for v in row[j+1:j+5]:int(v)
 for v in row[i+1:-1]:int(v)
 for digest in row[-1:]:require(len(digest)==64 and all(c in "0123456789abcdef" for c in digest))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_alpha_lifecycle import AlphaLifecycleOracle
  oracle=AlphaLifecycleOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(3 if parse(c)[0]==5 else 1 for c in commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x41ebe0','0x41ed70','0x40ff10','0x40ff90','0x41f0f0','0x41f110','0x41f9c0','0x41fd20','0x410340','supplied-type','supplied-resize','supplied-free')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Alpha lifecycle sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
