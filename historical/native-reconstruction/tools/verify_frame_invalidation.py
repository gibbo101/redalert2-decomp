# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete Building invalidation/cache/projection with existing dirty-region children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_redraw import verify as redraw_verify
RANGES={0x6aa090:0xec,0x450dd0:0x12e,0x6a29d0:0x132,0x453c70:0x2b,0x453c40:6,0x509800:6,0x77f110:0x3d}
def verify(data):
 result=redraw_verify(data);p=pefile.PE(data=data);records={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete invalidation range')
  records[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x2c,0x453c40),(0xa8,0x453c70),(0x124,0x450dd0)):
  if p.get_data(0x79cbbc+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Building dispatch differs')
 if p.get_data(0x7a3540+0x2c-0x400000,4)!=struct.pack('<I',0x509800):raise ValueError('Infantry RTTI differs')
 if struct.unpack('<d',p.get_data(0x79a728-0x400000,8))[0]!=.5:raise ValueError('Height literal differs')
 return dict(redraw=result,ranges=records,type_bounds_child='supplied45E290',scope='Complete6AA090/450DD0/6A29D0/453C70/453C40/FTOL and6A3020/union/intersection; supplied Type bounds and allocator; unscheduled')
