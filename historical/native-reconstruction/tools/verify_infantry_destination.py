# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin ordinary Infantry/Foot destinations, Walk QI/class and actual commands."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_walk_commands import RANGES as COMMANDS,TABLES as COMMAND_TABLES
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={**COMMANDS,0x501ce0:0x790,0x4c8030:0x1e8,0x6c7430:7,0x4f52f0:0x23,
 0x594770:0x12,0x509800:6,0x71dea0:0xa,0x454bf0:0x75,0x71fe90:0xa,
 0x71fab0:0x5d,0x53d2b0:0xa4,0x71fde0:0xd,0x71fdf0:0xd,
 0x53d250:0x1e,0x53d270:0x37,0x71f900:0x38,0x6dd40f:0x1a}
TABLES={**COMMAND_TABLES,0x7aeba0:0x24,0x79db04:0x50,0x7cf208:16,
 0x7afce0:16,0x7afcd0:16,0x7afcc0:16,0x7a5890:16,0x7a2050:16,
 0x7a1f80:16,0x7a1fa0:16,0x79a1bc:8,0x7f7610:8}
SERVICES={0x410290:'target coordinates',0x548000:'coordinate map',0x504740:'animation4DC',
 0x3c7594:'atomic increment',0x3c757c:'atomic decrement'}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Infantry destination engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Infantry destination PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Infantry destination range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for vt,off,target in ((0x7a3540,0x410,0x501ce0),(0x7a3540,0x3c,0x6c7430),(0x7a3540,0x16c,0x594770),
  (0x7a3540,0x2c,0x509800),(0x7aead8,0,0x71fe90),(0x7aead8,0x10,0x71dea0),(0x7aeba0,0xc,0x71f900)):
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry destination dispatch differs')
 for a,op in {0x501fa0:('mov','dword ptr [ebp + 0x4d0], esi'),0x502461:('call','0x4c8030'),
  0x4c8122:('mov','ecx, dword ptr [ebp + 0x494]'),0x4c81f6:('mov','eax, dword ptr [0xa40d2c]'),
  0x71f910:('mov','ecx, dword ptr [0x7a1fa0]'),0x6dd416:('push','0x7f7610'),
  0x6dd423:('mov','byte ptr [ebp + 0xb44], al')}.items():
  if ops.get(a)!=op:raise ValueError('Infantry destination association differs '+hex(a))
 if p.get_data(0x7a1fa0-0x400000,16)==p.get_data(0x7a1f80-0x400000,16):raise ValueError('Walk timer-class distinction differs')
 if p.get_data(0x7f7610-0x400000,8)!=b'JumpJet\0':raise ValueError('Base B44 INI key differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  services={hex(a):s for a,s in SERVICES.items()},scope='Complete ordinary Infantry/Foot roots with actual Walk commands, House/mission and successful QI/GetClassID/reference ordering. Non-JumpJet, nontransport; moving nonnull parent retarget refused. Coordinates/map/animation, initial records and scratch supplied; no production walking or objective transition.')
