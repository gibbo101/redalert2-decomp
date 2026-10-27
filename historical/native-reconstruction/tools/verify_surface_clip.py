# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied base linked surface clipping and null-adjustment intersection."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x775190:0x1cf,0x41fdf0:0x121}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Clip requires exact supplied base')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete clipping instruction span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x7751a2:('jne','0x7752d6'),0x7752e1:('call','0x41fdf0'),0x77530d:('call','0x41fdf0'),0x77535c:('ret','8')}.items():
  if ops.get(a)!=op:raise ValueError('Clip control differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete775190 and actual41FDF0 null adjustment children; four distinct records. No copy transfer/runtime adoption.')
