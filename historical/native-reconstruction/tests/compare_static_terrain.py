#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Verify unchanged supplied-1.006 reverse static Terrain traversal/eligibility."""
import argparse
import itertools
import json
from pathlib import Path
import random
import struct
import sys
import time
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
sys.path.insert(0,str(ROOT/'tools'))
from verify_static_terrain import verify
SOURCES=('tests/compare_static_terrain.py','tests/original_static_terrain.py',
         'tests/compare_terrain_visibility.py','tests/original_terrain_visibility.py',
         'tests/original_presentation.py','tests/presentation_profiles.py','tests/compare_original.py',
         'tests/presentation_evidence.py','tools/verify_terrain_visibility.py','tools/verify_static_terrain.py',
         'src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp','src/render/StaticTerrainTraversal.hpp',
         'src/render/StaticTerrainTraversal.cpp','tests/static_terrain_vectors.cpp')
def identities(exe,asset_dir):
    paths=[*sorted(asset_dir.glob('*.tem')),asset_dir/'mp03t4.map',asset_dir/'rules.ini']
    if len(paths)!=53:raise ValueError('Require 51 ordinary images and original map/rules fixture inputs')
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','inspection':verify(exe.read_bytes()),
            'sources':{p:hash_file(ROOT/p) for p in SOURCES},'assets':{str(p.resolve()):hash_file(p) for p in paths}}
def validate(evidence,receipt,fingerprint,current):
    validate_receipt(evidence,receipt,fingerprint)
    if evidence.get('executable_sha256')!=PATCHED_EXPECTED or evidence.get('profile')!='supplied-ra2-1006':
        raise ValueError('Static traversal engine/profile differs')
    if evidence['evidence'].get('identities')!=current:raise ValueError('Static traversal source/asset identity differs')
    if not(len(evidence['commands'])==len(evidence['expected'])==len(evidence['labels'])):
        raise ValueError('Static traversal vector counts differ')
def section(text,name):
    result={};active=False
    for line in text.splitlines():
        line=line.split(';',1)[0].strip()
        if line.startswith('['):active=line.lower()=='['+name.lower()+']'
        elif active and '=' in line:
            k,v=line.split('=',1);result[k.strip().lower()]=v.strip()
    return result
