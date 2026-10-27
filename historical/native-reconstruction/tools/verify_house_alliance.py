# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base complete House alliance eligibility and registry lookup roots."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x4ec4e0:0xfb,0x4ed760:0x30,0x67af90:0x3d}
TABLES={0x7ceb30:9}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied House alliance target required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('House alliance PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete House alliance root')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 expected={0x4ec4f3:('mov','eax, dword ptr [esi + 0x30]'),0x4ec50a:('shl','eax, cl'),0x4ec521:('call','0x67af90'),0x4ec529:('cmp','dword ptr [ecx + 0xbc], eax'),0x4ec541:('mov','eax, dword ptr [0xa40774]'),0x4ec551:('mov','al, byte ptr [esi + 0x13d]'),0x4ec5cf:('inc','ebp'),0x4ec5d5:('setne','al'),0x4ec5d8:('ret','4'),0x4ed77a:('cmp','dword ptr [ebx + 0xb8], ecx'),0x4ed78f:('ret',''),0x67afac:('call','0x781f20'),0x67afb8:('mov','eax, dword ptr [0x8661c0]'),0x67afcc:('ret','')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('House alliance association differs '+hex(a))
 if p.get_data(0x7ceb30-0x400000,9)!=b'Civilian\0':raise ValueError('House alliance country name differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete4EC4E0 nonnull eligibility,4ED760 House resolver,67AF90 country ordinal lookup.781F20 string comparison and initial owners/associations supplied; no MakeAlly mutation/runtime adoption.')
