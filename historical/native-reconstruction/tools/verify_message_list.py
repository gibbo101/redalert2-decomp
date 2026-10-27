#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact insertion, text/gadget/link ownership and actual metric/CRT children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_message_font import verify as metrics,RANGES as METRICS,TABLES as METRIC_TABLES
RANGES={**METRICS,0x5b4da0:0x3b8,0x497a50:6,0x6f15c0:0x5b,0x4cefe0:0x4f,0x4cf190:5,0x4cf170:0x11,0x4cf610:0x1c,0x539020:4,0x539040:0x21,0x539070:0x21,0x5390e0:0x24,0x539110:0x54,0x6f17f0:0x1e,0x4cf080:0x52,0x538fa0:0x4f,0x69a430:10,0x783605:0x1d,0x78365f:0x2a,0x783689:0x25,0x784704:0x40}
TABLES={**METRIC_TABLES,0x7adccc:0x58,0x7a18b4:0x28,0x7e5e0c:4}
def verify(data):
 parent=metrics(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a));
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete message list inspection '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x5b4db3:('call','0x497a50'),0x5b4e76:('call','0x431710'),0x5b4ef7:('call','dword ptr [eax + 0x24]'),0x5b505f:('mov','edi, ebp'),0x5b5061:('rep stosd','dword ptr es:[edi], eax'),0x5b5144:('call','0x5b4da0'),0x497a50:('mov','eax, dword ptr [0x84e9e8]'),0x69a430:('call','dword ptr [0x79a524]')}.items():
  if ops.get(a)!=op:raise ValueError('Message list association differs '+hex(a))
 table=lambda a,n:struct.unpack('<'+'I'*n,p.get_data(a-0x400000,n*4))
 v=table(0x7adccc,22)
 if any(v[i]!=a for i,a in {0:0x6f17f0,1:0x4cf190,4:0x5390e0,6:0x539040,7:0x539070,9:0x4cf170,21:0x4cf610}.items()) or table(0x7a18b4+0x18,2)!=(0x539040,0x539070):raise ValueError('Message list virtual association differs')
 if p.get_data(0x7e5e0c-0x400000,4)!=b':\0\0\0':raise ValueError('Message prefix separator differs')
 imports={i.address:(d.dll.decode(),i.name.decode() if i.name else '') for d in p.DIRECTORY_ENTRY_IMPORT for i in d.imports}
 if imports.get(0x79a524)!=('WINMM.dll','timeGetTime'):raise ValueError('Message clock import differs')
 return dict(metrics=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete5B4DA0 including actual metric/CRT/constructor/link/destructor/clock-conversion children. Initial records, heap allocation/free, timeGetTime and audio713DB0 supplied; no drawing/expiry polling/live objective claim.')
