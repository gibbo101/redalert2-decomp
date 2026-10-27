# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building frame predicate: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_frame import verify
ORIGINAL=('tests/compare_building_frame.py','tests/original_building_frame.py','tools/verify_building_frame.py')
NATIVE=('src/render/BuildingFrame.hpp','src/render/BuildingFrame.cpp','src/render/BuildingImage.hpp','src/sim/MissionTypedTagExpiration.hpp','src/sim/OriginalMath.hpp','src/sim/UnitDiscovery.hpp','src/sim/UnitDiscovery.cpp','tests/building_frame_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_building_frame=True,actual_health_ratio=True,actual_mission=True,type84_and_startup_supplied=True,drawing=False,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Building frame evidence/domain differs')
def command(mode=0,flags=(0,0,0,0),stage=0,frame=7,frames=(31,37),field564=0,mission=0,queued=0,health=50,strength=100,count=6,sequence=(3,6),later=(11,13,17,19,23,29,31,37,41,43),threshold=.5,alternate=.25):
 bits=lambda v:int.from_bytes(struct.pack('<d',v),'little')
 return ' '.join(map(str,(mode,*flags,stage,frame,*frames,field564,mission,queued,health,strength,count,*sequence,*later,bits(threshold),bits(alternate))))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==29 and all(-2**31<=n<2**31 for n in v[:27]) and 0<=v[0]<=5 and all(0<=n<=255 for n in v[1:5]) and all(0<=n<2**64 for n in v[27:]))
 return v
def scenarios():
 for flags in ((0,0,0,0),(128,255,255,255),(0,128,255,255),(0,0,128,0),(0,0,0,255)):
  for stage in (0,1,2,-1):
   for health,strength in ((25,100),(50,100),(51,100),(0,0),(1,0),(-1,0),(100,-100)):
    for field in (-1,0,1):yield 'full_priority_and_damage_equal_unordered_gates',command(flags=flags,stage=stage,health=health,strength=strength,field564=field)
 for mode in range(6):
  for flags in ((0,0,0,0),(0,0,128,0),(0,0,0,128)):
   for stage in (0,1,2):
    for mission,queued in ((19,0),(-1,19),(0,19)):
     yield 'retained_frame_live_type_stage_and_rules_across_actual_children',command(mode=mode,flags=flags,stage=stage,mission=mission,queued=queued,health=50)
 for flags in ((0,0,0,0),(0,0,128,0)):
  for stage in (0,1,2):
   for frame in (-2**31,2**31-1,-1,0):
    for mission in (0,19):yield 'wrapped_reverse_and_signed_sequence_max',command(flags=flags,stage=stage,frame=frame,mission=mission,count=2**31-1,sequence=(2**31-1,2),later=(2**31-1,2,-2**31,-1,-100,-200,100,101,-1,2**31-1))
 rng=random.Random(0x43be20)
 for _ in range(128):
  word=lambda:rng.randint(-2**31,2**31-1)
  yield 'seeded_numeric_and_branch_combinations',command(mode=rng.randrange(6),flags=tuple(rng.choice((0,0,128,255)) for _ in range(4)),stage=rng.choice((0,1,2,-1)),frame=word(),frames=(word(),word()),health=word(),strength=word(),count=word(),sequence=(word(),word()),later=tuple(word() for _ in range(10)),mission=rng.choice((0,19,-1)),queued=19,threshold=rng.choice((.5,.25,float('nan'),float('inf'),-float('inf'))))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_frame.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%3==0 and len(row)==i+7)
 for j in range(0,i,3):
  require(0<=int(row[j])<=4)
  for v in row[j+1:j+3]:int(v)
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_frame import BuildingFrameOracle
  oracle=BuildingFrameOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x43be20','0x5d4540','0x594770','type84')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building frame redraw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
