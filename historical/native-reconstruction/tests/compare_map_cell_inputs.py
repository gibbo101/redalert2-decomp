#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base decoded map reader, constructor projection and resident TMP inputs."""
import argparse,json,random,struct,subprocess,sys,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_cell_inputs import verify
SOURCES=('src/assets/MapCellInputs.hpp','src/assets/MapCellInputs.cpp','src/assets/Formats.cpp','src/assets/Formats.hpp',
 'src/assets/Bytes.hpp','src/assets/Archive.cpp','src/assets/Archive.hpp','src/assets/ArchiveSequence.cpp','src/assets/ArchiveSequence.hpp',
 'tests/map_cell_input_vectors.cpp','tests/compare_map_cell_inputs.py','tests/original_map_cell_inputs.py',
 'tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py',
 'tests/presentation_evidence.py','tests/compare_original.py','tools/verify_map_cell_inputs.py')
def identities(a):
    return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
      'owned_map_sha256':hash_file(a.map),'owned_tiles':{str(p):hash_file(p) for p in a.tiles}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Map input engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Map input identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Map input counts differ')
    for command in e['commands']:
        c=command.split()
        if not c or c[0] not in ('R','C','T'):raise ValueError('Unknown map input command')
        try:
            if c[0]=='C':assert len(c)==4;list(map(int,c[1:]))
            elif c[0]=='T':assert len(c)>=25;list(map(int,c[1:]));assert len(c)==9+6*int(c[2])*int(c[3])+16
            else:
                list(map(int,c[1:-1]));n=int(c[4]);pos=5+2*n;count=int(c[pos]);assert len(c)==pos+count+2
                if c[-1]!='-':bytes.fromhex(c[-1])
        except (ValueError,AssertionError,IndexError):raise ValueError('Malformed map input command') from None
def generate(a):
    from original_map_cell_inputs import MapCellInputOracle
    o=MapCellInputOracle(a.exe);rng=random.Random(0x5241324d)
    commands=[];expected=[];labels=[];groups={}
    def save(group,c,row):commands.append(c);expected.append(list(map(str,row)));labels.append(group);groups[group]=groups.get(group,0)+1
    term=0x80008000;invalid=0x7fff7fff
    for seed in range(64):save('complete_Cell_Abstract_constructor_selected_depth_fields_and_high_flags',f'C {seed} {term} {invalid}',o.run_map('C',seed,term,invalid))
    for seed in range(80):
        shifts=[(-2147483648,seed),(-1,-2147483648),(0,1),(100,2147483647),(65535,-17)] if seed%2 else []
        indices=[0,1,512,513,262143];data=b''
        records=[(0,0,65535,255,255,255),(1,0,100,3,127,1),(512,0,-1,4,128,2),
                 (0,1,-2147483648,7,31,3),(-1,0,2147483647,0,0,4),(511,511,0,0,0,5),
                 (0,512,0,0,0,6),(100,100,100,0,0,7),(0,0,seed,seed%256,seed%32,seed%3)]
        if seed%3==0:records.reverse()
        for x,y,tile,sub,level,ice in records:data+=struct.pack('<hhIBBB',x,y,tile&0xffffffff,sub,level,ice)
        data+=struct.pack('<I',term)+b'ignored trailing bytes'
        c=' '.join(map(str,['R',seed,term,invalid,len(shifts),*[v for pair in shifts for v in pair],len(indices),*indices,data.hex()]))
        save('complete_reader_signed_index_alias_missing_cells_remap_sentinel_duplicates_and_trailing_data',c,o.run_map('R',seed,term,invalid,shifts,indices,data))
    for n in range(384):
        cols,rows=1+n%4,1+(n//4)%2;count=cols*rows
        values=[int(n%7!=0),cols,rows,60,30,n%(count*3),-121,517]
        samples=[]
        for i in range(count):samples.extend([int((n+i)%5!=0),(n+i)%16,(n+i*37)%256,(n+i)%2,rng.choice([-2147483648,-31,0,15,2147483647]),rng.choice([-2147483648,-30,0,16,2147483647])])
        mapping=[rng.randrange(-2147483648,2147483648) for _ in range(16)]
        v=values+samples+mapping;save('resident_TMP_null_missing_subtile_signed_bytes_remainder_dimensions_and_wrapping','T '+' '.join(map(str,v)),o.tile(v))
    import pefile
    pe=pefile.PE(data=a.exe.read_bytes());mapping=list(struct.unpack('<16i',pe.get_data(0x7de4ec-0x400000,64)))
    owned_subs=0
    for path in a.tiles:
        d=path.read_bytes();cols,rows,w,h=struct.unpack_from('<4I',d);count=cols*rows;samples=[]
        for i in range(count):
            p=struct.unpack_from('<I',d,16+i*4)[0]
            if p:samples.extend([1,d[p+41],d[p+42],struct.unpack_from('<I',d,p+36)[0]&1,struct.unpack_from('<i',d,p+4)[0],struct.unpack_from('<i',d,p+24)[0]])
            else:samples.extend([0,0,0,0,0,0])
        for sub in range(count):
            v=[1,cols,rows,w,h,sub,-121,517,*samples,*mapping]
            save('owned_TMP_decoded_resident_metadata_and_actual_stock_land_table','T '+' '.join(map(str,v)),o.tile(v));owned_subs+=1
    data=subprocess.check_output([str(a.native),'--decode',str(a.map)])
    # Native decoding is a supplied fixture boundary, never original LZO proof.
    count=(len(data)-4)//11 if len(data)%11==4 else len(data)//11
    assert len(data) in (count*11,count*11+4)
    records=[struct.unpack_from('<hhIBBB',data,i*11) for i in range(count)]
    indices=[y*512+x for x,y,*_ in records];assert len(set(indices))==count
    raw=data[:count*11]+struct.pack('<I',term)
    c=' '.join(map(str,['R',17,term,invalid,0,count,*indices,raw.hex()]))
    save('all_owned_map_records_native_decoded_fixture_actual_original_reader_and_constructor',c,o.run_map('R',17,term,invalid,(),indices,raw))
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'ordered_selected_stores':o.store_count,
      'supplied_stream_reads':o.read_calls,'actual_tile_helper_roots':o.tile_calls,'owned_records':count,'owned_subtiles':owned_subs,
      'decoded_owned_fixture_sha256':__import__('hashlib').sha256(data).hexdigest(),'native_decoding_is_fixture_boundary':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--map',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/map-light/assets/mp03t4.map')
    p.add_argument('--tiles',nargs='+',type=Path,default=[ROOT/f'private/migration/supplied-ra2-1006/composition/assets/{name}.tem' for name in ('clear01','cliff01','slope01')])
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-cell-input-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/cell-inputs-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh map input destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:raise AssertionError('Native map input runner: '+error.stderr) from error
    elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Map input counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Map input run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 map cell/TMP input results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
