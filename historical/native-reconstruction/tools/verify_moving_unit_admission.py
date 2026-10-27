# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin actual moving-resident children of the complete base Unit admission root."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_admission import verify as parent,RANGES as OLD
EXTRA={0x4b8be0:0x99,0x5d4e40:0x21,0x4ba600:0xb2,0x4ba410:0x6e,
 0x77f110:0x3d,0x4a4ac0:0xd9}
RANGES={**OLD,**EXTRA}
TABLES={0x813df4:4097*4,0x817df8:4,0x7a0f8c:8,0x79d158:8,
 0x79b628:16,0x817dfc:65536,0x7a0180:768,0x7a00a0:112,0x7d8964:4}
def verify(data):
 result=parent(data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in EXTRA.items():
  raw=pe.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Moving admission incomplete range '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 for vt,off,target in ((0x7addf8,0x48,0x5d4e40),(0x7a04cc,0xa4,0x4a4ac0)):
  if pe.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Moving admission dispatch differs')
 if pe.get_data(0x7a00a4-0x400000,4)!=bytes(4):raise ValueError('Moving admission descriptor zero jump differs')
 return {'parent':result,'ranges':ranges,'tables':{hex(a):{'bytes':n,'sha256':hashlib.sha256(pe.get_data(a-0x400000,n)).hexdigest()} for a,n in TABLES.items()},
  'scope':'Complete ordinary Unit admission with actual target/Facing/Drive IsMoving, bearing, coordinates, distance and Drive+A4 for ordinary descriptors0..6. Supplied initial records, queues, numeric tables and associations. No Process, owned map, commands, nonzero Advance, scatter, special descriptors, startup or frame claim.'}
