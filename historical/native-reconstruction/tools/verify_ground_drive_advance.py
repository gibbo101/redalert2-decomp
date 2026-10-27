#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete ordinary Advance and actual coordinate/floor/numeric children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ground_movement_placement import verify as placement_verify
from verify_map_floor_height import RANGES as FLOOR
EXTRA={0x4a1000:0x1649,0x4a4740:0x7c,0x4c9b10:0xa6,0x4c2df0:0x67,
 0x6d8e90:0x16,0x7220c0:0x72,0x4b8b10:0xca,0x4b8be0:0x99,
 0x41b320:0x3d,0x548000:0x68,0x548070:0x38,0x4ca160:0x40,
 0x5d51c0:0x1d,0x5d4860:0xb1,0x4f5a20:0x4c,0x453eb0:0x1c}
RANGES={**FLOOR,**EXTRA}
def verify(data):
 parent=placement_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Advance child '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 for off,target in ((0x19c,0x4ca160),(0x1a0,0x41b320),(0x1b4,0x5d4860),(0x338,0x6d8e90),(0x4bc,0x4c9b10),(0x4c8,0x4c2df0)):
  if p.get_data(0x7addf8+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Advance dispatch differs')
 # Inspected association only, not executed stock type initialization.
 if p.get_string_at_rva(0x7f7504-0x400000)!=b'Accelerates':raise ValueError('Acceleration key differs')
 if p.get_string_at_rva(0x7f807c-0x400000)!=b'IsTrain':raise ValueError('IsTrain key differs')
 association={}
 for a,n in ((0x6da50f,7),(0x6dd5d3,0x1a),(0x6da2dc,6),(0x6db03a,0x1a)):
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Unaligned acceleration association')
  association[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest(),'executed':False}
 tables={0x7a0180:768,0x7a00a0:112,0x7a05c0:24}
 # Include every ordinary stream, including its first zero/zero terminator.
 for j in range(1,7):
  a=struct.unpack('<I',p.get_data(0x7a00a0+16*j-0x400000,4))[0]
  for k in range(128):
   x,y=struct.unpack('<ii',p.get_data(a+12*k-0x400000,8))
   if k and x==0 and y==0:tables[a]=12*(k+1);break
  else:raise ValueError('Unterminated Advance stream')
 return {'placement_ancestor':parent,'ranges':ranges,'acceleration_association_inspection':association,
  'tables':{hex(a):{'bytes':n,'sha256':hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()} for a,n in tables.items()},
  'scope':'Complete Advance with committed ordinary track, queue=-1, Accelerates=0, IsTrain=0, onMap=1, nonbridge empty overlay-free Cells, no destination object/jumpjet/turret rotation/Passive switching. Actual transform, interpolation, speed, Facing, Foot/Object/map/floor children. Mark, occupation/notification/post-Cell effects and initial map/type/actor state supplied. Acceleration/train defaults and INI blocks are inspection only. No preparation/Process/body/world/runtime/startup/frame proof.'}
