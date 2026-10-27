# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete viewport producer: original expectations separate from current native."""
import argparse,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_tactical_viewport_matrix import verify
ORIGINAL=('tests/compare_tactical_viewport_matrix.py','tests/original_tactical_viewport_matrix.py','tools/verify_tactical_viewport_matrix.py')
NATIVE=('src/render/TacticalViewportMatrix.hpp','src/render/TacticalViewport.hpp','src/render/VoxelRaster.cpp','src/render/VoxelRaster.hpp','src/assets/Formats.hpp','src/sim/OriginalMath.hpp','tests/tactical_viewport_matrix_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_viewport_parent=True,actual_FTOL=True,actual_matrix_transform=True,matrix_construction_supplied=True,frame_consumer_recovered=False)
def require(v):
 if not v:raise ValueError('Viewport evidence/domain differs')
def bits(v):return struct.unpack('<I',struct.pack('<f',v))[0]
def command(x,y,w,h,matrix):return ' '.join(map(str,(x,y,w,h,*matrix)))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==16 and all(-2**31<=n<2**31 for n in v[:4]) and all(0<=n<2**32 and n&0x7f800000!=0x7f800000 for n in v[4:]));return v
def scenarios():
 edges=(-2147483648,-16777219,-65537,-257,-1,0,1,257,16777219,2147483647)
 matrices=[[1,0,0,0,0,1,0,0,0,0,1,0],
  [256/60,256/30,0,0,-256/60,256/30,0,0,0,0,1,0],
  [1,-1,0,255.99998474121094,-1,1,0,-256.0000305175781,0,0,0,0],
  [2**32,2**-30,0,-2**63,2**-30,2**32,0,2**63,-1,1,0,123.5]]
 for m in matrices:
  for i,x in enumerate(edges):
   for j,y in enumerate(edges):yield 'wrapped_origins_complete_affine_FTOL',command(x,y,edges[(i+3)%10],edges[(j+5)%10],list(map(bits,m)))
 for m in matrices:
  for w,h in ((0,0),(1,1),(-1,-1),(59,14),(60,15),(61,16),(1024,720),(-2147483648,2147483647)):
   yield 'signed_dimension_division_and_complete_matrix',command(317,-923,w,h,list(map(bits,m)))
 # Finite float32 coefficients cover signed zero, subnormals, cancellation,
 # float32 overflow under toward-zero and out-of-signed64 FTOL low32 behavior.
 rng=random.Random(0x591380)
 pool=[bits(v) for v in (-0.,0.,-1.,1.,-256.,256.,-2**63,2**63,2**-126,2**100)]+[1,0x80000001,0x7f7fffff,0xff7fffff]
 for _ in range(256):
  yield 'seeded_finite_matrix_bits',command(*(rng.randint(-2**31,2**31-1) for _ in range(4)),[rng.choice(pool) for _ in range(12)])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_tactical_viewport_matrix.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(len(row)==39 and all(row[i]=='S' for i in (0,3,6,9,20,23,26,29)) and row[12]=='I' and row[16]=='O' and row[32]=='Z')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_tactical_viewport_matrix import TacticalViewportMatrixOracle
  oracle=TacticalViewportMatrixOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(oracle.entries=={'0x6a9170':len(commands),'0x77f110':2*len(commands),'0x591380':len(commands)})
  meta=dict(FLAGS,original_entries=oracle.entries,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Joined Tactical viewport sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
