# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact inactive-track Process target interior and actual null-destination tree."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_destination import verify as destination_verify,RANGES as DESTINATION,TABLES as DESTINATION_TABLES

BLOCK=0x4a0770
CONTINUE=0x4a0879
EXTRA={BLOCK:CONTINUE-BLOCK,0x41b320:0x3d,0x4cd9b0:15}
RANGES={**DESTINATION,**EXTRA}
TABLES={**DESTINATION_TABLES,0x7addf8:0x418}

def verify(data):
 parent=destination_verify(data)
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Unaligned idle target range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for off,target in ((0x1a0,0x41b320),(0x410,0x7053f0),(0x414,0x6fd630)):
  if p.get_data(0x7addf8+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Idle target dispatch differs')
 for a,op in {0x4a0782:('cmp','eax, 0xb'),0x4a078f:('mov','ebp, dword ptr [ecx + 0x494]'),
  0x4a0797:('add','ebp, 0x24'),0x4a079a:('call','dword ptr [eax + 0x1a0]'),
  0x4a07a3:('cmp','cx, word ptr [ebp]'),0x4a07ad:('cmp','dx, word ptr [ebp + 2]'),
  0x4a07b6:('cmp','dword ptr [ecx + 0x488], ebx'),0x4a07dc:('cmp','dword ptr [ecx + 0x98], 5'),
  0x4a07e9:('cmp','byte ptr [esi + 0x5f], bl'),0x4a0833:('cmp','ebp, dword ptr [esi + 0x38]'),
  0x4a085a:('call','0x4cd9b0'),0x4a0867:('call','dword ptr [edx + 0x414]'),
  0x4a086d:('xor','al, al')}.items():
  if ops.get(a)!=op:raise ValueError('Idle target operation differs '+hex(a))
 return dict(destination=parent,ranges=ranges,
  tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},
  scope='Inactive-track Process interior4A0770 through pre-rotation continuation4A0879 or actual early AL0 return. Actual kind/actor Cell words/direct target words, raw mission5 and full destination equality, null Unit/Foot/Drive destination or ordered clears. Mission414 effect, initial records and entry context supplied. Not complete Process, Advance/world/preview/SDL integration.')
