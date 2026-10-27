# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete sight Cell redraw parent; center and height are explicit probes."""
import hashlib,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_string_lookup import EXPECTED
RANGES={0x6aadd0:0x1a8}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=EXPECTED:raise ValueError('Exact supplied Cell redraw executable required')
 p=pefile.PE(data=data);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a));ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Cell redraw span')
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for a,op in {0x6aae0e:('mov','dword ptr [edi + 0x5c], eax'),0x6aaecf:('xor','ecx, ecx'),0x6aaed8:('call','0x6a2970'),0x6aaf3e:('cmp','eax, 0x31f'),0x6aaf61:('mov','byte ptr [edx + 0x138], 0')}.items():
  if ops.get(a)!=op:raise ValueError('Cell redraw association differs')
 return dict(executable_sha256=EXPECTED,ranges=ranges,scope='Complete6AADD0 with supplied center475D60/height6A2970 probes; native owner composition separate')
