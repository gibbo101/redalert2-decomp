#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base decoded overlay map reader and full-map permission evidence."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_map_overlay_loading import verify
SOURCES=('src/assets/MapWallUpdate.hpp','src/assets/MapOverlayLoading.hpp','src/assets/MapOverlayLoading.cpp',
 'src/assets/OverlayTypeInputs.hpp','src/assets/MapCellInputs.hpp',
 'tests/map_overlay_loading_vectors.cpp','tests/compare_map_overlay_loading.py',
 'tests/original_map_overlay_loading.py','tools/verify_map_overlay_loading.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py',
 'tools/verify_terrain_visibility.py')
def parse(command):
    tokens=command.split();assert tokens and tokens[0] in ('B','M')
    op=tokens[0];v=list(map(int,tokens[1:]))
    if op=='B':
        assert len(v)==3 and 0<=v[0]<=0xffffffff
        assert all(-2147483648<=n<=2147483647 for n in v[1:])
    else:
        assert len(v)>=15 and 0<=v[0]<=0xffffffff
        assert all(-2147483648<=n<=2147483647 for n in v[1:4]+v[5:7])
        assert 0<=v[4]<=0xffffffff and all(0<=n<=262144 for n in v[7:9])
        assert 0<=v[9]<=1024 and v[10] in (0,1) and 0<=v[11]<=255
        at=12+v[11]*4;assert len(v)>at
        assert all(0<=n<=0xffffffff for n in v[12:at])
        count=v[at];at+=1;assert 0<=count<=16384 and len(v)>at+count
        assert len(set(v[at:at+count]))==count and all(0<=n<262144 for n in v[at:at+count]);at+=count
        for _ in range(2):
            count=v[at];at+=1;assert 0<=count<=262144 and len(v)>=at+2*count
            pairs=[v[i:i+2] for i in range(at,at+2*count,2)]
            assert len({p[0] for p in pairs})==count and all(0<=i<262144 and 0<=b<=255 for i,b in pairs)
            at+=count*2
        assert at==len(v)
    return op,v
def identities(a):
    fixture=json.loads(a.fixture.read_text())
    if any(hash_file(Path(p))!=h for p,h in fixture['source_hashes'].items()):raise ValueError('Overlay source fixture changed')
    return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
      'owned_fixture_sha256':hash_file(a.fixture),'owned_source_hashes':fixture['source_hashes']}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Map overlay loading engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Map overlay loading identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Map overlay loading counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed map overlay command') from None
def generate(a):
    from original_map_overlay_loading import MapOverlayLoadingOracle
    def packed(x,y):return (x&65535)|((y&65535)<<16)
    o=MapOverlayLoadingOracle(a.exe);rng=random.Random(0x4f564c44);commands=[];expected=[];labels=[];groups={}
    def save(label,op,v):
        cmd=op+' '+' '.join(map(str,v));parse(cmd)
        commands.append(cmd);expected.append(o.run(op,v));labels.append(label);groups[label]=groups.get(label,0)+1
    edges=[-2147483648,-2147483647,-65536,-512,-1,0,1,2,80,85,511,512,65535,2147483646,2147483647]
    for n in range(1024):
        p=packed(rng.randrange(-32768,32768),rng.randrange(-32768,32768))
        save('full_map_word_geometry_signed_wrapped_end_and_strict_edges','B',[p,rng.choice(edges),rng.choice(edges)])
    for w,h in ((80,85),(1,1),(2,3),(0,0),(-1,4),(2147483647,1)):
        for x,y in ((0,0),(0,1),(1,0),(1,1),(51,72),(0,80),(1,80),(80,0),(80,1),(125,125),(126,125),(-32768,32767)):
            save('explicit_full_map_boundary_and_owned_cliff_position','B',[packed(x,y),w,h])
    def make(seed,version=2,w=80,h=85,filter=0,results=(1,0),limits=(262144,262144),divisor=0,data_mode=0,types=None,indices=None,active=None,data=None):
        if types is None:types=[[1 if i%3 else 0,2 if i%7==0 else 0,255 if i%5==0 else 0,2 if i%3 else 0] for i in range(255)]
        if indices is None:indices=[y*512+x for x,y in ((51,72),(52,72),(50,72),(1,80),(80,1),(125,125))]
        if active is None:active=[((50+i%20)+(65+i//20)*512,i) for i in range(256)]
        if data is None:data=[]
        return [seed,version,w,h,filter,*results,*limits,divisor,data_mode,len(types),*[x for t in types for x in t],len(indices),*indices,
          len(active),*[x for t in active for x in t],len(data),*[x for t in data for x in t]]
    for version in (-2147483648,0,1):save('old_version_skips_sections_but_executes_empty_cleanup','M',make(17,version=version))
    for results in ((0,0),(-1,-2147483648)):
        save('nonpositive_section_results_skip_stream_passes','M',make(23,results=results))
    for filter,divisor in ((0,0),(1,0),(0,1),(1,2)):
        save('complete_type_pass_all_byte_indices_image_animation_crate_gates_special_restore_and_allocation_failure','M',make(100+filter+divisor,filter=filter,divisor=divisor))
    save('data_pass_without_type_pass_writes_every_permitted_cell_and_fallback','M',make(41,results=(0,1)))
    save('both_passes_short_reads_type_sentinel_and_zero_data_defaults','M',make(49,results=(1,1),limits=(100,137)))
    save('type_pass_with_no_permitted_positions_still_queries_images','M',make(57,w=0,h=0))
    special=[(72*512+51+i,index) for i,index in enumerate((0x17,0x18,0x19,0x1a,0xec,0xed,0xee,0xef))]
    for divisor,results in ((0,(1,0)),(1,(1,1))):
        save('all_four_special_indices_restore_saved_data_even_after_failed_allocation_then_data_pass','M',
          make(65+divisor,divisor=divisor,results=results,types=[[1,0,0,0] for _ in range(240)],active=special))
    fixture=json.loads(a.fixture.read_text())
    save('owned_map_660_overlays_13515_cells_supplied_registry_images_and_constructor_effects','M',fixture['values'])
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'ordered_selected_guest_stores':o.stores,'supplied_service_calls':o.service_calls,
      'owned_cells':fixture['cell_count'],'owned_active_overlays':fixture['active_overlays'],
      'decoded_streams_images_and_temporary_constructor_effects_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/map-overlay-loading-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-loading-v1')
    p.add_argument('--fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh overlay input destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Map overlay loading result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Map overlay loading run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 map overlay loading results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
