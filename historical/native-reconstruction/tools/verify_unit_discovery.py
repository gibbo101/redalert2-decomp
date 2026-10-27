#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin base visibility/discovery, its third stock numeric chain and dispatch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ramp_geometry import verify as verify_geometry,RANGES as GEOMETRY
from verify_unit_membership import verify as verify_membership,RANGES as MEMBERSHIP
NUMERIC={0x544000:40,0x544030:19,0x544050:19,0x544070:19,0x544090:19,
 0x5440b0:19,0x5440d0:49,0x544110:33,0x544140:44,0x544170:39}
OUTPUTS={0xa6f240:8,0xa6fb48:8,0xa6f9e8:8,0xa6f9e0:8,0xa6f810:8,
 0xa6f210:8,0xa6fc30:4,0xa6f818:8,0xa6f9d8:8,0xa6fb40:4}
COMPLETE={0x568140:0x135,0x5683c0:0x158,0x476ac0:0x56,0x548070:0x38,
 0x491620:172,0x6c2440:0xdf,0x5d4230:14,0x4f52f0:0x23,
 0x594770:18,0x594cb0:0x65}
RANGES={**GEOMETRY,**MEMBERSHIP,**NUMERIC,**COMPLETE}
DISPATCH={0x7addf8+0x180:0x6c2440,0x7addf8+0x16c:0x594770,0x7addf8+0x1d0:0x594cb0}
CONSTANTS={0x7a58f8:60.,0x7a5900:0.017453292519943295}
def verify(data):
 geometry=verify_geometry(data);membership=verify_membership(data)
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in {**NUMERIC,**COMPLETE}.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete visibility/discovery range '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,v in CONSTANTS.items():
  if p.get_data(a-0x400000,8)!=struct.pack('<d',v):raise ValueError('Visibility numeric constant differs')
 for a,target in DISPATCH.items():
  if p.get_data(a-0x400000,4)!=struct.pack('<I',target):raise ValueError('Discovery dispatch differs')
 for a,op in {0x56814c:('idiv','dword ptr [0xa6fc30]'),0x5681d2:('test','byte ptr [ecx + 0x12c], 8'),
  0x568473:('test','byte ptr [eax + 0x140], 2'),0x5440fb:('mov','dword ptr [0xa6fc30], eax'),
  0x6c2470:('mov','byte ptr [esi + 0x374], bl'),0x6c24fd:('mov','eax, dword ptr [esi + 0x1b4]'),
  0x594ce4:('mov','dword ptr [esi + 0xa0], eax')}.items():
  if ops.get(a)!=op:raise ValueError('Visibility/discovery field association differs')
 return {'geometry':geometry,'membership':membership,'ranges':ranges,
  'constants':{hex(a):v for a,v in CONSTANTS.items()},'dispatch':{hex(a):hex(v) for a,v in DISPATCH.items()},
  'scope':'Complete primary/secondary map predicates, actual direction initializer/neighbor/word lookup, third stock numeric chain and Unit Techno/Object/House/Mission discovery. QueueMission second argument zero only. Initial records/globals supplied; optional Tag, occupied-Cell recalculation and atexit effects supplied. No fog renderer, startup, Process/runtime promotion or frame parity.'}
