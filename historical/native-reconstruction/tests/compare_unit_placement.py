#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-base FireAngle and complete Techno placement wrapper."""
import argparse,configparser,itertools,json,random,time,subprocess
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_placement import verify
SOURCES=('tests/compare_unit_placement.py','tests/original_unit_placement.py',
    'tests/unit_placement_vectors.cpp','tools/verify_unit_placement.py',
    'src/assets/UnitFireAngle.hpp','src/assets/Formats.hpp','src/assets/Formats.cpp',
    'src/sim/TechnoPlacement.hpp','src/sim/TechnoPlacement.cpp','src/sim/Facing.hpp','src/sim/UnitDrawingState.hpp',
    'src/sim/TerrainOccupation.hpp','src/sim/TerrainOccupation.cpp',
    'tests/original_unit_drawing_state.py','tests/original_unit_metadata.py',
    'tests/original_presentation.py','tests/original_foot_lit.py')
def identities(exe,assets):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
            'assets':{str((assets/'rules.ini').resolve()):hash_file(assets/'rules.ini')}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Placement engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Placement source/asset/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Placement counts differ')
    if any(c.split()[0] not in ('M','O','P','C') for c in e['commands']):raise ValueError('Unknown placement runner command')
def generate(exe,assets):
    from original_unit_placement import UnitPlacementOracle
    o=UnitPlacementOracle(exe);rng=random.Random(0x504c4143)
    commands=[];expected=[];labels=[];groups={}
    def save(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)));labels.append(group)
        groups[group]=groups.get(group,0)+1
    edges=[-2147483648,-65536,-1,0,1,8,255,65535,2147483647]
    for fallback,present,value in itertools.product(edges,(0,1),edges):
        save('scoped_FireAngle_default_read_store_actual_missing_GetInt', ['M',fallback,present,value],o.metadata(fallback,present,value))
    def placement(group,**kw):
        frame=kw.get('frame',100)
        d=dict(frame=frame,direction=0,fire=8,accept=1,on_map=1,b0=0,b1=0,predicate=0,effect=0,cell=1,divisor=104,
               requested=[18304,29312,416],position=[18432,29440,416],field1f4=6,field114=-1,field373=1,field190=1,
               field400=7,field3ec=9,field3f0=11,location=[21,37],cell_value=17,cell_kind=3,owner_default=5,
               body=[0,0,frame,0,0],barrel=[0,0,frame,0,768])
        d.update(kw)
        v=[d[k] for k in ('frame','direction','fire','accept','on_map','b0','b1','predicate','effect','cell','divisor')]
        v+=d['requested']+d['position']+[d[k] for k in ('field1f4','field114','field373','field190','field400','field3ec','field3f0')]
        v+=d['location']+[d[k] for k in ('cell_value','cell_kind','owner_default')]+d['body']+d['barrel']
        construct=kw.get('construct',False)
        result=o.placement(v,construct);save(group,['C' if construct else 'P',*v],result);return result
    for fire,frame in itertools.product(range(256),(0,100,-1)):
        placement('all_FireAngle_low_bytes_actual_Facing_and_clock_samples',fire=fire,frame=frame,direction=(fire*257)&0xffff)
    for accept,on_map,b0,b1,predicate in itertools.product((0,1,255,256),(0,1,255),(0,1),(0,255),(0,1,256)):
        placement('base_acceptance_onmap_early_returns_bridge_and_predicate_low_bytes',accept=accept,on_map=on_map,b0=b0,b1=b1,predicate=predicate,cell=b0,effect=b1)
    for n in range(512):
        frame=rng.choice(edges)
        fs=lambda:[rng.randrange(65536),rng.randrange(65536),rng.choice(edges),rng.choice([0,1,17]),rng.choice([0,1,768,32512,32768])]
        placement('wrapped_words_signed_coordinates_height_and_existing_facings',frame=frame,direction=rng.choice(edges),fire=rng.choice(edges),
                  body=fs(),barrel=fs(),requested=[rng.choice(edges) for _ in range(3)],position=[rng.choice(edges) for _ in range(3)],
                  divisor=rng.choice([1,104,256,2147483647]),field1f4=rng.choice(edges),field114=rng.choice(edges),
                  field373=rng.randrange(256),field190=rng.randrange(256),field400=rng.choice(edges),
                  field3ec=rng.choice(edges),field3f0=rng.choice(edges),location=[rng.choice(edges),rng.choice(edges)],
                  cell_value=rng.choice(edges),cell_kind=rng.choice(edges),owner_default=rng.choice(edges),effect=n%2,cell=(n//2)%2)
    p=configparser.ConfigParser(interpolation=None,strict=False,allow_no_value=True,inline_comment_prefixes=(';',))
    p.read_string((assets/'rules.ini').read_text(encoding='latin1'))
    if p.get('HTNK','FireAngle',fallback=None) is not None:raise ValueError('Stock FireAngle absence changed; inspect new value')
    save('owned_HTNK_missing_FireAngle_default',['O',str((assets/'rules.ini').resolve())],o.metadata(8,False,0))
    stock=placement('stock_actual_FireAngle_defaults_and_Facing_initializers_then_complete_wrapper_and_pitch',construct=True)
    pitch=stock[stock.index('pitch')+1:];assert pitch==[16384,15360,14336,14336,14336],pitch
    return commands,expected,labels,{'groups':groups,'audited_callable_roots':o.audit_calls,'audited_scoped_blocks':o.audit_blocks,
        'actual_facing_writes':o.facing_writes,'actual_scalar_writes':o.scalar_writes,'supplied_stack_writes':o.host_writes,
        'actual_missing_GetInt_calls':o.missing_integer_calls,'supplied_present_GetInt_calls':o.present_integer_calls,
        'stock_FireAngle':8,'stock_pitch_samples':pitch}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--asset-dir',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-placement-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/placement-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a.exe,a.asset_dir);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh placement evidence exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a.exe,a.asset_dir);generation=time.monotonic()-now
        metadata['scope']=current['inspection']['scope'];report=out/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:raise AssertionError(f'Native runner failed: {error.stderr}') from error
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Placement result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe,a.asset_dir)!=current or hash_file(a.native)!=runner:raise ValueError('Placement inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 placement results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
