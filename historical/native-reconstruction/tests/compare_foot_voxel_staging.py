#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential full Foot/cache/raster/pool/cached-staging join, supplied base."""
import argparse,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_voxel_snapshot import identities as snapshot_identities
from compare_voxel_part import poses
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_foot_voxel_staging import verify
SOURCES=('tests/compare_foot_voxel_staging.py','tests/original_foot_voxel_staging.py','tests/foot_voxel_staging_vectors.cpp',
 'tools/verify_foot_voxel_staging.py','tools/verify_foot_lit_draw.py','tools/verify_unit_voxel_draw.py','tools/verify_presentation_mapping.py',
 'src/render/FootVoxelStaging.hpp','src/render/FootVoxelStaging.cpp','src/render/FootLitDraw.hpp','src/render/FootLitDraw.cpp',
 'src/render/UnitLighting.hpp','src/render/UnitLighting.cpp')
def identities(a):
    return {**snapshot_identities(a),'joined_inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
            'joined_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Joined Foot engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Joined Foot identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Joined Foot counts differ')
    if any(not c.split() or c.split()[0] not in ('O','D') for c in e['commands']):raise ValueError('Unknown joined Foot command')
def generate(a):
    from original_foot_voxel_staging import FootVoxelStagingOracle
    bank=poses(a.exe,a.raster_data,a.poses);commands=[];expected=[];labels=[];groups={};audits=[]
    def save(label,command,row):
        commands.append(command);expected.append(list(map(str,row)));labels.append(label);groups[label]=groups.get(label,0)+1
    for pm in range(2):
        o=FootVoxelStagingOracle(a.exe,a.assets,bytes(768) if pm else a.palette.read_bytes())
        def draw(label,v):save(label,'D '+str(pm)+' '+' '.join(map(str,v)),o.draw_joined(v))
        for part in range(3):
            o.begin();save('native_index_and_supplied_pool_reset','O',['reset'])
            keys=[-2147483648,-2,0,31,2147483647]+[100+n*37 for n in range(27)]
            for heading,key in enumerate(keys):
                draw('actual_nested_cold_all_parts_headings_index_growth_and_sort',
                     [heading,part,key,1,0,1,heading%2,(-2147483648,-1,0,3,2147483647)[heading%5],1312,
                      128,128,0,0,256,256,0,0,0,0,*bank[heading][part]])
                draw('actual_nested_warm_before_model_validation_and_changed_pose',
                     [heading+1,part,key,1,0,0,(heading+1)%2,-1,65535,128,128,0,0,256,256,120,121,3,4,*bank[(heading+7)%32][part]])
            for heading in range(31,-1,-1):
                draw('actual_nested_warm_signed_search_and_changed_placement',
                     [heading,part,keys[heading],1,0,1,1,0,0,116,105,11,7,222,231,0,0,0,0,*bank[(heading+3)%32][part]])
            cases=[(0,0),(0,250),(250,0),(128,250),(128,-3),(-3,128),(128,128)]
            for n,(x,y) in enumerate(cases):
                for available,disabled,key in ((0,0,123),(1,1,keys[0]),(1,0,-1)):
                    draw('actual_nested_null_disabled_and_minus_one_bypass_clipped',
                         [n,part,key,available,disabled,1,n%2,0,(-1,0,1000,65535)[n%4],x,y,0,0,256,256,120,121,3,4,*bank[n%32][part]])
            for key,available,disabled in ((7654321,1,0),(keys[0],1,1),(-1,1,0),(keys[0],0,0)):
                draw('actual_nested_invalid_miss_and_invalid_bypass_retains_pixels',
                     [3,part,key,available,disabled,0,1,0,1312,128,128,0,0,256,256,120,121,3,4,*bank[0][part]])
        audits.append({'palette_mode':pm,'audited_roots':o.audit_calls,'heap_allocations':len(o.allocations),
                       'actual_joined_calls':o.joined_calls,'actual_cached_spans':o.cache_counts,
                       'actual_raster_children':o.actual_calls,'bounded_snapshot_source_reads':o.pool_source_reads,'loader_allocator_services':o.counts})
    return commands,expected,labels,{'groups':groups,'audits':audits,'source_pose_scenarios':32,'native_pool_capacity':0x80000}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets')
    p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/foot-voxel-staging-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/foot-stage-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh joined Foot destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Joined Foot output counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:20]}, lengths {len(x)}/{len(y)}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Joined Foot run inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
            'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 nested Foot/cache/staging results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
