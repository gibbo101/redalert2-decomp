#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin occupied passability, complete Cell children and actual actor kind slots."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_resident_cell import verify as cell,RANGES as CELL
from verify_unit_discovery import verify as membership,RANGES as MEMBERSHIP
KINDS={0x70a2d0:6,0x453c40:6,0x6e4b00:6}
RANGES={**CELL,**MEMBERSHIP,**KINDS}
DISPATCH={0x7addf8+0x2c:0x70a2d0,0x79cbbc+0x2c:0x453c40,0x7ad3cc+0x2c:0x6e4b00}
def verify(data):
 c,m=cell(data),membership(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in {0x478f40:0x1a9,**KINDS}.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete occupied Cell range')
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()};ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,target in DISPATCH.items():
  if p.get_data(a-0x400000,4)!=struct.pack('<I',target):raise ValueError('Occupied Cell kind dispatch differs')
 for a,op in {0x479032:('mov','esi, dword ptr [edi + 0xe4]'),0x47908a:('mov','dword ptr [edi + 0x4c], ebp'),
  0x47908d:('mov','esi, dword ptr [esi + 0x30]'),0x479094:('mov','dword ptr [edi + 0x4c], 0'),
  0x47909f:('mov','ecx, dword ptr [0xa3d290]')}.items():
  if ops.get(a)!=op:raise ValueError('Occupied Cell field/store association differs')
 return {'resident_cell':c,'membership':m,'ranges':ranges,'kind_dispatch':{hex(a):hex(v) for a,v in DISPATCH.items()},
  'scope':'Complete stable-list Unit/Building/Terrain occupied passability with actual map permission/lookup and kind leaves; complete resident Cell and membership children inspected for the join. Initial actor/type/House/scenario/Cell/registry/table inputs supplied. No construction/ownership, other actor kinds, bridge promotion, Process/runtime or frame parity.'}
