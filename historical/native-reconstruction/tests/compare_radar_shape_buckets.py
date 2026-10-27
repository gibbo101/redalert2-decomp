#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Radar shape bucket initialization with explicit original-answer reuse."""
import argparse,json,platform,subprocess,sys,time,itertools
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_radar_shape_buckets import verify,dimensions
NATIVE=('src/render/RadarShapeBuckets.hpp','src/render/RadarProjection.hpp','src/render/SurfacePixel.hpp','src/render/SurfaceRefresh.hpp','src/render/SurfaceFill.hpp','src/sim/OriginalMath.hpp','tests/radar_shape_buckets_vectors.cpp')
ORIGINAL=('tests/original_radar_shape_buckets.py','tools/verify_radar_shape_buckets.py','tests/compare_radar_shape_buckets.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_radar_shape_buckets.py')
FLAGS=dict(complete_shape_initializer=True,actual_vector_clear_and_null_external_resize=True,actual_FTOL_53_bit_toward_zero=True,heap_services_and_initial_records_supplied=True,dimension_probes_explicit_and_private=True,production_or_SDL_adoption=False)
TABLE_INPUT=None
def require(v):
 if not v:raise ValueError('Device pixel input/evidence differs')
def command(**kw):
 d=dict(mode=0,bits=1056964608,count=3,capacity=4,growth=10,owned=1,valid=1,present=1,failed=0,repeats=1,requested=12)
 dims=kw.pop('dims',TABLE_INPUT if TABLE_INPUT is not None else [1]*44)
 require(not set(kw)-set(d) and len(dims)==44);d.update(kw);return 'B '+' '.join(map(str,[*d.values(),*dims]))
def parse(cmd):
 t=cmd.split();require(len(t)==56 and t[0]=='B');f=list(map(int,t[1:]))
 require(f[0] in (0,1,2) and 0<=f[1]<2**32 and -2**31<=f[2]<2**31 and 0<=f[3]<=32 and -2**31<=f[4]<2**31 and all(0<=v<=255 for v in f[5:7]) and f[7] in (0,1) and f[8] in (0,1) and f[9] in (1,2) and -2**31<=f[10]<2**31 and all(-2**31<=v<2**31 for v in f[11:]));return f
def scenarios():
 for bits,owned,present,failed in itertools.product((0,1,1048576000,1056964608,1057132380,1065353216,1069547520,1073741824,3212836864,2139095040,2143289344),(0,2),(0,1),(0,1)):
  yield 'stock_dimensions_scale_raw_ownership_and_allocation_failure',command(bits=bits,owned=owned,present=present,failed=failed)
 for growth in (-1,0,1,7):
  yield 'growth_gate_and_repeated_initialization',command(growth=growth,repeats=2)
 for w,h in ((1,1),(0,0),(1,3),(4,1),(-3,2),(3,4)):
  yield 'authored_dimension_special_one_and_minimum_two',command(dims=[w]*22+[h]*22)
 for capacity,count,owned,present,failed,requested in itertools.product((0,4),(-1,1,8),(0,255),(0,1),(0,1),(0,2,6)):
  yield 'actual_resize_capacity_tails_clamp_and_failure',command(mode=1,capacity=capacity,count=count,owned=owned,present=present,failed=failed,requested=requested)
 for owned,present,valid in itertools.product((0,1,255),(0,1),(0,1,255)):
  yield 'actual_clear_external_and_owned_backing',command(mode=2,owned=owned,present=present,valid=valid)
def validate_row(cmd,row):
 parse(cmd);require(isinstance(row,list) and row.count('V')==1 and row.count('H')==1);i=0
 while i<len(row):
  tag=row[i]
  if tag=='H':require(i>=111 and row[i-111]=='V' and len(row)-i>=23);list(map(int,row[i+1:]));return
  n=dict(F=5,P=5,A=4,D=3,I=2,R=2,V=111).get(tag);require(n is not None and i+n<=len(row));list(map(int,row[i+1:i+n]));i+=n
 raise ValueError('Missing complete shape backing digests')
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):validate_row(cmd,row)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_radar_shape_buckets.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/radar-shape-buckets-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();global TABLE_INPUT;TABLE_INPUT=dimensions(a.exe.read_bytes());start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_radar_shape_buckets import RadarShapeBucketsOracle
  oracle=RadarShapeBucketsOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  for cmd,row in zip(commands,expected):validate_row(cmd,row)
  roots=sum(parse(c)[9] for c in commands)
  require(oracle.audit_calls==roots and all(oracle.counts[hex(a)]>0 for a in (0x632700,0x5b16e0,0x5b1b00,0x77f110)) and oracle.counts['allocations']>0 and oracle.counts['releases']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Radar shape bucket sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
