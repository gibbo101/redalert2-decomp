# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact parent, stock vector children and FTOL for radar shape initialization."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x632700:0x1cb,0x5b16e0:0x2a,0x5b1b00:0xd6,0x77f110:0x3d}
TABLE=0x7a6fa8
DATA={0x7cfc70:88,0x7cfcc8:88,0x79a728:8,0x79a708:8,0x79a6f8:8}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Radar shapes require exact supplied base')
 p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete radar shape span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for off,a in ((8,0x5b1b00),(12,0x5b16e0)):
  if p.get_data(TABLE+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Radar shape vector table differs')
 if [struct.unpack('<d',p.get_data(a-0x400000,8))[0] for a in (0x79a728,0x79a708,0x79a6f8)]!=[.5,1.,2.]:raise ValueError('Radar shape numeric constants differ')
 return dict(executable_sha256=EXPECTED,ranges=ranges,data={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in DATA.items()},scope='Complete632700/5B16E0 and5B1B00 null external argument; actual FTOL; heap services and initial records supplied; private stock dimension data')
def dimensions(data):
 verify(data);p=pefile.PE(data=data);return list(struct.unpack('<44i',p.get_data(0x7cfc70-0x400000,176)))
