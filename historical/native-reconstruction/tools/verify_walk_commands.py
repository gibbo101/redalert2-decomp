# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Walk command roots and actual Infantry guards/reset children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x71e020:0xe1,0x71e110:0x5f,0x71e1a0:0x72,0x6d8e80:0xe,
 0x6d6df0:7,0x6d6e00:7,0x508750:0x20,0x6a29b0:0x1c,0x77f110:0x3d}
TABLES={0x7aead8:0x7c,0x7a3540:0x4e0,0x79a728:8,0x7d8964:4}
SERVICES={0x548000:'coordinate map lookup',0x504740:'animation4DC'}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Walk command engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Walk command PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Walk command range '+hex(a))
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for vt,off,target in ((0x7aead8,0x44,0x71e020),(0x7aead8,0x48,0x71e110),(0x7aead8,0x78,0x71e1a0),
  (0x7a3540,0x324,0x6d8e80),(0x7a3540,0x1bc,0x6d6df0),(0x7a3540,0x1c0,0x6d6e00),
  (0x7a3540,0x4d0,0x508750),(0x7a3540,0x4dc,0x504740)):
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Walk command dispatch differs')
 for a,op in {0x71e02d:('call','dword ptr [eax + 0x324]'),0x71e040:('call','dword ptr [edx + 0x1bc]'),
  0x71e053:('call','dword ptr [eax + 0x1c0]'),0x71e0c7:('add','dword ptr [esi + 0x20], eax'),
  0x71e166:('call','dword ptr [edx + 0x4d0]'),0x71e1aa:('mov','bl, byte ptr [ecx + 0x30]'),
  0x508762:('mov','byte ptr [ecx + 0x5cc], 0'),0x6a29bf:('fmul','qword ptr [0xabe520]')}.items():
  if ops.get(a)!=op:raise ValueError('Walk command association differs '+hex(a))
 if p.get_data(0x79a728-0x400000,8)!=struct.pack('<d',.5) or p.get_data(0x7d8964-0x400000,4)!=struct.pack('<I',0xe7f):raise ValueError('Walk projection constants differ')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  services={hex(k):v for k,v in SERVICES.items()},scope='Complete Walk Move_To/Stop/immediate head with actual Infantry guards/reset and projection conversion. Map, animation4DC, initial records/global projection scale supplied. Not Infantry/Foot SetDestination, route finding, production walking or objectives.')
