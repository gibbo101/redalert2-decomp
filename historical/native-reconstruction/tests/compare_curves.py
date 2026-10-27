#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare ordinary curved-drive traces with the supplied base executable.
The path is an explicit fixture; no original pathfinder or mission system is claimed.
"""
import argparse
import hashlib
import json
import subprocess
from collections import Counter
from pathlib import Path
from original_curves import CurveOracle
from original_movement import TYPE
from compare_original import EXPECTED
from movement_evidence import prepare, identities, save, replay

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe',type=Path,required=True)
parser.add_argument('--native',type=Path,default=Path('build/native/movement-vectors'))
parser.add_argument('--report',type=Path)
parser.add_argument('--expectations',type=Path,help='Identity-checked native replay of private original expectations')
parser.add_argument('--native-data-exe',type=Path,help='Explicit retained disc table input; required for patched research')
args=parser.parse_args()
digest,profile,native_data,out=prepare(args,'curves')
if args.expectations:
 replay(args,digest,profile,native_data,out,'curves')
 raise SystemExit(0)
commands=[];expected=[];labels=[];groups=Counter();branches=Counter();callbacks=Counter();scenarios=0

def scenario(route,group,passive=False,edit_tick=-1,newroute=None,stop_tick=-1,terrain=1.0,frames=150):
    global scenarios
    scenarios+=1;o=CurveOracle(args.exe,terrain,allow_patched=True,audit_calls=True);o.begin(2688,2688,route[0]*8192,5,6)
    o.put(TYPE+0xba4,int(passive),'B')
    commands.append(f'BEGIN 2688 2688 {route[0]*8192} 5 6 {terrain:.17g}')
    commands.append(f'PASSIVE {int(passive)}')
    def path(dirs):o.path(dirs);commands.append('PATH '+str(len(dirs))+' '+' '.join(map(str,dirs)))
    path(route)
    for tick in range(frames):
        if tick==edit_tick:path(newroute)
        if tick==stop_tick:o.stop();commands.append('STOP')
        commands.append(f'DETAIL {tick}')
        expected.append(o.detail(tick));labels.append(f'{group}, scenario {scenarios}, tick {tick}, passive={passive}')
        groups[group]+=1
    branches.update(o.branches);callbacks.update(o.calls)

# All 64 direction pairs, including invalid curve descriptors and straight fallbacks.
for first in range(8):
    for second in range(8):scenario([first,second,second,second],'direction pairs',frames=120)
# Every valid ordinary curved descriptor; stop at early, middle and late positions.
meta=CurveOracle(args.exe,allow_patched=True,audit_calls=True)
for first in range(8):
    for second in range(8):
        raw=meta.get(meta.va(0x78b188)+12*(first*8+second),'B')
        if raw<3:continue
        for stop in [2,10,22]:scenario([first,second,second,second],'curve stops',stop_tick=stop,frames=180)
# Each raw curved shape, all new directions, immediately before/after the jump point.
for first,second in [(0,1),(0,2),(1,3),(1,2)]:
    raw=meta.get(meta.va(0x78b188)+12*(first*8+second),'B')
    jump=meta.get(meta.va(0x78b0a8)+16*raw+4,'i');jump_tick=((jump+1)*7+14)//15-1
    for newdir in range(8):
        for when in [jump_tick-1,jump_tick+1]:
            for passive in [False,True]:
                scenario([first,second,second,second],'route replacement',passive,when,[newdir]*3)
for route in [[0,1,2,3,4,5,6,7],[0,2,4,6,0,2],[1,3,5,7,1],[0,4,0,4],[7,0,1,2,1,0,7],[2,1,0,7,6,5]]:
    for passive in [False,True]:scenario(route,'mixed routes',passive,frames=260)
# Slower-speed interpolation on all four raw curve types, including stop credit.
for first,second in [(0,1),(0,2),(1,3),(1,2)]:
    scenario([first,second,second],'fractional speed',stop_tick=12,terrain=0.5,frames=240)

proc=subprocess.run([str(args.native),str(native_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
if proc.returncode:raise RuntimeError(proc.stderr)
actual=[[int(n) for n in row.split()] for row in proc.stdout.splitlines()]
if len(actual)!=len(expected):raise RuntimeError(f'Output count differs: {len(actual)} / {len(expected)}')
for i,(native,original) in enumerate(zip(actual,expected)):
    if native!=original:raise AssertionError(f'{labels[i]}\noriginal={original}\nnative={native}')
if branches[hex(meta.va(0x4a18a3))]==0 or branches[hex(meta.va(0x4a415c))]==0 or branches[hex(meta.va(0x4a3bcb))]==0:
    raise AssertionError('Expected switch, two-cell and fallback branches were not exercised')
report={'executable_sha256':digest,'native_sha256':hashlib.sha256(args.native.read_bytes()).hexdigest(),
        'comparisons':len(expected),'matched':len(expected),'scenarios':scenarios,'groups':dict(groups),
        'original_branches':dict(branches),'fixture_services':dict(callbacks),'original_instruction_bytes_changed':False,
        'scope':'Ordinary flat tracks, supplied routes, Passive guard; no pathfinding, blocked cells, short/special tracks or full passive-unit behavior claim'}
report.update(identities(args,digest,profile,native_data))
save(args,digest,profile,out,{'expected':expected,'labels':labels,'commands':commands},report)
print(f'{len(expected):,} original/native curve comparisons across {scenarios} traces: PASS')
print(dict(groups));print('Covered original branches:',dict(branches))
