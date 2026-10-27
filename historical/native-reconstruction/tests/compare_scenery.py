#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare exact-base healthy Terrain inputs and complete ordinary SHP surfaces."""
import argparse,hashlib,random,struct,time
from pathlib import Path
from scenery_evidence import prepare, identities, save, replay, run_native, hash_file
def wordhash(v):return hashlib.sha256(struct.pack('<'+str(len(v))+'H',*v)).hexdigest()
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=Path('build/native/scenery-vectors'))
p.add_argument('--data-dir',type=Path,default=Path('private/game'));p.add_argument('--expectations',type=Path)
p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'));p.add_argument('--report',type=Path,default=None)
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc data identity for patched research')
p.add_argument('--exporter',type=Path,default=Path('build/native/scenery-vectors'))
a=p.parse_args();a.suite='scenery'
engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
 replay(a,engine_digest,engine_profile,native_data,work)
 raise SystemExit(0)
original_started=time.monotonic()
from original_scenery import SceneryOracle
assets=a.assets
pal=[x<<2 for x in (assets/'temperat.pal').read_bytes()];iso=[x<<2 for x in (assets/'isotem.pal').read_bytes()]
o=SceneryOracle(a.exe,pal,allow_patched=True);commands=[];expected=[];labels=[];groups={};rng=random.Random(0x52413135)
def add(group,command,result):
 commands.append(' '.join(map(str,command)));expected.append(list(map(str,result)));labels.append(group);groups[group]=groups.get(group,0)+1
for height in [0,104,416,624,727,728,729,1456,-104,-728]:
 h=-o.projection(0,0,height)[1]
 for light in [-32768,-1,0,500,1000,1312,2000,32767]:
  add('complete_healthy_terrain_caller',['P',2,h,light],o.inputs(2,height,light))
# Both frames of the actual SHP; crop, transparent skips, odd canvas and row
# padding are exercised by original compressed spans rather than another decoder.
paths=[assets/'tree01.tem']
# Original routines also consume synthetic valid format-3 files without a file
# service. Their pixels are fixture data, not reverse-engineered game content.
for n in range(4):
 cw,ch=30+n,32+n;x,y=3+n,5+n;w,h=17+n,13+n
 pixels=[rng.randrange(1,256) if rng.randrange(4) else 0 for _ in range(w*h)]
 data=bytearray(struct.pack('<4H',0,cw,ch,2));data+=struct.pack('<4H4I',x,y,w,h,3,0,0,56)*2;rows=bytearray()
 for row in range(h):
  encoded=bytearray();i=0
  while i<w:
   v=pixels[row*w+i]
   if v:encoded.append(v);i+=1
   else:
    count=1
    while i+count<w and not pixels[row*w+i+count]:count+=1
    encoded+=bytes([0,count]);i+=count
  if n%2:encoded+=b'\0\1' # bounded terminal transparent encoder padding
  rows+=struct.pack('<H',len(encoded)+2)+encoded
 data+=rows;path=work/f'synthetic-{n}.shp';path.write_bytes(data);paths.append(path)
for n in range(240):
 path=paths[n%len(paths)];blob=path.read_bytes();frame=n%2;shadow=bool(frame)
 w,h=96,88;loc=[[80,80],[40,40],[0,0],[-10,50],[95,110],[130,70],[500,500]][(n//2)%7]
 clip=[0,0,w,h] if n%3 else [7,9,73,65]
 flags=0x4e01 if shadow else 0x4e00;gradient=0 if shadow else 2;z=[-3,-12,-63,-72,0,-107][n%6];brightness=[0,500,1000,1312,2000,3000][n%6]
 colors=[rng.randrange(65536) for _ in range(w*h)]
 depth=[rng.choice([0,65535,32660+rng.randrange(110)]) for _ in range(w*h)];alpha=[rng.randrange(256) for _ in range(w*h)]
 palette=[rng.randrange(65536) for _ in range(53*256)]
 result=o.draw(blob,frame,w,h,loc,clip,flags,z,gradient,brightness,colors,depth,alpha,palette)
 add('complete_compressed_shp_surfaces',['B',path,w,h,frame,*loc,*clip,flags,z,gradient,brightness,*colors,*depth,*alpha,*palette],[wordhash(v) for v in result])
for n in range(48):
 path=assets/'tree01.tem';w,h=96,88;loc=[[80,80],[45,60],[5,30],[110,100]][n%4];clip=[0,0,w,h] if n%3 else [7,9,73,65]
 height=[0,104,416,728,-104][n%5];height_pixels=-o.projection(0,0,height)[1];light=[500,1000,1312,2000][n%4]
 colors=[rng.randrange(65536) for _ in range(w*h)];depth=[rng.choice([65535,32630,32670,32768]) for _ in range(w*h)];alpha=[127]*(w*h)
 palette=[rng.randrange(65536) for _ in range(53*256)]
 result=o.scene(path.read_bytes(),w,h,loc,clip,height,light,colors,depth,alpha,palette)
 add('complete_terrain_and_two_shape_draws',['F',path,w,h,0,*loc,*clip,0,height_pixels,0,light,*colors,*depth,*alpha,*palette],[wordhash(v) for v in result])
for tint,shades in [([1000,1000,1000],53),([992,992,832],53),([512,384,128],27),([0,0,0],27)]:
 cvt,palette=o.converter(iso,pal,tint,shades)
 add('complete_ordinary_lightconvert',['L',assets/'isotem.pal',*tint,shades],[wordhash(palette)])
 for n in range(12):
  path=assets/'tree01.tem';frame=n%2;flags=0x4e01 if frame else 0x4e00;gradient=0 if frame else 2
  w,h=96,88;loc=[80,80] if n<6 else [50,60];clip=[0,0,w,h] if n%3 else [7,9,73,65];z=-63 if frame else -72
  colors=[0x6bef]*(w*h);depth=[rng.choice([65535,32630,32670,32768]) for _ in range(w*h)];alpha=[127]*(w*h)
  brightness=[500,1000,1312,2000][n%4]
  result=o.draw(path.read_bytes(),frame,w,h,loc,clip,flags,z,gradient,brightness,colors,depth,alpha,palette,cvt)
  add('owned_sprites_and_original_converters',['I',path,w,h,frame,*loc,*clip,flags,z,gradient,brightness,*colors,*depth,*alpha,assets/'isotem.pal',*tint,shades],[wordhash(v) for v in result])
oracles=[o]
fixtures={str(path):hash_file(path) for path in paths if path.parent==work}
report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'seed':1380004149,
        'fixture_sha256':fixtures,'original_generation_seconds':time.monotonic()-original_started,
        'audited_callable_roots':sum(o.audit_calls for o in oracles),'audited_blocks':sum(o.audit_blocks for o in oracles),
        'guarded_allocations':sum(len(getattr(o,'allocations',[])) for o in oracles),
        'original_instructions_modified':False,'scope':'Complete healthy Terrain caller, complete valid ordinary SHP wrapper/BSurface and selected raw/RLE body/shadow spans; successful ordinary converters. Bounded caller/input/permitted-write/heap audits exclude full actor arenas, original file/allocator/converter lifetime, alternate flags/actors, global scheduling and whole-frame parity. SHP null-shape patch difference is inspection only.'}
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
print(f'{engine_profile}: {len(commands):,} original/native scenery results: PASS; {report["groups"]}')
