#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base Image/string/default/section associations on decoded INI fixtures."""
import argparse,configparser,itertools,json,random,time,subprocess
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_model_inputs import verify
from compare_unit_metadata import SOURCES as PARENT_SOURCES
SOURCES=tuple(dict.fromkeys((*PARENT_SOURCES,'tests/compare_unit_model_inputs.py',
    'tests/original_unit_model_inputs.py','tests/unit_model_input_vectors.cpp',
    'tools/verify_unit_model_inputs.py','src/assets/UnitModelInputs.cpp','src/assets/UnitModelInputs.hpp',
    'tests/original_foot_lit.py','src/assets/Formats.cpp','src/assets/Formats.hpp',
    'src/assets/GameAssets.cpp','src/assets/GameAssets.hpp')))
def identities(exe,assets):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
            'assets':{str((assets/p).resolve()):hash_file(assets/p) for p in ('rules.ini','art.ini')}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Model input engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Model input source/asset/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Model input counts differ')
    if any(c.split()[0] not in ('S','M','C','O') for c in e['commands']):raise ValueError('Unknown model input runner command')
def generate(exe,assets):
    from original_unit_model_inputs import UnitModelInputOracle
    o=UnitModelInputOracle(exe);rng=random.Random(0x52413249)
    commands=[];expected=[];labels=[];groups={}
    def save(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)));labels.append(group)
        groups[group]=groups.get(group,0)+1
    def string(group,mode,capacity,value,fallback):
        save(group,['S',mode,capacity,value.hex() or '-', '~' if fallback is None else fallback.hex() or '-'],o.string(mode,capacity,value,fallback))
    for first,capacity in itertools.product(range(256),(2,3,4,25,64)):
        b=bytes([first]) if first else b''
        string('every_byte_and_bounded_copy_trim_padding',5,capacity,b+b'A  '+b,b'fallback')
    for leading,trailing in itertools.product(range(31),repeat=2):
        string('live_old_first_nonblank_pointer_in_trailing_trim',5,25,b' '*leading+b'A'+b' '*trailing,None)
    for mode,cap,fallback in itertools.product(range(9),(-1,0,1,2,3,24,25,64),(None,b'',b'old model',b' \x01FB\x20 ')):
        string('missing_records_null_names_output_short_or_negative_capacity_fallback',mode,cap,b'changed',fallback)
    for n in range(512):
        value=bytes(rng.randrange(1,256) for _ in range(n%128))
        string('arbitrary_decoded_bytes_truncation_unsigned_controls_and_padding',5,n%65,value,b'FB')
    for n in range(256):
        raw=bytes(rng.randrange(256) for _ in range(25))
        save('scoped_fixed_25_byte_constructor_copy_and_zero_count_offset',['C',raw.hex()],o.constructor(raw))
    initial=b'HTNK\0'+b'\0'*20
    edges=[-2147483648,-65536,-1,0,1,255,65535,2147483647]
    for n in range(1024):
        image=(rng.choice([b'OLD',b'ALIAS',b' \x01OLD ',b''])+b'\0').ljust(25,b'\x99')
        count,offset=(rng.choice(edges) for _ in range(2));values=[rng.choice(edges) for _ in range(2)]
        mode=n%6;mask=n%4;value=rng.choice([b'HTNK',b'NEW',b'  A   ',b'',b'X'*40,b' \x80Z '])
        save('actual_Image_read_scoped_integer_fields_and_actual_missing_fallback',
             ['M',image.hex(),count,offset,mask,*values,mode,value.hex() or '-'],
             o.metadata(image,count,offset,mask,values,mode,value))
    parsers=[]
    for name in ('rules.ini','art.ini'):
        p=configparser.ConfigParser(interpolation=None,strict=False,allow_no_value=True,inline_comment_prefixes=(';',));p.read_string((assets/name).read_text(encoding='latin1'));parsers.append(p)
    if any(p.get('HTNK',key,fallback=None) is not None for p,key in ((parsers[0],'Image'),(parsers[0],'TurretCount'),(parsers[1],'TurretOffset'))):
        raise ValueError('Owned stock absence/default fixture changed; inspect new entries')
    result=o.metadata(initial,0,0,0,[0,0],1,b'')[-4:]
    assert result==['state',initial.hex(),0,0]
    save('owned_HTNK_decoded_absences_with_actual_GetInt_fallback_and_native_reader',
         ['O',str((assets/'rules.ini').resolve()),str((assets/'art.ini').resolve())],result)
    return commands,expected,labels,{'groups':groups,'audited_callable_roots':o.audit_calls,
        'audited_scoped_blocks':o.audit_blocks,'actual_ReadString_calls':o.actual_strings,
        'actual_missing_GetInt_calls':o.actual_missing_integers,'supplied_present_integer_calls':o.supplied_integers,
        'guarded_type_stores':o.type_writes,'owned_HTNK_image':'HTNK','owned_HTNK_turret_count':0,'owned_HTNK_turret_offset':0}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--asset-dir',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-model-input-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/model-inputs-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a.exe,a.asset_dir);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh model input evidence exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a.exe,a.asset_dir);generation=time.monotonic()-now
        metadata['scope']=current['inspection']['scope'];report=out/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:raise AssertionError(f'Native runner failed: {error.stderr}') from error
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Model input result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe,a.asset_dir)!=current or hash_file(a.native)!=runner:raise ValueError('Model input run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 model input results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
