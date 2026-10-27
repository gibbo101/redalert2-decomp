# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building image getters predicate: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_image import verify
ORIGINAL=('tests/compare_building_image.py','tests/original_building_image.py','tools/verify_building_image.py')
NATIVE=('src/render/BuildingImage.hpp','src/render/BuildingImage.cpp','src/render/BuildingTypeBounds.hpp','src/assets/OverlayImage.hpp','src/sim/OriginalMath.hpp','tests/building_image_vectors.cpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_primary_getter=True,complete_secondary_getter=True,actual_theater_transform=True,actual_generic_transform=True,actual_ftol=True,file_crt_lifetime_services_supplied=True,type_startup_supplied=True)
def require(v):
 if not v:raise ValueError('Building image getters evidence/domain differs')
def command(op=0,mode=0,theater=0,p=0,secondary=0,owned=128,dp=1,ds=1,b9c=255,flag=0,override=0,start=7,count=9,duration=11,first=1,second=2,frames=6,repeat=1,timing=.6,name='CTARMY04'):
 bits=int.from_bytes(struct.pack('<d',timing),'little')
 return ' '.join(map(str,(op,mode,theater,p,secondary,owned,dp,ds,b9c,flag,override,start,count,duration,first,second,frames,repeat,bits,name or '-')))
def parse(cmd):
 parts=cmd.split();require(len(parts)==20);v=list(map(int,parts[:19]));name=parts[19];name='' if name=='-' else name
 require(v[0] in (0,1) and 0<=v[1]<=5 and v[2] in (-1,0,1,2) and all(0<=v[i]<=3 for i in (3,4,14,15)) and all(0<=v[i]<=255 for i in (5,6,7,8,9)) and all(-2**31<=v[i]<2**31 for i in (10,11,12,13)) and -32768<=v[16]<=32767 and 1<=v[17]<=3 and 0<=v[18]<2**64)
 require(len(name)<=24 and all(c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_.' for c in name))
 require(v[0]!=0 or v[14]!=0 or len(name)<19)
 return [*v,name]
def scenarios():
 for op in (0,1):
  for resident in (0,1,3):
   for demand in (0,1,128,255):
    for name in ('','CTARMY04'):
     yield 'resident_demand_empty_raw_flags',command(op=op,p=resident if op==0 else 0,secondary=resident if op==1 else 0,dp=demand,ds=demand,name=name)
  for mode in range(6):
   for first,second in ((1,2),(0,2),(0,0)):
    for repeat in (1,2):yield 'load_fallback_cleanup_late_fields_and_repeat',command(op=op,mode=mode,first=first,second=second,repeat=repeat)
  for name in ('X','A','CTARMY04','GTANK','ntarmy01','gaarmy01','xxunknown','123456789012345678'):
   for theater in (-1,0,1,2):
    for first in (0,1):yield 'filename_transform_and_fallback',command(op=op,theater=theater,name=name,first=first)
 for name in ('1234567890123456789','123456789012345678901234'):
  yield 'primary_success_without_entering_unterminated_fallback',command(name=name)
 for frames in (-32768,-3,-1,0,1,2,3,6,32767):
  for flag,override in ((0,0),(1,-2),(128,-1),(255,0),(1,2147483647),(128,2147483646)):
   for timing in (0.,.6,-.6,1.,float('inf'),float('nan')):
    yield 'signed_count_override_wrap_and_ftol',command(op=1,frames=frames,flag=flag,override=override,timing=timing)
 for timing in (-0.,-1e30,1e30,-2**63/900,2**63/900,2147483648/900,4294967295/900,1/900,.6,1.0000000000000002):
  for frames in (2,3,6,32767):yield 'timing_precision_and_conversion_boundary',command(op=1,timing=timing,frames=frames)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_image.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1 and len(row)-row.index('F')==10)
 widths={'C':2,'K':2,'L':2,'D':2,'H':2,'T':0,'P':2,'S':3,'M':1,'R':1,'F':9}
 i=0
 while i<len(row):
  token=row[i];require(token in widths);n=widths[token];require(i+n<len(row))
  for j in range(1,n+1):
   if token!='C' or j!=2:int(row[i+j])
  i+=n+1
 require(i==len(row))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_image import BuildingImageOracle
  oracle=BuildingImageOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==sum(parse(cmd)[17] for cmd in commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x458ce0','0x45e790','0x5d7bd0','0x5d7c20','0x77f110','load','cleanup')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building image getters redraw sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
