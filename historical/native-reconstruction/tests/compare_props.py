#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base ordinary props and raw/RLE SHP color/depth drawing."""
import argparse,hashlib,random,struct,time
from pathlib import Path
from scenery_evidence import prepare, identities, save, replay, run_native, hash_file

def wordhash(v):return hashlib.sha256(struct.pack('<'+str(len(v))+'H',*v)).hexdigest()
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
p.add_argument('--native',type=Path,default=Path('build/native/scenery-vectors'));p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--expectations',type=Path);p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path,default=None);p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc data identity for patched research')
p.add_argument('--exporter',type=Path,default=Path('build/native/scenery-vectors'))
a=p.parse_args();a.suite='props'
engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
 replay(a,engine_digest,engine_profile,native_data,work)
 raise SystemExit(0)
original_started=time.monotonic()
from original_props import PropsOracle
assets=a.assets
pal=[x<<2 for x in (assets/'temperat.pal').read_bytes()];iso=[x<<2 for x in (assets/'isotem.pal').read_bytes()]
commands=[];expected=[];labels=[];groups={};rng=random.Random(0x52413137)
def add(group,command,result):
 commands.append(' '.join(map(str,command)));expected.append(list(map(str,result)));labels.append(group);groups[group]=groups.get(group,0)+1
names=['hdstn01',*[f'lt_gen{n:02}' for n in range(1,5)],*[f'lt_sgn{n:02}' for n in range(1,5)],
 'lt_eur01','lt_eur02','pole01','pole02',*[f'sign{n:02}' for n in range(1,7)],*[f'trff{n:02}' for n in range(1,5)]]
paths=[assets/(name+'.tem') for name in names]
converters=[]
for tint,shades in [([992,992,832],53),([512,384,128],27)]:
 # converter() uses one fixed object address. Separate original memory spaces
 # prevent the 27-row constructor from overwriting the 53-row converter.
 oracle=PropsOracle(a.exe,pal,allow_patched=True)
 cvt,palette=oracle.converter(iso,pal,tint,shades)
 assert len(palette)==shades*256
 converters.append((oracle,cvt,palette,tint,shades))
o=converters[0][0];palette=converters[0][2]
for path in paths:
 blob=path.read_bytes();assert struct.unpack_from('<H',blob,6)[0]==2
 for n in range(8):
  w,h=160,128;loc=[[80,64],[0,64],[160,64],[80,0],[80,128],[15,23],[500,500],[110,80]][n]
  clip=[0,0,w,h] if n%3 else [7,9,140,108];height=[0,104,416,728][n%4]
  light=[0,500,1000,1312,2000,32767,-1,-32768][n];hp=-o.projection(0,0,height)[1]
  colors=[0x6bef]*(w*h);depth=[rng.choice([65535,32660,32768]) for _ in range(w*h)];alpha=[127]*(w*h)
  result=o.scene(blob,w,h,loc,clip,height,light,colors,depth,alpha,palette)
  add('owned_props_complete_terrain_draws',['F',path,w,h,0,*loc,*clip,0,hp,0,light,*colors,*depth,*alpha,*palette],[wordhash(v) for v in result])
  oracle,cvt,rows,tint,shades=converters[n%2]
  for frame in range(2):
   z=-hp-(3 if frame else 12);flags=0x4e01 if frame else 0x4e00;gradient=0 if frame else 2
   result=oracle.draw(blob,frame,w,h,loc,clip,flags,z,gradient,light,colors,depth,alpha,rows,cvt=cvt)
   add('owned_props_original_converter_frames',['I',path,w,h,frame,*loc,*clip,flags,z,gradient,light,*colors,*depth,*alpha,assets/'isotem.pal',*tint,shades],[wordhash(v) for v in result])
# Synthetic raw images exercise both raw body and raw shadow paths, zero source
# transparency, odd crops, clipping phases and signed depth/light boundaries.
for k in range(4):
 cw,ch=33+k,35+k;x,y=3+k,5+k;sw,sh=17+k,13+k
 pixels=bytes(rng.randrange(1,256) if rng.randrange(4) else 0 for _ in range(sw*sh))
 blob=struct.pack('<4H',0,cw,ch,2)+struct.pack('<4H4I',x,y,sw,sh,1,0,0,56)*2+pixels
 path=work/f'raw-{k}.shp';path.write_bytes(blob);paths.append(path)
 for n in range(64):
  w,h=48,40;frame=n%2;loc=[[24,20],[0,20],[48,20],[24,0],[24,40],[9,12],[-10,-10],[100,100]][n//2%8]
  clip=[0,0,w,h] if n%3 else [7,9,33,25]
  flags=0x4e01 if frame else 0x4e00;gradient=0 if frame else 2;z=[-3,-12,-63,-72,0,-107][n%6]
  light=[-32768,-1,0,500,1000,1312,2000,32767][n%8]
  colors=[rng.randrange(65536) for _ in range(w*h)];depth=[rng.choice([0,65535,32660+rng.randrange(110)]) for _ in range(w*h)];alpha=[rng.randrange(256) for _ in range(w*h)]
  rows=[rng.randrange(65536) for _ in range(53*256)]
  result=o.draw(blob,frame,w,h,loc,clip,flags,z,gradient,light,colors,depth,alpha,rows)
  add('raw_shp_complete_surfaces',['B',path,w,h,frame,*loc,*clip,flags,z,gradient,light,*colors,*depth,*alpha,*rows],[wordhash(v) for v in result])
oracles=[v[0] for v in converters]
fixtures={str(path):hash_file(path) for path in paths if path.parent==work}
report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'seed':1380004151,
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
print(f'{engine_profile}: {len(commands):,} original/native props results: PASS; {report["groups"]}')
