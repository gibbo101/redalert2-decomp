#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Loaded theater associations and actual color preparation against original."""
import argparse,configparser,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_tile_image import valid_command as valid_image,synthetic,OWNED
from compare_theater_tile_inputs import owned_inputs
from verify_theater_tile_files import verify
SOURCES=('src/assets/TheaterTileFiles.hpp','src/assets/TheaterTileFiles.cpp','src/assets/TheaterTileInputs.hpp','src/assets/TheaterTileInputs.cpp',
 'src/assets/TileImagePreparation.hpp','src/assets/TileImagePreparation.cpp','src/assets/Bytes.hpp','src/assets/MapCellInputs.hpp','src/sim/OriginalMath.hpp',
 'tests/theater_tile_file_vectors.cpp','tests/compare_theater_tile_files.py','tests/original_theater_tile_files.py','tests/original_theater_tile_inputs.py',
 'tests/compare_tile_image.py','tests/compare_theater_tile_inputs.py','tests/original_tile_image.py','tools/verify_theater_tile_files.py','tools/verify_theater_tile_inputs.py','tools/verify_tile_image.py',
 'tools/verify_map_cell_inputs.py','tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py','tests/presentation_evidence.py',
 'tests/compare_original.py','tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py')
TERMINAL=[-1,-1,65535,65535,-1,-1,6,0]
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'owned_TMPs':{n:hash_file(a.assets/n) for n in OWNED},'owned_ini_sha256':hash_file(a.ini)}
def command(theater,numbers,sets,prefixes,files):
    tokens=['F',str(theater),str(len(sets)),*map(str,numbers)]
    for row,prefix in zip(sets,prefixes):tokens += [*map(str,row),prefix.encode().hex()]
    tokens.append(str(len(files)))
    for name,data in files.items():tokens += [name.encode().hex(),data.hex()]
    return ' '.join(tokens)
def parse(cmd):
    t=cmd.split();assert t[0]=='F';theater,count=map(int,t[1:3]);assert theater in (0,1,2) and 1<=count<=1024
    numbers=list(map(int,t[3:19]));assert len(numbers)==16 and all(-2147483648<=n<=2147483647 for n in numbers);sets=[];prefixes=[];at=19
    for i in range(count):
        row=list(map(int,t[at:at+8]));assert len(row)==8 and all(-2147483648<=n<=2147483647 for n in row) and 0<=row[6]<64
        prefix=bytes.fromhex(t[at+8]).decode('ascii');assert 1<=len(prefix)<=16 and all(c.isascii() and (c.isalnum() or c in '_-') for c in prefix)
        sets.append(row);prefixes.append(prefix);at+=9
    assert sets[-1][0]==-1 and all(r[0]!=-1 for r in sets[:-1]) and sum(bool(r[6]&32) for r in sets[:-1])<=5
    assert sum(max(0,r[0]) for r in sets)<=65536
    files_count=int(t[at]);at+=1;assert 0<=files_count<=1024 and len(t)==at+files_count*2;files={}
    for i in range(files_count):
        name=bytes.fromhex(t[at]).decode('ascii');data=bytes.fromhex(t[at+1]);at+=2;assert name and name not in files
        valid_image('L '+' '.join(map(str,[0,0,11,3,0,3,5,2,*range(16)]))+' '+data.hex());files[name]=data
    return theater,numbers,sets,prefixes,files
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Theater file engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Theater file source/inspection/input identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Theater file counts differ')
    for cmd in e['commands']:
        try:parse(cmd)
        except (AssertionError,ValueError,IndexError,UnicodeError):raise ValueError('Malformed theater file command') from None
def generate(a):
    from original_theater_tile_files import TheaterTileFileOracle
    o=TheaterTileFileOracle(a.exe);rng=random.Random(0x5446494c);commands=[];expected=[];labels=[]
    def add(label,theater,numbers,sets,prefixes,files):
        cmd=command(theater,numbers,sets,prefixes,files);args=parse(cmd);commands.append(cmd);expected.append(list(map(str,o.run(*args))));labels.append(label)
    for case in range(128):
        theater=case%3;ext=('TEM','SNO','URB')[theater];marble=('MMT','MMS','MMU')[theater]
        count=case%4;sets=[];prefixes=[];files={}
        for s in range(count):
            prefix=('CLR','cliff','Tile','SLOPE')[s];prefixes.append(prefix);size=1+(case+s)%3
            sets.append([size,rng.choice([-1,size,0]),rng.choice([65535,*range(count+1)]),rng.choice([0,65535,*range(count+1)]),-1,-1,(case+s)%32,0])
            for j in range(size):
                variants=(case+s+j)%5
                for k in range(variants):
                    suffix='' if k==0 else chr(0x60+k);which=marble if (case+j+k)%3==0 else ext
                    files[prefix+f'{j+1:02d}'+suffix+'.'+which]=synthetic(*rng.choice([(0,0),(1,1),(2,1),(2,3)]),rng,case+j+k)
        add('nonlazy_normal_marble_fallback_order_and_contiguous_alternate_links',theater,[-1]*16,[*sets,TERMINAL],[*prefixes,'TILE'],files)
    for theater in range(3):
        ext=('TEM','SNO','URB')[theater]
        files={f'{name[:-6]}01.{ext}':(a.assets/name).read_bytes() for name in OWNED}
        prefixes=[name[:-6] for name in OWNED]+['TILE'];sets=[[1,-1,65535,65535,-1,-1,6,0] for _ in OWNED]+[TERMINAL]
        add('owned_clear_cliff_slope_loaded_binding_all_color_words',theater,[-1]*16,sets,prefixes,files)
    for theater in range(3):
        ext=('TEM','SNO','URB')[theater];data=(a.assets/'clear01.tem').read_bytes()
        files={'SAME01.'+ext:data,'SAME01a.'+ext:data}
        rows=[[1,-1,65535,65535,-1,-1,6,0],[1,-1,65535,65535,-1,-1,6,0],TERMINAL]
        add('repeated_cached_image_binding_relocates_only_relative_references',theater,[-1]*16,rows,['SAME','SAME','TILE'],files)
    numbers,rows=owned_inputs(a.ini)
    ini=configparser.ConfigParser(interpolation=None,strict=False,inline_comment_prefixes=(';',));ini.read(a.ini,encoding='latin1')
    prefixes=[ini.get(f'TileSet{i:04d}','FileName',fallback='TILE').strip() for i in range(len(rows))]
    files={prefix+'01.TEM':(a.assets/(prefix.lower()+'01.tem')).read_bytes() for prefix in prefixes if prefix.lower() in ('clear','cliff','slope')}
    add('owned_full_temperate_INI_with_three_loaded_files_others_absent_fixture',0,numbers,rows,prefixes,files)
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_entries':o.entries,'guest_stores':o.store_count,'supplied_service_calls':o.service_calls,
      'INI_base_constructor_file_cache_heap_vector_graphics_timer_services_supplied':True,'actual_color_preparation':True,'original_instructions_modified':False}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/theater-tile-file-vectors')
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/composition/assets');p.add_argument('--ini',type=Path,default=ROOT/'private/map-depth-1006/theater-assets/temperat.ini')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/theater-files-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh theater file destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Theater file result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Theater file run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 loaded theater results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
