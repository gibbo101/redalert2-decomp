# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin ordinary queued Walk preparation and actual head/current-Cell children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_walk_head as head
import verify_walk_arrival as arrival
EXTRA={0x5d47d0:0x22,0x5d51e0:0x57,0x41b630:0x19,0x4916d0:0x74}
RANGES={**head.RANGES,**arrival.RANGES,**EXTRA}
TABLES={**head.TABLES,**arrival.parent.TABLES,0x79b628:16}
SERVICES={0x548000:'coordinate Cell',0x548070:'packed Cell',0x55a280:'floor',
 0x503190:'Infantry admission result0',0x508980:'speed',0x4c2e60:'Mark',0x47bb30:'dirty',
 0x500aa0:'notification174',0x501ce0:'destination410',0x508750:'reset4D0'}
def verify(data):
 base=dict(head=head.verify(data),arrival=arrival.verify(data));p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in RANGES.items():
  ins=list(cs.disasm(p.get_data(a-0x400000,n),a));ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
  if a in EXTRA:
   if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete queued Walk child '+hex(a))
   ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest())
 for a,op in {0x71e907:('and','esi, 7'),0x71e9bb:('xor','edx, eax'),0x71e9cf:('call','0x5d47d0'),
  0x71e9ed:('call','dword ptr [esi + 0x194]'),0x71ef77:('call','0x71f590'),
  0x5d520a:('call','0x548000'),0x5d522d:('call','0x548000')}.items():
  if ops.get(a)!=op:raise ValueError('Queued Walk association differs '+hex(a))
 for off,target in ((0x1a4,0x5d51e0),(0x194,0x503190)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Queued Infantry dispatch differs')
 return dict(parent=base,extra_ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  initialized_direction_storage='4916D0 ->851AC0/64 bytes',services={hex(a):s for a,s in SERVICES.items()},
  scope='Complete ordinary queued Walk Process result0 with actual head, Infantry occupation, selector, level and double current-Cell getter. Admission, speed, Mark, floor/map, notification/destination/reset and initial records/seeding supplied. Route finding, special8 and nonzero admission refused. No production/SDL walking/objectives.')
