#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete tile usage/load sweep with actual nested iterator/variant/image paths."""
import argparse,json,random,struct,subprocess,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_tile_image import synthetic,valid_command as valid_image,OWNED
from compare_theater_tile_inputs import owned_inputs
from verify_tile_sweep import verify
SOURCES=('src/assets/TileSweep.hpp','src/assets/TileSweep.cpp','src/assets/TileVariants.hpp','src/assets/TileVariants.cpp',
 'src/assets/TileImagePreparation.hpp','src/assets/TileImagePreparation.cpp','src/assets/MapCellInputs.hpp','src/assets/Bytes.hpp',
 'src/sim/OriginalRandom.hpp','src/sim/OriginalRandom.cpp','src/sim/OriginalMath.hpp','tests/tile_sweep_vectors.cpp',
 'tests/compare_tile_sweep.py','tests/original_tile_sweep.py','tests/original_tile_variants.py','tests/original_tile_image.py',
 'tests/compare_tile_image.py','tests/compare_theater_tile_inputs.py','tools/verify_tile_sweep.py','tools/verify_tile_variants.py',
 'tools/verify_tile_image.py','tools/verify_theater_tile_inputs.py','tools/verify_map_cell_inputs.py','tests/original_presentation.py',
 'tests/original_foot_lit.py','tests/presentation_profiles.py','tests/presentation_evidence.py','tests/compare_original.py',
 'tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
 'map_decoder_sha256':hash_file(a.decoder),'owned_map_sha256':hash_file(a.map),'owned_ini_sha256':hash_file(a.ini),'owned_TMPs':{n:hash_file(a.assets/n) for n in OWNED}}
def encoded(s):return s.encode().hex() if s else '-'
def command(args):
    width,force,keep,clear,cursor,primary,nodes,cells,files,initialized,disabled,first,second,table,cache,small,neighbors=args
    t=['S',*map(str,[width,force,keep,clear,*cursor,initialized,disabled,first,second,*table,*cache,*small,*[v for d in neighbors for v in d],len(primary),*primary,len(nodes)])]
    for row in nodes:t += [*map(str,row[:6]),encoded(row[6]),*map(str,row[7:])]
    t.append(str(len(cells)))
    for row in cells:t += list(map(str,row))
    t.append(str(len(files)))
    for name,data in files.items():t += [encoded(name),data.hex()]
    return ' '.join(t)
def parse(cmd):
    t=cmd.split();assert t[0]=='S';h=list(map(int,t[1:13]));assert len(h)==12
    width,force,keep,clear,x,y,remaining,index,initialized,disabled,first,second=h
    assert 2<=width<=255 and all(0<=n<=255 for n in (force,keep,initialized,disabled)) and 0<=first<250 and 0<=second<250 and 0<=index<262144
    assert all(-2147483648<=n<=2147483647 for n in (x,y,remaining,clear))
    table=list(map(int,t[13:263]));cache=list(map(int,t[263:327]));small=list(map(int,t[327:343]));d=list(map(int,t[343:359]));at=359
    assert len(table)==250 and all(0<=n<=4294967295 for n in table) and len(cache)==64 and all(0<=n<=7 for n in cache)
    assert len(small)==16 and all(0<=n<=3 for n in small) and len(d)==16 and all(-1<=n<=1 for n in d)
    count=int(t[at]);at+=1;assert 0<=count<=1024;primary=list(map(int,t[at:at+count]));at+=count
    count=int(t[at]);at+=1;assert 0<=count<=1024;nodes=[]
    for i in range(count):
        before=list(map(int,t[at:at+6]));name='' if t[at+6]=='-' else bytes.fromhex(t[at+6]).decode('ascii');after=list(map(int,t[at+7:at+10]));at+=10
        assert len(before)==6 and len(after)==3 and 0<=len(name)<=13 and all(c.isalnum() or c in '._-' for c in name)
        nxt,variants,usage,lazy,required,owned=before;file_id,resident,prepared=after
        assert -1<=nxt<count and 1<=variants<=32 and 0<=usage<=4294967295 and all(0<=n<=255 for n in (lazy,required,owned)) and resident in (0,1) and prepared in (0,1)
        nodes.append([*before,name,*after])
    assert all(-1<=n<len(nodes) for n in primary) and (not primary or 0<=clear<len(primary))
    count=int(t[at]);at+=1;assert 0<=count<=20000;cells=[];positions=set()
    for i in range(count):
        row=list(map(int,t[at:at+5]));at+=5;cx,cy,tile,sub,flags=row
        assert 0<=cx<512 and 0<=cy<512 and 0<=tile<=2147483647 and 0<=sub<=255 and 0<=flags<=4294967295 and (cx,cy) not in positions
        positions.add((cx,cy));cells.append(row)
    count=int(t[at]);at+=1;assert 0<=count<=64 and len(t)==at+count*2;files={}
    for i in range(count):
        name='' if t[at]=='-' else bytes.fromhex(t[at]).decode('ascii');data=bytes.fromhex(t[at+1]);at+=2;assert name not in files
        valid_image('L '+' '.join(map(str,[0,0,11,3,0,3,5,2,*range(16)]))+' '+data.hex());files[name]=data
    assert all(-1<=row[7]<len(files) and (not(row[8] or row[9]) or row[7]>=0) for row in nodes)
    return width,force,keep,clear,[x,y,remaining,index],primary,nodes,cells,files,initialized,disabled,first,second,table,cache,small,[d[i:i+2] for i in range(0,16,2)]
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Sweep engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Sweep source/inspection/input identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Sweep counts differ')
    for cmd in e['commands']:
        try:parse(cmd)
        except (AssertionError,ValueError,IndexError,UnicodeError):raise ValueError('Malformed sweep command') from None
