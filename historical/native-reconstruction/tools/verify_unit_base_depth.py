#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin ordinary Unit base depth with actual prepared map/TMP children."""
import struct,pefile
from verify_resident_map_floor import verify as parent,RANGES as PARENT_RANGES
from verify_foot_depth import verify as foot,RANGES as FOOT_RANGES
RANGES={**PARENT_RANGES,**{a:FOOT_RANGES[a] for a in (0x6cfea0,0x5d4800,0x41b320,0x70a2d0,0x4b8be0,0x6a2970)}}
def verify(data):
 parents=parent(data);feet=foot(data);p=pefile.PE(data=data)
 if p.get_data(0x7f7124-0x400000,12)!=struct.pack('<3i',-1,-1,3):raise ValueError('Base-depth initial adjustments differ')
 return {'parent':parents,'foot':feet,'allowed_ranges':[hex(a) for a in RANGES],
  'initial_adjustments':[-1,-1,3],
  'scope':'Ordinary Unit kind-1/nonharvester/special-zero base depth after actual shared later map/floor finalization. Actual Facing/height/coordinates/map lookup/TMP dimensions/image getter and FTOL; prepared Cells/type images/overlays remain shared. Initial actor/type/global/height scale/default tile and ignored dimensions scratch supplied. Other Unit branches, construction/startup/order, null map pointers, runtime depth and whole-frame parity excluded.'}
