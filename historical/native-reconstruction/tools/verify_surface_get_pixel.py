# SPDX-License-Identifier: GPL-3.0-or-later
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_surface_pixel import verify as writer_verify,RANGES as WRITER,VT
RANGES={**WRITER,0x7741d0:0x50}
def verify(data):
 writer=writer_verify(data);p=pefile.PE(data=data);b=p.get_data(0x7741d0-0x400000,0x50);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,0x7741d0));ops={i.address:(i.mnemonic,i.op_str) for i in ins}
 if sum(i.size for i in ins)!=len(b) or p.get_data(VT+0x28-0x400000,4)!=struct.pack('<I',0x7741d0):raise ValueError('Stock GetPixel span/association differs')
 for a,op in {0x7741e6:('call','dword ptr [edx + 0x5c]'),0x7741f6:('cmp','eax, 2'),0x7741fd:('mov','bx, word ptr [edi]'),0x774211:('mov','bl, byte ptr [edi]'),0x77421d:('ret','4')}.items():
  if ops.get(a)!=op:raise ValueError('GetPixel control differs '+hex(a))
 return dict(writer=writer,get=dict(address='0x7741d0',bytes=len(b),sha256=hashlib.sha256(b).hexdigest()),scope='Complete7741D0 with actual shared stock lock/format/pitch/width/unlock; supplied allocation/geometry, no production/SDL adoption.')
