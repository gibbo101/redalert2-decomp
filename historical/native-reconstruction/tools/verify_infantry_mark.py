# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin base Infantry's actual Object/Techno/Foot Mark and nonnull Walk layer."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_unit_mark as unit
RANGES={a:n for a,n in unit.RANGES.items() if a not in (0x70a2d0,0x705020,0x4a47e0)}
RANGES.update({0x509800:6,0x506950:7,0x71faa0:8})
DISPATCH={0x7a3540+off:target for off,target in ((0x11c,0x4c2e60),(0x2c,0x509800),
 (0x38,0x6c7420),(0x74,0x4ca130),(0x80,0x6c12c0),(0x84,0x506950),
 (0x12c,0x5d36e0),(0x1a0,0x41b320),(0x2a0,0x6d3e50))}
DISPATCH[0x7aead8+0x74]=0x71faa0
def verify(data):
 # Reuse the exact binary/shared-wrapper guard, not Unit-kind semantics.
 unit.verify(data)
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or (ins[-1].mnemonic!='ret' and a!=0x6c12c0):raise ValueError('Incomplete Infantry Mark range')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,target in DISPATCH.items():
  if p.get_data(a-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry Mark dispatch differs')
 tables=p.get_data(0x40dc4c-0x400000,23)
 if tables[8+14]!=0 or struct.unpack_from('<I',tables)[0]!=0x40dc41:raise ValueError('Infantry cast is not identity')
 for a,op in {0x509800:('mov','eax, 0xf'),0x506950:('mov','eax, dword ptr [ecx + 0x5a8]'),
  0x71faa0:('mov','eax, 2'),0x71faa5:('ret','4')}.items():
  if ops.get(a)!=op:raise ValueError('Infantry Mark owner association differs')
 return dict(ranges=ranges,dispatch={hex(a):hex(t) for a,t in DISPATCH.items()},
  cast_tables_sha256=hashlib.sha256(tables).hexdigest(),
  scope='Complete Infantry-kind15 Object/Techno/Foot Mark with actual Infantry type getter and nonnull Walk layer2. Map insertion/removal and special-event effects, initial records and frame dirty resets remain supplied. No Infantry membership/Process/runtime or whole-frame claim.')
