#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base Techno old-sight removal."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
START,SIZE=0x6d5e90,0xa5
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Techno sight-removal engine required')
 p=pefile.PE(data=data);raw=p.get_data(START-0x400000,SIZE);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,START));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=SIZE or ops.get(0x6d5f32)!=('ret','0x10'):raise ValueError('Incomplete Techno sight-removal range')
 expected={0x6d5e90:('mov','al, byte ptr [ecx + 0x32d]'),0x6d5ea5:('mov','eax, dword ptr [esi + 0x34]'),0x6d5eae:('test','dl, dl'),0x6d5eb2:('mov','al, byte ptr [ecx + 0x1e4]'),0x6d5ebc:('mov','eax, dword ptr [ecx + 0x1f4]'),0x6d5ec2:('mov','byte ptr [ecx + 0x1e4], 0'),0x6d5ecd:('mov','dl, byte ptr [esp + 0x10]'),0x6d5f1f:('add','ecx, 0x1e8'),0x6d5f2c:('call','0x54a110')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Techno sight-removal association differs '+hex(a))
 if p.get_data(0x7a3540+0x41c-0x400000,4)!=struct.pack('<I',START):raise ValueError('Infantry sight-removal vtable association differs')
 return dict(range={hex(START):dict(bytes=SIZE,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())},scope='Complete base6D5E90 old-sight removal. Actual actor/owner/country fields and ordered active clear; reveal-area54A110 supplied with exact House and final child argument1. Visibility increment remains separate.')
