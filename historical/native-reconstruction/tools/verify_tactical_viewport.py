# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete base viewport producer and FTOL; inverse matrix is a probe."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x6a9170:0x121,0x77f110:0x3d}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Exact supplied viewport executable required')
 pe=pefile.PE(data=data);records={};ops={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete viewport range')
  records[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x6a91f2:('call','0x591380'),0x6a920f:('call','0x77f110'),0x6a921a:('call','0x77f110'),0x6a924a:('mov','ecx, dword ptr [0xabe568]'),0x6a9270:('mov','ecx, dword ptr [0xabe56c]')}.items():
  if ops.get(a)!=op:raise ValueError('Viewport association differs')
 return dict(executable_sha256=EXPECTED,ranges=records,scope='Complete6A9170 and actual FTOL; supplied inverse591380, centers/dimensions; no frame consumer/reset')
