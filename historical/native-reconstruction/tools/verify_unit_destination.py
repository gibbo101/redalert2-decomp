#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact ordinary Cell/null destination roots and selected actual children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x7053f0:0x1613,0x4c8030:0x1e8,0x636f10:0x25,0x636e10:0x10,
 0x594770:0x12,0x47cf80:6,0x70a2d0:6,0x4cde30:0x2a,
 0x4a4c40:5,0x49fc70:0x96,0x53d230:10,0x4cde90:0x16,0x4a4d00:0xd,
 0x454bf0:0x75,0x4a4d40:10,0x49f820:0x5d,0x53d2b0:0xa4,0x4a4c60:0xd,0x4a4c70:0xd,
 0x53d250:0x1e,0x53d270:0x37,0x4a47f0:0x38,
 0x410290:0x2d,0x47ba50:0x49,0x4706c0:0x7bb,0x77f110:0x3d,
 0x49fe30:181,0x49fef0:200,0x70a240:0x1b,0x6d8e80:14,0x4cd080:0x35,
 0x6d6df0:7,0x6d6e00:7,0x548000:0x68,0x6c12c0:8,0x705020:7}
TABLES={0x7addf8:0x414,0x7a04cc:0xc8,0x7a0594:0x24,0x79db04:0x58,
 0x7a177c:0x10,0x7cf208:16,0x7afce0:16,0x7afcd0:16,0x7afcc0:16,
 0x7a5890:16,0x7a2050:16,0x7a1f70:16,0x7a1f80:16,0x7a1f90:16,
 0x79a1bc:8,0x79ea48:8,0x79a728:8,0x79a730:8,0x79b610:8,0x79c9b0:8,0x7d8964:4}
DISPATCH=((0x7addf8,0x410,0x7053f0),(0x7addf8,0x16c,0x594770),
 (0x7addf8,0x324,0x70a240),(0x7addf8,0x328,0x4cd080),
 (0x7addf8,0x1bc,0x6d6df0),(0x7addf8,0x1c0,0x6d6e00),
 (0x79db04,0x2c,0x47cf80),(0x79db04,0x48,0x47ba50),(0x79db04,0x4c,0x410290),
 (0x7a177c,0xc,0x4cde30),(0x7a04cc,0x10,0x49fc70),(0x7a04cc,0x44,0x49fe30),
 (0x7a04cc,0x48,0x49fef0),(0x7a04cc,0x60,0x53d230),(0x7a04cc,0x98,0x4a4c40))
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied destination engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Destination PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete destination range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for vt,off,target in DISPATCH:
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Destination dispatch differs '+hex(vt+off))
 for a in (0x7a1f80,0x7a1f90):
  if p.get_data(a-0x400000,16)==p.get_data(0x7a1f70-0x400000,16):raise ValueError('Ordinary class distinction differs')
 if p.get_data(0x79a1bc-0x400000,8)!=struct.pack('<2I',0x3c7594,0x3c757c):raise ValueError('Destination atomic imports differ')
 if p.get_data(0x79ea48-0x400000,8)!=struct.pack('<d',0.30000001192092896):raise ValueError('Stop constant differs')
 return dict(ranges=ranges,tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},
  scope='Complete ordinary powered Unit Cell/null destination -> Foot -> actual Drive commands, vector clear, interface, Cell center/floor and map lookup. Non7/non16 missions, no transport/special type/effect/train/bridge adjustment. Supplied initial records, heap disposal and local scratch; no Scatter/Process/world/runtime join.')
