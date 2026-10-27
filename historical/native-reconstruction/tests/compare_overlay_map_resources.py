#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base overlay reader/placement with actual shared resource children."""
import argparse,json,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_overlay_map_resources import verify
from compare_overlay_map_preparation import SOURCES as BASE_SOURCES,parse as parse_base,commands as base_commands,identities as base_identities
from compare_map_overlay import SOURCES as RESOURCE_SOURCES
SOURCES=tuple(dict.fromkeys((*BASE_SOURCES,*RESOURCE_SOURCES,
 'src/assets/OverlayMapResources.hpp','src/assets/OverlayMapResources.cpp',
 'src/assets/ResourceMapInputs.hpp','src/assets/ResourceMapInputs.cpp',
 'src/assets/ResourceTypeInputs.hpp','src/assets/ResourceTypeInputs.cpp',
 'tests/overlay_map_resource_vectors.cpp','tests/original_overlay_map_resources.py',
 'tests/compare_overlay_map_resources.py','tools/verify_overlay_map_resources.py')))
def parse(command):
    c=command.split();assert c and c[0]=='N';v=list(map(int,c[1:]));assert len(v)>1
    count=v[0];assert 0<=count<=8;at=1+count*6;assert at<len(v)
    resources=[v[i:i+6] for i in range(1,at,6)]
    flags=v[at];assert 0<=flags<=255;at+=1;assert at+flags+9<len(v)
    assert all(0<=n<=255 for n in v[at:at+flags+9]);at+=flags+9
    _,base=parse_base('M '+' '.join(map(str,v[at:])));assert base[11]==flags
    assert all(0<=r[0]<count and 0<=r[1]<flags and 0<r[4]<=2147483647 and
      all(-2147483648<=n<=2147483647 for n in r) for r in resources)
    return 'N',v
def identities(a):
    base=base_identities(a)
    return {**base,'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Overlay map resource engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Overlay map resource identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Overlay map resource counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed overlay resource command') from None
def commands(a,frames):
    from prepare_overlay_loading_fixture import parse_ini
    base=base_commands(a);fixture=json.loads(a.fixture.read_text())
    rules=parse_ini(Path(next(p for p in fixture['source_hashes'] if p.endswith('rules.ini'))).read_bytes())
    flags=[int(rules.get(name,'Tiberium',fallback='no').strip().lower().startswith(('y','t','1'))) for name in fixture['type_names']]
    # Explicit diagnostic resource records: contiguous host-decoded flagged runs,
    # one image per overlay, no slopes, nine frames and distinct signed values.
    # This does not infer original Tiberium defaults, Image=1..4 mapping or INI load.
    runs=[]
    for i,flag in enumerate(flags):
        if flag:
            if runs and i==runs[-1][0]+runs[-1][1]:runs[-1][1]+=1
            else:runs.append([i,1])
    owned_resources=[[i,start,length,0,9,[-2147483648,25,50,2147483647][i]] for i,(start,length) in enumerate(runs)]
    def wrap(v,rs,fs):return [len(rs),*[n for row in rs for n in row],len(fs),*fs,*frames,*v]
    result=[]
    for i in (2,3,4,5,8,9):
        label,v=base[i];owned=i>=8
        fs=flags if owned else [int(n==102) for n in range(v[11])]
        rs=owned_resources if owned else [[0,102,1,0,3,-2147483648]]
        result.append(('actual_resource_'+label,wrap(v,rs,fs)))
    # Replace the sparse small map with adjacent resource cells. Reader order
    # makes later updates see earlier placements; data-only pass stays disabled.
    original=base[3][1];at=12+original[11]*6;cell_count=original[at];end=at+1+cell_count
    selected=[(1+2*512,102),(2+2*512,102),(2+3*512,101),(3+3*512,102),(4+3*512,3)]
    v=original[:end]+[len(selected),*[n for row in selected for n in row],0]+original[-5:]
    # Include a crate on resource land to verify the frame update precedes 255.
    v[12+3*6+4]=5
    fs=[255 if n in (3,101,102) else 0 for n in range(v[11])]
    result.append(('adjacent_resource_first_match_stored_index_and_crate_after_update',wrap(v,
        [[1,101,2,0,2,2147483647],[0,102,1,0,3,-2147483648]],fs)))
    result.append(('resource_marked_missing_range_logs_and_uses_record_zero',wrap(v,
        [[0,0,1,0,1,25]],fs)))
    result.append(('resource_land_nonresource_flag_preserves_preupdate_byte',wrap(v,[],[0]*v[11])))
    return result
def generate(a):
    from original_overlay_map_resources import OverlayMapResourceOracle
    o=OverlayMapResourceOracle(a.exe);cmds=[];expected=[];labels=[]
    for label,v in commands(a,o.frames):
        command='N '+' '.join(map(str,v));parse(command);cmds.append(command);expected.append(o.run('N',v));labels.append(label)
    return cmds,expected,labels,{'groups':dict.fromkeys(labels,1),'audited_roots':o.audit_calls,
      'actual_root_entries':o.roots,'ordered_selected_guest_stores':o.stores,'supplied_service_calls':o.service_calls,
      'actual_constructors':o.constructed,'actual_resource_entries':o.resource_entries,
      'actual_classifier_entries':o.classifier_entries,'missing_resource_logger_services':o.missing_logs,
      'shared_reader_lifetime_wall_and_actual_resource_children':True,
      'resource_type_records_are_diagnostic_supplied_inputs_not_original_initialization':True,
      'recalculation_passability_effects_remain_diagnostic_services':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-map-resource-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-map-resources-v1')
    p.add_argument('--fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
    a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt)
        cmds,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh overlay resource destination invalid or exists')
        now=time.monotonic();cmds,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,cmds);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Overlay map resource result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Overlay map resource run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(cmds),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
      'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':cmds,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(cmds):,} supplied-1.006 shared overlay resource scenarios: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
