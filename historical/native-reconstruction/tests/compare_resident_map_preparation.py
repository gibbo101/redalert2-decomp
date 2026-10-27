#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare the ordinary map pass on supplied general resident terrain inputs."""
import argparse
import configparser
import json
import random
import struct
import subprocess
import time
from pathlib import Path
import pefile
import compare_map_preparation as parent
from compare_theater_tile_inputs import owned_inputs
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED, write_report
from presentation_evidence import private_path, hash_file, validate_receipt, check_replay_destination
from verify_resident_map_preparation import verify

SOURCES = (*parent.SOURCES, 'src/assets/LandCharacteristics.hpp',
    'tests/compare_resident_map_preparation.py','tests/original_resident_map_preparation.py',
    'tools/verify_resident_map_preparation.py','tools/prepare_resident_map_fixture.py',
    'tests/compare_theater_tile_inputs.py','tools/verify_theater_tile_inputs.py')

def identities(a):
    return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
        'render_data_sha256':hash_file(a.render_data),'map_decoder_sha256':hash_file(a.decoder),
        'owned_inputs':{p.name:hash_file(p) for p in sorted(a.assets.iterdir()) if p.suffix in ('.tem','.ini','.map')}}

def command(common, land, shape, types, cells):
    return 'Q '+' '.join(map(str,[*common,*[v for row in land for v in row],*shape,len(types),
        *[v for row in types for v in row],len(cells),*[v for row in cells for v in row]]))

def parse(cmd):
    t=cmd.split();assert t[0]=='Q';v=list(map(int,t[1:]));common=v[:61]
    assert len(common)==61
    land=[v[i:i+9] for i in range(61,169,9)];shape=v[169:174];at=174
    assert len(land)==12 and all(len(row)==9 and all(0<=x<=0xffffffff for x in row[:8]) and 0<=row[8]<=255 for row in land)
    assert len(shape)==5 and shape[0]==common[0] and all(-2147483648<=x<=2147483647 for x in shape)
    assert common[50:61]==[row[2] for row in land[:11]]
    count=v[at];at+=1;assert 1<=count<=1024;types=[]
    for _ in range(count):
        header=v[at:at+5];assert len(header)==5
        present,columns,rows,width,height=header
        assert present in (0,1) and 1<=columns<=60 and 1<=rows<=60 and columns*rows<=60
        assert all(-2147483648<=x<=2147483647 for x in (width,height))
        end=at+5+columns*rows*6;row=v[at:end];assert len(row)==5+columns*rows*6
        for j in range(5,len(row),6):
            valid,raw,ramp,y,ey,extra=row[j:j+6]
            assert valid in (0,1) and 0<=raw<16 and 0<=ramp<=255 and extra in (0,1)
            assert -2147483648<=y<=2147483647 and -2147483648<=ey<=2147483647
            assert not(present and valid and common[11+raw]==10)
        types.append(row);at=end
    count=v[at];at+=1;assert 0<=count<=16384 and len(v)==at+count*14
    cells=[v[i:i+14] for i in range(at,len(v),14)]
    # Reuse the strict inherited common/Cell-domain guard, with absent images.
    probe=parent.command([*common[:5],common[5:11],common[11:27],common[27:42],common[42:50],common[50:61],
                          [[0,0,0,0,30,0,0,0]],cells])
    parent.parse(probe)
    return common,land,shape,types,cells

