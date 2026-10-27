#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base gate interaction and actual House/Mission/animation children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x55acd0:0x95,0x44d7d0:0xa1,0x44d880:0x3d,0x4e5580:0x51,
 0x496ab0:0x14,0x496b30:0x13,0x496b50:0x14,0x594710:0x5d,
 0x594c50:0x5c,0x594770:0x12,0x594cb0:0x65,0x6c7430:7,
 0x70a2d0:6,0x453c40:6,0x6e4b00:6,0x410240:3}
DISPATCH={0x79cbbc:{0x2c:0x453c40,0x3c:0x6c7430,0x16c:0x594770,
 0x1d0:0x594cb0,0x1d4:0x594c50,0x1d8:0x594710},
 0x7addf8:{0x2c:0x70a2d0,0x3c:0x6c7430},0x7ad3cc:{0x2c:0x6e4b00,0x3c:0x410240}}
CALLER={0x4a2670:0x20b5}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={};callers={}
 if p.OPTIONAL_HEADER.ImageBase!=0x400000 or p.FILE_HEADER.Machine!=0x14c:raise ValueError('Gate PE layout differs')
 for a,n in {**RANGES,**CALLER}.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete gate range '+hex(a))
  (callers if a in CALLER else ranges)[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for vt,slots in DISPATCH.items():
  for off,target in slots.items():
   if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Gate dispatch differs')
 for a,op in {0x70a2d0:('mov','eax, 1'),0x453c40:('mov','eax, 6'),
  0x6e4b00:('mov','eax, 0x24'),0x55ad03:('mov','esi, dword ptr [eax + 0xe4]'),
  0x55ad12:('cmp','edi, esi'),0x55ad4d:('mov','esi, dword ptr [esi + 0x30]'),
  0x55acf8:('mov','dword ptr [0xa6fa1c], eax'),0x44d82d:('call','dword ptr [edx + 0x16c]'),
  0x4e55c1:('shl','edx, cl'),0x496b3c:('cmp','dl, al'),
  0x59475d:('mov','eax, dword ptr [esp + 4]'),0x594c84:('mov','eax, dword ptr [esp + 8]'),
  0x4a341e:('call','0x55acd0'),0x4a3423:('test','al, al'),
  0x4a3425:('jne','0x4a3433'),0x4a342a:('mov','al, 1'),0x4a3430:('ret','0xc')}.items():
  if ops.get(a)!=op:raise ValueError('Gate field/caller association differs '+hex(a))
 return {'ranges':ranges,'caller_inspection_only':callers,
  'dispatch':{hex(vt):{hex(k):hex(v) for k,v in row.items()} for vt,row in DISPATCH.items()},
  'scope':'Complete map gate interaction, both Building helpers, House/object alliance, exact animation-byte predicates and actual Mission Set/Queue(second arg zero)/Commence. Stable primary lists, actual kinds Unit1/Building6/Terrain36 with returned-value checks, initial records and opaque child-entry timer padding supplied. Gate animation progression, admission and complete Process join/runtime excluded. Caller inspected only.'}
