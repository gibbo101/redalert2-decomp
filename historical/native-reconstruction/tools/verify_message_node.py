#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete base text node draw and actual admission/focus/font/HSV children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_message_text import verify as text,RANGES as TEXT,TABLES as TEXT_TABLES,GLOBALS
TABLES={**TEXT_TABLES,0x7adccc:0x74}
RANGES={**TEXT,0x6f15c0:0x5b,0x6f1620:0x1b7,0x4cf240:0x20,0x4cf630:0xe,0x497a50:6,0x4ff050:0x115}
def verify(data):
 parent=text(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete message node inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x6f1638:('call','0x4cf240'),0x6f1674:('call','0x497a50'),0x6f16eb:('call','0x4ff050'),0x6f173b:('call','dword ptr [0x79a524]'),0x6f1756:('sub','edx, ebp'),0x6f175c:('shr','edx, 4'),0x6f1770:('jg','0x6f178e'),0x6f179a:('call','dword ptr [edx + 0x58]'),0x6f17b8:('call','0x600830'),0x4cf254:('mov','byte ptr [ecx + 0x1c], 0'),0x6f160e:('mov','dword ptr [esi], 0x7adccc'),0x4cf630:('mov','edx, dword ptr [0x865ff8]')}.items():
  if ops.get(a)!=op:raise ValueError('Message node association differs '+hex(a))
 raw=p.get_data(0x7adccc-0x400000,0x74)
 if len(raw)!=0x74 or struct.unpack_from('<I',raw,0x58)[0]!=0x4cf630 or struct.unpack_from('<I',raw,0x6c)[0]!=0x6f1620:raise ValueError('Text-node vtable targets differ')
 return dict(text=parent,ranges=ranges,node_dispatch=dict(address='0x7adccc',bytes=len(raw),sha256=hashlib.sha256(raw).hexdigest(),focus='0x4cf630',draw='0x6f1620'),scope='Complete6F1620 through actual admission/font/focus/HSV/600830 and text pixels. Time/audio/surface/fill/cursor leaves and initial records supplied; production owners/UI unjoined.')
