# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete458510 file copy and first-frame conversion, with actual BUILDNGZ input."""
import argparse,json,platform,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from verify_building_depth_image import verify
from original_results import python_closure
ORIGINAL=('tests/compare_building_depth_image.py','tests/original_building_depth_image.py')
NATIVE=('src/assets/BuildingDepthImage.hpp','src/assets/BuildingDepthImage.cpp','tests/building_depth_image_vectors.cpp')
SOURCES=ORIGINAL+NATIVE+('tools/verify_building_depth_image.py',)
FLAGS=dict(complete_initializer458510=True,byte_wrapped_subtract=True,first_canvas_only=True,full_file_copy=True,ordered_global_and_buffer_stores=True,file_heap_cache_children_supplied=True,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Building depth initializer evidence/domain differs')
import struct,random
ASSET=None
def fixture(width,height,count,offset,seed,tail):
 # Valid backing even when crop dimensions deliberately differ from the canvas.
 rng=random.Random(seed);n=max(0,width)*max(0,height)
 blob=bytearray(struct.pack('<4H',0,width&65535,height&65535,count)+struct.pack('<4H4I',1,2,1,1,1,0,0,offset))
 blob+=bytes([0x5c])*max(0,offset-len(blob));blob+=bytes(rng.choice((0,1,64,65,66,127,128,255)) for _ in range(n));blob+=bytes([0xf1])*tail
 return bytes(blob)
def scenarios():
 for width,height in ((1,1),(3,2),(7,5),(0,3),(-2,2),(3,0),(4,-1)):
  for offset in (32,36):
   for tail in range(4):
    for old in (0,1):
     for mutation in (0,1,2):yield 'copy_tail_first_canvas_signed_bounds',[old,mutation,fixture(width,height,1,offset,71+tail,tail).hex()]
 for width,height in ((0,3),(-2,2),(3,0),(4,-1)):
  for count in (0,1):
   for old in (0,1):
    for mutation in (0,1,2):yield 'empty_or_null_first_frame_without_dereference',[old,mutation,fixture(width,height,count,0,77,0).hex()]
 for old in (0,1):
  for mutation in (0,1,2):yield 'actual_BUILDNGZ',[old,mutation,ASSET.hex()]
def parse(v):
 require(len(v)==3 and v[0] in (0,1) and v[1] in (0,1,2) and isinstance(v[2],str));blob=bytes.fromhex(v[2]);require(32<=len(blob)<0x40000);return v
def validate_row(row,cmd):
 require(row.count('F')==1);i=row.index('F');require(i%2==0 and len(row)==i+7)
 for j in range(0,i,2):require(1<=int(row[j])<=8);int(row[j+1])
 require(int(row[i+1]) in (2,3));require(all(len(v)==64 and set(v)<=set('0123456789abcdef') for v in row[i+2:i+6]));int(row[i+6])
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_depth_image.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},asset_source_sha256=hash_file(a.asset),environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);validate_row(row,cmd)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','asset'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();global ASSET;ASSET=a.asset.read_bytes();require(hash_file(a.asset)=='f91653da1f2c4b8e823a7db6ffb5e4c0fc003a9e74eef920adcad2feec739490');start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_depth_image import BuildingDepthImageOracle
  oracle=BuildingDepthImageOracle(a.exe);commands=[];labels=[];expected=[];payloads=[];now=time.monotonic()
  for label,cmd in scenarios():
   commands.append(cmd);labels.append(label);expected.append(oracle.run(bytes.fromhex(cmd[2]),cmd[0],cmd[1]))
   if label=='actual_BUILDNGZ':payloads.append(oracle.payload_hash)
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands));require(current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),complete_initializer_calls=len(commands),actual_payload_sha256=payloads,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(' '.join(map(str,c)) for c in commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout)
 require(current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building depth initializer sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