def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':
        raise ValueError('Resident map engine/profile differs')
    if e['evidence'].get('identities')!=current:
        raise ValueError('Resident map source/inspection/input identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):
        raise ValueError('Resident map counts differ')
    for cmd in e['commands']:
        try:parse(cmd)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed resident map command') from None

def floatbits(value):
    return struct.unpack('<I',struct.pack('<f',value))[0]

def general_tile(data):
    columns,rows,width,height=struct.unpack_from('<4i',data)
    result=[1,columns,rows,width,height]
    for j in range(columns*rows):
        ref=struct.unpack_from('<I',data,16+j*4)[0]
        result.extend([1,data[ref+0x29],data[ref+0x2a],struct.unpack_from('<i',data,ref+4)[0],
            struct.unpack_from('<i',data,ref+0x18)[0],struct.unpack_from('<I',data,ref+0x24)[0]&1] if ref else [0]*6)
    return result

def generate(a):
    from original_resident_map_preparation import ResidentMapPreparationOracle
    from original_map_preparation import CELLS
    o=ResidentMapPreparationOracle(a.exe);rng=random.Random(0x524d4150)
    commands=[];expected=[];labels=[];owned=[]
    def add(label,common,land,shape,types,cells):
        cmd=command(common,land,shape,types,cells)
        c,land,shape,types,cells=parse(cmd)
        args=[*c[:5],c[5:11],c[11:27],c[27:42],c[42:50],c[50:61],types,cells,shape]
        commands.append(cmd);expected.append(list(map(str,o.run(*args))));labels.append(label)
    for case in range(48):
        width=3+case%5;height=2+(case//5)%4
        land=[[rng.getrandbits(32) for _ in range(8)]+[rng.randrange(256)] for _ in range(12)]
        for row in land:row[2]=floatbits(rng.choice([0,0.005,0.01,0.02,0.7,1]))
        types=[]
        for i in range(16):
            columns,rows=rng.choice([(1,1),(2,2),(3,2),(2,4),(9,5)])
            tile=[int(i%7!=0),columns,rows,60,rng.choice([30,45,60])]
            for j in range(columns*rows):tile.extend([int((i+j)%11!=0),rng.choice([0,2,6,8]),rng.randrange(17),rng.choice([-30,0,45]),rng.choice([-15,0,60]),rng.randrange(2)])
            types.append(tile)
        cells=[]
        for y in range(width+height+1):
            for x in range(width+height+1):
                if x+y>width and abs(x-y)<width and x+y<=width+2*height:
                    cells.append([x,y,rng.randrange(16),rng.randrange(256),rng.randrange(13),rng.getrandbits(32),-1,0,0,rng.randrange(256),0,0,rng.choice([-1,0,7]),rng.getrandbits(32)])
        common=[width,height,case,-1 if case%8 else 0,case%3,100,100,100,100,0,28,
            *range(10),0,0,0,0,0,0,*([-1]*15),*o.initial_directions,*[row[2] for row in land[:11]]]
        add('general_resident_TMP_shared_Cells_Wheel_binding_and_visible_bounds',common,land,[width,case%2,case%3,width-1,height],types,cells)

    ini=configparser.ConfigParser(interpolation=None,strict=False,inline_comment_prefixes=(';',))
    ini.read(a.assets/'temperat.ini',encoding='latin1');numbers,sets=owned_inputs(a.assets/'temperat.ini')
    starts=[];types=[]
    for index,row in enumerate(sets):
        starts.append(len(types))
        if row[0]==-1:break
        assert not(row[6]&32) and row[1] in (-1,row[0]),'Owned shadow-caster/shift profile requires recovery'
        assert not ini.get(f'TileSet{index:04d}','TileAnimation',fallback='').strip(),'Owned animation requires recovery'
        prefix=ini.get(f'TileSet{index:04d}','FileName')
        for j in range(row[0]):
            path=a.assets/(prefix.lower()+f'{j+1:02d}.tem')
            types.append(general_tile(path.read_bytes()) if path.exists() else [0,1,1,60,30,*([0]*6)])
    lat=[starts[n] if 0<=n<len(starts) else -1 for n in numbers[:15]]
    rules=configparser.ConfigParser(interpolation=None,strict=False,allow_no_value=True,inline_comment_prefixes=(';',))
    rules.read(a.assets/'rules.ini',encoding='latin1')
    sections=('Clear','Road','Water','Rock','Wall','Tiberium','Beach','Rough','Ice','Railroad','Tunnel','Weeds')
    keys=('Foot','Track','Wheel','Hover','Winged','Float','Amphibious','FloatBeach');land=[]
    for section in sections:
        assert rules.has_section(section),'Missing owned land section needs explicit initial-state fixture'
        row=[]
        for key in keys:
            text=rules.get(section,key,fallback='1').strip()
            value=float(text[:-1])/100 if text.endswith('%') else float(text)
            row.append(floatbits(1.0 if key=='Winged' or value>=1 else value))
        text=rules.get(section,'Buildable',fallback='no').strip().lower()
        land.append([*row,int(bool(text) and text[0] in '1ty')])
    raw=subprocess.check_output([str(a.decoder),'--decode',str(a.assets/'mp03t4.map')])
    assert len(raw)%11==4
    records=[struct.unpack_from('<hhIBBB',raw,i*11) for i in range((len(raw)-4)//11)]
    cells=[[x,y,tile,sub,level,0,-1,0,0,0,0,ice,0,0] for x,y,tile,sub,level,ice in records]
    map_ini=configparser.ConfigParser(interpolation=None,strict=False);map_ini.read(a.assets/'mp03t4.map',encoding='latin1')
    size=list(map(int,map_ini.get('Map','Size').split(',')));local=list(map(int,map_ini.get('Map','LocalSize').split(',')))
    assert size==[0,0,80,85] and local==[5,5,70,73]
    pe=pefile.PE(str(a.exe));mapping=list(struct.unpack('<16i',pe.get_data(0x7de4ec-0x400000,64)))
    for mode in range(3):
        common=[80,85,0,-1,mode,100,100,100,86,0,28,*mapping,*lat,*o.initial_directions,*[row[2] for row in land[:11]]]
        add('owned_all_records_primary_resident_metadata_no_overlays_actors_or_variants_cliff_mode_'+str(mode),common,land,[80,*local],types,cells)
        summary={'cliff_mode':mode,'records':len(cells),'types':len(types),'resident_types':sum(row[0] for row in types),
                 'slope_cells':0,'extra_height_cells':0,'lands':{},'cliff_cell':None}
        for i,row in enumerate(cells):
            data=bytes(o.u.mem_read(CELLS+i*512,0x148));land_value=struct.unpack_from('<i',data,0xec)[0]
            summary['lands'][str(land_value)]=summary['lands'].get(str(land_value),0)+1
            summary['slope_cells']+=bool(data[0x11c]);summary['extra_height_cells']+=bool(data[0x11d])
            if row[:2]==[51,72]:summary['cliff_cell']={'tile':struct.unpack_from('<i',data,0x38)[0],
                'land':land_value,'level':data[0x11b],'slope':data[0x11c],'extra_height':data[0x11d],
                'passability':struct.unpack_from('<i',data,0x4c)[0]}
        owned.append(summary)
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_entries':o.entries,'guest_stores':o.stores,
        'owned':owned,'original_instructions_modified':False,'complete_startup_executed':False,
        'resident_records_primary_images_geometry_tables_rules_decoding_and_initial_state_supplied':True,
        'overlays_and_actors_absent':True,'palette_disabled':True}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-preparation-vectors')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin')
    p.add_argument('--decoder',type=Path,default=ROOT/'build/native/map-cell-input-vectors')
    p.add_argument('--assets',type=Path,default=ROOT/'private/map-depth-1006/resident-fixture-v1')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/resident-map-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh resident destination exists/invalid')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
    if proc.returncode:raise RuntimeError('Native resident map: '+proc.stderr.strip())
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Resident map counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Resident run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,
        'profile':'supplied-ra2-1006','evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
        'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
        'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands)} supplied-1.006 resident map results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')

if __name__=='__main__':main()
