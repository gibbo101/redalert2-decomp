# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete INI key-index construction/append/lookup and Section growth/contains."""
import hashlib,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x510ce0:19,0x510d00:199,0x5111d0:134,0x510dd0:151,0x510e70:149,0x511150:121,0x510ff0:151,0x511090:149,0x511280:121}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('INI index requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(('Incomplete INI index span',hex(a)))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 return dict(ranges=out,heap_and_CRT_sort_supplied=True,parser_merge_removal_and_startup_unjoined=True)
