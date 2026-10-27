# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint complete Team constructor and actual numerical base before addresses."""
import hashlib,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6b7430:0x6b776d-0x6b7430,0x40ff10:71,0x6b9590:115}
REG=(0x866178,0xac0cb0,0xac0c58,0xac0d60,0xac0d30)
VTABLES=(0x7ac950,0x7ac934,0x7ac92c,0x7ac924,0x79add8,0x79adbc,0x79adb4,0x79adac,0x79ae44,0x79ae3c)
SERVICES=(0x6bfa90,0x548070,0x782017,0x6b3870,0x668730,0x1100700)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Team constructor requires exact supplied base')
 p=pefile.PE(data=data);cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Team constructor/base')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 return dict(ranges=out,base_actual=True,children_supplied=[hex(a) for a in SERVICES])
