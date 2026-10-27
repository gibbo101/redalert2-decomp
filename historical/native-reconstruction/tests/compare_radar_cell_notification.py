# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete radar notification; guarded original-only reuse, current native."""
import argparse,itertools,json,platform,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_radar_cell_notification import verify
ORIGINAL=('tests/compare_radar_cell_notification.py','tests/original_radar_cell_notification.py','tools/verify_radar_cell_notification.py')
NATIVE=('src/render/RadarCellNotification.hpp','src/render/RadarMarkerPlacement.hpp','src/render/RadarProjection.hpp','src/render/SurfaceFill.hpp','tests/radar_cell_notification_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_radar_cell_notification=True,actual_intersection_and_ftol=True,surface_dimensions_and_dirty_child_probes_supplied=True,production_scheduling=False)
def require(v):
 if not v:raise ValueError('Invalid radar notification input/evidence')
def bits(v):return struct.unpack('<I',struct.pack('<f',v))[0]
def command(**kw):
 d=dict(present=1,x=3,y=1,mw=8,ox=0,oy=0,rw=16,rh=12,scale=bits(1.),width=16,height=12);require(not set(kw)-set(d));d.update(kw);return ' '.join(map(str,d.values()))
def parse(cmd):
 f=list(map(int,cmd.split()));require(len(f)==11 and f[0] in (0,1) and all(-32768<=n<=32767 for n in f[1:3]) and all(-2**31<=f[k]<2**31 for k in (3,4,5,6,7,9,10)) and 0<=f[8]<2**32);return f
def scenarios():
 for present,x,y in itertools.product((0,1),(-32768,-17,-1,0,1,3,15,32767),(-32768,-1,0,1,7,32767)):
  yield 'surface_gate_signed_words_and_clipping',command(present=present,x=x,y=y)
 for x,y,mw in itertools.product(range(-2,18),range(-1,5),(0,8,2147483647)):
  yield 'left_and_right_single_pixel_edges',command(x=x,y=y,mw=mw)
 for scale,width,height in itertools.product((0.,.125,.5,1.,1.25,2.,-1.,float('nan'),float('inf')),(0,1,16),(-1,0,12)):
  yield 'actual_ftol_float32_scales_and_dimensions',command(scale=bits(scale),width=width,height=height)
 for rw,rh,ox,oy in itertools.product((-2147483648,0,1,16,2147483647),(-1,0,12),(-2147483648,0,2147483647),(-2147483648,0,2147483647)):
  yield 'wrapped_geometry_and_nonpositive_clips',command(rw=rw,rh=rh,ox=ox,oy=oy)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and row and row[-1]=='Z' and row.count('Z')==1);i=0
 while i<len(row)-1:
  n=dict(W=2,H=2,Q=3).get(row[i]);require(n is not None and i+n<=len(row)-1);list(map(int,row[i+1:i+n]));i+=n
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_cell_notification.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-cell-notification-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_cell_notification import RadarCellNotificationOracle
  oracle=RadarCellNotificationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
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
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar Cell notification sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
