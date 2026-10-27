# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building frame predicate: original expectations separate from current native."""
import argparse,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_frame_redraw import verify
ORIGINAL=('tests/compare_building_frame_redraw.py','tests/original_building_frame_redraw.py','tools/verify_building_frame_redraw.py')
NATIVE=('src/render/BuildingFrameRedraw.hpp','src/render/BuildingFrameRedraw.cpp','src/sim/BuildingCoordinates.hpp','src/sim/BuildingCoordinates.cpp','src/sim/OriginalMath.hpp','tests/building_frame_redraw_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_building_frame_predicate=True,actual_building_A8=True,actual_FTOL=True,live_registry=True,frame_consumer_recovered=False)
def require(v):
 if not v:raise ValueError('Building frame evidence/domain differs')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def signed(v):return (v+2**31)%2**32-2**31
def command(origin=(0,0),rect=(0,0,1024,720),scale=.125,count=1,mode=0,order=(0,1,2),rows=None):
 if rows is None:rows=[(1,1,1,128,128,0),(1,1,1,128,0,0),(1,1,1,900000,900000,728)]
 return ' '.join(map(str,(*origin,*rect,bits(scale),count,mode,*order,*(v for row in rows for v in row))))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==30 and all(-2**31<=n<2**31 for n in v[:6]) and -1<=v[7]<=3 and 0<=v[8]<=6 and all(0<=n<3 for n in v[9:12]))
 scale=struct.unpack('<d',struct.pack('<Q',v[6]))[0];require(0<scale<=1)
 for i in range(3):require(all(0<=n<256 for n in v[12+i*6:15+i*6]) and all(-2**31<=n<2**31 for n in v[15+i*6:18+i*6]))
 return v
def div(a,b):return (1 if a>=0 else -1)*(abs(a)//b)
def projected(raw,scale):
 # Authored inputs only: place rectangles around arithmetic boundaries. The
 # expected decisions/traces always come from the actual original routines.
 x,y,z=raw;x=signed(x-128);y=signed(y-128)
 px=div(signed(div(signed(x*60),2)+div(signed(y*-60),2)),256)
 py=div(signed(div(signed(x*30),2)+div(signed(y*30),2)),256)
 return px,signed(py-int((z*scale+(z>=728))+.5))
def scenarios():
 raw=[(128,128,0),(128,128,727),(128,128,728),(128,128,729),(-128,256,-1),
  (2147483647,-2147483648,728),(-2147483648,2147483647,-2147483648),
  (71582788,-71582788,2147483647),(-65537,65537,-728),(14720,22912,208)]
 for scale in (.125,.5,1.):
  for xyz in raw:
   px,py=projected(xyz,scale)
   for dx in (-1,0,1):
    for dy in (-1,0,1):yield 'inclusive_projection_edges_wrapping_height_threshold',command(rect=(signed(px+dx),signed(py+dy),0,0),scale=scale,rows=[(1,1,1,*xyz)]*3)
   for ox,oy in ((2147483647,-2147483648),(-17,23)):
    yield 'wrapped_origin_and_reversed_rectangles',command(origin=(ox,oy),rect=(signed(px-ox),signed(py-oy),0,0),scale=scale,rows=[(255,128,2,*xyz)]*3)
 for i in range(8):
  row=((i>>2)&1,(i>>1)&1,i&1,128,128,0)
  for count in (-1,0,1,3):yield 'raw_gate_order_and_count',command(count=count,rows=[row]*3)
 for mode in range(7):
  for count in (1,2,3):
   for order in ((0,1,2),(0,2,1),(0,0,1)):
    yield 'live_count_backing_fields_and_saved_origin',command(rect=(15,-7,0,0),mode=mode,count=count,order=order)
 rng=random.Random(0x6aa180)
 for _ in range(128):
  rows=[(rng.choice((0,1,128,255)),rng.choice((0,1,128,255)),rng.choice((0,1,128,255)),*(rng.randint(-2**31,2**31-1) for _ in range(3))) for _ in range(3)]
  yield 'seeded_raw_flags_and_signed_full_width_fields',command(origin=tuple(rng.randint(-2**31,2**31-1) for _ in range(2)),rect=tuple(rng.randint(-2**31,2**31-1) for _ in range(4)),scale=rng.choice((.125,.1435,.5,1.)),count=rng.randint(-1,3),mode=rng.randrange(7),order=tuple(rng.randrange(3) for _ in range(3)),rows=rows)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_frame_redraw.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(len(row)>=4 and row[0]=='N' and row[-2]=='R' and row[-1] in ('0','1'))
 i=0
 while i<len(row)-2:
  key=row[i];require(key in ('N','B','G','C','M'));n=4 if key=='G' else 2
  require(i+n<=len(row)-2)
  for v in row[i+1:i+n]:int(v)
  i+=n
 require(i==len(row)-2)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_frame_redraw import BuildingFrameOracle
  oracle=BuildingFrameOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.total_coordinates>0)
  meta=dict(FLAGS,actual_coordinate_entries=oracle.total_coordinates,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building frame redraw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
