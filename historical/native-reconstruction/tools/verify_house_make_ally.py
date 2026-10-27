# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact supplied complete MakeAlly and composed target/score/eligibility roots."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_target_reference import verify as targets,RANGES as TR,TABLES as TT
from verify_house_alliance import verify as alliance,RANGES as AR,TABLES as AT
from presentation_profiles import PATCHED_EXPECTED
RANGES={**TR,**AR,0x4e5660:0x3ee,0x4eeba0:0xcd,0x6c9af0:0x10a,0x6c5070:0x22,0x77f110:0x3d}
TABLES={**TT,**AT,0x79b608:8}
def verify(data):
 t=targets(data);h=alliance(data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ops={};ranges={}
 for a,n in RANGES.items():
  raw=pe.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete MakeAlly range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest());ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={0x4e5672:('call','0x4ec4e0'),0x4e568a:('call','0x49e000'),0x4e56a3:('mov','dword ptr [esi + 0x5674], edi'),0x4e56da:('call','0x4eeba0'),0x4e5791:('call','0x40dc20'),0x4e57c0:('call','0x6b54a0'),0x4e57d1:('call','0x6b5910'),0x4e57de:('call','0x6b5910'),0x4e5827:('call','dword ptr [edx + 0x370]'),0x4e582d:('mov','eax, dword ptr [0x832480]'),0x4e58aa:('call','0x783764'),0x4e58c6:('call','0x77f110'),0x4e5a4b:('ret','8'),0x6c9bf7:('ret','4')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('MakeAlly association differs '+hex(a))
 if pe.get_data(0x79b608-0x400000,8)!=struct.pack('<d',900.):raise ValueError('MakeAlly duration multiplier differs')
 for vt in (0x7addf8,):
  if pe.get_data(vt+0x370-0x400000,4)!=struct.pack('<I',0x6c9af0):raise ValueError('Techno clear association differs')
 return dict(targets=t,alliance=h,ranges=ranges,scope='Complete4E5660 with actual eligibility, score update, tokens/resolution/cast/sort and null Techno target clear/weapon wrapper. Map/grid/notification/format/message/speech/redraw and named virtual leaves/startup supplied; production unjoined.')
