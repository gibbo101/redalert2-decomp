#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete joined base500AA0 -> base4C7220 -> base6C2B40."""
import argparse,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_update_position_effects_e1 import verify
NATIVE=('src/sim/InfantryUpdatePositionE1.hpp','src/sim/InfantryUpdatePositionE1.cpp','src/sim/InfantryPositionEffectsE1.hpp','src/sim/InfantryPositionEffectsE1.cpp','src/sim/InfantrySightSchedule.hpp','src/sim/InfantrySightSchedule.cpp','src/sim/CellResidentKind6.hpp','src/sim/CellResidentKind6.cpp','src/sim/InfantryWeaponSelection.hpp','src/sim/InfantryWeaponSelection.cpp','src/sim/PositionCloakEffect.hpp','src/sim/PositionCloakEffect.cpp','src/sim/CellDirtyEffect.hpp','src/sim/CellDirtyEffect.cpp','src/sim/MovementGate.hpp','src/sim/TechnoSight.hpp','src/sim/TechnoSight.cpp','src/sim/TechnoSightRemoval.hpp','src/sim/TechnoSightRemoval.cpp','src/sim/PostSightRefresh.hpp','src/sim/PostSightRefresh.cpp','src/sim/VisibilityStartup.hpp','src/sim/VisibilityStartup.cpp','src/assets/MapCellChildren.hpp','src/assets/MapCellChildren.cpp','src/assets/MapCoordinateCell.hpp','src/assets/MapCoordinateCell.cpp','src/assets/MapFloorHeight.hpp','src/assets/MapFloorHeight.cpp','tests/infantry_update_position_effects_e1_vectors.cpp')
ORIGINAL=('tests/original_infantry_update_position_effects_e1.py','tools/verify_infantry_update_position_effects_e1.py','tools/verify_movement_gate.py','tools/verify_techno_sight.py','tools/verify_techno_sight_removal.py','tools/verify_post_sight_refresh.py','tests/compare_post_sight_refresh.py','tests/compare_infantry_update_position_effects_e1.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_infantry_update_position_effects_e1.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_joined_500AA0_4C7220_6C2B40_path=True,shared_native_actor_field_identities=True,actual_parent_child_and_tail_instructions=True,actual_three_current_Cell_getters_nine_full_coordinate_lookups_and_target_center_floor=True,permission_success_continuation_and_tail_active_store=True,actual_null_target_weapon_selector_map_position_cloak_and_dirty_early_exits=True,actual_mission_commence_sight_removal_and_sight_addition_roots=True,two_complete_post_sight_roots=True,remaining_post_sight_calls_supplied=True,reveal_mask_and_redraw_leaves_supplied=True,initialized_empty_resident_global=True,actual_Cell_target_ownership=True,production_schedule=False)
def require(v):
 if not v:raise ValueError('Joined Infantry E1 evidence/input differs')
def command(*v):return 'J '+' '.join(map(str,v))
def parse(c):
 p=c.split();require(len(p)==16 and p[0]=='J');v=list(map(int,p[1:]));require(all(-2**31<=x<2**31 for x in (*v[:3],*v[6:8])) and -32768<=v[3]<=32767 and -32768<=v[4]<=32767 and -128<=v[5]<=127 and v[8] in (0,1) and all(0<=x<=255 for x in v[9:11]) and all(x in (0,1) for x in v[11:15]));return dict(zip(('x','y','z','tx','ty','tz','range','queued','onMap','state59a','state59c','permission','sightActive','fullPost','enabled'),v))
def divided(v):return v//256 if v>=0 else -((-v)//256)
def signed32(v):return (v+2**31)%2**32-2**31
def indexes(x,y):return signed32(divided(y)*512+divided(x)),(((divided(y)+2**15)%2**16-2**15)*512+((divided(x)+2**15)%2**16-2**15))
def target_cell(i,x,y):
 blocked=set(indexes(x,y));tx=(31+i*7)%480;ty=(17+i*11)%500
 while ty*512+tx in blocked:tx=(tx+3)%480
 return tx,ty,(i%7)-3
def scenarios():
 rng=random.Random(0x500aa04c);edges=(-2**31,-16777217,-257,-256,-1,0,1,255,256,257,16777216,2**31-1)
 for i in range(64):
  xyz=[edges[(i+j*3)%len(edges)] if i<24 else rng.randint(-2**31,2**31-1) for j in range(3)];target=target_cell(i,xyz[0],xyz[1])
  yield 'complete_joined_argument2_parent_coordinate_sight_effects_tail',command(*xyz,*target,edges[i%len(edges)],-1 if i%3 else 2,i&1,(i*37)&255,(255-i*19)&255,0,i&1,0,0)
 for i in range(16):
  x=(57+i%4)*256+192;y=(89+(i//4)%4)*256+192
  yield 'actual_map_permission_success_sight_and_tail_active_store',command(x,y,rng.randint(-2**31,2**31-1),57+i%4+2,89+(i//4)%4,0,8,-1,1,(i*53)&255,(255-i*29)&255,1,i&1,int(i>=14),int(i>=8))
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_update_position_effects_e1.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  f=parse(cmd);on=f['onMap'];yi=row.index('Y');require(row.count('m')==7+4*on and row.count('C')==3 and row.count('H')==3 and row.count('W')==6 and all(row.count(k)==1 for k in ('K','T','M','R','A','P','V','L','Y')) and row.count('S')==int(row[yi+15]) and row.count('Q')==row.count('e6')==row.count('G')==row.count('E')==row.count('D')==on and row.count('p')==2*on and row.count('B')==on*(2-f['enabled']) and row.count('c')==4*on and (int(row[yi+16])>0)==bool(f['fullPost']) and row[-2:]==['X',str(int(bool(f['enabled'] or (on and f['permission']))))])
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/infantry-update-position-effects-e1-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_update_position_effects_e1 import InfantryUpdatePositionEffectsE1Oracle
  oracle=InfantryUpdatePositionEffectsE1Oracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;entered=sum(parse(c)['onMap'] for c in commands);permitted=sum(parse(c)['permission'] for c in commands);full=sum(parse(c)['fullPost'] for c in commands);require(oracle.counts['0x500aa0']==len(commands) and oracle.counts['0x4c7220']==entered and oracle.counts['0x6c2b40']==entered and oracle.counts['0x508530']==entered and oracle.counts['0x6c1380']==entered and oracle.counts['0x6c2990']==entered and oracle.counts['0x47bb30']==entered and oracle.counts['current_cell_getter']==3*len(commands) and oracle.counts['full_map']==9*len(commands) and oracle.counts['target_coordinates']==len(commands) and oracle.counts['cell_floor']==len(commands) and oracle.counts['mission_commence']==oracle.counts['sight_remove']==oracle.counts['sight_add']==len(commands) and oracle.counts['post_sight']==full and oracle.counts['supplied.post_sight']==len(commands)-full and oracle.counts['supplied.mask6A8D40']>0 and oracle.counts['map']==4*entered and oracle.counts['selector_type']==3*entered and oracle.counts['selector_weapon']==2*entered and oracle.counts['mission']==7*len(commands)+4*entered and oracle.counts['active']==entered-permitted and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),ordered_child_stores=['actor+59C=0','actor+59A=0','scratch_A35E24=0'],evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'joined Infantry E1 sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
