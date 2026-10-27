#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare ordinary Infantry base508530 selection through the null-target exit."""
import argparse,json,math,platform,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_infantry_weapon_selection import verify

NATIVE=('src/sim/InfantryWeaponSelection.hpp','src/sim/InfantryWeaponSelection.cpp','tests/infantry_weapon_selection_vectors.cpp')
ORIGINAL=('tests/original_infantry_weapon_selection.py','tools/verify_infantry_weapon_selection.py','tests/compare_infantry_weapon_selection.py')
FLAGS=dict(complete_508530_and_6C1380_null_target_path=True,actual_type_multiple_turret_weapon_slot_mission_and_kind_helpers=True,
 normal_and_elite_E1_slots=True,special_states_27_through_30_refused=True,nonnull_target_branches_refused=True,
 weapon_records_and_default_flags_supplied_from_rules=True,production_position_effect_schedule=False)
def require(v):
 if not v:raise ValueError('Infantry weapon-selection evidence/input differs')
def bits(v):return struct.unpack('<Q',struct.pack('<d',v))[0]
def command(rank=0.,mission=2,normal=(1,1),elite=(1,1),normalFlags=(0,0),eliteFlags=(0,0),state=0):
 return 'S '+' '.join(map(str,(state,bits(rank),mission,*normal,*elite,*normalFlags,*eliteFlags)))
def parse(cmd):
 p=cmd.split();require(len(p)==12 and p[0]=='S');v=list(map(int,p[1:]));require(-2**31<=v[0]<2**31 and not 27<=v[0]<=30 and 0<=v[1]<2**64 and -1<=v[2]<=30 and all(x in (0,1) for x in v[3:]));
 return dict(zip(('state','rank','mission','normalPrimary','normalSecondary','elitePrimary','eliteSecondary','normalNever','normalArea','eliteNever','eliteArea'),v))
def elite(f):
 n=struct.unpack('<d',struct.pack('<Q',f['rank']))[0];return n>=2.
def selected(f,prefix):
 if elite(f) and f['elite'+prefix]:return f['elite'+prefix]
 return f['normal'+prefix]
def selected_flag(f,prefix):
 if elite(f) and f['eliteSecondary']:return f['elite'+prefix]
 return f['normal'+prefix]
def scenarios():
 ranks=(-1.,0.,math.nextafter(2.,0.),2.,3.,float('inf'),float('-inf'),float('nan'))
 for r in ranks:yield 'stock_E1_normal_or_elite_null_target',command(rank=r)
 for r in ranks:
  kw=dict(rank=r,normal=(1,0));kw['elite' if r>=2. else 'normal']=(1,0);yield 'missing_selected_secondary_returns_zero',command(**kw)
 for r in ranks:
  kw=dict(rank=r,normal=(0,1));kw['elite' if r>=2. else 'normal']=(0,1);yield 'missing_selected_primary_returns_zero',command(**kw)
 for r in ranks:
  kw=dict(rank=r);kw['eliteFlags' if r>=2. else 'normalFlags']=(1,0);yield 'selected_secondary_never_use_returns_zero',command(**kw)
 for r in ranks:
  kw=dict(rank=r,mission=16);kw['eliteFlags' if r>=2. else 'normalFlags']=(0,1);yield 'selected_secondary_area_fire_mission16_returns_one',command(**kw)
 for r in ranks:
  kw=dict(rank=r,mission=2);kw['eliteFlags' if r>=2. else 'normalFlags']=(0,1);yield 'selected_secondary_area_fire_other_mission_reaches_null_target',command(**kw)
 states=(-2**31,-100,-1,0,1,7,14,21,26,31,32,100,1000,2**31-1,5,18)
 for i,state in enumerate(states):
  r=(0.,2.)[i&1];yield 'ordinary_state_variation_stock_E1',command(rank=r,state=state)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_infantry_weapon_selection.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,fingerprint,current):
 validate_receipt(e,r,fingerprint);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 rows=list(scenarios());require(list(zip(e['labels'],e['commands']))==rows and len(rows)==64 and len(e['expected'])==len(rows))
 for cmd,row in zip(e['commands'],e['expected']):
  q=parse(cmd);sec=selected(q,'Secondary');pri=selected(q,'Primary');never=selected_flag(q,'Never');area=selected_flag(q,'Area')
  typeCalls=1+(1+int(elite(q) and not q['eliteSecondary']))
  if sec:typeCalls+=1+int(elite(q) and not q['elitePrimary'])
  require(row.count('T')==typeCalls and row.count('M')==(1 if sec and pri and not never and area else 0))
  result=1 if sec and pri and not never and area and q['mission']==16 else 0;require(row[-2:]==['R',str(result)])
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/infantry-weapon-selection-vectors')
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current);commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_infantry_weapon_selection import InfantryWeaponSelectionOracle
  oracle=InfantryWeaponSelectionOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now;parsed=[parse(c) for c in commands];weapons=sum(1+(selected(q,'Secondary')!=0) for q in parsed);missions=sum(bool(selected(q,'Secondary') and selected(q,'Primary') and not selected_flag(q,'Never') and selected_flag(q,'Area')) for q in parsed);kinds=sum(bool(selected(q,'Secondary') and selected(q,'Primary') and not selected_flag(q,'Never') and not(selected_flag(q,'Area') and q['mission']==16)) for q in parsed)
  if not (oracle.counts['0x508530']==oracle.counts['0x6c1380']==len(commands) and oracle.counts['weapon']==oracle.counts['elite']==weapons and oracle.counts['mission']==missions and oracle.counts['kind']==2*kinds):
   raise ValueError(f'Infantry weapon-selection call counts differ: {dict(oracle.counts)} expected weapons={weapons} missions={missions} kinds={kinds}')
  require(current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0);actual=[x.split() for x in run.stdout.splitlines()];require(actual==expected)
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native));hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands)
 write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Infantry weapon-selection sequences PASS; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
