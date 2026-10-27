#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Original/native ordinary Unit eligibility, clipping and viewport alias cases."""
import argparse
import itertools
import json
from pathlib import Path
import random
import sys
import time
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
sys.path.insert(0,str(ROOT/'tools'))
from verify_unit_visibility import verify
SOURCES=('tests/compare_unit_visibility.py','tests/original_unit_visibility.py',
         'tests/compare_terrain_visibility.py','tests/original_terrain_visibility.py','tests/original_presentation.py',
         'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py',
         'tools/verify_unit_visibility.py','tools/verify_dynamic_traversal.py','tools/verify_terrain_visibility.py',
         'src/render/UnitVisibility.hpp','src/render/UnitVisibility.cpp',
         'src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp','tests/unit_visibility_vectors.cpp')
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','inspection':verify(exe.read_bytes()),
            'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(evidence,receipt,fingerprint,current):
    validate_receipt(evidence,receipt,fingerprint)
    if evidence.get('executable_sha256')!=PATCHED_EXPECTED or evidence.get('profile')!='supplied-ra2-1006':
        raise ValueError('Unit visibility engine/profile differs')
    if evidence['evidence'].get('identities')!=current:raise ValueError('Unit visibility source/inspection identity differs')
    if not(len(evidence['commands'])==len(evidence['expected'])==len(evidence['labels'])):
        raise ValueError('Unit visibility vector counts differ')
def generate(exe):
    from original_unit_visibility import UnitVisibilityOracle
    oracle=UnitVisibilityOracle(exe);rng=random.Random(0x52413233)
    commands=[];expected=[];labels=[];groups={}
    def draw(group,state=(1,1,0),gate=(0,1,1),unused=-1,success=1,alias=0,
             bounds=(0,0,96,88),viewport=(0,0,96,88),projected=(46,47),coords=(18304,29312,416)):
        tokens=[*state,*gate,unused,success,alias,*bounds,*viewport,*projected,*coords]
        commands.append(' '.join(map(str,tokens)))
        expected.append(list(map(str,oracle.draw(state,gate,unused,success,alias,bounds,viewport,projected,coords))))
        labels.append(group);groups[group]=groups.get(group,0)+1
    for state in itertools.product([0,1,255],repeat=3):
        for bypass,context,force,success in itertools.product([0,1,255],[0,1],[0,1,255,256,257],[0,1,255,256]):
            draw('ordinary_unit_redraw_limbo_bypass_force_and_projection',state,(bypass,context,force),success=success)
    edges=[-2147483648,-2147483647,-32768,-1,0,1,32767,2147483646,2147483647]
    sizes=[-2147483648,-1,0,1,2,60,100,2147483647]
    for n in range(2048):
        bounds=[rng.randrange(-80,160),rng.randrange(-80,160),rng.randrange(-1,100),rng.randrange(-1,100)]
        viewport=[7,9,73,65]
        projected=[rng.choice(edges),rng.choice(edges)]
        if n%3==0:
            bounds=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
            viewport=[rng.choice(edges),rng.choice(edges),rng.choice(sizes),rng.choice(sizes)]
        draw('complete_clip_empty_draw_wrapping_and_live_viewport_alias',unused=rng.choice(edges),
             alias=n%2,bounds=bounds,viewport=viewport,projected=projected,
             coords=[rng.choice(edges),rng.choice(edges),rng.choice(edges)])
    for bounds,viewport,alias in itertools.product([(0,0,0,0),(7,9,73,65),(-5,-7,0,0),(100,100,1,1),(-10,-20,20,20)],
                                                   [(0,0,96,88),(7,9,73,65),(-5,-7,0,0)], [0,1]):
        draw('explicit_empty_touching_and_shared_clip',bounds=bounds,viewport=viewport,alias=alias)
    return commands,expected,labels,groups,oracle.audit_calls
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-visibility-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/traversal-1006/unit-visibility')
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
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh Unit visibility evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'seed':0x52413233,
                  'scope':'Unmodified Unit wrapper +0x370=0 and complete nested Object draw gate. Actual Unit virtual coordinate/type getters execute; projection and final DrawIt supplied. Ordered redraw/clip mutations, viewport alias, full arena/tails, original caller ESP/register/return and permitted-write audits. No special Unit state, non-Unit Object profiles, full drawing/scheduling/runtime integration or whole-frame parity.'}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(commands)==len(labels)):raise AssertionError('Unit visibility vector count differs')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: native {x}, original {y}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 ordinary Unit visibility results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
