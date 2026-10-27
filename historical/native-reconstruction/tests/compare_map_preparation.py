#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Ordinary map cell pass with actual shared-state recalculation and lighting."""
import argparse,json,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_preparation import verify
SOURCES=('src/assets/MapOverlay.hpp','src/assets/MapPreparation.hpp','src/assets/MapPreparation.cpp','src/assets/LandCharacteristics.hpp','src/assets/TileSweep.hpp','src/assets/TileSweep.cpp',
 'src/assets/MapCellAttributes.hpp','src/assets/MapCellAttributes.cpp','src/assets/MapCellChildren.hpp','src/assets/MapCellChildren.cpp',
 'src/assets/MapCellInputs.hpp','src/assets/MapCellInputs.cpp','src/assets/Bytes.hpp','src/render/MapLighting.hpp','src/render/MapLighting.cpp',
 'src/assets/RenderData.hpp','src/assets/RenderData.cpp','src/render/Lighting.hpp','src/sim/OriginalMath.hpp','tests/map_preparation_vectors.cpp',
 'tests/compare_map_preparation.py','tests/original_map_preparation.py','tests/original_map_cell_preparation.py','tests/original_presentation.py',
 'tests/original_foot_lit.py','tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py','tests/compare_terrain_visibility.py',
 'tools/verify_map_preparation.py','tools/verify_map_cell_preparation.py','tools/verify_map_cell_attributes.py','tools/verify_map_cell_children.py',
 'tools/verify_map_cell_inputs.py','tools/verify_foot_depth.py','tools/verify_tile_sweep.py','tools/verify_tile_variants.py','tools/verify_tile_image.py','tools/verify_terrain_visibility.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
 'render_data_sha256':hash_file(a.render_data),'map_decoder_sha256':hash_file(a.decoder),'owned_map_sha256':hash_file(a.map)}
def command(args):
    width,height,seed,hole,cliff,light,mapping,lat,directions,speeds,types,cells=args
    return 'P '+' '.join(map(str,[width,height,seed,hole,cliff,*light,*mapping,*lat,*directions,*speeds,len(types),*[v for row in types for v in row],len(cells),*[v for row in cells for v in row]]))
def parse(cmd):
    parts=cmd.split();assert parts[0]=='P';v=list(map(int,parts[1:]));width,height,seed,hole,cliff=v[:5]
    assert 2<=width<=255 and 1<=height and width+height<=256 and 0<=seed<=4294967295 and -1<=hole<16384 and 0<=cliff<=2
    light=v[5:11];mapping=v[11:27];lat=v[27:42];directions=v[42:50];speeds=v[50:61];assert len(speeds)==11
    assert all(-1000<=n<=1000 for n in light[:4]) and all(-10000<=n<=10000 for n in light[4:])
    assert all(0<=n<=10 for n in mapping) and all(-2147483648<=n<=2147483647 for n in lat) and all(0<=n<=4294967295 for n in directions+speeds)
    count=v[61];assert 1<=count<=1024;at=62;types=[]
    for i in range(count):
        row=v[at:at+8];at+=8;present,valid,ramp,land,h,y,ey,extra=row
        assert present in (0,1) and valid in (0,1) and 0<=ramp<=255 and 0<=land<16 and mapping[land]!=10 and extra in (0,1) and all(-2147483648<=n<=2147483647 for n in (h,y,ey));types.append(row)
    count=v[at];at+=1;assert 0<=count<=16384 and (hole==-1 or hole<count) and len(v)==at+count*14;cells=[];positions=set()
    for i in range(count):
        row=v[at:at+14];at+=14;x,y,tile,sub,level,flags,tube,land,slope,extra,data,ice,passability,field30=row
        assert 0<=x<512 and 0<=y<512 and (x,y) not in positions and 0<=tile<=2147483647 and 0<=level<=31 and all(0<=n<=255 for n in (sub,slope,extra,data,ice))
        assert 0<=flags<=4294967295 and 0<=field30<=4294967295 and -32768<=tube<=32767 and all(-2147483648<=n<=2147483647 for n in (land,passability));positions.add((x,y));cells.append(row)
    return width,height,seed,hole,cliff,light,mapping,lat,directions,speeds,types,cells

