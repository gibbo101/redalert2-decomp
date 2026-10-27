#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare original infantry subcell/occupation roots; replay with current C++."""
import argparse,itertools,json,re,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from verify_infantry_subcell import verify
NATIVE=('tests/infantry_subcell_vectors.cpp','src/sim/InfantrySubcell.cpp','src/sim/OriginalRandom.cpp',
 'src/render/Lighting.cpp','src/assets/InfantrySubcellData.cpp','src/assets/RenderData.cpp',
 'src/assets/PreparedData.cpp','src/assets/Archive.cpp')
ORIGINAL=('tests/original_infantry_subcell.py','tools/verify_infantry_subcell.py','tests/compare_infantry_subcell.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/presentation_evidence.py',
 'tests/compare_original.py','tools/verify_terrain_visibility.py','tools/prepare_infantry_subcell_data.py')
def source_closure():
 pending=list(NATIVE);seen=set()
 while pending:
  path=pending.pop()
  if path in seen:continue
  seen.add(path)
  for name in re.findall(r'^#include "([^"]+)"',(ROOT/path).read_text(),re.M):
   local=(ROOT/path).parent/name;pending.append(str(local.relative_to(ROOT)) if local.exists() else 'src/'+name)
 return tuple(sorted(seen))
SOURCES=(*source_closure(),*ORIGINAL,'tests/test_infantry_subcell.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(actual_complete_subcell_occupation_and_ordinary_selector=True,actual_offset_initializer_House_getter_RNG=True,
 selected_ordered_Cell_byte_and_owner_stores=True,initial_records_map_floor_and_seeding_supplied=True,
 building_policy_joined=False,Walk_head_caller_joined=False,production_world_join=False,runtime_enabled=False)
DEFAULT_CELLS=((0x12340000,0x56780000,0,17,23),(0x98760000,0xabcd0000,256,-7,9))
def require(ok):
 if not ok:raise ValueError('Infantry subcell evidence/input differs')
def step(op=3,point=(128,128,0),force=0,elevated=0,mutation=0,floor=0,threshold=104,house=3,height=104,cell=0):
 return (op,*point,force,elevated,mutation,floor,threshold,house,height,cell)
def command(steps=None,cells=DEFAULT_CELLS,disabled=0,first=0,second=103,seed=0x4764b0):
 steps=[step()] if steps is None else steps
 return 'I '+' '.join(map(str,(disabled,first,second,seed,*itertools.chain.from_iterable(cells),len(steps),*itertools.chain.from_iterable(steps))))
def parse(cmd):
 t=cmd.split();require(t and t[0]=='I');v=list(map(int,t[1:]));require(len(v)>=15)
 disabled,first,second,seed=v[:4];require(0<=disabled<=255 and 0<=first<250 and 0<=second<250 and 0<=seed<=0xffffffff)
 cells=[v[4:9],v[9:14]]
 for c in cells:require(all(0<=n<=0xffffffff for n in c[:3]) and all(-2147483648<=n<=2147483647 for n in c[3:]))
 count=v[14];require(1<=count<=1024 and len(v)==15+12*count);steps=[v[15+12*i:27+12*i] for i in range(count)]
 for s in steps:
  require(all(-2147483648<=n<=2147483647 for n in s));require(0<=s[0]<=3 and all(0<=s[i]<=255 for i in (4,5)) and 0<=s[6]<=511 and s[11] in (0,1))
 return disabled,first,second,seed,cells,steps
