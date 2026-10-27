#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base complete software rectangle fill and BSurface child inspection."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x774390:0x29,0x7743c0:0x2ec,0x41fdf0:0x121,0x453e40:0x21,0x435560:0x11,0x411290:0x24,0x411370:0x31,0x4112f0:0xa,0x4113b0:4,0x4113c0:0xe,0x4112c0:4}
VT=0x79aef8
SLOTS={5:0x774390,4:0x7743c0,23:0x411370,24:0x4112f0,28:0x4113b0,29:0x4113c0,30:0x411290,31:0x4112c0}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Surface fill requires exact supplied base')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete surface fill inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x7743ad:('call','0x7743c0'),0x7743ff:('call','0x41fdf0'),0x774469:('call','0x41fdf0'),0x7744c1:('call','dword ptr [edx + 0x5c]'),0x7744d8:('cmp','eax, 1'),0x7745e5:('or','eax, ebx'),0x774651:('or','eax, ebx')}.items():
  if ops.get(a)!=op:raise ValueError('Surface fill association differs '+hex(a))
 slots={str(k):hex(struct.unpack('<I',p.get_data(VT-0x400000+4*k,4))[0]) for k in SLOTS}
 if slots!={str(k):hex(v) for k,v in SLOTS.items()}:raise ValueError('BSurface fill slots differ')
 return dict(executable_sha256=EXPECTED,ranges=ranges,slots=slots,scope='Complete774390/7743C0 on supplied ordinary1/2-byte BSurface allocation; actual clipping/lock/unlock/pitch and ordered byte/word/dword stores. Optional intersection adjustment pointers null. No DSurface/message-global/UI claim.')
