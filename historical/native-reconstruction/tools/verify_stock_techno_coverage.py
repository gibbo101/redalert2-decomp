# SPDX-License-Identifier: GPL-3.0-or-later
"""Stock coverage virtuals, including complete Building availability."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_techno_coverage_world import verify as parent_verify,RANGES as PARENT,scale_bits
from verify_mission_building_expiration_services import SPANS
EXTRA={0x6cd6e0:3,0x6c7430:7,0x6c12c0:8,0x506950:7,0x453c60:7,0x450360:0x9e}
RANGES={**PARENT,**EXTRA}
def verify(data):
 parent=parent_verify(data);p=pefile.PE(data=data);ranges={}
 for a,n in EXTRA.items():
  b=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete stock coverage virtual')
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(b).hexdigest())
 if ranges[hex(0x450360)]['sha256']!=SPANS[0x450360][1]:raise ValueError('Building availability differs')
 if p.get_data(0x79a708-0x400000,8)!=struct.pack('<d',1.):raise ValueError('Availability power comparator differs')
 tables={0x7a3540:{0x30c:0x6cd6e0,0x80:0x6c12c0,0x84:0x506950,0x3c:0x6c7430},0x79cbbc:{0x30c:0x450360,0x80:0x6c12c0,0x84:0x453c60,0x3c:0x6c7430}}
 for vt,slots in tables.items():
  for off,a in slots.items():
   if p.get_data(vt+off-0x400000,4)!=struct.pack('<I',a):raise ValueError('Stock coverage dispatch differs')
 return dict(parent=parent,ranges=ranges,tables={hex(t):{hex(k):hex(v) for k,v in slots.items()} for t,slots in tables.items()},scope='Complete coverage/House/height/map with actual stock virtual30C/80/84/3C and450360. House power4E8330,634030/redraw and initial associations supplied; production not adopted.')
