# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
ENTRY=0x458510;SIZE=229
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Exact supplied depth initializer executable required')
 p=pefile.PE(data=data);raw=p.get_data(ENTRY-0x400000,SIZE);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,ENTRY))
 if sum(i.size for i in ins)!=SIZE or ins[-1].address!=0x4585f4 or ins[-1].mnemonic!='ret' or p.get_data(0x7cfdb0-0x400000,13)!=b'BUILDNGZ.SHP\0':raise ValueError('Incomplete depth initializer/name')
 return dict(entry=hex(ENTRY),bytes=SIZE,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest(),asset='BUILDNGZ.SHP',scope='Complete458510 parent; file/heap/cache/destruction children supplied')
