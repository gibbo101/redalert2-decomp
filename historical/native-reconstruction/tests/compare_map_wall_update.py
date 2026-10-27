#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base wall connections and complete wall-update parent evidence."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_wall_update import verify
SOURCES=('src/assets/MapWallUpdate.hpp','src/assets/MapWallUpdate.cpp','src/assets/MapCellInputs.hpp',
 'src/render/Redraw.hpp','src/render/Redraw.cpp','src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp',
 'tests/map_wall_update_vectors.cpp','tests/compare_map_wall_update.py','tests/original_map_wall_update.py',
 'tools/verify_map_wall_update.py','tests/original_overlay_type_inputs.py','tools/verify_overlay_type_inputs.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py','tools/verify_terrain_visibility.py')
def records(v,start,count):
    for _ in range(count):
        assert start+6<=len(v);overlay,data,neighbors,passability,owner,n=v[start:start+6];start+=6
        assert -1<=overlay<256 and 0<=data<=255 and 0<=neighbors<=255 and 0<=n<=8
        assert -2147483648<=passability<=2147483647 and -2147483648<=owner<=2147483647
        for _ in range(n):
            assert start+3<=len(v);kind,health,t=v[start:start+3];start+=3
            assert -2147483648<=kind<=2147483647 and -2147483648<=health<=2147483647 and 0<=t<=0xffffffff
    return start
def parse(command):
    tokens=command.split();assert tokens and tokens[0] in ('C','U');op=tokens[0];v=list(map(int,tokens[1:]))
    if op=='C':
        assert len(v)>=9 and all(-2147483648<=v[i]<=2147483647 for i in range(3)) and all(0<=n<=0xffffffff for n in v[3:8])
        assert 0<=v[8]<=8 and len(v)==9+3*v[8]
        for k,h,t in zip(v[9::3],v[10::3],v[11::3]):assert -2147483648<=k<=2147483647 and -2147483648<=h<=2147483647 and 0<=t<=0xffffffff
    else:
        assert len(v)>=27 and 0<=v[0]<=0xffffffff and 0<=v[1]<=255 and 0<=v[2]<=0xffffffff
        assert all(-2147483648<=n<=2147483647 for n in v[3:5]) and 0<=v[5]<=3 and 0<=v[6]<=2 and v[7] in (0,1)
        assert all(0<=n<=0xffffffff for n in v[8:13]+v[18:26]) and v[13:18]==[0,2,4,6,-1]
        assert 1<=v[26]<=16 and records(v,27,v[26])==len(v)
    return op,v
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Wall-update engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Wall-update identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Wall-update counts differ')
    for command in e['commands']:
        try:parse(command)
        except (ValueError,AssertionError,IndexError):raise ValueError('Malformed wall-update command') from None
def generate(a):
    from original_map_wall_update import MapWallUpdateOracle
    o=MapWallUpdateOracle(a.exe);rng=random.Random(0x57434f4e);commands=[];expected=[];labels=[];groups={}
    def packed(x,y):return (x&65535)|((y&65535)<<16)
    dirs=[packed(x,y) for x,y in ((0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1))]
    def save(label,op,v):
        command=op+' '+' '.join(map(str,v));parse(command);commands.append(command);expected.append(o.run(op,v));labels.append(label);groups[label]=groups.get(label,0)+1
    for target in (-2147483648,-1,0,1,2,3,22,26,203,2147483647):
        for overlay in (-2147483648,-1,0,1,2,26,203,2147483647):
            for face in (-2147483648,-1,0,1,2,3,4,6,8,2147483647):
                save('connection_equality_none_and_cardinal_gate_directions','C',[target,face,overlay,1,2,3,4,5,0])
    for target in (0,2,26,203):
        for face in (-1,0,1,2,4,6,7,8):
            for health in (-2147483648,-1,0,1,255,2147483647):
                for t in (0,1,2,3,4,5,0xffffffff):
                    save('ordered_live_building_gate_tower_and_wrong_kind_inputs','C',[target,face,-1,1,2,3,4,5,3,0,99,3,6,health,t,6,1,2])
    for n in range(128):
        gates=[rng.randrange(4) for _ in range(5)];nodes=[rng.choice((0,6,7,-1)),rng.choice((-1,0,1)),rng.randrange(4)]*3
        save('duplicate_and_null_gate_identities_keep_ordered_short_circuits','C',[rng.choice((0,2,26,-1)),rng.choice((-1,0,2,4,6)),rng.choice((-1,2,26)),*gates,3,*nodes])
    overlays=(-1,0,1,2,3,22,26,203,204,240)
    for seed in (0,1,2,3,15,16,31,32,47,48,127,255,256,0x7fffffff,0x80000000,0xffffffff):
        for index in overlays:
            for recalc in range(4):
                for alias in range(3):
                    cells=[]
                    for i in range(9):
                        ov=index if alias==1 else (index if i==0 else rng.choice(overlays))
                        nodes=[6,1,rng.randrange(1,6)] if i%3==1 else []
                        cells.extend([ov,seed&255,(seed+i)&255,rng.choice((-1,0,1,6)),i-2,len(nodes)//3,*nodes])
                    p=rng.choice((packed(51,72),packed(-32768,32767),packed(32767,-32768),0xffffffff))
                    v=[seed,rng.choice((0,1,2,255)),p,rng.randrange(-2147483648,2147483648),rng.randrange(-2147483648,2147483648),recalc,alias,rng.randrange(2),
                       1,2,3,4,5,*o.inspection['visits'],*dirs,9,*cells]
                    save('complete_wall_parent_shared_updates_damage_removal_passability_and_zone_order','U',v)
    for index in (0,1,2,3,22,26,203):
        for damage in range(0,256,16):
            for recalc in range(4):
                cells=[]
                for i in range(9):cells.extend([index if i==0 else -1,damage,0 if i%2 else 255,0,73,0])
                save('isolated_damage_nibbles_all_special_wall_removals_owner_and_passability_gates','U',
                     [16,255,packed(51,72),0,0,recalc,0,1,1,2,3,4,5,*o.inspection['visits'],*dirs,9,*cells])
    if not all(o.branches.values()):raise AssertionError('Missing wall-update branch evidence: '+str(o.branches))
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'actual_branch_entries':o.branches,
      'ordered_selected_guest_stores':o.stores,'supplied_service_calls':o.services,
      'bounds_lookup_occupant_dispatch_queues_zones_expiration_and_cell_recalculation_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-wall-update-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/map-wall-update-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh wall-update destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Wall-update result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Wall-update run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 map wall-update results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
