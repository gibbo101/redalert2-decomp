# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original buffer construction/destruction and pipe attachment/cleanup."""
import hashlib,struct,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x438380:0x2d,0x438410:0x28,0x69b050:0x43,0x69b010:0x32}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('INI input lifetime requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(('Incomplete INI input lifetime span',hex(a)))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 if p.get_data(0x7a3bc0-0x400000,4)!=struct.pack('<I',0x69b050):raise ValueError('INI pipe virtual attach differs')
 if p.get_data(0x79e9fc-0x400000,4)!=struct.pack('<I',0x69b050):raise ValueError('Base pipe virtual attach differs')
 return dict(ranges=out,heap_supplied=True,downstream_dispatch_profiles='supplied-and-actual',parser_and_startup_unjoined=True)
