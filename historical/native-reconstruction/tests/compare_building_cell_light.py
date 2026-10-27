# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete live Building ordinary drawing predicate: original expectations separate from current native."""
import argparse,hashlib,json,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from presentation_evidence import ROOT,hash_file,private_path,validate_receipt,check_replay_destination
from compare_original import PATCHED_EXPECTED,write_report
from original_results import python_closure
from verify_building_cell_light import verify
ORIGINAL=('tests/compare_building_cell_light.py','tests/original_building_cell_light.py','tools/verify_building_cell_light.py')
NATIVE=('src/render/BuildingOrdinaryDraw.hpp','src/render/BuildingOrdinaryDraw.cpp','src/render/BuildingFrameRedraw.hpp','src/render/BuildingFrameRedraw.cpp','src/sim/RevealArea.cpp','src/sim/RevealArea.hpp','src/sim/OriginalMath.hpp','tests/building_cell_light_vectors.cpp','src/render/BuildingCellLight.hpp')
SOURCES=ORIGINAL+NATIVE
FLAGS=dict(complete_building_ordinary=True,actual_map548070=True,signed_ambient10a=True,actual_packed_cell=True,actual_planar_projection=True,actual_height_projection=True,actual_ftol=True,children_and_startup_supplied=True,pixels=False,frame_scheduling=False)
def require(v):
 if not v:raise ValueError('Building ordinary evidence/domain differs')
from compare_building_ordinary import command as parent_command,parse as parent_parse,scenarios as parent_scenarios
def command(lookup=0,**kwargs):return f'{lookup} '+parent_command(**kwargs)
def parse(cmd):
 fields=cmd.split();require(len(fields)==44);lookup=int(fields[0]);require(0<=lookup<=2)
 return [lookup,*parent_parse(' '.join(fields[1:]))]
def scenarios():
 for i,(label,cmd) in enumerate(parent_scenarios()):yield 'joined_'+label,f'{i%3} '+cmd
 for raw in ((0,0),(-257,257),(-256,0),(511*256,511*256),(0,512*256),(-2147483648,2147483647)):
  for lookup in range(3):
   for ambient in (-32768,-1,0,32767):
    yield 'table_alias_hole_signed_boundary_fallback_repeated_layers',command(lookup=lookup,raw=raw,cell_height=ambient,stage=1,replacements=(0,0,0,0,1),frames=(1,1,1))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_building_cell_light.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e['executable_sha256']==PATCHED_EXPECTED and e['profile']=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(e['evidence']['original_instructions_executed'] is True and e['evidence']['original_instructions_modified'] is False)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  parse(cmd);validate_row(row)
def validate_row(row):
 require(row.count('F')==1);i=row.index('F');require(i%4==0 and len(row)==i+17)
 for j in range(0,i,4):
  require(1<=int(row[j])<=10)
  for v in row[j+1:j+4]:int(v)
 for v in row[i+1:]:int(v)
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_building_cell_light import BuildingCellLightOracle
  oracle=BuildingCellLightOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in list(scenarios()):commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;require(oracle.audit_calls==len(commands) and current==identities(a) and runner==hash_file(a.native))
  require(all(oracle.counts[k]>0 for k in ('0x548070','0x43a5e0','0x41b320','0x6a2870','0x5d4800','0x6a2970','0x77f110','0x6d1510')))
  meta=dict(FLAGS,actual_entries_and_services=dict(oracle.counts),identities=current,cases=len(commands),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[line.split() for line in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:raise AssertionError((i,labels[i],commands[i],got,want))
 guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=len(commands)-hits,original_generation_seconds=generation,native_comparison_seconds=time.monotonic()-now,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building Cell ambient joined sequences PASS; reuse hits/misses',hits,len(commands)-hits)
if __name__=='__main__':main()
