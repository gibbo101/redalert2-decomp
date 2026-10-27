#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact Trigger deleting destructor and Tag pointer-expiration recipient."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_tag_destruction import verify as verify_parent,RANGES as PARENT_RANGES,TABLES as PARENT_TABLES
RANGES={**PARENT_RANGES,0x6edba0:0x11f,0x6b4040:0x83}
TABLES={**PARENT_TABLES,0x7ad9e0:72}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Mission Trigger destruction range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x6edbc1:('call','0x6ecb90'),0x6edbef:('mov','dword ptr [0xa40ab0], ecx'),
  0x6edc38:('mov','dword ptr [0xac0cc0], ecx'),0x6edc81:('mov','dword ptr [0xac0d58], ecx'),
  0x6edca3:('call','0x40ff90'),0x6b4047:('cmp','dword ptr [esi + 0x24], ecx'),
  0x6b405d:('mov','dword ptr [esi + 0x28], eax'),0x6b4067:('mov','byte ptr [esi + 0x34], 1'),
  0x6b40b0:('mov','dword ptr [0xac0ce8], ecx')}.items():
  if ops.get(a)!=op:raise ValueError('Mission Trigger destruction association differs '+hex(a))
 tables={}
 for a,n in TABLES.items():tables[hex(a)]=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()
 trigger=struct.unpack('<18I',p.get_data(0x7ad9e0-0x400000,72))
 if trigger[2]!=0x4100b0 or trigger[8]!=0x6edba0 or trigger[11]!=0x6edb90 or trigger[12]!=0x6edb80 or trigger[17]!=0x4101e0:raise ValueError('Trigger cleanup virtual dispatch differs')
 return dict(parent=parent,ranges=ranges,tables=tables,scope='Complete Trigger deleting destructor6EDBA0 and Tag pointer-expiration6B4040, plus inherited cleanup/ordinary Tag destruction roots. Generic kind38 expiration effects beyond the recovered Tag recipient, RTTI/free and initial associations supplied; no discovery/actions/runtime.')
