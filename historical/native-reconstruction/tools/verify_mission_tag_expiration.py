# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base Tag44 expiration dispatch and complete map/logic/Cell children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from compare_original import PATCHED_EXPECTED
RANGES={0x6ecb90:0x321,0x559d80:0x12f,0x53e110:0x61,0x47a340:0xca,
        0x47a460:0x7a,0x42d120:0x36,0x4d5b40:0x26,0x6b42d0:6}
TABLES={0x6eceb4:0x51,0x79c5a0:28,0x7a2ae4:28,0x7ac700:72,
        0x547a27:10,0x4d477d:10}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Different supplied base executable')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Tag expiration root '+hex(a))
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x6b42d0:('mov','eax, 0x2c'),0x6eccfc:('call','0x783ce4'),
  0x6ecd73:('call','dword ptr [eax + 0x28]'),0x6ecd80:('push','1'),
  0x6ecd88:('call','0x559d80'),0x6ecd94:('call','0x53e110'),
  0x559de2:('mov','dword ptr [0xa6fa1c], eax'),0x559e05:('add','edi, 0x24'),
  0x559e38:('dec','ebp'),0x559e4f:('call','0x47a340'),0x559e8a:('mov','dword ptr [0x866248], ecx'),
  0x47a353:('dec','dword ptr [eax + 0x2c]'),0x47a3c7:('cmp','eax, 0x3d'),
  0x53e146:('mov','dword ptr [0x866170], ecx'),0x53e166:('dec','edx')}.items():
  if ops.get(a)!=op:raise ValueError('Tag expiration association differs '+hex(a))
 def word(a):return struct.unpack('<I',p.get_data(a-0x400000,4))[0]
 for a,target in ((0x7ac700+0x2c,0x6b42d0),(0x79c5a0+16,0x42d120),(0x7a2ae4+16,0x4d5b40)):
  if word(a)!=target:raise ValueError('Tag expiration virtual dispatch differs')
 index=p.get_data(0x6eced4-0x400000+44-12,1)[0]
 if word(0x6eceb4+4*index)!=0x6ecd5b:raise ValueError('Tag expiration switch differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  scope='Complete Tag44 generic/map/logic/Cell expiration, actual kind/find/null tag children. RTTI negative association, recipient and map selection effects supplied; no drain/destructor/discovery/actions/runtime.')
