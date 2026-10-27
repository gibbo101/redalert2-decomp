# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Infantry transfer wrapper and actual ground/packed-Cell children."""
import hashlib,struct,pefile,capstone
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x4ca7d0:0x41,0x4cce70:5,0x5d5410:0x22,0x5d4810:0x4f,0x41b320:0x3d}
SERVICES=(0x6cd940,0x55a280)
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied base required')
 p=pefile.PE(data=data);cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!=('jmp' if a==0x4cce70 else 'ret'):raise ValueError('Incomplete transfer wrapper span '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x378,0x4ca7d0),(0x54,0x4cce70),(0x1b0,0x5d4810),(0x1a0,0x41b320)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('E1 transfer wrapper dispatch differs')
 return dict(ranges=ranges,base_and_floor_children_supplied=True,actual_query_relative_height_and_packed_cell=True)
