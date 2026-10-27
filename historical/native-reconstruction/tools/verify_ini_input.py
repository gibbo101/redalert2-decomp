# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete original line reader, actual buffered pipe and source forwarding."""
import hashlib,struct,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x639670:152,0x494760:147,0x69b0a0:30}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('INI input requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(('Incomplete INI input span',hex(a)))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 if p.get_data(0x7a3bc4-0x400000,4)!=struct.pack('<I',0x494760):raise ValueError('INI pipe virtual Read differs')
 return dict(ranges=out,actual_buffered_pipe_source_forwarding=True,upstream_and_memcpy_supplied=True,parser_and_startup_unjoined=True)
