#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Differential patched redraw requests and bounded dirty-region queue decisions."""
import argparse
import itertools
import json
from pathlib import Path
import random
import sys
import time
from compare_terrain_visibility import ROOT,native
from compare_original import PATCHED_EXPECTED,write_report
from presentation_evidence import private_path,hash_file,validate_receipt,check_replay_destination
sys.path.insert(0,str(ROOT/'tools'))
from verify_redraw import verify
SOURCES=('tests/compare_redraw.py','tests/original_redraw.py','tests/redraw_vectors.cpp',
         'tools/verify_redraw.py','src/render/Redraw.hpp','src/render/Redraw.cpp',
         'src/render/TerrainVisibility.hpp','src/render/TerrainVisibility.cpp','src/render/Composition.hpp',
         'tests/compare_terrain_visibility.py','tests/original_presentation.py','tests/compare_original.py',
         'tests/presentation_profiles.py','tests/presentation_evidence.py')
def identities(exe):
    return {'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','inspection':verify(exe.read_bytes()),
            'sources':{p:hash_file(ROOT/p) for p in SOURCES}}
def validate(e,r,f,current):
    validate_receipt(e,r,f)
    if e.get('executable_sha256')!=PATCHED_EXPECTED or e.get('profile')!='supplied-ra2-1006':
        raise ValueError('Redraw engine/profile differs')
    if e['evidence'].get('identities')!=current:raise ValueError('Redraw source/inspection identity differs')
    if not(len(e['commands'])==len(e['expected'])==len(e['labels'])):raise ValueError('Redraw vector counts differ')
