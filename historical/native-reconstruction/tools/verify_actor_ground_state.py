#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin relative SetHeight, Drive ramp writers and their actual map children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_map_floor_height import verify as verify_floor,RANGES as FLOOR
COMPLETE={0x5d4860:0xb1,0x49fc30:0x35,0x4a05c0:0x25,0x5d51e0:0x57,
          0x548000:0x68,0x463f80:0x14}
PARENTS={0x4a05f0:0x5cb}
BLOCKS={0x4a05f0:0x5a}
RANGES={**FLOOR,**COMPLETE,**BLOCKS}
def verify(data):
 floor=verify_floor(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};bounds=set();ops={}
 for a,n in {**COMPLETE,**PARENTS}.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Ground state incomplete range '+hex(a))
  bounds.update(i.address for i in ins);bounds.add(a+n);ops.update((i.address,i.op_str) for i in ins)
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest(),'execution':'prefix-only' if a in PARENTS else 'complete'}
 blocks={}
 for a,n in BLOCKS.items():
  if a not in bounds or a+n not in bounds:raise ValueError('Unaligned Drive Process prefix')
  blocks[hex(a)]={'bytes':n,'instructions':len(list(cs.disasm(p.get_data(a-0x400000,n),a))),'sha256':hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()}
 for a,target in ((0x7addf8+0x1b4,0x5d4860),(0x7addf8+0x1a4,0x5d51e0),(0x7addf8+0x11c,0x4c2e60),
  (0x7a04cc+0x50,0x4a05c0),(0x7a04cc+0x7c,0x49fc30),(0x7a04cc+0x40,0x4a05f0)):
  if p.get_data(a-0x400000,4)!=struct.pack('<I',target):raise ValueError('Ground state dispatch differs')
 for a,op in ((0x4a061a,'dword ptr [edi + 0x20], ecx'),(0x4a0623,'dword ptr [edi + 0x1c], eax'),
  (0x49fc3d,'dword ptr [eax + 0x1c], ecx'),(0x49fc40,'dword ptr [eax + 0x18], ecx')):
  if ops[a]!=op:raise ValueError('Ground ramp field association differs')
 return {'floor':floor,'ranges':ranges,'blocks':blocks,
  'scope':'Complete Object relative SetHeight, Drive Force_New_Slope and Unlimbo; actual repeated Object current-Cell/map/floor children. Process only entry through 0x4A064A, no suffix/movement/placement caller. Mark effects, initial map/actor/locomotor and copied temporary timer padding supplied. No runtime, body-pose, construction, startup or frame parity.'}
