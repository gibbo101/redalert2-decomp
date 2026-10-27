#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare exact-engine wall owner and nested Cell-target distance/getters."""
import argparse,json,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_wall_owner import verify
SOURCES=('src/assets/MapWallOwner.hpp','src/assets/MapWallOwner.cpp','src/assets/MapCellInputs.hpp',
 'src/assets/RenderData.hpp','src/assets/RenderData.cpp','src/assets/Bytes.hpp',
 'src/sim/Drive.hpp','src/sim/OriginalMath.hpp','src/render/Lighting.hpp','src/render/Lighting.cpp',
 'tests/map_wall_owner_vectors.cpp','tests/compare_map_wall_owner.py','tests/original_map_wall_owner.py',
 'tools/verify_map_wall_owner.py','tools/verify_tile_image.py','tools/verify_terrain_visibility.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py')
def command(mode,overlay,wall,owner,position,height,rows):
    return ' '.join(map(str,[mode,overlay,wall,owner,*([position,height] if mode=='W' else []),len(rows),*[v for row in rows for v in row]]))
def parse(cmd):
    p=cmd.split();mode=p[0];assert mode in ('W','S');v=list(map(int,p[1:]));overlay,wall,owner=v[:3]
    assert -1<=overlay<8 and 0<=wall<=255 and -2147483648<=owner<=2147483647
    if mode=='W':position,height=v[3:5];at=5;assert 0<=position<=4294967295 and -2147483648<=height<=2147483647
    else:position=height=0;at=3
    count=v[at];at+=1;stride=10 if mode=='W' else 5
    assert 0<=count<=1024 and len(v)==at+count*stride
    rows=[v[i:i+stride] for i in range(at,len(v),stride)]
    for row in rows:
        assert all(0<=n<=255 for n in row[:3]) and -2147483648<=row[3]<=2147483647
        assert all(-2147483648<=n<=2147483647 for n in row[4:])
        if mode=='W':assert 0<=row[4]<22 and all(0<=n<=64 for n in row[5:7])
    return mode,overlay,wall,owner,position,height,rows
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'render_data_sha256':hash_file(a.render_data)}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Wall owner engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Wall owner source/inspection/input identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Wall owner counts differ')
    for cmd in e['commands']:
        try:parse(cmd)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed wall owner command') from None
def generate(a):
    from original_map_wall_owner import MapWallOwnerOracle
    o=MapWallOwnerOracle(a.exe);p=pefile.PE(str(a.exe));rng=random.Random(0x57414c4c)
    widths=struct.unpack('<22i',p.get_data(0x7cfc70-0x400000,88));heights=struct.unpack('<22i',p.get_data(0x7cfcc8-0x400000,88))
    commands=[];expected=[];labels=[];groups={}
    def add(label,mode,overlay,wall,owner,position,height,rows):
        cmd=command(mode,overlay,wall,owner,position,height,rows);args=parse(cmd)
        expected.append(o.run(*args));commands.append(cmd);labels.append(label);groups[label]=groups.get(label,0)+1
    for overlay,wall in ((-1,1),(0,0),(7,255)):
        add('early_owner_preservation_or_empty_registry_store','W',overlay,wall,123,0,0,[])
    # Explicit selector-only diagnostic service covers the signed sentinel and
    # tie edges even if no reachable coordinate returns exactly INT_MAX.
    for distance in (-2147483648,-1,0,1,2147483646,2147483647):
        for gate in range(8):
            rows=[[255 if gate&1 else 0,2 if gate&2 else 0,128 if gate&4 else 0,17,distance],
                  [1,1,1,-7,distance],[1,1,1,9,distance]]
            add('selection_only_gates_signed_distance_first_tie','S',0,1,42,0,0,rows)
    # Every original foundation table entry, exact co-location, z distance and
    # signed-word Cell positions; all coordinate additions/subtractions wrap.
    positions=[0,0x00020003,0x7fff8000,0x80007fff,0xffffffff]
    for foundation in range(22):
        for position in positions:
            x=(position&65535);x=x-65536 if x&32768 else x
            y=position>>16;y=y-65536 if y&32768 else y
            tx,ty=x*256+128,y*256+128;w,h=widths[foundation],heights[foundation]
            for dz in (0,1,8192):
                rows=[[1,1,1,7,foundation,w,h,tx-w*128+128,ty-h*128+128,dz]]
                add('actual_foundation_cell_getters_zero_and_vertical_distance','W',7,255,42,position,0,rows)
    edges=[-2147483648,-2147483647,-16777217,-1,0,1,16777217,2147483646,2147483647]
    for case in range(256):
        rows=[]
        for i in range(case%13):
            f=rng.randrange(22)
            rows.append([rng.choice([0,1,2,255]) for _ in range(3)]+[rng.choice(edges),f,widths[f],heights[f],*[rng.choice(edges) if case%2 else rng.randrange(-100000,100000) for _ in range(3)]])
        if rows and case%7==0:rows.append(list(rows[0]))
        add('actual_nested_registry_order_wrap_quantization_and_noncanonical_bytes','W',rng.choice([-1,0,7]),rng.choice([0,1,2,255]),rng.choice(edges),rng.getrandbits(32),rng.choice(edges),rows)
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_entries':o.entries,
      'selected_owner_stores':o.stores,'supplied_terrain_height_or_diagnostic_distance_calls':o.service_calls,
      'actual_numeric_negative_distances':o.negative_distances,'actual_numeric_zero_distances':o.zero_distances,
      'immutable_candidate_type_house_registry_and_nonselected_Cell_bytes_checked':True,
      'terrain_height_construction_map_parent_runtime_and_frame_unverified':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-wall-owner-vectors')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/map-wall-owner-v2')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh wall owner destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
    if proc.returncode:raise RuntimeError('Native wall owner: '+proc.stderr.strip())
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Wall owner result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}; {commands[i]}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Wall owner run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} wall owner/Cell-target distance results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
