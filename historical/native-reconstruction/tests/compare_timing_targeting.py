#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Original skirmish timing and destination turret/bearing oracle.
Original instructions stay unchanged; time/sleep and object services are explicit fixtures.
"""
import argparse
import hashlib
import json
import random
import struct
import subprocess
from collections import Counter
from pathlib import Path
from original_movement import Oracle, UNIT, ARG, STACK
from compare_original import EXPECTED
from movement_evidence import prepare, identities, save, replay
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EIP, UC_X86_REG_ESP, UC_X86_REG_ESI, UC_X86_REG_FPCW

TARGET, TARGET_VTABLE = 0x1111000, 0x1112000
class TargetOracle(Oracle):
    def __init__(self,exe,**kwargs):
        super().__init__(exe,precision=0xe7f,**kwargs)
        self.put(TARGET,TARGET_VTABLE)
        self.virtual(0x48,4,self.target_coords,'destination coordinate getter',TARGET_VTABLE)
    def target_coords(self):
        out=self.arg(0)
        self.u.mem_write(out,bytes(self.u.mem_read(TARGET+0x88,12)))
        return out
    def positions(self,x,y,tx,ty,present=True):
        self.u.mem_write(UNIT+0x88,struct.pack('<iii',x,y,0))
        self.u.mem_write(TARGET+0x88,struct.pack('<iii',tx,ty,0))
        self.put(UNIT+0x494,TARGET if present else 0)
    def bearing(self,x,y,tx,ty):
        self.positions(x,y,tx,ty)
        self.call(0x5cac70,[ARG,TARGET],this=UNIT)
        return self.get(ARG,'H')
    def turret(self,tick,x,y,present,tx,ty):
        self.positions(x,y,tx,ty,present)
        self.put(self.va(0xa2894c),tick)
        self.call(0x6f03d0,[],this=UNIT)
        return [self.facing(0x2f8,tick),self.get(UNIT+0x2f8,'H'),self.get(UNIT+0x2fc,'H'),
                self.get(UNIT+0x300,'i'),self.get(UNIT+0x308,'i'),self.get(UNIT+0x3f0)]

class ClockOracle(Oracle):
    def __init__(self,exe,**kwargs):
        super().__init__(exe,**kwargs)
        self.ms=0;self.sleeps=[]
        self.put(self.va(0xa255a8),5) # Original skirmish session branch.
        self.put(self.va(0xa56741),1,'B') # Statistics timer already initialized.
        self.put(self.va(0x785520),0x1220000)
        self.bind(0x1220000,0,lambda:self.ms,'timeGetTime fixture')
        self.put(self.va(0x7851e0),0x1220010)
        self.bind(0x1220010,4,self.sleep,'Sleep fixture')
        self.bind(0x495e60,0,lambda:0,'presentation wait service')
    def sleep(self):
        amount=self.arg(0);self.sleeps.append(amount)
        self.ms=(self.ms+max(1,amount))&0xffffffff
        return 0
    def block(self,start,end):
        self.u.reg_write(UC_X86_REG_ESP,STACK)
        self.u.emu_start(self.va(start),self.va(end),count=1000)
        if self.u.reg_read(UC_X86_REG_EIP)!=self.va(end):raise RuntimeError('Original block did not terminate')
        if self.audit_calls:self.audit_arenas()
    def remaining(self,start,duration,now):
        self.ms=now;self.put(self.va(0x821cb0),start);self.put(self.va(0x821cb8),duration)
        self.block(0x53e660,0x53e697)
        value=self.u.reg_read(UC_X86_REG_ESI)
        return value if value<0x80000000 else value-0x100000000
    def wait(self,start,work,slider):
        # Original slider conversion block: ECX = 6 - slider.
        self.u.reg_write(UC_X86_REG_EAX,slider)
        self.block(0x4cf4c4,0x4cf4cb)
        self.put(self.va(0xa28738),self.u.reg_read(UC_X86_REG_ECX))
        self.ms=start;self.sleeps=[]
        self.put(self.va(0xa56770),start>>4);self.put(self.va(0xa56778),60)
        # Original skirmish timer setup includes the actual coarse-clock helper.
        self.block(0x53def2,0x53df16)
        self.ms=(start+work)&0xffffffff
        self.call(0x53e660,[],this=0,budget=30000)
        return [self.ms,len(self.sleeps),*self.sleeps]

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe',type=Path,required=True)
parser.add_argument('--native',type=Path,default=Path('build/native/timing-targeting-vectors'))
parser.add_argument('--direction-data',type=Path,default=Path('private/derived/direction-data.bin'))
parser.add_argument('--report',type=Path)
parser.add_argument('--expectations',type=Path,help='Identity-checked native replay of private original expectations')
parser.add_argument('--native-data-exe',type=Path,help='Explicit retained disc table input; required for patched research')
args=parser.parse_args()
digest,profile,native_data,out=prepare(args,'timing-targeting')
if args.expectations:
 replay(args,digest,profile,native_data,out,'timing-targeting')
 raise SystemExit(0)
commands=[];expected=[];labels=[];counts=Counter();callbacks=Counter()
def case(command,result,label):
    commands.append(command);expected.append(result);labels.append(label);counts[label]+=1

clock=ClockOracle(args.exe,allow_patched=True,audit_calls=True)
for duration in range(7):
    for start in [-1,0,1,20,0x0ffffff0,0x0fffffff]:
        for now in [0,1,15,16,17,31,32,47,48,63,64,95,96,320,352,416,0xfffffff0,0xffffffff]:
            case(f'R {start} {duration} {now}',[clock.remaining(start,duration,now)],'remaining')
for slider in range(7):
    for start in [0,1,7,15,16,17,1007,1234567]:
        for work in [0,1,3,15,16,31,47,95,96,110,1000]:
            case(f'W {start} {work} {slider}',clock.wait(start,work,slider),'frame wait')
callbacks.update(clock.calls)

rng=random.Random(0x524133)
target=TargetOracle(args.exe,allow_patched=True,audit_calls=True)
# Axes, zero vector, all quadrants, table cutoffs, one-lepton and map-scale bearings.
values=[-262144,-65536,-4097,-101,-100,-99,-32,-2,-1,0,1,2,32,99,100,101,4097,65536,262144]
for dx in values:
    for dy in values:
        case(f'A 0 0 {dx} {dy}',[target.bearing(0,0,dx,dy)],'bearing')
for _ in range(6000):
    x,y,tx,ty=(rng.randrange(262144) for _ in range(4))
    case(f'A {x} {y} {tx} {ty}',[target.bearing(x,y,tx,ty)],'bearing')
# Ratios around every lookup bin boundary, including saturation at index 4097.
for i in range(4098):
    dx=4096;dy=int(i*0.024413354694843292*dx)
    for delta in [-1,0,1]:
        case(f'A 0 0 {dx} {dy+delta}',[target.bearing(0,0,dx,dy+delta)],'bearing threshold')
callbacks.update(target.calls)

for scenario in range(80):
    o=TargetOracle(args.exe,allow_patched=True,audit_calls=True);body=rng.randrange(65536);turret=rng.randrange(65536);rot=rng.choice([1,2,5,7,127])
    o.begin(2688,2688,body,rot,6)
    o.put(ARG,turret);o.call(0x4b8630,[ARG],this=UNIT+0x2f8)
    commands.append(f'B {body} {turret} {rot}')
    tx,ty=7000,3000
    for tick in range(120):
        if tick in [3,25,52,90]:tx,ty=rng.randrange(12000),rng.randrange(12000)
        x=2688+tick*11;y=2688-tick*3;present=not(60<=tick<75)
        case(f'T {tick} {x} {y} {int(present)} {tx} {ty}',o.turret(tick,x,y,present,tx,ty),'turret update')
    callbacks.update(o.calls)

proc=subprocess.run([str(args.native),str(native_data),str(args.direction_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True,check=True)
actual=[[int(n) for n in line.split()] for line in proc.stdout.splitlines()]
if len(actual)!=len(expected):raise RuntimeError(f'Native output count differs: {len(actual)} vs {len(expected)}')
# B commands initialize state without emitting a row.
output_commands=[line for line in commands if not line.startswith('B ')]
for i,(native,original) in enumerate(zip(actual,expected)):
    if native!=original:raise AssertionError(f'{labels[i]} {output_commands[i]}\nnative={native}\noriginal={original}')
report={'executable_sha256':digest,'native_sha256':hashlib.sha256(args.native.read_bytes()).hexdigest(),
        'comparisons':len(expected),'groups':dict(counts),'matched':len(expected),'seed':0x524133,
        'original_instruction_bytes_changed':False,'fixture_services':dict(sorted(callbacks.items())),
        'scope':'Skirmish coarse-clock timer/wait policy; flat destination-coordinate turret branch and quantized bearing; no whole-game/UI/network timing claim'}
report.update(identities(args,digest,profile,native_data))
save(args,digest,profile,out,{'expected':expected,'labels':labels,'commands':commands},report)
print(f'{len(expected):,} original/native timing and targeting comparisons: PASS')
print(dict(counts))
