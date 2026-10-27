#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete original Cell wall damage and actual recursive children."""
import argparse,itertools,json,subprocess,time
from pathlib import Path
import compare_map_wall_update as parent
from original_map_wall_damage import MapWallDamageOracle
from verify_map_wall_damage import verify
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
SOURCES=tuple(sorted(set((*parent.SOURCES,'src/sim/OriginalRandom.hpp','src/sim/OriginalRandom.cpp',
 'src/sim/OriginalRandomRange.hpp','tests/compare_map_wall_damage.py','tests/original_map_wall_damage.py',
 'tools/verify_map_wall_damage.py','tools/verify_random_range.py','tests/test_map_wall_damage.py'))))
def require(ok):
 if not ok:raise ValueError('Wall damage evidence differs')
def parse(command):
 parts=command.split();require(len(parts)>8 and parts[0]=='D');prefix=list(map(int,parts[1:7]))
 require(all(-2147483648<=v<=2147483647 for v in prefix[:4]) and 0<=prefix[4]<=255 and 0<=prefix[5]<1<<32)
 op,v=parent.parse(' '.join(parts[7:]));require(op=='U');return prefix,v
def command(damage=-1,levels=3,strength=200,force=0,disabled=0,rng=1,*,seed=0,index=203,data=0,alias=0,recalc=0,wall=1,all_neighbors=False,position=0x00480033):
 def packed(x,y):return (x&65535)|((y&65535)<<16)
 dirs=[packed(x,y) for x,y in ((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))]
 cells=[]
 for i in range(9):cells.extend([index if i==0 or all_neighbors else -1,data if i==0 else 0,(17*i)&255,5,77,0])
 values=[seed,0,position,123456,-654321,recalc,alias,wall,1,2,3,4,5,0,2,4,6,-1,*dirs,9,*cells]
 return 'D '+' '.join(map(str,[damage,levels,strength,force,disabled,rng]))+' U '+' '.join(map(str,values))
def scenarios():
 for index in (-1,0):yield 'absent_or_nonwall_no_queries',command(index=index,wall=0)
 for data in range(256):
  yield 'all_damage_bytes_and_aliasing',command(damage=1,force=255,data=data,alias=1,seed=data,levels=3,recalc=data%4)
 for levels,data,damage in itertools.product((-2147483648,-2,0,1,2,3,4,16,2147483647),(0,15,16,31,240,255),(-1,200)):
  yield 'signed_levels_byte_wrap_and_forced_removal',command(levels=levels,data=data,damage=damage,alias=2,seed=data&3)
 for strength,damage,disabled in itertools.product((-17,0,1,10,200,2147483647),(-18,-2,0,1,3,199),(0,255)):
  yield 'actual_inclusive_rng_threshold_and_consumption',command(strength=strength,damage=damage,disabled=disabled,rng=(strength^damage)&0xffffffff,data=1,seed=1)
 for index,alias,recalc in itertools.product((0,2,3,22,26,203),range(3),range(4)):
  yield 'recursive_neighbors_actual_wall_updates_and_zones',command(index=index,alias=alias,recalc=recalc,data=16,all_neighbors=True,seed=3)
 for position in (0xffffffff,0x7fff8000,0x80007fff,0):
  yield 'signed_word_coordinate_wrap',command(position=position,data=16,all_neighbors=True)
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES})
def check_coverage(meta):
 require(meta['cases']>0 and meta['audited_complete_roots']==meta['cases'])
 require(all(meta['counts'].get(k,0)>0 for k in ('0x475fe0','0x47604e','0x4761df','0x476223','0x4763b4','0x4763c3','random','draw','rejected')))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']==current)
 require(e['evidence']['Unit_caller_excluded'] is True and e['evidence']['runtime_enabled'] is False)
 require(bool(e['commands']) and len(e['commands'])==len(e['expected'])==len(e['labels']))
 for cmd in e['commands']:parse(cmd)
 check_coverage(e['evidence'])
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 for name in ('output','expectations','report'):p.add_argument('--'+name,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  folder=private_path(a.output,a.exe);require(not folder.exists() and not a.report);report=folder/'report.json'
  o=MapWallDamageOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run_damage(*parse(cmd))
   except BaseException:print('Failed damage scenario',label,cmd,flush=True);raise
   commands.append(cmd);labels.append(label);expected.append(row)
  generation=time.monotonic()-now;meta=dict(cases=len(commands),audited_complete_roots=o.audit_calls,counts=dict(o.counts),Unit_caller_excluded=True,runtime_enabled=False,
   supplied_bounds_lookup_zones_expiration_recalculation_and_initial_records=True)
 check_coverage(meta);now=time.monotonic();actual=parent.native(a.native,commands);comparison=time.monotonic()-now
 require(len(actual)==len(expected))
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:raise AssertionError((i,labels[i],commands[i],x,y))
 guards=subprocess.run([str(a.native),'--damage-guards'],capture_output=True,text=True)
 require(guards.returncode==0 and 'checks PASS' in guards.stdout)
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=len(commands),executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(len(commands),'complete Cell wall-damage roots PASS')
if __name__=='__main__':main()
