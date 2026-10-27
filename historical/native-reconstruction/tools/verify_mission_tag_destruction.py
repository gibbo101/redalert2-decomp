#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact deferred cleanup and ordinary-session Tag deleting destructor roots."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from compare_original import PATCHED_EXPECTED
RANGES={0x6ecf10:0x11c,0x6b42e0:0x1e,0x6b39f0:0x2c4,0x40ff90:0x1c,
 0x40cdf0:0x26,0x4100b0:8,0x4101e0:3,0x410240:3}
TABLES={0x7ac700:72,0x79e868:24}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Different supplied base executable')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete mission Tag destruction range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x6ecf2f:('call','dword ptr [edx + 0x44]'),0x6ecf5f:('mov','dword ptr [0xac0ce8], ecx'),
  0x6ecf88:('call','dword ptr [ecx + 8]'),0x6ed017:('call','dword ptr [edx + 0x20]'),
  0x6b42e3:('call','0x6b39f0'),0x6b3a14:('call','0x6ecb90'),0x6b3bb5:('mov','dword ptr [ecx + eax*4], esi'),
  0x6b3ca2:('call','0x6ecb90'),0x6b3ca9:('call','0x40ff90')}.items():
  if ops.get(a)!=op:raise ValueError('Mission Tag destruction association differs '+hex(a))
 tables={}
 for a,n in TABLES.items():tables[hex(a)]=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()
 tag=struct.unpack('<18I',p.get_data(0x7ac700-0x400000,72))
 if tag[2]!=0x4100b0 or tag[8]!=0x6b42e0 or tag[17]!=0x4101e0:raise ValueError('Tag cleanup virtual dispatch differs')
 vector=struct.unpack('<6I',p.get_data(0x79e868-0x400000,24))
 if vector[4]!=0x40cdf0:raise ValueError('Deferred vector search dispatch differs')
 return dict(ranges=ranges,tables=tables,scope='Complete6ECF10 cleanup and ordinary inactive-session Tag deleting destructor6B42E0/6B39F0 with actual Release/search/base destructor. Expiration, RTTI and free services supplied; active-session bookkeeping refused. Initial records/registries supplied; no Trigger destructor/discovery/actions/runtime.')
