#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the complete base initializer and every numerical child entered by this profile."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from compare_original import PATCHED_EXPECTED
RANGES={0x718060:3290,0x590060:43,0x58ff50:263,0x591380:120,0x58fef0:92,
 0x5909a0:156,0x590760:158,0x6229b0:266,0x622250:59,0x622180:30,
 0x4ba410:0x6e,0x4ba480:66,0x4ba4d0:73,0x77f110:61}
TABLE=0xaf8608
OUTPUTS=((0xaf6618,0x150),(0xaf6768,0xc00),(0xaf73a0,0x3f0),(0xaf77a8,48),
 (0xaf77e8,0x140),(0xaf7930,0xc00),(0xaf8538,0x4c0))
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
 p=pefile.PE(data=data)
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Ramp shadow PE layout differs')
 cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete ramp shadow root/child')
  ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
 return {'ranges':ranges,'shadow_table':hex(TABLE),'matrices':21,
  'scope':'Complete original initializer and numerical children execute; only 21 final shadow matrices compared. Two tilt globals/camera/light globals and initial output storage supplied. No native parity for other initializer outputs, ordered native writes, angle startup, Drive integration or frame claim.'}
