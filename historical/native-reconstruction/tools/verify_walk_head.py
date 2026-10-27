# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect actual Walk head caller and its overlay-free Cell/mission children."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_infantry_subcell as parent
EXTRA={0x71f590:0x36c,0x594770:0x12,0x476cc0:0x1991}
RANGES={**parent.RANGES,**EXTRA}
TABLES={**parent.TABLES,0x7a3540:0x170}
def verify(data):
 base=parent.verify(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in EXTRA.items():
  raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Walk head range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 for a,op in {0x71f5f0:('call','dword ptr [eax + 0xec]'),0x71f642:('call','dword ptr [edx + 0x16c]'),
  0x71f7da:('cmp','esi, edx'),0x71f808:('call','0x4764b0'),0x71f833:('call','0x476cc0'),
  0x71f8b2:('call','dword ptr [edx + 0xe8]'),0x476ce2:('je','0x478646'),0x478648:('mov','al, 1')}.items():
  if ops.get(a)!=op:raise ValueError('Walk head association differs '+hex(a))
 if p.get_data(0x7a3540+0x16c-0x400000,4)!=struct.pack('<I',0x594770):raise ValueError('Infantry mission virtual differs')
 return dict(parent=base,extra_ranges=ranges,infantry_vtable_sha256=hashlib.sha256(p.get_data(0x7a3540-0x400000,0x170)).hexdigest(),
  scope='Complete ordinary Walk71F590 roots, actual release/select/claim, mission and overlay-free476CC0. Entered nonnull-target, building and overlay effects refused. Initial records, map/floor and seeding supplied; no complete Process preparation, production binding or SDL walking.')
