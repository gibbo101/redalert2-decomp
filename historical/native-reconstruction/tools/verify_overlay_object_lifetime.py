#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Exact base temporary Overlay base construction, retirement and cleanup roots."""
import hashlib,struct
import pefile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from verify_overlay_placement import RANGES as PLACEMENT_RANGES,verify as verify_placement
RANGES={**PLACEMENT_RANGES,0x40ff10:0x47,0x5d22e0:529,0x405bf0:18,
 0x5d4e90:124,0x5d3700:389,0x6ecf10:284,0x5d4f10:11,
 0x4100b0:8,0x40cdf0:38,0x5dc300:0xa7}
def verify(data):
    parent=verify_placement(data);pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    for a,n in RANGES.items():
        blob=pe.get_data(a-0x400000,n);ins=list(cs.disasm(blob,a))
        if sum(i.size for i in ins)!=n or ins[-1].mnemonic!='ret':raise ValueError('Incomplete Overlay lifetime range '+hex(a))
        ranges[hex(a)]={'bytes':n,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest()}
    for off,target in {8:0x4100b0,0x20:0x5dc300,0x44:0x5d4f10,0xd0:0x5d3700}.items():
        if struct.unpack('<I',pe.get_data(0x7a77f4+off-0x400000,4))[0]!=target:raise ValueError('Overlay cleanup dispatch differs')
    return {'ranges':ranges,'placement':parent,'scope':'Complete temporary Overlay construction with actual Abstract/Object/resource defaults, ordinary loaded placement, retirement and nonempty cleanup/Overlay destructor. Already-limbo retirement/removal, Overlay-only negative RTTI domain. Heap/vector growth, pointer-expiration broadcasts, tag callbacks, lookup/resource/recalculation, RTTI and base Object destruction/free are supplied. No complete heap/ownership/registration destruction, alternate types/placement, runtime or whole-frame claim.'}
