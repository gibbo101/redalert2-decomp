# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the actual Walk retry/refill caller, not a replacement pathfinder."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_walk_speed as movement
import verify_infantry_destination as commands
from verify_walk_admission import RANGES as QUEUED
from verify_infantry_speed import RANGES as SPEED
EXTRA={0x508730:0x20,0x508ab0:0x23f}
RANGES={**QUEUED,**SPEED,**commands.RANGES,**EXTRA}
TABLES={**commands.TABLES,0x79b608:8}
SERVICES={0x4c3000:'supplied Foot route provider; writes the same route24',
 0x410290:'supplied target coordinates',0x548000:'supplied coordinate Cell',
 0x504740:'supplied animation',0x3c7594:'atomic increment',0x3c757c:'atomic decrement'}
def verify(data):
 base=dict(movement=movement.verify(data),commands=commands.verify(data))
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Walk route range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x71e2b9:('call','dword ptr [eax + 0x4cc]'),0x71e2d5:('fmul','qword ptr [0x79b608]'),
  0x71e2db:('call','0x77f110'),0x71e2ea:('mov','dword ptr [edi], edx'),
  0x71e2ef:('mov','dword ptr [edi + 8], eax'),0x71e325:('call','0x4c3000'),
  0x71e642:('mov','dword ptr [ecx + 0x53c], 0xa'),0x71e651:('call','dword ptr [edx + 0x484]'),
  0x508745:('mov','dword ptr [ecx + 0x5ac], 0xffffffff'),
  0x508ae3:('cmp','esi, 4'),0x508af2:('mov','cl, byte ptr [eax + 0xb44]')}.items():
  if ops.get(a)!=op:raise ValueError('Walk route association differs '+hex(a))
 for off,target in ((0x4cc,0x508730),(0x484,0x508ab0)):
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry route dispatch differs')
 if p.get_data(0x79b608-0x400000,8)!=struct.pack('<d',900.):raise ValueError('Route delay multiplier differs')
 return dict(parent=base,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  services={hex(a):s for a,s in SERVICES.items()},scope='Complete ordinary Walk Process retry wait or successful supplied route refill, with actual Infantry/Foot initial and arrival commands, admission/speed/head/occupation. Route provider, target coordinates, map/floor/Mark/notification/animation and initial records remain supplied. Failed routes, JumpJet children, special8 and nonzero admission refuse. No production/SDL walking/objectives.')
