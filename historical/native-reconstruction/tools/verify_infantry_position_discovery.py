# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact Infantry revealed-Cell caller and discovery child dispatch."""
import struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_infantry_position_effects_e1 import verify as verify_parent
from verify_unit_discovery import verify as verify_discovery, COMPLETE
CHILDREN={a:COMPLETE[a] for a in (0x6c2440,0x5d4230,0x4f52f0,0x594770,0x594cb0)}
def verify(data):
 parent=verify_parent(data);child=verify_discovery(data);p=pefile.PE(data=data)
 ops={i.address:(i.mnemonic,i.op_str) for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.get_data(0x6c2bf0-0x400000,0x4f),0x6c2bf0)}
 expected={0x6c2bf0:('mov','al, byte ptr [esi + 0x373]'),0x6c2bf8:('jne','0x6c2c22'),
  0x6c2c09:('test','byte ptr [eax + 0x12c], 0x10'),0x6c2c10:('je','0x6c2c22'),
  0x6c2c12:('mov','eax, dword ptr [0xa35db4]'),0x6c2c1c:('call','dword ptr [edx + 0x180]')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Infantry discovery caller differs '+hex(a))
 dispatch={0x180:0x6c2440,0x16c:0x594770,0x1d0:0x594cb0}
 for off,target in dispatch.items():
  if p.get_data(0x7a3540+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry discovery dispatch differs')
 return dict(parent=parent,child=child,infantry_dispatch={hex(k):hex(v) for k,v in dispatch.items()},scope='Complete Infantry4C7220/6C2B40 revealed-Cell discovery through exact Infantry dispatch and complete Techno/Object/House/Mission/QueueMission. Null Tag only; initialization supplied; no production visibility binding or live sight.')
