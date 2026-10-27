#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base ordinary loaded Overlay placement evidence and identity-bound replay."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_overlay_placement import verify
SOURCES=('src/assets/MapWallUpdate.hpp','src/assets/OverlayPlacement.hpp','src/assets/OverlayPlacement.cpp',
 'src/assets/OverlayTypeInputs.hpp','src/assets/MapOverlayLoading.hpp','src/assets/MapCellInputs.hpp',
 'src/sim/Drive.hpp','tests/overlay_placement_vectors.cpp','tests/compare_overlay_placement.py',
 'tests/original_overlay_placement.py','tools/verify_overlay_placement.py',
 'tests/original_overlay_type_inputs.py','tools/verify_overlay_type_inputs.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py',
 'tools/verify_terrain_visibility.py')
def parse(command):
    tokens=command.split();assert tokens and tokens[0] in ('C','M','U')
    op=tokens[0];v=list(map(int,tokens[1:]));assert len(v)==21
    assert all(0<=v[i]<=0xffffffff for i in (0,11,12))
    assert all(-2147483648<=v[i]<=2147483647 for i in (1,2,10,13,14,17))
    assert all(0<=v[i]<=255 for i in (3,4,5,6,7,8,9,18,19,20))
    assert 0<=v[16]<=v[15]<=32 and v[17]<=32
    i=v[1];assert v[2]!=9 and i not in (0x18,0x19,0xed,0xee,0x7e,0xa7) and not (0x7a<=i<=0x7d or 0xe9<=i<=0xec)
    return op,v
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Overlay placement engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Overlay placement identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Overlay placement counts differ')
    for command in e['commands']:
        try:parse(command)
        except (ValueError,AssertionError,IndexError):raise ValueError('Malformed overlay placement command') from None
def generate(a):
    from original_overlay_placement import OverlayPlacementOracle
    oracle=OverlayPlacementOracle(a.exe);rng=random.Random(0x504c4143);commands=[];expected=[];labels=[];groups={}
    def packed(x,y):return (x&65535)|((y&65535)<<16)
    def save(label,op,v):
        command=op+' '+' '.join(map(str,v));parse(command);commands.append(command)
        expected.append(oracle.run(op,v));labels.append(label);groups[label]=groups.get(label,0)+1
    def make(seed,**kw):
        values=dict(seed=seed,index=102,land=0,crate=0,slope=0,enabled=1,limbo=1,onMap=0,redraw=0,active=1,
          mode=1,position=packed(51,72),invalid=0x7fff7fff,flag=17,incoming=-1,capacity=4,count=2,growth=3,owns=1,growResult=1,resource=73)
        values.update(kw);return list(values.values())
    for mode in (-2147483648,-1,0,1,2,3,4,2147483647):
        for limbo in (0,1,2,255):
            for on_map in (0,1,255):
                for dirty in (0,1,255):
                    save('complete_mark_base_decisions_preserve_rejected_and_nonplacement_effects','M',make(rng.getrandbits(32),mode=mode,limbo=limbo,onMap=on_map,redraw=dirty))
    for mode in (1,3):
        for slope in (0,1,4,5,127,255):
            for index in (102,178):
                for land in (0,5):
                    for crate in (0,255):
                        save('mark_slope_dummy_exception_resource_then_crate_and_retirement_order','M',make(rng.getrandbits(32),mode=mode,limbo=0,slope=slope,index=index,land=land,crate=crate))
    for enabled in (0,1,2,255):
        for limbo in (0,1,255):
            for on_map in (0,1,255):
                for slope in (0,4,5,255):
                    save('object_unlimbo_gates_mark_rejection_and_consumed_temporary_success','U',make(rng.getrandbits(32),enabled=enabled,limbo=limbo,onMap=on_map,slope=slope,redraw=255))
    positions=[packed(x,y) for x,y in ((0,0),(1,1),(51,72),(-1,-1),(-32768,32767),(32767,-32768),(511,511),(32767,32767))]
    configurations=[(4,2,3,1,1),(4,4,3,1,1),(4,4,3,1,255),(4,4,3,1,0),
      (4,4,3,0,1),(0,0,3,0,1),(0,0,0,0,1),(4,4,0,1,1),
      (4,4,-1,1,1),(4,4,3,255,1),(4,2,3,0,0)]
    for p in positions:
        for capacity,count,growth,owns,result in configurations:
            for invalid in (p,p^1,p^0x10000):
                save('constructor_identity_registry_growth_invalid_words_and_flag_reset','C',make(rng.getrandbits(32),position=p,invalid=invalid,
                  capacity=capacity,count=count,growth=growth,owns=owns,growResult=result,incoming=rng.choice((-2147483648,-1,0,1,2147483647))))
    for n in range(384):
        save('seeded_complete_constructor_supplied_base_state_type_and_placement_edges','C',make(rng.getrandbits(32),
          index=rng.choice((-2147483648,-1,0,1,27,102,178,216,240,2147483647)),
          land=rng.choice((-2147483648,-1,0,1,5,10,2147483647)),crate=rng.choice((0,1,2,255)),
          slope=rng.choice((0,1,4,5,127,255)),enabled=rng.choice((0,1,255)),limbo=rng.choice((0,1,255)),
          onMap=rng.choice((0,1,255)),redraw=rng.choice((0,1,255)),active=rng.choice((0,1,255)),
          position=rng.choice(positions),flag=rng.randrange(-2147483648,2147483648),incoming=rng.randrange(-2147483648,2147483648),
          resource=rng.randrange(256)))
    for seed in (0,0xfedcba98,0x01234567,0xffffffff):
        save('identity_provider_absent_zero_counter_wrapped_increment_before_invalid_position','C',
             make(seed,invalid=packed(51,72)))
    return commands,expected,labels,{'groups':groups,'audited_roots':oracle.audit_calls,'actual_root_entries':oracle.roots,
      'ordered_selected_guest_stores':oracle.stores,'supplied_service_calls':oracle.services,
      'base_cell_resource_recalculation_and_retirement_effects_supplied':True}
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--exe',type=Path,required=True)
    parser.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-placement-vectors')
    parser.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-placement-v1')
    parser.add_argument('--expectations',type=Path);parser.add_argument('--report',type=Path);a=parser.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh overlay placement destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Overlay placement result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Overlay placement run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 ordinary overlay placement results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
