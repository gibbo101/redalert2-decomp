# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete AlphaImage constructors/base, expiration, cleanup and destructor/search."""
import hashlib,struct,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x41ebe0:0x41ed6f-0x41ebe0,0x41ed70:0x41eecf-0x41ed70,0x40ff10:71,0x40ff90:28,0x41f0f0:18,0x41f110:170,0x41f9c0:207,0x41fd20:38,0x410340:53}
SERVICES=(0x1100500,0x1100600,0x781d3b)
VTABLES=(0x79bfd4,0x79bfb8,0x79bfb0,0x79bfa8,0x79add8,0x79adbc,0x79adb4,0x79adac,0x79ae44,0x79ae3c)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Alpha lifecycle requires exact supplied base')
 p=pefile.PE(data=data);out={};cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(f'Incomplete alpha lifecycle body {a:x}')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 if p.get_data(0x79bf68+16-0x400000,4)!=struct.pack('<I',0x41fd20) or p.get_data(0x79bfd4+32-0x400000,4)!=struct.pack('<I',0x41f9c0):raise ValueError('Alpha lifecycle virtual targets differ')
 if p.get_data(0x79add8+32-0x400000,4)!=struct.pack('<I',0x410340):raise ValueError('Base deleting virtual differs')
 return dict(ranges=out,base_and_find_actual=True,supplied_type_resize_free=[hex(a) for a in SERVICES])
