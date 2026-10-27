#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect exact-base Enable/Disable Trigger action branches."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_trigger import verify as verify_parent,RANGES as PARENT_RANGES,TABLES as PARENT_TABLES
ACTION_RANGES={0x6adae0:0x38,0x6af1ea:0x2d,0x6af217:0x49,0x6af745:0x0f,0x6b1f10:0x7f,0x6edb60:0x09,0x6edb70:0x05}
RANGES={**PARENT_RANGES,**ACTION_RANGES};TABLES={**PARENT_TABLES,0x6af754:117*4}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Mission Trigger control range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x6adb04:('mov','edx, dword ptr [esi + 0x2c]'),0x6adb11:('jmp','dword ptr [edx*4 + 0x6af754]'),
  0x6af205:('call','0x6b1f10'),0x6af217:('cmp','dword ptr [esi + 0x50], ebp'),0x6af242:('call','0x6edb70'),
  0x6b1f14:('mov','eax, dword ptr [edi + 0x50]'),0x6b1f1b:('mov','eax, dword ptr [0xa40ab0]'),
  0x6b1f2f:('mov','ecx, dword ptr [eax + esi*4]'),0x6b1f3f:('mov','edx, dword ptr [edx + 0x60c]'),
  0x6b1f71:('call','0x6edb60'),0x6edb60:('mov','byte ptr [ecx + 0x40], 1'),
  0x6edb64:('jmp','0x6ed680'),0x6edb70:('mov','byte ptr [ecx + 0x40], 0')}.items():
  if ops.get(a)!=op:raise ValueError('Mission Trigger control association differs '+hex(a))
 table=struct.unpack('<117I',p.get_data(0x6af754-0x400000,117*4))
 if table[52]!=0x6af1ea or table[53]!=0x6af217:raise ValueError('Mission Trigger control action dispatch differs')
 full=p.get_data(0x6adae0-0x400000,0x6af752-0x6adae0)
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  full_dispatcher_sha256=hashlib.sha256(full).hexdigest(),scope='Complete base action53 Enable Trigger and action54 Disable Trigger branches, live registry/type/target/difficulty traversal and inherited complete timer reset. Action construction, scenario difficulty startup and caller stack scratch supplied; other actions/runtime excluded.')
