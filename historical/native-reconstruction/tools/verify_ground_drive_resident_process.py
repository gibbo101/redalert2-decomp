#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin result-6 preparation callers without widening the earlier Process proof."""
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_drive_admission_process import verify as parent_verify,RANGES
ASSOCIATIONS={
 0x4a072f:('push','1'),0x4a0734:('call','0x4a2670'),
 0x4a0b67:('push','1'),0x4a0b70:('call','0x4a2670'),
 0x4a370f:('mov','al, byte ptr [esp + 0x64]'),0x4a3718:('je','0x4a373b'),
 0x4a371a:('mov','dword ptr [ecx + 0x4d0], esi'),
 0x4a3732:('mov','eax, dword ptr [esp + 0x48]'),
 0x4a420b:('test','bl, bl'),0x4a420d:('je','0x4a4234'),
 0x4a420f:('mov','dword ptr [ecx + 0x4d0], 0xffffffff'),
 0x4a422b:('mov','eax, dword ptr [esp + 0x54]'),
 0x4a4502:('mov','dword ptr [edx + 4], eax'),
 0x4a4505:('push','0'),0x4a4507:('push','0'),
 0x4a4513:('call','0x4a2670')}
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ops={i.address:(i.mnemonic,i.op_str) for a,n in RANGES.items() for i in cs.disasm(p.get_data(a-0x400000,n),a)}
 for a,op in ASSOCIATIONS.items():
  if ops.get(a)!=op:raise ValueError('Resident Process association differs '+hex(a))
 return {'admission_Process':parent,'associations':{hex(a):list(op) for a,op in ASSOCIATIONS.items()},
  'scope':'Complete ordinary Process with actual stationary Unit admission, both preparation flag-1 result-6 retry callers and recursive flag-0 empty-queue retry. Distinct opaque padding supplied at its two load boundaries. Initial records/shared diagnostic Cells/House/type/settled Facing/Drive supplied; Mark/occupation/notification/mission/pathfinder remain services. Scatter/close-enough/nonzero Advance admission, production membership/runtime/startup/frames excluded.'}
