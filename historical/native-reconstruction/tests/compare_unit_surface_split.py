#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact Unit nonzero bridge-size decisions, split forwarding and surface pixels."""
import argparse,itertools,json,random,time,subprocess
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_foot_depth import SOURCES as PARENT_SOURCES
from verify_unit_surface_split import verify
SOURCES=tuple(dict.fromkeys((*PARENT_SOURCES,'tests/compare_unit_surface_split.py',
    'tests/original_unit_surface_split.py','tests/unit_surface_split_vectors.cpp',
    'tools/verify_unit_surface_split.py','src/render/UnitSurfaceSplit.cpp','src/render/UnitSurfaceSplit.hpp')))
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Surface split engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Surface split source/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Surface split counts differ')
    if any(c.split()[0] not in ('S','N','P') for c in e['commands']):raise ValueError('Unknown surface split command')
def generate(exe):
    from original_unit_surface_split import UnitSurfaceSplitOracle
    o=UnitSurfaceSplitOracle(exe);rng=random.Random(0x52413244)
    commands=[];expected=[];labels=[];groups={}
    def save(group,op,v,result):
        commands.append(' '.join(map(str,[op,*v])));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    edges=[-2147483648,-2147483647,-65536,-1,0,1,255,65535,2147483647]
    def tail(n,extreme=False):
        geometry=[rng.choice(edges) for _ in range(11)] if extreme else [128,128,4,5,32,32,0,0,80,64,1000]
        geometry[5]=rng.choice([-2147483648,-1,0,15,16,17,31,2147483647])
        return list(map(int,[n%7-1,n%3==1,n%3==2,rng.choice(edges),n%2,rng.choice(edges),rng.choice(edges),rng.choice(edges),*geometry]))
    for n,raw in enumerate(itertools.product([0,1,256,257],[0,1,256,257,-1],[0,1,-1],[0,-1],[0,1],[1,6],[0,1,256,257])):
        v=[*raw,*tail(n)];save('complete_low_byte_predicate_contact_selection_and_split_forwarding','S',v,o.forwarding(v))
    for n in range(512):
        raw=[rng.choice([0,1,255,256]),rng.choice(edges),rng.choice(edges),rng.choice(edges),n%2,rng.choice([0,6,-1,2147483647]),rng.choice(edges)]
        v=[*raw,*tail(n,True)];save('wrapped_destination_source_and_repeated_depth_queries','S',v,o.forwarding(v))
    for n in range(512):
        world=[n,rng.choice(edges),rng.choice(edges),n%5==0,rng.choice(edges),-32768,-32768,n%8]
        world=list(map(int,world));v=[1,0,0,n%2,n%2,6,n%2,*tail(n)]
        save('actual_cell_predicates_nested_before_contact_and_surface','N',[*world,*v],o.forwarding(v,world))
    for n in range(320):
        prefix=([0,0,0,0,0,0,0],[1,1,0,0,0,0,0],[1,0,0,1,1,6,1],[1,0,0,0,1,6,1],[1,1,1,1,1,6,1])[n%5]
        w,h=56,48;sw,sh=64,64;cx,cy=rng.randrange(8),rng.randrange(8)
        v=[n,w,h,sw,sh,rng.randrange(8),rng.randrange(8),rng.randrange(1,48),rng.randrange(1,57),
           rng.randrange(105,154),rng.randrange(105,154),cx,cy,rng.randrange(1,w-cx+1),rng.randrange(1,h-cy+1),
           rng.choice([-20,-1,0,1,7,25]),rng.choice([0,1,500,1000,2000,2200,65535]),n%8]
        save('actual_complete_final_surface_split_top_and_flat_RGB565_pixels','P',[*prefix,*v],o.pixels([*prefix,*v]))
    o.check_heap()
    if not all(o.gradient_calls.values()) or not o.contact_getters or not o.kind_calls:raise AssertionError('Missing nested split child coverage')
    return commands,expected,labels,{'groups':groups,'audited_new_roots':o.split_roots,
        'audited_roots_including_inherited_setup':o.audit_calls,'audited_inherited_alpha_blocks':o.audit_blocks,
        'actual_contact_getters':o.contact_getters,'supplied_contact_kind_calls':o.kind_calls,
        'actual_final_surface_calls':o.final_children,'actual_gradient_surface_calls':o.gradient_calls,
        'actual_RGB565_span_calls':o.span_calls,'changed_fixture_color_pixels':o.changed_pixels}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-surface-split-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/surface-split-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a.exe);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh surface split evidence exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a.exe);generation=time.monotonic()-now
        metadata['scope']=current['inspection']['scope'];report=out/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:raise AssertionError(f'Native split failed after {len(error.stdout.splitlines())} results: {error.stderr}') from error
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Surface split result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Surface split run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 surface split results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
