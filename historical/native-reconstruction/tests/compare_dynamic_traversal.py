#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential bounded Unit/Foot/Terrain per-frame traversal, exact 1.006 hash."""
import argparse
import itertools
import json
from pathlib import Path
import random
import struct
import subprocess
import sys
import time
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
sys.path.insert(0,str(ROOT/'tools'))
from verify_dynamic_traversal import verify
SOURCES=('tests/compare_dynamic_traversal.py','tests/original_dynamic_traversal.py',
         'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/presentation_profiles.py',
         'tests/compare_original.py','tests/presentation_evidence.py','tools/verify_dynamic_traversal.py',
         'tools/verify_terrain_visibility.py','src/render/DynamicTraversal.hpp','src/render/DynamicTraversal.cpp',
         'src/render/Composition.hpp','src/render/Composition.cpp','src/sim/OriginalMath.hpp',
         'tests/dynamic_traversal_vectors.cpp')
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','inspection':verify(exe.read_bytes()),
            'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(evidence,receipt,fingerprint,current):
    validate_receipt(evidence,receipt,fingerprint)
    if evidence.get('executable_sha256')!=PATCHED_EXPECTED or evidence.get('profile')!='supplied-ra2-1006':
        raise ValueError('Dynamic traversal engine/profile differs')
    if evidence['evidence'].get('identities')!=current:raise ValueError('Dynamic traversal source/inspection identity differs')
    if not(len(evidence['commands'])==len(evidence['expected'])==len(evidence['labels'])):
        raise ValueError('Dynamic traversal vector counts differ')
def bits(v):return struct.unpack('<i',struct.pack('<f',v))[0]
def actor(kind=0,flags=7,visible=255,animated=0,crumbling=0,coords=(256,256,0),reject=0,mutate=0,clip=(7,9,73,65)):
    return [kind,flags,visible,animated,crumbling,*coords,reject,int(mutate),*clip]
