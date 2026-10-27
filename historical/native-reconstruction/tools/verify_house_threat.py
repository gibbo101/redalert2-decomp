# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base complete threat-grid, score/enemy and coordinate roots."""
import hashlib,pefile,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x4f3420:0x1c5,0x4eeba0:0xcd,0x54e370:0x30}
TABLES={0x7d9fa0:36,0x7d9fc4:36}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied House threat target required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('House threat PE differs')
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete House threat root')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins});ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 expected={0x4f3425:('mov','ecx, 0x4204'),0x4f3432:('rep stosd','dword ptr es:[edi], eax'),0x4f3439:('dec','eax'),0x4f346b:('call','dword ptr [edx + 0x2a0]'),0x4f347f:('call','dword ptr [eax + 0x2c]'),0x4f34d8:('call','0x54e370'),0x4f355b:('sar','edx, cl'),0x4f3565:('add','dword ptr [ebx + ecx*4 + 0x56d0], edx'),0x4f3573:('jns','0x4f357b'),0x4f3587:('call','dword ptr [edx + 0x1a4]'),0x4f35d9:('jns','0x4f3448'),0x4f35e4:('ret',''),0x4eebcc:('add','dword ptr [ecx + 4], edi'),0x4eebf9:('jle','0x4eec36'),0x4eec23:('test','dword ptr [eax + 0x5674], ebp'),0x4eec52:('mov','dword ptr [eax + 0x54f0], edx'),0x4eec6a:('ret','8'),0x54e395:('lea','eax, [eax + esi*2 + 0x83]'),0x54e39d:('ret','4')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('House threat association differs '+hex(a))
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete4F3420 grid and54E370 projection;4EEBA0 score/enemy. Virtual2A0/2C/1A4 and initial associations supplied; no MakeAlly parent/production adoption.')
def table_values(data):
 verify(data);p=pefile.PE(data=data)
 return list(struct.unpack('<18i',p.get_data(0x7d9fa0-0x400000,72)))
