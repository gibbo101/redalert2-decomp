#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base reveal-area parent and actual numeric children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED

RANGES={0x54a110:0x440,0x6a2970:0x3c,0x4ba410:0x6e,0x77f110:0x3d}
TABLES={0x79a728:8,0x79a738:4,0x7d8964:4,0x7a5908:44}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied reveal-area engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Reveal-area PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete reveal-area range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 expected={0x54a123:('idiv','dword ptr [0xa6fc30]'),0x54a139:('call','0x6a2970'),0x54a15a:('call','0x6a2970'),
  0x54a24e:('cmp','eax, 0xb'),0x54a267:('mov','edi, dword ptr [eax*4 + 0x7a5908]'),
  0x54a295:('mov','eax, dword ptr [eax*4 + 0x7a58fc]'),0x54a2f9:('call','0x4e5540'),
  0x54a406:('call','0x4ba410'),0x54a40e:('call','0x77f110'),
  0x54a441:('mov','edx, dword ptr [esi + edx*4]'),0x54a44c:('mov','dword ptr [0xa6fa1c], eax'),
  0x54a4c6:('movsx','ecx, byte ptr [eax + 0x11b]'),0x54a4d8:('mov','edx, dword ptr [esi + 0x140]'),
  0x54a4e7:('mov','dword ptr [esi + 0x140], edx'),0x54a511:('call','0x49a0f0'),
  0x54a52c:('call','0x62fca0'),0x54a54d:('ret','0x20'),
  0x6a2993:('fmul','qword ptr [0xabe490]'),0x6a299d:('fadd','qword ptr [0x79a728]'),
  0x6a29a3:('call','0x77f110'),0x4ba410:('fld','qword ptr [esp + 4]'),0x77f12b:('fistp','qword ptr [eax]')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Reveal-area association differs '+hex(a))
 if struct.unpack('<d',p.get_data(0x79a728-0x400000,8))[0]!=.5 or p.get_data(0x79a738-0x400000,4)!=bytes(4):raise ValueError('Reveal-area numeric constants differ')
 if p.get_data(0x7d8964-0x400000,4)!=struct.pack('<I',0xe7f):raise ValueError('Reveal-area FTOL control differs')
 counts=list(struct.unpack('<11i',p.get_data(0x7a5908-0x400000,44)))
 if counts[0]!=1 or any(a>=b for a,b in zip(counts,counts[1:])):raise ValueError('Reveal-area count table shape differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},counts=counts,
  scope='Complete base54A110 reveal-area orchestration with actual height projection, table sqrt and FTOL. Startup spread/height-offset arrays and scale are supplied; House predicate and visibility children49A0F0/62FCA0 remain supplied.')
