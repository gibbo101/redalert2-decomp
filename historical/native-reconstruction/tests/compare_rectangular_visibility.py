# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Rectangular visibility caller: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_rectangular_visibility import verify
ORIGINAL=('tests/compare_rectangular_visibility.py','tests/original_rectangular_visibility.py','tools/verify_rectangular_visibility.py')
NATIVE=('src/render/RectangularVisibility.hpp','src/render/TacticalViewport.hpp','src/render/TacticalViewportMatrix.hpp','src/render/VoxelRaster.cpp','src/render/VoxelRaster.hpp','src/render/Composition.cpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/rectangular_visibility_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_rectangular_visibility=True,actual_affine_FTOL_projection_and_intersections=True,map_and_draw_services_supplied=True,animation_tail_always_requested=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Rectangular visibility evidence/domain differs')
def bits(v):return struct.unpack('<I',struct.pack('<f',v))[0]
def command(mode=0,present=1,permission=1,anchor=(3,3),rect=(0,0,120,80),origin=(0,0),viewport=(0,0,320,200),matrix=(1,0,0,0,0,1,0,0,0,0,1,0)):
 return ' '.join(map(str,(mode,present,permission,*anchor,*rect,*origin,*viewport,*map(bits,matrix))))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==27 and all(-2**31<=n<2**31 for n in v[:15]) and 0<=v[0]<=7 and v[1] in (0,1) and all(-32768<=n<=32767 for n in v[3:5]) and -300<=v[7]<=180 and -300<=v[8]<=80 and all(0<=n<2**32 and n&0x7f800000!=0x7f800000 for n in v[15:]));return v
def scenarios():
 for w in (-300,-240,-239,-1,0,1,59,60,61,180):
  for h in (-300,-255,-254,-1,0,1,14,15,30,75):
   for permission in (0,1,256,257):
    for present in (0,1):yield 'signed_loop_extents_low_byte_permission_and_unconditional_tail',command(rect=(0,0,w,h),permission=permission,present=present)
 for mode in range(1,8):
  for origin in ((0,0),(17,-23)):
   for viewport in ((0,0,320,200),(9,11,180,140)):yield 'late_origins_viewport_clip_and_cached_extents',command(mode=mode,origin=origin,viewport=viewport)
 for x in (-32768,-32767,-1,0,1,3,32766,32767):
  for y in (-32768,-1,0,3,32767):yield 'wrapped_word_row_and_column_steps_negative_center',command(anchor=(x,y))
 matrices=((1,0,0,0,0,1,0,0,0,0,1,0),(256/60,256/30,0,0,-256/60,256/30,0,0,0,0,1,0),(1,-1,0,255.99998474121094,-1,1,0,-256.0000305175781,0,0,0,0),(2**32,2**-30,0,-2**63,2**-30,2**32,0,2**63,-1,1,0,123.5))
 edges=(-2147483648,-16777219,-65537,-257,-1,0,1,257,16777219,2147483647)
 for matrix in matrices:
  for i,x in enumerate(edges):yield 'wrapped_inverse_inputs_float32_FTOL_low32_and_clamp',command(origin=(x,edges[(i+3)%10]),matrix=matrix)
 rng=random.Random(0x6a7820)
 for _ in range(160):
  edge=lambda:rng.choice(edges)
  yield 'wrapped_clips_nonzero_viewport_and_aliased_services',command(mode=rng.randrange(8),present=rng.randrange(2),permission=rng.choice((0,128,255,-1,256)),rect=(edge(),edge(),rng.choice((-300,-1,0,60,180)),rng.choice((-300,-1,0,15,75))),origin=(edge(),edge()),viewport=tuple(edge() for i in range(4)),anchor=(rng.choice((-32768,-1,0,3,32767)),rng.choice((-32768,-1,0,3,32767))))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_rectangular_visibility.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%5==0 and len(row)==i+15)
 for j in range(0,i,5):
  require(1<=int(row[j])<=9)
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_rectangular_visibility import RectangularVisibilityOracle
  oracle=RectangularVisibilityOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x6a7820','0x591380','0x77f110','0x6a27a0','0x41fdf0','coordinate','permission','lookup','draw','animation')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Rectangular visibility sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
