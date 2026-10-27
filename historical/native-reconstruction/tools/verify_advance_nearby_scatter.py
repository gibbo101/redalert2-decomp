# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Advance root with actual admission and Cell/Unit/nearby children."""
from verify_advance_cell_scatter import verify as child_verify,RANGES as CHILD,TABLES as CT
from verify_ground_drive_advance import RANGES as ADVANCE
from verify_ground_movement_placement import RANGES as PLACEMENT
from verify_advance_admission import verify as advance_verify
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
RANGES={**CHILD,**PLACEMENT,**ADVANCE,0x41b470:7,0x70b5e0:6,0x4916d0:116}
TABLES={**CT,0x7a0180:768,0x7a00a0:112,0x7a05c0:24,0x4a264c:28,0x851ac0:64,0x7ae328+0x2c:4}
def verify(data):
 child=child_verify(data);advance=advance_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for t,n in advance['Advance_stores']['advance_ancestor']['tables'].items():TABLES[int(t,16)]=n['bytes']
 raw=p.get_data(0x4916d0-0x400000,116);ins=list(cs.disasm(raw,0x4916d0))
 if sum(i.size for i in ins)!=116 or ins[-1].mnemonic!='ret':raise ValueError('Incomplete direction initializer')
 ops={i.address:(i.mnemonic,i.op_str) for i in cs.disasm(p.get_data(0x4a1000-0x400000,0x1649),0x4a1000)}
 for a,op in {0x4a164f:('mov','word ptr [esp + 0x14], cx'),0x4a1654:('mov','edx, dword ptr [esp + 0x14]'),0x4a1f98:('mov','dword ptr [ebp + 0x5c], ecx')}.items():
  if ops.get(a)!=op:raise ValueError('Advance caller scratch/continuation differs')
 return dict(child=child,advance=advance,root='0x4a1000',
  extra_complete_roots={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in ((0x41b470,7),(0x70b5e0,6),(0x4916d0,116))},
  tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items() if a!=0x851ac0},
  initialized_direction_storage='0x851ac0/64 bytes; actual initializer output, not PE file data',
  scope='Complete ordinary Advance with actual admission0/2/6/7 and actual Cell/Unit/nearby/destination children on one shared guest. Initial records, incoming scratch high word, Mark/occupation/notification, heap/atomic and destination padding supplied. No Process/production world/preview/runtime/SDL.')
