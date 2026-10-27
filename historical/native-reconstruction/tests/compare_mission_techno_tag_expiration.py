#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Shared Radio/Techno Tag-expiration original proofs and guarded replays."""
import argparse,itertools,json,platform,random,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
from verify_mission_techno_tag_expiration import verify
NATIVE=('src/sim/MissionTechnoTagExpiration.hpp','src/sim/MissionTagObjectExpiration.hpp','src/sim/MissionTagExpiration.hpp','src/sim/MissionTag.hpp','src/sim/MissionTrigger.hpp','src/sim/MissionEvent.hpp','tests/mission_techno_tag_expiration_vectors.cpp')
ORIGINAL=('tests/original_mission_techno_tag_expiration.py','tools/verify_mission_techno_tag_expiration.py','tests/compare_mission_techno_tag_expiration.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_techno_tag_expiration.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(complete_Radio_Techno_expiration_for_nonnull_Tag_flags14_bit0_clear=True,actual_Object_passenger_unlink_control_and_vector_search=True,shared_borrowed_fields_and_retained_backing_tails=True,virtual_effects_RNG_other_services_startup_and_timer_padding_supplied=True,typed_Foot_Infantry_Building_and_runtime_join=False)
def require(ok):
 if not ok:raise ValueError('Techno Tag expiration evidence/input differs')
def command(f):
 values=[f['root'],f['subject'],f['flags'],*f['instances'],f['objectTag'],*f['next'],*f['fields'],*f['weapons'],*f['numbers'],f['byte372'],f['byte5BA'],f['frame'],f['session'],f['scratch'],f['retry'],f['ownerResult'],f['predicate1'],f['kind'],f['predicateC'],f['queryResult'],f['mode'],*f['control'],*f['counts'],*(v for b in f['buffers'] for v in b),len(f['operations']),*f['operations']]
 return 'T '+' '.join(map(str,values))
def parse(cmd):
 parts=cmd.split();require(parts and parts[0]=='T');values=list(map(int,parts[1:]));at=0
 def take(n=1):
  nonlocal at
  result=values[at:at+n];at+=n;require(len(result)==n);return result
 root,subject,flags=take(3);instances=take(2);objectTag=take()[0];next=take(3);fields=take(15);weapons=take(8);numbers=take(5);byte372,byte5BA=take(2);frame,session,scratch,retry,ownerResult,predicate1,kind,predicateC,queryResult,mode=take(10);control=take(2);counts=take(4);buffers=[take(8) for _ in range(4)];count=take()[0];operations=take(count);require(at==len(values))
 require(root in range(4) and subject in (1,2) and 0<=flags<=255 and not flags&1 and objectTag in range(3))
 require(all(-2**31<=n<2**31 for n in (*instances,*numbers,frame,session,scratch,retry,kind)) and all(0<=n<2**32 for n in (predicate1,predicateC,*operations)))
 require(next[0] in (0,2) and next[1]==0 and next[2] in range(3) and fields[0] in range(4) and fields[4] in (0,8) and fields[8] in (0,6) and fields[9] in (0,7) and fields[14] in range(4))
 require(all(0<=n<=9 for n in (*fields,*weapons,ownerResult,queryResult,*control,*(n for b in buffers for n in b))) and all(-2<=n<=8 for n in counts) and 0<=byte372<=255 and 0<=byte5BA<=255 and mode in range(4) and 1<=count<=32)
 return dict(root=root,subject=subject,flags=flags,instances=instances,objectTag=objectTag,next=next,fields=fields,weapons=weapons,numbers=numbers,byte372=byte372,byte5BA=byte5BA,frame=frame,session=session,scratch=scratch,retry=retry,ownerResult=ownerResult,predicate1=predicate1,kind=kind,predicateC=predicateC,queryResult=queryResult,mode=mode,control=control,counts=counts,buffers=buffers,operations=operations)
def base():
 return dict(root=1,subject=1,flags=0,instances=[3,7],objectTag=1,next=[2,0,1],fields=[3,1,1,5,8,1,1,1,6,7,1,1,1,1,1],weapons=[1,0,2,1,9,1,1,2],numbers=[-1,-91,20,25,44],byte372=255,byte5BA=128,frame=100,session=0,scratch=-123,retry=8,ownerResult=5,predicate1=255,kind=2,predicateC=1,queryResult=1,mode=1,control=[1,2],counts=[8,6,6,7],buffers=[[1,2,1,0,1,9,1,2],[9,2,9,0,9,2,8,7],[2,1,1,2,1,9,2,1],[2,1,1,0,1,9,2,1]],operations=[1])
def scenarios():
 for root,removed,count in itertools.product((0,1),(0,1,2,255,256,257,0xffffff00,0xffffffff),(-2,0,1,4,8)):
  f=base();f.update(root=root,operations=[removed]);f['counts'][0]=count;yield 'raw_removal_and_Radio_count',command(f)
 rng=random.Random(0x6d2d10)
 for case in range(320):
  f=base();subject=1+case%2;f.update(subject=subject,flags=(0,2,128,254)[case%4],objectTag=case%3,instances=[(-2**31,-1,0,1,2**31-1)[case%5],rng.randint(-10,10)],mode=case%4,frame=(-2**31,-1,0,100,2**31-1)[case%5],session=(0,0,1,-1)[(case//4)%4],scratch=rng.randint(-2**31,2**31-1),retry=(4,8,-1,2**31-1)[case%4],predicate1=(0,1,255,256,511)[case%5],predicateC=(0,1,255,256,511)[(case//5)%5],kind=(2,15,0)[case%3],ownerResult=(0,5,subject)[case%3],queryResult=(subject,0,2)[case%3])
  f['fields']=[rng.choice((0,subject,2,9)) for _ in range(15)];f['fields'][0]=case%4;f['fields'][4]=8 if case&1 else 0;f['fields'][8]=6 if case&2 else 0;f['fields'][9]=7 if case&4 else 0;f['fields'][14]=case%4
  if case%3:f['fields'][6]=subject
  f['next']=[2 if case&1 else 0,0,case%3];f['weapons']=[rng.choice((0,1,2,9)) for _ in range(8)]
  f['numbers']=[(-1,-2**31,0,99,2**31-1)[case%5],-case,(0,10,11,20,2**31-1,-1)[case%6],(25,0,8)[case%3],44]
  f['counts']=[rng.randint(-2,8) for _ in range(4)];f['buffers']=[[rng.choice((0,1,2,9)) for _ in range(8)] for _ in range(4)]
  f['control']=[case%3,2];f['operations']=[(0,1,256,257)[(case//4)%4]] if case%7 else [0,256,257,1]
  yield 'live_Techno_fields_timer_services_pair_counts_and_tails',command(f)
 for root,head,nodeNext,subject in itertools.product((2,3),range(4),range(3),(1,2)):
  f=base();f.update(root=root,subject=subject,operations=[1,1]);f['fields'][0]=head;f['next'][2]=nodeNext;f['control']=[head,subject];yield 'independent_passenger_and_control_children',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_techno_tag_expiration.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_techno_tag_expiration import MissionTechnoTagExpirationOracle
  oracle=MissionTechnoTagExpirationOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  require(all(oracle.counts[hex(a)]>0 for a in (0x5d3bd0,0x636ba0,0x6d2d10,0x468a70,0x468120,0x4d5b40)))
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
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands);write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Techno Tag expiration sequences PASS;',meta['audited_original_calls'],'complete roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
