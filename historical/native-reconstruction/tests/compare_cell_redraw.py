# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete sight Cell redraw, explicit original reuse and current native comparison."""
import argparse,itertools,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_cell_redraw import verify
# Original dependencies exclude native-only integration and names.
ORIGINAL=('tests/compare_cell_redraw.py','tests/original_cell_redraw.py','tools/verify_cell_redraw.py')
NATIVE=('src/render/CellRedraw.hpp','tests/cell_redraw_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_cell_redraw=True,center_and_height_probes_supplied=True,production_scheduling=False)
def require(value):
 if not value:raise ValueError('Invalid Cell redraw evidence/domain')
def command(**kw):
 d=dict(loading=0,frame=17,last=-1,flags=8,redraw=1,x=128,y=128,z=208,height=0,ox=0,oy=0,vx=0,vy=0,vw=1024,vh=768,count=0,dirty=0);d.update(kw);return ' '.join(map(str,d.values()))
def parse(cmd):
 f=list(map(int,cmd.split()));require(len(f)==17 and all(-2**31<=n<2**31 for n in f));require(0<=f[3]<=2**31-1 and 0<=f[4]<=255 and 0<=f[16]<=255 and 0<=f[15]<=800);return f
def scenarios():
 for loading,frame,last,flags,redraw in itertools.product((0,255),(-1,0,17),(-1,0,17),(0,8,16,24),(0,255)):
  yield 'ordered_loading_frame_flags_redraw_gates',command(loading=loading,frame=frame,last=last,flags=flags,redraw=redraw)
 for x,y in itertools.product((-2147483648,-65537,-257,-1,0,1,255,65537,2147483647),repeat=2):
  yield 'wrapped_projection_signed_half_and_division',command(x=x,y=y,vx=-10000000,vw=20000000,vy=0,vh=20000000,oy=-10000000)
 for count,dirty,flags in itertools.product((0,1,797,798,799,800),(0,255),(0,8,24)):
  yield 'queue_threshold_capacity_tails_and_dirty_clearing',command(count=count,dirty=dirty,flags=flags)
 for x,y,z,height in itertools.product((-256,0,256),(-256,0,256),(-2147483648,208,2147483647),(-31,0,31)):
  yield 'center_Z_ignored_zero_height_argument_and_clipping',command(x=x,y=y,z=z,height=height,vw=0,vh=0)
 for ox,oy,vx,vy,vw,vh in [(30,30,0,0,0,0),(31,30,0,0,0,0),(-30,-15,0,0,0,0),(-31,-15,0,0,0,0),(0,-16,0,0,0,0),(0,0,2147483647,0,1,0),(0,0,0,2147483647,0,1)]:
  yield 'inclusive_screen_edges_and_wrapped_viewport',command(ox=ox,oy=oy,vx=vx,vy=vy,vw=vw,vh=vh)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and row.count('Z')==1);at=row.index('Z');require(len(row)-at==805);list(map(int,row[at+1:]));i=0
 while i<at:
  n=dict(F=2,C=4,H=2,Q=3,N=2,R=2,D=2).get(row[i]);require(n is not None and i+n<=at);list(map(int,row[i+1:i+n]));i+=n
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 require(r['expectations_sha256']==f and e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
from presentation_evidence import check_replay_destination
def identities(a):
 paths=python_closure(ROOT/'tests/compare_cell_redraw.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/cell-redraw-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_cell_redraw import CellRedrawOracle
  oracle=CellRedrawOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-8):j+20],want[max(0,j-8):j+20]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Cell redraw sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
