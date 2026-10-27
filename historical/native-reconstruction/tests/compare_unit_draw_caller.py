#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact patched ordinary Unit caller and bounded screen registry comparisons."""
import argparse,itertools,json,random,sys,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
sys.path.insert(0,str(ROOT/'tools'))
from verify_unit_draw_caller import verify
SOURCES=('tests/compare_unit_draw_caller.py','tests/original_unit_draw_caller.py',
         'tests/unit_draw_caller_vectors.cpp','tests/compare_terrain_visibility.py',
         'tests/original_presentation.py','tests/presentation_profiles.py',
         'tests/compare_original.py','tests/presentation_evidence.py',
         'tools/verify_unit_draw_caller.py','tools/verify_terrain_visibility.py',
         'src/render/UnitDrawCaller.hpp','src/render/UnitDrawCaller.cpp',
         'src/render/UnitLighting.hpp','src/render/UnitLighting.cpp','src/sim/OriginalMath.hpp')
SOURCES+=('src/render/UnitVisibility.hpp','src/render/UnitVisibility.cpp',
          'src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp',
          'src/render/UnitTypeVisibility.hpp','src/render/UnitTypeVisibility.cpp','src/sim/Facing.hpp')
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(evidence,receipt,fingerprint,current):
    validate_receipt(evidence,receipt,fingerprint)
    if evidence.get('executable_sha256')!=PATCHED_EXPECTED or evidence.get('profile')!='supplied-ra2-1006':
        raise ValueError('Unit caller engine/profile differs')
    if evidence['evidence'].get('identities')!=current:raise ValueError('Unit caller source/inspection identity differs')
    if not(len(evidence['commands'])==len(evidence['expected'])==len(evidence['labels'])):
        raise ValueError('Unit caller vector counts differ')
