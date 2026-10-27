#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Hash-pin the complete signed inclusive RNG range root and Scatter callers."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x6388a0:0xad}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied random-range engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Random-range PE differs')
 a=0x6388a0;raw=p.get_data(a-0x400000,0xad);ins=list(cs.disasm(raw,a));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=0xad or ops.get(0x63894a)!=('ret','8'):raise ValueError('Incomplete random range')
 for addr,op in {0x6388af:('je','0x638949'),0x6388b5:('jle','0x6388bb'),
  0x6388bc:('sub','ecx, ebx'),0x6388e2:('shl','ebp, cl'),
  0x6388eb:('jle','0x638945'),0x63893e:('and','eax, ebp'),
  0x638942:('jg','0x6388ee')}.items():
  if ops.get(addr)!=op:raise ValueError('Random-range arithmetic association differs '+hex(addr))
 callers={}
 for addr in (0x707574,0x707613,0x707656):
  code=p.get_data(addr-0x400000,5);decoded=list(cs.disasm(code,addr))
  if len(decoded)!=1 or (decoded[0].mnemonic,decoded[0].op_str)!=('call','0x6388a0'):raise ValueError('Scatter RNG call differs')
  callers[hex(addr)]=hashlib.sha256(code).hexdigest()
 return dict(ranges={hex(a):dict(bytes=len(raw),instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())},
  Scatter_caller_inspection_only=callers,
  scope='Complete terminating signed inclusive range policy with actual inlined XOR step; supplied initial state. No seeding/scenario association, Unit Scatter/Advance6 or runtime execution. Wider signed spans refused; host draw bound is not original behavior.')