def generate(exe):
    from original_dynamic_traversal import DynamicTraversalOracle
    oracle=DynamicTraversalOracle(exe);rng=random.Random(0x52413232)
    commands=[];expected=[];labels=[];groups={}
    def scan(group,actors,layers=None,force=1,scenario=0,context=1,bypass=0,origin=(0,0),surface=(320,200),
             viewport=(0,0,320,200),inverse=((-65536,-65536,0),(65536,0,0),(0,65536,0))):
        if layers is None:layers=[[],[],list(range(len(actors))),[],[]]
        inverse=[[bits(v) for v in p] for p in inverse]
        tokens=[len(actors),force,scenario,context,bypass,*origin,*surface,repr(oracle.scale),*viewport,
                *[v for p in inverse for v in p],*[v for a in actors for v in a],
                *[v for layer in layers for v in [len(layer),*layer]]]
        commands.append(' '.join(map(str,tokens)))
        expected.append(list(map(str,oracle.scan(actors,layers,force,scenario,context,bypass,origin,surface,viewport,inverse))))
        labels.append(group);groups[group]=groups.get(group,0)+1
    scan('empty_five_layers',[])
    for flags,scenario,context,bypass,reject,force in itertools.product([4,5,6,7,255],[0,0x1000],[0,1],[0,1,255],[0,1,255,256],[0,1,256,257]):
        scan('foot_flags_map_gates_and_force_dword',[actor(flags=flags,reject=reject)],
             scenario=scenario,context=context,bypass=bypass,force=force)
    for animated,crumbling,visible,reject in itertools.product([0,1,255],repeat=4):
        scan('terrain_static_skip_dynamic_gate_and_visibility_reset',
             [actor(1,2,visible,animated,crumbling,reject=reject)])
    # Both world bounds are lower-inclusive/upper-exclusive. The unused inverse
    # components deliberately disagree and must not affect the domain.
    for axis,v,kind in itertools.product([0,1],[-3001,-3000,-2999,-2001,-2000,-1999,3999,4000,4001,6999,7000,7001],[0,1]):
        p=[0,0,0];p[axis]=v
        scan('world_lower_inclusive_upper_exclusive',[actor(kind,7 if kind==0 else 2,animated=1,coords=p)],
             inverse=((-2000.875,-3000.875,100),(1000.875,-9999,200),(-9999,2000.875,300)))
    for x,y,z in itertools.product([-361,-360,-359,0,679,680,681],[-181,-180,-179,0,379,380,381],[-65536,-1,0,727,728,65536]):
        p=(18304,29312,z)
        projected=((p[0]*30-p[1]*30)//256,int((p[0]*15+p[1]*15)/256)-int(z*oracle.scale+(z>=728)+0.5))
        # X truncates toward zero too; correct only the negative numerator here.
        projected=(int((p[0]*30-p[1]*30)/256),projected[1])
        scan('inclusive_screen_margins_and_actual_projection',[actor(coords=p)],origin=(projected[0]-x,projected[1]-y))
    edges=[-2147483648,-2147483647,-16777217,-1,0,1,16777217,2147483646,2147483647]
    for n in range(128):
        viewport=[rng.choice(edges) for _ in range(4)];origin=[rng.choice(edges),rng.choice(edges)]
        scan('inverse_input_wrapping_half_and_float32_store',[],viewport=viewport,origin=origin)
    for n in range(256):
        values=[-2147483648,-2147483520,-65536.875,-1.875,-0.875,0,0.875,1.875,65536.875,2147483520]
        inverse=[[rng.choice(values) for _ in range(3)] for _ in range(3)]
        scan('inverse_output_truncation_and_wrapped_domain',[actor(coords=(n-128,n-128,0))],inverse=inverse)
    for n in range(1024):
        actors=[]
        for id in range(12):
            kind=rng.randrange(2);flags=rng.choice([4,5,6,7,255]) if kind==0 else rng.choice([0,2,128,130])
            p=[rng.randrange(-20000,20000),rng.randrange(-20000,20000),rng.choice([-65536,-1,0,727,728,65536])]
            actors.append(actor(kind,flags,rng.choice([0,1,255]),rng.randrange(2),rng.randrange(2),p,
                                rng.choice([0,1,255,256]),n%3==0 and id%3==0,
                                tuple(rng.choice(edges) for _ in range(4))))
        layers=[[rng.randrange(12) for _ in range(rng.randrange(18))] for _ in range(5)]
        scan('five_layer_forward_duplicates_shared_clip_and_extras',actors,layers,
             force=rng.choice(edges),scenario=rng.choice([0,0x1000,0xffffffff]),context=rng.randrange(2),bypass=rng.choice([0,1,255]),
             origin=(rng.randrange(-800,800),rng.randrange(-800,800)),surface=(rng.choice([0,320,2147483647]),rng.choice([0,200,2147483647])))
    # Dense synthetic layer: ordinary scenery is skipped without invoking its
    # eligibility service, while one moving Unit is admitted and gets extras.
    for n in range(16):
        actors=[actor(1,2,coords=(x*256+128,y*256+128,0)) for y in range(25) for x in range(23)]
        actors.append(actor(coords=(n*256+128,n*128+128,0)))
        scan('575_static_terrain_plus_one_moving_unit',actors)
    return commands,expected,labels,groups,oracle.audit_calls
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/dynamic-traversal-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/traversal-1006/dynamic')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
    a=p.parse_args();start=time.monotonic();current=identities(a.exe);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        evidence=json.loads(source.read_text());validate(evidence,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[evidence[k] for k in ('commands','expected','labels')];metadata=evidence['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh dynamic evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'seed':0x52413232,
                  'scope':'Complete unmodified per-frame caller in bounded Unit/Foot and Terrain domain; actual vtables/type leaves/coordinate getters/projection/Unit DrawBehind no-op. Inverse-camera transform, Foot +4C, map predicate, eligibility and extras are services; auxiliary collection empty. Ordered visible stores and callbacks, shared clip mutations, full fixture arenas/tails, original caller ESP/register/return and permitted-write audits. Supplied flags, no constructors, scheduling/final rendering/full-frame claim.'}
        report=out/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:
        raise AssertionError(f'Native traversal runner failed: {error.stderr.strip()}') from error
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(commands)==len(labels)):raise AssertionError('Dynamic vector count differs')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:
            at=next((i for i,(a,b) in enumerate(zip(x,y)) if a!=b),min(len(x),len(y)))
            raise AssertionError(f'{n} {labels[n]} token {at}: native {x[max(0,at-5):at+15]}, original {y[max(0,at-5):at+15]}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                    'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 dynamic traversal results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
