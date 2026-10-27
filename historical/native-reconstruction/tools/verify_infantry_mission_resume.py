# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base Infantry/Foot resume parents and ordinary entered Techno children."""
import hashlib,struct,pefile,capstone
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x509800:6,0x503c00:0x1fb,0x4c6f10:0x299,0x6d48f0:0x2a,0x4cdd70:0x57,0x6d1460:3,0x615360:0x114,0x6d1430:7,0x594770:0x12,0x5950d0:0xf,0x4cdaa0:0xf}
SERVICES=(0x454c70,0x4c8b00,0x4f52f0,0x6d7910,0x6000100,0x6000110,0x6000120)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Infantry resume executable required')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete resume range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for off,target in ((0x414,0x503c00),(0x438,0x4cdaa0),(0x16c,0x594770),(0x45c,0x4cdd70),(0x3c8,0x6d1460)):
  if struct.unpack('<I',p.get_data(0x7a3540+off-0x400000,4))[0]!=target:raise ValueError('Resume E1 vtable differs')
 for a,op in {0x4c6f32:('mov','byte ptr [esi + 0x59d], 1'),0x503c11:('call','0x4c6f10'),0x503d09:('call','0x5950d0')}.items():
  if ops.get(a)!=op:raise ValueError('Resume association differs')
 return dict(ranges=out)
