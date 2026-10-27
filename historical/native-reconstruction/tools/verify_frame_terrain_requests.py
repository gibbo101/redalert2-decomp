# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete6A3EF0 with actual center/projection/intersection children."""
import hashlib,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6a3ef0:528,0x475d60:77,0x6a27a0:200,0x41fdf0:289,0x77f110:61}
SERVICES=(0x4706c0,0x475520,0x41f1c0,0x6a7820,0x4110b0)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Frame terrain requires exact supplied base')
 p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(f'Incomplete frame terrain body {a:x}')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 return dict(ranges=ranges,half_literal=p.get_data(0x79a728-0x400000,8).hex(),supplied_services=[hex(a) for a in SERVICES])
