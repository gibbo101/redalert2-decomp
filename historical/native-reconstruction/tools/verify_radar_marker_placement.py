# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete marker coordinate/dirty helpers and their stock children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x631ba0:0x9d,0x632620:0xd2,0x5b1b00:0xd6,0x5b16e0:0x2a,
        0x77f110:0x3d,0x4112c0:4,0x4112d0:4}
TABLE=0x7a6fa8
DATA={0x7a87fc:4,TABLE:24}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Marker helpers require exact supplied base')
 p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete marker span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 if p.get_data(0x7a87fc-0x400000,4)!=struct.pack('<f',1/256):raise ValueError('Marker scale constant differs')
 if p.get_data(TABLE+8-0x400000,4)!=struct.pack('<I',0x5b1b00):raise ValueError('Dirty point stock resize differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,data={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in DATA.items()},scope='Complete631BA0/632620 with stock getters/resize/clear/FTOL; native heap and initial records supplied')
