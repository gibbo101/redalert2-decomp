#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Drive/base shadow pose and initialized numeric ancestors."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_ramp_geometry import verify as verify_geometry,RANGES as GEOMETRY_RANGES
EXTRA={0x4a0500:0xb2,0x53d0d0:0xf0,0x718d60:28,0x4b8be0:153,0x548000:104}
RANGES={**GEOMETRY_RANGES,**EXTRA}
def verify(data):
 geometry=verify_geometry(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Drive shadow range differs')
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 if p.get_data(0x79d170-0x400000,8)!=struct.pack('<d',.005):raise ValueError('Drive rocking threshold differs')
 if p.get_data(0x7a04f4-0x400000,4)!=struct.pack('<I',0x4a0500):raise ValueError('Drive shadow dispatch differs')
 return {'ranges':ranges,'numeric_ancestors':geometry,'rocking_threshold':.005,
  'scope':'Complete Drive wrapper/base pose/key with actual full-coordinate map lookup, Facing and initialized 21 ramp matrices. Initial actor/locomotor/map/timer/Facing/CRT records and entry FP supplied. Finite rocking, null/-1/wrapped keys and all ramps. No Unit caller, actor height/placement/update, ownership/runtime/startup/frame claim.'}
