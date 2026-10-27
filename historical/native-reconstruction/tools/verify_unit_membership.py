#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin Unit map/Cell membership, stock foundation and joined Mark/occupation."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_mark import verify as verify_mark,RANGES as MARK,DISPATCH as MD
from verify_unit_occupation import verify as verify_occupation,RANGES as OCC,DISPATCH as OD
COMPLETE={0x54ab70:0x3f4,0x54af70:0x367,0x473b30:0x1e9,0x473d20:0x107,
 0x5d4470:0x75,0x5d5d90:0x5b,0x482e10:0x47,0x41b470:7}
RANGES={**MARK,**OCC,**COMPLETE}
DISPATCH={**MD,**OD,0x7addf8+0x100:0x5d4470,0x7addf8+0xbc:0x41b470,
 0x7addf8+0x180:0x6c2440,0x7ae328+0x90:0x5d5d90}
def verify(data):
 mark=verify_mark(data);occupation=verify_occupation(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in COMPLETE.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Unit membership range '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()};ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,target in DISPATCH.items():
  if p.get_data(a-0x400000,4)!=struct.pack('<I',target):raise ValueError('Unit membership dispatch differs')
 for a,op in {0x54ab99:('mov','cl, byte ptr [eax + 0x205]'),0x54ac1c:('mov','ecx, dword ptr [eax + esi*4]'),
  0x473ba7:('cmp','dword ptr [esi + 0x30], ebp'),0x473baf:('mov','dword ptr [ebx + 0xe4], ebp'),
  0x473d80:('mov','dword ptr [esi + 0x30], 0'),0x41b470:('mov','al, byte ptr [ecx + 0x5a0]'),
  0x5d5dbc:('mov','dword ptr [0xa72fb0], eax'),0x5d5dd4:('mov','dword ptr [0xa72fb4], ecx')}.items():
  if ops.get(a)!=op:raise ValueError('Unit membership field/order association differs')
 return {'mark':mark,'occupation':occupation,'ranges':ranges,'dispatch':{hex(a):hex(n) for a,n in DISPATCH.items()},
  'scope':'Complete map/Cell insert/remove for Unit kind1, nonnull UnitType/Drive layer2, stock lazy single-Cell foundation and 32-slot copy; joined complete Foot/Techno/Object Mark and occupation with actual shared map/floor. Safe combined map slot domain only. Initial actor/type/house/Cell/table/global records, heap/atexit effects, visibility/notification/recalculation and event effects supplied. No Process/runtime, construction/startup, admission/reservation, bridge promotion or frame parity.'}
