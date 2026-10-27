#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin Unit admission and actual ordinary terrain, registry and actor children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x703040:0xb88,0x4c8730:0x207,0x4c86e0:0x49,0x47a130:0x26,
 0x476ac0:0x56,0x548070:0x38,0x53d4f0:5,0x44d880:0x3d,
 0x594770:0x12,0x496b30:0x13,0x4e5580:0x51,0x4e5540:0x3f,0x4e5500:0x32,
 0x6c7430:7,0x453c60:7,0x70a2d0:6,0x453c40:6,0x636e30:0x38,0x4b8c90:0x2d,
 0x49fc70:0x96,0x40dbd0:0x29,0x6d7910:0x80,0x7133a0:0x27,0x713420:0x18,
 0x6cd670:0x1a,0x6d85a0:0x38,0x6df680:0xe,0x6d8540:0x55,
 0x6c12c0:8,0x705020:7,0x6df5c0:0x17}
DISPATCH={0x7addf8:{0x2c:0x70a2d0,0x3c:0x6c7430,0x80:0x6c12c0,0x84:0x705020,
 0x16c:0x594770,0x194:0x703040,0x198:0x4c8730,0x28c:0x6cd670,
 0x398:0x6d85a0,0x39c:0x6d8540},0x79cbbc:{0x2c:0x453c40,0x3c:0x6c7430,0x84:0x453c60,0x16c:0x594770},
 0x7a04cc:{0x10:0x49fc70,0x1c:0x53d4f0}}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied admission engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.OPTIONAL_HEADER.ImageBase!=0x400000 or p.FILE_HEADER.Machine!=0x14c:raise ValueError('Admission PE layout differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or (ins[-1].mnemonic!='ret' and a!=0x6c12c0):raise ValueError('Incomplete admission range '+hex(a))
  if a==0x6c12c0 and (ins[-1].mnemonic,ins[-1].op_str)!=('jmp','dword ptr [eax + 0x84]'):raise ValueError('Admission type tail differs')
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for vt,slots in DISPATCH.items():
  for off,target in slots.items():
   if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Admission dispatch differs')
 tables=p.get_data(0x40dbfc-0x400000,23)
 for kind in (1,6):
  if struct.unpack_from('<I',tables,4*tables[8+kind-1])[0]!=0x40dbf1:raise ValueError('Admission cast identity differs')
 if p.get_data(0x79a708-0x400000,8)!=struct.pack('<d',1.) or p.get_data(0x79a6f8-0x400000,8)!=struct.pack('<d',2.):raise ValueError('Admission veteran thresholds differ')
 if p.get_data(0x79a738-0x400000,4)!=bytes(4):raise ValueError('Admission zero speed constant differs')
 for a,op in {0x703182:('cmp','dword ptr [esp + 0x80], 8'),
  0x703245:('mov','eax, dword ptr [ebp]'),0x70325a:('call','dword ptr [eax + 0x198]'),
  0x703449:('mov','esi, dword ptr [ebx + 0xe8]'),0x70345d:('mov','esi, dword ptr [ebx + 0xe4]'),
  0x70393a:('je','0x703aa9'),0x703a9e:('and','al, 0xdf'),
  0x4c87c4:('mov','dword ptr [ebp], edx'),0x4c889f:('mov','byte ptr [edx], 1'),
  0x4c892c:('mov','dword ptr [eax], ecx'),0x53d4f0:('xor','eax, eax'),
  0x47a130:('mov','ax, word ptr [ecx + 0x116]'),0x703a1e:('cmp','eax, 0x24')}.items():
  if ops.get(a)!=op:raise ValueError('Admission association differs '+hex(a))
 return {'ranges':ranges,'dispatch':{hex(v):{hex(k):hex(t) for k,t in r.items()} for v,r in DISPATCH.items()},
  'cast_tables_sha256':hashlib.sha256(tables).hexdigest(),
  'scope':'Complete Unit root in overlay-free UnitType+B94 restriction -1 loading1 unpromoted/count704=0 profile, stationary Unit and ordinary/gate Building residents. Actual Foot terrain/Drive wrapper, registry/neighbor/word lookup, House/Mission/kind/cast/weapon/ability/Facing/Drive children. Initial records, directions, speed bits and associations supplied. Moving allied, crushing resident, overlay/special Building/combat, startup, Process/runtime join excluded. Numeric result codes unnamed.'}
