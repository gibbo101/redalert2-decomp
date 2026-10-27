#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential complete Unit/world and actual fresh/cached shadow children."""
import argparse,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_shadow_voxel_world import identities as shadow_identities
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_voxel_shadow_world import verify
SOURCES=('tests/compare_unit_voxel_shadow_world.py','tests/original_unit_voxel_shadow_world.py','tests/unit_voxel_shadow_world_vectors.cpp',
         'tools/verify_unit_voxel_shadow_world.py','src/render/UnitVoxelShadowWorld.hpp','src/render/UnitVoxelShadowWorld.cpp')
def identities(a):
    return {**shadow_identities(a),'unit_shadow_world_inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
            'unit_shadow_world_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Unit/shadow/world engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Unit/shadow/world identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Unit/shadow/world counts differ')
    for command in e['commands']:
        c=command.split()
        if not c or len(c)!=(3 if c[0]=='O' else 24) or c[0] not in ('O','D'):raise ValueError('Unknown Unit/shadow/world command')
        try:list(map(int,c[1:]))
        except ValueError:raise ValueError('Unknown Unit/shadow/world numeric command') from None

def generate(a):
    from original_unit_voxel_shadow_world import UnitVoxelShadowWorldOracle
    commands=[];expected=[];labels=[];groups={};audits=[]
    def save(label,command,row):
        commands.append(command);expected.append(list(map(str,row)));labels.append(label);groups[label]=groups.get(label,0)+1
    for pm in range(2):
        o=UnitVoxelShadowWorldOracle(a.exe,a.assets,bytes(768) if pm else a.palette.read_bytes())
        def reset(seed):o.begin_unit(seed);save('four_indexes_pool_and_persistent_staging_reset',f'O {pm} {seed}',['reset'])
        def draw(label,v):save(label,'D '+' '.join(map(lambda x:str(int(x)),v)),o.draw_complete(v))
        reset(3)
        count=32 if pm==0 else 8
        for n in range(count):
            body=n*(2048 if pm==0 else 8192);turret=((n*7+3)%32)*2048
            draw('complete_unit_cold_actual_lit_final_shadow_snapshot_recursive_pixels',
                 [n,0,0,0,0,body,turret,14336,1,0,7,1,0,1312,0,n%2,0,80,72,0,0,160,144])
            draw('complete_unit_warm_changed_pitch_brightness_camera_and_split_pixels',
                 [n+1,0,1,0,0,body,turret,16384,1,0,7,1,-1,65535,0,(n+1)%2,0,80,72,3,5,151,133])
        if pm==0:
            for n in range(31,-1,-2):
                draw('complete_unit_reverse_warm_signed_shadow_search_and_clipping',
                     [n,n%5,n%2,0,0,n*2048,((n*7+3)%32)*2048,15360,255,0,7,1,2147483647,1000+n*31,0,n%2,0,
                      (-5,5,150,170)[n%4],(4,72,140,155)[n%4],0,0,160,144])
        for mode in range(5 if pm==0 else 1):
            reset(11+mode)
            for n in range(8):
                draw('complete_unit_cell_depth_shadow_stencil_raw_bypass_NoShadow_and_saved_cleanup',
                     [mode*11+n,mode,n%2,n==7,n%3==0,n*8192,(n*8192+16384)%65536,14336,n%2,n%3==0,
                      7 if n%2 else 1,n%2,0,(-1,0,500,1000,2000,2200,65535,1312)[n],n%2,n%2,n%3,
                      80,72,n%3,n%4,156,139])
        if not o.shadow_spans or not o.raw_spans or not all(o.gradient_calls.values()):raise AssertionError('Missing complete Unit shadow/final coverage')
        audits.append({'palette_mode':pm,'audited_roots':o.audit_calls,'heap_allocations':len(o.allocations),
            'actual_unit_calls':o.unit_calls,'actual_world_calls':o.world_calls,'actual_shadow_calls':o.shadow_calls,'actual_foot_shadow_entries':o.foot_shadow_entries,
            'actual_raw_shadow_spans':o.raw_spans,'actual_rle_shadow_spans':o.shadow_spans,'checked_zero_shape_bytes':o.shape_bytes,
            'actual_gradient_surface_calls':o.gradient_calls,'actual_staging_surfaces':o.staging_surfaces,'changed_color_pixels':o.changed_pixels,
            'map_service_calls':o.map_queries,'dimension_service_writes':o.dimension_writes,'actual_joined_calls':o.joined_calls,
            'actual_cached_spans':o.cache_counts,'actual_raster_children':o.actual_calls,'bounded_snapshot_source_reads':o.pool_source_reads})
    return commands,expected,labels,{'groups':groups,'audits':audits,'world_dimensions':[160,144],'native_pool_capacity':0x80000}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets')
    p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-voxel-shadow-world-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/unit-shadow-world-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Unit/shadow/world destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Unit/shadow/world output counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:20]}, lengths {len(x)}/{len(y)}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Unit/shadow/world run inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
            'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 complete Unit/world/shadow results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
