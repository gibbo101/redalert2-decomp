#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete prepared Process with actual Unit map effects."""
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_prepared_drive_state import verify as drive,RANGES as DRIVE
from verify_occupied_cell import verify as occupied,RANGES as OCCUPIED
RANGES={}
for group in (DRIVE,OCCUPIED):
 for address,size in group.items():RANGES[address]=max(size,RANGES.get(address,0))
def verify(data):
 d,o=drive(data),occupied(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ins=list(cs.disasm(p.get_data(0x4a16a6-0x400000,0x5d),0x4a16a6));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 for a,op in {0x4a16ab:('call','dword ptr [edx + 0xbc]'),0x4a16e9:('call','dword ptr [edx + 0xec]'),0x4a16f2:('mov','byte ptr [ecx + 0x5a0], 0'),0x4a16fc:('mov','byte ptr [edx + 0x5a1], 0')}.items():
  if ops.get(a)!=op:raise ValueError('Committed occupation eligibility association differs')
 return {'drive':d,'occupied':o,'scope':'Same-guest finalized shared map, actual ordinary Process/preparation/Advance, Unit eligibility/Mark/membership/discovery/occupation/Cell recalculation, height/ramp writers and body/shadow poses. Single nonbridge Unit, otherwise empty actors, null Tag/loading1, traversed Cells overlay-free. Initial records/routes/admission/reservation/mission/ownership supplied. No runtime/startup/frame claim.'}
