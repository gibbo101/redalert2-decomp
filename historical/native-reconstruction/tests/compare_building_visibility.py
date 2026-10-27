# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building visibility predicate: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_visibility import verify
ORIGINAL=('tests/compare_building_visibility.py','tests/original_building_visibility.py','tools/verify_building_visibility.py')
NATIVE=('src/render/BuildingVisibility.hpp','src/render/BuildingVisibility.cpp','src/render/BuildingFrameRedraw.hpp','src/render/BuildingFrameRedraw.cpp','src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp','src/render/Composition.hpp','src/sim/BuildingCoordinates.hpp','src/sim/BuildingCoordinates.cpp','src/sim/OriginalMath.hpp','tests/building_visibility_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_building_visibility=True,actual_coordinates=True,actual_projection=True,actual_intersection=True,actual_ftol=True,bounds_and_drawing_supplied=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Building visibility evidence/domain differs')
def command(force=1,special=0,mode=0,alias=0,bypass=0,context=1,marked=1,redraw=128,flag=0,hidden=0,viewport=(0,0,200,200),clip=(10,20,100,100),bounds=(-10,-15,200,200),raw=(128,128,0),origin=(0,0),size=(1024,720),scale=.125):
 bits=int.from_bytes(struct.pack('<d',scale),'little')
 return ' '.join(map(str,(force,special,mode,alias,bypass,context,marked,redraw,flag,hidden,*viewport,*clip,*bounds,*raw,*origin,*size,bits)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==30 and all(-2**31<=n<2**31 for n in v[:29]) and 0<=v[2]<=5 and v[3] in (0,1) and v[5] in (0,1) and all(0<=v[i]<=255 for i in (4,6,7,8,9)))
 require(0<v[29]<2**63 and 0<struct.unpack('<d',struct.pack('<Q',v[29]))[0]<=1)
 return v
def scenarios():
 for bypass in (0,1,128,255):
  for context in (0,1):
   for force in (0,1,256,-256,-1):
    for marked,redraw,flag in ((0,0,0),(0,128,0),(1,0,0),(128,255,0),(255,1,128)):
     yield 'raw_gates_force_low_byte_order_and_bypass',command(bypass=bypass,context=context,force=force,marked=marked,redraw=redraw,flag=flag)
 for mode in range(6):
  for alias in (0,1):
   for special in (0,1,256,-256,-1):
    for hidden in (0,128):yield 'late_viewport_coordinate_hidden_and_child_writes',command(mode=mode,alias=alias,special=special,hidden=hidden)
 for raw in ((0,0,0),(128,128,727),(128,128,728),(128,128,729),(-129,257,-728),(2147483647,-2147483648,2147483647),(-2147483648,2147483647,-2147483648)):
  for origin in ((0,0),(17,-23),(2147483647,-2147483648)):
   for scale in (.125,.1435,.5,1.):yield 'actual_coordinate_projection_full_width_and_ignored_result',command(raw=raw,origin=origin,scale=scale,size=(-360,-180))
 for clip in ((-10,-15,30,40),(190,0,1,1),(0,185,1,1),(0,0,0,0),(0,0,-30,-40),(2147483647,-2147483648,10,20)):
  for alias in (0,1):yield 'clipping_strict_overlap_and_alias',command(clip=clip,alias=alias)
 rng=random.Random(0x43a200)
 for _ in range(128):
  def rect():return tuple(rng.randint(-2**31,2**31-1) for _ in range(4))
  yield 'seeded_wrapped_clipping_and_gate_fields',command(force=rng.randint(-2**31,2**31-1),special=rng.randint(-2**31,2**31-1),mode=rng.randrange(6),alias=rng.randrange(2),bypass=rng.choice((0,1,128,255)),context=rng.randrange(2),marked=rng.choice((0,1,255)),redraw=rng.choice((0,1,128,255)),flag=rng.choice((0,1,255)),hidden=rng.choice((0,1,255)),viewport=rect(),clip=rect(),bounds=rect(),raw=rect()[:3],origin=rect()[:2])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_visibility.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+18)
 for j in range(0,i,4):
  require(1<=int(row[j])<=11)
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_visibility import BuildingVisibilityOracle
  oracle=BuildingVisibilityOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x43a200','0x41fdf0','0x453c70','0x6a29d0','0x77f110','bounds','ordinary','special')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building visibility redraw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
