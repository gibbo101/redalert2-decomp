# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-base surface refresh parent and stock geometry getters."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x634030:0xb2,0x411290:0x24,0x4112c0:4,0x4112d0:4}
PARENT_SHA='f2245eb94eb6fd1b23229abfa00fcbc167991e946274e94bf66ac99fe000a9d8'
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Surface refresh requires exact supplied base')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete surface refresh span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 if ranges['0x634030']['sha256']!=PARENT_SHA:raise ValueError('Surface refresh parent differs')
 for off,a in {0x78:0x411290,0x7c:0x4112c0,0x80:0x4112d0}.items():
  if p.get_data(0x79aef8+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Stock surface getter association differs')
 for a,op in {0x4112b1:('ret','4'),0x63407b:('call','dword ptr [ebx + 8]'),0x634080:('call','0x6324a0'),0x6340c7:('call','0x632000'),0x6340e1:('ret','')}.items():
  if ops.get(a)!=op:raise ValueError('Refresh ABI/control association differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete634030 with actual stock rect/width/height getters or explicit diagnostic virtuals. copy8,632000,6324A0, geometry/associations/scratch remain supplied. No production/SDL adoption.')
