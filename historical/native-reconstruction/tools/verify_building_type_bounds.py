# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Type bounds, signed frame accessor/constructor and release parent."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_redraw import verify as redraw
RANGES={0x45e290:0x4a5,0x45e920:0x33,0x45ed50:0x6c,0x42bcd0:0x20,0x45efe0:0xf0}
def verify(data):
 result=redraw(data);p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or (ins[-1].mnemonic!='ret' and a!=0x45e290):raise ValueError('Incomplete Type bounds range')
  if a==0x45e290 and ins[-1].op_str!='0x45e663':raise ValueError('Missing Type bounds loop tail')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x9c,0x458ce0),(0xc0,0x45e790)):
  if p.get_data(0x79d1f8+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('BuildingType image dispatch differs')
 return dict(redraw=result,ranges=ranges,building_type_vtable='0x79d1f8',scope='Complete45E290/45E920/45ED50/42BCD0/45EFE0; image getters and heap supplied; no demand loader/startup/frame scheduling')
