#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Process callers of the ordinary Advance admission continuation."""
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_advance_admission import verify as advance_verify
ASSOCIATIONS={0x4a0666:('call','0x4a1000'),0x4a0753:('call','0x4a1000'),
 0x4a0b9e:('call','0x4a1000'),0x4a0734:('call','0x4a2670'),0x4a0b70:('call','0x4a2670')}
CALLERS=(0x4a066b,0x4a0758,0x4a0ba3)
def verify(data):
 parent=advance_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ops={i.address:(i.mnemonic,i.op_str) for i in cs.disasm(p.get_data(0x4a05f0-0x400000,0x5cb),0x4a05f0)}
 for a,op in ASSOCIATIONS.items():
  if ops.get(a)!=op:raise ValueError('Process Advance association differs '+hex(a))
 return {'actual_Advance_admission':parent,'Process_associations':{hex(a):list(op) for a,op in ASSOCIATIONS.items()},
  'scope':'Complete ordinary Process and actual Advance0/2/7 with later preparation/wait/retry. Supplied diagnostic actors/Cells/type/House and named services. No production shared-world, drawing, preview or runtime adoption.'}
