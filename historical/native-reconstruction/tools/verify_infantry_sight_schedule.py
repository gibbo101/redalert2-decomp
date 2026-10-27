#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the exact Infantry argument-2 sight-scheduling interior suffix."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
START,END=0x501b69,0x501bd0
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Infantry sight scheduler engine required')
 p=pefile.PE(data=data);raw=p.get_data(START-0x400000,END-START);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,START));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=len(raw):raise ValueError('Incomplete Infantry sight scheduler range')
 expected={0x501b6d:('call','dword ptr [edx + 0x1d4]'),0x501b7f:('call','dword ptr [eax + 0x41c]'),0x501b91:('call','dword ptr [edx + 0x418]'),0x501ba7:('mov','ecx, dword ptr [esi + 0x1f4]'),0x501bb0:('add','ecx, 3'),0x501bcb:('call','0x54a550')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Infantry sight scheduler association differs '+hex(a))
 vtable=0x7a3540
 for off,target in ((0x174,0x500aa0),(0x1d4,0x594c50),(0x418,0x6d5c30),(0x41c,0x6d5e90)):
  if p.get_data(vtable+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry sight scheduler vtable differs '+hex(off))
 return dict(range={hex(START):dict(bytes=len(raw),instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())},vtable=hashlib.sha256(p.get_data(vtable-0x400000,0x420)).hexdigest(),scope='Exact base501B69..501BCF argument-2 interior suffix: supplied +1D4, then +41C sight removal, +418 sight addition and supplied54A550 post-sight call. Entry path and children remain separate.')
