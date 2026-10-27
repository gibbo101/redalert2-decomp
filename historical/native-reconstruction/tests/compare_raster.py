#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare original voxel pose matrices and complete indexed section buffers."""
import argparse,hashlib,json,random,struct,subprocess
from pathlib import Path
from original_raster import RasterOracle
from raster_evidence import prepare, identities, save, replay, run_native
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('--exe',type=Path,required=True)
p.add_argument('--data-dir',type=Path,default=Path('private/game'))
p.add_argument('--native',type=Path,default=Path('build/native/raster-vectors'))
p.add_argument('--raster-data',type=Path,default=Path('private/derived/raster-data.bin'))
p.add_argument('--render-data',type=Path,default=Path('private/derived/render-data.bin'))
p.add_argument('--report',type=Path)
p.add_argument('--expectations',type=Path,help='Identity-checked native replay; no original execution')
p.add_argument('--native-data-exe',type=Path,help='Explicit retained disc identity; required for patched research')
a=p.parse_args();digest,profile,native_data,evidence_dir=prepare(a)
if a.expectations:
    replay(a,digest,profile,native_data,evidence_dir)
    raise SystemExit(0)
o=RasterOracle(a.exe,allow_patched=True);out=a.assets
vpl=(out/'voxels.vpl').read_bytes();models=[o.load(out/n) for n in ['htnk.vxl','htnktur.vxl','htnkbarl.vxl']]
loader_services=dict(o.counts);o.counts.clear();commands=[];expected=[];labels=[];frames=0;poses=0;walks=set()
for name,model in zip(['htnk.vxl','htnktur.vxl','htnkbarl.vxl'],models):
    commands.append(f'L {out/name}');expected.append(o.metadata(model));labels.append('loader '+name)
rng=random.Random(0x524136)
headings=sorted({(n*2048+d)&65535 for n in range(32) for d in [-1025,-1024,-1023,0,1023,1024,1025]})
for heading in headings:
    turret=rng.randrange(65536);ms,words,cache=o.matrices(heading,turret)
    assert cache==(((heading>>10)+1)>>1)&31
    commands.append(f'M {heading} {turret}');expected.append(list(map(str,words)));labels.append(f'pose {heading}/{turret}');poses+=1
for part,(name,model) in enumerate(zip(['htnk.vxl','htnktur.vxl','htnkbarl.vxl'],models)):
    for n in range(64):
        body=(n*2048)&65535;turret=(body+8192)&65535
        ms,_,_=o.matrices(body,turret);matrix=o.multiply(ms[2],ms[0 if part==0 else 1])
        commands.append('P '+' '.join(map(str,[*ms[2],*ms[0 if part==0 else 1]])))
        expected.append(list(map(str,struct.unpack('<12I',struct.pack('<12f',*matrix)))));labels.append('camera/pose multiply')
        if n>=32:
            # Reverse-view octants and fractional translation.
            matrix=list(matrix);matrix[8:12]=[-v for v in matrix[8:12]];matrix[3]=0.375;matrix[7]=-0.625
        shades=o.shades(model,matrix)
        commands.append('S '+' '.join(map(str,[4 if part==2 else 2,*matrix])));expected.append(list(map(str,shades)));labels.append(f'lighting {name}, heading {body}, reversed={n>=32}')
        pixels,meta=o.draw(model,matrix,vpl,shades);walks.add(meta[6]);frame_digest=hashlib.sha256(pixels).hexdigest()
        commands.append('D '+' '.join(map(str,[str(out/name),str(out/'voxels.vpl'),*matrix,*shades])))
        expected.append([*map(str,meta),frame_digest]);labels.append(f'{name} heading {body}, reversed={n>=32}');frames+=1
        (evidence_dir/f'original-{part}-{n}.bin').write_bytes(pixels)
actual=run_native(a,commands)
assert len(actual)==len(expected)
for label,x,y in zip(labels,actual,expected):
    if x!=y:raise AssertionError(f'{label}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:12]}')
assert not o.counts,'Unexpected service callback during pose/render execution'
assert walks==set(range(8)),f'Incomplete traversal coverage: {walks}'
report={**identities(a,digest,profile,native_data),'loader_cases':3,'pose_cases':poses,
        'matrix_products':frames,'lighting_setups':frames,'indexed_frames':frames,'cases':len(actual),
        'pixels_per_frame':65536,'traversals':sorted(walks),'original_instructions_modified':False,
        'loader_services':loader_services,'render_services':o.counts,
        'audited_callable_roots':o.audit_calls,'audited_blocks':o.audit_blocks,
        'heap_allocations':len(o.allocations),'loader_canaries_preserved':True,
        'scope':'Stock successful single-section loader metadata/spans, flat Drive pose, relative zero-offset turret, original camera and complete lit indexed buffers. No optional embedded palette, whole actor/frame, composition or cache-lifetime parity.'}
save(a,evidence_dir,commands,expected,labels,report)
print(f'{profile}: 3 loader results, {poses} pose cases, {frames} matrix products/lighting setups/complete indexed buffers: PASS')
