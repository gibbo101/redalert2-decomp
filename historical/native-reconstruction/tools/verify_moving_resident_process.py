#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete result-2 wait/force-single callers and narrow Advance dispatch."""
import struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_drive_resident_process import verify as parent_verify
from verify_ground_drive_admission_process import RANGES
from verify_moving_unit_admission import verify as motion_verify
ASSOCIATIONS={
 0x4a3646:('cmp','eax, 2'),0x4a365a:('jne','0x4a3689'),
 0x4a365c:('mov','byte ptr [eax + 0x5a1], 1'),0x4a3677:('mov','ecx, dword ptr [ecx + 0x13d0]'),
 0x4a367d:('mov','dword ptr [edx], eax'),0x4a367f:('mov','eax, dword ptr [esp + 0x54]'),
 0x4a3683:('mov','dword ptr [edx + 4], eax'),0x4a3686:('mov','dword ptr [edx + 8], ecx'),
 0x4a36a9:('jge','0x4a36b5'),0x4a36af:('jne','0x4a3a98'),
 0x4a36da:('jge','0x4a36e6'),0x4a36e0:('jne','0x4a39c8'),
 0x4a36e6:('mov','bl, 1'),0x4a39c8:('xor','bl, bl'),0x4a39f7:('inc','edx'),
 0x4a3a01:('push','edx'),0x4a3a05:('call','0x4c3000'),
 0x4a3aa3:('je','0x4a3bfd'),0x4a3c7c:('mov','byte ptr [ecx + 0x57a], 0'),
 0x4a3c83:('mov','dword ptr [ebp + 0x58], 0xffffffff'),
 0x4a3f97:('mov','al, byte ptr [esp + 0x68]'),0x4a3f9d:('je','0x4a3fa1'),0x4a3f9f:('mov','esi, ebx'),
 0x4a41c7:('cmp','esi, 2'),0x4a41d4:('push','1'),0x4a41da:('call','0x4a2670'),
 0x4a1ca8:('jmp','dword ptr [eax*4 + 0x4a264c]'),0x4a1cb7:('cmp','eax, 1'),
 0x4a1cc5:('mov','al, byte ptr [edx + 0xba4]'),0x4a1ccd:('je','0x4a1f8d')}
def verify(data):
 parent=parent_verify(data);motion=motion_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ops={i.address:(i.mnemonic,i.op_str) for a,n in RANGES.items() for i in cs.disasm(p.get_data(a-0x400000,n),a)}
 for a,op in ASSOCIATIONS.items():
  if ops.get(a)!=op:raise ValueError('Moving-resident Process association differs '+hex(a))
 dispatch=struct.unpack('<7I',p.get_data(0x4a264c-0x400000,28))
 if dispatch[0]!=dispatch[2] or dispatch[2]!=0x4a1caf:raise ValueError('Moving-resident Advance dispatch differs')
 return {'resident_Process':parent,'moving_admission':motion,'associations':{hex(a):list(op) for a,op in ASSOCIATIONS.items()},
  'Advance_dispatch':[hex(a) for a in dispatch],
  'scope':'Complete ordinary Process with actual result2 through both preparation callers, wait/retry/failed-pathfinder option selection and force-single recursion; Advance2 only at Unit-kind1 Passive0 rejected switch. Initial motion/wait/rule/padding/type/House/diagnostic Cells and named failed-pathfinder/accessibility/mission/Mark effects supplied. No live actor1 Process, owned membership, runtime or frame claim.'}
