#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact patched Foot lit forwarding and actual nested successful cache protocol."""
import argparse,itertools,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from voxel_cache_evidence import SOURCES as CACHE_SOURCES
from verify_foot_lit_draw import verify
from verify_voxel_cache_mapping import verify as verify_cache
SOURCES=tuple(dict.fromkeys(tuple('tests/'+p for p in CACHE_SOURCES)+(
    'tests/compare_foot_lit.py','tests/original_foot_lit.py','tests/foot_lit_vectors.cpp',
    'tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py',
    'tools/verify_foot_lit_draw.py','tools/verify_voxel_cache_mapping.py','tools/inspect_patch.py',
    'src/render/FootLitDraw.hpp','src/render/FootLitDraw.cpp','src/render/VoxelCache.hpp','src/render/VoxelCache.cpp',
    'src/render/UnitLighting.hpp','src/render/UnitLighting.cpp','src/render/VoxelRaster.hpp',
    'src/render/Composition.hpp','src/assets/Formats.hpp','src/sim/OriginalMath.hpp')))
def identities(exe):
    disc=ROOT/'private/disc-allied/game.exe'
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','inspection':verify(exe.read_bytes()),
            'inherited_cache_inspection':verify_cache(disc.read_bytes(),exe.read_bytes()),
            'inspection_disc_sha256':hash_file(disc),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Foot lit engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Foot lit source/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Foot lit counts differ')
    if any(c.split()[0] not in ('F','N','O','Z') for c in e['commands']):raise ValueError('Unknown Foot lit command')
def generate(exe):
    from original_foot_lit import FootLitOracle,FootLitCacheOracle
    oracle=FootLitOracle(exe);nested=FootLitCacheOracle(exe);rng=random.Random(0x52413238)
    commands=[];expected=[];labels=[];groups={}
    def save(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    edges=[-2147483648,-2147483647,-1,0,1,127,128,2147483646,2147483647]
    patterns=[0,0x80000000,0x7f800000,0xff800000,0x7fc12345,0x7fa12345,1,0xffffffff,0x3f800000]
    def pose(n):return [patterns[(n+i)%len(patterns)] for i in range(12)]
    for x,y in itertools.product(edges,repeat=2):save('actual_Drive_zero_point_and_two_dword_stores',['Z',x,y],oracle.zero(x,y))
    for n,(has,mode,x,dx) in enumerate(itertools.product([0,1],range(3),edges,edges)):
        v=[has,mode,x,edges[(n+3)%9],dx,edges[(n+7)%9],0xfedcba98,edges[n%9],edges[(n+2)%9],0xabcdef01,
           *[edges[(n+i)%9] for i in range(4)],edges[(n+5)%9],0xffffffff,*pose(n)]
        save('complete_Foot_no_locomotor_actual_Drive_supplied_offsets_and_wrap',['F',*v],oracle.forward(v))
    for n in range(1024):
        v=[rng.randrange(2),rng.randrange(3),*[rng.randrange(-2**31,2**31) for _ in range(4)],
           rng.randrange(2**32),rng.choice(edges),rng.choice(edges),rng.randrange(2**32),
           *[rng.choice(edges) for _ in range(5)],rng.randrange(2**32),*[rng.randrange(2**32) for _ in range(12)]]
        save('complete_Foot_bitwise_pose_and_all_forwarded_arguments',['F',*v],oracle.forward(v))
    for sequence in range(8):
        nested.begin();save('nested_cache_reset',['O'],['reset'])
        keys=[-1,-2,0,31,-2147483648,2147483647]+rng.sample(range(-2000,2001),18)
        rows=[(k,1,0,1) for k in keys]+[(k,1,0,1) for k in keys[::-1]]
        rows +=[(rng.choice(keys),rng.choice([0,1,1]),rng.choice([0,0,1]),rng.choice([0,1,1])) for _ in range(32)]
        rows +=[(0,1,0,0),(999999,1,0,0),(-1,1,0,0)]
        for n,(key,available,disabled,valid) in enumerate(rows):
            v=[key,available,disabled,valid,rng.randrange(64),rng.choice([0,1,1312,2200,65535]),
               rng.randrange(2),rng.randrange(2),*[rng.choice(edges) for _ in range(4)],*pose(n)]
            save('actual_Foot_Drive_and_Techno_cache_hit_miss_bypass_invalid_protocol',
                 ['N',*v],nested.nested(v))
    nested.check_heap()
    return commands,expected,labels,groups,oracle.audit_calls,nested.audit_calls,oracle.host_point_writes,nested.host_writes
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/foot-lit-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/foot-lit')
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
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh Foot lit evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls,nested,points,writes=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_forward_roots':calls,'audited_nested_roots_including_retained_setup':nested,
                  'guarded_supplied_forward_point_writes':points,'guarded_supplied_cache_writes':writes,'seed':0x52413238,
                  'scope':current['inspection']['scope']+' Nested cache uses the retained healthy synthetic actor/type/model and bounded successful logical render/snapshot/heap services. No original VXL raster pixels or full Unit voxel child execute here. Forwarding inputs/rectangles are immutable; no aliasing or ownership claim.'}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Foot lit result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Foot lit run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 Foot lit results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
