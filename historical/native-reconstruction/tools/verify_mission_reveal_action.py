#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the exact-base action17 Reveal Around Waypoint dispatcher branch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_trigger import verify as verify_parent
RANGES={0x6adae0:0x38,0x6ae588:0x2d}
TABLES={0x6af754:117*4}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Mission Reveal action range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={
  0x6adaed:('mov','ecx, dword ptr [esp + 0x244]'),0x6adafb:('mov','dl, byte ptr [ecx + 0x7d]'),0x6adb02:('xor','ecx, ecx'),
  0x6adb04:('mov','edx, dword ptr [esi + 0x2c]'),0x6adb11:('jmp','dword ptr [edx*4 + 0x6af754]'),
  0x6ae588:('mov','eax, dword ptr [esp + 0x250]'),0x6ae58f:('mov','edx, dword ptr [esp + 0x24c]'),
  0x6ae597:('mov','eax, dword ptr [esp + 0x248]'),0x6ae59f:('push','ecx'),0x6ae5a1:('mov','ecx, esi'),
  0x6ae5a3:('call','0x6b0670'),0x6ae5b2:('ret','0x10')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Mission Reveal action association differs '+hex(a))
 table=struct.unpack('<117I',p.get_data(0x6af754-0x400000,117*4))
 if table[16]!=0x6ae588:raise ValueError('Mission Reveal action dispatch differs')
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  scope='Complete base action17 dispatcher forwarding and low-byte result. Child6B0670 reveal/map effects and action argument construction remain supplied.')
