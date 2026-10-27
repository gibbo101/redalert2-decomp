# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete actor marker parents, vector children and existing dirty/move code."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
from verify_surface_copy import RANGES as COPY,TABLES as COPY_TABLES
RANGES={0x631910:0x1db,0x631af0:0xad,0x634e40:0x107,0x634bc0:0x2a,
        0x634f50:0x40,0x632620:0xd2,0x5b1b00:0xd6,0x5b16e0:0x2a,
        0x411290:0x24,0x4112c0:4,0x4112d0:4,0x509800:6,0x453c40:6,
        **{a:n for a,n in COPY.items() if 0x783290<=a<0x783600}}
TABLE=0x7a8804;POINT_TABLE=0x7a6fa8
TABLES={a:v for a,v in COPY_TABLES.items() if 0x783290<=a<0x783600}
DATA={a:len(v)*4 for a,v in TABLES.items()}
DATA.update({TABLE:24,POINT_TABLE:24,0x7a3540+0x2c:4,0x79cbbc+0x2c:4})
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Marker buckets require exact supplied base')
 p=pefile.PE(data=data);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError(('Incomplete marker bucket span',hex(a)))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,values in TABLES.items():
  if p.get_data(a-0x400000,len(values)*4)!=struct.pack('<'+'I'*len(values),*values):raise ValueError('Marker CRT table differs')
 for a,expected in ((TABLE+8,0x634e40),(TABLE+12,0x634bc0),(TABLE+16,0x634f50),(POINT_TABLE+8,0x5b1b00),(0x7a3540+0x2c,0x509800),(0x79cbbc+0x2c,0x453c40)):
  if p.get_data(a-0x400000,4)!=struct.pack('<I',expected):raise ValueError('Marker stock table differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,data={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in DATA.items()},scope='Complete631910/631AF0 with stock dynamic marker resize/find/clear, actual dirty producer/point resize/getters/kinds and CRT move; heap/initial records/probes supplied')
