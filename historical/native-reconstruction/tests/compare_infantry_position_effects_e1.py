#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the bounded complete base4C7220 + base6C2B40 ordinary-E1 path."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_position_effects_e1 import verify

NATIVE=('src/sim/InfantryPositionEffectsE1.hpp','src/sim/InfantryPositionEffectsE1.cpp','src/sim/CellResidentKind6.hpp','src/sim/CellResidentKind6.cpp','src/sim/InfantryWeaponSelection.hpp','src/sim/InfantryWeaponSelection.cpp','src/sim/PositionCloakEffect.hpp','src/sim/PositionCloakEffect.cpp','src/sim/CellDirtyEffect.hpp','src/sim/CellDirtyEffect.cpp','tests/infantry_position_effects_e1_vectors.cpp')
ORIGINAL=('tests/original_infantry_position_effects_e1.py','tools/verify_infantry_position_effects_e1.py','tests/compare_infantry_position_effects_e1.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_infantry_position_effects_e1.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_4C7220_argument2_ordinary_E1_path=True,complete_entered_6C2B40_tail=True,
 actual_mission_coordinate_type_initialized_empty_resident_permission_and_active_helpers=True,
 permission_success_continuation_and_tail_active_store=True,
 actual_null_target_weapon_selector_map_position_cloak_and_dirty_early_exits=True,
 unsupported_alternate_effect_branches=False,production_position_effect_schedule=False)
def require(v):
 if not v:raise ValueError('Infantry E1 position-effects evidence/input differs')
def cell(v):return ((int(v/256)+0x8000)&0xffff)-0x8000
def command(x,y,z,a,c,on,permission=0):return 'F '+' '.join(map(str,(x,y,z,cell(x),cell(y),a,c,on,permission)))
def parse(cmd):
 p=cmd.split();require(len(p)==10 and p[0]=='F');v=list(map(int,p[1:]));require(all(-2**31<=x<2**31 for x in v[:3]) and all(-32768<=x<=32767 for x in v[3:5]) and all(0<=x<=255 for x in v[5:7]) and v[7] in (0,1) and v[8] in (0,1));require(v[3:5]==[cell(v[0]),cell(v[1])]);return dict(zip(('x','y','z','cellX','cellY','state59a','state59c','onMap','permission'),v))
def scenarios():
 rng=random.Random(0x4c7220);edges=(-2**31,-16777217,-16777216,-257,-256,-255,-1,0,1,255,256,257,16777215,16777216,2**31-1)
 for i in range(64):
  x=edges[i%len(edges)] if i<32 else rng.randint(-2**31,2**31-1);y=edges[(i*7+3)%len(edges)] if i<32 else rng.randint(-2**31,2**31-1)
  yield 'complete_argument2_position_effects_and_tail',command(x,y,rng.randint(-2**31,2**31-1),(i*37)&255,(255-i*19)&255,i&1)
 for i in range(16):
  x=(57+i%4)*256+192;y=(89+(i//4)%4)*256+192
  yield 'actual_map_permission_success_and_tail_active_store',command(x,y,rng.randint(-2**31,2**31-1),(i*53)&255,(255-i*29)&255,1,1)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_position_effects_e1.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  f=parse(cmd);on=f['onMap'];require(row.count('m')==4 and row.count('Q')==row.count('6')==1 and row.count('E')==row.count('D')==on and row.count('P')==1+on and row.count('B')==2*on and row.count('C')==1+3*on and row[-2:]==['X',str(on*f['permission'])])
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/infantry-position-effects-e1-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_position_effects_e1 import InfantryPositionEffectsE1Oracle
  oracle=InfantryPositionEffectsE1Oracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;entered=sum(parse(c)['onMap'] for c in commands);permitted=sum(parse(c)['permission'] for c in commands);require(oracle.counts['0x4c7220']==len(commands) and oracle.counts['0x6c2b40']==entered and oracle.counts['0x508530']==len(commands) and oracle.counts['0x6c1380']==len(commands) and oracle.counts['0x6c2990']==entered and oracle.counts['0x47bb30']==entered and oracle.counts['map']==len(commands)+3*entered and oracle.counts['type']==4*len(commands) and oracle.counts['selector_type']==3*len(commands) and oracle.counts['selector_weapon']==2*len(commands) and oracle.counts['mission']==4*len(commands) and oracle.counts['active']==entered-permitted and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),ordered_stores=['actor+59C=0','actor+59A=0','scratch_A35E24=0'],evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry E1 position-effects sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
