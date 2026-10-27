#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Loaded TMP metadata and all original color ramps against unchanged roots."""
import argparse,json,random,struct,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_tile_image import verify
SOURCES=('src/assets/TileImagePreparation.hpp','src/assets/TileImagePreparation.cpp','src/assets/MapCellInputs.hpp','src/assets/MapCellInputs.cpp',
 'src/assets/Bytes.hpp','src/sim/OriginalMath.hpp','tests/tile_image_vectors.cpp','tests/compare_tile_image.py','tests/original_tile_image.py',
 'tools/verify_tile_image.py','tools/verify_map_cell_inputs.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py','tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py')
OWNED=('clear01.tem','cliff01.tem','slope01.tem')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'owned_TMPs':{name:hash_file(a.assets/name) for name in OWNED}}
def valid_command(command):
    p=command.split();assert p[0] in ('L','G') and len(p)==26
    v=list(map(int,p[1:25]));assert 0<=v[0]<=4294967295 and v[1] in (0,1) and not(p[0]=='G' and v[1])
    assert all(0<=n<=4294967295 for n in v[2:8]) and all(-2147483648<=n<=2147483647 for n in v[8:])
    data=bytes.fromhex(p[-1]);assert len(data)>=16
    cols,rows=struct.unpack_from('<2i',data);assert 0<=cols<=255 and 0<=rows<=255 and cols*rows<=16384 and 16+cols*rows*4<=len(data)<0x1f0000
    for i in range(cols*rows):
        ref=struct.unpack_from('<I',data,16+i*4)[0]
        assert not ref or 16+cols*rows*4<=ref<=len(data)-52
        assert not ref or data[ref+0x29]<16
    return p[0],v,data

def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Tile image engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Tile image source/inspection/input identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Tile image counts differ')
    for command in e['commands']:
        try:valid_command(command)
        except (AssertionError,ValueError,IndexError,struct.error):raise ValueError('Malformed tile image command') from None

def synthetic(cols,rows,rng,mode):
    count=cols*rows;data=bytearray(struct.pack('<4i',cols,rows,rng.choice([-2147483648,0,30,60,2147483647]),rng.choice([-2147483648,0,30,60,2147483647]))+bytes(count*4));refs=[]
    for i in range(count):
        if (i+mode)%5==0:continue
        if refs and (i+mode)%7==0:struct.pack_into('<I',data,16+i*4,rng.choice(refs));continue
        p=len(data);refs.append(p);struct.pack_into('<I',data,16+i*4,p);chunk=bytearray(rng.randbytes(52))
        for off in (4,0x18):struct.pack_into('<i',chunk,off,rng.choice([-2147483648,-45,-1,0,30,75,2147483647]))
        struct.pack_into('<I',chunk,0x24,rng.getrandbits(32));chunk[0x29]=rng.randrange(16);chunk[0x2a]=rng.randrange(256)
        for off in range(0x2b,0x31):chunk[off]=rng.choice([0,1,127,128,181,182,183,254,255,rng.randrange(256)])
        data.extend(chunk)
    return bytes(data)

def generate(a):
    from original_tile_image import TileImageOracle
    o=TileImageOracle(a.exe);rng=random.Random(0x544d5049);commands=[];expected=[];labels=[]
    def add(label,op,data,seed,old,packing,mapping):
        cmd=op+' '+' '.join(map(str,[seed,old,*packing,*mapping]))+' '+data.hex();valid_command(cmd)
        commands.append(cmd);expected.append(list(map(str,o.run(op,data,seed,old,packing,mapping))));labels.append(label)
    stock=[11,3,0,3,5,2];shifts=[0,1,2,3,5,11,15,16,31,32,35,255,4294967295]
    for i in range(384):
        cols,rows=rng.choice([(0,0),(0,255),(255,0),(1,1),(2,1),(1,2),(2,3),(3,4),(4,2)])
        data=synthetic(cols,rows,rng,i);op='G' if i%2 else 'L'
        packing=stock if i%3 else [rng.choice(shifts) for _ in range(6)]
        mapping=[rng.choice([-2147483648,-1,0,1,2,3,6,10,2147483647]) for _ in range(16)]
        add('lazy_load_relocation_color_ramps_metadata_and_consumers',op,data,rng.getrandbits(32),int(op=='L' and i%4==0),packing,mapping)
    for name in OWNED:
        for op in ('L','G'):
            data=(a.assets/name).read_bytes();add('owned_'+name+'_all_subtile_inputs_and_color_words',op,data,13,int(op=='L'),stock,list(range(16)))
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_entries':o.entries,'guest_stores':o.stores,'supplied_service_calls':o.service_calls,
      'file_heap_vector_services_supplied':True,'actual_color_builder_and_metadata_children':True,'original_instructions_modified':False}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/tile-image-vectors')
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/composition/assets')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/tile-image-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh tile image destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Tile image result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Tile image run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 loaded TMP results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
