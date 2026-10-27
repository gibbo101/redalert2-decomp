#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base508530 and its ordinary null-target base6C1380 path."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED

RANGES={0x508530:0x40,0x6c1380:0x250}
HELPERS={0x6c12c0:8,0x506950:7,0x6df680:0xe,0x6d8540:0x55,
         0x713420:0x18,0x6df5c0:0x17,0x6df5e0:0x17,0x594770:0x12,0x509800:6}

def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:
  raise ValueError('Exact supplied Infantry weapon-selection engine required')
 p=pefile.PE(data=data);c=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in {**RANGES,**HELPERS}.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Infantry weapon-selection range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={
  0x508530:('mov','eax, dword ptr [ecx + 0x5ac]'),0x508550:('mov','dl, byte ptr [eax + 0x5cc]'),
  0x508568:('call','0x6c1380'),0x6c1388:('call','dword ptr [eax + 0x80]'),
  0x6c1390:('call','0x6df680'),0x6c13b5:('call','dword ptr [edx + 0x39c]'),
  0x6c13cb:('call','dword ptr [eax + 0x39c]'),0x6c13db:('mov','al, byte ptr [ebp + 0x112]'),
  0x6c13e9:('mov','al, byte ptr [ebp + 0x126]'),0x6c13f7:('call','dword ptr [edx + 0x16c]'),
  0x6c1412:('call','dword ptr [eax + 0x2c]'),0x6c146c:('test','esi, esi'),
  0x6c15a0:('xor','eax, eax'),0x6d8568:('call','dword ptr [eax + 0x80]'),
  0x6d8583:('call','dword ptr [edx + 0x80]'),0x6d858b:('call','0x6df5c0')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Infantry weapon-selection association differs '+hex(a))
 vtable=0x7a3540
 associations=((0x2c,0x509800),(0x80,0x6c12c0),(0x84,0x506950),(0x16c,0x594770),
               (0x2b8,0x508530),(0x39c,0x6d8540))
 for off,target in associations:
  if p.get_data(vtable+off-0x400000,4)!=struct.pack('<I',target):
   raise ValueError('Infantry weapon-selection vtable differs '+hex(off))
 return dict(ranges=ranges,vtable=hashlib.sha256(p.get_data(vtable-0x400000,0x3a0)).hexdigest(),
  associations={hex(o):hex(t) for o,t in associations},
  scope='Complete base508530 and base6C1380 with actual type, multiple-turret, normal/elite weapon-slot, mission and Infantry-kind helpers through null target. States27..30, positive turret count and nonnull target branches remain refused.')
