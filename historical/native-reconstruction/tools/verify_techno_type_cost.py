# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Type cost, House multiplier, E1 kind/base and FTOL children."""
import hashlib,struct,pefile,capstone
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x6dad30:0x45,0x4f5960:0x80,0x6dace0:7,0x50af60:6,0x77f110:0x3d}
TABLES={0x4f59e0:58,0x79b7f8:4,0x7d8964:4}
KIND=0x5e1f000
SERVICES=(KIND,)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Type-cost executable required')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);out={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Type-cost span '+hex(a))
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x84,0x6dad30),(0xac,0x6dace0),(0x2c,0x50af60)):
  if p.get_data(0x7a3a78+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('InfantryType cost dispatch differs')
 t=p.get_data(0x4f59e0-0x400000,58)
 for kind in range(3,41):
  want={3:0x4f59a2,7:0x4f59b0,16:0x4f5986,40:0x4f5994}.get(kind,0x4f59d5)
  if struct.unpack_from('<I',t,4*t[20+kind-3])[0]!=want:raise ValueError('House cost dispatch differs')
 for a,op in {0x6dad46:('fstp','dword ptr [esp + 4]'),0x6dad4a:('call','dword ptr [eax + 0xac]'),0x6dad58:('fmul','dword ptr [esp + 4]'),0x6dad5c:('call','0x77f110')}.items():
  if ops.get(a)!=op:raise ValueError('Type cost operation differs '+hex(a))
 if p.get_data(0x79b7f8-0x400000,4)!=struct.pack('<f',1.) or p.get_data(0x7d8964-0x400000,4)!=struct.pack('<I',0xe7f):raise ValueError('Cost constant/FP control differs')
 return dict(ranges=out,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},complete_type_cost_and_house_multiplier=True,actual_E1_kind_base_and_ftol=True,other_kind_query_and_startup_supplied=True,live_transfer_unjoined=True)
