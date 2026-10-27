#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base500AA0 and the bounded ordinary-E1 associations."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
from verify_cell_resident_kind6 import verify as verify_resident
START,END=0x500aa0,0x501ca9
HELPERS={0x594770:0x12,0x4717b0:0x2f,0x473e30:0x43,0x473e80:0x43,0x47cf80:6,0x71dea0:0xa}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Infantry update-position engine required')
 p=pefile.PE(data=data);c=Cs(CS_ARCH_X86,CS_MODE_32);raw=p.get_data(START-0x400000,END-START);ins=list(c.disasm(raw,START));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=len(raw):raise ValueError('Incomplete Infantry update-position range')
 expected={0x500adc:('cmp','eax, 2'),0x5014c0:('mov','cl, byte ptr [eax + 0xc14]'),0x501571:('cmp','eax, 0xb'),0x5015f5:('call','dword ptr [edx + 0x16c]'),0x50177d:('cmp','eax, 0x11'),0x501aa3:('mov','al, byte ptr [esi + 0x370]'),0x501b33:('cmp','dword ptr [esi + 0xa0], -1'),0x501b6d:('call','dword ptr [edx + 0x1d4]'),0x501b7f:('call','dword ptr [eax + 0x41c]'),0x501b91:('call','dword ptr [edx + 0x418]'),0x501bcb:('call','0x54a550'),0x501bee:('call','0x548000'),0x501c18:('call','dword ptr [ecx + 0x10]'),0x501c9a:('call','0x4c7220')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Infantry update-position association differs '+hex(a))
 vtable=0x7a3540
 for off,target in ((0x16c,0x594770),(0x1a4,0x5d51e0),(0x174,START),(0x1d4,0x594c50),(0x418,0x6d5c30),(0x41c,0x6d5e90)):
  if p.get_data(vtable+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Infantry update-position vtable differs '+hex(off))
 helpers={}
 for a,n in HELPERS.items():
  b=p.get_data(a-0x400000,n);decoded=list(c.disasm(b,a))
  if sum(i.size for i in decoded)!=n:raise ValueError('Incomplete helper '+hex(a))
  helpers[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest())
 return dict(range={hex(START):dict(bytes=len(raw),instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())},helpers=helpers,
  resident_search=verify_resident(data),vtable=hashlib.sha256(p.get_data(vtable-0x400000,0x420)).hexdigest(),
  scope='Complete base500AA0 with a bounded argument2 ordinary-E1 path: actual mission getter and initialized empty Cell kind-6 resident helpers, supplied map/target-coordinate/sight/post-update children. Alternate mission/type/resident/locomotor tails remain refused.')
