#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base Cell visibility-mask calculation and map lookup."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x6a8d40:0x3dd,0x548070:0x38}
TABLE=0x7ac3bc
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied visibility-mask engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Visibility-mask PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete visibility-mask range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 expected={0x6a8d53:('call','0x548070'),0x6a8d5e:('je','0x6a8f34'),0x6a8d6a:('test','al, 3'),
  0x6a8d78:('test','bl, al'),0x6a8f3a:('test','al, 0x18'),0x6a8f48:('test','bl, al'),
  0x6a9106:('movsx','eax, byte ptr [ebp + 0x7ac3bc]'),0x6a9111:('ret','8'),
  0x6a9114:('mov','eax, edi'),0x6a911a:('ret','8')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Visibility-mask association differs '+hex(a))
 table=p.get_data(TABLE-0x400000,256)
 return dict(ranges=ranges,result_table_sha256=hashlib.sha256(table).hexdigest(),scope='Complete base6A8D40 primary/secondary center gates, eight wrapped neighbor lookups, exact mask composition and signed result-table selection with actual map548070. Startup result-table ownership remains supplied.')
