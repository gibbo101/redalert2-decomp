# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Building43A200 with actual coordinate/projection/intersection/FTOL."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x43a200:0x17a,0x453c70:0x2b,0x6a29d0:0x132,0x41fdf0:0x121,0x77f110:0x3d}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact Building visibility target required')
 p=pefile.PE(data=data);records={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Building visibility range')
  records[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0xfc,0x43a200),(0xa8,0x453c70),(0x124,0x450dd0)):
  if p.get_data(0x79cbbc+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Building visibility dispatch differs')
 if p.get_data(0x79a728-0x400000,8)!=struct.pack('<d',.5):raise ValueError('Building projection literal differs')
 return dict(ranges=records,scope='Complete43A200/453C70/6A29D0/41FDF0/FTOL; bounds and ordinary/special drawing supplied; no frame scheduling')
