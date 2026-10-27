#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Fresh exact-base resource construction, numeric-key list and INI evidence."""
import argparse,json,random,struct,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_resource_type_inputs import verify
SOURCES=('src/assets/ResourceTypeInputs.hpp','src/assets/ResourceTypeInputs.cpp',
 'src/assets/MapOverlay.hpp','src/assets/MapCellChildren.hpp','src/assets/MapCellInputs.hpp','src/assets/OverlayTypeInputs.hpp',
 'tests/resource_type_input_vectors.cpp','tests/original_resource_type_inputs.py','tests/compare_resource_type_inputs.py',
 'tools/verify_resource_type_inputs.py','tests/original_land_characteristics.py','tools/prepare_overlay_loading_fixture.py',
 'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/original_foot_lit.py',
 'tests/presentation_profiles.py','tests/compare_original.py','tests/presentation_evidence.py','tools/verify_terrain_visibility.py')
def parse(command):
    c=command.split();assert c and c[0] in ('I','C','L');op=c[0];v=c[1:];assert v
    assert 0<=int(v[0])<=0xffffffff
    def profile(at):
        assert at+14<=len(v);assert all(0<=int(n)<=0xffffffff for n in v[at:at+13])
        assert int(v[at+1])<256 and len(v[at+13])<128;return at+14
    if op=='I':assert profile(1)==len(v)
    else:
        at=1
        for _ in range(2):
            assert at+5<=len(v);capacity,owns,growth,success,count=map(int,v[at:at+5]);at+=5
            assert 0<=count<=capacity<=512 and 0<=owns<=255 and -1<=growth<=512 and 0<=success<=0xffffffff
            assert at+count<=len(v) and all(0<=int(n)<8 for n in v[at:at+count]);at+=count
        if op=='C':assert at+2==len(v) and 0<=int(v[at])<8 and len(v[at+1])<24
        else:
            count=int(v[at]);at+=1;assert -1<=count<=400
            for _ in range(max(0,count)):
                assert at+4<=len(v) and len(v[at])<64 and 0<=int(v[at+1])<=0x7fffffff and 0<=int(v[at+2])<=0xffffffff and len(v[at+3])<24
                at=profile(at+4)
            assert at==len(v)
    return op,v
