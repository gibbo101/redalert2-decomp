#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Verify complete patched static requests with nested Terrain traversal/eligibility."""
import argparse
import itertools
import json
from pathlib import Path
import random
import sys
import time
from compare_static_terrain import SOURCES as STATIC_SOURCES
from compare_redraw import validate
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,check_replay_destination
sys.path.insert(0,str(ROOT/'tools'))
from verify_static_redraw import verify
SOURCES=tuple(dict.fromkeys((*STATIC_SOURCES,'tests/compare_redraw.py',
    'tests/compare_static_redraw.py','tests/original_static_redraw.py','tests/static_redraw_vectors.cpp',
    'tools/verify_static_redraw.py','src/render/StaticRedraw.hpp','src/render/StaticRedraw.cpp',
    'src/render/Redraw.hpp','src/sim/TerrainOccupation.hpp',
    'src/render/Composition.hpp','src/render/Composition.cpp','src/sim/OriginalMath.hpp')))
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','inspection':verify(exe.read_bytes()),
            'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def generate(exe):
    from original_static_redraw import StaticRedrawOracle
    o=StaticRedrawOracle(exe);rng=random.Random(0x52413236);commands=[];expected=[];labels=[];groups={}
    def scan(group,cells=(),regions=(),actors=(),full=0,origin=(0,0),viewport=(0,0,320,200),first=(0,0,0,0),second=(0,0,0,0)):
        tokens=[len(cells),len(regions),full,*origin,repr(o.scale),*viewport,*first,*second,
                *[v for p in cells for v in p],*[v for r in regions for v in r],len(actors),*[v for a in actors for v in a]]
        commands.append(' '.join(map(str,tokens)))
        expected.append(list(map(str,o.scan(cells,regions,full,origin,viewport,first,second,actors))))
        labels.append(group);groups[group]=groups.get(group,0)+1
    for full in [0,1,255,256,257,-2147483648,-1]:
        scan('full_low_byte_follows_cells_and_reverse_regions',[(1,1),(2,1)],[(40,20,80,60,0),(2,3,40,50,255)],
             full=full,first=(3,4,5,6),second=(7,8,9,10),viewport=(1,2,320,200))
    for x,y,full in itertools.product([-4097,-4096,-1,0,1,4095,4096],[-4097,-4096,-1,0,1,4095,4096],[0,1]):
        scan('signed_cell_conversion_and_projection',[(x,y)],full=full,origin=(-21,17),viewport=(7,9,100,80))
    for first,second in itertools.product([(1,2,10,10),(0,0,0,1),(0,0,1,0),(-1,-1,-1,-1),(2,3,1,1)],repeat=2):
        scan('edge_extent_filters_and_aliasing',first=first,second=second)
    edges=[-2147483648,-2147483647,-65536,-1,0,1,2,320,2147483646,2147483647]
    def actor(shape=(20,20,30,30),flags=(1,0,0,1,1,0)):
        return [*flags,*shape,18304,29312,416,46,47]
    for i in range(1024):
        viewport=[rng.randrange(-20,20),rng.randrange(-20,20),320,200]
        regions=[(*[rng.randrange(-80,180) for _ in range(2)],rng.randrange(-1,200),rng.randrange(-1,180),rng.choice([0,1,255]))
                 for _ in range(rng.randrange(13))]
        if i%3==0:
            viewport=[rng.choice(edges) for _ in range(4)]
            regions=[(*[rng.choice(edges) for _ in range(4)],rng.choice([0,1,255])) for _ in regions]
        actors=[]
        for n in range(rng.randrange(9)):
            shape=[rng.randrange(-40,400),rng.randrange(-40,250),rng.randrange(-1,100),rng.randrange(-1,100)]
            if i%3==0:shape=[rng.choice(edges) for _ in range(4)]
            actors.append(actor(shape,[rng.choice([0,1,255]) for _ in range(6)]))
        scan('combined_request_order_clip_wrap_gate_and_actor_state',[(rng.randrange(-20,20),rng.randrange(-20,20)) for _ in range(rng.randrange(6))],
             regions,actors,full=rng.choice([0,1,255,256]),origin=(rng.choice(edges),rng.choice(edges)),viewport=viewport,
             first=tuple(rng.choice(edges) for _ in range(4)),second=tuple(rng.choice(edges) for _ in range(4)))
    for i in range(16):
        actors=[actor((x*12,y*8,20,40)) for y in range(25) for x in range(23)]
        scan('575_synthetic_static_actors_multiple_requests',[(i,i),(i+1,i)],
             [(0,0,160,100,0),(120,60,180,140,255)],actors,full=i%2,
             first=(0,0,20,200),second=(0,0,320,10))
    scan('empty_request_caller')
    scan('full_800_visible_cells',[(i%40-20,i//40-10) for i in range(800)],full=1)
    return commands,expected,labels,groups,o.audit_calls
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/static-redraw-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/traversal-1006/static-redraw')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
    a=p.parse_args();start=time.monotonic();current=identities(a.exe);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh static request evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'seed':0x52413236,
            'scope':'Complete static request caller with actual coordinate/world projection, nested static Terrain scan/eligibility and type/alive/coordinate dispatch. Immutable bounded lists; render bounds, tactical projection and final drawing are services. Compare order, argument aliasing, redraw fields, nested ordered writes/events, complete arenas/tails and caller ESP/register/return guards. No original outer frame scheduler, surface lifetime or full-frame parity.'}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(commands)==len(labels)):raise AssertionError('Static request vector count differs')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:
            at=next((i for i,(a,b) in enumerate(zip(x,y)) if a!=b),min(len(x),len(y)))
            raise AssertionError(f'{n} {labels[n]}: token {at}: native {x[max(0,at-5):at+15]}, original {y[max(0,at-5):at+15]}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
        'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
        'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
        'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 static request results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
