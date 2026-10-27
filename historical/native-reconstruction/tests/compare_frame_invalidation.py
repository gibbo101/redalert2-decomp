# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Frame invalidation predicate: original expectations separate from current native."""
import argparse,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_frame_invalidation import verify
ORIGINAL=('tests/compare_frame_invalidation.py','tests/original_frame_invalidation.py','tools/verify_frame_invalidation.py')
NATIVE=('src/render/FrameInvalidation.hpp','src/render/FrameInvalidation.cpp','src/render/BuildingRenderBounds.hpp','src/render/BuildingRenderBounds.cpp','src/render/BuildingFrameRedraw.hpp','src/render/BuildingFrameRedraw.cpp','src/render/Redraw.hpp','src/render/Redraw.cpp','src/render/Composition.hpp','src/render/UnitVisibility.cpp','src/sim/BuildingCoordinates.hpp','src/sim/BuildingCoordinates.cpp','src/sim/OriginalMath.hpp','tests/frame_invalidation_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_invalidation=True,complete_bounds_cache=True,actual_projection=True,actual_dirty_region=True,type_bounds_supplied=True,frame_schedule_recovered=False)
def require(v):
 if not v:raise ValueError('Frame invalidation evidence/domain differs')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def signed(v):return (v+2**31)%2**32-2**31
def actor(raw=(128,128,0),redraw=1,kind=6,cache=(0,0,0,0,0,-3,-4,20,20),rect=(-10,-15,30,40)):
 return (kind,redraw,*raw,*cache,*rect)
def command(kind=2,mode=0,origin=(0,0),offset=(0,0),size=(1024,720),scale=.125,count=1,capacity=0,growth=2,owns=1,success=1,qcount=0,requested=(-100,-100,200,200),order=(0,1,2),rows=None,slots=None):
 if rows is None:rows=[actor(),actor(raw=(384,128,728)),actor(raw=(512,128,729))]
 if slots is None:slots=[(-5,-5,10,10,0),(500,500,20,20,1),(1000,1000,1,1,0)]
 return ' '.join(map(str,(kind,mode,*origin,*offset,*size,bits(scale),count,capacity,growth,owns,success,qcount,*requested,*order,*(v for r in rows for v in r),*(v for r in slots for v in r))))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==91 and v[0] in (0,1,2) and 0<=v[1]<=6 and all(-2**31<=n<2**31 for n in v[:8]) and -1<=v[9]<=3 and 0<=v[10]<=3 and 0<=v[14]<=v[10] and 0<=v[11]<=3 and v[12] in (0,1) and v[13] in (0,1) and all(0<=i<3 for i in v[19:22]))
 require(0<struct.unpack('<d',struct.pack('<Q',v[8]))[0]<=1)
 require(all(-2**31<=n<2**31 for n in v[15:]))
 for i in range(3):require(v[22+i*18] in (6,15) and 0<=v[23+i*18]<=255)
 for i in range(3):require(0<=v[80+i*5]<=255)
 return v
def scenarios():
 raw=[(0,0,0),(128,128,727),(128,128,728),(128,128,729),(-129,257,-728),(2147483647,-2147483648,2147483647),(-2147483648,2147483647,-2147483648),(14720,22912,208)]
 for kind in (0,1,2):
  for xyz in raw:
   for scale in (.125,.1435,.5,1.):
    for origin in ((0,0),(17,-23),(2147483647,-2147483648)):
     yield 'full_width_projection_height_and_cache_misses',command(kind=kind,origin=origin,scale=scale,rows=[actor(raw=xyz)]*3)
 # A8 subtracts128: these cache keys make an exact hit, even with no image child.
 for cache in ((0,0,0,0,0,-3,-4,20,20),(0,0,1,0,0,-3,-4,20,20),(0,0,0,1,0,-3,-4,20,20),(0,0,0,0,1,-3,-4,20,20)):
  yield 'cache_hit_and_individual_key_changes',command(kind=1,rows=[actor(cache=cache)]*3)
 for kind in (1,2):
  for mode in range(7):
   for order in ((0,1,2),(0,0,1),(0,2,1)):
    yield 'late_count_backing_origin_offset_position_and_raw_flags',command(kind=kind,mode=mode,count=3,order=order,rows=[actor(raw=(256,256,0)),actor(raw=(512,256,0)),actor(raw=(256,512,0))])
 for count in (-1,0,1,3):
  for kind,flag in ((15,255),(6,0),(6,128),(6,255)):
   yield 'RTTI_first_redraw_raw_byte',command(count=count,rows=[actor(raw=(256,256,0),kind=kind,redraw=flag)]*3)
 for capacity in (0,1,2,3):
  for qcount in range(capacity+1):
   for growth,owns,success in ((0,0,0),(2,0,1),(2,1,0),(2,1,1)):
    yield 'joined_queue_containment_growth_refusal_and_capacity_tails',command(capacity=capacity,qcount=qcount,growth=growth,owns=owns,success=success,rows=[actor(raw=(256,256,0))]*3,count=3)
 for x,y,w,h in ((-10,-15,30,40),(20,-15,1,1),(-11,-15,1,1),(-10,25,1,1),(-10,-16,1,1),(-10,-15,0,0),(0,0,-30,-40)):
  yield 'strict_overlap_edge_touching_and_unmodified_relative_registration',command(requested=(x,y,w,h),rows=[actor(raw=(128,128,0),cache=(1,0,0,0,0,0,0,0,0))]*3)
 rng=random.Random(0x6aa090)
 for _ in range(128):
  yield 'seeded_wrapped_rectangles_registry_and_queue',command(mode=rng.randrange(7),count=rng.randint(-1,3),origin=tuple(rng.randint(-2**31,2**31-1) for _ in range(2)),offset=tuple(rng.randint(-2**31,2**31-1) for _ in range(2)),requested=tuple(rng.randint(-2**31,2**31-1) for _ in range(4)),order=tuple(rng.randrange(3) for _ in range(3)),rows=[actor(raw=tuple(rng.randint(-2**31,2**31-1) for _ in range(3)),kind=rng.choice((6,15)),redraw=rng.choice((0,1,128,255)),rect=tuple(rng.randint(-2**31,2**31-1) for _ in range(4))) for _ in range(3)])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_frame_invalidation.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0)
 for j in range(0,i,4):
  require(int(row[j]) in set(range(1,17))|{20,21,22,23})
  for v in row[j+1:j+4]:int(v)
 tail=list(map(int,row[i+1:]));require(len(tail)>=32 and 0<=tail[30]<=tail[31]<=6 and len(tail)==32+tail[31]*5)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_frame_invalidation import FrameInvalidationOracle
  oracle=FrameInvalidationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands)+1 and current==identities(a) and runner==hash_file(a.native))
  require(oracle.total_types>0 and oracle.total_dirty>0 and oracle.total_project>0)
  meta=dict(FLAGS,actual_type_service_calls=oracle.total_types,actual_dirty_entries=oracle.total_dirty,actual_cache_entries=oracle.total_cache,actual_projection_entries=oracle.total_project,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Frame invalidation redraw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
