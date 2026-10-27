# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base shared Radio/Techno expiration with ordinary Tag subjects."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_mission_tag_object_expiration import verify as verify_object,RANGES as OBJECT
RANGES={**OBJECT,0x636ba0:0x4b,0x6d2d10:0x32a,0x468a70:0x41,0x468120:0x18,0x4d5b40:0x26}
TABLES={0x7a2ae4:28}
def verify(data):
 parent=verify_object(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Techno expiration root '+hex(a))
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x636baf:('call','0x5d3bd0'),0x636bd4:('mov','dword ptr [eax], 0'),0x636bda:('mov','eax, dword ptr [esi + 0xd0]'),
  0x6d2d23:('call','0x636ba0'),0x6d2d33:('call','0x468a70'),0x6d2e10:('call','0x6388a0'),
  0x6d2e1f:('mov','dword ptr [esi + 0x148], ecx'),0x6d2e25:('mov','dword ptr [esi + 0x14c], edx'),
  0x6d2e2b:('mov','dword ptr [esi + 0x150], eax'),0x6d2f19:('call','0x468120'),
  0x6d2f7e:('cmp','eax, -1'),0x6d2fc7:('call','dword ptr [eax + 0x10]'),
  0x6d3007:('call','dword ptr [eax + 0x10]'),0x468a86:('mov','dword ptr [ecx + 4], eax'),
  0x468aab:('mov','dword ptr [ecx + 0x30], eax')}.items():
  if ops.get(a)!=op:raise ValueError('Techno expiration association differs '+hex(a))
 if p.get_data(0x7a2af4-0x400000,4)!=struct.pack('<I',0x4d5b40):raise ValueError('Pointer search dispatch differs')
 return dict(parent=parent,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete Radio/Techno expiration for nonnull Tag subjects with flags14 bit0 clear, actual Object prefix/passenger unlink/control cleanup/vector search. Virtual effects/RNG/other service children, startup and retry-local padding supplied. No typed Foot/Infantry/Building or runtime join.')
