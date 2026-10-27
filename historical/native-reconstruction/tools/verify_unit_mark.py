#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Unit-kind Object/Techno/Foot Mark and actual scalar children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x4c2e60:0x8a,0x6c2550:0x33,0x5d4160:0xce,0x40dc20:0x29,
 0x6d3e50:0x4f,0x6c7420:0xa,0x41b320:0x3d,0x4ca130:0x25,
 0x4a47e0:8,0x70a2d0:6,0x6c12c0:8,0x705020:7,0x5d36e0:0x18,0x4e09a0:0x2e}
DISPATCH={0x7addf8+0x11c:0x4c2e60,0x7addf8+0x2c:0x70a2d0,
 0x7addf8+0x38:0x6c7420,0x7addf8+0x74:0x4ca130,0x7addf8+0x80:0x6c12c0,
 0x7addf8+0x84:0x705020,0x7addf8+0x12c:0x5d36e0,0x7addf8+0x1a0:0x41b320,
 0x7addf8+0x2a0:0x6d3e50,0x7a04cc+0x74:0x4a47e0}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied base engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Unit Mark PE layout differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or (ins[-1].mnemonic!='ret' and a!=0x6c12c0):raise ValueError('Incomplete Unit Mark range '+hex(a))
  if a==0x6c12c0 and (ins[-1].mnemonic,ins[-1].op_str)!=('jmp','dword ptr [eax + 0x84]'):raise ValueError('Unit type tail dispatch differs')
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()};ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,target in DISPATCH.items():
  if p.get_data(a-0x400000,4)!=struct.pack('<I',target):raise ValueError('Unit Mark dispatch differs')
 tables=p.get_data(0x40dc4c-0x400000,23)
 if hashlib.sha256(tables).hexdigest()!='6e2d5904519415bad02f84d780e8e3add70b818d5848dbb175fd4c406e4e6cb5':raise ValueError('Techno-cast tables differ')
 # Pin the extracted tables by hash, without incorporating their bytes. Unit
 # kind 1 selects the identity return; other kinds are outside native scope.
 if tables[8]!=0 or struct.unpack_from('<I',tables)[0]!=0x40dc41:raise ValueError('Unit techno-cast identity differs')
 for a,op in {0x4c2e69:('cmp','edi, 2'),0x5d4201:('mov','byte ptr [esi + 0x74], 1'),
  0x5d421d:('mov','byte ptr [esi + 0x74], bl'),0x6c2561:('mov','al, byte ptr [esi + 0x370]'),
  0x5d36e7:('mov','byte ptr [ecx + 0x75], 1'),0x6d3e91:('mov','eax, dword ptr [edi + 0x598]')}.items():
  if ops.get(a)!=op:raise ValueError('Unit Mark field association differs')
 return {'ranges':ranges,'dispatch':{hex(a):hex(n) for a,n in DISPATCH.items()},'cast_tables_sha256':hashlib.sha256(tables).hexdigest(),
  'scope':'Complete Object/Techno/Foot Mark in Unit kind 1 with actual kind/cast, image/type/owner/word-coordinate, nonnull Drive layer 2 and Object/map redraw children. Initial actor/type/house/locomotor/tactical records and type-null option supplied. Map insert/remove and special-event effects supplied. No actual membership/occupation/Process join, construction/startup, runtime or frame parity.'}
