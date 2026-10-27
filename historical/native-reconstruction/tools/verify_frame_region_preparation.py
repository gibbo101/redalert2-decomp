# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint complete6A33F0 and its actual coordinate/rectangle children."""
import hashlib
import pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6a33f0:626,0x475d60:77,0x47d040:32,0x453e40:33,0x6a27a0:200,0x41fdf0:289,0x77f110:61}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Frame region executable differs')
 pe=pefile.PE(data=data);result={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(f'Frame region complete range differs: {a:x}')
  result[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 return dict(ranges=result,half_literal=pe.get_data(0x79a728-0x400000,8).hex(),supplied_children=['4706c0 height','7761c0 depth refresh','4754b0 terrain'])
