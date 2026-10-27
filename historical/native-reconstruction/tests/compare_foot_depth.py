#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact patched Foot depth/gradient, cell predicates and nested surface pixels."""
import argparse,itertools,json,random,time,subprocess
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_unit_surface import SOURCES as SURFACE_SOURCES
from verify_foot_depth import verify
SOURCES=tuple(dict.fromkeys((*SURFACE_SOURCES,
    'tests/compare_foot_depth.py','tests/original_foot_depth.py','tests/foot_depth_vectors.cpp',
    'tests/foot_depth_fixture.hpp','tools/verify_foot_depth.py','src/render/FootDepth.hpp',
    'src/render/FootDepth.cpp','src/render/UnitLighting.hpp','src/render/UnitLighting.cpp',
    'src/sim/Drive.cpp')))
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Foot depth engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Foot depth source/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Foot depth counts differ')
    if any(c.split()[0] not in ('F','Q','N','K','P') for c in e['commands']):raise ValueError('Unknown Foot depth command')
def generate(exe):
    from original_foot_depth import FootDepthOracle
    o=FootDepthOracle(exe);rng=random.Random(0x52413242)
    commands=[];expected=[];labels=[];groups={};predicate_values={i:set() for i in range(5)}
    def save(group,op,v,result):
        commands.append(' '.join(map(str,[op,*v])));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    edges=[-2147483648,-2147483647,-65536,-1,0,1,255,65535,2147483647]
    coordinate_edges=edges+[8388352,8388607,8388608,-8388608,-8388609,16777216]
    for n in range(2048):
        v=[n%2,(n//2)%2,rng.choice(edges),rng.choice(edges),*[rng.choice(edges) for _ in range(7)],
           rng.choice([0,1,255,256,257,-1]),rng.choice(edges)]
        save('complete_Foot_signed_products_max_wrapping_low_byte_and_Drive_null','F',v,o.wrapper(v,'F'))
    for n,(kind,seed) in enumerate(itertools.product(range(5),range(512))):
        world=[seed,rng.choice(coordinate_edges),rng.choice(coordinate_edges),rng.choice([0,0,0,1,256,255]),
               rng.choice(edges),-32768,-32768,rng.choice([-1,0,1,4,7,2147483647])]
        result=o.query(kind,world);predicate_values[kind].add(result[-1])
        save('complete_cell_predicates_query_order_signed_levels_flags_tiles_and_word_wrap','Q',[kind,*world],result)
    for n in range(1024):
        world=[n,rng.randrange(512)*256+rng.randrange(256),rng.randrange(512)*256+rng.randrange(256),
               n%4==0,rng.choice(edges),-32768,-32768,n%8]
        world=list(map(int,world))
        v=[*world,n%2,1,0,2,*[rng.choice(edges) for _ in range(4)],rng.choice(edges)]
        save('complete_Foot_with_actual_cell_predicates_and_Drive','N',v,o.wrapper(v,'N'))
    for n in range(128):
        world=[0,(n%16)*256+128,(n//16)*256+128,0,0,-32768,-32768,4]
        v=[*world,n%2,1,0,2,*[rng.choice(edges) for _ in range(4)],-1]
        save('complete_Foot_with_actual_healthy_base_depth_and_zero_tile_dimensions_service','K',v,o.wrapper(v,'K'))
    for n in range(192):
        w,h=40,32;sw,sh=48,40;cx,cy=rng.randrange(6),rng.randrange(6)
        v=[n,w,h,sw,sh,rng.randrange(8),rng.randrange(8),rng.randrange(1,32),rng.randrange(1,28),
           rng.randrange(110,151),rng.randrange(110,147),cx,cy,rng.randrange(1,w-cx+1),rng.randrange(1,h-cy+1),
           -1,rng.choice([0,1,500,1000,2000,2200,65535]),n%8]
        save('complete_Unit_surface_actual_Foot_depth_gradient_base_and_RGB565_pixels','P',v,o.pixels(v))
    o.check_heap()
    if not o.base_calls or not o.dimension_writes or not o.span_calls:raise AssertionError('Nested Foot children did not execute')
    for kind,values in predicate_values.items():
        if values!=({0,1,2} if kind in (0,2) else {0,1}):raise AssertionError(f'Incomplete predicate {kind} outputs: {values}')
    return commands,expected,labels,groups,{'audited_new_roots':o.new_roots,
        'predicate_outputs':{str(k):sorted(v) for k,v in predicate_values.items()},
        'audited_roots_including_inherited_setup':o.audit_calls,'audited_inherited_alpha_blocks':o.audit_blocks,
        'actual_base_depth_calls':o.base_calls,'guarded_supplied_tile_dimension_writes':o.dimension_writes,
        'map_service_calls':o.map_calls,'actual_final_surface_calls':o.final_children,
        'actual_RGB565_span_calls':o.span_calls,'changed_fixture_color_pixels':o.changed_pixels}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/foot-depth-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/foot-depth-v1')
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
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh Foot depth evidence exists')
        now=time.monotonic();commands,expected,labels,groups,audits=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,**audits,'seed':0x52413242,'scope':current['inspection']['scope']}
        report=out/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:
        raise AssertionError(f'Native Foot depth failed after {len(error.stdout.splitlines())} output lines: {error.stderr}') from error
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Foot depth result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Foot depth run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 Foot depth results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
