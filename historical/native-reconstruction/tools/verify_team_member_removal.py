# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Team RemoveMember parent on the exact supplied base."""
import hashlib,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x6b8fb0:0x20e}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Team removal requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Team removal span')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 return dict(ranges=out,complete_remove_member_parent=True,children_supplied=True)
