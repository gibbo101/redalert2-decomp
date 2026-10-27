#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-base complete healthy Unit voxel caller against readable C++."""
import argparse,itertools,json,random,subprocess,time
from pathlib import Path
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_voxel_draw import verify
SOURCES=('tests/compare_unit_voxel_draw.py','tests/original_unit_voxel_draw.py',
         'tests/unit_voxel_draw_vectors.cpp','tools/verify_unit_voxel_draw.py',
         'tests/original_foot_lit.py','tests/original_presentation.py','tests/presentation_profiles.py',
         'tests/compare_original.py','tests/presentation_evidence.py',
         'tools/verify_terrain_visibility.py','src/render/UnitVoxelDraw.hpp','src/render/UnitVoxelDraw.cpp',
         'src/render/FootLitDraw.hpp','src/render/FootLitDraw.cpp','src/render/VoxelCache.hpp','src/render/VoxelCache.cpp',
         'src/render/ShadowKeys.hpp','src/render/ShadowKeys.cpp','src/render/Composition.hpp','src/render/Composition.cpp',
         'src/render/VoxelRaster.hpp','src/render/VoxelRaster.cpp','src/render/Lighting.hpp',
         'src/assets/RasterData.hpp','src/assets/RasterData.cpp','src/assets/PreparedData.hpp','src/assets/PreparedData.cpp',
         'src/assets/Archive.hpp','src/assets/Formats.hpp','src/sim/OriginalMath.hpp')
def identities(exe,raster):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'raster_data_sha256':hash_file(raster),
            'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Unit voxel engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Unit voxel source/data/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Unit voxel counts differ')
    if any(c.split()[0] not in ('V','B') for c in e['commands']):raise ValueError('Unknown Unit voxel command')
def generate(exe):
    from original_unit_voxel_draw import UnitVoxelDrawOracle
    oracle=UnitVoxelDrawOracle(exe);rng=random.Random(0x52413239)
    commands=[];expected=[];labels=[];groups={}
    def save(group,v):
        commands.append(('B ' if len(v)==21 else 'V ')+' '.join(map(str,v)));expected.append(list(map(str,oracle.draw(v))))
        labels.append(group);groups[group]=groups.get(group,0)+1
    for body,turret,warm in itertools.product(range(32),range(32),range(2)):
        save('complete_root_actual_Drive_Foot_matrix_and_cold_warm_part_order',
             [body*2048,turret*2048,0,1,1,warm,1,200,100,0,0,400,300,1312,1400,
              (body+turret)%2,body%2,1000,2000,416])
    headings=sorted({(n*2048+d)&65535 for n in range(32) for d in (-1025,-1024,-1023,0,1023,1024,1025)})
    for n,heading in enumerate(headings):
        save('heading_quantization_and_missing_barrel',
             [heading,headings[(n*7)%len(headings)],0,1,[0,1,255][n%3],n%2,0,
              -1,2147483647,-19,7,0,25,0,-1,[0,1,2,255,256,257][n%6],n%2,-257,255,-1])
    edges=[-2147483648,-2147483647,-65536,-1,0,1,31,32,33,65535,2147483646,2147483647]
    for n in range(1024):
        save('signed_HVA_remainder_key_gate_wrapped_arguments_and_predicate_low_byte',
             [rng.randrange(65536),rng.randrange(65536),rng.choice(edges),rng.choice([1,2,31,32,33,256,2147483647]),
              rng.choice([0,1,2,127,255]),rng.randrange(2),rng.randrange(2),
              *[rng.choice(edges) for _ in range(8)],rng.choice([0,1,2,255,256,257]),rng.randrange(2),
              *[rng.choice(edges) for _ in range(3)]])
    # Steady original-facing inputs: stock placement's three sampled angles
    # quantize to neutral, neutral and bin 7. These are not firing/timer recovery.
    for body,turret in itertools.product(range(32),range(32)):
        save('stock_settled_barrel_all_body_turret_bins_cold',
             [body*2048,turret*2048,0,1,1,0,1,200,100,0,0,400,300,1312,1400,
              (body+turret)%2,body%2,1000,2000,416,14336])
    for pitch,warm,barrel,gate,camera in itertools.product(range(32),range(4),range(2),(0,1),range(2)):
        save('all_pitch_bins_independent_hot_empty_parts_missing_barrel_and_bypass',
             [(pitch*7%32)*2048,(pitch*11%32)*2048,0,1,gate,warm,barrel,
              200,100,0,0,400,300,1312,1400,pitch%2,camera,1000,2000,416,pitch*2048])
    for n,heading in enumerate(headings):
        save('pitch_quantization_ties_wrap_and_intermediate_stock_sample',
             [headings[n],headings[(n*13)%len(headings)],0,1,1,0,1,200,100,
              0,0,400,300,1312,1400,0,n%2,1000,2000,416,heading])
    for pitch in (16384,15360,14336):
        save('stock_placement_pitch_samples_supplied_to_complete_drawing_root',
             [0,8192,0,1,1,0,1,200,100,0,0,400,300,1312,1400,0,1,1000,2000,416,pitch])
    return commands,expected,labels,{'groups':groups,'audited_roots':oracle.audit_calls,
        'guarded_supplied_writes':oracle.host_writes,'actual_pitch_rotation_calls':oracle.pitch_rotations,
        'actual_barrel_Facing_calls':oracle.barrel_facing_reads,'actual_pose_builds':oracle.pose_builds,
        'actual_warm_pose_copies':oracle.warm_pose_copies,'seed':0x52413239}
def native(path,raster,commands):
    proc=subprocess.run([str(path),str(raster)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    return [line.split() for line in proc.stdout.splitlines()]
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-voxel-draw-vectors')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/voxel-root')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a.exe,a.raster_data);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh Unit voxel evidence exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a.exe);generation=time.monotonic()-now
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,a.raster_data,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Unit voxel result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: differences {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:16]}, counts {len(x)}/{len(y)}')
    if identities(a.exe,a.raster_data)!=current or hash_file(a.native)!=runner:raise ValueError('Unit voxel run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start,
            'scope':current['inspection']['scope']+' Complete root stack/return/callee-saved, execution allowlist and arena/image-write guards. Cache prechecks use independently hot matching entries or empty counts; no cold-search/nonempty indexes. Foot forwards into supplied final Techno children. Pose key gate at 0x839A58 is a raw input, not recovered startup/global ownership.'}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 complete healthy Unit voxel results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
