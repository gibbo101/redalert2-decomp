#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete Object/Foot layer roots with actual coordinate/floor children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
from verify_map_floor_height import verify as verify_floor
RANGES={0x4cc4b0:0x1c,0x5d52f0:0xd7,0x4ca6f0:0xde,0x49fdb0:0x71,
 0x5d4e40:0x21,0x55a280:0x79,0x4706c0:0x7bb,0x77f110:0x3d,0x548000:0x68,
 0x49f600:0x12,0x4c2870:0x12}
TABLES={0x7addf8:0xbc,0x7a04cc:0x1c,0x79a728:8,0x79a730:8,0x79b610:8,0x79c9b0:8,0x7d8964:4}
DISPATCH=((0x7addf8,0x48,0x5d4e40),(0x7addf8,0x4c,0x4ca6f0),
 (0x7addf8,0xb8,0x4cc4b0),(0x7a04cc,0x18,0x49fdb0))
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied layer engine required')
 floor=verify_floor(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete layer range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for vt,off,target in DISPATCH:
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Layer dispatch differs')
 return dict(ranges=ranges,tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},
  floor=floor,scope='Complete Object/Foot layer and actual Foot/Drive/Object coordinates, map/Cell floor and coordinate Cell lookup. Supplied actor/Drive/registry/Cells/globals and floor template; optional diagnostic bridge mutation is not gameplay. No Scatter/admission/Process/world/runtime join.')
