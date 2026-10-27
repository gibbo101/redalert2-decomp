#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin the actual zero-point Unit caller and complete shared nearby children."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_unit_scatter_world import verify as verify_world,RANGES as WORLD,TABLES as WT
from verify_nearby_location_map import verify as verify_nearby,RANGES as NEARBY,TABLES as NT
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={a:max(WORLD.get(a,0),NEARBY.get(a,0)) for a in WORLD.keys()|NEARBY.keys()}
TABLES={a:max(WT.get(a,0),NT.get(a,0)) for a in WT.keys()|NT.keys()}
def verify(data):
 if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied Unit nearby engine required')
 inherited=[verify_world(data),verify_nearby(data)];p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ops={i.address:(i.mnemonic,i.op_str) for a,n in RANGES.items() for i in cs.disasm(p.get_data(a-0x400000,n),a)}
 for a,op in {0x70748d:('mov','al, byte ptr [ebp + 0x79]'),0x7074a0:('mov','edx, dword ptr [ecx + 0x5a4]'),
  0x7074ba:('call','0x5502e0'),0x7074c1:('cmp','ax, word ptr [0xad0488]'),
  0x55032b:('shl','eax, 9'),0x550368:('movsx','eax, word ptr [ecx + 2]'),
  0x550418:('movsx','eax, ax'),0x5505c3:('movsx','eax, ax'),0x55079b:('movsx','eax, ax'),0x550934:('movsx','eax, ax'),0x550d2f:('movsx','eax, ax')}.items():
  if ops.get(a)!=op:raise ValueError('Unit nearby caller/query association differs '+hex(a))
 return dict(inherited=inherited,scope='Complete zero-point Unit Scatter through actual nearby search/permission/rectangle/Cell admission/projection and actual Cell destination effects, shared actor/Drive/map/fallback. Initial records/type5A4/geometry/frame/sentinel/associations supplied; zero target selects by frame, sqrt/RNG/QueueMission not entered. No Cell dispatch/Advance6/Process/production owned world/runtime join.')
