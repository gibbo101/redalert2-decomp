#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the exact-base visibility-change resident discovery projection."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x568520:0xca,0x471660:0xfa,0x5d4e40:0x21,0x4ba410:0x6e,0x77f110:0x3d}
CALLS=(0x499f87,0x49a0b4,0x49a331,0x49a59c,0x55a397,0x55a46e)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied visibility engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Visibility PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete visibility discovery range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest());ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 expected={0x56852a:('mov','ecx, dword ptr [eax + 0x24]'),0x568573:('movsx','eax, byte ptr [esi + 0x11b]'),
  0x56857a:('lea','ecx, [edi - 2]'),0x568585:('mov','al, byte ptr [esp + 0x24]'),0x568596:('call','0x6328f0'),
  0x5685ae:('call','0x471660'),0x5685c0:('call','dword ptr [edx + 0x180]'),0x5685c6:('inc','bp'),
  0x5685c8:('add','edi, 2'),0x5685cb:('inc','bx'),0x47169f:('mov','ecx, dword ptr [ecx + 0xe4]'),
  0x4716b7:('mov','al, byte ptr [esi + 0x14]'),0x4716c2:('cmp','esi, dword ptr [ebp + 0x10]'),
  0x4716d0:('call','dword ptr [edx + 0x48]'),0x471737:('mov','esi, dword ptr [esi + 0x30]')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Visibility discovery association differs '+hex(a))
 raw_calls=[]
 for section in p.sections:
  raw=section.get_data();base=p.OPTIONAL_HEADER.ImageBase+section.VirtualAddress
  for i in range(len(raw)-4):
   if raw[i]==0xe8 and ((base+i+5+struct.unpack_from('<i',raw,i+1)[0])&0xffffffff)==0x568520:raw_calls.append(base+i)
 if tuple(raw_calls)!=CALLS:raise ValueError('Visibility discovery caller inventory differs')
 return dict(ranges=ranges,callers=[hex(x) for x in CALLS],scope='Complete base568520 seven-Cell visibility-change projection with actual closest resident/numeric/coordinate children and supplied Cell notification/DiscoveredBy effects. Reveal-area and Techno sight parents remain unjoined.')
