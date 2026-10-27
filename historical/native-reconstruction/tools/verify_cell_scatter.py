#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin Cell snapshot/dispatch and actual base cast/promotion/type children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x476920:0x19d,0x40dc20:0x29,0x7133a0:0x27,0x713420:0x18,
 0x6d7910:0x80,0x6c12c0:8,0x705020:7,0x453c60:7,
 0x70a2d0:6,0x453c40:6,0x6e4b00:6}
VTABLES={1:0x7addf8,6:0x79cbbc,36:0x7ad3cc}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied base Cell scatter engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Cell scatter PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or (ins[-1].mnemonic!='ret' and a!=0x6c12c0):raise ValueError('Incomplete Cell scatter range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,op in {0x476930:('mov','esi, dword ptr [edi + 0xe8]'),0x476938:('mov','esi, dword ptr [edi + 0xe4]'),
  0x476980:('mov','esi, dword ptr [edi + 0xe8]'),0x476988:('mov','esi, dword ptr [edi + 0xe4]'),
  0x47696b:('mov','esi, dword ptr [esi + 0x30]'),0x476a00:('mov','esi, dword ptr [esi + 0x30]'),
  0x47693e:('mov','al, byte ptr [esp + 0x34]'),0x476a30:('mov','al, byte ptr [esp + 0x38]'),
  0x476a83:('call','dword ptr [edx + 0x15c]'),0x476a63:('mov','edx, dword ptr [ecx + 0x194]'),
  0x476aba:('ret','0x10')}.items():
  if ops.get(a)!=op:raise ValueError('Cell scatter association differs '+hex(a))
 table=p.get_data(0x40dc4c-0x400000,23)
 kinds=[k for k in range(1,16) if struct.unpack_from('<I',table,4*table[8+k-1])[0]==0x40dc41]
 if kinds!=[1,2,6,15]:raise ValueError('Cell scatter Techno cast differs')
 dispatch={}
 for kind,vt in VTABLES.items():
  slots={off:struct.unpack('<I',p.get_data(vt+off-0x400000,4))[0] for off in (0x2c,0x15c)}
  if slots[0x2c]!={1:0x70a2d0,6:0x453c40,36:0x6e4b00}[kind]:raise ValueError('Cell scatter kind dispatch differs')
  dispatch[str(kind)]={hex(k):hex(v) for k,v in slots.items()}
 for a,value in ((0x79a708,1.),(0x79a6f8,2.)):
  if p.get_data(a-0x400000,8)!=struct.pack('<d',value):raise ValueError('Promotion threshold differs')
 grow=struct.unpack('<I',p.get_data(0x79db84-0x400000,4))[0]
 if grow!=0x40cd40:raise ValueError('Cell scratch growth dispatch differs')
 return dict(ranges=ranges,dispatch=dispatch,Techno_cast_sha256=hashlib.sha256(table).hexdigest(),
  supplied_services=['vector growth 40CD40','heap disposal 781D3B','member +15C dispatch'],
  Unit_scatter_dispatch_inspection_only=dispatch['1']['0x15c'],
  scope='Complete Cell root with actual Techno cast, promotion predicates, ability3 and Unit/Building type children. Supplied initial Cells/Next/types/House/rules and heap/member Scatter services. No Unit Scatter execution, Advance6/Process/world/runtime or frame claim.')
