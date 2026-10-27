#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Cell variant selection and actual XOR RNG state against exact original."""
import argparse,json,random,struct,time
from pathlib import Path
import pefile
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_tile_variants import verify
SOURCES=('src/sim/OriginalRandom.hpp','src/sim/OriginalRandom.cpp','src/assets/TileVariants.hpp','src/assets/TileVariants.cpp',
 'tests/tile_variant_vectors.cpp','tests/compare_tile_variants.py','tests/original_tile_variants.py','tools/verify_tile_variants.py',
 'tools/verify_map_cell_inputs.py','tests/original_presentation.py','tests/original_foot_lit.py','tests/presentation_profiles.py',
 'tests/presentation_evidence.py','tests/compare_original.py','tests/compare_terrain_visibility.py','tools/verify_terrain_visibility.py')
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def parse(cmd):
    t=cmd.split();op=t[0];v=list(map(int,t[1:]));assert op in ('R','V')
    if op=='R':
        assert len(v)==254;disabled,first,second,count,*table=v
        assert 0<=disabled<=255 and 0<=first<250 and 0<=second<250 and 1<=count<=1024 and all(0<=n<=4294967295 for n in table)
        return op,[disabled,first,second,count,table]
    assert len(v)==357
    initialized,disabled,first,second=v[:4];table=v[4:254];cache=v[254:318];small=v[318:334];d=v[334:350]
    x,y,sub,count,cols,rows,present=v[350:]
    assert 0<=initialized<=255 and 0<=disabled<=255 and 0<=first<250 and 0<=second<250 and all(0<=n<=4294967295 for n in table)
    assert all(-2147483648<=n<=2147483647 for n in [*cache,*small,count]) and all(-1<=n<=1 for n in d)
    assert -32768<=x<=32767 and -32768<=y<=32767 and 0<=sub<=255 and present in (0,1)
    assert 0<=cols<=255 and 0<=rows<=255 and (not sub or not present or (cols and rows))
    return op,[initialized,disabled,first,second,table,cache,small,[d[i:i+2] for i in range(0,16,2)],x,y,sub,count,cols,rows,present]
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Variant engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Variant source/inspection identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Variant counts differ')
    for cmd in e['commands']:
        try:parse(cmd)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed variant command') from None
def generate(a):
    from original_tile_variants import TileVariantOracle
    o=TileVariantOracle(a.exe);rng=random.Random(0x56415249);p=pefile.PE(str(a.exe))
    small=list(struct.unpack('<16i',p.get_data(0x7d2b90-0x400000,64)));neighbors=list(struct.unpack('<16i',p.get_data(0x7d2bd0-0x400000,64)))
    commands=[];expected=[];labels=[];draws=[]
    def add(label,op,v):
        cmd=op+' '+' '.join(map(str,v));kind,args=parse(cmd);result=o.random(*args) if kind=='R' else o.variant(*args)
        commands.append(cmd);expected.append(list(map(str,result)));labels.append(label);draws.append(result[-1])
    indices=[0,1,102,103,248,249]
    for i in range(64):
        table=[rng.getrandbits(32) for _ in range(250)];first=rng.choice(indices);second=first if i%4==0 else rng.choice(indices)
        add('XOR_step_sequence_wrap_disabled_and_full_state','R',[rng.choice([0,0,0,1,255]),first,second,rng.choice([1,2,249,250,251,503,1024]),*table])
    edge=[-32768,-32767,-257,-256,-1,0,1,255,256,32767]
    for i in range(256):
        initialized=0 if i%4==0 else rng.choice([1,2,255]);disabled=rng.choice([0,0,0,1,255]);table=[rng.getrandbits(32) for _ in range(250)]
        cache=[rng.choice([-2147483648,-1,0,1,2,3,4,5,6,7,2147483647]) for _ in range(64)]
        sub=rng.choice([0,0,1,2,7,255]);cols,rows=rng.choice([(0,0),(1,1),(2,3),(6,1),(1,255),(255,2),(255,255)])
        present=int(bool(cols and rows) and i%7!=0)
        v=[initialized,disabled,rng.choice(indices),rng.choice(indices),*table,*cache,*small,*neighbors,rng.choice(edge),rng.choice(edge),sub,
           rng.choice([-2147483648,-1,0,1,2,3,4,5,6,7,8,2147483647]),cols,rows,present]
        add('first_use_full_table_rng_consumption_resident_null_and_signed_subtile_coordinates','V',v)
    return commands,expected,labels,{'audited_roots':o.audit_calls,'actual_entries':o.entries,'cases_by_root':{'R':64,'V':256},
      'RNG_calls_per_case':draws,'original_tables_from_exact_engine':True,'supplied_initial_RNG_cache_and_resident_fields':True,'original_instructions_modified':False}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True);p.add_argument('--native',type=Path,default=ROOT/'build/native/tile-variant-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/variant-v1');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh variant destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Variant result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Variant run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),
      'original_instructions_modified':False,'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 tile variant/RNG results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
