#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare indexed staging, assembled RGB565 surfaces and shadow cache decisions."""
import argparse,hashlib,random,struct
from pathlib import Path
from staging_evidence import prepare, identities, save, replay, run_native

def hashbytes(b):return hashlib.sha256(bytes(b)).hexdigest()
def hashwords(v):return hashbytes(struct.pack('<'+'H'*len(v),*v))
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True);p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--native',type=Path,default=Path('build/native/staging-vectors'))
p.add_argument('--raster-data',type=Path,default=Path('private/derived/raster-data.bin'));p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path);p.add_argument('--expectations',type=Path)
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
p.add_argument('--raster-exporter',type=Path,default=Path('build/native/raster-vectors'))
a=p.parse_args();engine_digest,engine_profile,native_data,work=prepare(a)
if a.expectations:
 replay(a,engine_digest,engine_profile,native_data,work)
 raise SystemExit(0)
from original_staging import ShadowDispatchOracle
o=ShadowDispatchOracle(a.exe,allow_patched=True);rng=random.Random(0x524139);out=a.assets
commands=[];expected=[];labels=[];groups={}
def add(group,values,result,label=''):
 commands.append(' '.join(map(str,values)));expected.append(list(map(str,result)));labels.append(label or group);groups[group]=groups.get(group,0)+1
iso=[b<<2 for b in (out/'temperat.pal').read_bytes()]
# Duplicate and equidistant colors, source zero, distinct source/dest palettes.
palettes=[(iso,iso),([0]*768,[0]*768),([255]*768,[255]*768)]
for i in range(9):
 x=[rng.randrange(256) for _ in range(768)];y=x[:] if i%2 else [rng.randrange(256) for _ in range(768)]
 y[96:99]=y[45:48];x[99:102]=[1,1,1];y[0:6]=[0,1,1,2,1,1];palettes.append((x,y))
for i,(x,y) in enumerate(palettes):add('converters',['P',*x,*y],o.indexed_converter(x,y),f'converter {i}')
remap=o.indexed_converter(iso,iso)
boundaries=[([0,0,0,0],[128,128,10,10]),([128,128,10,10],[138,138,1,1]),([128,128,10,10],[128,128,10,10]),([128,128,10,10],[126,126,10,10]),([0,0,-1,12],[0,0,0,0]),([2,3,5,6],[1,1,0,8])]
for i in range(512):boundaries.append(([rng.randrange(-100,150),rng.randrange(-100,150),rng.randrange(-2,100),rng.randrange(-2,100)],[rng.randrange(-100,150),rng.randrange(-100,150),rng.randrange(-2,100),rng.randrange(-2,100)]))
for x,y in boundaries:add('dirty_unions',['U',*x,*y],o.dirty(x,y),f'union {x}/{y}')
for i in range(128):
 w,h,sw,sh=48,40,21,17;src=[rng.randrange(256) for _ in range(sw*sh)];target=[rng.randrange(256) for _ in range(w*h)]
 box=[rng.randrange(-3,5),rng.randrange(-3,5),rng.randrange(8,29),rng.randrange(8,23)];loc=[rng.randrange(-12,44),rng.randrange(-10,37)];clip=[0,0,w,h] if i%3==0 else [3,5,38,29]
 # Explicit maps test nonzero -> zero; original blitter selected by constructor.
 mapping=bytes((n*13+i)%256 for n in range(256)) if i%2 else remap
 ptr=struct.unpack('<I',o.u.mem_read(o.index_blitter+4,4))[0];o.u.mem_write(ptr,mapping)
 b=o.indexed_blit(w,h,src,sw,sh,box,loc,clip,target)
 add('indexed_blits',['I',w,h,sw,sh,*box,*loc,*clip,*src,*target,*mapping],[hashbytes(b)])
palette=[(s<<8)|i for s in range(53) for i in range(256)]
for i in range(128):
 w,h,sw,sh=48,40,21,17;src=[rng.randrange(256) for _ in range(sw*sh)];colors=[rng.randrange(65536) for _ in range(w*h)]
 depth=[rng.choice([65535,0,32720,32721,32722,32730,32760,32767,32768]) for _ in colors];alpha=[rng.randrange(256) for _ in colors]
 box=[rng.randrange(-3,5),rng.randrange(-3,5),rng.randrange(8,29),rng.randrange(8,23)];loc=[rng.randrange(-12,44),rng.randrange(-10,37)];clip=[0,0,w,h] if i%3==0 else [3,5,38,29];z=rng.choice([-1,-60,-105,15,-65536,65536]);bri=rng.choice([0,500,1000,2000])
 c,d=o.final_blit(w,h,src,sw,sh,box,loc,clip,z,bri,colors,depth,alpha,palette);assert d==depth
 add('final_surface_blits',['F',w,h,sw,sh,*box,*loc,*clip,z,bri,*src,*colors,*depth,*alpha,*palette],[hashwords(c),hashwords(d)])
