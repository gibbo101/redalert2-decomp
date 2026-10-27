# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint complete observer callbacks and their two double constants."""
import hashlib,struct,capstone,pefile
from verify_team_membership import EXPECTED
RANGES={0x41dfb0:191,0x41e070:187}
CONSTANTS={0x79b610:0.,0x79a728:.5}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Observer weight requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete observer callback')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for a,v in CONSTANTS.items():
  if p.get_data(a-0x400000,8)!=struct.pack('<d',v):raise ValueError('Observer constant differs')
 return dict(ranges=out,constants={hex(a):struct.pack('<d',v).hex() for a,v in CONSTANTS.items()},precision_bits=53,rounding_control_words=[0x27f,0xe7f],finite_profile=True)
