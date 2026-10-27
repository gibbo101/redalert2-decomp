# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact stock Infantry/Building color flag and House queries."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x41b410:7,0x41b2e0:5,0x509270:0x3d,0x4e5540:0x3f}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Radar color requires exact supplied base')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete radar actor instruction span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 tables={0x7a3540:{0xc0:0x41b410,0xcc:0x509270},0x79cbbc:{0xc0:0x41b410,0xcc:0x41b2e0}}
 for vt,slots in tables.items():
  for off,a in slots.items():
   if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Radar actor stock virtual differs')
 for a,op in {0x50927f:('call','0x4e5540'),0x509288:('mov','al, byte ptr [esp + 8]'),0x509290:('mov','eax, dword ptr [esi + 0x1b4]'),0x50929a:('mov','eax, dword ptr [esi + 0x410]'),0x5092a4:('mov','eax, dword ptr [0xa35db4]')}.items():
  if ops.get(a)!=op:raise ValueError('Radar color late field/control differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,tables={hex(v):{hex(k):hex(a) for k,a in t.items()} for v,t in tables.items()},scope='Complete stock C0/CC for Infantry and Building, actual4E5540 using existing native predicate. Initial fields/House association supplied; no startup/production/SDL adoption.')
