#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base Unit +4B8 and its early-path children, without patching."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x705160:0x288,0x548070:0x38,0x5d4e40:0x21,0x6d7910:0x80,0x7133a0:0x27,0x713420:0x18}
DISPATCH={0x48:0x5d4e40,0x4b8:0x705160}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied next-Cell engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.OPTIONAL_HEADER.ImageBase!=0x400000 or p.FILE_HEADER.Machine!=0x14c:raise ValueError('Next-Cell PE layout differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete next-Cell range '+hex(a))
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for off,target in DISPATCH.items():
  if p.get_data(0x7addf8+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Next-Cell dispatch differs')
 for a,op in {0x70517b:('mov','eax, dword ptr [esi + 0x140]'),
  0x705196:('call','dword ptr [edx + 0x48]'),0x7051d9:('movsx','ecx, byte ptr [esi + 0x11b]'),
  0x7051f6:('mov','al, byte ptr [edx + 0xaf3]'),0x705202:('mov','ecx, edi'),
  0x705211:('mov','al, byte ptr [esp + 0x30]'),0x70521d:('test','byte ptr [esi + 0x128], 0x1f'),
  0x705245:('test','byte ptr [esi + 0x124], 0x1f'),0x70525a:('mov','esi, dword ptr [esi + 0xe8]'),
  0x705262:('mov','esi, dword ptr [esi + 0xe4]'),0x54809f:('mov','dword ptr [0xa6fa1c], edx'),
  0x7051a6:('sar','eax, 8'),0x7051ba:('lea','edx, [esp + 0xc]')}.items():
  if ops.get(a)!=op:raise ValueError('Next-Cell association differs '+hex(a))
 for a,n in ((0x79a708,1.),(0x79a6f8,2.)):
  if p.get_data(a-0x400000,8)!=struct.pack('<d',n):raise ValueError('Next-Cell promotion constant differs')
 return {'ranges':ranges,'Unit_dispatch':{hex(k):hex(v) for k,v in DISPATCH.items()},
  'scope':'Complete Unit +4B8 root with actual word lookup, coordinate getter and unpromoted ability17 children. Early noncrusher return or warning nonzero/selected low-five occupation zero. Warning delivery, warning0 list/crush, promoted ability and runtime excluded. Initial actor/type/Cell/slot associations supplied.'}
