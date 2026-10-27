# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Infantry wrapper with actual ground/relative-height/packed-Cell children."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_infantry_transfer_wrapper import verify
ORIGINAL=('tests/compare_infantry_transfer_wrapper.py','tests/original_infantry_transfer_wrapper.py','tools/verify_infantry_transfer_wrapper.py')
NATIVE=('src/sim/ObjectGroundQueries.hpp','src/sim/ActorGroundState.hpp','src/sim/TechnoHouseTransfer.hpp','src/sim/TerrainOccupation.cpp','src/sim/TerrainOccupation.hpp','tests/infantry_transfer_wrapper_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_infantry_wrapper=True,actual_ground_query_relative_height_and_packed_cell=True,base_and_floor_children_supplied=True,live_diagnostic_mutations=True,production_transfer_unjoined=True)
NAMES=('root','marked','bridge','x','y','z','floor','level','bridgeHeight','base','mutation')
DEFAULT=(2,1,0,14784,22976,208,208,104,416,1,0)
def require(v):
 if not v:raise ValueError('Infantry transfer wrapper evidence/domain differs')
def command(**kw):
 require(not set(kw)-set(NAMES));return ' '.join(map(str,(kw.get(k,v) for k,v in zip(NAMES,DEFAULT))))
def parse(cmd):
 f=list(map(int,cmd.split()));require(len(f)==11 and f[0] in range(4) and all(0<=f[i]<=255 for i in (1,2)) and all(-2**31<=f[i]<2**31 for i in range(3,10)) and f[10] in range(9));return f
def signed(v):return (v+2**31)%2**32-2**31
def scenarios():
 for root,marked,bridge,level,neighbor in itertools.product((0,2),(0,1,128,255),(0,1,255),(-2147483648,-1073741825,-1073741824,-1,0,1,104,1073741823,1073741824,2147483647),(-1,0,1)):
  yield 'signed_wrapped_threshold_neighbors_and_raw_gates',command(root=root,marked=marked,bridge=bridge,level=level,z=signed(signed(2*level)+neighbor+91+(416 if bridge else 0)),floor=91)
 for z,floor,bridge,bh in itertools.product((-2147483648,-1,0,1,2147483647),(-2147483648,-1,0,2147483647),(0,1,255),(-2147483648,-1,0,416,2147483647)):
  yield 'complete_relative_height_wrapping_and_bridge',command(root=1,z=z,floor=floor,bridge=bridge,bridgeHeight=bh)
 coords=(-2147483648,-16777473,-16777216,-257,-256,-255,-1,0,1,255,256,257,16777216,2147483647)
 for x,y in itertools.product(coords,repeat=2):yield 'full_signed_division_before_word_truncation',command(root=3,x=x,y=y)
 for base,marked,z in itertools.product((0,256,1,257,-1),(0,1,128,255),(0,207,208,209)):
  yield 'wrapper_base_low_byte_and_ground_cell_store',command(base=base,marked=marked,z=z,floor=0)
 for root,mutation,bridge,marked in itertools.product((0,1,2),range(1,9),(0,255),(0,128)):
  yield 'late_height_bridge_threshold_and_point_diagnostic',command(root=root,mutation=mutation,bridge=bridge,marked=marked,z=208,floor=0)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_transfer_wrapper.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(isinstance(row,list) and all(isinstance(v,str) for v in row) and row.count('F')==1)
 i=row.index('F');require(len(row)==i+10 and all(0<=int(v)<2**32 for v in row[i+1:]) and all(int(row[i+j])<=255 for j in (6,7)))
 k=0
 while k<i:
  tag=row[k];n={'B':2,'H':1,'P':4,'D':2,'C':1,'W':2}.get(tag);require(n is not None and k+n<=i)
  values=list(map(int,row[k+1:k+n]));require(all(-2**31<=v<2**32 for v in values));k+=n
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();verify(a.exe.read_bytes());start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_transfer_wrapper import InfantryTransferWrapperOracle
  oracle=InfantryTransferWrapperOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls>=len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts.get(hex(a),0)>0 for a in (0x4ca7d0,0x4cce70,0x5d5410,0x5d4810,0x41b320)))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   at=next((j for j,(g,w) in enumerate(zip(got,want)) if g!=w),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],len(got),len(want),at,got[max(0,at-10):at+10],want[max(0,at-10):at+10]))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry transfer wrapper sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
