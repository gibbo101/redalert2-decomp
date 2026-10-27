# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete6D7C80; named Foot children remain supplied services."""
import hashlib,pefile,capstone
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x6d7c80:0x93}
SERVICES=(0x5f1f000,0x5f1f010,0x5f1f020)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied reference-cleanup executable required')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ops={};out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Reference cleanup span differs')
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x6d7c80:('mov','eax, dword ptr [0xa40c30]'),0x6d7c94:('mov','ecx, dword ptr [0xa40c24]'),0x6d7cc4:('mov','dword ptr [esi + 0xa8], ebx'),0x6d7cca:('mov','byte ptr [esi + 0x5ba], bl'),0x6d7ce7:('mov','eax, dword ptr [0x866188]'),0x6d7cf3:('mov','edx, dword ptr [0x86617c]')}.items():
  if ops.get(a)!=op:raise ValueError('Reference cleanup operation differs '+hex(a))
 return dict(ranges=out,complete_parent=True,foot_children_supplied=True,production_transfer_unjoined=True)
