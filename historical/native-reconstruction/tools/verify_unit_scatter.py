#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the Unit Scatter parent, selected real children and supplied boundaries."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x7072d0:0x617,0x6c12d0:0x49,0x6c12c0:8,0x705020:7,
 0x594770:0x12,0x5950d0:0xf,0x594cb0:0x65,0x70a2d0:6,
 0x454bf0:0x75,0x4a4d40:10,0x49f820:0x5d,0x53d2b0:0xa4,
 0x4a4c60:0xd,0x4a4c70:0xd,0x53d250:0x1e,0x53d270:0x37,0x4a47f0:0x38,
 0x4b8c90:0x2d,0x4a4d20:0x1c,0x4b8be0:0x99,
 0x6388a0:0xad,0x4ba600:0xb2,0x4ba410:0x6e,0x77f110:0x3d}
# Complete original children at these addresses remain named supplied services.
SERVICES={0x4ca6f0:'coordinates',0x548070:'lookup',0x4cc4b0:'layer',
 0x55a660:'bounds',0x5d47d0:'level',0x703040:'admission',
 0x6a6a50:'projection',0x5502e0:'pathfinder',0x7053f0:'destination'}
TABLES={0x813df4:4097*4,0x817df8:4,0x7a0f8c:8,0x79d158:8,0x79b628:16,
 0x7cf208:16,0x7afce0:16,0x7afcd0:16,0x7a5890:16,0x7afcc0:16,0x7a2050:16,
 0x7a1f70:16,0x7a1fd0:16,0x7addf8:0x414,0x7a04cc:0xc8,0x7a0594:0x24,
 0x79a1bc:8}
DISPATCH=((0x7addf8,0x26c,0x6c12d0),(0x7addf8,0x16c,0x594770),
 (0x7addf8,0x80,0x6c12c0),(0x7addf8,0x84,0x705020),
 (0x7addf8,0x2c,0x70a2d0),(0x7addf8,0x1d0,0x594cb0),
 (0x7addf8,0x4c,0x4ca6f0),(0x7addf8,0xb8,0x4cc4b0),
 (0x7addf8,0x194,0x703040),
 (0x7addf8,0x410,0x7053f0),(0x7a04cc,0,0x4a4d40),
 (0x7a0594,0xc,0x4a47f0),(0x7a0594,4,0x4a4c60),(0x7a0594,8,0x4a4c70))
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Unit Scatter engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Scatter PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Scatter range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for vt,off,target in DISPATCH:
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Scatter dispatch differs '+hex(vt+off))
 if p.get_data(0x7a1f70-0x400000,16)==p.get_data(0x7a1fd0-0x400000,16):raise ValueError('Ordinary Drive class exclusion association differs')
 if p.get_data(0x79a1bc-0x400000,8)!=struct.pack('<2I',0x3c7594,0x3c757c):raise ValueError('Scatter atomic import differs')
 return dict(ranges=ranges,tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},
  services={hex(a):s for a,s in SERVICES.items()},
  scope='Unit Scatter parent control policy with actual eligibility, ordinary Drive successful interface ownership, Facing, bearing, RNG and QueueMission. Coordinate/map/layer/level/bounds/admission/projection/pathfinder/destination remain supplied. No Advance6/world/runtime join.')
