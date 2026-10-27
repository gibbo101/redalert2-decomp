# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete6A7820 with actual affine, FTOL, constructors, projection and intersections."""
import hashlib,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6a7820:894,0x437690:25,0x41b630:25,0x591380:120,0x77f110:61,0x6a27a0:200,0x6ac850:30,0x41fdf0:289}
SERVICES=(0x548000,0x54aab0,0x548070,0x475520,0x41f5e0)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Rectangular visibility requires exact supplied base')
 p=pefile.PE(data=data);out={};cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(f'Incomplete rectangular visibility body {a:x}')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 return dict(ranges=out,supplied_map_and_draw_children=[hex(a) for a in SERVICES],half_literal=p.get_data(0x79a728-0x400000,8).hex())
