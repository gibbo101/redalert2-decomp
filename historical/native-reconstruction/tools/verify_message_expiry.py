#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete message expiry and shared insertion/list children."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_message_list import verify as insertion,RANGES as INSERTION,TABLES
RANGES={**INSERTION,0x5b5610:0xdc}
def verify(data):
 parent=insertion(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);a=0x5b5610;raw=p.get_data(a-0x400000,0xdc);ins=list(cs.disasm(raw,a));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=len(raw):raise ValueError('Incomplete expiry inspection')
 for a,op in {0x5b5622:('mov','eax, dword ptr [esi + 0x24]'),0x5b563e:('call','0x69a430'),0x5b5643:('sub','eax, dword ptr [0x839980]'),0x5b564b:('cmp','ebx, dword ptr [esi + 0x24]'),0x5b564e:('jle','0x5b569e'),0x5b565b:('mov','ebx, eax'),0x5b565d:('call','dword ptr [edx + 0x24]'),0x5b5678:('mov','word ptr [eax], 1'),0x5b569a:('mov','esi, ebx'),0x5b56d9:('mov','dword ptr [eax + 0x10], esi')}.items():
  if ops.get(a)!=op:raise ValueError('Message expiry association differs '+hex(a))
 return dict(insertion=parent,expiry=dict(address='0x5b5610',bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest()),scope='Complete ordinary5B5610 plus actual insertion/metric/CRT/text/gadget/link/destructor/clock-conversion children. Initial records, heap/timeGetTime/audio leaves supplied; no drawing or production scheduling claim.')
