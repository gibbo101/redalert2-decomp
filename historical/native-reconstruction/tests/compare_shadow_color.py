#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare base-RA2 HSV/remapping and complete shadow masks/surfaces."""
import argparse,hashlib,random,struct
from pathlib import Path
from shadow_color_evidence import prepare, identities, save, replay, run_native

def words_digest(values):return hashlib.sha256(struct.pack('<'+'H'*len(values),*values)).hexdigest()
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True);p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--native',type=Path,default=Path('build/native/shadow-color-vectors'))
p.add_argument('--raster-data',type=Path,default=Path('private/derived/raster-data.bin'))
p.add_argument('--report',type=Path)
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
p.add_argument('--raster-exporter',type=Path,default=Path('build/native/raster-vectors'))
p.add_argument('--expectations',type=Path,help='Replay previously generated original results without Unicorn')
a=p.parse_args();engine_digest,profile,native_data,work=prepare(a)
if a.expectations:
    replay(a,engine_digest,profile,native_data,work)
    raise SystemExit(0)
from original_shadow_color import ShadowColorOracle
o=ShadowColorOracle(a.exe,allow_patched=True);out=a.assets
models=[o.load(out/n) for n in ['htnk.vxl','htnktur.vxl','htnkbarl.vxl']]
loader_services=dict(o.counts);o.counts.clear()
commands=[];expected=[];labels=[];groups={};rng=random.Random(0x524138)
def add(group,command,result,label=''):
    commands.append(command);expected.append(list(map(str,result)));labels.append(label or group);groups[group]=groups.get(group,0)+1
for hue in range(256):
    for sat in [0,1,127,254,255]:
        for val in [0,1,128,254,255]:
            hsv=[hue,sat,val];add('hsv','H '+' '.join(map(str,hsv)),o.hsv(hsv),f'HSV {hsv}')
for _ in range(512):
    hsv=[rng.randrange(256) for _ in range(3)];add('hsv','H '+' '.join(map(str,hsv)),o.hsv(hsv),f'HSV {hsv}')
raw=(out/'unittem.pal').read_bytes();palette=[b<<2 for b in raw]
stock=[];in_colors=False
for line in (out/'rules.ini').read_text(encoding='latin1').splitlines():
    line=line.split(';')[0].strip()
    if line.startswith('['):in_colors=line.lower()=='[colors]';continue
    if in_colors and '=' in line:
        name,value=line.split('=',1);hsv=[int(v.strip()) for v in value.split(',')];stock.append((name,hsv))
cases=[(f'ramp {h}/{s}/{v}',[h,s,v]) for h in range(256) for s in [0,128,255] for v in [0,128,255]]+stock
for name,hsv in cases:
    values=o.remap(hsv,palette)
    assert values[:48]==palette[:48] and values[96:]==palette[96:]
    add('remaps','C '+' '.join(map(str,[*hsv,out/'unittem.pal'])),values,name)
for angle in [0,0.19634954631328583,0.7853981852531433,-0.7853981852531433,1.5707963705062866,3.1415927410125732]+[rng.uniform(-3,3) for _ in range(58)]:
    angle=struct.unpack('<f',struct.pack('<f',angle))[0];add('offsets',f'O {angle}',o.offset(angle))
headings=sorted({(n*2048+d)&65535 for n in range(32) for d in [-1024,-1023,0,1023,1024]})
for h in headings:add('shadow_poses',f'M {h}',o.shadow_pose(h))
for part,model in enumerate(models):
    path=out/['htnk.vxl','htnktur.vxl','htnkbarl.vxl'][part]
    for heading in range(32):
        matrices,_,_=o.matrices(heading*2048,(heading*2048+8192)&65535)
        pose=list(matrices[0 if part==0 else 1]);camera=list(matrices[2])
        # Identity-HVA stock parts, plus fractional camera/model translations.
        if heading%2:pose[3]=0.375;pose[7]=-0.625;camera[3]=0.25;camera[7]=-0.5
        bits=o.offset(0.7853981852531433);offset=struct.unpack('<3f',struct.pack('<3I',*bits))
        for style,x,y in [(-1,0,0),(0,0,0),(3,-64 if heading%2 else 32,-48 if heading%2 else 24)]:
            try:pixels,meta=o.shadow(model,pose,camera,offset,style,x,y)
            except Exception as error:raise RuntimeError(f'Original shadow part={part} heading={heading} stencil={style}/{x}/{y}') from error
            add('shadow_masks','R '+' '.join(map(str,[path,*pose,*camera,*offset,style,x,y])),[*meta,hashlib.sha256(pixels).hexdigest()],f'shadow part {part} heading {heading} stencil {style}/{x}/{y}')
            buffer=work/f'original-{part}-{heading}-{style}.bin'
            if buffer.exists() and buffer.read_bytes()!=pixels:raise ValueError('Different original buffer already exists')
            if not buffer.exists():buffer.write_bytes(pixels)
for i in range(97):
    w,h,sw,sh=(256,256,256,256) if i==96 else (48,40,21,17)
    source=[1]*(sw*sh) if i==96 else [0 if rng.randrange(5)==0 else rng.randrange(1,256) for _ in range(sw*sh)]
    colors=list(range(65536)) if i==96 else [rng.randrange(65536) for _ in range(w*h)]
    depth=[65535]*(w*h) if i==96 else [rng.choice([65535,0,32720,32721,32722,32730,32760,32767,32768]) for _ in range(w*h)]
    srcbox=[0,0,sw,sh] if i==96 else [rng.randrange(-3,5),rng.randrange(-3,5),rng.randrange(10,29),rng.randrange(8,23)]
    loc=[0,0] if i==96 else [rng.randrange(-12,44),rng.randrange(-10,37)]
    clip=[0,0,w,h] if i==96 else ([0,0,w,h] if i%3==0 else [3,5,38,29])
    z=0 if i==96 else rng.choice([-1,-60,-105,15,-65536,65536])
    c,d=o.shadow_blit(w,h,source,sw,sh,srcbox,loc,clip,z,colors,depth)
    assert d==depth
    if i==96:assert c==[(x>>1)&0x7bef for x in colors]
    add('shadow_blits','B '+' '.join(map(str,[w,h,sw,sh,*srcbox,*loc,*clip,z,*source,*colors,*depth])),[words_digest(c),words_digest(d)])
assert not o.counts,'Unexpected loader/allocator services during rendering'
actual=run_native(a,commands)
if len(actual)!=len(expected):raise AssertionError(f'Wrong result count {len(actual)}/{len(expected)}')
for label,x,y in zip(labels,actual,expected):
    if x!=y:raise AssertionError(f'{label}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:12]}')
report={**identities(a,engine_digest,profile,native_data),'groups':groups,'cases':len(commands),
        'audited_callable_roots':o.audit_calls,'audited_blocks':o.audit_blocks,
        'guarded_allocations':len(o.allocations),'original_instructions_modified':False,
        'loader_services':loader_services,'render_services':o.counts,
        'flat_pose_service':'hash-selected Map getter returns a supplied ramp-zero cell',
        'scope':'HSV; ColorScheme copy/remap prefix with open-frame audit; full initializer/flat shadow pose; light offset; single-section occupied-column masks with explicit BSurface stencils; complete clipped RGB565 shadow Z-read surfaces. Bounded caller/input/write audits are not ordered native-original write, full actor, cache or full-frame parity.'}
save(a,work,commands,expected,labels,report)
print(f'{profile}: {len(commands)} original/native shadow and player-color cases: PASS; {groups}')
