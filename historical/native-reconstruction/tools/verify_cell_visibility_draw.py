# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-base complete Cell visibility parent, both rasters and stock address children."""
import hashlib,struct,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x475520:172,0x474260:675,0x474510:794,0x411230:52,0x411370:49,0x4112f0:10,0x4113b0:4,0x4113c0:14,0x4112c0:4}
SERVICES=(0x6a8d40,0x5956c0)
VT=0x79aef8
ASSETS={'SHROUD.SHP':'9818f7e2685fb1e8ed75ceff568aaf5d36350c747cbd4f30856458bba12e4964','FOG.SHP':'b8e3640435140041f0ac3d4ff18ad99b035a2292b685a2fd89c64bf1cc55e73f'}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Cell visibility draw requires exact supplied base')
 p=pefile.PE(data=data);result={};cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(cs.disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(f'Incomplete visibility draw body {a:x}')
  result[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest())
 for off,a in {0x5c:0x411370,0x60:0x4112f0,0x70:0x4113b0,0x74:0x4113c0,0x7c:0x4112c0}.items():
  if p.get_data(VT+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Alpha vtable differs')
 if p.get_data(0x7d2c70-0x400000,19)!=b'FOG.SHP\0SHROUD.SHP\0\0'[:19]:raise ValueError('Visibility filenames differ')
 return dict(ranges=result,supplied_mask_and_loader=[hex(a) for a in SERVICES],stock_vtable=hex(VT))
