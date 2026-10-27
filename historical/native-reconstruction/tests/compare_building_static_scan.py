# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building static scan predicate: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_static_scan import verify
ORIGINAL=('tests/compare_building_static_scan.py','tests/original_building_static_scan.py','tools/verify_building_static_scan.py')
NATIVE=('src/render/BuildingStaticScan.hpp','src/render/BuildingStaticScan.cpp','src/render/FrameInvalidation.hpp','src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp','src/render/Composition.hpp','tests/building_static_scan_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_building_static_scan=True,actual_intersection=True,actual_rtti=True,bounds_and_drawing_supplied=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Building static scan evidence/domain differs')
def actor(kind=6,hidden=0,redraw=128,bounds=(-10,-15,30,40)):return (kind,hidden,redraw,*bounds)
def command(force=1,mode=0,count=3,bypass=0,offset=(0,0),dirty=(-100,-100,200,200),clip=(-100,-100,200,200),order=(0,1,2),rows=None):
 if rows is None:rows=[actor(),actor(bounds=(10,20,30,40)),actor(bounds=(500,500,10,10))]
 return ' '.join(map(str,(force,mode,count,bypass,*offset,*dirty,*clip,*order,*(v for r in rows for v in r))))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==38 and all(-2**31<=n<2**31 for n in v) and 0<=v[1]<=7 and -1<=v[2]<=3 and 0<=v[3]<=255 and all(0<=i<3 for i in v[14:17]))
 for i in range(3):require(v[17+i*7] in (6,15) and all(0<=v[j]<=255 for j in (18+i*7,19+i*7)))
 return v
def scenarios():
 for count in (-1,0,1,3):
  for kind in (6,15):
   for hidden in (0,1,128,255):
    for bypass in (0,1,128,255):
     yield 'forward_RTTI_hidden_raw_bypass_without_redraw_gate',command(count=count,bypass=bypass,rows=[actor(kind=kind,hidden=hidden,redraw=0)]*3)
 for mode in range(8):
  for order in ((0,1,2),(0,0,1),(0,2,1)):
   for force in (0,1,256,-2147483648,2147483647):
    yield 'live_count_backing_saved_offset_late_clip_and_clear_after_draw',command(mode=mode,order=order,force=force,rows=[actor()]*3,bypass=128)
 for rect in ((-10,-15,30,40),(20,-15,1,1),(-11,-15,1,1),(-10,25,1,1),(-10,-16,1,1),(0,0,0,0),(0,0,-30,-40),(2147483647,-2147483648,10,20)):
  for offset in ((0,0),(17,-23),(2147483647,-2147483648)):
   yield 'intersection_strict_edges_reversed_extents_wrapping',command(dirty=rect,offset=offset,rows=[actor()]*3)
 rng=random.Random(0x6a9f60)
 for _ in range(128):
  def rect():return tuple(rng.randint(-2**31,2**31-1) for _ in range(4))
  yield 'seeded_wrapped_rectangles_and_live_registry',command(force=rng.randint(-2**31,2**31-1),mode=rng.randrange(8),count=rng.randint(-1,3),bypass=rng.choice((0,1,128,255)),offset=rect()[:2],dirty=rect(),clip=rect(),order=tuple(rng.randrange(3) for _ in range(3)),rows=[actor(kind=rng.choice((6,15)),hidden=rng.choice((0,1,128,255)),redraw=rng.choice((0,1,128,255)),bounds=rect()) for _ in range(3)])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_static_scan.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+16)
 for j in range(0,i,4):
  require(1<=int(row[j])<=10)
  for v in row[j+1:j+4]:int(v)
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_static_scan import BuildingStaticScanOracle
  oracle=BuildingStaticScanOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x6a9f60','0x41fdf0','0x453c40','0x509800','bounds','draw')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building static scan redraw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
