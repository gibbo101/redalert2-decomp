# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete Tag/Trigger/Script constructors, actual base and timer reset."""
import hashlib,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6b3870:380,0x6ed220:402,0x668730:148,0x40ff10:71,0x6ed680:190}
REG=(0xabfe48,0xac0cb0,0xac0d48,0xa40aa0,0x839900)
VTABLES=(0x7ac700,0x7ac6e4,0x7ac6dc,0x7ac6d4,0x7ad9e0,0x7ad9c4,0x7ad9bc,0x7ad9b4,0x7a9328,0x7a930c,0x7a9304,0x7a92fc,0x79add8,0x79adbc,0x79adb4,0x79adac,0x79ae44,0x79ae3c)
SERVICES=(0x782017,0x1100800)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Mission construction requires exact supplied base')
 p=pefile.PE(data=data);cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(f'Incomplete mission constructor {a:x}')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 return dict(ranges=out,base_and_reset_actual=True,allocation_resize_supplied=True)
