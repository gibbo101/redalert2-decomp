#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare map quantization, normalization, complete cell inputs and lit surfaces."""
import argparse,hashlib,math,random,struct,subprocess
from pathlib import Path
from map_light_evidence import prepare,identities,save,replay,run_native
def words(v):return hashlib.sha256(struct.pack('<'+'H'*len(v),*v)).hexdigest()
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True);p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--native',type=Path,default=Path('build/native/map-light-vectors'))
p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path);p.add_argument('--expectations',type=Path)
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
p.add_argument('--exporter',type=Path,default=Path('build/native/map-light-vectors'))
a=p.parse_args();engine_digest,engine_profile,native_data,work=prepare(a);assets=a.assets
if a.expectations:
    replay(a,engine_digest,engine_profile,native_data,work)
    raise SystemExit(0)
from original_map_light import MapLightOracle,MapLightSurfaceOracle
o=MapLightOracle(a.exe,allow_patched=True);blit=MapLightSurfaceOracle(a.exe,allow_patched=True);rng=random.Random(0x52413130)
commands=[];expected=[];labels=[];groups={}
def add(group,command,result,label=''):
    commands.append(' '.join(map(str,command)));expected.append(list(map(str,result)));labels.append(label or group);groups[group]=groups.get(group,0)+1
for w,h in [(1,1),(3,5),(16,16),(31,29),(64,48),(96,80),(127,127),(256,256)]:
    plane=blit.visible_alpha(w,h)
    add('visible_alpha_constructor',['V',w,h],[words(plane)])
# Actual double conversion, including representable neighbors on both sides
# of decimal boundaries. All downstream integer settings are explicit.
values=[0.,1.,-1.,.6,.032,10.,-10.]
for n in range(-256,257):
    v=n/100;values.extend([math.nextafter(v,-math.inf),v,math.nextafter(v,math.inf)] if v else [v])
for v in values:
    row=[v,1.,v,-v,v,v];add('ini_quantization',['Q',*row],o.quantize(row),f'quantize {v!r}')
tints=[[1000]*3,[0]*3,[1]*3,[2]*3,[2000]*3,[-1,999,2001],[1001,1000,500],[500,1001,1000],[500,1000,1001]]
for n in range(1500):tints.append([rng.randrange(-400,2401) for _ in range(3)])
for i,t in enumerate(tints):
    brightness=[-5000,-1,0,1,728,1000,2000,2001,20000][i%9]
    add('normalization',['N',brightness,*t],o.normalize(brightness,t),f'normalize {brightness}/{t}')
raw=[59,100,100,100,0,32]
# All elevations, height/Ground branches, tint ties and neutral sentinels.
cells=[]
for z in range(32):
    for s in [raw,[100,80,100,60,500,32],[100,100,80,60,-250,50],[100,60,80,100,500,-32],[0,0,0,0,0,0],[200,200,200,200,0,0]]:
        cells.append((s,33,86,z,[],0))
for x,y in [(0,0),(-1,-1),(0,1),(1,0),(-1,0),(1023,1023)]:cells.append((raw,x,y,4,[],0))
# Radial boundary, inactive/future sources, negative tints, ordered overlaps,
# differing source Z (original falloff ignores height), sqrt-table cases.
for i in range(640):
    x,y=33,86;radius=[1,128,256,1024,2048,5000,32767][i%7];sources=[]
    for j in range(1+i%8):
        dx=rng.randrange(-4000,4001);dy=rng.randrange(-4000,4001)
        if i<32:dx=[0,radius-1,radius,radius+1][i%4];dy=0
        sources.append([x*256+128+dx,y*256+128+dy,rng.randrange(-4096,4097),radius,rng.randrange(-1000,2001),*[rng.randrange(-500,1001) for _ in range(3)],int(j%4!=1),[0,9,10,11][j%4]])
    cells.append(([rng.randrange(201),*[rng.randrange(201) for _ in range(3)],rng.randrange(-500,501),rng.randrange(-50,101)],x,y,i%32,sources,10))
