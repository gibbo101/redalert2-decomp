# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import presentation_profile
RANGES={0x568280:0x135,0x568140:0x135,0x476ac0:0x56,0x548070:0x38}
def verify(data):
 digest,profile=presentation_profile(data,allow_patched=True)
 if profile!='supplied-ra2-1006':raise ValueError('Radar discovery requires supplied base target')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete discovery root')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest(),instructions=len(ins));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,op in {0x56828c:('idiv','dword ptr [0xa6fc30]'),0x56830e:('mov','ecx, dword ptr [eax + 0x13c]'),0x568320:('call','0x476ac0'),0x568399:('mov','ecx, dword ptr [eax + 0x13c]'),0x5683b2:('ret','4'),0x5681d2:('test','byte ptr [ecx + 0x12c], 8')}.items():
  if ops.get(a)!=op:raise ValueError('Discovery field/control differs '+hex(a))
 return dict(executable_sha256=digest,ranges=ranges,scope='Complete568280 and568140 on shared table/fallback, actual neighbor3 and548070; initial records/divisor/direction supplied; no radar parent/runtime adoption.')
