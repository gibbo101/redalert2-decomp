#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Drive body pose, interpolation and stock initializer ancestors."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ramp_geometry import verify as geometry_verify,RANGES as GEOMETRY
from verify_actor_ground_state import verify as state_verify,COMPLETE as STATE,BLOCKS as PREFIX
EXTRA={0x4a0050:1189,0x53d030:159,0x718d60:28,0x718df0:116,0x622ac0:409,0x622eb0:245,
 0x4a4d20:28,0x5901b0:42,0x5901e0:42,0x590180:41,0x590880:156,0x591180:508,
 0x58fe10:22,0x4b8be0:153,0x705020:7,0x4ba580:40}
TAILS={0x6c12c0:8}
RANGES={**GEOMETRY,**STATE,**PREFIX,**EXTRA,**TAILS}
TABLES={0x80bdd4:4097*4,0x7a0f88:4,0x79b630:8,0x7a8660:8,0x79c520:8}
def verify(data):
 parent=geometry_verify(data);state=state_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in {**EXTRA,**TAILS}.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!=('jmp' if a in TAILS else 'ret'):raise ValueError('Incomplete Drive body range '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 for a,target in ((0x7a04f0,0x4a0050),(0x7addf8+0x80,0x6c12c0),(0x7addf8+0x84,0x705020)):
  if p.get_data(a-0x400000,4)!=struct.pack('<I',target):raise ValueError('Body/type dispatch differs')
 return {'geometry':parent,'state':state,'ranges':ranges,
  'tables':{hex(a):{'bytes':n,'sha256':hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()} for a,n in TABLES.items()},
  'scope':'Complete Drive body pose/key, actual Facing/type/matrix/table interpolation and stock numeric/initializer children. Optional actual Unlimbo or Process ramp prefix before pose in same guest. Finite rocking and supplied type doubles/actor/map/tick/Facing/initial timer state. Stock quaternion initialization compared; no general quaternion API/antipodal domain, actor height/placement, complete movement/Process, Unit drawing/runtime/startup/frame parity.'}
