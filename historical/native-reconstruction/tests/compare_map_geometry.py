#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Initial map geometry/selected Cell preparation against unchanged base roots."""
import argparse,configparser,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_geometry import verify
SOURCES=('src/assets/MapGeometry.hpp','src/assets/MapGeometry.cpp','src/assets/MapCellInputs.hpp','src/assets/MapCellInputs.cpp',
 'src/assets/MapCellChildren.hpp','tests/map_geometry_vectors.cpp','tests/compare_map_geometry.py','tests/original_map_geometry.py',
 'tools/verify_map_geometry.py','tools/verify_map_cell_inputs.py','tests/original_map_cell_inputs.py',
 'tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py','tests/presentation_evidence.py',
 'tests/compare_original.py','tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'owned_map_sha256':hash_file(a.map)}
def valid_command(command):
    c=command.split();op=c[0];v=list(map(int,c[1:]))
    assert all(-2147483648<=n<=4294967295 for n in v)
    if op=='G':
        assert len(v)==8;seed,invalid,x,y,w,h,level,rebuild=v
        assert 0<=seed<=4294967295 and 0<=invalid<=4294967295 and -2147483648<=x<=2147483647 and -2147483648<=y<=2147483647
        assert w>0 and h>0 and w+h<=256 and 0<=level<=255 and rebuild in (0,1)
    elif op=='B':
        assert len(v)==4;w,h,old,seed=v
        assert -2147483648<=w<=2147483647 and -2147483648<=h<=2147483647 and old in (0,1) and 0<=seed<=4294967295
        assert (((w+h+1)&0xffffffff)**2&0xffffffff)<=66049
    else:
        assert op=='V' and len(v)==9 and all(-2147483648<=n<=2147483647 for n in v[:8]) and 0<=v[-1]<=4294967295
    return op,v

def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Geometry engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Geometry source/inspection/input identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Geometry counts differ')
    for command in e['commands']:
        try:valid_command(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed geometry command') from None

def generate(a):
    from original_map_geometry import MapGeometryOracle
    o=MapGeometryOracle(a.exe);rng=random.Random(0x4d415047);commands=[];expected=[];labels=[];counts={'G':0,'B':0,'V':0}
    def add(label,op,v):
        command=op+' '+' '.join(map(str,v));valid_command(command)
        commands.append(command);expected.append(list(map(str,o.run(op,v))));labels.append(label);counts[op]+=1
    for i,(w,h) in enumerate([(1,1),(1,7),(7,1),(2,3),(3,2),(7,8),(8,7),(17,19),(63,1),(64,1),(1,63),(1,64),(63,64),(64,63),(128,128),(255,1),(1,255)]):
        add('initial_empty_table_Y_major_selected_constructor_and_position_stores','G',
          [rng.getrandbits(32),rng.getrandbits(32),rng.choice([-2147483648,0,1,2147483647]),rng.choice([-19,0,1,143]),w,h,[0,1,127,128,255][i%5],i%2])
    ini=configparser.ConfigParser(interpolation=None,strict=False);ini.read_string(a.map.read_text(encoding='latin1'))
    full=list(map(int,ini['Map']['Size'].split(',')));visible=list(map(int,ini['Map']['LocalSize'].split(',')))
    add('owned_Size_80x85_initial_13515_cells','G',[0x1006,0x7fff7fff,*full,0,1])
    add('owned_LocalSize_actual_intersection_and_clamps','V',[0,0,*full[2:],*visible,0x1006])
    buffer_shapes=[(1,1),(0,0),(-1,0),(0,-1),(-3,5),(3,-5),(80,85),(128,128),(255,0),
      (2147483647,-2147483648),(2147483647,-2147483600),(-2147483648,2147483600)]
    for w,h in buffer_shapes:
        for old in (0,1):add('buffer_capacity_fill_preserved_tail_signed_subzone_division','B',[w,h,old,rng.getrandbits(32)])
    edges=[-2147483648,-2147483647,-100,-1,0,1,2,3,6,50,80,85,2147483646,2147483647]
    for i in range(1024):
        if i<512:
            full=[0,0,rng.choice([1,3,50,80,85,256]),rng.choice([1,7,50,85,256])]
            r=[rng.choice(edges) for _ in range(4)]
        else:full=[rng.choice(edges) for _ in range(4)];r=[rng.choice(edges) for _ in range(4)]
        add('visible_signed_wrapped_empty_and_clamp_arithmetic','V',[*full,*r,rng.getrandbits(32)])
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_entries':o.entries,'guest_stores':o.store_count,
      'supplied_service_calls':o.service_count,'cases_by_root':counts,'owned_full':list(map(int,ini['Map']['Size'].split(','))),
      'owned_visible':visible,'empty_pointer_table_entries':262144,'original_instructions_modified':False,
      'heap_zone_light_graphics_vector_services_supplied':True,'INI_screen_reset_callers_inspection_only':True}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-geometry-vectors')
    p.add_argument('--map',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/map-light/assets/mp03t4.map')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/geometry-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh geometry destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Geometry result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Geometry run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 map geometry results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