def generate(a):
    from original_tile_sweep import TileSweepOracle
    o=TileSweepOracle(a.exe);rng=random.Random(0x53574545);p=pefile.PE(str(a.exe))
    small=list(struct.unpack('<16i',p.get_data(0x7d2b90-0x400000,64)));d=struct.unpack('<16i',p.get_data(0x7d2bd0-0x400000,64));neighbors=[d[i:i+2] for i in range(0,16,2)]
    commands=[];expected=[];labels=[];visits=[];usage=[];load_counts=[]
    def state():return [rng.choice([0,1,2,255]),rng.choice([0,0,1,255]),rng.choice([0,103,249]),rng.choice([0,103,249]),[rng.getrandbits(32) for _ in range(250)],[rng.randrange(8) for _ in range(64)],small,neighbors]
    def add(label,args):
        cmd=command(args);checked=parse(cmd);result=o.run(*checked);commands.append(cmd);expected.append(list(map(str,result)));labels.append(label)
        visits.append(len(o.visits));usage.append(len(o.usage)//2);load_counts.append(len(o.requests))
    for case in range(128):
        width=2+case%4;height=2+(case//4)%3;primary=[];nodes=[];files={}
        for group,size in enumerate((1,2,5 if case%2 else 3)):
            primary.append(len(nodes))
            for alt in range(size):
                node=len(nodes);name=f'N{node:03d}.TEM';data=synthetic(*rng.choice([(1,1),(2,3),(6,1)]),rng,case+node);files[name]=data
                empty=bool(alt and (case+node)%7==0);resident=int(empty or rng.randrange(2));prepared=rng.randrange(2)
                nodes.append([node+1 if alt+1<size else -1,size-alt,rng.choice([0,0,1,4294967295]),rng.choice([0,1,2,255]),rng.choice([0,1,255]),rng.choice([0,1,2,255]),'' if empty else name,node,resident,prepared])
        primary.append(-1);cells=[]
        for y in range(2*(width+height)):
            for x in range(width+height+1):
                if x+y>width and x-y<width and y-x<width and x+y<=width+2*height:
                    cells.append([x,y,rng.choice([0,1,2,65535,len(primary)+7]),rng.choice([0,1,2,255]),rng.getrandbits(32)])
        if case%16==0:cells=[c for c in cells if c[:2]!=[1,width]]
        force=0 if case%16==0 else rng.choice([0,0,1,2,255]);initial=[case-9,case+17,case%7,case%262144]
        add('complete_usage_iterator_forced_shape_count_reduction_lazy_load_release_and_RMG_keep', [width,force,rng.choice([0,1,2,255]),0,initial,primary,nodes,cells,files,*state()])
    numbers,rows=owned_inputs(a.ini);nodes=[];primary=[];files={n[:-4].capitalize()+'.TEM':(a.assets/n).read_bytes() for n in OWNED}
    # Native-decoded map bytes and decoded INI/type assignments are fixture inputs.
    import configparser
    ini=configparser.ConfigParser(interpolation=None,strict=False,inline_comment_prefixes=(';',));ini.read(a.ini,encoding='latin1')
    prefixes=[ini.get(f'TileSet{i:04d}','FileName',fallback='TILE').strip() for i in range(len(rows))]
    file_names=list(files)
    for s,row in enumerate(rows[:-1]):
        for j in range(max(0,row[0])):
            index=len(nodes);name=prefixes[s]+f'{j+1:02d}.TEM';found=next((k for k,n in enumerate(file_names) if n.lower()==name.lower()),-1)
            primary.append(index);nodes.append([-1,1,0,0,int(bool(row[6]&16)),0,'',found,int(found>=0),int(found>=0)])
    raw=subprocess.check_output([str(a.decoder),'--decode',str(a.map)]);count=(len(raw)-4)//11 if len(raw)%11==4 else len(raw)//11
    records=[struct.unpack_from('<hhIBBB',raw,i*11) for i in range(count)];cells=[[x,y,tile,sub,0] for x,y,tile,sub,level,ice in records]
    add('all_owned_map_records_actual_iterator_usage_with_838_primary_types_three_resident_images', [80,0,0,0,[7,9,2,13],primary,nodes,cells,files,*state()])
    assert len(o.visits)==count+1 and len(o.usage)//2==count,'Owned iterator did not visit every supplied map cell'
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_entries':o.entries,'guest_stores':o.stores,'supplied_service_calls':o.service_calls,
      'visits_per_case':visits,'usage_stores_per_case':usage,'file_requests_per_case':load_counts,'owned_records':count,'owned_primary_types':len(primary),
      'native_decoded_map_fixture_sha256':__import__('hashlib').sha256(raw).hexdigest(),'construction_file_heap_vector_timer_log_services_supplied':True,'original_instructions_modified':False}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/tile-sweep-vectors')
    p.add_argument('--map',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/map-light/assets/mp03t4.map');p.add_argument('--ini',type=Path,default=ROOT/'private/map-depth-1006/theater-assets/temperat.ini')
    p.add_argument('--assets',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/composition/assets');p.add_argument('--decoder',type=Path,default=ROOT/'build/native/map-cell-input-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/sweep-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh sweep destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Sweep result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Sweep run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 tile sweep results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
