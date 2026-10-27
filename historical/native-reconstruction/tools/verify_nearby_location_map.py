#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete nearby search with actual Cell/rectangle/permission/projection."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_nearby_location import verify as verify_policy,RANGES as POLICY,TABLES as PT
from verify_nearby_cell_admission import verify as verify_admission,RANGES as ADMISSION,TABLES as AT
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={**{a:n for a,n in POLICY.items() if a!=0x49f600},**ADMISSION,0x6a6a50:0x17b,0x548070:0x38}
TABLES={**PT,**AT}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied nearby map engine required')
 inherited=[verify_policy(data),verify_admission(data)];p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete nearby map range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest());ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,op in {0x6a6aae:('call','0x548070'),0x6a6ac9:('call','0x548070'),0x6a6b33:('call','0x548070'),0x6a6b56:('shl','ecx, 7'),0x6a6b8e:('jle','0x6a6ba7')}.items():
  if ops.get(a)!=op:raise ValueError('Nearby projection association differs '+hex(a))
 return dict(inherited=inherited,ranges=ranges,tables={hex(a):dict(bytes=n,sha256=hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest()) for a,n in TABLES.items()},
  scope='Complete nearby5502E0 with actual direct permission55A740, rectangle550CF0/Cell478760, projection6A6A50/map548070 and table sqrt4BA410. Shared Cells/slots/fallback. Zone-1 (including caller65535 normalization), burrow0; entered other children refused. Initial records/type/speeds/dimensions/frame/sentinel supplied. No Unit/Cell Scatter/Advance6/Process/production world/runtime join.')
