# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete E1 transfer parent/wrapper and joined accounting/null children."""
import hashlib,struct,pefile,capstone
from verify_house_infantry_accounting import verify as accounting_verify,RANGES as ACCOUNTING,TABLES as ACCOUNTING_TABLES
RANGES={**ACCOUNTING,0x6cd940:0x2a0,0x4ca7d0:0x41,0x6155e0:0x1d7,0x6d1430:7,0x67c150:0x174,0x6c7420:10,0x636e10:16}
TABLES={**ACCOUNTING_TABLES,0x6cdbe0:27}
# Every other entered child is an explicit supplied service, never a patched
# parent instruction. Distinct synthetic addresses stand in for virtual entries.
VIRTUAL={0x370:0x5c2f000,0x410:0x5c2f010,0xdc:0x5c2f020,0x80:0x5c2f030,0x11c:0x5c2f050,0x2a0:0x5c2f060,0x414:0x5c2f070,0x424:0x5c2f080,0x420:0x5c2f090,0x54:0x5c2f0a0,0x1a0:0x5c2f0b0}
COST=0x5c2f040;INDEX=0x5c2f0c0
SERVICES=(*VIRTUAL.values(),COST,INDEX,0x6d7c80,0x548000,0x548070,0x476b20)
def verify(data):
 parent=accounting_verify(data);p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete House transfer range '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x378,0x4ca7d0),(0x38,0x6c7420),(0x2c,0x509800)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('E1 transfer dispatch differs')
 table=p.get_data(0x6cdbe0-0x400000,27);i=table[12+14]
 if struct.unpack_from('<I',table,i*4)[0]!=0x6cd9f9:raise ValueError('E1 transfer5310 switch differs')
 return dict(accounting=parent,ranges=out,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},complete_to_return_E1_transfer=True,actual_accounting_kind_country_null_controller_radio=True,disabled_sidebar_only=True,remaining_children_and_startup_supplied=True,production_transfer_unjoined=True)
