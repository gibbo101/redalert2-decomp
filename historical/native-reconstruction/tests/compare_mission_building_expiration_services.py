#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Building expiration stock null-target and pending-mission services proof."""
import argparse,itertools,json,math,platform,random,struct,subprocess,sys,time
from pathlib import Path
import capstone,pefile,unicorn
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import ROOT,private_path,hash_file,validate_receipt,check_replay_destination
from original_results import python_closure
import compare_mission_typed_tag_expiration as parent
from verify_mission_building_expiration_services import verify
NATIVE=tuple(p for p in parent.NATIVE if p!='tests/mission_typed_tag_expiration_vectors.cpp')+('src/sim/MissionBuildingTarget.hpp','tests/mission_building_expiration_services_vectors.cpp')
ORIGINAL=('tests/original_mission_building_expiration_services.py','tools/verify_mission_building_expiration_services.py','tests/compare_mission_building_expiration_services.py')
SOURCES=(*NATIVE,*ORIGINAL,'tests/test_mission_building_expiration_services.py','tools/run_evidence.py','CMakeLists.txt')
FLAGS=dict(actual_Building_expiration_stock_null_target_and_pending_services=True,complete_availability_permission_restore_and_stock_getters=True,nonnull_target_admission_excluded=True,House_power_service_weapon_release_and_earlier_effects_supplied=True,diagnostic_mutations_not_gameplay_observations=True,production_and_waypoint_join=False)
def require(ok):
 if not ok:raise ValueError('Building expiration service evidence/input differs')
bits=parent.bits
def defaults():
 return dict(profile=0,entry=0,pending9C=-1,queuedA4=255,byte530=1,word3FC=0,byte59C=1,byte404=255,word310=99,byte170=0,availabilityTypes=[[1,1,1,0] for _ in range(5)],powerBits=bits(1.),policyIndex=-1,policyByte=0,effectMode=0)
def command(f):
 values=[f[k] for k in ('profile','entry','pending9C','queuedA4','byte530','word3FC','byte59C','byte404','word310','byte170')]
 values += [v for record in f['availabilityTypes'] for v in record]
 values += [f[k] for k in ('powerBits','policyIndex','policyByte','effectMode')]
 return parent.command(f)+' : '+' '.join(map(str,values))
def parse(cmd):
 chunks=cmd.split(' : ');require(len(chunks)==2);f=parent.parse(chunks[0]);values=list(map(int,chunks[1].split()));require(len(values)==34)
 for k,v in zip(('profile','entry','pending9C','queuedA4','byte530','word3FC','byte59C','byte404','word310','byte170'),values[:10]):f[k]=v
 f['availabilityTypes']=[values[10+i*4:14+i*4] for i in range(5)]
 for k,v in zip(('powerBits','policyIndex','policyByte','effectMode'),values[30:]):f[k]=v
 require(f['profile'] in (0,1) and f['entry'] in range(11) and f['effectMode'] in range(5))
 require(all(-2**31<=f[k]<2**31 for k in ('pending9C','word3FC','word310','policyIndex')))
 require(all(0<=f[k]<=255 for k in ('queuedA4','byte530','byte59C','byte404','byte170')) and 0<=f['powerBits']<2**64 and 0<=f['policyByte']<2**32)
 require(all(0<=r[0]<=255 and -2**31<=r[1]<2**31 and 0<=r[2]<=255 and 0<=r[3]<=255 for r in f['availabilityTypes']))
 if f['profile']:
  require(f['root']==6 and f['childMode']==0 and f['typed'][0] in (1,2,9,15,16) and f['weapons'][0] in (0,9))
  require(f['fields'][9] in (0,7))
  if f['entry'] in (0,5):require(f['fields'][7]==0)
 return f
def base(entry=0):
 f=parent.parent.base();f.update(parent.defaults());f.update(defaults());f.update(profile=1,entry=entry,root=6,operations=[0,257]);f['typed'][0]=15;f['typed'][4]=0;f['fields'][7]=0;f['fields'][9]=7;f['weapons'][0]=9
 return f
