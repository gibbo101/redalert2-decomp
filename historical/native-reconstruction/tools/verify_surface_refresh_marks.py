# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base complete6324A0 and634030 parent/getter composition."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_surface_refresh import verify as parent_verify,RANGES as PARENT
EXTRA={0x6324a0:0x173};RANGES={**PARENT,**EXTRA}
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);a=0x6324a0;b=p.get_data(a-0x400000,0x173);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a));sha=hashlib.sha256(b).hexdigest()
 if sum(i.size for i in ins)!=0x173 or sha!='cc1eaf1499f556d35160e3417674a62c5147b70ae0f51e6c9b04ebdfdcdfe245' or ins[-1].mnemonic!='ret':raise ValueError('Surface mark child differs')
 return dict(parent=parent,ranges={hex(a):dict(bytes=len(b),sha256=sha)},scope='Complete6324A0 standalone and joined634030 zero-mode. Actual geometry getters; actor C0/CC,663D30,copy8,pixel24 and initialization supplied. No production/SDL adoption.')