def generate(exe):
    from original_unit_draw_caller import UnitDrawCallerOracle
    oracle=UnitDrawCallerOracle(exe);rng=random.Random(0x52413235)
    commands=[];expected=[];labels=[];groups={}
    def save(op,group,values,result):
        commands.append(op+' '+' '.join(map(str,values)));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    def registry(group,count=0,x=46,y=47,ox=10,oy=20,width=96,height=88):
        values=[count,x,y,ox,oy,width,height];save('registry',group,values,oracle.registry(*values))
    def draw(group,nested=None,**changes):
        args=dict(flags=0,shape=0,loaded=123,x=46,y=47,bx=0,by=0,bw=96,bh=88,
                  cx=18304,cy=29312,cz=416,offset=0,add14=0,index=-1,layer=2,ground=416,
                  ambient=1112,extra=200,cell_flags=0,predicate=0,visible=1,voxel=1,model=1,
                  alt_voxel=0,alt_model=0,count=0,ox=10,oy=20,width=96,height=88)
        if not set(changes)<=set(args):raise ValueError('Unknown fixture field')
        args.update(changes);values=list(args.values())
        result=oracle.draw(values,nested)
        save('draw' if nested is None else 'nested',group,values+([] if nested is None else list(nested)),result)
    edges=[-2147483648,-2147483647,-32768,-1,0,1,32767,2147483646,2147483647]
    for count,x,y,origin in itertools.product([0,1,498,499,500],[-33,-32,-31,0,127,128,129],
                                             [-33,-32,-31,0,119,120,121],[(0,0),(-2147483648,2147483647)]):
        registry('registry_inclusive_margins_capacity_and_origin_wrap',count,x,y,*origin)
    for count in range(501):registry('registry_every_valid_count',count=count)
    for _ in range(1024):
        registry('registry_signed_wrap_and_capacity_tails',count=rng.randrange(501),
                 x=rng.choice(edges),y=rng.choice(edges),ox=rng.choice(edges),oy=rng.choice(edges),
                 width=rng.choice(edges),height=rng.choice(edges))
    for n in range(256):
        draw('every_resource_flag_offset_byte_and_add14_byte',flags=n,offset=n,add14=n,
             shape=0xaabbccdd,loaded=0xfedcba98,index=255)
    for offset,add14,index,layer,visible,voxel,model in itertools.product(
            [-128,-1,0,1,127],[0,1,255,256],[-128,-1,0,1,127,255],[2,5],[0,1,255,256],[0,1],[0,1]):
        draw('caller_layer_secondary_type_model_and_distinct_foot_point',offset=offset,add14=add14,
             index=index,layer=layer,visible=visible,voxel=voxel,model=model,
             alt_voxel=1-voxel,alt_model=1-model)
    for ambient,extra,cell_flags,predicate,visible in itertools.product(
            [-32768,-149,-1,0,1,1112,32767],[-2147483648,-500,-1,0,200,2147483647],
            [0,0x10000,0xfffffeff],[0,1,255,256],[0,1]):
        draw('nested_ordinary_cell_brightness_and_wrapped_extra',ambient=ambient,extra=extra,
             cell_flags=cell_flags,predicate=predicate,visible=visible)
    for n in range(1024):
        draw('complete_ordinary_caller_wrapping_points_clips_and_registry',
             flags=rng.randrange(256),shape=rng.randrange(2**32),loaded=rng.randrange(2**32),
             x=rng.choice(edges),y=rng.choice(edges),bx=rng.choice(edges),by=rng.choice(edges),
             bw=rng.choice(edges),bh=rng.choice(edges),cx=rng.randrange(-255,131072),cy=rng.randrange(-255,131072),
             cz=rng.choice(edges),offset=rng.randrange(256),add14=rng.randrange(256),index=rng.randrange(256),
             layer=rng.choice([2,5]),ground=rng.choice(edges),ambient=rng.randrange(-32768,32768),
             extra=rng.choice(edges),cell_flags=rng.randrange(2**32)&~0x100,predicate=rng.choice([0,1,255,256]),
             visible=rng.choice([0,1,255,256]),voxel=rng.choice([0,1,255,256]),model=rng.randrange(2),
             alt_voxel=rng.choice([0,1,255,256]),alt_model=rng.randrange(2),count=rng.randrange(501),
             ox=rng.choice(edges),oy=rng.choice(edges),width=rng.choice(edges),height=rng.choice(edges))
    for n in range(1024):
        draw('nested_actual_gate_caller_registry_and_clip',
             nested=(rng.choice([0,1,255]),rng.choice([0,1,255]),rng.choice([0,1,255]),
                     rng.choice([0,1,255]),rng.randrange(2),rng.choice([0,1,255,256,257]),rng.choice([0,1,255,256])),
             flags=rng.randrange(256),offset=rng.randrange(256),add14=rng.randrange(256),
             index=rng.choice([-1,-128,0,127,255]),layer=rng.choice([2,5]),
             visible=rng.choice([0,1,255,256]),voxel=rng.randrange(2),model=rng.randrange(2),
             alt_voxel=rng.randrange(2),alt_model=rng.randrange(2),
             bx=rng.randrange(-20,120),by=rng.randrange(-20,120),bw=rng.randrange(-1,120),bh=rng.randrange(-1,120),
             x=rng.choice(edges),y=rng.choice(edges),count=rng.choice([0,499,500]))
    oracle.check_table()
    return commands,expected,labels,groups,oracle.audit_calls
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-draw-caller-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/caller')
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
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh caller evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'seed':0x52413235,
                  'scope':'Complete unmodified ordinary Unit caller and screen registry, actual nested coordinate/map/height wrapper. Layer/ground/predicates/alternate type/final VXL/SHP/Foot decoration supplied read-only. Ordered external writes/events, whole fixture arenas/capacity tails/table, caller ESP/register/return guards. No harvester/bridge/flag/active-timer or alternate cell-light branch, full child rendering, runtime integration or frame parity.'}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(commands)==len(labels)):raise AssertionError('Caller result count differs')
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
    print(f'{len(commands):,} supplied-1.006 Unit caller results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
