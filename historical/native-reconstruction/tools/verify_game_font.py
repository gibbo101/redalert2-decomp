#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact stock fonT loader/constructor/fallback and real metric consumer ranges."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_message_font import verify as metrics,RANGES as METRICS,TABLES
RANGES={**METRICS,0x431040:0xbd,0x431150:0x270,0x431ec0:0x84}
def verify(data):
 parent=metrics(data);p=pefile.PE(data=data);ops={};ranges={};cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete game font inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x431093:('call','0x431150'),0x4310ad:('call','0x431ec0'),0x4311bf:('push','0x20000'),0x4311ff:('cmp','eax, 0x546e6f66'),0x43123f:('cmp','eax, 0x20000'),0x43134a:('imul','edi, dword ptr [esi + 0x14]'),0x431358:('cmp','word ptr [eax], bp'),0x431eea:('mov','cx, word ptr [edi + 0xb0]'),0x431f08:('mov','byte ptr [eax], dl'),0x431f27:('not','dl'),0x431f29:('mov','byte ptr [eax - 1], dl')}.items():
  if ops.get(a)!=op:raise ValueError('Game font association differs '+hex(a))
 imports={i.address:(d.dll.decode(),i.name.decode() if i.name else '') for d in p.DIRECTORY_ENTRY_IMPORT for i in d.imports}
 if imports.get(0x79a4a8)!=('USER32.dll','SetRect'):raise ValueError('Game font rectangle import differs')
 return dict(metrics=parent,ranges=ranges,scope='Complete successful431040 ->431150 ordinary fonT ->431EC0 plus actual metric consumers. File/heap/SetRect APIs and heap fill supplied; FoNt variant/failures and destructor not proved. No insertion/drawing claim.')
