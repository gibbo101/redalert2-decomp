# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-base complete friendly E1 resident admission children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_infantry_permission import verify as parent
RANGES={0x4e5580:0x51,0x509800:6,0x6c7430:7,0x71dea0:10,0x594770:0x12}
def verify(data):
 result=parent(data);p=pefile.PE(data=data);c=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete resident child '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for vt,off,a in ((0x7a3540,0x2c,0x509800),(0x7a3540,0x3c,0x6c7430),(0x7a3540,0x16c,0x594770),(0x7aead8,0x10,0x71dea0)):
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Resident dispatch differs')
 raw=p.get_data(0x503a40-0x400000,31)
 if struct.unpack('<4I',raw[:16])!=(0x50382c,0x503988,0x5038a3,0x5038cb) or raw[16+14]!=2:raise ValueError('Infantry switch differs')
 return dict(parent=result,ranges=ranges,switch_sha256=hashlib.sha256(raw).hexdigest(),scope='Complete overlay-free503190 with ordinary friendly E1 resident lists, actual mission/kind/House/Walk queries. Startup/associations supplied; special missions, transport, demolition and hostile residents excluded.')
