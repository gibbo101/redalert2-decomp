#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Advance's ordinary 0/2 rejection and result7 default branch."""
import struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_drive_stores import verify as stores_verify
from verify_moving_resident_process import verify as admission_verify
ASSOCIATIONS={
 0x4a1c7b:('call','0x5d47d0'),0x4a1c90:('call','0x548070'),
 0x4a1c99:('call','dword ptr [edi + 0x194]'),0x4a1c9f:('cmp','eax, 6'),
 0x4a1ca2:('ja','0x4a1f8d'),0x4a1ca8:('jmp','dword ptr [eax*4 + 0x4a264c]'),
 0x4a1cb7:('cmp','eax, 1'),0x4a1cc5:('mov','al, byte ptr [edx + 0xba4]'),
 0x4a1ccd:('je','0x4a1f8d'),0x4a1f8d:('mov','ecx, dword ptr [ebp + 0x5c]'),
 0x4a1f94:('inc','ecx'),0x4a1f98:('mov','dword ptr [ebp + 0x5c], ecx')}
DISPATCH=(0x4a1caf,0x4a1e97,0x4a1caf,0x4a1eb2,0x4a1f8d,0x4a1f8d,0x4a1f05)
def verify(data):
 stores=stores_verify(data);admission=admission_verify(data)
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ops={i.address:(i.mnemonic,i.op_str) for i in cs.disasm(p.get_data(0x4a1000-0x400000,0x1649),0x4a1000)}
 for a,op in ASSOCIATIONS.items():
  if ops.get(a)!=op:raise ValueError('Advance admission association differs '+hex(a))
 dispatch=struct.unpack('<7I',p.get_data(0x4a264c-0x400000,28))
 if dispatch!=DISPATCH:raise ValueError('Advance admission switch table differs')
 return {'Advance_stores':stores,'actual_admission_ancestry':admission,
  'associations':{hex(a):list(op) for a,op in ASSOCIATIONS.items()},'dispatch':[hex(a) for a in dispatch],
  'scope':'Complete ordinary Advance with actual Unit admission0/2/7. Unit-kind1 Passive0 rejected switch for0/2; unsigned default continuation for7. No Process/preparation, production ownership, runtime or frame proof. Initial actor/type/House/diagnostic Cells and named Mark/occupation/notification effects supplied.'}
