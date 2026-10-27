# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact terminal interior entry; no complete Advance/mission-effect claim."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
from verify_map_floor_height import verify as floor_verify
BLOCK=0x4a2166
RANGES={BLOCK:0x193,0x4a1fa1:0x1d,0x4a263a:15,
 0x410290:0x2d,0x47ba50:0x49,0x4706c0:0x7bb,0x77f110:0x3d,
 0x41b320:0x3d,0x4ca6f0:0xde,0x49fdb0:0x71,0x5d4e40:0x21,
 0x4cd9b0:15,0x594770:0x12}
TABLES={0x79db04:0x50,0x7addf8:0x494,0x7a04cc:0x1c,
 0x79a728:8,0x79a730:8,0x79b610:8,0x79c9b0:8,0x7d8964:4}
STORES={0x4a21fb:('d',0x34,4),0x4a2203:('d',0x38,4),0x4a220c:('d',0x3c,4),
 0x4a2232:('d',0x40,4),0x4a223a:('d',0x44,4),0x4a2242:('d',0x48,4),
 0x4a2245:('d',0x63,1),0x4a2249:('d',0x63,1),0x4a1fa9:('d',0x4c,4),
 0x4cd9b2:('a',0x490,4),0x4cd9b8:('a',0x494,4),0x4a2282:('a',0x4d0,4)}
DISPATCH=((0x79db04,0x48,0x47ba50),(0x79db04,0x4c,0x410290),
 (0x7addf8,0x48,0x5d4e40),(0x7addf8,0x4c,0x4ca6f0),
 (0x7addf8,0x1a0,0x41b320),(0x7addf8,0x16c,0x594770),
 (0x7addf8,0x174,0x6fe610),(0x7addf8,0x414,0x6fd630),
 (0x7addf8,0x490,0x4ca2b0),(0x7a04cc,0x18,0x49fdb0))
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied terminal engine required')
 floor=floor_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Unaligned terminal range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for vt,off,target in DISPATCH:
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Terminal dispatch differs')
 for a,op in {0x4a21d6:('mov','ecx, dword ptr [ebp + 0x3c]'),0x4a21eb:('jge','0x4a224d'),
  0x4a2297:('cmp','eax, 2'),0x4a22cb:('je','0x4a22dc'),0x4a22e4:('jne','0x4a1fa1')}.items():
  if ops.get(a)!=op:raise ValueError('Terminal operation differs '+hex(a))
 return dict(ranges=ranges,tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},floor=floor,
  scope='Interior terminal4A2166 through actual return, with actual target Cell, Foot/Drive/registry coordinates, floor, mission getter and target clears. Entry track/index/head/residual/associations/divisor supplied. Notification174, mission414 and postCell490 effects supplied. No complete Advance/Process/world/runtime join.')
