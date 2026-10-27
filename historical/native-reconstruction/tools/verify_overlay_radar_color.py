# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete5DD000 and initialized image-getter paths."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x5dd000:0x149,0x5dd150:0x10f,0x5293d0:0x26,0x432d70:0x19}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied overlay-color target required')
 pe=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete overlay-color span')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 if ranges['0x5dd000']['sha256']!='17953ec1c3ff6f499bf61b4d6b113f8c0aefe83de1ca2584f62467e2dea5ec1a':raise ValueError('Overlay color range differs')
 if pe.get_data(0x7a7a08+0x9c-0x400000,4)!=struct.pack('<I',0x5dd150):raise ValueError('Overlay image slot differs')
 return dict(ranges=ranges,scope='Complete5DD000 with initialized primary5DD150 and authored alternate5293D0 image binding, actual zero-color constructor. Demand loading, actual animation class construction, file ownership and production remain outside this proof.')
