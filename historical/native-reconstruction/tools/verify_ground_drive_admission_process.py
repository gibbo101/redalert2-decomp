#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete ordinary Process with actual gate/admission/next-Cell children."""
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_drive_gate_process import verify as gate_verify,RANGES as GATE
from verify_unit_admission import verify as admission_verify,RANGES as ADMISSION
from verify_unit_next_cell import verify as next_verify,RANGES as NEXT
RANGES={**GATE,**ADMISSION,**NEXT}
def verify(data):
 gate=gate_verify(data);admission=admission_verify(data);next_cell=next_verify(data)
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ops={i.address:(i.mnemonic,i.op_str) for a,n in RANGES.items() for i in cs.disasm(p.get_data(a-0x400000,n),a)}
 for a,op in {0x4a35f9:('call','0x55acd0'),0x4a3c11:('mov','dword ptr [edx + 0x4d0], 0xffffffff'),
  0x4a40e4:('call','dword ptr [edi + 0x194]'),0x4a416f:('call','0x55acd0'),
  0x4a417d:('mov','dword ptr [eax + 0x4d0], edi'),0x4a4183:('mov','dword ptr [ebp + 0x58], edi'),
  0x4a45a5:('mov','dword ptr [edx + 0x528], edi'),0x4a45d6:('mov','dword ptr [ecx + 0x52c], edi'),
  0x4a4513:('call','0x4a2670'),0x4a3e73:('call','dword ptr [edx + 0x4b8]'),
  0x4a4713:('call','dword ptr [edx + 0x4c8]')}.items():
  if ops.get(a)!=op:raise ValueError('Admission Process caller association differs '+hex(a))
 return {'gate_Process':gate,'admission':admission,'next_Cell':next_cell,
  'scope':'Complete ordinary Process/preparation/Advance with actual 0/3/7 preparation admission, zero-result Advance switch admission, gates and warning1/low-five-zero next-Cell on shared Cells/fallback. Initial actor/type/House/Cell/direction/speed and animation records supplied. Mark/occupation/notification/mission and failed pathfinder remain services. Other admission codes and warning/crush paths excluded; runtime not promoted.'}
