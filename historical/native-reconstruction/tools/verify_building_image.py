# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete base Building primary/secondary demand getters and name/timing children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_overlay_image import verify as overlay
RANGES={0x458ce0:0x11e,0x45e790:0x18d,0x5d7bd0:0x4a,0x5d7c20:5,0x77f110:0x3d}
def verify(data):
 inherited=overlay(data);p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Building image range')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x9c,0x458ce0),(0xc0,0x45e790)):
  if p.get_data(0x79d1f8+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Building image dispatch differs')
 if p.get_data(0x79b608-0x400000,8)!=struct.pack('<d',900.) or p.get_data(0x7ced14-0x400000,5)!=b'.SHP\0':raise ValueError('Building image constants differ')
 return dict(overlay=inherited,ranges=ranges,scope='Complete458CE0/45E790/5D7BD0/5D7C20/FTOL; file/CRT/lifetime services and Type startup supplied; no heap/frame scheduling')
