# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Building static traversal and its exact rect/RTTI children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x6a9f60:0x12c,0x41fdf0:0x121,0x453c40:6,0x509800:6}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact Building static target required')
 p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(('Incomplete Building static range',hex(a)))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x2c,0x453c40),(0x124,0x450dd0)):
  if p.get_data(0x79cbbc+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Building static vtable differs')
 return dict(ranges=ranges,scope='Complete6A9F60 with actual rect intersection/Building and Infantry RTTI; bounds and final drawing services; no frame schedule')
