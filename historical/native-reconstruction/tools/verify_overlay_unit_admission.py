# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base Unit overlay branch and complete House control leaf."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_admission import verify as parent_verify
HOUSE=0x4f52f0
HOUSE_SIZE=0x23
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 raw=p.get_data(HOUSE-0x400000,HOUSE_SIZE);ins=list(cs.disasm(raw,HOUSE))
 if sum(i.size for i in ins)!=HOUSE_SIZE or ins[-1].mnemonic!='ret':raise ValueError('Incomplete House control leaf')
 expected={0x703331:('mov','eax, dword ptr [ebx + 0x44]'),0x70333d:('mov','ecx, dword ptr [0xa35dec]'),
  0x703346:('mov','al, byte ptr [esi + 0x27a]'),0x703377:('mov','al, byte ptr [esi + 0x278]'),
  0x703385:('mov','al, byte ptr [esi + 0x1fd]'),0x7033e9:('mov','cl, byte ptr [eax + 0x144]'),
  0x7033f3:('mov','cl, byte ptr [eax + 0x146]'),0x7033fd:('cmp','dword ptr [esi + 0x9c], 6')}
 ops={i.address:(i.mnemonic,i.op_str) for i in cs.disasm(p.get_data(0x703040-0x400000,0xb88),0x703040)}
 if any(ops.get(a)!=value for a,value in expected.items()):raise ValueError('Overlay admission fields differ')
 return dict(parent=parent,House_control_sha256=hashlib.sha256(raw).hexdigest(),House_control_instructions=len(ins),
  scope='Complete Unit admission with actual overlay branch and House control leaf; unpromoted/stationary ordinary actors. No crushing effects, movement, Process or runtime adoption.')
