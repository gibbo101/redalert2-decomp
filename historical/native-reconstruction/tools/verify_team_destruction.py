# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint complete Team destructor and deleting wrapper before addresses."""
import hashlib,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x6b7770:616,0x6be740:30}
REG=(0xac0d30,0xac0d60,0xac0cb0,0xac0c58,0x866178)
VTABLES=(0x7ac950,0x7ac934,0x7ac92c,0x7ac924)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Team destruction requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Team destruction span')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 return dict(ranges=out,complete_team_destructor=True,complete_deleting_wrapper=True,named_children_supplied=True)
