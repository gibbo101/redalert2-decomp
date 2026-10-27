# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete stock base Infantry/Building threat and getter associations."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x6d3e50:0x4f,0x4532f0:7,0x6c12c0:8,0x506950:7,0x453c60:7,0x509800:6,0x453c40:6}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Techno threat target required')
 pe=pefile.PE(data=data);ops={};ranges={}
 if pe.FILE_HEADER.Machine!=0x14c or pe.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Techno threat PE differs')
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Techno threat span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={0x6d3e56:('call','dword ptr [eax + 0x80]'),0x6d3e66:('call','dword ptr [edx + 0x2c]'),0x6d3e70:('call','0x4532f0'),0x6d3e80:('mov','edi, dword ptr [eax + 0xbe8]'),0x6d3e86:('call','0x4532f0'),0x6d3e8b:('imul','eax, edi'),0x6d3e91:('mov','eax, dword ptr [edi + 0x598]'),0x6d3e9e:('ret',''),0x4532f0:('mov','eax, dword ptr [ecx + 0x564]')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Techno threat association differs '+hex(a))
 tables={0x7a3540:{0x80:0x6c12c0,0x84:0x506950,0x2c:0x509800,0x2a0:0x6d3e50},0x79cbbc:{0x80:0x6c12c0,0x84:0x453c60,0x2c:0x453c40,0x2a0:0x6d3e50}}
 for vt,slots in tables.items():
  for offset,target in slots.items():
   if pe.get_data(vt+offset-0x400000,4)!=struct.pack('<I',target):raise ValueError('Stock Techno threat vtable differs')
 return dict(ranges=ranges,tables={hex(vt):{hex(k):hex(v) for k,v in slots.items()} for vt,slots in tables.items()},scope='Complete6D3E50 and4532F0 with actual stock Infantry/Building type/kind children. Initial fields/associations supplied; grid/caller/runtime adoption not established by this proof.')
