# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied-base scheme resolver and reused locale-zero comparator."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x663d30:0x5a,0x781f20:0xd0}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Scheme resolver requires exact supplied base')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete scheme instruction span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x663d30:('mov','eax, dword ptr [0xab6f08]'),0x663d42:('mov','eax, dword ptr [0xab6efc]'),0x663d4a:('mov','ecx, dword ptr [eax + 0x304]'),0x663d52:('call','0x781f20'),0x663d5c:('mov','eax, dword ptr [0xab6efc]'),0x663d66:('cmp','dword ptr [edx + 0x310], edi'),0x663d6e:('mov','ecx, dword ptr [0xab6f08]'),0x663d77:('jl','0x663d47'),0x663d83:('mov','eax, dword ptr [eax + esi*4]'),0x781f36:('jne','0x781f73')}.items():
  if ops.get(a)!=op:raise ValueError('Scheme resolver control differs '+hex(a))
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete663D30 with actual781F20 locale-zero comparison; live registry/count/category and saved registry return. Initial records/names/startup supplied; no runtime adoption.')
