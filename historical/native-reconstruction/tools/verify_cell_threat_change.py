# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint complete Cell threat parent and four children on the supplied base."""
import hashlib,pefile,capstone
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x476b20:0x7a,0x4e5dc0:0x6a,0x4e5500:0x32,0x4f52f0:0x23,0x54e370:0x30}
TABLES={0x7d9fa0:36,0x7d9fc4:36}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Cell threat executable required')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Cell threat span')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x476b21:('mov','eax, dword ptr [ecx + 0x24]'),0x476b4c:('mov','edx, dword ptr [0xa3229c]'),0x476b88:('mov','eax, dword ptr [0xa322a8]'),0x4e5dce:('neg','esi'),0x4e5def:('sar','eax, cl'),0x4e5e04:('sub','dword ptr [ecx], eax'),0x4e5e0f:('mov','dword ptr [ecx], 0')}.items():
  if ops.get(a)!=op:raise ValueError('Cell threat association differs '+hex(a))
 return dict(ranges=out,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()})
