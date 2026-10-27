# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact Foot/Infantry/Building Tag expiration on the supplied base executable."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_techno_tag_expiration import verify as verify_parent,RANGES as PARENT,TABLES as PARENT_TABLES
RANGES={**PARENT,0x4c8460:0x26b,0x501cb0:0x2a,0x449e40:0x16a,0x594770:0x12,0x509800:6,0x453c40:6,0x5d4e40:0x21,0x548070:0x38,0x5d4540:0x20,0x40ffb0:0x10,0x6b42d0:6}
TABLES={**PARENT_TABLES,0x7ac6e4:28}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete typed expiration root '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x4c8473:('call','0x6d2d10'),0x4c84c6:('call','dword ptr [edx + 0x28]'),0x4c84fc:('call','0x6d6e50'),
  0x4c8566:('call','dword ptr [eax + 0x16c]'),0x4c8625:('mov','eax, dword ptr [esi + 0x4a0]'),0x4c8679:('mov','edx, dword ptr [esi + 0x47c]'),0x4c8608:('call','0x548070'),0x4c8641:('mov','dword ptr [esi + 0x4ac], edx'),
  0x501cbe:('call','0x4c8460'),0x501ccb:('mov','dword ptr [esi + 0x5a8], 0'),0x449e4f:('call','0x6d2d10'),
  0x449ea8:('call','0x5d4540'),0x449ebb:('test','ah, 0x41'),0x449eef:('call','0x44ca60'),0x449f7b:('call','dword ptr [eax + 0x10]'),
  0x5d4543:('fild','dword ptr [ecx + 0x6c]'),0x5d454c:('call','dword ptr [eax + 0x84]'),0x5d4558:('fdivr','qword ptr [esp]'),
  0x509800:('mov','eax, 0xf'),0x453c40:('mov','eax, 6'),0x6b42d0:('mov','eax, 0x2c')}.items():
  if ops.get(a)!=op:raise ValueError('Typed expiration association differs '+hex(a))
 dispatch=((0x7a3540,0x28,0x501cb0),(0x79cbbc,0x28,0x449e40),(0x7a3540,0x2c,0x509800),(0x79cbbc,0x2c,0x453c40),(0x7a3540,0x16c,0x594770),(0x79cbbc,0x16c,0x594770),(0x7ac6e4,0xc,0x40ffb0))
 for vt,off,target in dispatch:
  if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Typed expiration vtable differs')
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},dispatch=[list(row) for row in dispatch],scope='Complete Foot/Infantry/Building Tag expiration, actual inherited parents, mission/kind/coordinate/map/ratio/secondary-Tag-kind/search children. Nonnull Tag flags14 bit0-clear; kind4 factory branch excluded by actual Tag kind44. Nested dispatch/6D6E50/84 association/animation and earlier named leaves remain supplied; no waypoint/production join.')
