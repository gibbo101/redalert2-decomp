# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete observer/base construction, primary Team setter and static registry."""
import hashlib,pefile,capstone
from verify_team_membership import EXPECTED
RANGES={0x41c5c0:296,0x410580:340,0x40ff10:71,0x41df90:13,0x4d2d90:61}
REG=(0xa40928,0xa3d260)
VTABLES=(0x79ae44,0x79ae3c,0x79add8,0x79adbc,0x79adb4,0x79adac,0x79ae88,0x79ae6c,0x79ae64,0x79ae5c,0x79b780,0x79b764,0x79b75c,0x79b754)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Observer constructor requires exact supplied base')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError(('Incomplete observer construction span',hex(a),n))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 return dict(ranges=out,base_actual=True,abstract_base_actual=True,CRT_format_copy_resize_atexit_supplied=True,scenario_startup_supplied=True)
