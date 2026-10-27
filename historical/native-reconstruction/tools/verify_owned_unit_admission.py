#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin one-guest prepared map, mutable membership and actual Unit decisions."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_membership_drive import verify as membership,RANGES as MEMBERSHIP
from verify_ground_drive_admission_process import verify as admission,RANGES as ADMISSION
RANGES={}
for group in (MEMBERSHIP,ADMISSION):
 for address,size in group.items():RANGES[address]=max(size,RANGES.get(address,0))
def verify(data):
 m,a=membership(data),admission(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 fields={}
 for start,size,ops in (
  (0x70a607,3,{0x70a607:('or','edi, 0xffffffff')}),
  (0x70a61b,6,{0x70a61b:('mov','dword ptr [esi + 0xb94], edi')}),
  (0x70ad45,0x20,{0x70ad45:('mov','edx, dword ptr [edi + 0xb94]'),
   0x70ad4e:('push','0x7f9328'),0x70ad5a:('call','0x46a970'),
   0x70ad5f:('mov','dword ptr [edi + 0xb94], eax')})):
  raw=p.get_data(start-0x400000,size);ins=list(cs.disasm(raw,start));found={i.address:(i.mnemonic,i.op_str) for i in ins}
  if sum(i.size for i in ins)!=size or any(found.get(k)!=v for k,v in ops.items()):raise ValueError('Base restriction association differs')
  fields[hex(start)]={'bytes':size,'sha256':hashlib.sha256(raw).hexdigest()}
 if p.get_data(0x7f9328-0x400000,21)!=b'MovementRestrictedTo\0':raise ValueError('Base restriction INI key differs')
 return {'membership':m,'admission':a,'restriction_B94_scoped_inspection':fields,
  'scope':'Same guest finalized shared map, ordinary Process, actual gates/admission/next-Cell, Unit Mark/membership/discovery/occupation/recalculation, floor/ramp and both poses. One nonbridge Unit, otherwise empty lists, loading1/null Tag. Initial actor/type/House/registry/direction/speed/owner associations supplied; UnitType+B94 is the MovementRestrictedTo restriction, not MovementZone. Type/House construction, stationary residents, gate animation, pathfinding, runtime command and full-frame parity excluded.'}
