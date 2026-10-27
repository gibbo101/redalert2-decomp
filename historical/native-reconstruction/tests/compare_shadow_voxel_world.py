#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential complete shadow cache/render/snapshot/raw or cached world pixels."""
import argparse,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_cached_voxel_shadow import identities as cached_identities
from compare_voxel_part import poses
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_shadow_voxel_world import verify
SOURCES=('tests/compare_shadow_voxel_world.py','tests/original_shadow_voxel_world.py','tests/shadow_voxel_world_vectors.cpp',
         'tools/verify_shadow_voxel_world.py','tools/verify_shadow_color_mapping.py','tests/shadow_color_profiles.py',
         'src/render/ShadowVoxelWorld.hpp','src/render/ShadowVoxelWorld.cpp','src/render/ShadowCache.hpp')
def identities(a):
    return {**cached_identities(a),'shadow_world_inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
            'shadow_world_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Shadow/world engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Shadow/world identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Shadow/world counts differ')
    for command in e['commands']:
        c=command.split()
        if c==['O']:continue
        if len(c)!=35 or c[0]!='D':raise ValueError('Unknown shadow/world command')
        try:list(map(int,c[1:]))
        except ValueError:raise ValueError('Unknown shadow/world numeric command') from None

def generate(a):
    from original_shadow_voxel_world import ShadowVoxelWorldOracle
    bank=poses(a.exe,a.raster_data,a.poses)
    o=ShadowVoxelWorldOracle(a.exe,a.assets,a.palette.read_bytes());commands=[];expected=[];labels=[];groups={}
    def save(label,command,row):
        commands.append(command);expected.append(list(map(str,row)));labels.append(label);groups[label]=groups.get(label,0)+1
    def reset():o.begin();save('shadow_index_and_supplied_pool_reset','O',['reset'])
    def draw(label,part,key,heading=0,seed=3,available=1,disabled=0,bad=0,suppressed=0,no_shadow=0,allow=1,mode=1,stencil=0,
             point=(80,72),clip=(0,0,160,144),z=-1,dirty=(0,0,0,0)):
        v=[seed,part,key,available,disabled,bad,suppressed,no_shadow,allow,mode,stencil,*point,*clip,z,*dirty,*bank[heading][part]]
        save(label,'D '+' '.join(map(str,v)),o.draw_full_shadow(v))
    keys=[-2147483648,-2,0,31,2147483647]+[100+n*37 for n in range(27)]
    profiles=(((80,72),(0,0,160,144),-1),((-8,8),(3,5,151,133),0),((145,132),(0,0,160,144),12),
              ((-90,-80),(1,2,157,140),-90),((10,15),(20,19,101,100),32768),((159,143),(0,0,160,144),-32768),
              ((0,0),(0,0,160,144),32767),((40,40),(0,0,0,144),1))
    for part in range(3):
        reset()
        for heading,key in enumerate(keys):
            draw('actual_cold_all_parts_headings_HVA_frame_zero_stencil_growth_recursive_hit',part,key,heading,heading,
                 mode=1+heading%2,stencil=heading%2,dirty=(5,7,13,17))
            draw('warm_current_HVA_absent_changed_pose_stencil_and_planes',part,key,(heading+7)%32,heading+1,
                 mode=0,stencil=(heading+1)%2,dirty=(248,249,24,23))
        for heading in range(31,-1,-1):
            point,clip,z=profiles[heading%8]
            draw('warm_reverse_signed_search_changed_clipping_and_depth',part,keys[heading],(heading+3)%32,heading,
                 mode=0,stencil=1,point=point,clip=clip,z=z,dirty=(-9,-11,13,17))
        for n,(point,clip,z) in enumerate(profiles):
            for available,disabled,key in ((0,0,7654321),(1,1,keys[0]),(1,0,-1)):
                draw('null_disabled_minus_one_raw_bypass_ignores_rebuild_guard_no_dirty_union',part,key,n,n,
                     available=available,disabled=disabled,allow=0,mode=1+n%2,stencil=n%2,
                     point=point,clip=clip,z=z,dirty=(5,7,13,17))
        for bad,suppressed,no_shadow in ((1,0,0),(0,1,0),(0,0,1),(1,1,1)):
            for key in (keys[0],987654321,-1):
                draw('actor_type_model_prechecks_before_warm_lookup_or_bypass',part,key,bad=bad,suppressed=suppressed,
                     no_shadow=no_shadow,mode=0,dirty=(5,7,13,17))
        draw('cacheable_cold_miss_disallowed_without_HVA',part,987654321,allow=0,mode=0)
    if not o.raw_spans or not o.shadow_spans or not o.pool_source_reads:raise AssertionError('Missing actual raw/cached/raster/pool coverage')
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'heap_allocations':len(o.allocations),
        'actual_shadow_calls':o.shadow_calls,'actual_rle_shadow_spans':o.shadow_spans,'actual_raw_shadow_spans':o.raw_spans,
        'checked_zero_shape_bytes':o.shape_bytes,'bounded_snapshot_source_reads':o.pool_source_reads,'actual_nested_calls':o.joined_calls,
        'source_pose_scenarios':32,'world_dimensions':[160,144],'native_pool_capacity':0x80000}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets')
    p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/shadow-voxel-world-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/shadow-world-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh shadow/world destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Shadow/world output counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:20]}, lengths {len(x)}/{len(y)}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Shadow/world run inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
            'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 complete shadow cache/render/world results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
