# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete stock coverage add/remove parents, with named supplied children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from presentation_profiles import PATCHED_EXPECTED
RANGES={0x6c83f0:0x2f1,0x6c86f0:0x2ce}
LEAVES={0x6a2970:0,0x4f52b0:0,0x4e5540:4,0x548070:4,0x634030:0,0x4e09a0:4}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied coverage target required')
 p=pefile.PE(data=data);ranges={};ops={}
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Coverage PE differs')
 for a,n in RANGES.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete coverage span')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x6c8413:('call','dword ptr [eax + 0x30c]'),0x6c8435:('movsx','eax, byte ptr [eax + 0xade]'),0x6c844d:('mov','byte ptr [esi + 0x1fd], 1'),0x6c8745:('mov','ebx, dword ptr [edx + 8]'),0x6c89b4:('call','0x4e09a0')}.items():
  if ops.get(a)!=op:raise ValueError('Coverage instruction differs '+hex(a))
 for vt in (0x7a3540,0x79cbbc):
  for slot,target in ((0x3ac,0x6c83f0),(0x3b0,0x6c86f0)):
   if p.get_data(vt+slot-0x400000,4)!=struct.pack('<I',target):raise ValueError('Stock coverage vtable differs')
 return dict(ranges=ranges,stock_tables=['0x7a3540','0x79cbbc'],scope='Complete6C83F0/6C86F0 with named supplied virtual/House/height/map/refresh/redraw leaves. No original initialization or production adoption.')
