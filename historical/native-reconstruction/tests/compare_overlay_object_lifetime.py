#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base temporary Overlay construction/placement/retirement/cleanup evidence."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_overlay_object_lifetime import verify
SOURCES=('src/assets/MapWallUpdate.hpp','src/assets/OverlayObjectLifetime.hpp','src/assets/OverlayObjectLifetime.cpp',
 'src/assets/OverlayPlacement.hpp','src/assets/OverlayPlacement.cpp',
 'src/assets/OverlayTypeInputs.hpp','src/assets/MapOverlayLoading.hpp','src/assets/MapCellInputs.hpp','src/sim/Drive.hpp',
 'tests/overlay_object_lifetime_vectors.cpp','tests/compare_overlay_object_lifetime.py',
 'tests/original_overlay_object_lifetime.py','tools/verify_overlay_object_lifetime.py',
 'tests/original_overlay_placement.py','tools/verify_overlay_placement.py',
 'tests/original_overlay_type_inputs.py','tools/verify_overlay_type_inputs.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py','tools/verify_terrain_visibility.py')
def parse(command):
    tokens=command.split();assert tokens and tokens[0] in ('C','R','K')
    op=tokens[0];v=list(map(int,tokens[1:]));assert len(v)==13
    assert all(0<=v[i]<=0xffffffff for i in (0,1,2,9))
    assert all(-2147483648<=v[i]<=2147483647 for i in (3,4,7))
    assert 0<=v[6]<=v[5]<=16 and v[7]<=16
    assert 0<=v[8]<=255 and 0<=v[10]<=255 and 1<=v[11]<=8 and 0<=v[12]<=255
    return op,v
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Overlay object lifetime engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Overlay object lifetime identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Overlay object lifetime counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,IndexError,ValueError):raise ValueError('Malformed Overlay object lifetime command') from None
def generate(a):
    from original_overlay_object_lifetime import OverlayObjectLifetimeOracle
    o=OverlayObjectLifetimeOracle(a.exe);rng=random.Random(0x4f424a4c);commands=[];expected=[];labels=[];groups={}
    def save(label,op,v):
        command=op+' '+' '.join(map(str,v));parse(command);commands.append(command);expected.append(o.run(op,v));labels.append(label);groups[label]=groups.get(label,0)+1
    configs=[(4,2,3,1,1),(4,4,3,1,1),(4,4,3,1,255),(4,4,3,1,256),(4,4,3,1,257),
      (4,4,3,0,1),(0,0,3,0,1),(0,0,0,0,1),(4,4,0,1,1),(4,4,-1,1,1),(4,4,3,255,0)]
    positions=[0,0x00480033,0x7fff8000,0x80007fff,0xffffffff,0x7fff7fff]
    def values(seed,p=0x00480033,invalid=0x7fff7fff,cfg=configs[0],n=1,mode=1):
        cap,count,growth,owns,result=cfg
        return [seed,p,invalid,rng.randrange(-2147483648,2147483648),rng.randrange(-2147483648,2147483648),cap,count,growth,owns,result,rng.randrange(256),n,mode]
    for cfg in configs:
        for p in positions:
            for n in (1,3,8):
                for mode in (0,1,8,9,24,25,4,5):
                    save('complete_construct_actual_base_defaults_registrations_placement_retirement_and_optional_cleanup','C',values(rng.getrandbits(32),p=p,cfg=cfg,n=n,mode=mode))
    for cfg in configs:
        for seed in (0,1,255,0x01234567,0xfedcba98):
            for n in (1,3,8):
                for mode in (0,1,32,33,64,65,96,97):
                    save('actual_retirement_tag_broadcast_rejected_limbo_queue_growth_duplicates_and_cleanup','R',values(seed,cfg=cfg,n=n,mode=mode))
    for seed in range(256):
        for n in (1,3,8):
            cfg=(16,16,1,1,1)
            save('nonempty_cleanup_all_active_masks_remove_all_queued_duplicates_keep_active_and_capacity_tails','K',values(seed,cfg=cfg,n=n))
    for seed in (0,0x01234567,0xfedcba98):
        for invalid in (0x00480033,0x00480032,0x00490033):
            save('identity_absence_and_wrapping_before_invalid_constructor_and_empty_cleanup','C',values(seed,invalid=invalid,cfg=(0,0,1,1,1),n=1))
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'ordered_selected_guest_stores':o.stores,'supplied_service_calls':o.services,
      'external_broadcasts_heap_rtti_base_destruction_and_cell_effects_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-object-lifetime-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-object-lifetime-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh Overlay object destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Overlay object result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Overlay object run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 temporary Overlay lifecycle results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