def scenarios():
 for label,cmd in parent.scenarios():
  f=parent.parse(cmd);f.update(defaults());yield 'retained_typed_'+label,command(f)
 # Availability exits, signed comparisons and the original unordered/CF rule.
 for case in range(180):
  f=base(3);f.update(byte530=(0,1,255)[case%3],word3FC=(-2**31,-1,0,1,2**31-1)[(case//3)%5],actorHealth=(-2**31,-1,0,1,2**31-1)[(case//15)%5],byte59C=(0,1,255)[(case//5)%3],effectMode=case%5)
  f['extraCounts'][2]=(-2,-1,0,1,2,8)[(case//2)%6]
  f['availabilityTypes']=[[(0,1,255)[case%3],(-2**31,-1,0,1,2**31-1)[(case//3)%5],(0,1,255)[(case//4)%3],(0,1,255)[(case//7)%3]] for _ in range(5)]
  f['powerBits']=bits((-math.inf,0.,math.nextafter(1.,0.),1.,math.nextafter(1.,math.inf),math.inf,math.nan)[case%7])
  yield 'availability_signed_and_early_exit',command(f)
 for ratio,count,effect in itertools.product((-math.inf,-1.,0.,math.nextafter(1.,0.),1.,math.nextafter(1.,math.inf),math.inf,math.nan),(1,2),range(5)):
  f=base(3);f.update(powerBits=bits(ratio),effectMode=effect);f['extraCounts'][2]=count;f['availabilityTypes'][-1][3]=1;f['byte59C']=0
  yield 'power_unordered_equal_threshold_and_late_live_type_count',command(f)
 for entry in (1,2):
  for case in range(90):
   f=base(entry);f.update(effectMode=case%5,policyByte=(0,1,256,257,0xffffffff)[(case//5)%5],policyIndex=(-2**31,-1,0,1,2**31-1)[case%5]);f['fields'][6]=(0,1,2)[(case//3)%3];f['fields'][9]=(0,7)[(case//9)%2];f['weapons'][0]=(0,9)[(case//2)%2];f['numbers'][3]=(19,-1,8)[case%3]
   yield 'null_clear_equal_early_return_late_target_release_and_repeat',command(f)
 for entry in (4,5,8):
  for pending,mission,byte in itertools.product((-2**31,-1,0,19,2**31-1),(-1,8,19),(0,255)):
   f=base(entry);f.update(pending9C=pending,queuedA4=byte,effectMode=3);f['numbers'][3]=mission;f['fields'][6]=1
   yield 'pending_distinct_queue_restore_stores_and_resume',command(f)
 for entry in (6,7,9,10):
  for case in range(15):
   f=base(entry);f.update(policyByte=(0,1,256,257,0xffffffff)[case%5],policyIndex=(-2**31,-1,0,1,2**31-1)[case%5],byte170=(0,1,255)[case%3],effectMode=case%5);f['typed'][0]=(1,2,9,15,16)[case%5]
   yield 'stock_getters_permission_low_byte_and_signed_index',command(f)
 for case in range(160):
  f=base();f.update(subject=1+case%2,mode=case%4,pending9C=(-1,0,19,8)[(case//4)%4],effectMode=(case//3)%5,byte170=(0,1,255)[(case//2)%3],policyByte=(0,256,257)[case%3],powerBits=bits((0.,1.,math.nan)[case%3]))
  subject=f['subject'];f['fields'][6]=subject;f['fields'][2]=subject;f['fields'][3]=subject;f['fields'][4]=8;f['numbers'][3]=(19,8,-1)[(case//8)%3];f['typed'][4]=subject
  yield 'complete_Building_expiration_actual_target_pending_getters',command(f)
def identities(a):
 paths=python_closure(ROOT/'tests/compare_mission_building_expiration_services.py',{'sources':dict.fromkeys(ORIGINAL)})
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
  require(a.output is not None and not a.report);folder=private_path(a.output,a.exe);require(not folder.exists());from original_mission_building_expiration_services import MissionBuildingExpirationServicesOracle
  oracle=MissionBuildingExpirationServicesOracle(a.exe);commands=[];labels=[];expected=[];now=time.monotonic()
  for label,cmd in scenarios():commands.append(cmd);labels.append(label);expected.append(oracle.run(parse(cmd)))
  generation=time.monotonic()-now
  require(all(oracle.counts[hex(address)]>0 for address in (0x449e40,0x440450,0x6c9af0,0x450360,0x6c5070,0x594d80,0x6cd880,0x453c60,0x5950e0,0x41b410,0x41b2e0)))
  require(all(oracle.counts[k]>0 for k in ('supplied.power','supplied.clear68A490','supplied.weaponIndex','supplied.weaponPermission','supplied.release')))
  require(current==identities(a) and runner==hash_file(a.native))
  meta=dict(FLAGS,identities=current,cases=len(commands),counts=dict(oracle.counts),selected_stores=dict(oracle.stores),audited_original_calls=oracle.audit_calls,evidence_mode='fresh-original',original_instructions_executed=True,original_instructions_modified=False,original_generation_seconds=generation,receipt_contains_original_results_only=True)
  source=folder/'expected.json';write_report(a.exe,source,dict(executable_sha256=PATCHED_EXPECTED,profile='supplied-ra2-1006',commands=commands,labels=labels,expected=expected,evidence=meta));fingerprint=hash_file(source);write_report(a.exe,folder/'report.json',dict(meta,expectations_sha256=fingerprint));report=folder/'native-comparison.json'
 now=time.monotonic();run=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',capture_output=True,text=True);report.parent.mkdir(parents=True,exist_ok=True);report.with_suffix('.stdout').write_text(run.stdout);report.with_suffix('.stderr').write_text(run.stderr);require(run.returncode==0)
 actual=[r.split() for r in run.stdout.splitlines()];require(len(actual)==len(expected))
 for i,(got,want) in enumerate(zip(actual,expected)):
  if got!=want:
   j=next((j for j,(x,y) in enumerate(zip(got,want)) if x!=y),min(len(got),len(want)));raise AssertionError((i,labels[i],commands[i],j,got[max(0,j-6):j+15],want[max(0,j-6):j+15]))
 comparison=time.monotonic()-now;guards=subprocess.run([str(a.native),'--guards'],capture_output=True,text=True,check=True);require('guards PASS' in guards.stdout and current==identities(a) and runner==hash_file(a.native))
 hits=len(commands) if a.expectations else 0;misses=0 if a.expectations else len(commands);write_report(a.exe,report,dict(meta,identities=current,native_sha256=runner,evidence_mode='cached-original-replay' if a.expectations else 'fresh-original',original_instructions_executed=not bool(a.expectations),original_sequence_reuse_hits=hits,original_sequence_reuse_misses=misses,original_generation_seconds=generation,native_comparison_seconds=comparison,elapsed_seconds=time.monotonic()-start,expectations_sha256=fingerprint));print(len(commands),'Building expiration service sequences PASS;',meta['audited_original_calls'],'complete roots; reuse hits/misses',hits,misses)
if __name__=='__main__':main()
