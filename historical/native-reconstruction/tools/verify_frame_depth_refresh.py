# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete exact-base7761C0 including the block after its first return."""
import hashlib,struct,pefile,capstone
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x7761c0:0x173,0x411370:0x31,0x4112f0:0xa,0x4113b0:4,0x4113c0:0xe,0x4112c0:4}
VT=0x79aef8;SLOTS={0x5c:0x411370,0x60:0x4112f0,0x70:0x4113b0,0x74:0x4113c0,0x7c:0x4112c0}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Frame depth requires exact supplied base')
 p=pefile.PE(data=data);ranges={};ops={};dis=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(dis.disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete depth instruction span')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for off,a in SLOTS.items():
  if p.get_data(VT+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Depth stock virtual association differs')
 for a,op in {0x7761da:('call','dword ptr [esi + 0x5c]'),0x7761e4:('call','dword ptr [eax + 0x60]'),0x7762ec:('ret','0x10'),0x7762ef:('test','dl, 2'),0x776331:('jmp','0x7762c6')}.items():
  if ops.get(a)!=op:raise ValueError('Depth control span differs')
 return dict(ranges=ranges,stock_surface_vtable=hex(VT),scope='Complete7761C0 and actual ordinary stock surface lock/unlock/width/format/pitch; nonnull bounded backing, supplied owner geometry/startup, no scheduling')
