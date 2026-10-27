# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the positive-route preparation caller and actual resident selection."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_process_terminal_scatter import verify as parent_verify,RANGES as PARENT,TABLES
EXTRA={0x471660:0xfa,0x41b780:0x31}
RANGES={**PARENT,**EXTRA}
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic not in ('ret','jmp'):raise ValueError('Incomplete preparation child')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 return dict(parent=parent,extra=ranges,scope='Complete actor0 Process with supplied positive route result/queue and actual preparation candidate/resident/alliance/close/Scatter continuation. No original pathfinding, Process1, SDL displacement or production adoption.')
