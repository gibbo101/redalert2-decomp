# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the complete Cell wall-damage parent and its existing children."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_map_wall_update import verify as wall_verify,RANGES as WALL
from verify_random_range import verify as random_verify,RANGES as RANDOM
RANGES={**WALL,**RANDOM,0x475fe0:0x3ef}
def verify(data):
 wall=wall_verify(data);random=random_verify(data);p=pefile.PE(data=data)
 code=p.get_data(0x475fe0-0x400000,0x3ef);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,0x475fe0))
 ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=len(code) or ops.get(0x4763cc)!=('ret','4'):
  raise ValueError('Incomplete wall damage root')
 for a,op in {0x475fef:('je','0x4763c3'),0x47601f:('cmp','esi, eax'),
  0x47603c:('call','0x6388a0'),0x476127:('sub','ecx, esi'),
  0x47614b:('mov','byte ptr [edi + 0x11e], al'),0x4761df:('call','0x475fe0'),
  0x476226:('mov','dword ptr [edi + 0x50], esi'),0x476229:('mov','dword ptr [edi + 0x44], esi'),
  0x47622c:('mov','byte ptr [edi + 0x11e], 0'),0x4763ac:('mov','byte ptr [eax + 0x122], dl')}.items():
  if ops.get(a)!=op:raise ValueError('Wall damage association differs '+hex(a))
 call=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.get_data(0x6ff2f3-0x400000,5),0x6ff2f3))
 if len(call)!=1 or (call[0].mnemonic,call[0].op_str)!=('call','0x475fe0'):
  raise ValueError('Unit wall removal caller differs')
 return dict(wall=wall,random=random,root=dict(bytes=len(code),instructions=len(ins),sha256=hashlib.sha256(code).hexdigest()),
  scope='Complete Cell475FE0 with actual inclusive RNG, recursive damage and wall-update children; supplied initial records, map lookups, bounds/camera, dirty/zone/expiration and recalculation services. Unit notification caller, complete Unit tick and runtime traversal excluded.')
