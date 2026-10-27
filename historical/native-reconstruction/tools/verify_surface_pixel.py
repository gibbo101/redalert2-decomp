# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete exact-base BSurface SetPixel and ordinary stock lock chain."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x774220:0x59,0x411370:0x31,0x4112f0:0xa,0x4113b0:4,0x4113c0:0xe,0x4112c0:4}
VT=0x79aef8;SLOTS={0x24:0x774220,0x5c:0x411370,0x60:0x4112f0,0x70:0x4113b0,0x74:0x4113c0,0x7c:0x4112c0}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Pixel requires exact supplied base')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete pixel instruction span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for off,a in SLOTS.items():
  if p.get_data(VT+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Pixel stock virtual association differs')
 for a,op in {0x774233:('call','dword ptr [edx + 0x5c]'),0x774243:('cmp','eax, 2'),0x77424f:('mov','word ptr [edi], ax'),0x774262:('mov','byte ptr [edi], cl'),0x774276:('ret','8')}.items():
  if ops.get(a)!=op:raise ValueError('Pixel control/store differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete774220 with actual stock lock/bpp/pitch/width/unlock. Allocation/geometry supplied; bounded nonnull backing and exact null-base zero-address return. No DSurface/runtime adoption.')
