#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base overlay registry/default/INI projection evidence."""
import argparse,json,random,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_overlay_type_inputs import verify
SOURCES=('src/assets/OverlayTypeInputs.hpp','src/assets/OverlayTypeInputs.cpp',
 'tests/overlay_type_input_vectors.cpp','tests/compare_overlay_type_inputs.py',
 'tests/original_overlay_type_inputs.py','tools/verify_overlay_type_inputs.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py',
 'tools/verify_terrain_visibility.py')
def parse(command):
    tokens=command.split();assert tokens and tokens[0] in ('C','I','L')
    op=tokens[0];v=tokens[1:];seed=int(v[0]);assert 0<=seed<=0xffffffff
    if op=='I':
        assert len(v)==26
        for i,n in enumerate(v):
            if i!=23: assert 0<=int(n)<=0xffffffff
        assert 0<=int(v[2])<1<<17 and len(v[23])<128
    else:
        capacity,owns,growth,success,fail,count=map(int,v[1:7])
        assert 0<=count<=capacity<=512 and 0<=owns<=255 and -1<=growth<=512
        assert success in (0,1,2,255,256,257) and -1<=fail<=400
        assert all(0<=int(n)<8 for n in v[7:7+count])
        at=7+count
        if op=='C':assert len(v)==at+2 and 0<=int(v[at])<8 and len(v[at+1])<32
        else:
            count=int(v[at]);assert -1<=count<=400 and len(v)==at+1+2*max(0,count)
            for i in range(at+1,len(v),2):assert 0<=int(v[i])<=0xffffffff and len(v[i+1])<32
    return op,v
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'rules_sha256':hash_file(a.rules)}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Overlay type inputs engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Overlay type inputs identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Overlay type inputs counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed map overlay command') from None
def generate(a):
    from original_overlay_type_inputs import OverlayTypeInputOracle
    import configparser
    o=OverlayTypeInputOracle(a.exe);rng=random.Random(0x4f545950);commands=[];expected=[];labels=[];groups={}
    def save(label,op,v):
        cmd=op+' '+' '.join(map(str,v));parse(cmd)
        commands.append(cmd);expected.append(o.run(*parse(cmd)));labels.append(label);groups[label]=groups.get(label,0)+1
    for n in range(384):
        count=n%6;capacity=count if n%2 else count+2
        handles=[rng.randrange(4) for _ in range(count)]
        save('constructor_defaults_append_first_equal_pointer_and_growth_failure','C',
          [rng.getrandbits(32),capacity,[0,1,2,255][n%4],[-1,0,1,4][(n//4)%4],
           [0,1,2,255,256,257][(n//16)%6],-1,count,*handles,n%8,'T'+str(n)])
    for n in range(768):
        mask=rng.randrange(1<<17) if n%3 else (1<<17)-1
        integers=[rng.getrandbits(32) for _ in range(3)]
        flags=[rng.choice([0,1,2,255,256,257,0xffffffff]) for _ in range(14)]
        integers[0]=[0,1,5,0xffffffff][n%4]
        flags[1]=[0,2,255,256][(n//4)%4];flags[6]=[0,2,255,256][(n//16)%4]
        length=[0,1,2,256][n%4];name=['-','Anim','Other','MISSING'][n%4]
        save('complete_ini_order_preserved_defaults_low_bytes_resource_land_and_image_animation_branches','I',
          [rng.getrandbits(32),[0,1,2,255,256,257][n%6],mask,[0,1,2,255,256][n%5],n%256,
           *integers,*flags,length,name,rng.getrandbits(32),rng.getrandbits(32)])
    for n in range(192):
        count=n%5;capacity=count+(2 if n%2 else 0);handles=[i%3 for i in range(count)]
        entries=[rng.choice(['Existing0','existing0','EXISTING1','Alpha','ALPHA','Beta','none','<NoNe>','-',
             '0123456789012345678901234567890']) for _ in range(n%16)]
        length=[(0 if name=='-' else len(name)) for name in entries]
        save('list_enumeration_case_insensitive_resolver_duplicates_none_and_allocation_failures','L',
          [rng.getrandbits(32),capacity,n%2,[0,1,4][n%3],[0,1,256,257][n%4],[-1,0,3][n%3],count,*handles,
           len(entries),*[v for pair in zip(length,entries) for v in pair]])
    for count in (-1,0,1):
        save('list_result_depends_on_entry_count_even_for_empty_values','L',
          [0,0,0,0,0,-1,0,count,*([0,'-'] if count==1 else [])])
    save('list_nonzero_read_with_empty_buffer_still_resolves_empty_identifier','L',
      [0,2,1,1,1,-1,0,2,1,'-',0,'Ignored'])
    ini=configparser.ConfigParser(interpolation=None,strict=False,allow_no_value=True,inline_comment_prefixes=(';',))
    ini.read_string(a.rules.read_text(encoding='latin1'))
    entries=list(ini['OverlayTypes'].items())
    save('owned_rules_decoded_list_order_numeric_keys_not_used_as_indices','L',
      [0,len(entries),1,1,1,-1,0,len(entries),*[v for key,name in entries for v in (len(name.strip()),name.strip() or '-')]])
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'ordered_selected_stores':o.stores,'supplied_service_calls':o.services,'owned_list_entries':len(entries),
      'base_constructor_ini_parser_crt_file_heap_services_supplied':True}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/overlay-type-input-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/overlay-inputs-v1')
    p.add_argument('--rules',type=Path,default=ROOT/'private/map-depth-1006/resident-fixture-v1/rules.ini');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh overlay input destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Overlay type inputs result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Overlay type inputs run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 overlay type input results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