def generate(exe):
    from original_redraw import RedrawOracle
    o=RedrawOracle(exe);rng=random.Random(0x52413235);commands=[];expected=[];labels=[];groups={}
    def add(group,tokens,result):
        commands.append(' '.join(map(str,tokens)));expected.append(list(map(str,result)));labels.append(group)
        groups[group]=groups.get(group,0)+1
    add('initial_queue_fields',['I'],o.initial())
    for counter,mode,old,present in itertools.product(range(256),[-2147483648,-1,0,1,2,256,2147483647],[0,2],[0,1]):
        args=[old,counter,255 if counter&1 else 0,present,91,mode]
        add('all_counter_bytes_and_map_modes',['M',*args],o.request('M',*args))
    for needs,present,old,counter in itertools.product(range(256),[0,1],[-1,0,2],[0,255]):
        args=[old,counter,255,present,needs,2147483647]
        add('all_redraw_bytes_and_idempotence',['O',*args],o.request('O',*args))
    edges=[-2147483648,-2147483647,-65536,-1,0,1,2,10,65536,2147483646,2147483647]
    for i in range(2048):
        first=[rng.choice(edges) for _ in range(4)];second=[rng.choice(edges) for _ in range(4)]
        add('union_signed_wrap_and_invalid_extents',['U',*first,*second],o.union(first,second))
    def queue(group,count,slots,incoming,growth=10,owns=True,success=True):
        add(group,['Q',count,len(slots),growth,int(owns),int(success),*[v for s in slots for v in s],*incoming],
            o.queue(count,slots,growth,owns,success,incoming))
    rectangles=[(0,0,10,10),(1,1,2,2),(-1,-1,12,12),(2,2,10,10),(-2,-2,10,10),
                (10,0,10,10),(0,10,10,10),(5,0,10,10),(0,5,10,10),(9,9,10,10),
                (-5,0,10,10),(0,-5,10,10),(0,0,0,10),(0,0,10,0),(0,0,-1,10),
                (0,0,10,-1),(2147483640,0,10,10),(-2147483648,0,10,10)]
    for first,second,f1,f2 in itertools.product(rectangles,rectangles,[0,1,255],[0,1,255]):
        queue('containment_flags_partial_overlap_touching_and_empty',1,[(*first,f1),(77,78,79,80,81)],(*second,f2))
    for cap,growth,owns,success,flag in itertools.product(range(9),[-1,0,1,10],[0,1],[0,1],[0,1,255]):
        slots=[(i*30,0,10,10,i%2) for i in range(cap)]
        queue('capacity_ownership_growth_and_failure',cap,slots,(1000,1000,10,10,flag),growth,owns,success)
    for i in range(1536):
        count=rng.randrange(17);slots=[]
        for n in range(count+rng.randrange(4)):
            rect=[rng.randrange(-30,31),rng.randrange(-30,31),rng.randrange(-2,33),rng.randrange(-2,33)]
            if i%3==0:rect=[rng.choice(edges) for _ in range(4)]
            slots.append((*rect,rng.choice([0,1,255])))
        if count and i%4==0:incoming=slots[rng.randrange(count)]
        else:incoming=(*[rng.choice(edges) for _ in range(4)],rng.choice([0,1,255]))
        queue('ordered_removal_tail_best_merge_and_wrap',count,slots,incoming)
    # Multiple deletions followed by best-area merging; first equal-area candidate wins.
    for offset,flag in itertools.product(range(-16,17),[0,1,255]):
        slots=[(0,0,10,10,0),(2,2,2,2,flag),(5,0,10,10,0),(3,3,1,1,flag),(70,70,10,10,255),(81,82,83,84,85)]
        queue('multiple_delete_stable_ties_and_uncleared_tail',5,slots,(offset,0,14,12,flag))
    return commands,expected,labels,groups,o.audit_calls
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--exe',type=Path,required=True)
    p.add_argument('--native',type=Path,default=ROOT/'build/native/redraw-vectors')
    p.add_argument('--output',type=Path,default=ROOT/'private/traversal-1006/redraw')
    p.add_argument('--expectations',type=Path);p.add_argument('--report',type=Path)
    a=p.parse_args();start=time.monotonic();current=identities(a.exe);runner=hash_file(a.native)
    if a.expectations:
        source=private_path(a.expectations,a.exe);receipt=source.parent/'report.json';fingerprint=hash_file(source)
        e=json.loads(source.read_text());validate(e,json.loads(receipt.read_text()),fingerprint,current)
        report=private_path(a.report or source.parent/'replay-report.json',a.exe);check_replay_destination(report,source,receipt)
        commands,expected,labels=[e[k] for k in ('commands','expected','labels')];metadata=e['evidence'];generation=0
    else:
        out=private_path(a.output,a.exe)
        if a.report:raise ValueError('Fresh runs use --output')
        if (out/'expected.json').exists() or (out/'report.json').exists():raise ValueError('Fresh redraw evidence exists')
        now=time.monotonic();commands,expected,labels,groups,calls=generate(a.exe);generation=time.monotonic()-now
        metadata={'groups':groups,'audited_callable_roots':calls,'seed':0x52413235,
            'scope':'Complete object/map redraw requests and wrapping counter; complete dirty-region registration with actual union/intersection and vector/empty initializers. Allocation/atexit are explicit services. Compare defined entry fields, capacity tails and ordered writes; three entry padding bytes and allocator internals have no native parity claim. Caller ESP/register/return and full arena/metadata guards. No region callers/frame scheduling, runtime integration or whole-frame parity.'}
        report=out/'report.json'
    now=time.monotonic();actual=native(a.native,commands);elapsed=time.monotonic()-now
    if not(len(actual)==len(expected)==len(commands)==len(labels)):raise AssertionError('Redraw vector count differs')
    for n,(x,y) in enumerate(zip(actual,expected)):
        if x!=y:
            at=next((i for i,(a,b) in enumerate(zip(x,y)) if a!=b),min(len(x),len(y)))
            raise AssertionError(f'{n} {labels[n]}: {commands[n]}\ntoken {at}: native {x[max(0,at-5):at+15]}, original {y[max(0,at-5):at+15]}')
    if identities(a.exe)!=current or hash_file(a.native)!=runner:raise ValueError('Run inputs changed')
    result={**metadata,'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006','identities':current,
        'native_sha256':runner,'cases':len(commands),'evidence_mode':'cached-original-replay' if a.expectations else 'fresh-original',
        'original_instructions_executed':not bool(a.expectations),'original_instructions_modified':False,
        'native_comparison_seconds':elapsed,'original_generation_seconds':generation,'elapsed_seconds':time.monotonic()-start}
    if not a.expectations:
        source=out/'expected.json';write_report(a.exe,source,{'executable_sha256':PATCHED_EXPECTED,'profile':'supplied-ra2-1006',
            'commands':commands,'expected':expected,'labels':labels,'evidence':result});fingerprint=hash_file(source)
    result['expectations_sha256']=fingerprint;write_report(a.exe,report,result)
    print(f'{len(commands):,} supplied-1.006 redraw results: PASS ({result["evidence_mode"]}, {elapsed:.3f}s native)')
if __name__=='__main__':main()
