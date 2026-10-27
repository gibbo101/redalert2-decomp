#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin loaded wall Mark, actual Object Mark, permission and neighbor dispatch."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_overlay_placement import verify as verify_placement
RANGES={0x5da970:0xcb3,0x5d4160:206,0x41b320:61,0x5d36e0:24,
        0x4718b0:0x45c,0x476ac0:0x56,0x5dc2e0:6}
INSPECTION_ONLY={0x475960:0x3f7}
def verify(data):
    parent=verify_placement(data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,n in {**RANGES,**INSPECTION_ONLY}.items():
        blob=pe.get_data(a-0x400000,n);ins=list(cs.disasm(blob,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete wall placement range '+hex(a))
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest()}
    if struct.unpack('<I',pe.get_data(0x7a77f4+0x1a0-0x400000,4))[0]!=0x41b320:raise ValueError('Wall coordinate dispatch differs')
    return {'ranges':{hex(a):ranges[hex(a)] for a in RANGES},
      'inspection_only':{hex(a):ranges[hex(a)] for a in INSPECTION_ONLY},
      'placement_dispatch':parent,
      'scope':'Complete Overlay Mark in loaded ordinary wall/no-animation domain with actual Object Mark/word getter/redraw flag, complete Cell permission loaded-true path and actual neighbor getter. Lookup, wall connection/redraw/recalculation parent, animation absence, redraw queue and retirement remain supplied. Wall-update parent inspected only; no complete wall connections, alternate placement, constructor/reader/runtime or whole-frame claim.'}
