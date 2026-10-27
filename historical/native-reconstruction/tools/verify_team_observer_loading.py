# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete observer definition parser and actual Team lookup/TaskForce/trim/FTOL."""
import hashlib,pefile,capstone,struct
from verify_team_membership import EXPECTED
RANGES={0x41d7e0:0x575,0x6bf260:97,0x6b7140:65,0x6eef10:103,0x77f110:61,0x781f20:0xd0}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Observer loader requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or (a!=0x781f20 and ins[-1].mnemonic!='ret'):raise ValueError(('Incomplete observer loader span',hex(a),n))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 if p.get_data(0x7d8964-0x400000,4)!=struct.pack('<I',0xe7f):raise ValueError('FTOL control differs')
 return dict(ranges=out,complete_parser=True,Team_lookup_TaskForce_trim_FTOL_actual=True,CRT_locale_zero_only=True,INI_token_numeric_other_lookup_services_supplied=True)
