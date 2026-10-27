# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete viewport producer: original expectations separate from current native."""
import argparse,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_tactical_viewport import verify
ORIGINAL=('tests/compare_tactical_viewport.py','tests/original_tactical_viewport.py','tools/verify_tactical_viewport.py')
NATIVE=('src/render/TacticalViewport.hpp','src/sim/OriginalMath.hpp','tests/tactical_viewport_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_viewport_parent=True,actual_FTOL=True,inverse_matrix_probe=True,frame_consumer_recovered=False)
def require(v):
 if not v:raise ValueError('Viewport evidence/domain differs')
def bits(v):return struct.unpack('<I',struct.pack('<f',v))[0]
def command(x,y,w,h,ox=0,oy=0,oz=0,late=None):return ' '.join(map(str,(x,y,w,h,ox,oy,oz,*(late if late is not None else (w,h)))))
def parse(cmd):
 v=list(map(int,cmd.split()));require(len(v)==9 and all(-2**31<=v[i]<2**31 for i in (0,1,2,3,7,8)) and all(0<=v[i]<2**32 for i in (4,5,6)));return v
def scenarios():
 edges=(-2147483648,-16777219,-65537,-257,-1,0,1,257,16777219,2147483647)
 for i,x in enumerate(edges):
  for j,y in enumerate(edges):yield 'wrapped_origins_float32_inputs_signed_dimensions',command(x,y,edges[(i+3)%10],edges[(j+5)%10])
 outputs=[bits(v) for v in (-0.,0.,-0.9,0.9,-255.9,255.9,-256.9,256.9,-2147483648.,2147483648.,4294967296.,-4294967552.,-2**63,2**63)]+[0x7fc01234,0xffc01234,0x7f800000,0xff800000,1,0x80000001]
 for i,x in enumerate(outputs):
  for j,y in enumerate(outputs):yield 'FTOL_low32_signed_division_and_ignored_Z',command(3377,-1251,1025,721,x,y,outputs[(i+j)%len(outputs)])
 for w,h in ((0,0),(1,1),(-1,-1),(59,14),(60,15),(61,16),(1024,720),(-2147483648,2147483647)):
  yield 'late_dimensions_after_inverse',command(317,-923,1024,720,bits(12456.75),bits(-27891.75),bits(123.),(w,h))
 rng=random.Random(0x6a9170)
 for _ in range(128):
  yield 'seeded_full_widths_float_bits_and_late_dimensions',command(*(rng.randint(-2**31,2**31-1) for _ in range(4)),*(rng.randrange(2**32) for _ in range(3)),late=(rng.randint(-2**31,2**31-1),rng.randint(-2**31,2**31-1)))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_tactical_viewport.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(len(row)==38 and all(row[i]=='S' for i in (0,3,6,9,19,22,25,28)) and row[12]=='I' and row[16]=='L' and row[31]=='Z')
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_tactical_viewport import TacticalViewportOracle
  oracle=TacticalViewportOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Tactical viewport sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
