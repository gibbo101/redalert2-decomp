#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete base ordinary model-loading protocol, with supplied resource services."""
import argparse,itertools,json,random,time,subprocess
from pathlib import Path
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
from verify_unit_models import verify
SOURCES=('tests/compare_unit_models.py','tests/original_unit_models.py',
         'tests/unit_model_vectors.cpp','tools/verify_unit_models.py',
         'src/assets/UnitModels.cpp','src/assets/UnitModels.hpp',
         'tests/original_presentation.py','tests/original_foot_lit.py',
         'tests/presentation_evidence.py','tests/presentation_profiles.py',
         'tests/compare_original.py','tests/compare_terrain_visibility.py')
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'inspection':verify(exe.read_bytes()),'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':raise ValueError('Unit model engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Unit model source/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Unit model counts differ')
    if any(c.split()[0]!='M' for c in e['commands']):raise ValueError('Unknown unit model runner command')
def generate(exe):
    from original_unit_models import UnitModelOracle
    o=UnitModelOracle(exe);rng=random.Random(0x5241324d)
    commands=[];expected=[];labels=[];groups={}
    def case(group,image='HTNK',old=0,available=(1,1,1),allocate=63,errors=(0,)*6,dims=((10,20,30),),maximum=99,seed=15):
        # A valid HVA following a null VXL would call a descriptor through null.
        # Such malformed allocation/parser combinations are outside this domain.
        for i,a in enumerate(available):
            if a&255 and not allocate&(1<<(2*i)) and allocate&(1<<(2*i+1)) and errors[2*i+1]&255==0:
                raise ValueError('Fixture would request a null voxel descriptor')
        tokens=['M',image,old,*available,allocate,*errors,len(dims),*[x for row in dims for x in row],maximum,seed]
        commands.append(' '.join(map(str,tokens)));labels.append(group)
        expected.append(list(map(str,o.run(image,old,available,allocate,errors,dims,maximum,seed))))
        groups[group]=groups.get(group,0)+1
    for old,availability in itertools.product(range(64),range(8)):
        case('all_old_part_presence_and_optional_file_availability',old=old,
             available=tuple((1 if availability&(1<<i) else 0) for i in range(3)),seed=old)
    for allocate in range(64):
        for old in (0,63):
            errors=[0]*6
            for i in range(3):
                if not allocate&(1<<(i*2)):errors[i*2+1]=255
            case('allocation_failures_keep_later_load_order_and_barrel',old=old,allocate=allocate,errors=errors)
    for mask in range(64):
        for old in (0,63):
            case('every_parser_error_combination_and_existing_parts',old=old,
                 errors=tuple(127 if mask&(1<<i) else 0 for i in range(6)))
    for availability in itertools.product((0,1,256,257,2147483648,2147483903,4294967295),repeat=3):
        case('availability_uses_low_byte_and_preserves_optional_records',old=63,available=availability)
    for axis,value in itertools.product(range(3),range(256)):
        d=[0,0,0];d[axis]=value
        case('every_dimension_byte_minimum_eight_and_repeated_equal_queries',dims=(tuple(d),))
    for n in range(512):
        dims=tuple(tuple(rng.randrange(256) for _ in range(3)) for _ in range(1+n%6))
        case('multi_section_maxima_cache_order_words_and_flags',image=rng.choice(['HTNK','rhino','X','A'*24]),
             old=rng.randrange(64),available=tuple(rng.choice((1,127,255)) for _ in range(3)),
             dims=dims,maximum=rng.choice([-2147483648,-1,0,2147483647]),seed=rng.getrandbits(32))
    return commands,expected,labels,{'groups':groups,'audited_callable_roots':o.audit_calls,
        'actual_section_getter_calls':o.section_calls,'actual_kind_calls':o.kinds,'actual_multiple_turret_calls':o.multiples,
        'ordered_type_stores':o.store_count,'supplied_service_calls':o.service_calls,'guarded_host_stack_writes':o.service_writes}
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/unit-model-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/unit-draw-1006/models-v1')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path);a=p.parse_args()
    start=time.monotonic();current=identities(a.exe);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh model evidence exists')
        now=time.monotonic();commands,expected,labels,metadata=generate(a.exe);generation=time.monotonic()-now
        metadata['scope']=current['inspection']['scope'];report=out/'report.json'
    now=time.monotonic()
    try:actual=native(a.native,commands)
    except subprocess.CalledProcessError as error:raise AssertionError(f'Native runner failed: {error.stderr}') from error
    elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(labels)):raise AssertionError('Unit model result counts differ')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:raise AssertionError(f'{n} {labels[n]} {commands[n]}: native {x}, original {y}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Unit model run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
            'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
            'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
            'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
                     'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 model protocol results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
