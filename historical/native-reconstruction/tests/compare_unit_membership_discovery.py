#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Join actual visibility and discovery to Unit Mark/map/Cell occupation."""
import argparse,itertools,json,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from compare_unit_membership import command as membership_command,parse as membership_parse,row,RECORDS
from compare_unit_discovery import SOURCES as DISCOVERY_SOURCES
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_discovery import verify
SOURCES=(*DISCOVERY_SOURCES,'tests/original_unit_membership_discovery.py','tests/compare_unit_membership_discovery.py')
FIELDS=[0,0,0,0,0,0,1,0,0,0,0,14,-1,0,0,0]
def command(fields=None,**kwargs):
 kwargs.setdefault('header',[0,0,1,0,0,0,0,128,0])
 return 'J '+' '.join(map(str,FIELDS if fields is None else fields))+' '+membership_command(**kwargs)[2:]
def parse(cmd):
 p=cmd.split();assert p[0]=='J';f=list(map(int,p[1:17]));assert len(f)==16
 assert all(0<=n<1<<32 for n in f[:4]) and all(0<=f[i]<=255 for i in (*range(4,9),13,14,15))
 assert -2147483648<=f[9]<=2147483647 and f[10] in (0,1) and all(-2147483648<=f[i]<=2147483647 for i in (11,12))
 h,r,l,planes,rows=membership_parse('U '+' '.join(p[17:]));assert h[6] in (0,1) and h[8]==0
 return f,h,r,l,planes,rows
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
 validate_receipt(e,r,f)
 if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Joined discovery engine/profile differs')
 if e['evidence'].get('identities')!=current:raise ValueError('Joined discovery identity differs')
 if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Joined discovery counts differ')
 for cmd in e['commands']:
  try:parse(cmd)
  except (AssertionError,ValueError,IndexError,OverflowError):raise ValueError('Malformed joined discovery command') from None
def generate(a):
 from original_unit_membership_discovery import UnitMembershipDiscoveryOracle
 o=UnitMembershipDiscoveryOracle(a.exe);p=pefile.PE(str(a.exe));planes=list(struct.unpack('<100Q',p.get_data(0x7d27e8-0x400000,800)))
 commands=[];expected=[];labels=[];groups={};steps=0;rng=random.Random(0x6c2440)
 def add(label,fields=None,rows=None,header=None,records=None):
  nonlocal steps
  cmd=command(fields=fields,rows=rows,header=header or [0,0,1,0,0,0,0,128,0],records=records,planes=planes)
  args=parse(cmd);commands.append(cmd);expected.append(o.run_joined(*args));labels.append(label);groups[label]=groups.get(label,0)+1;steps+=len(args[-1])
 for level,ramp,primary,secondary,gate in itertools.product((-1,0,1,4),(0,7,13,20),(0,8),(0,2),(0,1)):
  rec=[r.copy() for r in RECORDS];rec[0][0:2]=[level,ramp];rec[3][2]=secondary;rec[0][2]=secondary
  f=FIELDS.copy();f[:4]=[primary]*4
  add('joined_complete_Mark_visibility_discovery_occupation_ramp_floor_and_repeated_state',f,
   [row(mode=m,z=level*104+128) for m in (1,2,0,3,0)],header=[0,0,1,gate,0,0,0,128,0],records=rec)
 for current,owner,mission,queued,human,control,h13d,override in itertools.product((0,1),(0,1),(-1,14,15),( -1,14),(0,255),(0,128),(0,255),(0,1)):
  f=FIELDS.copy();f[4:8]=[human,control,human,control];f[8:13]=[h13d,override,owner,mission,queued]
  add('joined_current_House_owner_raw_control_mission_and_secondary_override',f,
   [row(root=root) for root in (2,3,2,3)],header=[0,0,255,1,0,0,current,128,0])
 for i in range(48):
  rec=[r.copy() for r in RECORDS];f=FIELDS.copy();f[:4]=[rng.getrandbits(32) for _ in range(4)];f[4:8]=[rng.choice((0,1,255)) for _ in range(4)];f[10]=rng.randrange(2);f[11:13]=rng.choice(((-1,14),(14,-1),(15,14),(19,14)));f[13:]=[rng.choice((0,1,255)) for _ in range(3)]
  for r in rec:r[:5]=[rng.randrange(-128,128),rng.randrange(21),rng.getrandbits(32),rng.getrandbits(32),rng.getrandbits(32)]
  add('long_shared_fallback_visibility_fields_mission_and_membership_sequences',f,
   [row(mode=(1,2,0,3,0)[j%5],x=rng.choice((51,52,53))*256+rng.randrange(256),z=rng.randint(-2147483648,2147483647),eligible=rng.choice((0,1,255)),alt=rng.choice((0,1))) for j in range(25)],
   header=[rng.randrange(256),rng.randrange(256),1,rng.choice((0,1,-1)),0,0,rng.randrange(2),rng.randint(-2147483648,2147483647),0],records=rec)
 return commands,expected,labels,{'groups':groups,'query_steps':steps,'audited_original_calls':o.audit_calls,'actual_entries':o.entries,
  'selected_original_stores':o.selected_stores,'actual_visibility_and_discovery_calls':{k:v for k,v in o.service_counts.items() if k in ('0x568140','0x5683c0','0x6c2440')},
  'remaining_services':{k:v for k,v in o.service_counts.items() if k not in ('0x568140','0x5683c0','0x6c2440')},
  'third_stock_numeric_chain_values':o.stock,'initial_records_globals_and_occupied_Cell_recalculation_supplied':True,'Process_runtime_and_frame_parity_excluded':True}
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-membership-vectors')
 p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/unit-membership-discovery-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
 a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
 if a.expectations:
  source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
  report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
 else:
  dest=private_path(a.output,a.exe)
  if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh joined discovery destination invalid or exists')
  now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
 now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
 if proc.returncode:raise RuntimeError('Native joined discovery: '+proc.stderr.strip())
 actual=[r.split() for r in proc.stdout.splitlines()];elapsed=time.monotonic()-now
 if len(actual)!=len(expected):raise AssertionError('Joined discovery result counts differ')
 for i,(x,y) in enumerate(zip(actual,expected)):
  if x!=y:
   first=next((j for j,(xx,yy) in enumerate(zip(x,y)) if xx!=yy),min(len(x),len(y)))
   raise AssertionError(f'Joined discovery {i} {labels[i]} at {first}: {x[max(0,first-8):first+12]} != {y[max(0,first-8):first+12]}; {commands[i]}')
 safety=['','J 0',command()+' trailing',command(fields=[*FIELDS[:10],2,*FIELDS[11:]]),command(header=[0,0,1,0,0,0,-1,128,0]),command(header=[0,0,1,0,0,0,0,128,1])]
 for cmd in safety:
  r=subprocess.run([str(a.native)],input=cmd+'\n',text=True,capture_output=True)
  if r.returncode==0 or not r.stderr.strip():raise AssertionError('Joined discovery safety refusal missing')
 if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Joined discovery run changed')
 result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'native_safety_refusals':len(safety),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
  'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
  'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
 if not a.expectations:
  source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
 result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
 print(f'{len(commands):,} joined discovery sequences: PASS ({result["evidence_mode"]}, {metadata["query_steps"]:,} calls, {elapsed:.3f}s native)')
if __name__=='__main__':main()
