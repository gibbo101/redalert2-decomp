#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the exact-base action11 Text Trigger dispatcher branch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_trigger_control import verify as verify_parent
RANGES={0x6adae0:0x38,0x6ae2ff:0x83,0x6af745:0x0f,0x77f110:0x3d}
TABLES={0x6af754:117*4}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Mission text action range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={
  0x6adb04:('mov','edx, dword ptr [esi + 0x2c]'),0x6adb11:('jmp','dword ptr [edx*4 + 0x6af754]'),
  0x6ae2ff:('mov','al, byte ptr [esi + 0x54]'),0x6ae302:('mov','ecx, dword ptr [0xa3d290]'),
  0x6ae308:('add','esi, 0x54'),0x6ae30b:('mov','bl, byte ptr [ecx + 0x2239]'),
  0x6ae311:('mov','ecx, 0xa3d298'),0x6ae325:('call','0x6715d0'),0x6ae32e:('je','0x6af745'),
  0x6ae334:('mov','edx, dword ptr [0x839848]'),0x6ae33b:('fld','qword ptr [edx + 0x1128]'),
  0x6ae341:('fmul','qword ptr [0x79b608]'),0x6ae347:('call','0x77f110'),
  0x6ae34d:('push','0x4046'),0x6ae353:('push','0x62e'),0x6ae358:('push','0x7f6bd0'),
  0x6ae35d:('xor','edx, edx'),0x6ae35f:('mov','ecx, esi'),0x6ae361:('call','0x6f9ec0'),
  0x6ae369:('mov','ecx, 0xa3dc70'),0x6ae36e:('call','0x5b4da0'),0x6ae373:('mov','al, 1'),
  0x77f12b:('fistp','qword ptr [eax]')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Mission text action association differs '+hex(a))
 table=struct.unpack('<117I',p.get_data(0x6af754-0x400000,117*4))
 if table[10]!=0x6ae2ff:raise ValueError('Mission text action dispatch differs')
 if struct.unpack('<d',p.get_data(0x79b608-0x400000,8))[0]!=900.:raise ValueError('Mission text duration scale differs')
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  duration_scale=900.0,scope='Complete base action11 branch and exact x87 delay conversion. Color-table lookup, CSF localization, message-list insertion, scenario/rules startup and inline action construction remain supplied children/inputs.')
