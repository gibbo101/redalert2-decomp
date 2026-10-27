# SPDX-License-Identifier: GPL-3.0-or-later
"""Inspect complete base event root and the actual late House resolver."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x6e6050:0x704,0x4ed760:0x30}
TABLES={0x6e6754:0x150}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied base mission-event engine required')
 p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 if p.FILE_HEADER.Machine!=0x14c or p.OPTIONAL_HEADER.ImageBase!=0x400000:raise ValueError('Mission event PE differs')
 result={};ops={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);instructions=list(cs.disasm(raw,a))
  if sum(i.size for i in instructions)!=n:raise ValueError('Incomplete mission-event inspection')
  ops.update({i.address:(i.mnemonic,i.op_str) for i in instructions})
  result[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 for a,expected in {0x6e6050:('sub','esp, 0x18'),0x6e60d6:('cmp','eax, edx'),
  0x6e61d7:('sub','ecx, edx'),0x6e6256:('cmp','esi, eax'),0x6e625e:('mov','cl, byte ptr [0xa40d13]'),
  0x6e661c:('call','0x4ed760'),0x6e6751:('ret','0x18'),0x4ed78f:('ret','')}.items():
  if ops.get(a)!=expected:raise ValueError('Mission event association differs '+hex(a))
 def word(a):return struct.unpack('<I',p.get_data(a-0x400000,4))[0]
 for kind,target in ((13,0x6e61c3),(47,0x6e60b8),(33,0x6e61f3)):
  index=p.get_data(0x6e677c-0x400000+kind-13,1)[0]
  if word(0x6e6754+4*index)!=target:raise ValueError('Mission event early dispatch differs')
 for kind in (4,33):
  index=p.get_data(0x6e67ac-0x400000+kind-1,1)[0]
  if word(0x6e67a4+4*index)!=0x6e6256:raise ValueError('Mission pulse match dispatch differs')
  index=p.get_data(0x6e681c-0x400000+kind-12,1)[0] if kind>=12 else None
  if index is not None and word(0x6e67e4+4*index)!=0x6e6619:raise ValueError('Mission House pulse dispatch differs')
  index=p.get_data(0x6e6870-0x400000+kind-3,1)[0]
  if word(0x6e684c+4*index)!=0x6e66f9:raise ValueError('Mission late House continuation differs')
 return dict(ranges=result,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  scope='Complete root paths for4/13/33/47 with actual House resolver; initial event/House/timer/global records supplied. No scheduler/pulse production/action/discovery/infantry/SDL proof.')
