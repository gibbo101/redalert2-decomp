#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare original compressed voxel rows, pool append and cached staging pixels."""
import argparse,itertools,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_voxel_part_staging import identities as staging_identities
from compare_voxel_part import poses
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_voxel_snapshot import verify
SOURCES=('tests/compare_voxel_snapshot.py','tests/original_voxel_snapshot.py','tests/voxel_snapshot_vectors.cpp',
         'tools/verify_voxel_snapshot.py','src/render/VoxelSnapshot.hpp','src/render/VoxelSnapshot.cpp')
def identities(a):
    return {**staging_identities(a),'snapshot_inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
            'snapshot_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Snapshot engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Snapshot identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Snapshot counts differ')
    if any(c.split()[0] not in ('R','S','B') for c in e['commands']):raise ValueError('Unknown snapshot command')
def generate(a):
    from original_voxel_snapshot import VoxelSnapshotOracle,pixels
    bank=poses(a.exe,a.raster_data,a.poses);commands=[];expected=[];labels=[];groups={};audits=[]
    def save(label,command,result):
        commands.append(command);expected.append(list(map(str,result)));labels.append(label);groups[label]=groups.get(label,0)+1
    for pm in range(2):
        palette=bytes(768) if pm else a.palette.read_bytes();o=VoxelSnapshotOracle(a.exe,a.assets,palette)
        if pm==0:
            for w,mode,pad in itertools.product((0,1,2,3,7,254,255,256,257,509,510,511,512,1024,4096),range(4),((0,0),(0,71),(93,0))):
                source=pixels(0,mode,max(w,1),1)[:w]+bytes(pad)
                save('row_length_count_only_decode_and_inclusive_zero_lookahead',f'R {w} {source.hex()}',o.row(w,source))
        def synthetic(label,seed,mode,w,h,crop,capacity=65536,cursor=7,draw=None):
            v=[pm,seed,mode,w,h,*crop,capacity,cursor];result,row=o.snapshot(pixels(seed,mode,w,h),w,h,crop,capacity,cursor)
            if result:
                draw=draw or [seed,128,128,0,0,256,256,0,0,0,0,0,1312]
                row+=o.cached(result,draw);v+=draw
            save(label,'S '+' '.join(map(str,v)),row)
        for mode,w,h in itertools.product(range(4),(1,7,255,256),(1,3)):
            synthetic('snapshot_full_rows_and_warm_cached_pixels',0,mode,w,h,[-3,-2,0,0,w,h])
        # Each capacity boundary includes the header/previous rows without rollback.
        for capacity,cursor in itertools.product((0,7,11,12,13,15,16,17,19,20,23,24,30,40,80,100),(0,7)):
            if cursor<=capacity:synthetic('snapshot_capacity_failure_and_retained_prefix',71,2,13,3,[65535,65536,1,0,11,3],capacity,cursor)
        for seed,(point,clip,dirty) in enumerate(itertools.product(
                ((-10,0),(250,128),(128,-10),(128,250),(128,128)),
                ((0,0,256,256),(11,7,222,231),(0,0,0,256),(0,0,256,0)),
                ((0,0,0,0),(120,121,3,4)))):
            synthetic('cached_clipping_relative_origin_dirty_union_and_zero_erasure',seed,2,40,5,[-3,-2,0,0,40,5],
                      draw=[seed,*point,*clip,*dirty,0x10 if seed%2 else 0,(-1,0,1000,65535)[seed%4]])
        for w,h in ((0,0),(0,3),(3,0)):
            synthetic('empty_snapshot_dimensions',19,1,8,8,[-32768,32767,0,0,w,h])
        for part,heading in itertools.product(range(3),range(32)):
            seed=heading;v=[seed,part,1,0,128,128,0,0,256,256,1312,*bank[heading][part]]
            rendered=o.draw_staging(v);raw=bytes(o.u.mem_read(o.va(0xacae68),65536))+bytes([seed,seed*3%256])
            crop=list(map(int,rendered[1:7]));snap,row=o.snapshot(raw,256,256,crop,65536,7);assert snap
            draw=[seed,128,128,0,0,256,256,120,121,3,4,0,1312]
            save('actual_part_raster_snapshot_then_cached_staging_stock_all_headings',
                 'B '+' '.join(map(str,[pm,seed,part,*bank[heading][part],*draw])),
                 ['raster',*rendered[-2:],*row,*o.cached(snap,draw)])
        audits.append({'palette_mode':pm,'audited_roots':o.audit_calls,'allocations':len(o.allocations),
                       'actual_cached_calls':o.cache_counts,'actual_fresh_raster':o.actual_calls,
                       'source_byte_reads':o.source_reads,'maximum_source_read_extent':o.max_source_read})
    return commands,expected,labels,{'groups':groups,'audits':audits,'source_pose_scenarios':32}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets')
    p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/voxel-snapshot-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/snapshot-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh snapshot destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Snapshot output counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:20]}, lengths {len(x)}/{len(y)}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Snapshot run inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
            'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 voxel snapshot/cached results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
