#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin ordinary map cell-preparation parent and actual nested children."""
import hashlib
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_map_cell_preparation import verify as verify_cells,RANGES as CELL_RANGES
from verify_tile_sweep import RANGES as SWEEP_RANGES
from verify_tile_image import RANGES as IMAGE_RANGES
from verify_foot_depth import RANGES as FOOT_RANGES
RANGES={**CELL_RANGES,0x491620:FOOT_RANGES[0x491620],0x54b2e0:0x276,0x55a490:SWEEP_RANGES[0x55a490],0x476ba0:0x112,
 0x4790f0:0x211,0x479440:1191,0x5383c0:474,0x51fc50:6,0x51fc60:15,0x529590:0x171,0x77f110:IMAGE_RANGES[0x77f110]}
def verify(data):
    cells=verify_cells(data);p=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,n in RANGES.items():
        raw=p.get_data(a-0x400000,n);ins=list(cs.disasm(raw,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete map preparation range '+hex(a))
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(raw).hexdigest()}
    return {'ranges':ranges,'cell_inspection':cells,'direction_initializer':'0x491620 -> 0x851a70',
      'scope':'Complete ordinary map cell-preparation parent with empty transient list, no tags/overlays, actual iterator, resource absent leaf, full Cell recalculation/LAT/passability/permission/lookup/TMP and light installation/numeric/normalization/factory disabled branch. Construction, original tables/initial state, registry/geometry/land speeds/scenario settings are supplied; no palette/converter allocation, sources, bridge/zone construction, runtime or whole-frame parity.'}
