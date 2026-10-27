# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
ENTRY=0x6d1480;SIZE=138
CODE='91c277ae008125e0701002bb8d2de6ef74e1f53fc43a5ff60cba888680f028cc'
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Exact supplied sprite selection executable required')
 pe=pefile.PE(data=data);raw=pe.get_data(ENTRY-0x400000,SIZE);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,ENTRY))
 if hashlib.sha256(raw).hexdigest()!=CODE or len(ins)!=46 or sum(i.size for i in ins)!=SIZE or ins[-1].mnemonic!='ret':raise ValueError('Complete sprite selector differs')
 return dict(entry=hex(ENTRY),bytes=SIZE,instructions=len(ins),sha256=CODE,scope='Complete6D1480; virtual Type80/owner predicate/CC children and initial records supplied')
