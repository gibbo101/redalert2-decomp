# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin full constructor invocation; verify only its registration suffix."""
import hashlib,struct,pefile,capstone
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x4f90f0:0x258,0x4fb5c0:0x4a,0x4fb610:0x4a,0x4fb660:0x4a,0x40ffd0:0x25}
REG=0xa35d08;BASE_SERVICE=0x410580;RESIZE=0x5f1f000
SERVICES=(BASE_SERVICE,RESIZE)
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied country-registration executable required')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ops={};out={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Country constructor span differs '+hex(a))
  out[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x4f9298:('mov','eax, dword ptr [0xa35d18]'),0x4f92d1:('mov','eax, dword ptr [0xa35d18]'),0x4f9308:('mov','dword ptr [esi + 0xb8], ecx'),0x4f930e:('mov','eax, dword ptr [0xa35d18]'),0x4f933a:('mov','dword ptr [esi + 0xb4], ebx')}.items():
  if ops.get(a)!=op:raise ValueError('Country registry operation differs '+hex(a))
 return dict(ranges=out,registration_suffix_only=True,complete_original_constructor_invoked=True,base_and_list_startup_supplied=True,production_transfer_unjoined=True)
