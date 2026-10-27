# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete nonlazy ObjectType image startup and filename tables."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x5d7630:0x1d1}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied startup target required')
 pe=pefile.PE(data=data);a,n=next(iter(RANGES.items()));raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));digest=hashlib.sha256(raw).hexdigest()
 if sum(i.size for i in ins)!=n or digest!='abce7033f2409c78007ebf75d43b835340ce8fc4b8b186fb834fe55ab51eb1ee':raise ValueError('Startup range differs')
 for i,(ext,letter) in enumerate(((b'TEM\0',b'T'),(b'SNO\0',b'A'),(b'URB\0',b'U'))):
  if pe.get_data(0x79abac+i*104-0x400000,4)!=ext or pe.get_data(0x79abb4+i*104-0x400000,1)!=letter:raise ValueError('Startup theater table differs')
 for a,value in ((0x7e8110,b'%sA\0'),(0x7ced14,b'.SHP\0')):
  if pe.get_data(a-0x400000,len(value))!=value:raise ValueError('Startup filename constant differs')
 return dict(address='0x5d7630',bytes=n,instructions=len(ins),sha256=digest,scope='Complete startup policy; CRT, cache and release supplied; no startup scheduling or IO fidelity claim')
