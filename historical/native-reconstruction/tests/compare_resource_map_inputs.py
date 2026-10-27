#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Initialized resource records propagated into actual shared overlay placement."""
import argparse,json,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_overlay_map_resources import SOURCES as OVERLAY_SOURCES,commands as overlay_commands,parse as parse_overlay,identities as overlay_identities
from compare_resource_type_inputs import SOURCES as TYPE_SOURCES,parse as parse_type
from verify_resource_map_inputs import verify
SOURCES=tuple(dict.fromkeys((*OVERLAY_SOURCES,*TYPE_SOURCES,
 'src/assets/ResourceMapInputs.hpp','src/assets/ResourceMapInputs.cpp',
 'tests/compare_resource_map_inputs.py','tools/verify_resource_map_inputs.py')))

def parse(command):
    c=command.split();assert c and c[0]=='J';v=list(map(int,c[1:]));assert v
    count=v[0];assert 0<count<=8;at=1+count*5;assert at<len(v)
    for row in (v[i:i+5] for i in range(1,at,5)):
        key,length,base,image,value=row
        assert 0<=key<=2147483647 and -2147483648<=length<=2147483647 and 0<=base<=0xffffffff
        assert -2147483648<=image<=2147483647 and -2147483648<=value<=2147483647
    _,tail=parse_overlay('N '+' '.join(map(str,v[at:])))
    assert tail[0]==0
    return 'J',v

def identities(a):
    return {**overlay_identities(a),'inspection':verify(a.exe.read_bytes()),
      'sources':{p:hash_file(ROOT/p) for p in SOURCES}}

def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Resource map inputs engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Resource map inputs identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Resource map inputs counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed resource map command') from None

def commands(a,frames):
    from prepare_overlay_loading_fixture import parse_ini
    fixture=json.loads(a.fixture.read_text());rules=parse_ini(Path(next(p for p in fixture['source_hashes'] if p.endswith('rules.ini'))).read_bytes())
    owned=[]
    for key,name in rules['Tiberiums'].items():
        owned.append([int(key),len(name.strip()),1,int(rules.get(name,'Image')),int(rules.get(name,'Value'))])
    result=[];base=overlay_commands(a,frames)
    def add(label,entries,v):
        # Remove diagnostic records. The native and original sides independently
        # initialize replacements from the same declared INI-result services.
        tail=[0,*v[1+6*v[0]:]]
        result.append((label,[len(entries),*[x for row in entries for x in row],*tail]))
    for i in (0,1,2,3,4,5):
        label,v=base[i];is_owned=i in (4,5)
        add('initialized_'+label,owned if is_owned else [[0,4,1,1,25]],v)
    label,v=base[6]
    add('overlapping_original_default_ranges_first_match_before_crate',[[0,4,1,1,-2147483648],[1,4,1,1,2147483647]],v)
    image_two=v.copy();flags_at=1+6*v[0];image_two[flags_at+1+27]=1
    map_at=flags_at+1+v[flags_at]+9;image_two[map_at+12+27*6+4]=5
    cells_at=map_at+12+v[map_at+11]*6;streams_at=cells_at+1+v[cells_at]
    for i in range(streams_at+2,streams_at+1+v[streams_at]*2,2):
        if image_two[i] in (101,102):image_two[i]=27
    add('existing_numeric_slot_image_two_retains_previous_eight_slopes',[[0,4,1,1,25],[0,4,1,2,50]],image_two)
    add('image_two_initial_zero_slopes_and_failed_existing_ini_ignored',[[0,4,1,2,50],[0,4,256,1,25],[1,-1,1,1,25]],image_two)
    return result

def initialize(o,rows,seed):
    from original_resource_type_inputs import REGISTRIES,digest
    from original_foot_lit import words
    entries=[]
    for i,(key,length,base,image,value) in enumerate(rows):
        conf=[base,36,0,0,value&0xffffffff,0,0,image&0xffffffff,0,0,0,0,0,'-']
        entries.extend([key,key,length&0xffffffff,'Resource'+str(i),*conf])
    size=len(rows)
    command='L '+' '.join(map(str,[seed,size,1,1,1,0,size,1,1,1,0,size,*entries]))
    o.run(*parse_type(command))
    u=o.u;buffer=words(u,REGISTRIES[0]+4,1)[0];count=words(u,REGISTRIES[0]+16,1)[0];result=[]
    def signed(v):return v-0x100000000 if v&0x80000000 else v
    for p in words(u,buffer,count):
        image=words(u,p+0xe0,1)[0];assert image
        result.append([signed(words(u,p+0x98,1)[0]),signed(words(u,image+0x264,1)[0]),
          signed(words(u,p+0xe8,1)[0]),signed(words(u,p+0xec,1)[0]),signed(words(u,p+0xe4,1)[0]),signed(words(u,p+0xb8,1)[0])])
    return result,digest([count,*[x for row in result for x in row]])

def generate(a):
    from original_resource_type_inputs import ResourceTypeInputOracle
    from original_overlay_map_resources import OverlayMapResourceOracle
    t=ResourceTypeInputOracle(a.exe);o=OverlayMapResourceOracle(a.exe);cmds=[];expected=[];labels=[]
    for label,v in commands(a,o.frames):
        command='J '+' '.join(map(str,v));parse(command);count=v[0];at=1+count*5
        rows=[v[i:i+5] for i in range(1,at,5)];tail=v[at:]
        # Original phases are separately audited. Only selected initialization
        # results transfer; this is not execution of an original startup parent.
        seed=tail[1+tail[1]+1+9]
        records,fingerprint=initialize(t,rows,seed)
        tail=[len(records),*[x for row in records for x in row],*tail[1:]]
        cmds.append(command);labels.append(label);expected.append([fingerprint,*o.run('N',tail)])
    return cmds,expected,labels,{'groups':dict.fromkeys(labels,1),
      'resource_type_audits':t.audit_calls,'resource_type_entries':t.roots,
      'resource_type_selected_stores':t.stores,'resource_type_supplied_calls':t.services,
      'overlay_audits':o.audit_calls,'overlay_entries':o.roots,
      'overlay_selected_stores':o.stores,'overlay_supplied_calls':o.service_calls,
      'actual_constructors':o.constructed,'actual_resource_entries':o.resource_entries,
      'actual_classifier_entries':o.classifier_entries,'missing_resource_logger_services':o.missing_logs,
      'initialized_selected_records_transferred_between_separately_audited_guests':True,
      'original_startup_parent_executed':False,'recalculation_passability_remain_diagnostic':True}

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-map-resource-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/resource-map-inputs-v1')
    p.add_argument('--fixture',type=Path,default=ROOT/'private/map-depth-1006/overlay-reader-owned-v1.json')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);cmds,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh resource map destination invalid or exists')
        now=time.monotonic();cmds,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,cmds);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Resource map input result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Resource map inputs run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(cmds),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':cmds,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(cmds):,} initialized resource/overlay scenarios: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
