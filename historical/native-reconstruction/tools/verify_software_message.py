#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base message chain with actual software DSurface fill dispatch."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_message import verify as mission,RANGES as MISSION,TABLES
from verify_surface_fill import verify as fill,RANGES as FILL
EXTRA={0x4ab4f0:0x2b,0x4ab520:0x20e,0x4112d0:4}
RANGES={**MISSION,**FILL,**EXTRA}
ASSOCIATIONS={0x5198ea:0x3f,0x4aa4a0:0x36,0x4b37c0:0x18}
def verify(data):
 parent=mission(data);surface=fill(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in {**EXTRA,**ASSOCIATIONS}.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete display fill inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x4ab50f:('call','0x4ab520'),0x4ab52e:('test','eax, eax'),0x4ab553:('mov','al, byte ptr [0x7d6294]'),0x4ab55a:('je','0x4ab6fc'),0x4ab70f:('call','0x7743c0'),0x519912:('call','0x4aa4a0'),0x51991b:('mov','dword ptr [0x839958], eax'),0x4aa4d0:('mov','dword ptr [esi], 0x7a0be4'),0x4b37c0:('mov','eax, dword ptr [0x839958]'),0x4b37d2:('mov','dword ptr [0x83995c], eax')}.items():
  if ops.get(a)!=op:raise ValueError('Display fill association differs '+hex(a))
 if struct.unpack('<2I',p.get_data(0x7a0be4-0x400000+16,8))!=(0x4ab520,0x4ab4f0):raise ValueError('Display fill slots differ')
 return dict(mission=parent,fill=surface,ranges=ranges,scope='Actual mission/list/text through4AB4F0/4AB520 hardware-enable-byte0 software path and7743C0; supplied shared surface interface/allocation/nonzero descriptor/lock/unlock. Constructor/default/current association fragments inspected only, no startup/device/UI claim.')
