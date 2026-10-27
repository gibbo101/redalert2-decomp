#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete base4C7220 and its entered base6C2B40 argument-2 tail."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
from verify_cell_resident_kind6 import verify as verify_resident
from verify_infantry_weapon_selection import verify as verify_weapon,RANGES as WEAPON_RANGES,HELPERS as WEAPON_HELPERS
from verify_position_cloak_effect import verify as verify_cloak,RANGE as CLOAK_RANGE,HELPERS as CLOAK_HELPERS
from verify_cell_dirty_effect import verify as verify_dirty,RANGE as DIRTY_RANGE

RANGES={0x4c7220:0x892,0x6c2b40:0xff,**WEAPON_RANGES,
        CLOAK_RANGE[0]:CLOAK_RANGE[1]-CLOAK_RANGE[0],
        DIRTY_RANGE[0]:DIRTY_RANGE[1]-DIRTY_RANGE[0]}
HELPERS={0x6c12c0:8,0x506950:7,0x594770:0x12,0x41b320:0x3d,
         0x5d4e40:0x21,0x4717b0:0x2f,0x55a660:0xd7,0x4cafe0:0x17,
         **WEAPON_HELPERS,**CLOAK_HELPERS,0x548070:0x38}

def verify(data):
 if len(data)!=4485392 or hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:
  raise ValueError('Exact supplied Infantry position-effects engine required')
 p=pefile.PE(data=data);c=Cs(CS_ARCH_X86,CS_MODE_32);ranges={};ops={}
 for a,n in {**RANGES,**HELPERS}.items():
  raw=p.get_data(a-0x400000,n);ins=list(c.disasm(raw,a))
  if sum(i.size for i in ins)!=n:raise ValueError('Incomplete Infantry position-effects range '+hex(a))
  ranges[hex(a)]=dict(bytes=n,instructions=len(ins),sha256=hashlib.sha256(raw).hexdigest())
  ops.update({i.address:(i.mnemonic,i.op_str) for i in ins})
 expected={
  0x4c7236:('mov','byte ptr [esi + 0x59c], 0'),0x4c723d:('mov','byte ptr [esi + 0x59a], 0'),
  0x4c7486:('call','dword ptr [eax + 0x2b8]'),0x4c74bd:('call','dword ptr [edx + 0x16c]'),
  0x4c74cc:('call','dword ptr [eax + 0x16c]'),0x4c74db:('call','dword ptr [edx + 0x16c]'),
  0x4c74ea:('call','dword ptr [eax + 0x16c]'),0x4c7524:('call','dword ptr [eax + 0x1a0]'),
  0x4c753a:('call','0x548070'),0x4c76ff:('mov','dword ptr [0xa35e24], eax'),
  0x4c7832:('call','0x4717b0'),0x4c78f6:('call','dword ptr [eax + 0x1a0]'),
  0x4c7902:('call','0x55a660'),0x4c790f:('call','dword ptr [edx + 0x468]'),
  0x4c7aa5:('call','0x6c2b40'),0x6c2b72:('call','dword ptr [eax + 0x48]'),
  0x6c2baa:('call','dword ptr [eax + 0x3b8]'),0x6c2be0:('call','0x55a660'),
  0x6c2c04:('call','0x548070'),0x6c2c2c:('call','0x548070'),0x6c2c33:('call','0x47bb30')}
 for a,op in expected.items():
  if ops.get(a)!=op:raise ValueError('Infantry position-effects association differs '+hex(a))
 vtable=0x7a3540
 associations=((0x48,0x5d4e40),(0x80,0x6c12c0),(0x16c,0x594770),(0x1a0,0x41b320),
               (0x2b8,0x508530),(0x3b8,0x6c2990),(0x468,0x4cafe0))
 for off,target in associations:
  if p.get_data(vtable+off-0x400000,4)!=struct.pack('<I',target):
   raise ValueError('Infantry position-effects vtable differs '+hex(off))
 return dict(ranges=ranges,resident_search=verify_resident(data),weapon_selection=verify_weapon(data),
  position_cloak_effect=verify_cloak(data),cell_dirty_effect=verify_dirty(data),
  vtable=hashlib.sha256(p.get_data(vtable-0x400000,0x46c)).hexdigest(),
  associations={hex(o):hex(t) for o,t in associations},
  scope='Complete base4C7220 argument2 ordinary-E1 path and entered base6C2B40 tail with actual null-target Infantry weapon selection, initialized empty Cell kind-6 search, map lookup, position-cloak Cell-mask exit and Cell dirty overlay exit. The first permission-success path bypasses active-placement and the tail permission-success path stores active32D=1. Footprint, mode2, Cell object/edge, bridge, active-placement early return, visible-map, animation, special-map and entered cloak/dirty effect branches remain refused.')
