#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-1.006 rectangle, Terrain bounds and draw-eligibility vectors."""
import argparse
import itertools
import json
from pathlib import Path
import random
import struct
import subprocess
import sys
import time
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from verify_terrain_visibility import verify

SOURCES=('tests/original_terrain_visibility.py','tests/compare_terrain_visibility.py',
         'tests/original_presentation.py','tests/presentation_profiles.py','tests/compare_original.py',
         'tests/presentation_evidence.py','tools/verify_terrain_visibility.py')
NATIVE=('src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp',
        'src/render/Composition.hpp','src/assets/Shp.hpp','src/sim/TerrainOccupation.hpp',
        'tests/terrain_visibility_vectors.cpp')
def identities(exe,asset_dir):
    result=verify(exe.read_bytes())
    assets={str(p.resolve()):hash_file(p) for p in sorted(asset_dir.glob('*.tem'))}
    if len(assets)!=51:raise ValueError('Require all 51 retained ordinary tree/prop assets')
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'sources':{p:hash_file(ROOT/p) for p in (*SOURCES,*NATIVE)},
            'assets':assets,'inspection':result}
def validate(evidence,receipt,fingerprint,current):
    validate_receipt(evidence,receipt,fingerprint)
    if evidence.get('executable_sha256')!=PATCHED_EXPECTED or evidence.get('profile')!='supplied-ra2-1006':
        raise ValueError('Cached visibility engine/profile differs')
    if evidence['evidence'].get('identities')!=current:raise ValueError('Cached visibility source/asset/inspection identity differs')
    if not(len(evidence['commands'])==len(evidence['expected'])==len(evidence['labels'])):
        raise ValueError('Cached visibility vector counts differ')
