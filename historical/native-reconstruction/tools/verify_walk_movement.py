# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint bounded committed Walk Process and actual numeric/placement children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x71dff0:0x21,0x71e220:0x1367,0x71dea0:0xa,0x71e170:0x22,
 0x5d4e40:0x21,0x41b320:0x3d,0x6d8e80:0xe,0x4c2df0:0x67,
 0x4ca160:0x40,0x5d51c0:0x1d,0x5d4860:0xb1,0x4b8b10:0xca,0x453eb0:0x1c,
 0x4ba600:0xb2,0x4ba410:0x6e,0x4ba480:66,0x4ba4d0:73,0x77f110:0x3d}
SERVICES={0x508980:'speed',0x4c2e60:'Mark',0x55a280:'floor',0x548070:'lookup',0x548000:'currentCell',0x47bb30:'dirty'}
TABLES={0x7aead8:0xc4,0x7a3540:0x4d4,0x813df4:4097*4,0x817df8:4,0x817dfc:65536,
 0x79b620:24,0x7a0f8c:8,0x79d158:8,0x79a738:4,0x79a708:8,0x79b610:8}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Walk engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Walk PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Walk range '+hex(a))
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,expected in {0x71dffe:('call','0x71e220'),0x71f0ca:('cmp','eax, 0x11'),
  0x71f3bb:('sub','ecx, 0x3fff'),0x71f44e:('mov','word ptr [esp + 0x1e], ax'),
  0x71f4b3:('sub','edx, 4'),0x71f54c:('mov','byte ptr [eax + 0x74], 0')}.items():
  if ops.get(a)!=expected:raise ValueError('Walk association differs '+hex(a))
 for base,off,target in ((0x7aead8,0x40,0x71dff0),(0x7aead8,0x10,0x71dea0),(0x7aead8,0x4c,0x71e170),
  (0x7a3540,0x48,0x5d4e40),(0x7a3540,0x19c,0x4ca160),(0x7a3540,0x1a0,0x41b320),
  (0x7a3540,0x1b4,0x5d4860),(0x7a3540,0x324,0x6d8e80),(0x7a3540,0x4c8,0x4c2df0),
  (0x7a3540,0x4bc,0x508980)):
  if p.get_data(base+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Walk dispatch differs')
 pi=struct.unpack('<d',p.get_data(0x79d158-0x400000,8))[0]
 if struct.pack('<d',pi/-32767.)!=p.get_data(0x79b620-0x400000,8):raise ValueError('Walk scalar association differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  services={hex(a):name for a,name in SERVICES.items()},scope='Complete committed Walk Process roots with planar distance>=17. Initial selected subcell, actor/type/Facing/global records, speed, Mark, floor, map lookups and dirty effects supplied. No arrival, next-subcell selection, route finding, infantry startup/animation, production world, SDL movement or objectives.')
