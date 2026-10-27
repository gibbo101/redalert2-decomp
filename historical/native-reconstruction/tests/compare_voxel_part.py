#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact staged part wrapper and actual raster, using owned single-section models."""
import argparse,itertools,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_voxel_part import verify
from verify_raster_mapping import verify as raster_verify
from compare_unit_voxel_draw import identities as pose_identities,validate as pose_validate
SOURCES=('tests/compare_voxel_part.py','tests/original_voxel_part.py','tests/voxel_part_vectors.cpp',
 'tools/verify_voxel_part.py','tools/verify_raster_mapping.py','tests/original_raster.py','tests/raster_profiles.py',
 'tests/original_presentation.py','tests/presentation_profiles.py','tests/original_foot_lit.py',
 'tests/compare_unit_voxel_draw.py','tests/presentation_evidence.py','src/render/VoxelPartDraw.hpp',
 'src/render/VoxelPartDraw.cpp','src/render/VoxelRaster.hpp','src/render/VoxelRaster.cpp','src/render/Lighting.hpp',
 'src/render/Lighting.cpp','src/assets/Formats.hpp','src/assets/Formats.cpp','src/assets/RasterData.hpp',
 'src/assets/RasterData.cpp','src/assets/RenderData.hpp','src/assets/RenderData.cpp','src/assets/PreparedData.hpp',
 'src/assets/PreparedData.cpp','src/sim/OriginalMath.hpp')
def poses(exe,raster,source):
    e=json.loads(source.read_text());r=json.loads((source.parent/'report.json').read_text())
    pose_validate(e,r,hash_file(source),pose_identities(exe,raster));result=[]
    for command,row,label in zip(e['commands'],e['expected'],e['labels']):
        if label!='stock_settled_barrel_all_body_turret_bins_cold':continue
        args=list(map(int,command.split()[1:]));body,turret=args[:2]
        if turret!=(body+8192)%65536:continue
        parts={int(row[i+1]):list(map(int,row[i+13:i+25])) for i,v in enumerate(row) if v=='lit'}
        result.append([parts[0xb0],parts[0xb8],parts[0xc0]])
    if len(result)!=32:raise ValueError('Expected all 32 original stock pose pairs')
    return result
def identities(a):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','inspection':verify(a.exe.read_bytes()),
        'raster_inspection':raster_verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
        'raster_data_sha256':hash_file(a.raster_data),'render_data_sha256':hash_file(a.render_data),
        'pose_expectations_sha256':hash_file(a.poses),'pose_identities':pose_identities(a.exe,a.raster_data),
        'sources':{p:hash_file(ROOT/p) for p in SOURCES},
        'assets':{name:hash_file(a.assets/name) for name in ('htnk.vxl','htnktur.vxl','htnkbarl.vxl','voxels.vpl')}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Part engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Part source/asset/pose/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Part counts differ')
    if any(c.split()[0]!='P' for c in e['commands']):raise ValueError('Unknown part command')
def generate(a):
    from original_voxel_part import VoxelPartOracle
    bank=poses(a.exe,a.raster_data,a.poses);o=VoxelPartOracle(a.exe,a.assets)
    commands=[];expected=[];labels=[];groups={}
    def save(label,v):
        expected.append(list(map(str,o.draw(v))));commands.append('P '+' '.join(map(str,v)));labels.append(label);groups[label]=groups.get(label,0)+1
    for part,mode,heading in itertools.product(range(3),range(3),range(32)):
        save('actual_raster_stock_body_turret_settled_barrel_HVA_absent_identity_and_three_frames',
             [part,mode,[-2147483648,-1,0,1,2,3,2147483647][heading%7],128,128,0,0,256,256,1312,0x2800,0,0,0,0,0,17,29,*bank[heading][part]])
    for n,(f204,f205,house,predicate) in enumerate(itertools.product((0,1,255),(0,1),(0,1,256),(0,1,256))):
        save('actual_flag_short_circuit_house_low_byte_adjustment_and_wrapped_draw_forwarding',
             [n%3,n%3,-1,-2147483648,2147483647,-7,11,256,256,-1,0x2810,f204,f205,house,predicate,
              0xfffffff7,-2147483648,2147483647,*bank[n%32][n%3]])
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'loader_services':o.counts,
        'actual_nested_calls':o.actual_calls,'heap_allocations':len(o.allocations),'source_pose_scenarios':32}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/voxel-part-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/part-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report or (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh part evidence destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=out/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Part output counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:20]}, lengths {len(x)}/{len(y)}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Part run inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,
        'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
        'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
        'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 complete staged part/raster results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