def native(path,commands):
    proc=subprocess.run([str(path)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    return [line.split() for line in proc.stdout.splitlines()]
def generate(exe,assets):
    # Importing the JIT oracle is restricted to fresh runs; replay needs no Unicorn.
    from original_terrain_visibility import TerrainVisibilityOracle
    oracle=TerrainVisibilityOracle(exe);rng=random.Random(0x52413230)
    commands=[];expected=[];labels=[];groups={}
    def add(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    edges=[-2147483648,-2147483647,-32768,-257,-1,0,1,255,32767,2147483646,2147483647]
    sizes=[-2147483648,-1,0,1,2,17,100,2147483647]
    for n in range(3072):
        a=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
        b=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
        if n%3==0:
            a=[rng.randrange(-100,100),rng.randrange(-100,100),rng.randrange(1,100),rng.randrange(1,100)]
            b=[a[0]+rng.randrange(-30,30),a[1]+rng.randrange(-30,30),rng.randrange(1,100),rng.randrange(1,100)]
        x,y=rng.choice(edges),rng.choice(edges);mask=n%4
        add('rectangle_signed_wrap_and_adjustments',['I',*a,*b,mask,x,y],oracle.intersection(a,b,mask,x,y))
    for side,extent in itertools.product([-1,0,1,9,10,11],[-1,0,1,10]):
        a=[0,0,10,10];b=[side,side,extent,extent]
        add('rectangle_touching_empty_and_exact',['I',*a,*b,3,17,-53],oracle.intersection(a,b,3,17,-53))
    def bounds(group,screen,origin,image):
        tokens=[-1] if image is None else [len(image[2]),image[0],image[1],*[v for f in image[2] for v in f]]
        add(group,['B',*screen,*origin,*tokens],oracle.bounds(screen,origin,image))
    images=[]
    for path in assets:
        data=path.read_bytes();width,height,count=struct.unpack_from('<3H',data,2)
        assert count==2
        frames=[struct.unpack_from('<4H',data,8+24*n) for n in range(count)]
        image=(width,height,frames);images.append(image)
        for n in range(16):
            screen=[rng.choice(edges),rng.choice(edges)];origin=[rng.choice(edges),rng.choice(edges)]
            bounds('owned_tree_prop_body_shadow_bounds',screen,origin,image)
    crops=[0,1,3,20,32767,32768,65535]
    for n in range(1024):
        count=[0,1,2,3,4,6][n%6]
        image=(rng.choice(crops),rng.choice(crops),[tuple(rng.choice(crops) for _ in range(4)) for _ in range(count)])
        bounds('signed_metadata_empty_odd_and_union', [rng.choice(edges),rng.choice(edges)],
               [rng.choice(edges),rng.choice(edges)],image)
    for n in range(12):bounds('null_image_global_empty',[rng.choice(edges),rng.choice(edges)],[3,-7],None)
    def draw(group,state,gate,unused,success,bounds,viewport,shape,projected,coords):
        add(group,['D',*state,*gate,unused,success,*bounds,*viewport,*shape,*projected,*coords],
            oracle.draw(state,gate,unused,success,bounds,viewport,shape,projected,coords))
    for state in itertools.product([0,1,2,255],repeat=3):
        for bypass,context,force in itertools.product([0,1,255],[0,1],[0,1,255,256]):
            draw('complete_redraw_map_limbo_bypass_gates',state,[bypass,context,force],
                 rng.choice(edges),rng.choice([0,1,255]),[0,0,96,88],[0,0,96,88],
                 [20,20,30,30],[46,47],[18304,29312,416])
    for n in range(2048):
        viewport=[rng.randrange(-20,20),rng.randrange(-20,20),96,88]
        bounds=[rng.randrange(-100,150),rng.randrange(-100,150),rng.randrange(-1,150),rng.randrange(-1,150)]
        shape=[rng.randrange(-60,120),rng.randrange(-60,120),rng.randrange(-1,100),rng.randrange(-1,100)]
        if n%4==0:
            bounds=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
            shape=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
            viewport=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
        draw('clipping_strict_overlap_and_projection_result',[1,255,0],[0,1,257],rng.choice(edges),n%2,
             bounds,viewport,shape,[rng.choice(edges),rng.choice(edges)],
             [rng.choice(edges),rng.choice(edges),rng.choice(edges)])
    for image in [None,*images]:
        for n in range(16):
            screen=[rng.randrange(-120,220),rng.randrange(-120,220)];origin=[rng.randrange(-20,20),rng.randrange(-20,20)]
            state=[1,1,0];gate=[0,1,n%2];unused=rng.choice(edges);success=n%2
            clip=[0,0,96,88] if n%3 else [7,9,73,65];viewport=[0,0,96,88]
            shape=[0,0,0,0];projected=[rng.randrange(-120,220),rng.randrange(-120,220)];coords=[18304,29312,416]
            metadata=[-1] if image is None else [len(image[2]),image[0],image[1],*[v for f in image[2] for v in f]]
            add('complete_eligibility_with_actual_owned_image_bounds',
                ['E',*state,*gate,unused,success,*clip,*viewport,*shape,*projected,*coords,*screen,*origin,*metadata],
                oracle.draw(state,gate,unused,success,clip,viewport,shape,projected,coords,(screen,origin,image)))
    return commands,expected,labels,groups,oracle.audit_calls
def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/terrain-visibility-vectors')
    p.add_argument('--asset-dir',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/terrain-types/assets')
    p.add_argument('--output',type=Path,default=ROOT/'private/traversal-1006/visibility')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
    a=p.parse_args();start=time.monotonic();current=identities(a.exe,a.asset_dir);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        evidence=json.loads(source.read_text());validate(evidence,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe)
        check_replay_destination(report,source,receipt)
        commands,expected,labels=[evidence[k] for k in ('commands','expected','labels')]
        metadata=evidence['evidence'];mode='cached-original-replay';generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output, not --report')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh visibility evidence already exists')
        generation_start=time.monotonic()
        commands,expected,labels,groups,calls=generate(a.exe,sorted(a.asset_dir.glob('*.tem')))
        generation=time.monotonic()-generation_start
        metadata={'groups':groups,'audited_callable_roots':calls,'seed':0x52413230,
                  'scope':'Complete rectangle and Terrain bounds; complete eligibility with both supplied dimensions and actual nested owned-image dimensions. Projection/final draw remain supplied. Actual Terrain/type/image/coordinate dispatch executes. Caller/ESP/register, permitted-write, full fixture-arena and ordered external mutation/service audits. No original traversal, final rendering, dynamic invalidation, full actor lifetime or whole-frame parity.'}
        mode='fresh-original';report=out/'report.json'
    compare_start=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-compare_start
    if len(actual)!=len(expected):raise AssertionError('Native result count differs')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe,a.asset_dir)!=current or hash_file(a.native)!=runner:raise ValueError('Run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'identities':current,'native_sha256':runner,'cases':len(commands),'evidence_mode':mode,
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        evidence={'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,
                  'expected':expected,'labels':labels,'evidence':result}
        source=out/'expected.json';write_report(a.exe,source,evidence);fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 Terrain visibility results: PASS ({mode}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
