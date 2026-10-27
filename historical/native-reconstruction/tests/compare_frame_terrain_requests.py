# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Frame terrain request caller: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_frame_terrain_requests import verify
ORIGINAL=('tests/compare_frame_terrain_requests.py','tests/original_frame_terrain_requests.py','tools/verify_frame_terrain_requests.py')
NATIVE=('src/render/FrameRegionPreparation.hpp','src/render/FrameTerrainRequests.hpp','src/render/StaticRedraw.hpp','src/render/SurfaceFill.hpp','src/render/Composition.hpp','src/render/Composition.cpp','tests/frame_terrain_requests_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_frame_terrain_requests=True,actual_center_projection_intersection=True,terrain_animation_rectangle_alpha_children_supplied=True,live_cell_and_forward_dirty_queues=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Frame terrain evidence/domain differs')
def command(mode=0,count=3,dirty=3,full=0,origin=(0,0),viewport=(0,0,320,200),first=(3,4,20,30),second=(7,8,10,11),clip=(0,0,320,200),order=(0,1,2),cells=((1,1),(2,1),(-1,2)),regions=((0,0,80,60,1),(31,29,40,50,0),(120,70,80,60,255)),present=1):
 return ' '.join(map(str,(mode,count,dirty,full,*origin,*viewport,*first,*second,*clip,*order,*(v for row in cells for v in row),*(v for row in regions for v in row),present)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==47 and all(-2**31<=n<2**31 for n in v) and 0<=v[0]<=12 and -1<=v[1]<=3 and -1<=v[2]<=3 and all(0<=n<3 for n in v[22:25]) and all(-32768<=n<=32767 for n in v[25:31]) and all(0<=v[i]<=255 for i in (35,40,45)) and v[46] in (0,1));return v
def scenarios():
 for count in (-1,0,1,3):
  for dirty in (-1,0,1,3):
   for full in (0,1,255,256,257,-2147483648,-1):
    for present in (0,1):yield 'cell_edges_and_forward_dirty_even_full',command(count=count,dirty=dirty,full=full,present=present)
 for mode in range(1,13):
  for count in (0,1,3):
   for dirty in (0,1,3):yield 'live_mutations_late_slots_backing_and_saved_screen_clip',command(mode=mode,count=count,dirty=dirty)
 for v in (-32768,-1,0,1,32767):
  for order in ((0,1,2),(0,0,1),(2,1,0)):yield 'center_signed16_and_aliases',command(cells=((v,1),(1,v),(v,v)),order=order)
 edges=(-2147483648,-2147483647,-65536,-1,0,1,320,2147483646,2147483647);rng=random.Random(0x6a3ef0)
 for _ in range(160):
  rect=lambda:tuple(rng.choice(edges) for _ in range(4))
  yield 'wrapped_regions_empty_alpha_and_flags',command(mode=rng.randrange(13),count=rng.randrange(4),dirty=rng.randrange(4),full=rng.choice(edges),origin=rect()[:2],viewport=rect(),first=rect(),second=rect(),clip=rect(),regions=tuple((*rect(),rng.choice((0,1,128,255))) for _ in range(3)),present=rng.randrange(2))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_frame_terrain_requests.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+62)
 for j in range(0,i,5):
  require(1<=int(row[j])<=15)
  for v in row[j+1:j+5]:int(v)
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_frame_terrain_requests import FrameTerrainOracle
  oracle=FrameTerrainOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x6a3ef0','0x475d60','0x6a27a0','0x41fdf0','height','terrain','animation','rectangle','alpha')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Frame terrain request sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