def scenarios():
 points=(0,1,63,64,68,69,70,80,85,86,87,88,100,127,128,129,156,168,169,170,171,176,186,187,188,191,192,193,254,255)
 for x in points:
  yield 'classifier_center_threshold_quadrants_and_negative_low_bytes',command(steps=[step(op=0,point=(x-256,y+256,2147483647)) for y in points])
 preferred=((64,64,0),(192,64,0),(64,192,0),(192,192,0),(128,128,0))
 for mask,elevated in itertools.product(range(64),(0,1,128)):
  cells=((0x12340000|mask,0x56780000|(mask^31),256,17,23),DEFAULT_CELLS[1])
  yield 'all_occupation_masks_both_layers_and_RNG_sequences',command(cells=cells,first=249,second=102,
   steps=[step(point=p,elevated=elevated) for p in preferred]*2)
 for force,elevated,mask in itertools.product((1,128,255),(0,1,255),(0,0x40,0x60,0xff)):
  cells=((mask,mask,0,17,23),DEFAULT_CELLS[1])
  yield 'raw_force_bypasses_bit5_and_building',command(cells=cells,steps=[step(point=p,force=force,elevated=elevated) for p in preferred])
 for disabled,first,second in itertools.product((0,1,128,255),(0,249),(0,103,249)):
  yield 'center_random_disabled_and_wrap',command(disabled=disabled,first=first,second=second,steps=[step()]*16)
 for flag,threshold,z in itertools.product((0,256),(-2147483648,-104,0,104,2147483647),(-2147483648,-105,-104,-1,0,103,104,105,2147483647)):
  cells=((0xaabbcc1f,0xddeeff1f,flag,17,23),DEFAULT_CELLS[1])
  yield 'occupation_release_height_wrap_flag_asymmetry_and_owner_mask',command(cells=cells,
   steps=[step(op=op,point=p,threshold=threshold,floor=104) for p in ((64,64,z),(192,64,z),(64,192,z),(192,192,z),(128,128,z)) for op in (2,1,2)])
 for mutation in (0,1,2,4,8,16,32,64,128,256,511):
  for cell in (0,1):
   yield 'saved_classification_Cell_identity_and_late_floor_effects',command(steps=[step(op=op,point=(-64,-192,104),mutation=mutation,cell=cell) for op in (1,2,3,1,2)])
 for mask in (0,4,8,16,28):
  for p in ((-1,-1,0),(-257,-511,17),(2147483647,-2147483648,-7)):
   yield 'aligned_negative_and_wrapped_bases_both_selector_branches',command(cells=((mask,mask,0,9,10),DEFAULT_CELLS[1]),
    steps=[step(point=p,elevated=e,mutation=m,force=f,height=2147483647,floor=7) for e in (0,128) for m in (0,511) for f in (0,255)])
def identities(a):
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in ORIGINAL},
  data={k:hash_file(getattr(a,k)) for k in ('render_data','subcell_data')}),native_sources={p:hash_file(ROOT/p) for p in source_closure()})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006')
 require(e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels']))
 require(e['evidence']['audited_original_calls']==1+sum(len(parse(cmd)[-1]) for cmd in e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);require(isinstance(row,list) and all(isinstance(t,str) for t in row) and row.count('Z')==1 and row.count('rng')==1)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native','render-data','subcell-data'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source)
  e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,expected,labels=[e[k] for k in ('commands','expected','labels')];meta=e['evidence'];generation=0
  report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());report=folder/'report.json'
  from original_infantry_subcell import InfantrySubcellOracle
  o=InfantrySubcellOracle(a.exe);commands=[];expected=[];labels=[];now=time.monotonic()
  for label,cmd in scenarios():
   try:row=o.run(*parse(cmd))
   except BaseException:print('Failed subcell scenario',label,cmd,flush=True);raise
   commands.append(cmd);expected.append(row);labels.append(label)
  generation=time.monotonic()-now;meta=dict(FLAGS,cases=len(commands),audited_original_calls=o.audit_calls,counts=dict(o.counts))
  require(all(o.counts.get(hex(k),0)>0 for k in (0x4763d0,0x4764b0,0x508410,0x5084a0,0x483390,0x6388a0,0x6c7420)))
  # Preserve original answers before native comparison, even if current C++
  # fails. A native repair must not regenerate these unchanged original roots.
  require(current==identities(a) and runner==hash_file(a.native))
  origin=dict(meta,identities=current,evidence_mode='fresh-original',original_instructions_executed=True,
   original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json'
  write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,expected=expected,labels=labels,evidence=origin))
  fingerprint=hash_file(source);write_report(a.exe,report,dict(origin,expectations_sha256=fingerprint))
  report=folder/'native-comparison.json'
 now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data),str(a.subcell_data)],input='\n'.join(commands)+'\n',capture_output=True,text=True)
 report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(proc.stdout);report.with_suffix('.stderr').write_text(proc.stderr)
 require(proc.returncode==0);actual=[r.split() for r in proc.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)))
   raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True)
 require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 result=dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',
  original_instructions_executed=not bool(a.expectations),original_instructions_modified=False,
  original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result);print(len(commands),'infantry subcell sequences PASS;',meta['audited_original_calls'],'audited original calls')
if __name__=='__main__':main()
