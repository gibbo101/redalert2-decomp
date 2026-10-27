#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the exact-base action37 Make Ally dispatcher branch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_trigger import verify as verify_parent
RANGES={0x6adae0:0x38,0x6ae382:0x3d,0x6af745:0x0f}
TABLES={0x6af754:117*4}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Mission ally action range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={
  0x6adb04:('mov','edx, dword ptr [esi + 0x2c]'),0x6adb11:('jmp','dword ptr [edx*4 + 0x6af754]'),
  0x6ae382:('mov','esi, dword ptr [esi + 0x74]'),0x6ae385:('cmp','esi, -1'),0x6ae388:('je','0x6af745'),
  0x6ae390:('call','0x4ed760'),0x6ae395:('mov','edi, dword ptr [esp + 0x244]'),
  0x6ae39e:('push','ebp'),0x6ae39f:('push','esi'),0x6ae3a2:('call','0x4e5660'),
  0x6ae3a7:('push','ebp'),0x6ae3a8:('push','edi'),0x6ae3ab:('call','0x4e5660'),0x6ae3b0:('mov','al, 1')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Mission ally action association differs '+hex(a))
 table=struct.unpack('<117I',p.get_data(0x6af754-0x400000,117*4))
 if table[36]!=0x6ae382:raise ValueError('Mission ally action dispatch differs')
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  scope='Complete base action37 Make Ally dispatcher branch. House lookup, House MakeAlly effects, action construction and House startup/association remain supplied children/inputs.')
