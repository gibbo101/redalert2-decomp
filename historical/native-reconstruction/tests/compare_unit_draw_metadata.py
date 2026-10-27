#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Selected base depth/split metadata with scoped original loaders/defaults."""
import argparse,configparser,itertools,json,random,time,subprocess
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from compare_unit_metadata import SOURCES as PARENT_SOURCES
from verify_unit_draw_metadata import verify,FIELDS
SOURCES=tuple(dict.fromkeys((*PARENT_SOURCES,'tests/compare_unit_draw_metadata.py',
    'tests/original_unit_draw_metadata.py','tests/unit_draw_metadata_vectors.cpp',
    'tools/verify_unit_draw_metadata.py','src/assets/UnitDrawMetadata.cpp','src/assets/UnitDrawMetadata.hpp',
    'tests/original_foot_lit.py')))
def identities(exe,rules):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES},
            'rules':{str(rules.resolve()):hash_file(rules)}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Draw metadata engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Draw metadata source/asset/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Draw metadata counts differ')
    if any(c.split()[0] not in ('M','C','O') for c in e['commands']):raise ValueError('Unknown draw metadata runner command')
def owned_values(rules):
    p=configparser.ConfigParser(interpolation=None,strict=False,allow_no_value=True,inline_comment_prefixes=(';',))
    p.read_string(rules.read_text(encoding='latin1'))
    return [p.get('HTNK',row[1],fallback=None) for row in FIELDS]
def generate(exe,rules):
    from original_unit_draw_metadata import UnitDrawMetadataOracle
    o=UnitDrawMetadataOracle(exe);rng=random.Random(0x52413243)
    commands=[];expected=[];labels=[];groups={}
    def save(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)))
        labels.append(group);groups[group]=groups.get(group,0)+1
    def case(group,defaults,mask,values,mode,text,side):
        save(group,['M',*defaults,mask,*values,mode,text.hex() or '-',side],o.metadata(defaults,mask,values,mode,text,side))
    save('scoped_register_setup_and_five_constructor_defaults',['C'],o.defaults_case())
    edges=[-2147483648,-2147483647,-65536,-1,0,1,255,65535,2147483647]
    for n in range(1024):
        defaults=[*[rng.choice(edges) for _ in range(4)],rng.choice(edges)]
        case('integer_read_fallback_key_order_exact_word_stores_and_actual_boolean',defaults,n%16,
             [rng.choice(edges) for _ in range(4)],n%6,rng.choice([b'yes',b'No',b'Yarbitrary',b'false',b'?',b'']),n%2)
    for first,fallback in itertools.product(range(256),[0,1,127,255]):
        case('every_boolean_first_byte_inside_actual_type_loader',[10,5,10,0,fallback],0,[0]*4,5,
             bytes([first])+b'ignored' if first else b'',first%2)
    for mode,fallback in itertools.product(range(5),range(256)):
        case('missing_section_key_record_or_text_preserves_fallback_byte',[10,5,10,0,fallback],0,[0]*4,mode,b'yes',fallback%2)
    stock=owned_values(rules);defaults=[10,5,10,0,0]
    values=[int(v) if v is not None else d for v,d in zip(stock[:4],defaults[:4])]
    mask=sum(1<<i for i,v in enumerate(stock[:4]) if v is not None)
    result=o.metadata(defaults,mask,values,5 if stock[4] is not None else 1,(stock[4] or '').encode('latin1'),logging=False)
    if result!=['fields',10,8,13,0,1]:raise AssertionError('Selected owned HTNK draw metadata changed')
    save('owned_HTNK_decoded_field_inputs_not_original_text_or_integer_parsing',['O',str(rules.resolve())],result)
    return commands,expected,labels,{'groups':groups,'audited_callable_roots':o.audit_calls,
        'audited_scoped_blocks':o.audit_blocks,'new_scoped_blocks':o.selected_blocks,
        'guarded_integer_service_calls':o.integer_calls,'unrelated_original_only_byte_stores':o.side_writes,
        'owned_HTNK_fields':dict(zip((r[1] for r in FIELDS),result[1:]))}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--rules',type=Path,default=ROOT/'private/migration/supplied-ra2-1006/scenery/assets/rules.ini')
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-draw-metadata-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/draw-metadata-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a.exe,a.rules);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh draw metadata evidence exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a.exe,a.rules);generation=time.monotonic()-now
        metadata['scope']=current['inspection']['scope'];report=out/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:raise AssertionError(f'Native runner failed: {error.stderr}') from error
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Draw metadata result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe,a.rules)!=current or hash_file(a.native)!=runner:raise ValueError('Draw metadata run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 draw metadata results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
