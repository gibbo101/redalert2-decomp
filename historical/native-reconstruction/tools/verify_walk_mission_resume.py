# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint actual Walk IPiggyback query, predicate, reference and Foot composition."""
import hashlib,struct,pefile,capstone
from verify_infantry_mission_resume import verify as parent_verify,RANGES as PARENTS,SERVICES as PARENT_SERVICES
RANGES={**PARENTS,0x4c8b00:0xaf,0x454c70:0x75,0x71fe90:0xa,0x71fab0:0x5d,0x53d2b0:0xa4,0x71fde0:0xd,0x53d250:0x1e,0x71fba0:0x2d,0x71dea0:0xa,0x71fee0:0xa,0x71fdf0:0xd,0x53d270:0x37,0x4c2df0:0x67}
TABLES={0x7cfc30:16,0x7a2050:16,0x7afce0:16,0x7afcd0:16,0x7a5890:16,0x7afcc0:16,0x7aeba0:0x24,0x7aead8:0x14,0x7aeab4:0x18,0x79a1bc:8,0x79a708:8,0x79b610:8}
SERVICES=tuple(a for a in PARENT_SERVICES if a not in (0x454c70,0x4c8b00))+(0x3c7594,0x3c757c)
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic not in ('ret','jmp'):raise ValueError('Incomplete Walk resume range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for vt,off,target in ((0x7aead8,0,0x71fe90),(0x7aead8,0x10,0x71dea0),(0x7aeab4,0x14,0x71fba0),(0x7aeab4,8,0x71fee0),(0x7a3540,0x4c8,0x4c2df0)):
  if struct.unpack('<I',p.get_data(vt+off-0x400000,4))[0]!=target:raise ValueError('Walk resume vtable differs')
 if p.get_data(0x7cfc30-0x400000,16)!=p.get_data(0x7a2050-0x400000,16):raise ValueError('Walk piggyback IID differs')
 return dict(parent=parent,ranges=out,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()})
