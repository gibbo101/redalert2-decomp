#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare original actor keys, complete healthy lit cache wrapper and selected buffers."""
import argparse,hashlib,random
from pathlib import Path
from voxel_cache_evidence import prepare, identities, save, replay, run_native
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=Path('build/native/voxel-cache-vectors'))
p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--raster-data',type=Path,default=Path('private/derived/raster-data.bin'));p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path);p.add_argument('--expectations',type=Path)
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
p.add_argument('--exporter',type=Path,default=Path('build/native/raster-vectors'))
p.add_argument('--staging-exporter',type=Path,default=Path('build/native/staging-vectors'))
a=p.parse_args();engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
 replay(a,engine_digest,engine_profile,native_data,work)
 raise SystemExit(0)
else:
 from original_voxel_cache import VoxelCacheOracle
 o=VoxelCacheOracle(a.exe,allow_patched=True);rng=random.Random(0x52413133);commands=[];expected=[];labels=[];groups={}
 def add(group,command,result):
  commands.append(' '.join(map(str,command)));expected.append(list(map(str,result)));labels.append(group);groups[group]=groups.get(group,0)+1
 def reset():
  o.begin();add('protocol_resets',['O'],['reset'])
 angles=[0,1,1023,1024,2047,2048,8191,8192,32767,32768,64511,64512,65535]
 for loco in [-2147483648,-2,-1,0,1,31,32,1023,65535,2147483647]:
  for frame in [-1,0,1,31,32,63,2147483647]:
   for heading in angles:
    offset=rng.choice([0,0,1,-1,128]);add('actor_key_blocks',['K',loco,frame,heading,offset],o.keys(loco,frame,heading,offset))
 for i in range(1024):
  loco=rng.randrange(-2147483648,2147483648);frame=rng.randrange(-2147483648,2147483648);heading=rng.randrange(65536);offset=rng.choice([0,1,64,-64])
  add('actor_key_blocks',['K',loco,frame,heading,offset],o.keys(loco,frame,heading,offset))
 for sequence in range(12):
  reset();keys=[0,31,-1,-2,2147483647,-2147483648]+rng.sample(range(-2000,2001),64)
  rows=[(k,True,False,True) for k in keys]
  rows += [(k,True,False,True) for k in keys[::-1]]
  rows += [(rng.choice(keys),rng.choice([True,True,False]),rng.choice([False,False,True]),rng.choice([True,True,False])) for _ in range(64)]
  rows += [(0,True,False,False),(999999,True,False,False),(-1,True,False,False)]
  for key,available,disabled,valid in rows:
   frame=rng.randrange(64);brightness=rng.randrange(2201)
   result=o.dispatch(key,available,disabled,valid,frame,brightness)
   add('healthy_lit_wrapper_index',['D',key,int(available),int(disabled),int(valid),frame,brightness],[v for row in result for v in row])
 # Reuse the staging helper's source-path/symlink/different-content safeguards.
 # The harness never downloads or modifies the supplied installation.
 assets=a.assets
 names=['htnk','htnktur','htnkbarl'];vpl=(assets/'voxels.vpl').read_bytes()
 models=[o.load(assets/(n+'.vxl')) for n in names]
 # Each part has a separate supplied type index, as in the actual Unit caller.
 reset();frames={}
 for bh,th in [(0,0)]+[(b*2048,0) for b in range(32)]+[(b*2048,8192) for b in range(32)]+[(0,t*2048) for t in range(32)]+[(0,0),(32768,0),(0,0)]:
  matrices,_,loco=o.matrices(bh,th);body,turret,camera=matrices;body_key,turret_key=o.keys(loco,0,th,0)
  for part in range(3):
   o.index=0x1604000+part*0x40
   key=turret_key if part else body_key
   matrix=o.multiply(camera,turret if part else body);candidate,meta=o.draw(models[part],matrix,vpl,o.shades(models[part],matrix))
   events=o.dispatch(key,True,False,True)
   built=events[0][0]=='render';identity=events[1][1] if built else events[0][1]
   if built:frames[identity]=(candidate,meta[:6])
   selected,rectangle=frames[identity]
   add('selected_owned_cached_buffers',['R',assets,part,bh,th,0],[key,int(built),0,hashlib.sha256(selected).hexdigest(),*rectangle])
 # Explicit bypass still renders after warm hits and does not replace cached images.
 for bh,th in [(0,0),(32768,0),(0,8192),(0,0)]:
  matrices,_,loco=o.matrices(bh,th);body,turret,camera=matrices;body_key,turret_key=o.keys(loco,0,th,0)
  for part in range(3):
   o.index=0x1604000+part*0x40;key=turret_key if part else body_key
   matrix=o.multiply(camera,turret if part else body);candidate,meta=o.draw(models[part],matrix,vpl,o.shades(models[part],matrix))
   events=o.dispatch(key,True,True,True);assert len(events)==2 and events[0][0]=='render'
   add('owned_bypass_buffers',['R',assets,part,bh,th,1],[key,1,1,hashlib.sha256(candidate).hexdigest(),*meta[:6]])
 o.check_heap()
 report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'seed':0x52413133,
         'services':o.services,'heap_file_services':o.counts,'audited_callable_roots':o.audit_calls,
         'audited_blocks':o.audit_blocks,'audited_supplied_service_writes':o.host_writes,
         'guarded_allocations':len(o.allocations),'original_instructions_modified':False,
         'scope':'Actual Unit body/turret key blocks, complete healthy ordinary lit wrapper, real signed comparator/qsort/search and successful index growth. Virtual healthy predicates/type/house query, render rectangle, snapshot identity and cached draw are fixtures. Owned selected buffers combine original pose/lighting/raster with wrapper decisions and logical snapshot contents. Bounded caller/input/permitted-write/heap and explicit supplied-write audits exclude ordered native-original writes, full actor/type creation, compressed pool/failure/eviction, status flags, shadow identity and whole-frame parity.'}
actual=run_native(a,commands)
if len(actual)!=len(expected):raise AssertionError(f'Result count {len(actual)}/{len(expected)}')
for i,(x,y) in enumerate(zip(actual,expected)):
 if x!=y:raise AssertionError(f'{i} {commands[i][:180]}: native {x[:12]}, original {y[:12]}')
report['cases']=len(commands)
report.update(identities(a,engine_digest,engine_profile,native_data))
save(a,work,commands,expected,labels,report)
print(f'{engine_profile}: {len(commands):,} original/native voxel-cache protocol results: PASS; {report["groups"]}')