def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Map preparation engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Map preparation source/inspection/input identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Map preparation counts differ')
    for cmd in e['commands']:
        try:parse(cmd)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed map preparation command') from None

def generate(a):
    from original_map_preparation import MapPreparationOracle
    o=MapPreparationOracle(a.exe);rng=random.Random(0x4d415050);pe=pefile.PE(str(a.exe));directions=o.initial_directions
    commands=[];expected=[];labels=[];visits=[]
    mapping=[0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0];lat=[100,200,300,400,500,600,700,800,900,20,40,1,2,3,4]
    speed_values=[struct.unpack('<I',struct.pack('<f',f))[0] for f in (0,0.005,0.01,0.02,1.0)]
    def add(label,args):
        cmd=command(args);result=o.run(*parse(cmd));commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);visits.append(len(o.visits))
    for case in range(64):
        width=2+case%5;height=2+(case//5)%4;types=[]
        for i in range(1024):types.append([int((i+case)%7!=0),int((i+case)%11!=0),rng.randrange(6),rng.choice([0,2,6,8]),rng.choice([30,60,75]),rng.choice([-30,0,45]),rng.choice([-15,0,60]),rng.randrange(2)])
        cells=[]
        for y in range(width+height+1):
            for x in range(width+height+1):
                if x+y>width and abs(x-y)<width and x+y<=width+2*height:
                    cells.append([x,y,rng.choice([1,2,3,4,20,40,41,42,43,44,55,63,1024,65535]),rng.choice([0,0,0,1,255]),rng.randrange(13),rng.getrandbits(32),-1,rng.randrange(9),rng.randrange(6),rng.randrange(256),rng.randrange(256),rng.randrange(256),rng.choice([-1,0,7,2147483647]),rng.getrandbits(32)])
        light=[rng.randrange(201),rng.randrange(30,121),rng.randrange(30,121),rng.randrange(30,121),rng.randrange(-100,201),rng.randrange(61)]
        add('complete_two_pass_parent_shared_cell_LAT_passability_lighting_and_buffer_state',[width,height,case,-1 if case%8 else rng.randrange(len(cells)),case%3,light,mapping,lat,directions,[rng.choice(speed_values) for _ in range(11)],types,cells])
    raw=subprocess.check_output([str(a.decoder),'--decode',str(a.map)]);count=(len(raw)-4)//11 if len(raw)%11==4 else len(raw)//11
    records=[struct.unpack_from('<hhIBBB',raw,i*11) for i in range(count)]
    # All original positions/levels/tiles are supplied. Images deliberately absent;
    # this tests full iterator/light/buffer sequencing, not real loaded-map metadata.
    types=[[0,0,0,0,30,0,0,0] for _ in range(838)];cells=[[x,y,tile,sub,level,0,-1,0,0,0,0,ice,0,0] for x,y,tile,sub,level,ice in records]
    add('owned_all_decoded_positions_levels_tiles_838_null_images_not_loaded_map_fidelity',[80,85,0,-1,0,[100,100,100,86,0,28],mapping,[-1]*15,directions,[speed_values[-1]]*11,types,cells])
    assert len(o.visits)==2*(count+1)
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_entries':o.entries,'guest_stores':o.stores,'visits_per_case':visits,
      'owned_records':count,'initialized_direction_sha256':__import__('hashlib').sha256(struct.pack('<8I',*o.initial_directions)).hexdigest(),'owned_map_images_deliberately_absent':True,'palette_disabled_factory_actual':True,'original_instructions_modified':False}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/map-preparation-vectors')
    p.add_argument('--render-data',type=Path,default=ROOT/'private/derived/ra2-1006/render-data.bin');p.add_argument('--decoder',type=Path,default=ROOT/'build/native/map-cell-input-vectors');p.add_argument('--map',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/map-light/assets/mp03t4.map')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/map-preparation-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh map preparation destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();proc=subprocess.run([str(a.native),str(a.render_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
    if proc.returncode:raise RuntimeError('Native map preparation: '+proc.stderr.strip())
    actual=[row.split() for row in proc.stdout.splitlines()];elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Map preparation result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Map preparation run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 map preparation results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
