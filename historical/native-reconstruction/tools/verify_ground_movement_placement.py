#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Foot/Object setters and aligned Drive placement blocks."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_actor_ground_state import verify as ground_verify,RANGES as GROUND
COMPLETE={0x4ca160:0x40,0x5d51c0:0x1d}
PARENT={0x4a1000:0x1649}
BLOCKS={0x4a2054:0xbe,0x4a1ab0:0x4b}
RANGES={**GROUND,**COMPLETE,**BLOCKS}
def verify(data):
 ground=ground_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};bounds=set()
 for a,n in {**COMPLETE,**PARENT}.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete placement range '+hex(a))
  bounds.update(i.address for i in ins);bounds.add(a+n)
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest(),'execution':'blocks-only' if a in PARENT else 'complete'}
 blocks={}
 for a,n in BLOCKS.items():
  if a not in bounds or a+n not in bounds:raise ValueError('Unaligned placement block')
  raw=p.get_data(a-0x400000,n)
  blocks[hex(a)]={'bytes':n,'instructions':len(list(cs.disasm(raw,a))),'sha256':hashlib.sha256(raw).hexdigest()}
 for a,v in ((0x7addf8+0x19c,0x4ca160),(0x7addf8+0x1b4,0x5d4860),(0x7addf8+0x11c,0x4c2e60)):
  if p.get_data(a-0x400000,4)!=struct.pack('<I',v):raise ValueError('Ground placement dispatch differs')
 return {'ground':ground,'ranges':ranges,'blocks':blocks,'scope':'Complete Foot/Object SetLocation and actual relative-height/map/floor children. Only two aligned Drive Advance placement blocks, candidate/register/caller scratch supplied; not full Advance/Process/route/clearance. Mark effects and initial map/actor state supplied. No body/world/runtime/startup/frame parity.'}
