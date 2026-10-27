# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base device lock/unlock and their ordinary metadata getters."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x4aac80:0x13b,0x4aae40:0x9a,0x4aac60:4,0x4aac70:7}
SLOTS={0x5c:0x4aac80,0x60:0x4aae40,0x70:0x4aac60,0x74:0x4aac70}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Device pixel requires exact supplied base')
 p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete device span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,a in SLOTS.items():
  if p.get_data(0x7a0be4+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Device pixel virtual differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete4AAC80/4AAE40 with actual4AAC60/4AAC70; status/restore/device Lock/Unlock supplied; no original device or copy execution')
