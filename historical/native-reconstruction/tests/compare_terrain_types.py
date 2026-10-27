#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare base Terrain type/image decisions and every stock ordinary tree image."""
import argparse,hashlib,random,struct,time
from pathlib import Path
from scenery_evidence import prepare, identities, save, replay, run_native, hash_file

def wordhash(v):return hashlib.sha256(struct.pack('<'+str(len(v))+'H',*v)).hexdigest()
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
p.add_argument('--native',type=Path,default=Path('build/native/scenery-vectors'));p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--expectations',type=Path);p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path,default=None);p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc data identity for patched research')
p.add_argument('--exporter',type=Path,default=Path('build/native/scenery-vectors'))
a=p.parse_args();a.suite='terrain-types'
engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
 replay(a,engine_digest,engine_profile,native_data,work)
 raise SystemExit(0)
original_started=time.monotonic()
from original_terrain_types import TerrainTypeOracle
from original_scenery import SceneryOracle
assets=a.assets
o=TerrainTypeOracle(a.exe,allow_patched=True);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x52413136)
def add(group,command,result):
 commands.append(' '.join(map(str,command)));expected.append(list(map(str,result)));labels.append(group);groups[group]=groups.get(group,0)+1
for current in [-2147483648,-200,-2,-1,0,1,2,200,2147483647]:
 for stock in [-2147483648,-1,0,1,2,200,32767,2147483647]:add('strength_default_prefix',['S',current,stock],o.strength(current,stock))
for n in range(384):
 force=n%2;requested=n//2%3;previous=[-1,0,1,2,3][n//6%5]
 count=n%9;items=[]
 for i in range(count):
  name=f'TREE{(n+i)%28+1:02}' if n%3 else f'tree{(n+i)%28+1:02}'
  items.append((name,rng.randrange(2),rng.randrange(2),rng.choice([0,0xffffffff,7,0x2000000+i*16]),rng.choice([0,0x2200000+i*16])))
 add('complete_theater_reload',['R',force,requested,previous,count,*[v for item in items for v in item]],o.reload(force,requested,previous,items))
pal=[x<<2 for x in (assets/'temperat.pal').read_bytes()];iso=[x<<2 for x in (assets/'isotem.pal').read_bytes()]
s=SceneryOracle(a.exe,pal,allow_patched=True);cvt,palette=s.converter(iso,pal,[992,992,832],53)
paths=[assets/f'tree{n:02}.tem' for n in range(1,29)]
for path in paths:
 blob=path.read_bytes();cw,ch=struct.unpack_from('<2H',blob,2)
 assert struct.unpack_from('<H',blob,6)[0]==2
 # A separate complete original Terrain call for each owned type at eight
 # placements: visible, clipped on each edge, alternate origin and fully outside.
 for n in range(8):
  w,h=160,128;loc=[[80,64],[0,64],[160,64],[80,0],[80,128],[15,23],[500,500],[110,80]][n]
  clip=[0,0,w,h] if n%3 else [7,9,140,108];height=[0,104,416,728][n%4]
  light=[0,500,1000,1312,2000,32767,-1,-32768][n];hp=-s.projection(0,0,height)[1]
  colors=[0x6bef]*(w*h);depth=[rng.choice([65535,32660,32768]) for _ in range(w*h)];alpha=[127]*(w*h)
  result=s.scene(blob,w,h,loc,clip,height,light,colors,depth,alpha,palette)
  add('owned_trees_complete_terrain_draws',['F',path,w,h,0,*loc,*clip,0,hp,0,light,*colors,*depth,*alpha,*palette],[wordhash(v) for v in result])
  for frame in range(2):
   z=-hp-(3 if frame else 12);flags=0x4e01 if frame else 0x4e00;gradient=0 if frame else 2
   result=s.draw(blob,frame,w,h,loc,clip,flags,z,gradient,light,colors,depth,alpha,palette,cvt)
   add('owned_trees_original_converter_draws',['I',path,w,h,frame,*loc,*clip,flags,z,gradient,light,*colors,*depth,*alpha,assets/'isotem.pal',992,992,832,53],[wordhash(v) for v in result])
oracles=[o,s]
fixtures={str(path):hash_file(path) for path in paths if path.parent==work}
report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'seed':1380004150,
        'fixture_sha256':fixtures,'original_generation_seconds':time.monotonic()-original_started,
        'audited_callable_roots':sum(o.audit_calls for o in oracles),'audited_blocks':sum(o.audit_blocks for o in oracles),
        'guarded_allocations':sum(len(getattr(o,'allocations',[])) for o in oracles),
        'original_instructions_modified':False,'scope':'Terrain strength prefix with supplied ObjectType loader, complete theater reload/makepath with ordered native-original pointer/ownership events; all 28 owned ordinary tree images through complete Terrain/SHP. Bounded caller/input/permitted-write/heap audits exclude full actor arenas, original file/allocator/converter lifetime, alternate flags/actors, global scheduling and whole-frame parity. SHP null-shape patch difference is inspection only.'}
native_started=time.monotonic()
actual=run_native(a,commands)
report['native_comparison_seconds']=time.monotonic()-native_started
if len(actual)!=len(expected):raise AssertionError(f'Result count mismatch {len(actual)} != {len(expected)}')
for i,(x,y) in enumerate(zip(actual,expected)):
 if x!=y:raise AssertionError(f'case {i} {commands[i][:180]}: native {x}, original {y}')
report['cases']=len(commands)
report.update(identities(a,engine_digest,engine_profile,native_data))
if {str(path):hash_file(path) for path in paths if path.parent==work}!=fixtures:raise ValueError('Synthetic fixtures changed during native replay')
save(a,work,commands,expected,labels,report)
print(f'{engine_profile}: {len(commands):,} original/native terrain-types results: PASS; {report["groups"]}')
