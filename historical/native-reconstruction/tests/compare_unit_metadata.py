#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Original GetBool, scoped type field loaders/defaults and supplied HTNK inputs."""
import argparse,configparser,itertools,json,time
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_metadata import verify,FIELDS
SOURCES=('tests/compare_unit_metadata.py','tests/original_unit_metadata.py',
         'tests/unit_metadata_vectors.cpp','tools/verify_unit_metadata.py',
         'tests/original_presentation.py','tests/presentation_profiles.py',
         'tests/compare_terrain_visibility.py','tests/compare_original.py','tests/presentation_evidence.py',
         'tools/verify_terrain_visibility.py','src/assets/Formats.cpp','src/assets/Formats.hpp',
         'src/assets/Bytes.hpp','src/assets/UnitTypeMetadata.cpp','src/assets/UnitTypeMetadata.hpp')
def identities(exe,assets):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
            'assets':{str((assets/name).resolve()):hash_file(assets/name) for name in ('rules.ini','art.ini')}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Metadata engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Metadata source/asset/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Metadata counts differ')
    if any(c.split()[0] not in ('B','M','C','O') for c in e['commands']):raise ValueError('Unknown metadata runner command')
def owned_values(assets):
    configs=[]
    for name in ('rules.ini','art.ini'):
        p=configparser.ConfigParser(interpolation=None,strict=False,allow_no_value=True,inline_comment_prefixes=(';',))
        p.read_string((assets/name).read_text(encoding='latin1'));configs.append(p)
    return [(configs[1] if n==1 else configs[0]).get('HTNK',row[1],fallback='').encode('latin1')
            for n,row in enumerate(FIELDS)]
def generate(exe,assets):
    from original_unit_metadata import UnitMetadataOracle
    stock=owned_values(assets)
    oracle=UnitMetadataOracle(exe);commands=[];expected=[];labels=[];groups={}
    def save(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    def boolean(group,mode,fallback,value):
        save(group,['B',mode,fallback,value.hex() or '-'],oracle.boolean(mode,fallback,value))
    fallbacks=[-2147483648,-257,-1,0,1,2,127,128,255,256,257,2147483647]
    for first,fallback in itertools.product(range(256),fallbacks):
        value=bytes([first])+b'ignored tail' if first else b''
        boolean('every_first_byte_locale_zero_and_low_fallback_byte',5,fallback,value)
    for value,fallback in itertools.product(
            [b'Yes',b'yAnything',b'Totally',b'1suffix',b'False',b'nAnything',b'0suffix',
             b'2',b'?',b' Yes',b'\ttrue',b''],range(256)):
        boolean('prefix_only_no_value_trimming_and_every_fallback',5,fallback,value)
    for mode,fallback in itertools.product([0,1,2,3,4,6,7],range(256)):
        boolean('missing_null_section_key_record_and_string',mode,fallback,b'yes')
    for field,mode,fallback,value in itertools.product(range(5),[1,5],fallbacks,
            [b'',b'yes',b'Yarbitrary',b't',b'1suffix',b'false',b'Nonsense',b'0',b'2',b'?']):
        save('selected_original_type_read_call_and_byte_store',
             ['M',field,mode,fallback,value.hex() or '-'],oracle.metadata(field,mode,fallback,value))
    save('five_scoped_constructor_zero_stores',['C'],oracle.defaults())
    results=[]
    for field,value in enumerate(stock):
        results.append(oracle.metadata(field,5,0,value)[field])
    save('owned_HTNK_decoded_fields_not_full_text_parser',
         ['O',str((assets/'rules.ini').resolve()),str((assets/'art.ini').resolve())],results)
    return commands,expected,labels,groups,oracle.audit_calls,oracle.audit_blocks
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--asset-dir',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-metadata-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/metadata')
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
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh metadata evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls,blocks=generate(a.exe,a.asset_dir);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'audited_scoped_blocks':blocks,
                  'scope':current['inspection']['scope']+' Owned rules/art are previously selected private exports; fixture text decoding is supplied. Original byte/stack/arena writes audited, including exact selected type stores. No full constructor/INI parser/model or actor parity.'}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Metadata result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe,a.asset_dir)!=current or hash_file(a.native)!=runner:raise ValueError('Metadata run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 GetBool/type metadata results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
