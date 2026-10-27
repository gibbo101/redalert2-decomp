# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete INI node/list/entry construction, insertion and scalar cleanup."""
import hashlib,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x40e160:17,0x40e180:75,0x40e1d0:69,0x490e80:105,0x510bb0:111,0x510c20:179,0x510b60:68}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('INI records require exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(('Incomplete INI record span',hex(a)))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 return dict(ranges=out,heap_free_supplied=True,parser_index_and_startup_unjoined=True)
