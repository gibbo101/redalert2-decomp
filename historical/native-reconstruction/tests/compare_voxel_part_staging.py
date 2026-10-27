#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare complete part root with actual byte Convert selection and staging copy."""
import argparse,itertools,json,subprocess,time
from pathlib import Path
from compare_original import PATCHED_EXPECTED,write_report
from compare_terrain_visibility import ROOT
from compare_voxel_part import identities as part_identities,poses
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_voxel_part_staging import verify
SOURCES=('tests/compare_voxel_part_staging.py','tests/original_voxel_part_staging.py',
 'tests/voxel_part_staging_vectors.cpp','tools/verify_voxel_part_staging.py','tools/verify_staging_mapping.py',
 'tools/verify_composition_mapping.py','tools/verify_voxel_cache_mapping.py','tests/original_staging.py',
 'tests/original_shadow_color.py','tests/original_composition.py','tests/staging_profiles.py',
 'tests/shadow_color_profiles.py','tests/composition_profiles.py','tests/voxel_cache_profiles.py',
 'src/render/VoxelPartStaging.hpp','src/render/VoxelPartStaging.cpp','src/render/UnitStaging.hpp',
 'src/render/UnitStaging.cpp')
def identities(a):
    return {**part_identities(a),'nested_inspection':verify((ROOT/'private/disc-allied/game.exe').read_bytes(),a.exe.read_bytes()),
            'palette_sha256':hash_file(a.palette),'nested_sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Staging part engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Staging part identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Staging part counts differ')
    if any(c.split()[0] not in ('M','S') for c in e['commands']):raise ValueError('Unknown staging part command')
def generate(a):
    from original_voxel_part_staging import VoxelPartStagingOracle
    bank=poses(a.exe,a.raster_data,a.poses);commands=[];expected=[];labels=[];groups={};audits=[]
    def save(label,command,row):
        commands.append(command);expected.append(list(map(str,row)));labels.append(label);groups[label]=groups.get(label,0)+1
    for pm in range(2):
        palette=bytes(768) if pm else a.palette.read_bytes();o=VoxelPartStagingOracle(a.exe,a.assets,palette)
        save('actual_byte_converter_remap',f'M {pm}',['remap',*o.mapping])
        def draw(label,v):save(label,'S '+str(pm)+' '+' '.join(map(str,v)),o.draw_staging(v))
        for part,heading in itertools.product(range(3),range(32)):
            draw('actual_staged_stock_body_turret_settled_barrel_all_headings',
                [heading,part,1,0,128,128,0,0,256,256,1312,*bank[heading][part]])
        clips=[(-3,128,0,0,256,256),(257,128,0,0,256,256),(128,-3,0,0,256,256),
               (128,257,0,0,256,256),(128,128,0,0,0,256),(116,105,11,7,222,231)]
        for n,(heading,clip) in enumerate(itertools.product((0,7,16,31),clips)):
            part=n%3;mode=(0,2)[n%2]
            draw('actual_staged_clipping_HVA_and_zero_remap_erasure',
                 [n,part,mode,(-2147483648,-1,1,2147483647)[n%4],*clip,(-1,0,1000,65535)[n%4],*bank[heading][part]])
        audits.append({'palette_mode':pm,'audited_roots':o.audit_calls,'heap_allocations':len(o.allocations),
                       'actual_selector_calls':len(o.selected),'actual_surface_calls':o.draws,'actual_indexed_spans':o.spans,
                       'actual_raster_children':o.actual_calls,'loader_services':o.counts})
    return commands,expected,labels,{'groups':groups,'audits':audits,'source_pose_scenarios':32}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/raster/assets')
    p.add_argument('--palette',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/staging/assets/temperat.pal')
    p.add_argument('--raster-data',type=Path,default=ROOT/'private/derived/ra2-1006/raster-data.bin')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--poses',type=Path,default=ROOT/'private/unit-draw-1006/barrel-v1/expected.json')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/voxel-part-staging-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/part-stage-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report or (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh staging destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=out/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.raster_data),str(a.render_data),str(a.assets),str(a.palette)],
        input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Staging part output counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {[(i,xx,yy) for i,(xx,yy) in enumerate(zip(x,y)) if xx!=yy][:20]}, lengths {len(x)}/{len(y)}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Staging run inputs changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,
        'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
        'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
        'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 nested part/staging results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
