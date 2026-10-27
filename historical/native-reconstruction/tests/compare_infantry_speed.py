#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete Infantry speed with actual Foot/House/type/promotion roots."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
import copy
import struct,math
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_infantry_speed import verify
NATIVE=('src/sim/InfantrySpeed.cpp','tests/infantry_speed_vectors.cpp')
ORIGINAL=('tests/original_infantry_speed.py','tools/verify_infantry_speed.py','tests/compare_infantry_speed.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tools/verify_terrain_visibility.py')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^\"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_infantry_speed.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Infantry_and_Foot_speed=True,actual_type_House_country_and_promotion0=True,
 signed64_FTOL_low_dword_and_signed_division_wrap=True,late_live_fields_and_repeated_queries=True,
 initial_records_associations_supplied=True,complete_Process_join=False,production_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Infantry speed evidence/input differs')
def dbits(n):return struct.unpack('<Q',struct.pack('<d',n))[0]
def fbits(n):return struct.unpack('<I',struct.pack('<f',n))[0]
def command(base=32,country=1.,multiplier=1.,percentage=1.,veterancy=0.,rules=1.5,calls=1,flag=0,typeFlag=0,veteran=0,elite=0,mutation=0,trigger=0):
 return 'S '+' '.join(map(str,(base&0xffffffff,fbits(country),dbits(multiplier),dbits(percentage),dbits(veterancy),dbits(rules),calls,flag,typeFlag,veteran,elite,mutation,trigger)))
def parse(cmd):
 t=cmd.split();require(len(t)==14 and t[0]=='S');v=list(map(int,t[1:]))
 require(all(0<=n<=0xffffffffffffffff for n in v) and all(v[i]<=0xffffffff for i in (0,1)))
 require(1<=v[6]<=16 and all(v[i]<=255 for i in (7,8,9,10)) and v[11]<=31 and v[12]<=32)
 return v
def scenarios():
 for base,flags,factors in itertools.product((-2147483648,-2147483647,-100,-3,-1,0,1,2,3,31,32,33,255,2147483647),
  ((0,0),(1,0),(1,1),(255,128)),((1.,1.,1.),(.1,.75,.3333333333333333),(1.25,1.75,.375))):
  yield 'signed_base_conversion_stages_and_flag_division',command(base=base,flag=flags[0],typeFlag=flags[1],country=factors[0],multiplier=factors[1],percentage=factors[2])
 for veterancy,veteran,elite,rules in itertools.product((-1.,0.,math.nextafter(1.,0.),1.,math.nextafter(2.,0.),2.,float('inf'),float('nan')),(0,1),(0,128),(.5,1.5,2.25)):
  yield 'actual_promotion_thresholds_repeated_queries_and_bonus',command(base=31,veterancy=veterancy,veteran=veteran,elite=elite,rules=rules,calls=2)
 for base,multiplier,percentage in itertools.product((-1,1),(0.,-0.,5e-324,-5e-324,.9999999999999999,2147483648.,4294967296.,math.nextafter(2.**63,0.),-2.**63,math.nextafter(-2.**63,-float('inf')),2.**63,float('inf'),-float('inf'),float('nan')),(.5,1.,2.)):
  yield 'signed64_invalid_and_low_dword_conversion',command(base=base,multiplier=multiplier,percentage=percentage,flag=255,typeFlag=128)
 for country in (0.,-0.,1.401298464324817e-45,-1.,float('inf'),-float('inf'),float('nan')):
  yield 'country_float32_and_nonfinite',command(country=country)
 for percentage in (float('nan'),float('inf'),-float('inf'),-1.,0.,.5,1.,2.):
  yield 'late_percentage_without_clamping',command(base=31,percentage=percentage)
 for mask,trigger,veterancy in itertools.product((1,2,4,8,16,31),range(1,13),(0.,1.5,2.)):
  yield 'query_time_mutations_preserve_live_aliases',command(base=31,mutation=mask,trigger=trigger,veterancy=veterancy,veteran=1,elite=1,calls=2)

def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_original_calls']==sum(parse(cmd)[6] for cmd in e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  count=parse(cmd)[6];require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('R')==count)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_infantry_speed import InfantrySpeedOracle
  o=InfantrySpeedOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_speed(parse(cmd))
   except BaseException:print('Failed Infantry speed scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.counts))
  require(o.counts['0x508980']==o.audit_calls and o.counts['0x4c9b10']==o.audit_calls and all(o.counts.get(hex(k),0)>0 for k in (0x4f5a20,0x6d8e90,0x7133a0,0x713420,0x50af60,0x509800,0x77f110)))
  require(current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=origin))
  fingerprint=hash_file(source);write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True)
 require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint)
 write_report(a.exe,report,result);print(len(commands),'Infantry speed sequences PASS;',meta['audited_original_calls'],'audited original calls; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
