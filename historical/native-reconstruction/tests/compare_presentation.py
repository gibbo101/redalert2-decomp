#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare recovered lighting, RGB565 palette, VPL lookup and depth primitives."""
import argparse
import math
import random
import struct
import subprocess
from collections import Counter
from pathlib import Path
from original_presentation import PresentationOracle
from presentation_evidence import prepare, identities, save, replay

p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True)
p.add_argument('--vpl',type=Path,help='Existing private VPL; otherwise export it read-only from --data-dir')
p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--native',type=Path,default=Path('build/native/presentation-vectors'))
p.add_argument('--report',type=Path)
p.add_argument('--expectations',type=Path,help='Identity-checked native replay of private original expectations')
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity for data verification; required for patched research')
a=p.parse_args();digest,profile,native_data,out=prepare(a)
if a.expectations:
    replay(a,digest,profile,native_data,out)
    raise SystemExit(0)
o=PresentationOracle(a.exe,allow_patched=True);rng=random.Random(0x524135)
commands=[];expected=[];labels=[];groups=Counter()
def case(command,value,group):
    commands.append(command);expected.append(value);labels.append(group+f' #{len(commands)}');groups[group]+=len(value)
def f32(v):return struct.unpack('<f',struct.pack('<f',v))[0]
def vector():
    v=[rng.uniform(-1,1) for _ in range(3)];n=math.sqrt(sum(x*x for x in v));return [f32(x/n) for x in v]
for kind in range(1,5):
    for n in range(48):
        light,view=vector(),vector();intensity=[1.,2.,3.,8.][n%4];single=n%3==0
        if n<6:light=[[0,0,0],[0,0,1],[1,0,0],[-1,0,0],[0,1,0],[0,-1,0]][n];view=[0,0,1]
        if n==6:light=[0,0,-1];view=[0,0,1]
        case('L '+' '.join(map(str,[kind,int(single),*light,*view,intensity])),o.lighting(kind,light,view,intensity,single),'normal shades')
for n in range(24):
    shades=1 if n%4==0 else 53
    tint=[[1000]*3,[0]*3,[2000]*3,[-100,999,3000],[500,1500,750],[1001,998,1000]][n%6]
    palette=[rng.randrange(256) for _ in range(768)];mask=[int(n%3==0 or (n%3==1 and 16<=i<=31)) for i in range(256)]
    case('P '+' '.join(map(str,[shades,*tint,*palette,*mask])),o.palette(shades,tint,palette,mask),'RGB565 palette entries')
vpl=a.vpl.read_bytes();sections=struct.unpack_from('<I',vpl,8)[0]
for shade in range(sections):
    for color in range(256):case(f'V {color} {shade}',o.vpl(vpl,color,shade),'VPL lookups')
for n in range(160):
    candidate=[-1,0,1,32767,65534,65535,65536,100][n%8];size=1+n%31;start=n%size;count=n%97
    palette=[rng.randrange(65536) for _ in range(256)];source=[rng.randrange(256) if i%7 else 0 for i in range(count)]
    destination=[rng.randrange(65536) for _ in range(count)]
    depth=[(candidate+[-1,0,1,32000][i%4])&65535 for i in range(size)]
    case('Z '+' '.join(map(str,[candidate,count,size,start,*palette,*source,*destination,*depth])),o.span(candidate,palette,source,destination,depth,start),'depth outputs')
proc=subprocess.run([str(a.native),str(a.render_data),str(a.vpl)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
actual=[[int(v) for v in line.split()] for line in proc.stdout.splitlines()]
if len(actual)!=len(expected):raise AssertionError('Output count mismatch')
for label,x,y in zip(labels,actual,expected):
    if x!=y:
        differences=[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy]
        raise AssertionError(f'{label}: lengths {len(x)}/{len(y)}, differences (index,native,original): {differences[:12]}')
report={**identities(a,digest,profile,native_data),'cases':len(expected),'matched_values':sum(groups.values()),'groups':dict(groups),'seed':0x524135,'x87_control_word':'0x0e7f','original_instruction_bytes_changed':False,'fixture_services':[], 'scope':'Full normal shade kernels, LightConvert scalar RGB565 output with supplied palette/mask/tint, VPL lookup block, transparent depth span including circular buffer wrap. No original full-frame or rasterizer parity.',
        'audited_callable_roots':o.audit_calls,'audited_lookup_blocks':o.audit_blocks,
        'audit_scope':'Callable root return/ESP/callee-saved registers/caller stack beyond consumed arguments, bounded output/field/stack writes and immutable primitive inputs. Lookup block checks its single permitted stack-byte store and unchanged ESP. No ordered native/original write or full actor-arena comparison.'}
save(a,out,commands,expected,labels,report)
print(f'{len(expected):,} presentation cases / {sum(groups.values()):,} original/native values: PASS');print(dict(groups))
