#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base6C2990 and its two ordered cloak-prefix exits."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED

RANGE=(0x6c2990,0x6c2b35)
EXPECTED_SHA256='0c679420f3e9152c6ef66b3958a1c4bb15ef580d4a2783c75842f34dfa358d89'
HELPERS={0x5d4e40:0x21,0x548070:0x38,0x47c2c0:0x1b}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied position cloak-effect engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for start,end in ((RANGE[0],RANGE[1]),*((a,a+n) for a,n in HELPERS.items())):
  raw=p.get_data(start-0x400000,end-start);ins=list(cs.disasm(raw,start))
  if sum(i.size for i in ins)!=len(raw):raise ValueError('Incomplete position cloak-effect range '+hex(start))
  ranges[hex(start)]=dict(bytes=len(raw),instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 if ranges[hex(RANGE[0])]['sha256']!=EXPECTED_SHA256 or ops.get(0x6c2b34)!=('ret',''):
  raise ValueError('Complete position cloak-effect range differs')
 expected={0x6c299f:('call','dword ptr [eax + 0x48]'),0x6c29dd:('call','0x548070'),
  0x6c29ee:('call','0x47c2c0'),0x6c29ff:('call','dword ptr [eax + 0x280]'),
  0x47c2cb:('mov','eax, dword ptr [eax + 0x78]')}
 for address,op in expected.items():
  if ops.get(address)!=op:raise ValueError('Position cloak-effect association differs '+hex(address))
 vtable=0x7a3540
 for off,target in ((0x48,0x5d4e40),(0x280,0x6c9020)):
  if p.get_data(vtable+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Position cloak-effect vtable differs '+hex(off))
 return dict(ranges=ranges,associations={'Infantry+48':'0x5d4e40','Infantry+280':'0x6c9020'},
  scope='Complete base6C2990 bytes with actual coordinates, map lookup and Cell+78 House-bit helper through Cell-mask and supplied actor-predicate early returns. Entered global object traversal, temporary allocation, target notifications and actor effect remain refused.')
