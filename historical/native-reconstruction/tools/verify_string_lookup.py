#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint supplied-base localization lookup and its real CRT search/comparator."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
EXPECTED='e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f'
RANGES={0x6f9ec0:0x62,0x782025:0x8c,0x781f20:0xd0}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('String lookup requires exact supplied base target')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete string lookup inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={0x6f9eca:('mov','dword ptr [esi], 0'),0x6f9ed0:('mov','eax, dword ptr [0xad0440]'),0x6f9eda:('mov','eax, 0x7f8eb8'),0x6f9ee3:('mov','ecx, dword ptr [0xad0438]'),0x6f9ee9:('push','0x781f20'),0x6f9eee:('push','0x28'),0x6f9ef3:('call','0x782025'),0x6f9efd:('je','0x6f9f22'),0x6f9f03:('mov','edx, dword ptr [eax + 0x24]'),0x6f9f0c:('mov','edx, dword ptr [ecx + edx*4]'),0x6f9f0f:('mov','dword ptr [esi], edx'),0x6f9f11:('mov','eax, dword ptr [eax + 0x24]'),0x6f9f1c:('mov','eax, dword ptr [ecx + eax*4]'),0x782050:('jne','0x782055'),0x782052:('lea','eax, [ebx - 1]'),0x782062:('call','dword ptr [ebp + 0x18]'),0x781f32:('cmp','dword ptr [eax + 8], 0'),0x781f36:('jne','0x781f73'),0x781f4a:('sub','al, 0x41'),0x781f4c:('cmp','al, 0x1a'),0x781f6e:('movsx','eax, al')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('String lookup association differs '+hex(a))
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Base6F9EC0 found/no-label paths, complete CRT782025 and actual CRT781F20 locale-zero comparison. Missing-label allocation/formatting/logging and nonzero CRT locale remain unjoined; initial label/text/extra registry and CSF loading supplied.')
