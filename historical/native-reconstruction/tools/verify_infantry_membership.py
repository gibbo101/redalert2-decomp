# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin actual Infantry foundation/map/Cell membership and occupation dispatch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_infantry_mark as mark
import verify_infantry_subcell as subcell
import verify_unit_membership as unit
from verify_map_floor_height import RANGES as FLOOR
COMPLETE={a:n for a,n in unit.COMPLETE.items() if a!=0x5d5d90}
COMPLETE[0x50a000]=0x5b
RANGES={**FLOOR,**mark.RANGES,**COMPLETE,0x548000:0x68,
 **{a:subcell.RANGES[a] for a in (0x4763d0,0x47d060,0x508410,0x5084a0,0x4ba410)}}
DISPATCH={**mark.DISPATCH,**{0x7a3540+o:t for o,t in ((0x100,0x5d4470),(0xbc,0x41b470),
 (0xe8,0x508410),(0xec,0x5084a0),(0x180,0x6c2440))},0x7a3a78+0x90:0x50a000}
def verify(data):
 parent=dict(mark=mark.verify(data),occupation=subcell.verify(data));p=pefile.PE(data=data)
 cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Infantry membership range')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,t in DISPATCH.items():
  if p.get_data(a-0x400000,4)!=struct.pack('<I',t):raise ValueError('Infantry membership dispatch differs')
 for a,op in {0x50a001:('mov','cl, byte ptr [0xa411a0]'),0x50a026:('mov','byte ptr [0xa411a0], dl'),
  0x50a02c:('mov','dword ptr [0xa4117c], eax'),0x50a044:('mov','dword ptr [0xa41180], ecx'),
  0x50a052:('mov','eax, 0xa4117c'),0x50a058:('ret','4'),
  0x473c7a:('cmp','eax, 0xf'),0x473c7e:('je','0x473d10'),
  0x473d8e:('cmp','eax, 0xf'),0x473d91:('je','0x473e1f')}.items():
  if ops.get(a)!=op:raise ValueError('Infantry foundation ownership differs')
 return dict(parent=parent,ranges=ranges,dispatch={hex(a):hex(t) for a,t in DISPATCH.items()},
  floor=__import__('verify_map_floor_height').verify(data),
  scope='Complete ordinary Infantry Mark/map/Cell membership with actual Infantry foundation and floors. Both Cell parents skip Infantry occupation and eligibility. Actual borrowed native actor/Cell/map owners. Initial records, visibility/notification/recalculation/atexit remain supplied. Safe combined map index only. No Walk Process, E1 startup, runtime walking, drawing or objectives.')