def generate(exe,assets):
    from original_static_terrain import StaticTerrainOracle
    oracle=StaticTerrainOracle(exe);rng=random.Random(0x52413231)
    commands=[];expected=[];labels=[];groups={}
    def scan(group,actors,layer,force=1,bypass=0,context=1,dirty=(0,0,96,88),clip=(0,0,96,88),viewport=(0,0,96,88)):
        tokens=[len(actors),len(layer),force,bypass,context,*dirty,*clip,*viewport,*[v for a in actors for v in a],*layer]
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,oracle.scan(actors,layer,force,bypass,context,dirty,clip,viewport))))
        labels.append(group);groups[group]=groups.get(group,0)+1
    def actor(alive=1,animated=0,crumbling=0,on_map=1,redraw=1,limbo=0,shape=(20,20,30,30)):
        return (0x24,alive,animated,crumbling,on_map,redraw,limbo,*shape,18304,29312,416,46,47)
    for flags in itertools.product([0,1,255],repeat=6):
        for force in [0,1,256]:scan('complete_static_gates_and_redundant_clear',[actor(*flags)],[0],force)
    edges=[-2147483648,-2147483647,-32768,-1,0,1,32767,2147483646,2147483647]
    sizes=[-2147483648,-1,0,1,2,60,100,2147483647]
    for n in range(1024):
        actors=[]
        for id in range(8):
            shape=[rng.randrange(-80,160),rng.randrange(-80,160),rng.randrange(-1,100),rng.randrange(-1,100)]
            a=list(actor(*[rng.choice([0,1,255]) for _ in range(6)],shape=shape))
            a[0]=rng.choice([0x24,0x24,6,4,39]);actors.append(a)
        layer=[rng.randrange(8) for _ in range(rng.randrange(14))]
        dirty=[rng.randrange(-40,80),rng.randrange(-40,80),rng.randrange(-1,120),rng.randrange(-1,120)]
        clip=[7,9,73,65] if n%3 else [0,0,96,88];viewport=[0,0,96,88]
        if n%4==0:
            dirty=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
            clip=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
            viewport=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
            for a in actors:a[7:11]=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
        scan('reverse_duplicates_filters_clip_wrap_and_state',actors,layer,rng.choice([0,1,255,256,257]),
             rng.choice([0,1,255]),rng.randrange(2),dirty,clip,viewport)
    scan('empty_layer',[],[])
    for n in range(64):
        actors=[actor() for _ in range(8)];layer=list(range(8));rng.shuffle(layer)
        scan('equal_bounds_order_is_exact_reverse',actors,layer,n%2)
    rules=(assets/'rules.ini').read_text();images={}
    for path in sorted(assets.glob('*.tem')):
        blob=path.read_bytes();w,h,count=struct.unpack_from('<3H',blob,2)
        assert count==2 and section(rules,path.stem).get('isanimated','no').lower() in ('no','false','0')
        images[path.stem]=(w,h,[struct.unpack_from('<4H',blob,8+24*i) for i in range(count)])
    placements=[(int(k)%1000,int(k)//1000,v.lower()) for k,v in section((assets/'mp03t4.map').read_text(),'Terrain').items() if v.lower() in images]
    assert len(placements)==565
    layer=sorted(range(len(placements)),key=lambda id:sum(placements[id][:2]))
    # Original map placement/order inputs, supplied flat world/screens. This
    # verifies the visitor, not elevation/projection or the map decoder.
    for n in range(16):
        cx,cy,_=placements[n*31];origin=((cx-cy)*30-128,(cx+cy)*15-96);actors=[]
        for x,y,type in placements:
            screen=((x-y)*30,(x+y)*15);shape=oracle.bounds(screen,origin,images[type])
            actors.append((0x24,1,0,0,1,1,0,*shape,x*256+128,y*256+128,0,screen[0]-origin[0],screen[1]-origin[1]))
        scan('whole_565_placement_reverse_static_scan',actors,layer,dirty=(0,0,256,192),clip=(0,0,256,192),viewport=(0,0,256,192))
    return commands,expected,labels,groups,oracle.audit_calls
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/static-terrain-vectors')
    p.add_argument('--asset-dir',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/terrain-types/assets')
    p.add_argument('--output',type=Path,default=ROOT/'private/traversal-1006/static')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
    a=p.parse_args();start=time.monotonic();current=identities(a.exe,a.asset_dir);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        evidence=json.loads(source.read_text());validate(evidence,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[evidence[k] for k in ('commands','expected','labels')];metadata=evidence['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh original static evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls=generate(a.exe,a.asset_dir);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'seed':0x52413231,
                  'scope':'Complete static Terrain reverse region scan, actual alive predicate, complete nested eligibility and coordinate getters. Nonterrain type IDs, dimensions, projection/final draw are services. Ordered actor visits, callbacks and external redraw/bounds writes, whole configured fixture arenas/tails, caller ESP/return/register/permitted writes. Map fixture screens are flat/supplied; no dynamic traversal, invalidation scheduling, surfaces or whole-frame parity.'}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(commands)==len(labels)):raise AssertionError('Static vector count differs')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:
            at=next((i for i,(a,b) in enumerate(zip(x,y)) if a!=b),min(len(x),len(y)))
            raise AssertionError(f'{n} {labels[n]} token {at}: native {x[max(0,at-5):at+15]}, original {y[max(0,at-5):at+15]}')
    if identities(a.exe,a.asset_dir)!=current or hash_file(a.native)!=runner:raise ValueError('Run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 static Terrain traversal results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
