# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete Walk, Infantry commands, membership and actual map/floor children."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
import verify_walk_route as walk
import verify_infantry_membership as membership
RANGES={}
for source in (walk.RANGES,membership.RANGES,{0x548070:0x38}):
 for a,n in source.items():RANGES[a]=max(n,RANGES.get(a,0))
TABLES={**walk.TABLES,0x40dc4c:23,0x7a3a78:0x94,0x7d27e8:800}
SERVICES={0x568140:4,0x5683c0:4,0x6c2440:4,0x472540:4,0x78298a:0,
 0x47bb30:0,0x500aa0:4,0x4c3000:12,0x410290:8,0x504740:12,0x3c7594:4,0x3c757c:4}
def verify(data):
 parents=dict(walk=walk.verify(data),membership=membership.verify(data));p=pefile.PE(data=data)
 c=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
 for a,n in RANGES.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Infantry world range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,sha256=hashlib.sha256(raw).hexdigest())
 return dict(parent=parents,ranges=ranges,tables={hex(a):hashlib.sha256(p.get_data(a-0x400000,n)).hexdigest() for a,n in TABLES.items()},
  services={hex(a):n for a,n in SERVICES.items()},scope='Complete actual Infantry/Foot order and queued Walk Process on shared production map/floor/membership/occupation owners. Route, target coordinates, visibility, notification, dirty/recalculation and initial state remain supplied. No startup, E1 loading, pathfinding, animation/drawing, SDL or objectives.')
