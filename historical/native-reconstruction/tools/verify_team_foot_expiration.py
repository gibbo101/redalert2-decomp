# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact Team subject and Foot/Infantry expiration entry associations."""
import hashlib,struct,capstone,pefile
from verify_mission_typed_tag_expiration import verify as verify_parents
def verify(data):
 result=verify_parents(data);p=pefile.PE(data=data);cs=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 raw=p.get_data(0x6be730-0x400000,6);ins=list(cs.disasm(raw,0x6be730))
 if [(i.mnemonic,i.op_str) for i in ins]!=[('mov','eax, 0x22'),('ret','')]:raise ValueError('Team kind association differs')
 for a,target in ((0x7ac950+0x2c,0x6be730),(0x7a3540+0x28,0x501cb0),(0x7a12a0+0x28,0x4c8460)):
  if struct.unpack('<I',p.get_data(a-0x400000,4))[0]!=target:raise ValueError('Team/Foot expiration virtual association differs')
 return dict(parents=result,team_kind34=dict(bytes=6,sha256=hashlib.sha256(raw).hexdigest()),scope='Complete Foot/Infantry inherited expiration for non-Tag Team34 subject flags14 bits0/1 clear; named children and startup supplied; no Team broadcast or runtime adoption')
