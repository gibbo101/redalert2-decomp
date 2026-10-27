# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin inherited pixel parents on actual device virtuals."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_device_surface_pixels import verify as parent
RANGES={0x774220:0x59,0x7741d0:0x50}
def verify(data):
 p=pefile.PE(data=data);ranges={};base=parent(data)
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete inherited pixel span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest())
 return dict(device=base,ranges=ranges,scope='Complete774220/7741D0 using actual device Lock/Unlock/bpp/pitch; device OS results and initial backing supplied')
