# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Infantry/Foot speed and actual type/House/promotion children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x508980:0x49,0x4c9b10:0xa6,0x6c12c0:8,0x506950:7,0x6d8e90:0x16,
 0x4f5a20:0x4c,0x509800:6,0x50af60:6,0x6d7910:0x80,0x7133a0:0x27,0x713420:0x18,0x77f110:0x3d}
TABLES={0x7a3540:0x4c0,0x7a3a74:0x34,0x7bb070:20,0x7db150:32,0x79a708:8,0x79a6f8:8,0x7d8964:4}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Infantry speed engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Infantry speed PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a));ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
  if sum(i.size for i in ins)!=n or (ins[-1].mnemonic!='ret' and a!=0x6c12c0):raise ValueError('Incomplete Infantry speed range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for vt,off,target in ((0x7a3540,0x2c,0x509800),(0x7a3540,0x80,0x6c12c0),(0x7a3540,0x84,0x506950),
  (0x7a3540,0x338,0x6d8e90),(0x7a3540,0x4bc,0x508980),(0x7a3a78,0x2c,0x50af60)):
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry speed dispatch differs')
 for a,op in {0x50af60:('mov','eax, 0x10'),0x509800:('mov','eax, 0xf'),
  0x4f5a55:('pop','esi'),0x4f5a56:('fld','dword ptr [edx + 0x128]'),
  0x4c9b41:('fmul','qword ptr [esp + 0xc]'),0x4c9b45:('fmul','qword ptr [esi + 0x470]'),
  0x4c9b7d:('fmul','qword ptr [esi + 0x468]'),0x5089a4:('mov','eax, 0x55555555'),
  0x77f12b:('fistp','qword ptr [eax]')}.items():
  if ops.get(a)!=op:raise ValueError('Infantry speed association differs '+hex(a))
 if p.get_data(0x7a3a74-0x400000,4)!=struct.pack('<I',0x7bb070) or p.get_data(0x7bb07c-0x400000,4)!=struct.pack('<I',0x7db150):raise ValueError('InfantryType RTTI association differs')
 if not p.get_data(0x7db158-0x400000,24).startswith(b'.?AVInfantryTypeClass@@\0'):raise ValueError('InfantryType identity differs')
 if p.get_data(0x7d8964-0x400000,4)!=struct.pack('<I',0xe7f):raise ValueError('FTOL precision/control differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  scope='Complete Infantry508980/Foot4C9B10 speed with actual type kind16, body kind15, House/country128, base speed, promotion0 and64-bit FTOL children. Initial records/associations supplied. No terrain/commands/Process/production/SDL join.')
