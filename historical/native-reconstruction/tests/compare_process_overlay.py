#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original/native candidate overlay and crushing-marker Process join."""
import argparse,copy,itertools,json,time
from pathlib import Path
import compare_process_preparation_scatter as parent
from compare_process_terminal_scatter import defaults
from original_process_overlay import ProcessOverlayOracle
from verify_process_overlay import verify
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
SOURCES=tuple(sorted(set((*parent.SOURCES,'src/sim/GroundDriveOverlay.hpp',
 'tests/compare_process_overlay.py','tests/original_process_overlay.py',
 'tools/verify_process_overlay.py','tests/test_process_overlay.py'))))
require=parent.require
def command(c,overlay,route=None):
 return 'X '+' '.join(map(str,overlay))+' '+parent.command(c,route=route,threshold=0)
def parse(cmd):
 parts=cmd.split();require(len(parts)>10 and parts[0]=='X');v=list(map(int,parts[1:10]))
 require(0<=v[0]<=9 and 0<=v[1]<=1 and all(0<=v[i]<=255 for i in (2,3,6,7)))
 require(all(-2147483648<=v[i]<=2147483647 for i in (4,5)) and 0<=v[8]<1<<32)
 c=parent.parse(' '.join(parts[10:]));c['candidate_overlay']=v;return c
def scenarios():
 def base():
  c=defaults();c.update(process_track=-1,head=[0,0,0],cell=9,position=[12672,12928,0],
   destination=[13184,13184,0],desired=16384,start=16384,queue=[-1]*24,speed=255)
  for row in c['cells']:row[7]=row[8]=-1
  c['secondary'][0]['position']=[12928,12928,0]
  return c
 for crush,wall,crusher,af4,index264 in itertools.product((0,1,255),(0,1),(0,1),(0,255),(0,1)):
  if wall and (not crusher or not crush):continue # Other weapon wall children remain outside this Process fixture.
  c=base();c['objects'][0][9]=crusher
  yield 'candidate_and_crossing_fields',command(c,[4,0,crush,wall,-1,index264,af4,173,0x3f400000])
 # Allied wall result4 is overridden only for Cell overlay index zero + Crusher.
 for flag,mode in itertools.product((1,255),range(4)):
  c=base();c['objects'][0][9]=255;c['fp_mode']=mode
  yield 'allied_wall_index_zero_override',command(c,[4,0,flag,1,0,0,255,29,0x7fc00001])
 # Independent type index, raw initial state and velocity retention.
 for index,initial,bits in itertools.product((0,1),(0,255),(0x80000000,0x7fc00001)):
  c=base();c['objects'][0][9]=1
  yield 'distinct_Cell_and_type_index_initial_bits',command(c,[4,index,255,0,-1,-1,255,initial,bits])
 # All headings with a distinct second direction: positive candidate must force straight.
 directions=((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))
 for first,(dx,dy) in enumerate(directions):
  c=base();c['objects'][0][9]=1;c.update(position=[12928-dx*256,12928-dy*256,0],desired=first<<13,start=first<<13)
  yield 'candidate_forces_first_direction',command(c,[4,0,255,0,-1,0,255,0,0x3f800000],route=[first,(first+1)%8]+[-1]*22)
def identities(a):
 result=parent.identities(a);result['sources']={p:hash_file(ROOT/p) for p in SOURCES};result['overlay_inspection']=verify(a.exe.read_bytes());return result
def check_coverage(meta):
 counts=meta['actual_counts']
 require(all(counts.get(k,0)>0 for k in ('actual.overlay_admission','0x4a3575','0x4a1a4e','store.0x59f','store.0x28c','0x4a3548')))
 require(meta['audited_complete_Process_calls']==meta['cases'])
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']==current)
 require(e['evidence']['overlay_destruction_excluded'] is True and e['evidence']['runtime_enabled'] is False)
 require(bool(e['commands']) and len(e['commands'])==len(e['labels'])==len(e['expected']))
 for cmd in e['commands']:parse(cmd)
 check_coverage(e['evidence'])
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for name in ('exe','native','legacy-native'):p.add_argument('--'+name,type=Path,required=True)
 for name,file in [('direction','direction-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('geometry','ramp-geometry-data.bin')]:p.add_argument('--'+name+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/file)
 for name in ('output','expectations','report'):p.add_argument('--'+name,type=Path)
 a=p.parse_args();a.pilot=False;a.pilot_limit=None;start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  folder=private_path(a.output,a.exe);require(not folder.exists() and not a.report)
  oracle=ProcessOverlayOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:answer=oracle.run(parse(cmd))
   except BaseException:print('Failed overlay Process',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(answer);labels.append(label)
  generation=time.monotonic()-now;report=folder/'report.json'
  meta=dict(actual_counts=dict(oracle.counts),cases=len(commands),audited_complete_Process_calls=sum(oracle.counts['Process_return.'+str(i)] for i in (0,1)),
   overlay_destruction_excluded=True,runtime_enabled=False,initial_records_routes_and_named_effects_supplied=True)
 check_coverage(meta)
 now=time.monotonic();count=parent.parent.compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',
  evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'complete overlay Process roots PASS')
if __name__=='__main__':main()
