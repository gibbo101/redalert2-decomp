# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact DSurface initializer and actual radar surface-kind associations."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x4aa4a0:0xfd,0x630b10:0x42,0x630cfd:0x38}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Surface startup requires exact supplied base')
 pe=pefile.PE(data=data);ops={};ranges={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete startup span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x4aa54f:('call','dword ptr [ecx + 0x18]'),0x4aa576:('call','dword ptr [ecx + 0x58]'),0x4aa59a:('ret','0xc'),0x630b43:('call','0x4aa4a0'),0x630d2b:('mov','dword ptr [esi], 0x79aef8')}.items():
  if ops.get(a)!=op:raise ValueError('Startup control differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete4AA4A0 with supplied allocation/CreateSurface/GetSurfaceDesc results. Actual radar first DSurface and second BSurface associations inspected, caller not executed. No runtime adoption.')
