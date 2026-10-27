#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base decoded overlay map reader and full-map permission evidence."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_overlay_map_preparation import verify
from compare_map_overlay_loading import SOURCES as READER_SOURCES,parse as parse_reader
from compare_overlay_object_lifetime import SOURCES as LIFETIME_SOURCES
from compare_overlay_wall_construction import SOURCES as WALL_SOURCES
SOURCES=tuple(dict.fromkeys((*READER_SOURCES,*LIFETIME_SOURCES,*WALL_SOURCES,
 'src/assets/OverlayMapPreparation.hpp','src/assets/OverlayMapPreparation.cpp',
 'tests/overlay_map_preparation_vectors.cpp','tests/original_overlay_map_preparation.py',
 'tests/compare_overlay_map_preparation.py','tools/verify_overlay_map_preparation.py',
 'tools/prepare_overlay_loading_fixture.py')))
def parse(command):
    tokens=command.split();assert tokens and tokens[0]=='M';v=list(map(int,tokens[1:]));assert len(v)>=20
    n=v[11];assert 0<=n<=255;at=12+6*n;assert at<len(v)
    types=[v[i:i+6] for i in range(12,at,6)]
    assert all(0<=t[2]<=255 and 0<=t[3]<=255 and 0<=t[5]<=255 and -2147483648<=t[4]<=2147483647 for t in types)
    old=v[:12]+[x for t in types for x in t[:4]]+v[at:-5]
    parse_reader('M '+' '.join(map(str,old)))
    enabled,capacity,growth,owns,result=v[-5:];assert 0<=enabled<=255 and 0<=capacity<=1024 and 0<=growth<=1024 and 0<=owns<=255 and 0<=result<=0xffffffff
    return 'M',v
def identities(a):
    fixture=json.loads(a.fixture.read_text())
    if any(hash_file(Path(p))!=h for p,h in fixture['source_hashes'].items()):raise ValueError('Overlay source fixture changed')
    return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
      'owned_fixture_sha256':hash_file(a.fixture),'owned_source_hashes':fixture['source_hashes']}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Overlay map preparation engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Overlay map preparation identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Overlay map preparation counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed map overlay command') from None
def commands(a):
    from prepare_overlay_loading_fixture import parse_ini
    fixture=json.loads(a.fixture.read_text());rules=parse_ini(Path(next(p for p in fixture['source_hashes'] if p.endswith('rules.ini'))).read_bytes())
    land_names=('clear','road','water','rock','wall','tiberium','beach','rough','ice','railroad','tunnel','weeds')
    def yes(name,key):return rules.get(name,key,fallback='no').strip().lower().startswith(('y','t','1'))
    owned=[];old=fixture['values'];n=old[11]
    for i,name in enumerate(fixture['type_names']):
        land=rules.get(name,'Land',fallback='Clear').strip().lower();assert land in land_names
        owned.extend([*old[12+4*i:16+4*i],5 if yes(name,'Tiberium') else land_names.index(land),int(yes(name,'Wall'))])
    owned=old[:12]+owned+old[12+4*n:]+[1,0,64,1,1]
    def make(seed=7,version=2,results=(1,1),limits=(262144,262144),divisor=0,enabled=1,w=2,h=3,growth=16,owns=1,result=1):
        types=[[1,0,0,0,0,0] for _ in range(103)]
        for i in (0,2,26):types[i][5]=1
        types[102][4]=5;types[3][2]=255;types[4][0]=0
        cells=[y*512+x for y in range(1,6) for x in range(1,6) if x+y>2 and abs(x-y)<2 and x+y<=8]
        active=[(1+2*512,0),(2+2*512,0),(2+3*512,102),(3+3*512,3),(4+3*512,4),(20+20*512,102)]
        data=[(1+2*512,32),(2+2*512,7),(2+3*512,11),(3+3*512,255)]
        return [seed,version,w,h,0,*results,*limits,divisor,1,len(types),*[x for row in types for x in row],len(cells),*cells,len(active),*[x for row in active for x in row],len(data),*[x for row in data for x in row],enabled,0,growth,owns,result]
    return [
      ('old_version_actual_empty_cleanup',make(version=1)),
      ('nonpositive_sections_actual_empty_cleanup',make(results=(0,-1))),
      ('small_shared_wall_resource_crate_both_passes_actual_lifetime',make()),
      ('small_type_only_preserves_constructor_effects_and_shared_wall_connections',make(seed=0,results=(1,0),result=257)),
      ('allocation_failure_no_construction_then_data_defaults',make(divisor=1)),
      ('disabled_unlimbo_retains_active_temporary_objects_in_cleanup',make(enabled=0)),
      ('data_only_zero_after_short_read',make(results=(0,1),limits=(262144,10))),
      ('short_type_stream_no_placements',make(limits=(10,10))),
      ('owned_660_overlays_13515_cells_actual_construction_walls_retirement_cleanup_both_passes',owned),
      ('owned_type_only_preserves_actual_placement_before_saved_data',owned[:6]+[0]+owned[7:])]
def generate(a):
    from original_overlay_map_preparation import OverlayMapPreparationOracle
    o=OverlayMapPreparationOracle(a.exe);result=[];expected=[];labels=[];groups={}
    for label,v in commands(a):
        command='M '+' '.join(map(str,v));parse(command);result.append(command);expected.append(o.run('M',v));labels.append(label);groups[label]=1
    return result,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'ordered_selected_guest_stores':o.stores,'supplied_service_calls':o.service_calls,'actual_constructors':o.constructed,
      'shared_decoded_reader_placement_lifetime_wall_update':True,
      'decoding_images_type_cell_initialization_heap_queues_resource_recalculation_broadcast_rtti_base_destruction_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-map-preparation-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-map-preparation-v1')
    p.add_argument('--fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh overlay input destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Overlay map preparation result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Overlay map preparation run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 overlay map preparation results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
