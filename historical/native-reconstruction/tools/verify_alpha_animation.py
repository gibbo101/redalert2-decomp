# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete alpha-animation drawing and forced table initialization, exact supplied base."""
import hashlib,struct,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x41f1c0:1048,0x41f5e0:866,0x41f950:112,0x41fdf0:289,0x411230:52,0x411370:49,0x4112f0:10,0x4113b0:4,0x4113c0:14,0x4112c0:4}
VT=0x79aef8
SERVICE=0x1100500
# A named supplied Object Type virtual method; only that child's output is stubbed.
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Alpha animation requires exact supplied base')
 p=pefile.PE(data=data);out={};cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(f'Incomplete alpha body {a:x}')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 for off,a in {0x5c:0x411370,0x60:0x4112f0,0x70:0x4113b0,0x74:0x4113c0,0x7c:0x4112c0}.items():
  if p.get_data(VT+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Alpha surface vtable differs')
 mask=p.get_data(0x79b850-0x400000,1800)
 return dict(ranges=out,stock_vtable=hex(VT),tile_mask_sha256=hashlib.sha256(mask).hexdigest(),supplied_type_query=True)
