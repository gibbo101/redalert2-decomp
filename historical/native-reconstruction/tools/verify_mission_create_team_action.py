#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the exact-base action4 Create Team dispatcher branch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_trigger import verify as verify_parent
RANGES={0x6adae0:0x38,0x6aec7d:0x36}
TABLES={0x6af754:117*4}
GLOBALS={0xa40774:4}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Mission Create Team action range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={
  0x6adb04:('mov','edx, dword ptr [esi + 0x2c]'),0x6adb11:('jmp','dword ptr [edx*4 + 0x6af754]'),
  0x6aec7d:('mov','ecx, dword ptr [0xa40774]'),0x6aec83:('inc','ecx'),0x6aec84:('mov','dword ptr [0xa40774], ecx'),
  0x6aec8a:('mov','esi, dword ptr [esi + 0x30]'),0x6aec8d:('cmp','esi, ebp'),0x6aec8f:('je','0x6aec99'),
  0x6aec91:('push','ebp'),0x6aec92:('mov','ecx, esi'),0x6aec94:('call','0x6bec80'),
  0x6aec99:('mov','eax, dword ptr [0xa40774]'),0x6aec9e:('dec','eax'),0x6aec9f:('mov','dword ptr [0xa40774], eax'),
  0x6aeca4:('mov','al, 1')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Mission Create Team action association differs '+hex(a))
 table=struct.unpack('<117I',p.get_data(0x6af754-0x400000,117*4))
 if table[3]!=0x6aec7d:raise ValueError('Mission Create Team action dispatch differs')
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},globals={hex(a):n for a,n in GLOBALS.items()},
  scope='Complete base action4 Create Team dispatcher branch. TeamType pointer construction, child6BEC80 effects and global startup/sharing remain supplied.')
