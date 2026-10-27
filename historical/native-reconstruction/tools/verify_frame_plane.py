# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete exact-base depth/alpha plane scroll and full clear, actual fill children."""
import hashlib,pefile,capstone
from verify_surface_fill import verify as fill_verify,RANGES as FILL,VT
RANGES={**FILL,0x775d60:0x3f3,0x410c50:0x3f3,0x776160:57,0x411050:57}
def verify(data):
 old=fill_verify(data);p=pefile.PE(data=data);d=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(d.disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete frame plane span')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 # Corresponding instruction bytes differ only in internal relative targets;
 # both complete roots execute separately, not via redirected original code.
 for a in (0x775d60,0x410c50):
  ins=list(d.disasm(p.get_data(a-0x400000,0x3f3),a));assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='0xc'
 return dict(ranges=ranges,stock_surface_slots=old['slots'],scope='Complete775D60/410C50 and776160/411050, actual ordinary BSurface fill/clipping/stock children; bounded nonwrapping common allocation, no frame scheduling')
