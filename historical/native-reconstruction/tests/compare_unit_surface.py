#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact patched final Unit surface, flags, house selection and nested RGB565 draw."""
import argparse,itertools,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from unit_light_evidence import SOURCES as LIGHT_SOURCES
from verify_unit_surface import verify
SOURCES=tuple(dict.fromkeys(tuple('tests/'+p for p in LIGHT_SOURCES)+(
    'tests/compare_unit_surface.py','tests/original_unit_surface.py','tests/unit_surface_vectors.cpp',
    'tests/original_foot_lit.py','tests/compare_terrain_visibility.py','tools/verify_unit_surface.py',
    'tools/verify_terrain_visibility.py','src/render/UnitSurfaceDraw.hpp','src/render/UnitSurfaceDraw.cpp',
    'src/render/UnitTypeVisibility.hpp','src/render/UnitTypeVisibility.cpp',
    'src/render/Composition.hpp','src/render/Composition.cpp','src/render/VoxelRaster.hpp',
    'src/render/Lighting.hpp','src/assets/Formats.hpp','src/sim/OriginalMath.hpp',
    'src/sim/Facing.hpp','src/sim/Drive.hpp')))
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Unit surface engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Unit surface source/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Unit surface counts differ')
    if any(c.split()[0] not in ('D','S','P') for c in e['commands']):raise ValueError('Unknown Unit surface command')
def generate(exe):
    from original_unit_surface import UnitSurfaceOracle
    o=UnitSurfaceOracle(exe);rng=random.Random(0x52413241)
    commands=[];expected=[];labels=[];groups={}
    def save(group,op,v,result):
        commands.append(' '.join(map(str,[op,*v])));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    edges=[-2147483648,-2147483647,-257,-1,0,1,255,2147483646,2147483647]
    for n,(phase,owner) in enumerate(itertools.product(range(-512,512),range(2))):
        origin=rng.choice(edges);frame=((origin+phase-64+2**31)%2**32)-2**31
        v=[frame,origin,-1,0,(0,0x2800,0xffffffff)[n%3],owner]
        save('signed_phase_windows_and_preserved_bits','D',v,o.flags(v))
    for n,(frame,start,duration,owner) in enumerate(itertools.product(edges,edges,edges,range(2))):
        v=[frame,edges[n%9],start,duration,rng.randrange(2**32),owner]
        save('signed_wrapped_timers_paused_and_owner_early_return','D',v,o.flags(v))
    for n,(layer,a,b,disguise,owner) in enumerate(itertools.product([-2147483648,-1,0,1,2,3,4,5,2147483647],
                                                    [0,1,256,255],[0,1,256],[0,1],range(2))):
        v=[layer,edges[n%9],a,b,0,owner,0,0,disguise,n%256,0,-1,0,n%8,edges[(n+1)%9],
           edges[(n+2)%9],edges[(n+3)%9],0,*[rng.choice(edges) for _ in range(10)],rng.choice(edges)]
        save('complete_wrapper_layers_low_bytes_short_circuit_flags_and_wrap','S',v,o.draw(v))
    for n in range(1024):
        v=[rng.choice([-1,0,1,2,3,4,5]),rng.choice(edges),rng.randrange(512),rng.randrange(512),
           rng.choice([0,1,2]),rng.randrange(256),rng.randrange(256),rng.randrange(2),rng.randrange(512),
           *[rng.choice(edges) for _ in range(4)],rng.randrange(8),*[rng.choice(edges) for _ in range(3)],0,
           *[rng.choice(edges) for _ in range(11)]]
        save('complete_wrapper_house_timer_disguise_and_signed_inputs','S',v,o.draw(v))
    for n in range(256):
        v=[0,0,0,0,0,n%2,0,0,0,n,0,-1,0,n%8,0,-1,2,1,200,180,111,113,28,24,0,0,640,480,1000]
        save('actual_healthy_Foot_Drive_Techno_layer_nested_wrapper','S',v,o.draw(v))
    for n in range(384):
        w,h=40,32;sw,sh=48,40
        dirty=[rng.randrange(-4,sw+3),rng.randrange(-4,sh+3),rng.randrange(-1,38),rng.randrange(-1,34)]
        if n<96:dirty=[n%7,n%5,25,23]
        point=[rng.randrange(110,161),rng.randrange(110,153)]
        # The real caller supplies a viewport contained in the destination.
        # Source/destination rectangles can cross it; the viewport itself cannot.
        cx,cy=rng.randrange(6),rng.randrange(6)
        clip=[cx,cy,rng.randrange(1,w-cx+1),rng.randrange(1,h-cy+1)]
        v=[n,w,h,sw,sh,*dirty,*point,*clip,rng.choice([-9,-1,0,1,9]),
           rng.choice([0,1,500,1000,2000,2200,65535]),n%8]
        save('complete_wrapper_actual_surface_clipping_alpha_depth_read_and_RGB565_pixels','P',v,o.pixels(v))
    o.check_heap()
    if not o.span_calls or not o.changed_pixels:raise AssertionError('Nested pixel fixtures did not draw')
    return commands,expected,labels,groups,{'audited_new_roots':o.root_calls,
        'audited_roots_including_inherited_alpha_setup':o.audit_calls,'audited_inherited_alpha_blocks':o.audit_blocks,
        'actual_final_surface_calls':o.final_children,'actual_RGB565_span_calls':o.span_calls,
        'actual_healthy_layer_calls':o.layer_calls,'changed_fixture_color_pixels':o.changed_pixels}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-surface-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/surface-v1')
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
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh Unit surface evidence exists')
        now=time.monotonic();commands,expected,labels,groups,audits=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,**audits,'seed':0x52413241,'scope':current['inspection']['scope']}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Unit surface result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Unit surface run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 Unit surface results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
