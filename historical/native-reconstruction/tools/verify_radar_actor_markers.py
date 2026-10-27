# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-build complete marker callers and their stock virtual associations."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x6d74d0:0x25,0x6d7500:0x25,0x6d7530:0x12,
        0x451800:0x5d,0x451860:0x5d,0x4518c0:0x66,0x6328d0:0x17}
TABLES={0x7a3540+0x420:(0x6d74d0,0x6d7500,0x6d7530),
        0x79cbbc+0x420:(0x451800,0x451860,0x4518c0)}
DATA={p:12 for p in TABLES}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Actor marker callers require exact supplied base')
 pe=pefile.PE(data=data);ranges={}
 for p,n in RANGES.items():
  raw=pe.get_data(p-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,p))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete actor marker span')
  ranges[hex(p)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for p,words in TABLES.items():
  if pe.get_data(p-0x400000,12)!=struct.pack('<3I',*words):raise ValueError('Actor marker virtual table differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Six complete actor callers and complete6328D0; child marker/dirty effects supplied separately')
