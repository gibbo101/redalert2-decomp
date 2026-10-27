#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete text/glyph/metrics/color and surface-binding roots."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_font_glyph import verify as glyph,RANGES as GLYPH
from verify_message_font import verify as metrics,RANGES as METRICS,TABLES
RANGES={**GLYPH,**METRICS,0x4318d0:10,0x431cc0:0x1b7,0x4320b0:0x9d,0x432150:0x18,0x432350:0x58,0x63cf20:0x86}
GLOBALS=(0x852fb8,0x852fbc,0x852fc0,0x852fc4,0x852fc8,0x852fcc)
def verify(data):
 g=glyph(data);m=metrics(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete text inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x431d11:('jge','0x431e4d'),0x431d7e:('call','0x63cf20'),0x431e08:('call','0x4318e0'),0x431e5d:('call','0x4314b0'),0x431e62:('mov','ecx, dword ptr [esp + 0x24]'),0x431e6d:('lea','eax, [ecx + edx]'),0x4320d2:('shr','eax, 1'),0x432140:('call','0x432000'),0x432159:('call','dword ptr [eax + 0x60]'),0x432366:('call','0x4320b0'),0x43238a:('call','0x431cc0'),0x432394:('call','0x432150'),0x63cf39:('and','esi, 0xff'),0x63cf4d:('sar','eax, 8')}.items():
  if ops.get(a)!=op:raise ValueError('Text association differs '+hex(a))
 return dict(glyph=g,metrics=m,ranges=ranges,scope='Complete431CC0/63CF20/4320B0/432150/432350 with actual glyph/intersection/measurement. Named surface/SetRect and initial colors/font/text records supplied. No production message/UI claim.')
