#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin ordinary Cell visibility wrapper, parent and stock-E1 counter child."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED

RANGES={0x62fca0:0x1c,0x499fc0:0x129,0x47c840:0x5a,0x47c8a0:0x53,0x548070:0x38}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Cell visibility engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Cell visibility PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Cell visibility range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 expected={0x62fcaf:('call','0x499fc0'),0x62fcb9:('ret','0xc'),0x499fc9:('call','0x548070'),
  0x499fd0:('mov','eax, dword ptr [esi + 0x140]'),0x49a004:('mov','dword ptr [esi + 0x140], eax'),
  0x49a01b:('call','0x47c840'),0x49a029:('call','0x6a8d40'),0x49a03b:('mov','byte ptr [esi + 0x120], al'),
  0x49a061:('call','0x6a8d40'),0x49a074:('mov','byte ptr [esi + 0x121], cl'),
  0x49a09f:('call','0x6aadd0'),0x49a0b4:('call','0x568520'),0x49a0d9:('call','0x47be00'),
  0x49a0e6:('ret','0xc'),0x47c840:('cmp','dword ptr [ecx + 0x130], 1'),
  0x47c85a:('mov','dword ptr [ecx + 0x130], eax'),0x47c876:('mov','dword ptr [ecx + 0x12c], eax'),
  0x47c893:('mov','dword ptr [ecx + 0x140], eax'),0x47c899:('ret','')}
 expected.update({0x49a014:('call','0x47c8a0'),0x47c8a1:('mov','esi, dword ptr [ecx + 0x130]'),0x47c8ac:('mov','dword ptr [ecx + 0x130], 0'),0x47c8bd:('mov','dword ptr [ecx + 0x130], eax'),0x47c8cf:('mov','dword ptr [ecx + 0x130], eax'),0x47c8ec:('mov','dword ptr [ecx + 0x140], eax'),0x47c8f2:('ret','')})
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Cell visibility association differs '+hex(a))
 return dict(ranges=ranges,scope='Complete wrapper62FCA0 and parent499FC0 with low-byte-selected counter-decrement47C840/counter-increment47C8A0 and actual map548070. Visibility-mask6A8D40, redraw6AADD0, resident projection568520 and refresh47BE00 remain supplied.')
