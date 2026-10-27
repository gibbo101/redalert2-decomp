# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete43BE20 frame selector with actual health-ratio and mission children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x43be20:0x191,0x5d4540:0x20,0x594770:0x12}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact Building frame target required')
 p=pefile.PE(data=data);records={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Building frame range')
  records[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x16c,0x594770),):
  if p.get_data(0x79cbbc+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Building frame dispatch differs')
 return dict(ranges=records,scope='Complete43BE20/5D4540/594770; type84 service and startup supplied; no drawing or frame scheduling')
