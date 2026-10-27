#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect the exact-base action19 sound and action21 speech branches."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_trigger import verify as verify_parent
RANGES={0x6adae0:0x38,0x6ae961:0x22,0x6aead3:0x1e}
TABLES={0x6af754:117*4}
def verify(data):
 parent=verify_parent(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Mission audio action range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={
  0x6adb04:('mov','edx, dword ptr [esi + 0x2c]'),0x6adb11:('jmp','dword ptr [edx*4 + 0x6af754]'),
  0x6ae961:('mov','ecx, dword ptr [esi + 0x74]'),0x6ae964:('push','ebp'),0x6ae965:('mov','edx, 0x2000'),
  0x6ae96a:('push','0x3f800000'),0x6ae96f:('call','0x713db0'),0x6ae974:('mov','al, 1'),
  0x6aead3:('mov','ecx, dword ptr [esi + 0x74]'),0x6aead6:('push','-1'),0x6aead8:('mov','edx, 2'),
  0x6aeadd:('call','0x7158c0'),0x6aeae2:('mov','al, 1')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Mission audio action association differs '+hex(a))
 table=struct.unpack('<117I',p.get_data(0x6af754-0x400000,117*4))
 if table[18]!=0x6ae961 or table[20]!=0x6aead3:raise ValueError('Mission audio action dispatch differs')
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  scope='Complete base action19 sound and action21 speech dispatcher branches. Audio children, index construction, audio startup/state and playback remain supplied.')
