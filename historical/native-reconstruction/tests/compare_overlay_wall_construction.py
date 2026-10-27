#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base wall constructor/Unlimbo/Mark nested with wall-construction evidence."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_overlay_wall_construction import verify
from compare_map_wall_update import parse as parse_update, SOURCES as WALL_SOURCES
from compare_overlay_placement import SOURCES as PLACEMENT_SOURCES
SOURCES=tuple(dict.fromkeys((*WALL_SOURCES,*PLACEMENT_SOURCES,
 'tests/overlay_wall_construction_vectors.cpp','tests/compare_overlay_wall_construction.py',
 'tests/original_overlay_wall_construction.py','tools/verify_overlay_wall_construction.py',
 'tools/verify_overlay_wall_placement.py')))
def parse(command):
    tokens=command.split();assert tokens and tokens[0] in ('C','U');op=tokens[0];v=list(map(int,tokens[1:]));assert len(v)>=44
    assert 0<=v[0]<256 and v[0] not in (0x18,0x19,0xed,0xee,0x7e,0xa7)
    assert all(0<=n<=255 for n in v[1:7]) and all(0<=n<=0xffffffff for n in v[7:9])
    assert all(-2147483648<=n<=2147483647 for n in v[9:12])
    assert 0<=v[13]<=v[12]<=16 and -2147483648<=v[14]<=16 and 0<=v[15]<=255 and 0<=v[16]<=0xffffffff
    parse_update('U '+' '.join(map(str,v[17:])))
    assert v[18]==1
    return op,v
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Wall construction engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Wall construction identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Wall construction counts differ')
    for command in e['commands']:
        try:parse(command)
        except (ValueError,AssertionError,IndexError):raise ValueError('Malformed wall-construction command') from None
def generate(a):
    from original_overlay_wall_construction import OverlayWallConstructionOracle
    from original_map_wall_update import packed
    o=OverlayWallConstructionOracle(a.exe);rng=random.Random(0x57434f4e53);commands=[];expected=[];labels=[];groups={}
    dirs=[packed(x,y) for x,y in ((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))]
    configs=[(4,2,3,1,1),(4,4,3,1,1),(4,4,3,1,255),(4,4,3,1,256),(4,4,3,1,257),
      (4,4,3,0,1),(0,0,3,0,1),(0,0,0,0,1),(4,4,0,1,1),(4,4,-1,1,1),(4,4,3,255,0)]
    def make(seed,**kw):
        d=dict(index=203,slope=0,enabled=1,limbo=1,on_map=0,redraw=0,active=1,p=packed(51,72),invalid=0x7fff7fff,
          flag=-2147483648,incoming=0,owner=3,cfg=configs[0],recalc=1,alias=0,n=9,all_walls=0,cell_p=packed(51,72),custom=False)
        d.update(kw);capacity,count,growth,owns,result=d['cfg']
        prefix=[d['index'],d['slope'],d['enabled'],d['limbo'],d['on_map'],d['redraw'],d['active'],d['p'],d['invalid'],d['flag'],d['incoming'],d['owner'],capacity,count,growth,owns,result]
        cells=[]
        for i in range(d['n']):
            overlay=rng.choice((-1,0,1,2,3,22,26,203,204,240));nodes=[rng.choice((0,6,7)),rng.choice((-1,0,1,2147483647)),rng.randrange(6)]*2
            cells.extend([overlay,rng.choice((0,16,32,48,127,255)),(seed+i*31)&255,rng.randrange(-2147483648,2147483648),rng.randrange(-2147483648,2147483648),2,*nodes])
        directions=[rng.getrandbits(32) for _ in range(8)] if d['custom'] else dirs
        return prefix+[seed,1,d['cell_p'],rng.choice((0,-2147483648,2147483647)),rng.choice((0,-2147483648,2147483647)),d['recalc'],d['alias'],d['all_walls'],1,2,3,4,5,0,2,4,6,-1,*directions,d['n'],*cells]
    def save(label,op,v):
        command=op+' '+' '.join(map(str,v));parse(command);commands.append(command);expected.append(o.run(op,v));labels.append(label);groups[label]=groups.get(label,0)+1
    for enabled in (0,1,2,255):
        for limbo in (0,1,255):
            for on_map in (0,1,255):
                for redraw in (0,1,255):
                    save('actual_unlimbo_gates_and_rejected_base_state','U',make(rng.getrandbits(32),enabled=enabled,limbo=limbo,on_map=on_map,redraw=redraw))
    for cfg in configs:
        for p in (0x00480033,0x7fff8000,0x80007fff,0x7fff7fff):
            for enabled in (0,1,255):
                for incoming in (-1,0,2147483647):
                    save('constructor_registration_growth_identity_invalid_coordinates_and_flag_reset','C',make(rng.getrandbits(32),cfg=cfg,p=p,enabled=enabled,incoming=incoming))
    for op in ('C','U'):
        for index in (0,1,2,3,22,26,178,203,204,240):
            for slope in (0,4,5,255):
                for alias in range(3):
                    for recalc in range(4):
                        save('complete_wall_placement_actual_shared_update_owner_and_neighbor_mutations',op,make(rng.getrandbits(32),index=index,slope=slope,alias=alias,recalc=recalc,incoming=rng.choice((-1,0,1)),flag=rng.choice((-1,0,1)),owner=rng.randrange(-2147483648,2147483648)))
    for seed in (0,1,254,255,256,0x01234567,0xfedcba98,0xffffffff):
        for alias in range(3):
            for p in (0x7fff8000,0x80007fff,0xffffffff,0x00000000):
                save('supplied_direction_word_wrap_alias_counter_overflow_and_identity_absence','C',make(seed,alias=alias,p=p,cell_p=p,custom=True,n=1 if alias==1 else 9,cfg=(0,0,1,1,257)))
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'wall_branch_entries':o.branches,'successful_wall_permissions':o.placements,
      'ordered_selected_guest_stores':o.stores,'supplied_service_calls':o.services,
      'base_construction_growth_bounds_lookup_queues_recalculation_retirement_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-wall-construction-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-wall-construction-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh wall-construction destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Wall construction result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Wall construction run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 map wall-construction results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