for s,x,y,z,sources,clock in cells:
    fields=[*s,x,y,z,clock,len(sources),*[v for source in sources for v in source]]
    add('cell_lighting',['C',*fields],o.cell(s,x,y,z,sources,clock),f'cell {x}/{y}/{z}: {s} sources={len(sources)}')
# Real supplied map [Lighting] numeric values and cells are supplied inputs,
# not a claim that the original INI parser/map constructor was executed.
section=False;settings={};maptext=(assets/'mp03t4.map').read_text()
for line in maptext.splitlines():
    line=line.strip()
    if line.startswith('['):section=line.lower()=='[lighting]'
    elif section and '=' in line:
        k,v=line.split('=',1);settings[k.lower()]=float(v)
mapvalues=[settings.get(k,d) for k,d in zip(['ambient','red','green','blue','ground','level'],[1,1,1,1,0,0])]
mapraw=o.quantize(mapvalues)
# Use the native asset reader only to obtain explicit cell coordinates;
# original execution independently calculates every resulting light output.
cellrows=subprocess.check_output([str(a.native),'--cells',str(assets/'mp03t4.map')],text=True)
for row in cellrows.splitlines():
    x,y,z=map(int,row.split())
    add('owned_map_cells',['C',*mapraw,x,y,z,0,0],o.cell(mapraw,x,y,z),f'owned map {x},{y},{z}')
# End-to-end complete planes with independently executed original palette
# and final surface copy; explicit sources/visibility/actor placement.
palettes=[[v<<2 for v in (assets/n).read_bytes()] for n in ['isotem.pal','unittem.pal']]
for i in range(96):
    s,x,y,z,sources,clock=cells[(i*7)%len(cells)];r=o.cell(s,x,y,z,sources,clock)
    pal=palettes[i%2];table=o.palette(53,r[5:],pal,[1]*256)
    w,h,sw,sh=40,32,21,17;src=[rng.randrange(256) if n%7 else 0 for n in range(sw*sh)]
    colors=[rng.randrange(65536) for _ in range(w*h)];depth=[rng.choice([0,32730,32760,32767,32768,65535]) for _ in colors]
    alpha=[127 if i%3==0 else rng.randrange(256) for _ in colors]
    box=[1,2,18,14];at=[rng.randrange(-12,38),rng.randrange(-10,30)];clip=[0,0,w,h] if i%2 else [3,5,30,23];adjust=-1-z*15
    c,d=blit.final_blit(w,h,src,sw,sh,box,at,clip,adjust,r[3],colors,depth,alpha,table)
    add('lit_surfaces',['B',*s,x,y,z,clock,len(sources),*[v for source in sources for v in source],w,h,sw,sh,*box,*at,*clip,adjust,*pal,*src,*colors,*depth,*alpha],[words(c),words(d)],f'lit surface {i}')
report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'seed':0x52413130,
        'owned_map_values':mapvalues,'owned_map_integers':mapraw,'original_instructions_modified':False,
        'fixture_services':{'flat cell coordinate/height getter':o.getter_calls},'surface_fixture_services':blit.counts,
        'audited_callable_roots':o.audit_calls+blit.audit_calls,'audited_blocks':o.audit_blocks+blit.audit_blocks,
        'guarded_allocations':len(blit.allocations),
        'scope':'Actual map-loader numeric blocks, complete normalization/ordinary cell lighting with explicit sources, and visible-alpha constructor. Combined scalar palette/final surface copy has explicit source/visibility/placement. Bounded caller/input/write audits exclude ordered native-original writes, INI parsing, full actor/source/house/visibility/lifetime and full-frame parity.'}
actual=run_native(a,commands)
if len(actual)!=len(expected):raise AssertionError(f'Result count {len(actual)}/{len(expected)}')
for i,(label,x,y) in enumerate(zip(labels,actual,expected)):
    if x!=y:raise AssertionError(f'{i}: {label}: native {x[:10]}, original {y[:10]}')
report['cases']=len(commands)
# Recheck identities after both original and native execution.
report.update(identities(a,engine_digest,engine_profile,native_data))
save(a,work,commands,expected,labels,report)
print(f'{engine_profile}: {len(commands):,} original/native map-light results: PASS; {groups}')
