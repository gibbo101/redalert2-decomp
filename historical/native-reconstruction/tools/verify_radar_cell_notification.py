# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete visibility-to-radar notification and actual intersection/FTOL."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x6328f0:0x1ae,0x41fdf0:0x121,0x77f110:0x3d}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Exact supplied notification executable required')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete notification span '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x632987:('call','0x41fdf0'),0x6329e6:('call','0x77f110'),0x632a81:('call','0x632620'),0x632a9b:('ret','4')}.items():
  if ops.get(a)!=op:raise ValueError('Notification association differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete6328F0 with actual41FDF0/77F110; surface dimension and dirty-point children supplied probes')
