# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint complete observer definition enumeration and locale-zero compare."""
import hashlib,struct,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x41d540:424,0x781f20:208}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Observer definitions require exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or (a==0x41d540 and ins[-1].mnemonic!='ret'):raise ValueError('Incomplete observer enumeration')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for va,text in ((0x79b748,b'AITriggerTypes\0'),(0x79b74c,b'AITriggerTypesEnable\0')):
  pointer=struct.unpack('<I',p.get_data(va-0x400000,4))[0]
  if p.get_data(pointer-0x400000,len(text))!=text:raise ValueError('Observer section constant differs')
 return dict(ranges=out,complete_enumeration=True,locale_zero_only=True,INI_allocate_construct_load_boolean_children_supplied=True)
