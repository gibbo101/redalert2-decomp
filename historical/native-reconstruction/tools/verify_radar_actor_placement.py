# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact complete actor marker placement parent and stock virtual associations."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x6d8120:0x2a5}
TABLES={0x7a3540+0x2f8:0x6d7a10,0x79cbbc+0x2f8:0x452220}
DATA={p:4 for p in TABLES}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Actor placement requires exact supplied base')
 pe=pefile.PE(data=data);ranges={}
 for p,n in RANGES.items():
  raw=pe.get_data(p-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,p))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete placement span')
  ranges[hex(p)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for p,value in TABLES.items():
  if pe.get_data(p-0x400000,4)!=struct.pack('<I',value):raise ValueError('Placement permission stock association differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete6D8120 with explicitly supplied child probes; permission child routines inspected separately, not recovered')
