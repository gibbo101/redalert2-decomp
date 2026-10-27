# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin candidate overlay preparation and the later crushing marker stores."""
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_process_preparation_scatter import verify as parent_verify,RANGES as PARENT,TABLES
RANGES={**PARENT,0x476ce8:0x17}
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={}
 for a,n in ((0x4a2670,0x20b5),(0x4a1000,0x1670)):
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in cs.disasm(p.get_data(a-0x400000,n),a))
 expected={0x4a3541:('mov','eax, dword ptr [esi + 0x44]'),0x4a3544:('test','eax, eax'),
  0x4a356b:('mov','al, byte ptr [edx + 0x1fd]'),0x4a3575:('mov','byte ptr [esp + 0x13], 1'),
  0x4a3fcf:('mov','al, byte ptr [esp + 0x13]'),0x4a1a4e:('mov','al, byte ptr [ebp + 0x64]'),
  0x4a1a78:('mov','eax, dword ptr [esi + 0x264]'),0x4a1a85:('mov','byte ptr [eax + 0x59f], 1'),
  0x4a1a97:('mov','cl, byte ptr [eax + 0xaf4]'),0x4a1aa4:('mov','dword ptr [eax + 0x28c], 0xbca3d70a')}
 if any(ops.get(a)!=v for a,v in expected.items()):raise ValueError('Candidate/crushing fields differ')
 child=list(cs.disasm(p.get_data(0x476ce8-0x400000,0x17),0x476ce8))
 if sum(i.size for i in child)!=0x17 or (child[-1].mnemonic,child[-1].op_str)!=('je','0x478646'):
  raise ValueError('Overlay Cell entry early return differs')
 return dict(parent=parent,scope='Complete actor0 Process with actual overlay admission, candidate byte and crossing flag59F/velocity28C; Cell-entry overlay27A=0. Initial records, route finding and named effects supplied. Overlay destruction, complete Unit tick, Process1 and runtime adoption excluded.')
