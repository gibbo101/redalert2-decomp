# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact result6 dispatch block and its distinct stock numeric initializer chain."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_cell_nearby_scatter import verify as verify_cell,RANGES as CELL,TABLES as CT
from verify_ramp_geometry import LEAVES,CRT,TABLES as GT
ROOTS={0x49f450:40,0x49f480:19,0x49f4a0:19,0x49f4c0:19,0x49f4e0:19,
 0x49f500:19,0x49f520:49,0x49f560:33,0x49f590:44,0x49f5c0:39}
GLOBALS={0x852980:8,0x8529c8:8,0x8529b8:8,0x8529b0:8,0x852988:8,
 0x852960:8,0x8529d0:4,0x852990:8,0x8529a8:8,0x8529c0:4}
CONSTANTS={0x79a6f8:2.,0x79a700:256.,0x79a708:1.,0x79a710:45.,0x79a718:60.,
 0x79a720:90.,0x79a728:.5,0x79a730:1/256,0x7a0f80:651.8986469044033,0x79ea38:60.,0x79ea40:0.017453292519943295}
BLOCK=0x4a1f05;END=0x4a1f8d
RANGES={**CELL,**ROOTS,**LEAVES,**CRT,BLOCK:END-BLOCK}
TABLES={**CT,**GT,**{a:8 for a in CONSTANTS}}
ASSOCIATIONS={0x4a1f0f:('call','0x548000'),0x4a1f1a:('test','ch, 1'),
 0x4a1f42:('call','0x548000'),0x4a1f56:('idiv','dword ptr [0x8529d0]'),
 0x4a1f63:('cmp','eax, 2'),0x4a1f6d:('mov','edx, dword ptr [esp + 0x14]'),
 0x4a1f7b:('push','0x852998'),0x4a1f80:('push','esi'),
 0x4a1f81:('call','0x548000'),0x4a1f88:('call','0x476920')}
def verify(data):
 inherited=verify_cell(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);regions={};ops={}
 for a,n in {**ROOTS,**LEAVES,**CRT,BLOCK:END-BLOCK}.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Advance Cell region differs')
  if a in ROOTS and ins[-1].mnemonic!='ret':raise ValueError('Drive numeric root incomplete')
  regions[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest(),instructions=len(ins),complete_function=a in ROOTS or a in LEAVES)
  ops.update((i.address,(i.mnemonic,i.op_str)) for i in ins)
 for a,op in ASSOCIATIONS.items():
  if ops.get(a)!=op:raise ValueError('Advance Cell association differs '+hex(a))
 for a,n in CONSTANTS.items():
  if p.get_data(a-0x400000,8)!=struct.pack('<d',n):raise ValueError('Drive geometry constant differs')
 return dict(inherited=inherited,regions=regions,constants={hex(a):n for a,n in CONSTANTS.items()},
  scope='Only original Advance result6 block4A1F05..4A1F8D, actual Cell/Unit/nearby/destinations and distinct stock ten-root Drive geometry chain. Admission, placement, entry stack/registers and continuation supplied. Not complete Advance or Process, startup/owned world/preview/drawing/SDL.')