def identities(a):return {'inspection':verify(a.exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},'rules_sha256':hash_file(a.rules)}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Resource type inputs engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Resource type inputs identity differs')
    if not(e['commands'] and len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Resource type inputs counts differ')
    for command in e['commands']:
        try:parse(command)
        except (AssertionError,ValueError,IndexError):raise ValueError('Malformed resource type command') from None
def cases(a):
    from prepare_overlay_loading_fixture import parse_ini
    rng=random.Random(0x52455354);result=[]
    def add(label,op,v):
        cmd=op+' '+' '.join(map(str,v));parse(cmd);result.append((label,cmd))
    def registry(n,shift=0):
        count=(n+shift)%5;cap=count if n%2 else count+2
        return [cap,[0,1,255][(n+shift)%3],[-1,0,1,4][(n//3+shift)%4],
          [0,1,2,255,256,257][(n//12+shift)%6],count,*[i%3 for i in range(count)]]
    def conf(base=1,mask=255,image=1,debris='-',length=0,reals=None):
        if reals is None:reals=[0,0x3fb99999,0,0x3ff00000]
        return [base,mask,17,23,25,0,3,image&0xffffffff,*reals,length&0xffffffff,debris]
    for n in range(384):add('constructor_count_before_append_two_registries_growth_low_byte_and_untouched_timer_words','C',
        [rng.getrandbits(32),*registry(n),*registry(n,1),n%8,'Resource'+str(n)])
    double_bits=[0,0x8000000000000000,1,0x8000000000000001,0x3fb999999999999a,0x3ff0000000000000,
      0x7fefffffffffffff,0xffefffffffffffff,0x7ff0000000000000,0xfff0000000000000,
      0x7ff8000000001234,0xfff8000000005678,0x7ff0000000000001,0xfff0000000000011]
    images=[0xffffffff,0xfffffffe,0,1,2,3,4,5,2147483647,2147483648]
    for n in range(768):
        bits=[double_bits[(n//10)%len(double_bits)],double_bits[(n//140)%len(double_bits)]]
        reals=[word for b in bits for word in (b&0xffffffff,b>>32)]
        p=conf(base=[0,1,2,255,256,257][n%6],mask=255 if n%3 else rng.randrange(256),image=images[n%len(images)],
          debris=['-','A,B,MISSING,C','MISSING',',A,,B,'][n%4],length=[0,1,0xffffffff][(n//4)%3],reals=reals)
        p[2:7]=[rng.getrandbits(32) for _ in range(5)]
        add('ini_full_order_double_stores_nan_payloads_image_switch_missing_preservation_and_debris','I',[rng.getrandbits(32),*p])
    for image in images:
        add('explicit_successful_image_switch_all_signed_edges','I',[7,*conf(image=image)])
    for n in range(96):
        count=n%8;entries=[]
        for i in range(count):
            index=[0,1,7,0,30][i%5];value=['New','OTHER','New','Ignored','Last'][i%5]
            entries.extend([str(index),index,[0,1,0xffffffff,3][(i+n)%4],value,
              *conf(base=[0,1,256,257][(n+i)%4],image=(n+i)%6-1,debris='A,MISSING,B',length=(n+i)%2)])
        add('numeric_key_existing_identity_new_slots_length_signed_gate_and_ignored_ini_failure','L',
          [rng.getrandbits(32),*registry(n),*registry(n,1),count,*entries])
    for count in (-1,0):add('nonpositive_list_count_still_true','L',[0,0,1,4,1,0,0,1,4,1,0,count])
    rules=parse_ini(a.rules.read_bytes());entries=[]
    for key,name in rules['Tiberiums'].items():
        p=conf(mask=0);ints=['Spread','Growth','Value','Power','Color','Image']
        for i,k in enumerate(ints):
            if rules.has_option(name,k) and k!='Color':p[1]|=1<<i;p[2+i]=int(rules.get(name,k))&0xffffffff
        for i,k in enumerate(('SpreadPercentage','GrowthPercentage')):
            if rules.has_option(name,k):
                b=struct.unpack('<Q',struct.pack('<d',float(rules.get(name,k))))[0];p[1]|=1<<(6+i);p[8+i*2:10+i*2]=[b&0xffffffff,b>>32]
        # Named-color resolution is supplied; a distinct host result exercises
        # Color without claiming original color registry initialization.
        if rules.has_option(name,'Color'):p[1]|=1<<4;p[6]=len(entries)+5
        debris=rules.get(name,'Debris',fallback='').strip();p[12:]=[len(debris),debris or '-']
        entries.extend([key,int(key),len(name.strip()),name.strip(),*p])
    add('owned_rules_four_resource_entries_actual_constructor_ini_and_image_association','L',
        [0,0,1,8,1,0,0,1,8,1,0,len(rules['Tiberiums']),*entries])
    return result
def generate(a):
    from original_resource_type_inputs import ResourceTypeInputOracle
    o=ResourceTypeInputOracle(a.exe);commands=[];expected=[];labels=[];groups={}
    for label,cmd in cases(a):
        commands.append(cmd);expected.append(o.run(*parse(cmd)));labels.append(label);groups[label]=groups.get(label,0)+1
    return commands,expected,labels,{'groups':groups,'audited_roots':o.audit_calls,'actual_root_entries':o.roots,
      'image_branch_entries':o.image_branches,'ordered_selected_stores':o.stores,'supplied_service_calls':o.services,
      'base_parser_color_token_animation_vector_heap_growth_services_supplied':True,
      'double_return_direct_register_injection':True,'signaling_nan_hardware_semantics_verified':False,
      'owned_resource_entries':4}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/resource-type-input-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/map-depth-1006/resource-inputs-v1')
    p.add_argument('--rules',type=Path,default=ROOT/'private/map-depth-1006/resident-fixture-v1/rules.ini');p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();start=time.monotonic();current=identities(a);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source);e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay.json',a.exe);check_replay_destination(report,source,receipt);commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        dest=private_path(a.output,a.exe)
        if a.report or (dest/'expected.json').exists() or (dest/'report.json').exists():raise ValueError('Fresh resource input destination invalid or exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a);generation=time.monotonic()-now;report=dest/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if len(actual)!=len(expected):raise AssertionError('Resource type inputs result counts differ')
    for i,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{i} {labels[i]}: {x} != {y}')
    if identities(a)!=current or hash_file(a.native)!=runner:raise ValueError('Resource type inputs run changed')
    result={**metadata,'identities':current,'native_sha256':runner,'cases':len(commands),'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
      'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original','original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
      'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=dest/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 resource type input results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
