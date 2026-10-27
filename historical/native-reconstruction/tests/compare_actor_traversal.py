#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-engine Foot/Drive getters, field subset and combined drawing caller."""
import argparse
import itertools
import json
from pathlib import Path
import random
import sys
import time
from compare_dynamic_traversal import SOURCES as DYNAMIC_SOURCES,bits
from compare_unit_visibility import SOURCES as UNIT_SOURCES
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
sys.path.insert(0,str(ROOT/'tools'))
from verify_actor_traversal import verify
SOURCES=tuple(dict.fromkeys((*DYNAMIC_SOURCES,*UNIT_SOURCES,
    'tests/compare_actor_traversal.py','tests/original_actor_traversal.py','tests/actor_traversal_vectors.cpp',
    'tools/verify_actor_traversal.py','src/sim/FootCoordinates.hpp','src/sim/FootCoordinates.cpp',
    'src/sim/TerrainOccupation.hpp')))
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','inspection':verify(exe.read_bytes()),
            'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(evidence,receipt,fingerprint,current):
    validate_receipt(evidence,receipt,fingerprint)
    if evidence.get('executable_sha256')!=PATCHED_EXPECTED or evidence.get('profile')!='supplied-ra2-1006':
        raise ValueError('Actor traversal engine/profile differs')
    if evidence['evidence'].get('identities')!=current:raise ValueError('Actor traversal source/inspection identity differs')
    if not(len(evidence['commands'])==len(evidence['expected'])==len(evidence['labels'])):
        raise ValueError('Actor traversal vector counts differ')
def actor(kind=0,flags=7,visible=255,coords=(256,256,0),on_map=1,redraw=1,limbo=0,index=255,reject=0,
          destination=(0,0,0),success=1,projected=(46,47)):
    return [kind,flags,visible,*coords,on_map,redraw,limbo,index,reject,*destination,success,*projected]
def generate(exe):
    from original_actor_traversal import ActorTraversalOracle
    o=ActorTraversalOracle(exe);rng=random.Random(0x52413234);commands=[];expected=[];labels=[];groups={}
    def add(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)));labels.append(group)
        groups[group]=groups.get(group,0)+1
    for byte in range(256):add('scoped_constructor_field_inputs',['G',byte],o.fields(byte))
    edges=[-2147483648,-2147483647,-32768,-1,0,1,32767,2147483646,2147483647]
    def foot(group,index,current,destination,x,y,unused):
        add(group,['F',index,*current,*destination,x,y,unused],o.foot(index,current,destination,x,y,unused))
    for index,x,y in itertools.product(range(128),[0,1,32767,32768,65535],[0,1,32767,32768,65535]):
        foot('all_indexed_entries_signed_words',index,(18304,29312,416),(777,888,999),x,y,rng.choice(edges))
    for index,case in itertools.product(range(128,256),range(8)):
        current=[rng.choice(edges) for _ in range(3)];dest=[rng.choice(edges) for _ in range(3)]
        if case==0:current=dest=[0,0,0]
        elif case==1:dest=[0,0,0]
        elif case<5:dest=[0,0,0];dest[case-2]=1
        elif case==5:current=[0,0,0]
        foot('all_negative_indices_drive_empty_and_foot_fallback',index,current,dest,0,0,rng.choice(edges))
    def scan(group,actors,layers=None,force=1,scenario=0,context=1,bypass=0,origin=(0,0),surface=(320,200),
             viewport=(0,0,320,200),inverse=((-65536,-65536,0),(65536,0,0),(0,65536,0))):
        if layers is None:layers=[[],[],list(range(len(actors))),[],[]]
        inverse=[[bits(v) for v in p] for p in inverse]
        tokens=['D',len(actors),force,scenario,context,bypass,*origin,*surface,repr(o.scale),*viewport,
                *[v for p in inverse for v in p],*[v for a in actors for v in a],
                *[v for layer in layers for v in [len(layer),*layer]]]
        add(group,tokens,o.scan(actors,layers,force,scenario,context,bypass,origin,surface,viewport,inverse))
    scan('empty_combined_caller',[])
    for on_map,redraw,limbo,scenario,force,success in itertools.product([0,1,255],[0,1,255],[0,1,255],
                                                                     [0,0x1000],[0,1,256,257],[0,1,255,256]):
        scan('nested_unit_gate_state_force_projection',[actor(on_map=on_map,redraw=redraw,limbo=limbo,success=success)],
             scenario=scenario,force=force)
    for context,bypass,reject,index in itertools.product([0,1],[0,1,255],[0,1,255,256],[0,127,128,255]):
        scan('combined_foot_and_context_map_gates',[actor(coords=(0,0,0),on_map=0,redraw=0,limbo=1,index=index,reject=reject)],
             scenario=0x1000,context=context,bypass=bypass,force=0)
    for n in range(768):
        actors=[]
        for id in range(12):
            kind=rng.randrange(2);p=[rng.randrange(-20000,20000),rng.randrange(-20000,20000),rng.choice([-65536,-1,0,727,728,65536])]
            if n%4==0 and id==0:p=[0,0,0]
            actors.append(actor(kind,flags=rng.choice([7,135,255]) if not kind else 2,coords=p,
                                on_map=rng.choice([0,1,255]),redraw=rng.choice([0,1,255]),limbo=rng.choice([0,1,255]),
                                index=rng.randrange(256),reject=rng.choice([0,1,255,256]),
                                destination=[0,0,0] if n%2 else [rng.choice(edges) for _ in range(3)],
                                success=rng.choice([0,1,255,256]),projected=[rng.choice(edges),rng.choice(edges)]))
        layers=[[rng.randrange(12) for _ in range(rng.randrange(18))] for _ in range(5)]
        viewport=[rng.choice(edges),rng.choice(edges),rng.choice([-1,0,1,320,2147483647]),rng.choice([-1,0,1,200,2147483647])]
        scan('combined_duplicates_order_clipping_alias_and_state',actors,layers,viewport=viewport,
             force=rng.choice(edges),scenario=rng.choice([0,0x1000,0xffffffff]),context=rng.randrange(2),bypass=rng.choice([0,1,255]),
             origin=(rng.randrange(-800,800),rng.randrange(-800,800)),surface=(320,200))
    for n in range(16):
        actors=[actor(1,2,coords=(x*256+128,y*256+128,0)) for y in range(25) for x in range(23)]
        actors.append(actor(coords=(n*256+128,n*128+128,0),destination=(4096,4096,0)))
        scan('575_static_terrain_and_real_unit_getter_gate',actors)
    return commands,expected,labels,groups,o.audit_calls,o.audit_blocks
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/actor-traversal-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/traversal-1006/actors')
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
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh actor evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls,blocks=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'audited_blocks':blocks,'seed':0x52413234,
                  'scope':'Complete Foot/Drive getters and sentinel initializers; Abstract constructor plus scoped Object/Techno/Foot field stores. Complete per-frame caller with real secondary getters and nested ordinary Unit/Object eligibility; healthy static Terrain skipped. Actual Unit/Drive vtables, coordinates/type/behind/projection execute. Inverse camera, map predicate, tactical projection, final DrawIt and extras remain services. Ordered visible/redraw/clip writes and callbacks, full fixture arenas/tails, root caller ESP/register/return and scoped-block write/stack guards. No complete actor construction, dynamic redraw scheduling, final rendering/runtime or whole-frame parity.'}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(commands)==len(labels)):raise AssertionError('Actor vector count differs')
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
    print(f'{len(commands):,} supplied-1.006 combined actor/getter results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
