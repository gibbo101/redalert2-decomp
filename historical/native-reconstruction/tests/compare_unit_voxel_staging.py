#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential complete Unit/cache/raster/staging/pool/cleanup join, supplied base."""
import argparse,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_foot_voxel_staging import identities as foot_identities
from compare_voxel_part import poses
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_voxel_staging import verify
SOURCES=('tests/compare_unit_voxel_staging.py','tests/original_unit_voxel_staging.py','tests/unit_voxel_staging_vectors.cpp',
 'tools/verify_unit_voxel_staging.py','tools/verify_map_light_mapping.py','tests/map_light_profiles.py',
 'src/render/UnitVoxelStaging.hpp','src/render/UnitVoxelStaging.cpp',
 'src/render/UnitVoxelDraw.hpp','src/render/UnitVoxelDraw.cpp')
def identities(a):
    return {**foot_identities(a),'unit_inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
            'unit_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Joined Unit engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Joined Unit identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Joined Unit counts differ')
    if any(not c.split() or c.split()[0] not in ('O','D') for c in e['commands']):raise ValueError('Unknown joined Unit command')
def generate(a):
    from original_unit_voxel_staging import UnitVoxelStagingOracle
    commands=[];expected=[];labels=[];groups={};audits=[]
    def save(label,command,row):
        commands.append(command);expected.append(list(map(str,row)));labels.append(label);groups[label]=groups.get(label,0)+1
    for pm in range(2):
        o=UnitVoxelStagingOracle(a.exe,a.assets,bytes(768) if pm else a.palette.read_bytes())
        def reset(seed):o.begin_unit(seed);save('three_indexes_supplied_pool_and_patterned_surface_reset',f'O {pm} {seed}',['reset'])
        def draw(label,v):save(label,'D '+' '.join(map(str,v)),o.draw_unit(v))
        reset(3)
        for n in range(32):
            body=n*2048;turret=((n*7+3)%32)*2048
            draw('complete_unit_cold_parts_headings_order_growth_and_sort',
                 [body,turret,14336,1,0,7,1,0,1312,0,n%2,0,30,40,0,0,320,240])
            draw('complete_unit_warm_changed_pose_brightness_and_missing_models',
                 [body,turret,16384,1,0,0,1,-1,65535,1,n%2,0,-3,7,11,7,211,201])
        for n in range(31,-1,-1):
            draw('complete_unit_reverse_warm_queries_and_persistent_cleanup',
                 [n*2048,((n*7+3)%32)*2048,15360,255,0,7,1,2147483647,0,255,n%2,0,250,9,0,0,320,240])
        for disabled,valid,gate,barrel in ((1,7,1,1),(0,7,0,1),(0,3,1,0),(0,1,1,1)):
            draw('warm_prechecks_before_disabled_bypass_and_optional_model_change',
                 [0,6144,0,gate,disabled,valid,barrel,0,1312,0,1,0,9,7,0,0,256,256])
        for mask in (1,3,5):
            reset(19+mask)
            for k,valid in enumerate((mask,7,7)):
                draw('independent_body_turret_barrel_cold_warm_prechecks',
                     [4096,32768,14336+k*1024,1,0,valid,1,0,1000+k*500,0,1,0,17,23,0,0,256,256])
        # Reset isolates pitch/cache scenarios. Same key + changed pitch retains
        # a warm snapshot; bypass exposes the changed geometry. No invalidation
        # or actor-timing claim follows from these supplied consecutive headings.
        for n,(disabled,gate,barrel,valid,empty) in enumerate(((0,1,1,7,1),(1,1,1,7,2),(0,0,1,7,0),
                (0,1,0,3,1),(0,1,1,0,2),(1,1,0,0,0))):
            reset(7+n)
            for k,pitch in enumerate((16384,15360,14336,0)):
                draw('complete_unit_bypass_missing_optional_barrel_invalid_and_clipped_cleanup',
                     [2048,61440,pitch,gate,disabled,valid,barrel,k,(-1,0,1000,65535)[k],k%2,0,empty,-5,3,0,0,0 if k==3 else 256,256])
        audits.append({'palette_mode':pm,'audited_roots':o.audit_calls,'heap_allocations':len(o.allocations),
                       'actual_unit_calls':o.unit_calls,'actual_joined_calls':o.joined_calls,'actual_cached_spans':o.cache_counts,
                       'actual_raster_children':o.actual_calls,'bounded_snapshot_source_reads':o.pool_source_reads})
    return commands,expected,labels,{'groups':groups,'audits':audits,'native_pool_capacity':0x80000}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets')
    p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-voxel-staging-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/unit-stage-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh joined Unit destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Joined Unit output counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:20]}, lengths {len(x)}/{len(y)}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Joined Unit run inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
            'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 nested Unit/cache/staging/cleanup results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
