#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare bounded world projection and complete original buffer-surface composition."""
import argparse,hashlib,json,random,struct,subprocess
from pathlib import Path
from original_composition import TmpOracle,FlatDepthOracle
from composition_evidence import prepare, identities, save, replay, run_native
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True)
p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--native',type=Path,default=Path('build/native/composition-vectors'))
p.add_argument('--raster-data',type=Path,default=Path('private/derived/raster-data.bin'))
p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path)
p.add_argument('--expectations',type=Path,help='Identity-checked native replay; no original execution')
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
a=p.parse_args();digest,profile,native_data,evidence_dir=prepare(a)
if a.expectations:
 replay(a,digest,profile,native_data,evidence_dir)
 raise SystemExit(0)
o=TmpOracle(a.exe,allow_patched=True);out=a.assets
rng=random.Random(0x524137);commands=[];expected=[];labels=[];groups={}
def case(command,result,label,group):
 commands.append(command);expected.append(list(map(str,result)));labels.append(label);groups[group]=groups.get(group,0)+1
for n in range(256):
 x,y=[rng.randrange(-100000,100001) for _ in range(2)];z=[0,104,416,624,727,728,729,1456,-104,-728][n%10]
 case(f'P {x} {y} {z}',o.projection(x,y,z),f'projection #{n}','world projection')
for heading in sorted({(i*8192+d)&65535 for i in range(8) for d in [-1,0,1,4095,4096]}):case(f'O {heading}',[o.order(heading)],f'order {heading}','part order')
foot=FlatDepthOracle(a.exe,allow_patched=True)
for height in [0,104,416,624,727,728,729,1456]:case(f'Z {height}',[foot.adjustment(height)],f'flat depth {height}','flat unit depth')
palette=[rng.randrange(65536) for _ in range(53*256)]
for n in range(96):
 w,h,sw,sh=64,48,19,17;box=[[-2,0,19,15],[2,1,16,13],[0,0,19,17]][n%3];at=[[-10,-2],[-1,0],[0,-10],[8,8],[55,39],[80,70]][n%6];clip=[0,0,w,h] if n%2 else [4,3,55,39]
 z=[-1,-61,-106,0,-7][n%5];brightness=[1000,0,500,2000,1250][n%5]
 source=[rng.randrange(1,256) if i%7 else 0 for i in range(sw*sh)];colors=[rng.randrange(65536) for _ in range(w*h)]
 depth=[rng.choice([0,65535,32768-(i//w)+z-20+rng.randrange(41)]) for i in range(w*h)];alpha=[rng.randrange(256) for _ in range(w*h)]
 color,zplane=o.blit(w,h,source,sw,sh,box,at,clip,z,brightness,colors,depth,alpha,palette)
 def plane_digest(values):return hashlib.sha256(struct.pack('<'+'H'*len(values),*values)).hexdigest()
 case('B '+' '.join(map(str,[w,h,sw,sh,*box,*at,*clip,z,brightness,*source,*colors,*depth,*alpha,*palette])),[plane_digest(color),plane_digest(zplane)],f'unit blit #{n}','complete unit surfaces')
for name in ['clear01.tem','cliff01.tem','slope01.tem']:
 blob=(out/name).read_bytes();cols,rows=struct.unpack_from('<II',blob)
 for sub in range(cols*rows):
  if not struct.unpack_from('<I',blob,16+4*sub)[0]:continue
  for x,y,level in [(15,22,0),(15,22,4),(40,-3,2),(-4,10,7)]:
   color,zplane=o.tmp(blob,x,y,level,sub)
   case(f'T {out/name} {sub} {x} {y} {level}',[plane_digest(color),plane_digest(zplane)],f'tile {name}/{sub} {x}/{y}/{level}','complete TMP surfaces')
actual=run_native(a,commands)
assert len(actual)==len(expected)
for label,x,y in zip(labels,actual,expected):
 if x!=y:raise AssertionError(f'{label}\n native={x}\n original={y}')
report={**identities(a,digest,profile,native_data),'groups':groups,'matched_cases':len(expected),'cases':len(expected),
        'audited_callable_roots':o.audit_calls,'audited_blocks':o.audit_blocks,
        'flat_depth_audited_roots':foot.o.root_calls,'flat_depth_services':dict(foot.o.calls),
        'guarded_allocations':len(o.allocations),'original_instructions_modified':False,
        'scope':'World projection; ordinary barrel/turret dispatch block; complete alpha Z-read unit surfaces on actual BSurface methods; ordinary TMP draws with supplied file getter/palette/alpha-cache entry; flat healthy depth with supplied map/getter/tile services. Caller/input/write-range audits are not ordered native-original write or full actor/frame/lifetime parity.'}
save(a,evidence_dir,commands,expected,labels,report)
print(f'{profile}: {len(expected)} original/native world/composition cases: PASS');print(groups)
