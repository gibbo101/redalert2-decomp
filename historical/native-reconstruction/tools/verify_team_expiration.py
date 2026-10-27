# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact Team34 expiration branch and its actual kind dispatch/table."""
import hashlib,struct,capstone,pefile
from verify_team_membership import EXPECTED
RANGES={0x6ecb90:0x321,0x6be730:6}
TABLES={0x6eceb4:0x51,0x7ac950:0x48}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Team expiration requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Team expiration span')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 def word(a):return struct.unpack('<I',p.get_data(a-0x400000,4))[0]
 kind=list(c.disasm(p.get_data(0x6be730-0x400000,6),0x6be730))
 if word(0x7ac950+0x2c)!=0x6be730 or [(i.mnemonic,i.op_str) for i in kind]!=[('mov','eax, 0x22'),('ret','')]:raise ValueError('Team kind34 dispatch differs')
 index=p.get_data(0x6eced4-0x400000+34-12,1)[0]
 if word(0x6eceb4+4*index)!=0x6ece5d:raise ValueError('Team expiration table differs')
 return dict(ranges=out,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete Team34 generic expiration with actual kind; negative RTTI, selection and AC0C18 recipient effects supplied; no runtime adoption')
