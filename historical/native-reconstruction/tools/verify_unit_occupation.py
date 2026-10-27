#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base Unit occupation virtuals and actual map/floor children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_map_floor_height import verify as verify_floor,RANGES as FLOOR
COMPLETE={0x707980:0x5e,0x7079e0:0x53,0x548000:0x68}
RANGES={**FLOOR,**COMPLETE}
DISPATCH={0x7addf8+0xe8:0x707980,0x7addf8+0xec:0x7079e0}
def verify(data):
 floor=verify_floor(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in COMPLETE.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Unit occupation range '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,target in DISPATCH.items():
  if p.get_data(a-0x400000,4)!=struct.pack('<I',target):raise ValueError('Unit occupation dispatch differs')
 for a,op in {0x7079a7:('add','eax, edx'),0x7079a9:('cmp','eax, ecx'),
  0x7079b3:('test','ah, 1'),0x7079c0:('mov','dword ptr [edi + 0x128], eax'),
  0x7079d3:('mov','dword ptr [edi + 0x124], eax'),0x707a15:('mov','dword ptr [edi + 0x128], eax'),
  0x707a28:('mov','dword ptr [edi + 0x124], eax')}.items():
  if ops.get(a)!=op:raise ValueError('Unit occupation field/width association differs')
 return {'floor':floor,'ranges':ranges,'dispatch':{hex(a):hex(n) for a,n in DISPATCH.items()},
  'scope':'Complete Unit occupation mark/unmark with actual coordinate lookup/map floor/Cell arithmetic. Saved Cell identity, signed wrapped floor+threshold, delayed coordinate/flag reads, asymmetric bridge gate and full dword stores. Initial Cell/map/global/occupation state supplied; optional boundary mutations explicitly diagnostic. No Object/Techno/Foot Mark, membership, admission, reservation, actor construction, startup, runtime integration or frame parity.'}
