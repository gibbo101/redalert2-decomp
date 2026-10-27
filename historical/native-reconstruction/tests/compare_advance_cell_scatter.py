#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Advance result6 block joined to actual zero-point Cell/Unit nearby children."""
import argparse,copy,json,re,subprocess,time
from pathlib import Path
import compare_cell_nearby_scatter as parent
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_advance_cell_scatter import verify
NATIVE=('tests/advance_cell_scatter_vectors.cpp',*parent.NATIVE[1:],'src/render/RampGeometry.cpp','src/assets/RampGeometryData.cpp','src/assets/RasterData.cpp')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  p=pending.pop()
  if p in seen:continue
  seen.add(p)
  for n in re.findall(r'^#include "([^"]+)"',(ROOT/p).read_text(),re.M):
   local=(ROOT/p).parent/n;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+n)
 return tuple(sorted(seen))
SOURCES=tuple(sorted(set((*parent.SOURCES,*source_closure(),'tests/advance_cell_scatter/CMakeLists.txt','tests/original_advance_cell_scatter.py','tests/compare_advance_cell_scatter.py','tools/verify_advance_cell_scatter.py','tools/verify_ramp_geometry.py','tools/verify_voxel_ramp_shadow.py','tests/test_advance_cell_scatter_evidence.py'))))
FLAGS=dict(actual_Advance_result6_block=True,complete_Advance=False,actual_Cell_Unit_nearby_destination_children=True,
 actual_distinct_stock_Drive_geometry=True,entry_stack_registers_and_initial_associations_supplied=True,
 Process_joined=False,production_owned_world_join=False,runtime_enabled=False)
def require(ok):
 if not ok:raise ValueError('Malformed or unsupported Advance Cell Scatter evidence/input')
def defaults():
 c=parent.defaults();c.update(candidate=[13184,12928,0],scratch=0xaabbccdd,head=[12928,12928,0]);return c
def command(**kw):
 c=defaults();c.update(kw)
 return 'B '+' '.join(map(str,[*c['candidate'],c['scratch']]))+' '+parent.command(**{k:v for k,v in c.items() if k in parent.defaults()})
def parse(cmd):
 t=cmd.split();require(len(t)>6 and t[0]=='B');v=list(map(int,t[1:5]));require(all(-2147483648<=n<=2147483647 for n in v[:3]) and 0<=v[3]<=0xffffffff)
 c=parent.parse(' '.join(t[5:]));require(all(a[:5]==[0,0,0,1,1] for a in c['actions']))
 # Cell identity is supplied for retained projection only; the original/native
 # final query must independently resolve this same actual head destination.
 x,y=c['head'][:2];index=((int(y/256)<<9)+int(x/256))&0xffffffff
 found=next((i for i,row in enumerate(c['cells'][:9]) if row[0]==index),9)
 require(c['cell']==found);c.update(candidate=v[:3],scratch=v[3]);return c
def identities(a):return dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in SOURCES},direction_data_sha256=hash_file(a.direction_data),render_data_sha256=hash_file(a.render_data),raster_data_sha256=hash_file(a.raster_data),geometry_data_sha256=hash_file(a.geometry_data))
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e.get('evidence',{}).get('identities')==current)
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v and r.get(k) is v)
 require(bool(e.get('commands')) and len(e['commands'])==len(e.get('labels',[]))==len(e.get('expected',[])))
 for cmd,row in zip(e['commands'],e['expected']):parse(cmd);require(row.count('state')==1 and row.count('actor')==4 and row.count('geometry')==row.count('scratch'))
def generate(a):
 from original_advance_cell_scatter import AdvanceCellScatterOracle
 o=AdvanceCellScatterOracle(a.exe);commands=[];expected=[];labels=[];groups={}
 def add(label,**kw):
  cmd=command(**kw)
  try:row=o.run(parse(cmd))
  except BaseException:print('Failed Advance Cell case',len(commands),label,flush=True);raise
  commands.append(cmd);expected.append(row);labels.append(label);groups[label]=groups.get(label,0)+1
 add('candidate_distinct_from_actual_Drive_head')
 for flags in (0,1,0x100,0x1000,0x1100,0xffffffff):
  for level in (-128,-1,0,127):
   for gap in (-3,-2,0,2,3):
    cells=defaults()['cells'];cells[5][5]=flags;cells[5][3]=level;cells[4][8]=1
    add('actual_flag_signed_level_height_and_list_selection',cells=cells,position=[12928,12928,(level+gap)*104])
 for mode in range(4):
  for scratch in (0,1,0xffffff00,0xaabbccdd):add('retained_upper_stack_bytes_and_host_FP',fp_mode=mode,scratch=scratch)
 for z in (-2147483648,-313,-312,-311,-209,-208,-207,-1,0,1,207,208,209,311,312,313,2147483647):
  cells=defaults()['cells'];cells[5][5]=0x100;cells[4][8]=1
  add('signed_division_toward_zero_at_height_threshold',cells=cells,position=[12928,12928,z],suspended=1)
 for candidate in ((-257,-65537,0),(-1,0,0),(2147483647,-2147483648,17)):
  cells=defaults()['cells'];cells[9][5]=0x100;cells[9][3]=-1;cells[4][8]=1
  add('candidate_fallback_then_distinct_head',candidate=list(candidate),cells=cells,position=[12928,12928,312])
 for missing in (0,4,5):
  cells=defaults()['cells'];cells[missing][0]=-1
  if missing==4:cells[9][7]=0
  add('shared_fallback_at_candidate_or_head',cells=cells,cell=9 if missing==4 else 4)
 require(o.counts['elevated.0'] and o.counts['elevated.1'] and o.counts['0x476920'])
 return commands,expected,labels,dict(FLAGS,groups=groups,actual_counts=dict(o.counts),audited_block_calls=o.audit_calls-10,geometry_entries=o.geometry_entries,geometry_stores=o.geometry_stores,geometry_values=o.geometry_values,distinct_original_instructions=len(o.instructions))
def compare(a,commands,expected,report):
 p=subprocess.run([str(a.native),str(a.exe),str(a.direction_data),str(a.render_data),str(a.raster_data),str(a.geometry_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(p.stdout);report.with_suffix('.stderr').write_text(p.stderr)
 if p.returncode:raise AssertionError(('Advance Cell native runner failed',p.returncode,p.stderr[:1000]))
 rows=p.stdout.splitlines();require(len(rows)==len(commands))
 for i,(got,want) in enumerate(zip(rows,expected)):
  got=got.split()
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError(('Advance Cell differs',i,j,got[max(0,j-7):j+12],want[max(0,j-7):j+12]))
 return len(rows)
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,required=True)
 for name,filename in [('direction','direction-data.bin'),('render','render-data.bin'),('raster','raster-data.bin'),('geometry','ramp-geometry-data.bin')]:p.add_argument('--'+name+'-data',type=Path,default=ROOT/'private/derived/ra2-1006'/filename)
 p.add_argument('--output',type=Path);p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,receipt)
 else:
  folder=private_path(a.output,a.exe);require(not a.report and not(folder/'expected.json').exists() and not(folder/'report.json').exists())
  now=time.monotonic();commands,expected,labels,meta=generate(a);generation=time.monotonic()-now;report=folder/'report.json'
 now=time.monotonic();count=compare(a,commands,expected,report.with_name(report.stem+'-native'));comparison=time.monotonic()-now
 require(current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,cases=count,executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 if not a.expectations:
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=result));fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(count,'Advance Cell Scatter block sequences PASS')
if __name__=='__main__':main()
