#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Foot, Infantry and Building Tag-expiration proof and guarded replay."""
import argparse,itertools,json,math,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
import compare_mission_techno_tag_expiration as parent
from verify_mission_typed_tag_expiration import verify
NATIVE=tuple(p for p in parent.NATIVE if p!='tests/mission_techno_tag_expiration_vectors.cpp')+('src/sim/MissionTypedTagExpiration.hpp','src/sim/OriginalMath.hpp','src/sim/RevealArea.hpp','src/sim/RevealArea.cpp','src/sim/CellVisibilityState.hpp','src/sim/TerrainOccupation.hpp','src/sim/Drive.hpp','tests/mission_typed_tag_expiration_vectors.cpp')
ORIGINAL=('tests/original_mission_typed_tag_expiration.py','tools/verify_mission_typed_tag_expiration.py','tests/compare_mission_typed_tag_expiration.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_typed_tag_expiration.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Foot_Infantry_Building_expiration_for_nonnull_Tag_flags14_bit0_clear=True,actual_inherited_Radio_Techno_Object_and_mission_kind_coordinate_map_ratio_secondary_Tag_kind=True,kind4_factory_path_excluded_by_actual_Tag_kind44=True,nested_virtual_6D6E50_strength84_association_animation_and_earlier_leaves_supplied=True,initial_records_map_type_FP_profile_padding_supplied=True,waypoint_recipients_and_runtime_join=False)
def require(ok):
 if not ok:raise ValueError('Typed Tag expiration evidence/input differs')
def bits(value):return struct.unpack('<Q',struct.pack('<d',value))[0]
def defaults():
 return dict(typed=[15,1,1,1,0,1,1,1,9,1,1,1,1,1,1,1,9],recordHealth=[1,2,3],recordByte7D=[1,1,1],recordNext4C8=[2,0,0],typeBytes=[1]*5,queuedA0=8,actorHealth=100,globalByte=1,point=[19*256+128,19*256+128,0],extraCounts=[8,8,8],extraBuffers=[[1,1,2,9,0,1,2,9] for _ in range(3)],strengths=[3]*5,animations=[[1,1] for _ in range(5)],thresholdBits=bits(.5),strengthType=15,childMode=0,mapMode=0)
def command(f):
 v=[*f['typed'],*f['recordHealth'],*f['recordByte7D'],*f['recordNext4C8'],*f['typeBytes'],f['queuedA0'],f['actorHealth'],f['globalByte'],*f['point'],*f['extraCounts'],*(v for b in f['extraBuffers'] for v in b),*f['strengths'],*(v for b in f['animations'] for v in b),f['thresholdBits'],f['strengthType'],f['childMode'],f['mapMode']]
 return parent.command(f)+' | '+' '.join(map(str,v))
def parse(cmd):
 chunks=cmd.split(' | ');require(len(chunks)==2);left=chunks[0].split();root=int(left[1]);require(root in range(7));left[1]=str(root if root<4 else 1);f=parent.parse(' '.join(left));f['root']=root;values=list(map(int,chunks[1].split()));at=0
 def take(n=1):
  nonlocal at
  r=values[at:at+n];at+=n;require(len(r)==n);return r
 f['typed']=take(17);f['recordHealth']=take(3);f['recordByte7D']=take(3);f['recordNext4C8']=take(3);f['typeBytes']=take(5);f['queuedA0'],f['actorHealth'],f['globalByte']=take(3);f['point']=take(3);f['extraCounts']=take(3);f['extraBuffers']=[take(8) for _ in range(3)];f['strengths']=take(5);f['animations']=[take(2) for _ in range(5)];f['thresholdBits'],f['strengthType'],f['childMode'],f['mapMode']=take(4);require(at==len(values))
 require(all(0<=n<=16 for n in (*f['typed'],*f['recordNext4C8'],*(n for b in f['extraBuffers'] for n in b))) and f['typed'][15] in range(4) and f['typed'][16] in (1,2,9,15,16))
 require(all(-2**31<=n<2**31 for n in (*f['recordHealth'],*f['point'],*f['strengths'],f['queuedA0'],f['actorHealth'])) and all(0<=n<=255 for n in (*f['recordByte7D'],*f['typeBytes'],*(n for b in f['animations'] for n in b),f['globalByte'])))
 require(all(-2<=n<=8 for n in f['extraCounts']) and 0<=f['thresholdBits']<2**64 and f['strengthType'] in (1,2,9,15,16) and f['childMode'] in range(4) and f['mapMode'] in range(3))
 if root==6:require(f['typed'][4]!=f['subject'] or f['typed'][0] in (1,2,9,15,16))
 return f
def scenarios():
 for label,cmd in parent.scenarios():
  f=parent.parse(cmd);f.update(defaults());yield 'retained_parent_'+label,command(f)
 rng=random.Random(0x4c8460)
 for root in (4,5):
  for case in range(128):
   f=parent.base();f.update(defaults());subject=1+case%2;f.update(root=root,subject=subject,flags=(0,2,128,254)[(case//2)%4],mode=case%4,childMode=(case//4)%4,mapMode=case%3,kind=(15,2,0)[case%3],operations=[(0,1,256,257)[case%4]])
   f['fields'][2]=subject;f['fields'][6]=0;f['numbers'][3]=(-1,8,0)[(case//8)%3];f['queuedA0']=(8,0)[(case//16)%2]
   f['typed']=[rng.choice((0,subject,2,9)) for _ in range(17)];f['typed'][0]=15;f['typed'][4]=0;f['typed'][15]=(subject,0,3,3)[(case//2)%4];f['typed'][16]=subject if case%11==0 else 9;f['typed'][6]=subject;f['typed'][9]=subject if case&2 else 0
   f['recordHealth']=[(-1,0,1,2**31-1)[(case//2)%4],(-2**31,0,2,7)[(case//4)%4],(-1,0,1,7)[(case//8)%4]];f['globalByte']=(0,1,255)[(case//16)%3]
   if case%17==0:f['typed'][15]=subject;f['recordHealth'][subject-1]=0
   f['recordByte7D']=[(0,255)[(case//16)%2]]*3;f['typeBytes']=[(0,255)[(case//32)%2]]*5
   f['point']=[(-2**31,-257,-255,19*256+128,20*256,2**31-1)[case%6],(19*256+1,20*256+1,-1)[case%3],case]
   f['extraCounts']=[rng.randint(-2,8) for _ in range(3)];f['extraBuffers']=[[rng.choice((0,1,2,9)) for _ in range(8)] for _ in range(3)]
   if case%13==0 and f['typed'][16]==9 and f['childMode']!=3:f['operations']=[0,257]
   yield 'actual_Foot_and_Infantry_inherited_calls_late_fields_and_map',command(f)
 for case in range(160):
  f=parent.base();f.update(defaults());subject=1+case%2;f.update(root=6,subject=subject,childMode=case%4,mode=(case//4)%4,operations=[(0,1,256,257)[case%4]])
  f['typed']=[rng.choice((0,subject,2,9)) for _ in range(17)];f['typed'][0]=(15,16,subject)[case%3];f['typed'][4]=subject if case%5 else 0;f['typed'][15]=0;f['typed'][16]=9
  f['actorHealth']=(-2**31,-1,0,1,50,2**31-1)[case%6];f['strengths']=[(-2**31,-1,0,1,3,10,2**31-1)[(case//3)%7]]*5
  f['thresholdBits']=bits((-math.inf,-.5,0.,.1,.5,1.,math.inf,math.nan)[(case//7)%8]);f['strengthType']=(1,2,9,15,16)[case%5]
  f['animations']=[[(0,1,255)[(case//4)%3],(0,1,255)[(case//8)%3]] for _ in range(5)];f['extraCounts']=[0,0,rng.randint(-2,8)];f['extraBuffers'][2]=[rng.choice((0,1,2,9)) for _ in range(8)]
  yield 'actual_Building_health_FP_animation_and_Tag_kind44_cleanup',command(f)
 for numerator,denominator,threshold in ((1,10,.1),(1,10,math.nextafter(.1,0.)),(1,3,1/3),(1,3,math.nextafter(1/3,0.)),(0,0,.5),(1,0,math.inf),(-1,0,-math.inf)):
  f=parent.base();f.update(defaults());f.update(root=6,actorHealth=numerator,strengths=[denominator]*5,thresholdBits=bits(threshold));f['typed'][4]=1;yield 'original_FP_rounding_equal_unordered_infinite_boundaries',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_typed_tag_expiration.py',{'sources':dict.fromkeys(ORIGINAL)})
 return dict(original=dict(inspection=verify(a.exe.read_bytes()),sources={p:hash_file(ROOT/p) for p in sorted(paths)},environment=dict(python=sys.version,python_sha256=hash_file(Path(sys.executable).resolve()),machine=platform.machine(),unicorn=unicorn.__version__,capstone=capstone.__version__,pefile=pefile.__version__)),native_sources={p:hash_file(ROOT/p) for p in NATIVE})
def validate(e,r,f,current):
 validate_receipt(e,r,f);require(e.get('executable_sha256')==PATCHED_EXPECTED and e.get('profile')=='supplied-ra2-1006' and e['evidence']['identities']['original']==current['original'])
 for k,v in FLAGS.items():require(e['evidence'].get(k) is v)
 require(list(zip(e['labels'],e['commands']))==list(scenarios()) and len(e['expected'])==len(e['commands']))
 for cmd,row in zip(e['commands'],e['expected']):require(isinstance(row,list) and all(isinstance(x,str) for x in row) and row.count('state')==1 and row.count('R')==len(parse(cmd)['operations']))
 require(e['evidence']['audited_original_calls']==sum(len(parse(c)['operations']) for c in e['commands']))
def main():
 p=argparse.ArgumentParser(description=__doc__)
 for k in ('exe','native'):p.add_argument('--'+k,type=Path,required=True)
 for k in ('output','expectations','report'):p.add_argument('--'+k,type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  require(not a.output and a.report is not None);source=private_path(a.expectations,a.exe);fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads((source.parent/'report.json').read_text()),fingerprint,current)
  commands,labels,expected=[e[k] for k in ('commands','labels','expected')];meta=e['evidence'];generation=0;report=private_path(a.report,a.exe);check_replay_destination(report,source,source.parent/'report.json')
 else:
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_typed_tag_expiration import MissionTypedTagExpirationOracle
  oracle=MissionTypedTagExpirationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  require(all(oracle.counts[hex(a)]>0 for a in (0x5d3bd0,0x636ba0,0x6d2d10,0x468a70,0x468120,0x4d5b40,0x4c8460,0x501cb0,0x449e40,0x594770,0x5d4e40,0x548070,0x5d4540,0x40ffb0,0x6b42d0)))
  require(all(oracle.counts[k]>0 for k in ('map_fallback','map_normal','supplied.animation.0','supplied.animation.1','supplied.strength.mode1','supplied.strength.mode2')))
  require(all(oracle.stores[hex(a)]>0 for a in (0x4c84a4,0x4c84eb,0x4c8509,0x4c85ad,0x4c85b3,0x4c860d,0x4c8613,0x4c8641,0x4c8695,0x501ccb,0x449f47,0x449f5c,0x449f8d)))
  require(oracle.counts['retained_Infantry_destination']>0 and oracle.counts['supplied.nested']>0 and oracle.counts['supplied.animation']>0)
  require(all(oracle.stores[hex(a)]>0 for a in (0x636bd4,0x468a86,0x468aab,0x46812d,0x468130,0x6d2e1f,0x6d2e25,0x6d2e2b,0x6d2e69,0x6d2e6f,0x6d2e90,0x6d2e96,0x6d2f90,0x6d2fd9,0x6d3019)))
  require(all(oracle.counts[k]>0 for k in ('supplied.owner.mode2','supplied.range.mode2','supplied.serviceA.mode2')))
  require(oracle.counts['supplied.owner']>0 and oracle.counts['supplied.range']>0 and oracle.counts['supplied.kind']>0 and oracle.counts['supplied.action400']>0 and current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),selected_stores=dict(oracle.stores),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0)
 actual=[r.split() for r in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands);write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Typed Tag expiration sequences PASS;',meta['audited_original_calls'],'complete roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
