# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-base complete nonzero radar pixel parent and numeric leaves."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
from verify_surface_refresh import RANGES as REFRESH,verify as refresh_verify
RANGES={**REFRESH,0x632000:0x49f,0x77f110:0x3d}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Radar pixel requires exact supplied base')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete radar pixel inspection')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x632098:('call','0x77f110'),0x6320ae:('call','0x77f110'),0x6320ff:('call','0x568140'),0x632124:('call','0x568280'),0x6321b8:('call','0x4e5580'),0x63233d:('call','0x663d30'),0x632373:('idiv','dword ptr [ecx + 0x90]'),0x63248a:('mov','dword ptr [esi], edx'),0x63249c:('ret','4')}.items():
  if ops.get(a)!=op:raise ValueError('Radar pixel control differs '+hex(a))
 if p.get_data(0x79dd80-0x400000,4)!=struct.pack('<f',.5) or p.get_data(0x79a728-0x400000,8)!=struct.pack('<d',.5):raise ValueError('Radar projection constants differ')
 return dict(parent=refresh_verify(data),ranges=ranges,scope='Complete632000 and634030 nonzero branch with actual stock geometry and FTOL53-bit/toward-zero projection. Floor/discovery/House/type/color/resolver/pixel services and initial state supplied; no production/SDL adoption.')
