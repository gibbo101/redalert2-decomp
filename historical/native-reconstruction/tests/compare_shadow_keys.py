#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare actual Unit/Drive shadow keys, full Foot forwarding and selected masks."""
import argparse,hashlib,random,struct,time
from pathlib import Path
from shadow_key_evidence import prepare, identities, save, replay, run_native
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=Path('build/native/shadow-key-vectors'))
p.add_argument('--data-dir',type=Path,default=Path('private/game'));p.add_argument('--expectations',type=Path)
p.add_argument('--raster-data',type=Path,default=Path('private/derived/raster-data.bin'));p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path)
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
p.add_argument('--exporter',type=Path,default=Path('build/native/raster-vectors'))
p.add_argument('--staging-exporter',type=Path,default=Path('build/native/staging-vectors'))
a=p.parse_args();engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
 replay(a,engine_digest,engine_profile,native_data,work)
 raise SystemExit(0)
else:
 original_started=time.monotonic()
 from original_shadow_keys import ShadowKeysOracle
 o=ShadowKeysOracle(a.exe,allow_patched=True);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x52413134)
 def add(group,command,result):
  commands.append(' '.join(map(str,command)));expected.append(list(map(str,result)));labels.append(group);groups[group]=groups.get(group,0)+1
 bodies=[-2147483648,-1,0,1,31,32,992,1023,1024,32768,2147483647]
 headings=[0,1023,1024,2048,8192,32767,32768,64511,64512,65535]
 for body in bodies:
  for heading in headings:
   for y in [-2147483648,-17,-16,-1,0,15,16,31,2147483647]:
    speed=rng.choice([-1,0,1,1,2,3,4,5]);balloon=rng.choice([False,False,True])
    add('unit_seed_flat_drive',['K',body,heading,y,speed,int(balloon)],o.keys(body,heading,y,speed,balloon))
 for i in range(512):
  body=rng.randrange(-2147483648,2147483648);heading=rng.randrange(65536);y=rng.randrange(-2147483648,2147483648)
  speed=rng.choice([-1,0,1,2,3,4,5,7]);balloon=rng.choice([False,False,True])
  add('unit_seed_flat_drive',['K',body,heading,y,speed,int(balloon)],o.keys(body,heading,y,speed,balloon))
 for current in [-2147483648,-2,-1,0,1,2,3,4,5,6,7,2147483647]:
  for crusher in [False,True]:add('unit_speed_default',['D',current,int(crusher)],o.speed_default(current,crusher))
 # Execute the real flat Drive predicate/point too, supplying only actor height zero.
 for at in [[0,0],[123,-234],[2147483647,-2147483648],[-2147483648,2147483647]]:
  add('complete_foot_real_flat_drive',['G',*at],o.foot(at,[0,0],True,1,True))
 # General complete Foot cases supply virtual results and record full forwarding.
 for has in [False,True]:
  for predicate in [0,1,2,255]:
   for loc,offset in [([0,0],[0,0]),([10,-10],[-3,4]),([2147483647,-2147483648],[1,-1]),([-2147483648,2147483647],[-1,1])]:
    add('complete_foot_forwarding',['F',*loc,*offset,int(has),predicate],o.foot(loc,offset,has,predicate))
 for i in range(512):
  loc=[rng.randrange(-2147483648,2147483648) for _ in range(2)];offset=[rng.randrange(-2147483648,2147483648) for _ in range(2)]
  has=rng.choice([True,True,False]);predicate=rng.choice([0,1,1,2,255])
  add('complete_foot_forwarding',['F',*loc,*offset,int(has),predicate],o.foot(loc,offset,has,predicate))
 assets=a.assets
 model=o.load(assets/'htnk.vxl');o.begin_cache();add('protocol_reset',['O'],['reset']);snapshots={}
 angle=struct.unpack('<f',o.u.mem_read(o.va(0x785cf0),4))[0];offset=struct.unpack('<3f',struct.pack('<3I',*o.offset(angle)))
 for n in range(129):
  heading=((n%32) if n<64 else (31-n%32))*2048 if n<128 else 0
  body=((((heading>>10)+1)>>1)&31)<<5;words=o.keys(body,heading);key=words[0]
  pose=struct.unpack('<12f',struct.pack('<12I',*words[1:]));camera=o.matrices(heading,heading)[0][2];style=n%3
  candidate,meta=o.shadow(model,pose,camera,offset,style,0,0)
  events=o.dispatch(key,0,False,False,True,False,True);built=events[0][0]=='render'
  identity=events[1][1] if built else events[0][1]
  if built:snapshots[identity]=(candidate,meta[:6])
  pixels,rectangle=snapshots[identity]
  add('selected_owned_shadow_masks',['R',assets,body,heading,style],[key,int(built),hashlib.sha256(pixels).hexdigest(),*rectangle])
 o.check_heap()
 report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'seed':0x52413134,
         'fixture_services':o.services,'heap_file_services':o.counts,'audited_callable_roots':o.audit_calls,
         'audited_blocks':o.audit_blocks,'audited_supplied_point_writes':o.host_point_writes,
         'guarded_allocations':len(o.allocations),'original_generation_seconds':time.monotonic()-original_started,'original_instructions_modified':False,
         'scope':'Actual ordinary Unit seed/default blocks and complete flat Drive Shadow_Matrix/base pose with supplied point/map cell. Complete Foot dispatch with virtual predicate/point and final-wrapper recorder; forwarding is checked. Caller/input/permitted-write/heap audits and explicit supplied point write bounds exclude ordered native-original writes and full actor arenas. Selected occupied-column masks/crops with original successful shadow-wrapper decisions use supplied logical snapshot identities. Full Unit/type/INI draw/creation, original compressed pool/lifetime, nonflat/status/airborne and whole-frame parity are excluded.'}
native_started=time.monotonic()
actual=run_native(a,commands)
report['native_comparison_seconds']=time.monotonic()-native_started
if len(actual)!=len(expected):raise AssertionError('Result count mismatch')
for i,(x,y) in enumerate(zip(actual,expected)):
 if x!=y:raise AssertionError(f'{i} {commands[i]}: native {x}, original {y}')
report['cases']=len(commands)
report.update(identities(a,engine_digest,engine_profile,native_data))
save(a,work,commands,expected,labels,report)
print(f'{engine_profile}: {len(commands):,} original/native shadow-key protocol results: PASS; {report["groups"]}')