models=[o.load(out/n) for n in ['htnk.vxl','htnktur.vxl','htnkbarl.vxl']];vpl=(out/'voxels.vpl').read_bytes()
mapping=o.indexed_converter(iso,iso)
for i in range(64):
 bh=(i%32)*2048;th=(i*6144+1023*(i//32))&65535
 matrices,_,_=o.matrices(bh,th);body,turret,cam=matrices;frames=[]
 for j,model in enumerate(models):
  pose=o.multiply(cam,body if j==0 else turret);frames.append(o.draw(model,pose,vpl,o.shades(model,pose)))
 stage=bytes(65536);dirty=[0,0,0,0];order=[0,1,2] if o.order(th) else [0,2,1]
 for j in order:
  pixels,meta=frames[j];b=meta[:6];at=[128+b[0],128+b[1]]
  stage=o.indexed_blit(256,256,pixels,256,256,b[2:6],at,[0,0,256,256],stage);dirty=o.dirty(dirty,[*at,*b[4:6]])
 bits=o.offset(0.7853981852531433);offset=struct.unpack('<3f',struct.pack('<3I',*bits));sh,sb=o.staged_shadow(models[0],body,cam,offset,stage)
 for profile in [0,1]:
  w,h=96,80;colors=[(n*71)&65535 for n in range(w*h)];depth=[32700+n%99 if profile else 65535 for n in range(w*h)];alpha=[n%256 for n in range(w*h)];clip=[3,5,80,64] if profile else [0,0,w,h]
  c,d=o.final_blit(w,h,stage,256,256,dirty,[48+dirty[0]-128,50+dirty[1]-128],clip,-1,1000,colors,depth,alpha,palette)
  c,d=o.shadow_blit(w,h,sh,256,256,sb[2:6],[48+sb[0],50+sb[1]],clip,-1,c,d)
  add('assembled_units',['A',out,bh,th,profile],[*dirty,hashbytes(stage),hashbytes(sh),hashwords(c),hashwords(d)],f'assembled {bh}/{th}/{profile}')
 buffer=work/f'stage-{i}.bin'
 if buffer.exists() and buffer.read_bytes()!=stage:raise ValueError('Different original staging buffer already exists')
 if not buffer.exists():buffer.write_bytes(stage)
cache_services_before=dict(o.counts);o.counts.clear()
for scenario in range(3):
 o.begin_cache();add('cache_resets',['N'],['reset'])
 keys=[2,2,1,1,2,-1,-2,2147483647,-2147483648]+list(range(40,-1,-1))
 cases=[[k,0,0,0,1,0,1] for k in keys]
 cases += [[rng.choice(keys),rng.randrange(2),rng.randrange(2),rng.randrange(2),rng.randrange(2),rng.randrange(2),rng.randrange(2)] for _ in range(512)]
 for c in cases:
  events=o.dispatch(*c);flat=[v for row in events for v in row];add('shadow_dispatch',['K',*c],flat,f'cache scenario {scenario}: {c}')
actual=run_native(a,commands)
if len(actual)!=len(expected):raise AssertionError(f'Wrong result count {len(actual)}/{len(expected)}')
for i,(label,x,y) in enumerate(zip(labels,actual,expected)):
 if x!=y:raise AssertionError(f'Case {i} {label}: {[(n,xx,yy) for n,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:12]}, lengths {len(x)}/{len(y)}')
report={**identities(a,engine_digest,engine_profile,native_data),'groups':groups,'cases':len(commands),
        'audited_callable_roots':o.audit_calls,'audited_blocks':o.audit_blocks,'guarded_allocations':len(o.allocations),
        'original_instructions_modified':False,'pre_cache_services':cache_services_before,'cache_allocator_services':o.counts,
        'scope':'Complete one-shade Convert, selected byte-blitter initialization, transparent indexed blit, dirty-union block, complete final surface copy, assembled stock parts/staged shadow/world surfaces. Full successful shadow wrapper/index decisions with supplied type getter, render/snapshot/cached-blit services and allocator. Bounded caller/input/write audits are not ordered native-original writes, original pool/eviction/allocation failure, full actor or full-frame parity.'}
save(a,work,commands,expected,labels,report)
print(f'{engine_profile}: {len(commands)} original/native staging and shadow-dispatch results: PASS; {groups}')
