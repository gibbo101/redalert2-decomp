# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base complete House map sight scans and existing House predicates."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x49e000:0x10c,0x49de00:0x1ff,0x4f52b0:0x34,0x4e5540:0x3f}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied House map refresh target required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('House map refresh PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete House map refresh root')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 expected={0x49e001:('mov','ebx, dword ptr [0xa40c30]'),0x49e018:('mov','eax, dword ptr [0xa40c24]'),0x49e051:('call','0x4f52b0'),0x49e074:('call','dword ptr [eax + 0x41c]'),0x49e0c2:('call','0x4e5540'),0x49e109:('ret','8'),0x49de77:('call','dword ptr [eax + 0x418]'),0x49de94:('add','edx, 3'),0x49deaf:('call','0x54a550'),0x49df53:('call','dword ptr [eax + 0x2c]'),0x49df65:('mov','cl, byte ptr [eax + 0x534]'),0x49df75:('call','0x4f52b0'),0x49df8f:('call','dword ptr [eax + 0x418]'),0x49dfe6:('call','dword ptr [eax + 0x3ac]'),0x49dffc:('ret','8'),0x4f52b7:('jne','0x4f52d6'),0x4e556c:('shl','edx, cl')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('House map refresh association differs '+hex(a))
 return dict(ranges=ranges,scope='Complete49E000/49DE00 scans with actual4F52B0/4E5540. Sight/type/image virtual effects,54A550 and startup associations supplied; no MakeAlly/production adoption.')
