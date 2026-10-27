# SPDX-License-Identifier: GPL-3.0-or-later
"""Join coverage parents to actual House, height/FTOL and packed-Cell roots."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_techno_coverage import verify as parent_verify,RANGES as PARENT
RANGES={**PARENT,0x4f52b0:0x34,0x4e5540:0x3f,0x6a2970:0x3c,0x77f110:0x3e,0x548070:0x38}
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete coverage child span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest())
 return dict(parent=parent,ranges=ranges,scope='Complete coverage parents with actual4F52B0/4E5540/6A2970/77F110/548070. Shared House/map/fallback; virtual30C/type80/Owner3C and refresh/redraw remain supplied. No production adoption.')
def scale_bits(data):
 # Authored numeric input; ABE490 is runtime storage, not a file table.
 verify(data);return struct.unpack('<Q',struct.pack('<d',.125))[0]
