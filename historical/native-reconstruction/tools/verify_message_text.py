#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete base600830 and CRT scratch children with prior text composition."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_font_alignment import verify as alignment,RANGES as ALIGNMENT,TABLES,GLOBALS
RANGES={**ALIGNMENT,0x600830:0x446,0x783605:0x1d,0x783622:0x3d,0x783850:0x2f,0x737e30:0xe8}
def verify(data):
 parent=alignment(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete message text inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x600835:('call','0x783850'),0x60088b:('call','0x737e30'),0x6008b7:('call','0x783622'),0x6008fc:('mov','word ptr [esp + 0x103e], 0'),0x600994:('mov','ecx, dword ptr [esp + 0x105c]'),0x60099b:('call','0x431710'),0x600a2c:('call','0x431690'),0x600a89:('call','0x5fe1b0'),0x600c10:('call','0x5fd290'),0x600c61:('ret','0x24'),0x737e54:('je','0x737f0f')}.items():
  if ops.get(a)!=op:raise ValueError('Message consumer association differs '+hex(a))
 return dict(alignment=parent,ranges=ranges,scope='Complete600830/783605/783622/783850, actual fitting/width/alignment/text/pixels, actual zero-context737E30. Nonzero IME refresh/fill/cursor surface leaves and initial records supplied. No node/production UI claim.')
