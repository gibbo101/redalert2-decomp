# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect complete supplied-base subcell roots, initializer and numeric children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x4763d0:0x84,0x47d060:0x26,0x508410:0x8f,0x5084a0:0x89,
 0x6c7420:0xa,0x4764b0:0x296,0x483390:0x74,0x6388a0:0xad,0x4ba410:0x6e,0x77f110:0x3d}
TABLES={0x7d2b6c:36,0x817dfc:65536,0x79a738:4,0x79d578:8,0x7d8964:4,0x7a3540:0xf0}
SERVICES={0x548000:'Cell lookup',0x55a280:'floor'}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied infantry engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Infantry PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  terminal='jmp' if a==0x47d060 else 'ret'
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!=terminal:raise ValueError('Incomplete infantry range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x47641d:('cmp','eax, 0x3c'),0x476550:('mov','cl, byte ptr [esp + 0x28]'),
  0x47671e:('mov','cl, byte ptr [esp + 0x2c]'),0x508463:('mov','byte ptr [esi + 0x128], cl'),
  0x5084e9:('mov','byte ptr [esi + 0x128], cl'),0x5084ef:('test','al, 0x1c'),
  0x476665:('call','0x6388a0'),0x476719:('call','0x55a280')}.items():
  if ops.get(a)!=op:raise ValueError('Infantry association differs '+hex(a))
 for off,target in ((0x38,0x6c7420),(0xe8,0x508410),(0xec,0x5084a0)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry dispatch differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  services={hex(a):s for a,s in SERVICES.items()},scope='Complete subcell classifier, Infantry occupy/release and ordinary Cell selector with actual offset initializer, House getter, RNG and numerics. Building children refused; floor/map, initial records and seeding supplied. No Walk head caller, production join or runtime walking.')
