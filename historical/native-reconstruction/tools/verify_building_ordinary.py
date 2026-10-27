# SPDX-License-Identifier: GPL-3.0-or-later
"""Complete ordinary Building parent and actual packed/planar/height/FTOL children."""
import hashlib,struct,pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x43a5e0:0x5e1,0x41b320:0x3d,0x6a2870:0x84,0x5d4800:7,0x6a2970:0x3c,0x77f110:0x3d}
def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact Building ordinary target required')
 p=pefile.PE(data=data);records={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,a))
  if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Building ordinary range')
  records[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 for off,target in ((0x10c,0x43a5e0),(0x1a0,0x41b320),(0x1b8,0x5d4800)):
  if p.get_data(0x79cbbc+off-0x400000,4)!=struct.pack('<I',target):raise ValueError('Building ordinary dispatch differs')
 for a,raw in ((0x5480a5,b'\xc2\x04\x00'),(0x6d1cc8,b'\xc2\x3c\x00')):
  if p.get_data(a-0x400000,len(raw))!=raw:raise ValueError('Building child stack ownership differs')
 return dict(ranges=records,scope='Complete43A5E0/41B320/6A2870/5D4800/6A2970/FTOL; image/RTTI/mission/partner/timer/ratio/frame/foundation/Cell/draw services supplied; no pixels/schedule')
