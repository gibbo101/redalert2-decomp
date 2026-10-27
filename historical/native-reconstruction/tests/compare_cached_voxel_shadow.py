#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential complete compressed Unit/world shadow child and RGB565 pixels."""
import argparse,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_unit_voxel_world import identities as world_identities
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_cached_voxel_shadow import verify
SOURCES=('tests/compare_cached_voxel_shadow.py','tests/original_cached_voxel_shadow.py','tests/cached_voxel_shadow_vectors.cpp',
         'tools/verify_cached_voxel_shadow.py','src/render/CachedVoxelShadow.hpp','src/render/CachedVoxelShadow.cpp',
         'src/render/VoxelShadow.cpp','src/render/VoxelShadow.hpp','src/render/VoxelSnapshot.cpp','src/render/VoxelSnapshot.hpp')
def identities(a):
    return {**world_identities(a),'cached_shadow_inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
            'cached_shadow_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Cached shadow engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Cached shadow identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Cached shadow counts differ')
    if any(len(c.split())!=17 for c in e['commands']):raise ValueError('Unknown cached shadow command')
def generate(a):
    from original_cached_voxel_shadow import CachedVoxelShadowOracle
    o=CachedVoxelShadowOracle(a.exe,a.assets,a.palette.read_bytes());commands=[];expected=[];labels=[]
    profiles=((80,72,0,0,160,144,-1,0,0,0,0),(-8,8,3,5,151,133,0,5,7,13,17),
              (145,132,0,0,160,144,12,248,249,24,23),(-90,-80,1,2,157,140,-90,100,110,25,16),
              (10,15,20,19,101,100,32768,5,7,13,17),(159,143,0,0,160,144,-32768,0,0,0,0),
              (0,0,0,0,160,144,32767,-9,-11,13,17),(40,40,0,0,0,144,1,0,0,0,0))
    for mode in range(4):
        for size,(w,h) in enumerate(((1,1),(16,8),(32,24),(128,48),(256,64))):
            for n,p in enumerate(profiles):
                v=[3+size+n,mode,w,h,-5,-8,*p]
                commands.append(' '.join(map(str,v)));expected.append(list(map(str,o.draw_shadow(v))))
                labels.append('actual_cached_shadow_clipping_depth_zero_shape_and_dirty_bounds')
    if not o.shadow_spans or not o.shape_bytes:raise AssertionError('No actual compressed shadow/Z-shape coverage')
    return commands,expected,labels,{'groups':{labels[0]:len(commands)},'audited_roots':o.audit_calls,
                                   'actual_rle_shadow_spans':o.shadow_spans,'checked_zero_shape_bytes':o.shape_bytes,'world_dimensions':[160,144]}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets')
    p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/cached-voxel-shadow-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/cached-shadow-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh cached shadow destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Cached shadow output counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Cached shadow run inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
            'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 cached Unit/world shadow results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
