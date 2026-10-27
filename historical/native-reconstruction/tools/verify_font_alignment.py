#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete base RGB/alignment/clip caller through actual text-to-pixels."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_font_text import verify as text,RANGES as TEXT,TABLES,GLOBALS
RANGES={**TEXT,0x5fe1b0:0x1c5,0x431430:0x10,0x431450:0xd,0x431460:0x33}
def verify(data):
 parent=text(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete aligned text inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x5fe1b5:('mov','cl, byte ptr [0xa40d28]'),0x5fe1d3:('mov','ecx, dword ptr [0x839958]'),0x5fe24d:('mov','edi, dword ptr [0x84e9e8]'),0x5fe265:('call','0x4314b0'),0x5fe27f:('sub','eax, edx'),0x5fe305:('mov','eax, dword ptr [ebx]'),0x5fe32a:('call','0x431450'),0x5fe336:('call','0x431460'),0x5fe33e:('call','0x431430'),0x5fe364:('call','0x432350'),0x5fe369:('sub','eax, ebp')}.items():
  if ops.get(a)!=op:raise ValueError('Aligned text association differs '+hex(a))
 return dict(text=parent,ranges=ranges,scope='Complete5FE1B0 with actual measurement/setters/surface/text/glyph/intersection/color. Supplied initial defaults/packing/records/SetRect/surface services and diagnostic mutations; upper message/UI unjoined.')
