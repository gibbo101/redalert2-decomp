#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base Techno sight with actual type/timer/conversion children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED

RANGES={0x6d5c30:0x256,0x6c12c0:8,0x705020:7,0x7133a0:0x27,
        0x713420:0x18,0x77f110:0x3d}
TABLES={0x79a6f8:8,0x79a708:8,0x79b610:8,0x79c518:8,0x7d8964:4,
        0x7addf8:0x41c}

def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:
  raise ValueError('Exact supplied Techno sight engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:
  raise ValueError('Techno sight PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic not in ('ret','jmp'):
   raise ValueError('Incomplete Techno sight range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 expected={
  0x6d5c38:('mov','al, byte ptr [esi + 0x32d]'),
  0x6d5c4f:('mov','al, byte ptr [ecx + 0x1a6]'),
  0x6d5c7c:('idiv','dword ptr [ecx + 0x1324]'),
  0x6d5c92:('mov','byte ptr [esp + 0x24], 0'),
  0x6d5c97:('mov','byte ptr [esi + 0x378], al'),
  0x6d5ca2:('call','dword ptr [eax + 0x80]'),
  0x6d5cbd:('fmul','qword ptr [0x79c518]'),
  0x6d5cc3:('fadd','qword ptr [0x79a708]'),
  0x6d5ccb:('call','0x77f110'),
  0x6d5cde:('call','0x7133a0'),0x6d5ce9:('call','0x713420'),
  0x6d5d42:('fld','qword ptr [ecx + 0x5a0]'),
  0x6d5d48:('fcomp','qword ptr [0x79b610]'),
  0x6d5d81:('mov','byte ptr [esi + 0x1e4], 1'),
  0x6d5d88:('mov','dword ptr [ecx], eax'),
  0x6d5d8a:('mov','dword ptr [esi + 0x1f4], ebx'),
  0x6d5de2:('call','0x54a110'),0x6d5e26:('call','0x54a110'),
  0x6d5e78:('call','0x54a110'),0x6d5e83:('ret','0x10'),
  0x6c12c2:('jmp','dword ptr [eax + 0x84]'),
  0x705020:('mov','eax, dword ptr [ecx + 0x5ac]'),
  0x7133a2:('fcomp','qword ptr [0x79a708]'),
  0x7133b1:('fcomp','qword ptr [0x79a6f8]'),
  0x713422:('fcomp','qword ptr [0x79a6f8]'),
  0x77f12b:('fistp','qword ptr [eax]')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Techno sight association differs '+hex(a))
 for off,target in ((0x80,0x6c12c0),(0x84,0x705020),(0x418,0x6d5c30)):
  if p.get_data(0x7addf8+off-0x400000,4)!=struct.pack('<I',target):
   raise ValueError('Unit sight vtable association differs '+hex(off))
 constants={0x79a6f8:2.0,0x79a708:1.0,0x79b610:0.0,0x79c518:0.01}
 for a,value in constants.items():
  if struct.unpack('<d',p.get_data(a-0x400000,8))[0]!=value:
   raise ValueError('Techno sight constant differs '+hex(a))
 if p.get_data(0x7d8964-0x400000,4)!=struct.pack('<I',0xe7f):
  raise ValueError('Techno sight FTOL control differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  reveal_calls=['0x6d5de2','0x6d5e26','0x6d5e78'],
  scope='Complete base6D5C30 Techno sight with actual Unit type thunks, timer predicates and FTOL. Reveal-area54A110 is a supplied child; visibility mutation and production scheduling remain unjoined.')
