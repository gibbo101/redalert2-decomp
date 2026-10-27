# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-base complete Team admission parent; children supplied."""
import hashlib,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6b8dc0:0x1f0}
SERVICES=(0x636f10,0x594db0,0x668870,0x1100800,0x1100810,0x1100820,0x1100830)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Team admission requires exact supplied base')
 p=pefile.PE(data=data);cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete admission range')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 return dict(ranges=out,complete_admission_parent=True,children_supplied=True)
