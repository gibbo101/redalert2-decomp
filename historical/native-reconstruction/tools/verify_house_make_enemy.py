# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied complete MakeEnemy including its out-of-line tail."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x4e5a70:0x27a,0x4eeba0:0xcd,0x77f110:0x3d}
TABLES={0x79b608:8}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied MakeEnemy target required')
 pe=pefile.PE(data=data);ops={};ranges={}
 if pe.FILE_HEADER.Machine!=0x14c or pe.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('MakeEnemy PE differs')
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete MakeEnemy span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={0x4e5ac2:('call','0x4eeba0'),0x4e5b14:('mov','dword ptr [esi + 0x5674], ecx'),0x4e5b33:('neg','edx'),0x4e5b35:('sbb','edx, edx'),0x4e5b37:('inc','edx'),0x4e5bad:('mov','dword ptr [esi + 0x120], ecx'),0x4e5bbf:('call','0x4eeba0'),0x4e5c32:('call','0x77f110'),0x4e5cd1:('ret','8'),0x4e5ce8:('jmp','0x4e5cab')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('MakeEnemy association differs '+hex(a))
 if pe.get_data(0x39b608,8)!=struct.pack('<d',900.):raise ValueError('MakeEnemy duration constant differs')
 return dict(ranges=ranges,tables={hex(a):hashlib.sha256(pe.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},scope='Complete4E5A70 including4E5CD4 tail, actual4EEBA0 score and77F110 conversion; map/grid/UI/speech and startup supplied, production unjoined.')
