#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Compare flat-ground drive/turret traces against the hash-pinned base executable."""
import argparse
import hashlib
import json
import random
import struct
import subprocess
from collections import Counter
from pathlib import Path
from original_movement import Oracle, UNIT, ARG
from compare_original import EXPECTED
from movement_evidence import prepare, identities, save, replay

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe',type=Path,required=True)
parser.add_argument('--native',type=Path,default=Path('build/native/movement-vectors'))
parser.add_argument('--report',type=Path)
parser.add_argument('--expectations',type=Path,help='Identity-checked native replay of private original expectations')
parser.add_argument('--native-data-exe',type=Path,help='Explicit retained disc table input; required for patched research')
args=parser.parse_args()
digest,profile,native_data,out=prepare(args,'movement')
if args.expectations:
 replay(args,digest,profile,native_data,out,'movement')
 raise SystemExit(0)
commands=[];expected=[];labels=[];callbacks=Counter();scenarios=0

def emit(line):commands.append(line)
def check(value,label):expected.append(value);labels.append((len(commands)-1,label))
# Full speed method: original type-speed conversion block, percentage setter, and
# Foot::GetCurrentSpeed. Country/instance multipliers one, unpromoted, no towing.
o=Oracle(args.exe,allow_patched=True,audit_calls=True)
for value in [-100,-1,0,1,2,5,6,7,25,50,99,100,101,2147483647]:
 for percent in [-1.,0.,0.125,0.3,0.5,0.625,1.,1.5]:
  emit(f'SPEED {value} 33 {percent:.17g}')
  speed=o.set_ini_speed(value,33)
  words=struct.unpack('<II',struct.pack('<d',percent));o.call(0x4c2910,words,this=UNIT)
  check([speed,o.call(0x4c95c0,[],this=UNIT)],'speed')
callbacks.update(o.calls)

def scenario(direction,heading,count,terrain=1.,speed=6,rot=5,stop=-1,order_tick=-1,newdir=0,turn_tick=-1,precision=0x27f):
 global scenarios
 scenarios+=1
 # Terrain speed entries are original float32 data; native receives that exact value.
 terrain=struct.unpack('<f',struct.pack('<f',terrain))[0]
 o=Oracle(args.exe,terrain,precision,allow_patched=True,audit_calls=True);o.begin(2688,2688,heading,rot,speed)
 emit(f'BEGIN 2688 2688 {heading} {rot} {speed} {terrain:.17g}')
 o.order(direction,count);emit(f'ORDER {direction} {count}')
 frames=max(180 if terrain>=0.5 else 340,count*24+40)
 for tick in range(frames):
  if tick==stop:o.stop();emit('STOP')
  if tick==order_tick:o.order(newdir,2);emit(f'ORDER {newdir} 2')
  if tick==turn_tick:
   target=(heading+12345)&65535;o.put(ARG,target);o.put(o.va(0xa2894c),tick);o.call(0x4b8550,[ARG],this=UNIT+0x2e0);emit(f'TURN {target} {tick}')
  emit(f'STEP {tick}');check(o.step(tick),f'scenario {scenarios}, direction={direction}, tick={tick}, stop={stop}, order={order_tick}, precision={precision:x}')
 callbacks.update(o.calls)

for direction in range(8):
 for heading in [direction*8192,0,32768,8193]:scenario(direction,heading,3)
 for tick in [0,1,5,11,20]:scenario(direction,direction*8192,3,stop=tick)
 # New route during a body turn; deliberately no moving curved-track case.
 scenario(direction,((direction+2)%8)*8192,3,order_tick=3,newdir=(direction+4)%8)
 for terrain in [0.5,0.625,0.3]:scenario(direction,direction*8192,2,terrain=terrain)
 # Check both x87 53/64-bit precision modes over the live arithmetic domain.
 scenario(direction,8193,2,precision=0x37f)
 scenario(direction,direction*8192,1)
 scenario(direction,direction*8192,23)
 scenario(direction,((direction+3)%8)*8192,2,stop=2)
 scenario(direction,8193,2,rot=2)
proc=subprocess.run([str(args.native),str(native_data)],input='\n'.join(commands)+'\n',text=True,capture_output=True)
if proc.returncode:raise RuntimeError(f'Native failed: {proc.stderr}')
actual=[[int(n) for n in row.split()] for row in proc.stdout.splitlines()]
if len(actual)!=len(expected):raise RuntimeError(f'Result count mismatch: {len(actual)} vs {len(expected)}')
for i,(a,b) in enumerate(zip(actual,expected)):
 if a!=b:
  line,label=labels[i]
  raise AssertionError(f'{label}\ncommand={commands[line]}\noriginal={b}\nnative={a}\ncommand index={line}')
report={'executable_sha256':digest,'native_sha256':hashlib.sha256(args.native.read_bytes()).hexdigest(),'scenarios':scenarios,'comparisons':len(expected),'matched':len(expected),'original_instructions_patched':False,'environment_callbacks':dict(sorted(callbacks.items())),'scope':'Flat straight tracks, healthy unpromoted Rhino, supplied direction queue, no combat/destination actor, no original pathfinding or scheduler claim'}
report.update(identities(args,digest,profile,native_data))
save(args,digest,profile,out,{'values':expected,'labels':labels,'commands':commands},report)
print(f'{len(expected):,} original/native movement comparisons across {scenarios} traces: PASS')
print('Original full drive process and turret update; flat-world services substituted, instruction bytes unchanged.')
