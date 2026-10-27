# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact stock actor permission parents, local/alliance and veterancy leaves."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x6d7a10:0x1e6,0x452220:0x169,0x4f52b0:0x34,0x4e5540:0x3f,
        0x7133a0:0x27,0x713420:0x18}
DATA={0x79a708:8,0x79a6f8:8}
TABLES={0x7a3540+0x2f8:0x6d7a10,0x79cbbc+0x2f8:0x452220}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Radar permission requires exact supplied base')
 pe=pefile.PE(data=data);ranges={}
 for p,n in RANGES.items():
  raw=pe.get_data(p-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,p))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete permission span')
  ranges[hex(p)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for p,value in TABLES.items():
  if pe.get_data(p-0x400000,4)!=struct.pack('<I',value):raise ValueError('Stock permission association differs')
 if pe.get_data(0x39a708,8)!=struct.pack('<d',1.) or pe.get_data(0x39a6f8,8)!=struct.pack('<d',2.):raise ValueError('Promotion constants differ')
 return dict(executable_sha256=EXPECTED,ranges=ranges,data={hex(p):hashlib.sha256(pe.get_data(p-0x400000,n)).hexdigest() for p,n in DATA.items()},scope='Complete Infantry/Building2F8 with actual local/alliance/veterancy; coordinate visibility/2FC/height/dimensions child probes supplied')
