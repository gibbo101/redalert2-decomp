#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Process/preparation with actual map/Building gate children."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_drive_process import verify as process_verify,RANGES as PROCESS
from verify_movement_gate import verify as gate_verify,RANGES as GATES
RANGES={**PROCESS,**GATES}
def verify(data):
 parent=process_verify(data);gate=gate_verify(data)
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ops={i.address:(i.mnemonic,i.op_str) for a,n in RANGES.items() for i in cs.disasm(p.get_data(a-0x400000,n),a)}
 for a,op in {0x4a0734:('call','0x4a2670'),0x4a0b70:('call','0x4a2670'),
  0x4a341e:('call','0x55acd0'),0x4a3423:('test','al, al'),0x4a3425:('jne','0x4a3433'),
  0x4a342a:('mov','al, 1'),0x4a3430:('ret','0xc'),0x4a3441:('call','0x4b8be0'),
  0x4a34eb:('call','dword ptr [eax + 0x194]')}.items():
  if ops.get(a)!=op:raise ValueError('Gate Process result/caller association differs '+hex(a))
 return {'process':parent,'gate':gate,'scope':'Complete ordinary Process/preparation/Advance with actual result-bearing gate interaction and unchanged complete Building/House/Mission/animation children on shared map slots/fallback. Initial records and caller animation changes supplied; admission remains supplied zero, next-Cell/Mark/occupation/notification/mission and failed pathfinder remain services. No occupied-route/runtime/startup/frame claim.'}
