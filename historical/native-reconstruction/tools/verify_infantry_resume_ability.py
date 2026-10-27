# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact actual promotion/Type/QueueMission below Walk and Infantry resume."""
import hashlib,struct,pefile,capstone
from verify_walk_mission_resume import verify as parent_verify,RANGES as PARENTS,TABLES as PARENT_TABLES,SERVICES as PARENT_SERVICES
EXTRA={0x6d7910:0x80,0x7133a0:0x27,0x713420:0x18,0x6c12c0:8,0x506950:7,0x594cb0:0x65}
RANGES={**PARENTS,**EXTRA};TABLES={**PARENT_TABLES,0x79a6f8:8,0x7f9978:72,0x7f99c8:11,0x7f7720:19}
SERVICES=tuple(a for a in PARENT_SERVICES if a not in (0x6d7910,0x6000120))
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ranges={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic not in ('ret','jmp'):raise ValueError('Incomplete resume ability range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x80,0x6c12c0),(0x84,0x506950),(0x1d0,0x594cb0)):
  if struct.unpack('<I',p.get_data(0x7a3540+off-0x400000,4))[0]!=target:raise ValueError('E1 resume type/queue vtable differs')
 if struct.unpack('<d',p.get_data(0x79a6f8-0x400000,8))[0]!=2.:raise ValueError('Promotion bound differs')
 if p.get_string_at_rva(struct.unpack('<I',p.get_data(0x7f9978+16*4-0x400000,4))[0]-0x400000)!=b'GUARD_AREA':raise ValueError('Ability16 name differs')
 if p.get_string_at_rva(0x7f7720-0x400000)!=b'DefaultToGuardArea':raise ValueError('B00 key differs')
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},inspected_only_b00_key_slice='6DD241..6DD255')
