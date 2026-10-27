# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building ordinary drawing predicate: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_ordinary import verify
ORIGINAL=('tests/compare_building_ordinary.py','tests/original_building_ordinary.py','tools/verify_building_ordinary.py')
NATIVE=('src/render/BuildingOrdinaryDraw.hpp','src/render/BuildingOrdinaryDraw.cpp','src/render/BuildingFrameRedraw.hpp','src/render/BuildingFrameRedraw.cpp','src/sim/RevealArea.cpp','src/sim/RevealArea.hpp','src/sim/OriginalMath.hpp','tests/building_ordinary_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_building_ordinary=True,actual_packed_cell=True,actual_planar_projection=True,actual_height_projection=True,actual_ftol=True,children_and_startup_supplied=True,pixels=False,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Building ordinary evidence/domain differs')
def command(mode=0,mission=0,kind=6,image=1,second=2,stage=0,hidden=0,adjust=17,offset=(3,-7),depth=5,count=6,replacements=(2,3,4,5,6),partner=0,flags=(0,0),timer=0,width=3,height=2,latewidth=3,global_value=123,image_count=6,frames=(0,1,2),z=208,cell_height=4,raw=(14784,22976),point=(30,40),clip=(0,0,200,200),fraction=.5,ratio=.5,threshold=.5,scale=.125):
 bits=lambda v:int.from_bytes(struct.pack('<d',v),'little')
 return ' '.join(map(str,(mode,mission,kind,image,second,stage,hidden,adjust,*offset,depth,count,*replacements,partner,*flags,timer,width,height,latewidth,global_value,image_count,*frames,z,cell_height,*raw,*point,*clip,bits(fraction),bits(ratio),bits(threshold),bits(scale))))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==43 and all(-2**31<=n<2**31 for n in v[:39]) and all(0<=n<2**64 for n in v[39:]))
 require(0<=v[0]<=9 and all(0<=v[i]<=7 for i in (3,4,12,13,14,15,16)) and v[17] in (0,1) and all(0<=v[i]<=255 for i in (6,18,19)) and all(-32768<=v[i]<=32767 for i in (10,25,30)) and 0<=v[20]<=15)
 scale=struct.unpack('<d',struct.pack('<Q',v[42]))[0];require(0<scale<=1)
 return v
def scenarios():
 for mission in (0,16,18,19,24):
  for stage in (0,1,2):
   for image in (0,1):
    for hidden in (0,128):
     for clipheight in (-1,0,200):yield 'initial_image_raw_gates_stage_and_main_clip',command(mission=mission,stage=stage,image=image,hidden=hidden,clip=(0,0,200,clipheight))
 for mode in range(10):
  for mission in (0,16,19,24):
   for stage in (0,1):
    for frame in (0,3):yield 'late_children_identity_mutation_and_all_layer_arguments',command(mode=mode,mission=mission,stage=stage,frames=(frame,2,4),partner=1,flags=(0,128),timer=3)
 for timer in range(16):
  for fraction in (-1.,0.,.1435,.5,1.,2.,float('nan')):
   for count in (-1,0,6):yield 'complete_timer_short_circuit_clamp_and_fraction',command(mission=24,timer=timer,fraction=fraction,count=count)
 for partner,flags in ((0,(0,0)),(1,(0,0)),(1,(128,0)),(1,(0,255))):
  for replacements in ((0,0,0,0,0),(2,3,4,5,6),(0,3,0,5,6)):
   for ratio in (.25,.5,.75,float('nan')):yield 'alternative_partner_priority_overlay_and_damage',command(mission=16,partner=partner,flags=flags,replacements=replacements,stage=1,ratio=ratio)
 for raw in ((-257,257),(2**31-1,-2**31),(0,0)):
  for width,height in ((-2**31,2**31-1),(8,2),(-1,0),(3,5)):
   for frames in ((-1,7,9),(3,7,9)):
    for image_count in (-3,6):yield 'signed_metadata_wrapped_planar_packed_cell_and_second_width',command(raw=raw,width=width,height=height,latewidth=width,frames=frames,image_count=image_count,offset=(2**31-1,-2**31),adjust=-2**31,z=2**31-1,depth=-32768,cell_height=-32768,global_value=-2**31)
 rng=random.Random(0x43a5e0)
 for _ in range(160):
  word=lambda:rng.randint(-2**31,2**31-1)
  yield 'seeded_branch_numeric_and_late_owner_combinations',command(mode=rng.randrange(10),mission=rng.choice((0,16,18,19,24)),kind=rng.choice((5,6)),stage=rng.choice((0,1,2)),hidden=rng.choice((0,0,255)),adjust=word(),offset=(word(),word()),count=word(),partner=rng.randrange(2),flags=(rng.choice((0,128)),rng.choice((0,255))),timer=rng.randrange(16),width=word(),height=word(),latewidth=rng.choice((3,8)),image_count=rng.choice((-3,0,6,32767)),frames=(word(),word(),word()),z=word(),raw=(word(),word()),ratio=rng.choice((.5,.75,float('nan'))),fraction=rng.choice((.1435,.5,-.2)),replacements=tuple(rng.randrange(8) for _ in range(5)))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_ordinary.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+17)
 for j in range(0,i,4):
  require(1<=int(row[j])<=8)
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_ordinary import BuildingOrdinaryOracle
  oracle=BuildingOrdinaryOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x43a5e0','0x41b320','0x6a2870','0x5d4800','0x6a2970','0x77f110','0x6d1510')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building ordinary drawing redraw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
