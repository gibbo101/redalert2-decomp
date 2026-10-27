#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Selected theater set/type inputs against complete unchanged base loader."""
import argparse,configparser,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_theater_tile_inputs import verify,KEYS
SOURCES=('src/assets/TheaterTileInputs.hpp','src/assets/TheaterTileInputs.cpp','src/assets/MapCellInputs.hpp','tests/theater_tile_input_vectors.cpp',
 'tests/compare_theater_tile_inputs.py','tests/original_theater_tile_inputs.py','tools/verify_theater_tile_inputs.py',
 'tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py','tests/presentation_evidence.py',
 'tests/compare_original.py','tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'owned_ini_sha256':hash_file(a.ini)}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Theater engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Theater source/inspection/input identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Theater counts differ')
    for command in e['commands']:
        c=command.split()
        try:
            assert c[0]=='T';v=list(map(int,c[1:]));assert 1<=v[0]<=1024 and len(v)==17+8*v[0]
            rows=[v[i:i+8] for i in range(17,len(v),8)];assert rows[-1][0]==-1
            assert all(row[0]!=-1 for row in rows[:-1]) and all(0<=row[6]<=63 for row in rows)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed theater command') from None
def owned_inputs(path):
    # Native host decoding of supplied INI values; this is not original parsing.
    ini=configparser.ConfigParser(interpolation=None,strict=False,inline_comment_prefixes=(';',));ini.read_string(path.read_text(encoding='latin1'))
    def integer(section,key,fallback):return ini.getint(section,key,fallback=fallback)
    def boolean(section,key,fallback):
        text=ini.get(section,key,fallback='').strip().lower()
        return fallback if not text or text[0] not in '1ty0nf' else int(text[0] in '1ty')
    numbers=[integer('General',key,-1) for key in KEYS];rows=[]
    for i in range(1024):
        section=f'TileSet{i:04d}';count=integer(section,'TilesInSet',-1)
        if count==-1:rows.append([-1,-1,65535,65535,-1,-1,6,0]);break
        flags=sum(boolean(section,key,fallback)<<bit for bit,(key,fallback) in enumerate([
          ('Morphable',0),('AllowToPlace',1),('AllowBurrowing',1),('AllowTiberium',0),('RequiredForRMG',0),('ShadowCaster',0)]))
        rows.append([count,integer(section,'LastTilesInSet',-1),integer(section,'MarbleMadness',65535),
          integer(section,'NonMarbleMadness',65535),integer(section,'ToSnowTheater',-1),integer(section,'ToTemperateTheater',-1),flags,
          integer(section,'ShadowTiles',0)])
    else:raise ValueError('Owned theater terminator absent')
    return numbers,rows
def generate(a):
    from original_theater_tile_inputs import TheaterTileInputOracle
    o=TheaterTileInputOracle(a.exe);rng=random.Random(0x54494c45);commands=[];expected=[];labels=[]
    def add(label,numbers,rows):
        commands.append('T '+' '.join(map(str,[len(rows),*numbers,*[n for row in rows for n in row]])))
        expected.append(list(map(str,o.run(numbers,rows))));labels.append(label)
    terminal=[-1,-1,65535,65535,-1,-1,6,0]
    for n in range(384):
        count=n%9;rows=[];casters=0
        for i in range(count):
            size=rng.choice([-2,0,1,2,3,8]);flags=(n+i)%64
            if flags&32:casters+=1
            if casters>5:flags&=31
            rows.append([size,rng.choice([-2147483648,-2,-1,0,size,17,2147483647]),
              rng.choice([65535,*range(count+1)]),rng.choice([65535,*range(count+1)]),
              rng.choice([-2147483648,-1,0,123,2147483647]),rng.choice([-2147483648,-1,0,123,2147483647]),flags,rng.choice([-2,0,1,3])])
        numbers=[rng.choice([-2147483648,-2,-1,*range(count+2),2147483647]) for _ in KEYS]
        add('signed_counts_shifts_terminal_association_flags_and_alternate_set_bases',numbers,[*rows,terminal])
    for k in range(16):
        for value in (-2,-1,0,1,2,3):
            numbers=[-1]*16;numbers[k]=value
            add('individual_selected_General_key_association',numbers,[[2,-1,65535,65535,-1,-1,6,0],[3,-1,65535,65535,-1,-1,6,0],terminal])
    numbers,rows=owned_inputs(a.ini);add('owned_temperate_values_all_images_absent_projection',numbers,rows)
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_loader_entries':o.root_entries,
      'actual_tile_constructor_entries':o.constructor_entries,'supplied_INI_calls':o.ini_calls,'guest_stores':o.store_count,
      'owned_sets_including_terminator':len(rows),'owned_primary_types':sum(max(0,row[0]) for row in rows),
      'all_TMP_alternate_images_absent':True,'original_INI_base_constructor_file_heap_graphics_services_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/theater-tile-input-vectors')
    p.add_argument('--ini',type=Path,default=ROOT/'private/map-depth-1006/theater-assets/temperat.ini')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/theater-inputs-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh theater destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Theater result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Theater run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 theater projection results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
