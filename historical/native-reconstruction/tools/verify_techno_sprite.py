# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6d1510:1979,0x6a2970:60,0x77f110:61,0x4521b0:40,0x6d6df0:7,0x6d6e00:7,0x41b410:7,0x6c12c0:8,0x453c60:7}
TABLES={0x6d1ccc:20,0x6d1ce0:20,0x79a728:8,0x79a738:4}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Exact supplied sprite engine required')
 p=pefile.PE(data=data);records={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!=('jmp' if a==0x6c12c0 else 'ret'):raise ValueError('Incomplete sprite routine')
  records[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for a,targets in ((0x6d1ccc,(0x6d155f,0x6d1566,0x6d1566,0x6d1555,0x6d1cc1)),(0x6d1ce0,(0x6d1a7b,0x6d1b3a,0x6d1c10,0x6d1c63,0x6d1c10))):
  if p.get_data(a-0x400000,20)!=struct.pack('<5I',*targets):raise ValueError('Sprite mode jump table differs')
 if p.get_data(0x6d1cc8-0x400000,3)!=b'\xc2\x3c\x00':raise ValueError('Sprite15-argument ABI differs')
 return dict(ranges=records,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete6D1510 with actual Building brightness/byte predicates/Type getter/height projection/FTOL; other named children/SHP wrapper/converters/startup supplied, no pixels/schedule')
