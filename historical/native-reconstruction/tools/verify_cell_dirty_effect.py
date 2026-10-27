#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base47BB30 while exposing its five ordered early returns."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGE=(0x47bb30,0x47bc7a)
EXPECTED_SHA256='cfaf1c15a66466af138f4fd16cc1ff4e692e207514e7b519943780ceae1a0bfb'
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Cell dirty-effect engine required')
 p=pefile.PE(data=data);start,end=RANGE;raw=p.get_data(start-0x400000,end-start)
 if hashlib.sha256(raw).hexdigest()!=EXPECTED_SHA256:raise ValueError('Cell dirty-effect range differs')
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,start));
 if sum(i.size for i in ins)!=len(raw) or ins[-1].address!=0x47bc79 or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Cell dirty-effect range')
 ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 expected={0x47bb37:('cmp','dword ptr [ebx + 0x44], 0x7e'),0x47bb41:('cmp','byte ptr [ebx + 0x11e], 0x30'),
  0x47bb4e:('mov','al, byte ptr [ebx + 0x11c]'),0x47bb5c:('test','dword ptr [ebx + 0x140], 0x20000'),
  0x47bb6c:('mov','esi, dword ptr [ebx + 0xe4]'),0x47bc79:('ret','')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Cell dirty-effect association differs '+hex(a))
 return dict(range=dict(start=hex(start),end=hex(end),bytes=len(raw),instructions=len(ins),sha256=EXPECTED_SHA256),
  scope='Complete base47BB30 bytes with exact ordered overlay126/data48/flat/flag20000/primary-head gates. Differential execution covers all five early returns. Resident-bearing traversal, object effects, allocation and global construction remain refused/unentered.')
