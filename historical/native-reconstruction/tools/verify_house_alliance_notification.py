# SPDX-License-Identifier: GPL-3.0-or-later
"""Fingerprint the complete supplied-base House alliance notification parent."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x4ec5e0:0xfc}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied alliance notification target required')
 pe=pefile.PE(data=data)
 if pe.FILE_HEADER.Machine!=0x14c or pe.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Alliance notification PE differs')
 ops={};ranges={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete alliance notification span')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 expected={0x4ec5ed:('mov','bl, byte ptr [eax + 0x111d]'),0x4ec5f9:('call','dword ptr [edx + 4]'),0x4ec5fc:('test','al, al'),0x4ec661:('mov','byte ptr [esi + 0x191], bl'),0x4ec6b7:('call','0x4e5a70'),0x4ec6be:('call','0x4e5660'),0x4ec6c3:('mov','ecx, dword ptr [0xa322a8]'),0x4ec6db:('ret','')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Alliance notification association differs '+hex(a))
 return dict(ranges=ranges,scope='Complete4EC5E0; session virtual4 and recursive MakeAlly/MakeEnemy effects, initialization and production adoption remain supplied/unjoined.')
