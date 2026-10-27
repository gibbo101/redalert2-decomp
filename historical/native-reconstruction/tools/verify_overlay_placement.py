#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete exact-base Overlay construction/Mark and actual Object children."""
import hashlib
import struct
import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from verify_terrain_visibility import PATCHED_EXPECTED
RANGES={0x5da7d0:0xff,0x5da970:0xcb3,0x5d3890:824,0x5d4160:206,
        0x5dc170:7,0x5dcd50:31,0x5d51c0:29,0x41b320:61,
        0x5d36e0:24,0x5dc2e0:6,0x40ffd0:37,0x663170:14}
INSPECTION_ONLY={0x5d22e0:529,0x5d4e90:124}
def verify(data):
    if hashlib.sha256(data).hexdigest()!=PATCHED_EXPECTED:raise ValueError('Exact supplied engine required')
    pe=pefile.PE(data=data);cs=Cs(CS_ARCH_X86,CS_MODE_32);ranges={}
    if pe.OPTIONAL_HEADER.ImageBase!=0x400000 or pe.FILE_HEADER.Machine!=0x14c:raise ValueError('PE layout differs')
    for start,size in {**RANGES,**INSPECTION_ONLY}.items():
        blob=pe.get_data(start-0x400000,size);ins=list(cs.disasm(blob,start))
        if sum(i.size for i in ins)!=size or ins[-1].mnemonic!='ret':raise ValueError('Incomplete overlay placement range '+hex(start))
        ranges[hex(start)]={'bytes':size,'instructions':len(ins),'sha256':hashlib.sha256(blob).hexdigest()}
    for vt,slots in {0x7a77f4:{0x2c:0x5dc2e0,0x84:0x5dc170,0xd4:0x5d3890,
      0xf0:0x5d4e90,0x11c:0x5da970,0x12c:0x5d36e0,0x19c:0x5d51c0,0x1a0:0x41b320},
      0x7a7a08:{0x6c:0x5dcd50}}.items():
        for slot,target in slots.items():
            if struct.unpack('<I',pe.get_data(vt+slot-0x400000,4))[0]!=target:raise ValueError('Overlay placement dispatch differs')
    return {'ranges':{key:value for key,value in ranges.items() if int(key,16) in RANGES},
      'inspection_only':{key:value for key,value in ranges.items() if int(key,16) in INSPECTION_ONLY},
      'scope':'Complete Overlay constructor/Mark and Object Unlimbo/Mark/identity/counter children; loading nonzero, nonwall/nonbridge/no-animation ordinary type. Provider/counter initial state supplied. Base construction and retirement roots inspection only; base construction, registry growth, animation absence, Cell lookup/resource/recalculation and retirement effects supplied. No complete base initialization, alternate overlay placement, actual retirement/destruction/heap ownership, runtime or whole-frame claim.'}
