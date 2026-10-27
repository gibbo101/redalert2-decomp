# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect actual selected-head arrival, empty-head helper and Stop dispatch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_walk_movement as parent
EXTRA={0x71f590:0x36c,0x71e110:0x5f,0x4ca6f0:0xde,0x71df70:0x71}
RANGES=dict(parent.RANGES,**{})
RANGES.update(EXTRA)
SERVICES=dict(parent.SERVICES)
SERVICES.update({0x5084a0:'release occupation',0x508410:'claim occupation',0x500aa0:'notification174',
 0x501ce0:'destination410',0x508750:'movement reset4D0'})
def verify(data):
 base=parent.verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Walk arrival range '+hex(a))
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for baseva,off,target in ((0x7aead8,0x48,0x71e110),(0x7aead8,0x18,0x71df70),(0x7a3540,0x4c,0x4ca6f0),
  (0x7a3540,0xec,0x5084a0),(0x7a3540,0xe8,0x508410),(0x7a3540,0x174,0x500aa0),
  (0x7a3540,0x410,0x501ce0),(0x7a3540,0x4d0,0x508750)):
  if p.get_data(baseva+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Walk arrival dispatch differs')
 if ops.get(0x71f874)!=('mov','eax, dword ptr [esi]'):raise ValueError('Walk empty-head association differs')
 return dict(parent=base,extra_ranges=ranges,services={hex(a):n for a,n in SERVICES.items()},
  scope='Complete selected-head Walk Process paths including arrival; empty-point head helper and Stop actual. Negative secondary index. Occupation, notification, destination and reset effects remain supplied. No initial/next subcell preparation, production world, SDL walking or objectives.')
