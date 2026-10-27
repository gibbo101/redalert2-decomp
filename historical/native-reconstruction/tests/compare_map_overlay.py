#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Fresh exact-base overlay classifier/resource/passability evidence."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_overlay import verify
SOURCES=('src/assets/MapOverlay.hpp','src/assets/MapOverlay.cpp','src/assets/MapCellChildren.hpp',
 'src/assets/MapCellChildren.cpp','src/assets/MapCellInputs.hpp','tests/map_overlay_vectors.cpp',
 'tests/compare_map_overlay.py','tests/original_map_overlay.py','tools/verify_map_overlay.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py',
 'tools/verify_terrain_visibility.py')
def parse(command):
    tokens=command.split();assert tokens and tokens[0] in ('C','P','R')
    op=tokens[0];v=list(map(int,tokens[1:]))
    if op=='P':
        assert len(v)==30 and 0<=v[0]<=0xffffffff
        assert v[4]==-1 or 0<=v[4]<64
        assert all(0<=n<=0xffffffff for n in v[18:])
    else:
        at=2 if op=='C' else 4;assert len(v)>at
        count=v[at];assert 0<=count<=8
        assert len(v)==at+1+count*6+(25 if op=='R' else 0)
        overlay=v[0 if op=='C' else 1];assert overlay==-1 or 0<=overlay<64
        if op=='R':
            assert 0<=v[0]<=0xffffffff
            rest=v[at+1+count*6:]
            assert all(n==-1 or 0<=n<64 for n in rest[8:16])
            assert all(0<=n<=255 for n in rest[16:])
    return op,v
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Map overlay engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Map overlay identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Map overlay counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed map overlay command') from None
def generate(a):
    from original_map_overlay import MapOverlayOracle,packed
    o=MapOverlayOracle(a.exe);rng=random.Random(0x4f564552);commands=[];expected=[];labels=[];groups={}
    def save(label,op,v):
        cmd=op+' '+' '.join(map(str,v));parse(cmd)
        row=o.run(op,v);commands.append(cmd);expected.append(list(map(str,row)));labels.append(label);groups[label]=groups.get(label,0)+1
    def flat(rows):return [x for row in rows for x in row]
    edges=[-2147483648,-2147483647,-64,-1,0,1,16,63,64,2147483646,2147483647]
    for n in range(768):
        overlay=-1 if n%17==0 else n%64;rs=[]
        for i in range(n%9):
            image=rng.choice(edges) if n%3 else overlay-(i%3)
            rs.append([rng.choice(edges),image,rng.choice(edges),rng.choice(edges),1,0])
        save('classifier_signed_wrapped_adjacent_ranges_first_match_byte_gate_and_missing_log','C',
             [overlay,[0,1,2,255,256][n%5],len(rs),*flat(rs)])
    ordinary=[packed(0,-1),packed(1,-1),packed(1,0),packed(1,1),packed(0,1),packed(-1,1),packed(-1,0),packed(-1,-1)]
    positions=[packed(51,72),packed(0,0),packed(32767,32767),packed(-32768,-32768),packed(512,0),packed(-1,1)]
    bits=[0,0x80000000,1,0x80000001,0x3c23d709,0x3c23d70a,0x3c23d70b,0x3f800000,0xbf800000,0x7f800000,0xff800000,0x7fc00000]
    for n in range(2304):
        mask=n%16;flags=[255 if mask&1 else 0,2 if mask&2 else 0,n%2,(n//2)%2,128 if mask&4 else 0,1 if mask&8 else 0]
        shape=[100,0,0,100,100] if n%4 else [rng.choice(edges) for _ in range(5)]
        save('no_occupants_overlay_priority_zero_unordered_ordinary_threshold_and_actual_permission','P',
          [positions[(n//32)%6] if n%4==0 else packed(51,72),rng.choice([-128,-7,0,4,127]),n%256,n%12,
           -1 if n%13==0 else n%64,(n//16)%12,*flags,*shape,n%2,*[bits[(n//192+i)%len(bits)] for i in range(12)]])
    # All 256 neighbor masks, every positive tested divisor, null/nonresource,
    # unmatched-to-zero classification, aliases, fallback and wrapped values.
    for n in range(1024):
        rs=[[0,4,8,4,1+n%11,rng.choice(edges)],[1,20,8,4,1+(n//11)%9,rng.choice(edges)]]
        overlay=[6,14,22,30,50,-1][(n//256)%6];flag=0 if n%31==0 else 255
        mask=n%256;neighbors=[rng.choice([6,14]) if mask&(1<<i) else rng.choice([-1,22,50]) for i in range(8)]
        dirs=ordinary.copy()
        if n%17==0:dirs[0]=packed(512,0);dirs[4]=packed(0,1)
        save('resource_argument_zero_all_neighbor_masks_divisors_wrap_alias_and_fallback','R',
           [positions[(n//128)%6],overlay,flag,rng.randrange(256),len(rs),*flat(rs),*dirs,*neighbors,*o.frames])
    for overlay,flag in [(-1,1),(6,0),(50,1)]:
        save('resource_absent_nonresource_and_unmatched_fallback','R',
          [packed(51,72),overlay,flag,201,1,0,4,8,4,3,-2147483648,*ordinary,*([-1]*8),*o.frames])
    for overlay in range(64):
        save('classifier_explicit_adjacent_endpoints_and_overlapping_first_match','C',
          [overlay,255,2,7,4,8,4,1,0,9,6,8,4,1,0])
    profiles=[(1,0,[0]*6),(1,0,[2,255,0,0,255,255]),(1,0,[0,255,0,0,255,255]),
              (1,0,[0,0,0,0,255,255]),(2,0,[0,0,0,0,255,0]),(0,-1,[0]*6)]
    for speed in bits:
        for cell_land,overlay,flags in profiles:
            speeds=[0x3f800000]*12;speeds[0]=speed
            save('passability_explicit_permitted_zero_nan_threshold_and_flag_priority','P',
              [packed(51,72),0,0,cell_land,overlay,0,*flags,100,0,0,100,100,1,*speeds])
    for mask in range(256):
        save('resource_explicit_all_256_masks_with_all_eight_neighbors_present','R',
          [packed(51,72),6,255,201,1,0,4,8,4,1+mask%11,-2147483648,
           *ordinary,*[6 if mask&(1<<i) else -1 for i in range(8)],*o.frames])
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'ordered_selected_stores':o.stores,'map_lookup_events':o.queries,'missing_resource_log_services':o.logs,
      'classifier_resource_passability_permission_lookup_instructions_actual':True,
      'registries_defaults_ini_land_directions_initial_state_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-overlay-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-children-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh map overlay destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Map overlay result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Map overlay run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 map overlay results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
