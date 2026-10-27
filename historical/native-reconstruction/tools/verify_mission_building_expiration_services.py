# SPDX-License-Identifier: GPL-3.0-or-later
"""Stock Building expiration target-clear and mission-continuation services."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_typed_tag_expiration import verify as verify_parent,RANGES as PARENT,TABLES as PARENT_TABLES
SPANS={4457552: (207, '986f2031ea641789f7984c7159fcf068ba221df48de03604679346dde26e6656'), 7117552: (266, '948137b397acd6e4cc8f84282e435350508c7e2030d191ec100b44a617193ed5'), 4522848: (158, '8ed0756da6c1533a50fadb106b936dddaa91cec0f7e77c0d0b499b0c0ed9bb00'), 7098480: (34, '35a4606ff6aa8144fc7f703a50b1b81f69a45a6490086d8bf61d135713eb68ff'), 5852544: (40, '130032b6e4b0dd64c9a4ceb57384052f69cfd61cf60cde2d60a1bbaeabc2bf98'), 7133312: (37, '9440aec076d4b02313605adbfb7a712c11f85404d79fe27381e016522406d4d1'), 4537440: (7, '0bf6580abb40f2b2bb5610e168c11507faba706bca7c0508e535a65bd53f6ada'), 4305936: (7, 'bb20b834cb470d87ae48d0e8640098e31091697db80844e9365cafbb5ebdad82'), 4305632: (5, '5fed5afb29946811bf02359627a94bc01d08d31b779528feaadde3866af9c855'), 5853408: (15, 'cad0d6edd5eef54df5410a6e9621895546ec3234e2ede659633aeb0657cd6eef')}
RANGES={**PARENT,**{a:n for a,(n,h) in SPANS.items()}}
TABLES={**PARENT_TABLES,0x79a708:8}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for a,(n,h) in SPANS.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if hashlib.sha256(raw).hexdigest()!=h or sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Building target service span differs '+hex(a))
 dispatch={0x370:0x440450,0x30c:0x450360,0x354:0x6c5070,0x1e4:0x5950e0,0x1e0:0x6cd880,0xc0:0x41b410,0xcc:0x41b2e0,0x84:0x453c60}
 for off,a in dispatch.items():
  if p.get_data(0x79cbbc+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Stock Building target vtable differs')
 if p.get_data(0x79a708-0x400000,8)!=struct.pack('<d',1.):raise ValueError('Availability comparison differs')
 return dict(parent=parent,spans={hex(a):dict(bytes=n,sha256=h) for a,(n,h) in SPANS.items()},dispatch={hex(k):hex(v) for k,v in dispatch.items()},scope='Actual Building expiration joins null-target440450/6C9AF0, complete availability450360, weapon permission6C5070, pending mission594D80/6CD880 and stock type/disguise/query/pending getters. Nonnull target admission excluded. House power, service68A490, weapon leaves/release and earlier effects/startup remain supplied; no production join.')
