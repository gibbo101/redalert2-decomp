# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact-base mission control constructor, INI parent and table initialization slice."""
import hashlib,struct,pefile,capstone
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x594dd0:0x35,0x594e10:0x15,0x594e30:0x1a5,0x594db0:0x12,0x5950d0:0xf,0x4d4520:0x1c,0x6524f2:0x1d}
SERVICES=(0x50c9b0,0x50f410,0x50e3a0)
NAMES=('Sleep','Attack','Move','QMove','Retreat','Guard','Sticky','Enter','Capture','Eaten','Harvest','Area Guard','Return','Stop','Ambush','Hunt','Unload','Sabotage','Construction','Selling','Repair','Rescue','Missile','Harmless','Open','Patrol','Paradrop Approach','Paradrop Overfly','Wait','Attack Move')
KEYS={0x7e1d70:'NoThreat',0x7e1d68:'Zombie',0x7e1d5c:'Recruitable',0x7e1d50:'Paralyzed',0x7e1d44:'Retaliate',0x7e1d3c:'Scatter',0x7cef5c:'Rate',0x7e1d34:'AARate'}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied base required')
 p=pefile.PE(data=data);c=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(x.size for x in ins)!=n:raise ValueError('Incomplete mission control range '+hex(a))
  ranges[hex(a)]=dict(size=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
 string=lambda a:p.get_string_at_rva(a-0x400000).decode('ascii')
 pointers=struct.unpack('<30I',p.get_data(0x7cd774-0x400000,120))
 if tuple(map(string,pointers))!=NAMES or string(0x7cdecc)!='<none>' or any(string(p)!=k for p,k in KEYS.items()):raise ValueError('Mission control names/keys differ')
 if p.get_data(0x79b610-0x400000,8)!=b'\0'*8:raise ValueError('Zero constant differs')
 return dict(ranges=ranges,names=list(NAMES),keys={hex(p):k for p,k in KEYS.items()})
